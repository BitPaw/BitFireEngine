#include "ID3.h"

#include <File/ByteStream.h>
#include <Text/Text.h>

#include "ID3Version.h"
#include "ID3v2xFrameTag.h"

#define ID3HeaderSignature {'I','D','3'}
#define ID3Debug 1

#if ID3Debug
#include <cstdio>
#endif

BF::ID3::ID3()
{
    Text::Clear(Title, ID3TitleSize);
    Text::Clear(Artist, ID3ArtistSize);
    Text::Clear(Album, ID3AlbumSize);
    Text::Clear(Year, ID3YearSize);
    Text::Clear(Comment, ID3CommentSize);

    Genre = -1;
    TrackID = -1;
}

size_t BF::ID3::Parse(const unsigned char* data, const size_t dataSize)
{
    ByteStream dataStream(data, dataSize);
    ID3Version version = ID3Version::Invalid;

    //Check header
    {
        // Einen ID3v2-Block erkennt man am Header, dessen erste fünf Bytes aus der Zeichenkette „ID3“ und der ID3v2-Version (z. B. $04 00 für ID3v2.4) bestehen
        const unsigned char signbature[3] = ID3HeaderSignature;
        const size_t signbatureSize = sizeof(signbature);
        const bool isValidHeader = dataStream.ReadAndCompare(signbature, signbatureSize);

        if(!isValidHeader)
        {
            return 0;
        }
    }

    // Check Version
    {
        char versionTag[2];

        dataStream.Read(versionTag, 2);

        switch(versionTag[0])
        {
            case 0x00:
                version = ID3Version::v2x0;
                break;

            case 0x02:
                version = ID3Version::v2x2;
                break;

            case 0x03:
                version = ID3Version::v2x3;
                break;

            case 0x04:
                version = ID3Version::v2x4;
                break;

            default: // Version is probably 1.x
            {
                const Byte* trackIDAdress = dataStream.CursorCurrentAdress() + ID3CommentSize - 2;
                const unsigned short trackIDSymbol = ((unsigned short)trackIDAdress[0]) << 8 + trackIDAdress[1];
                const bool isVersion1x0 = trackIDSymbol == 0x0000;

                if(isVersion1x0)
                {
                    version = ID3Version::v1x0;
                }
                else
                {
                    version = ID3Version::v1x1;
                }

                dataStream.CursorRewind(2u); // Go the steps back from the version, as 1.x does not have this field.

                break;
            }
        }

        // Cancel if version is invalid
        {
            const bool isValidVersion = version != BF::ID3Version::Invalid;

            if(!isValidVersion)
            {
                return 0;
            }
        }
    }

    // Parse
    {
        const bool useOldHeader = version == BF::ID3Version::v1x0 || version == BF::ID3Version::v1x1;

        if(useOldHeader)
        {
            const bool hasTrackID = version == BF::ID3Version::v1x1;

            dataStream.Read(Title, ID3TitleSize);
            dataStream.Read(Artist, ID3ArtistSize);
            dataStream.Read(Album, ID3AlbumSize);
            dataStream.Read(Year, ID3YearSize);

            if(hasTrackID)
            {
                dataStream.Read(Comment, ID3CommentSize - 1);
                dataStream.Read(TrackID);
            }
            else
            {
                dataStream.Read(Comment, ID3CommentSize);
            }

            dataStream.Read(Genre);
        }
        else
        {
            unsigned int sizeOfDataSegment = 0;
            bool a = false;
            bool b = false;
            bool c = false;

            // Read flags
            {
                unsigned char flags = 0;

                dataStream.Read(flags);

                a = (flags & 0b10000000) >> 7;
                b = (flags & 0b01000000) >> 6;
                c = (flags & 0b00100000) >> 5;
            }

            // read Size
            {
                ClusterInt sizeCluster;

                dataStream.Read(sizeCluster.Data, 4u);

                // Size format: x000 x000 x000 x000 => 28 Bit int
                // The first bit of each byte not only unused but shall be merged!
                // Some banana thought this was a good idea, as to
                // provide a limitation of how big the value can be.

                const unsigned int as = (unsigned int)sizeCluster.A << (16 - 3);
                const unsigned int bs = (unsigned int)sizeCluster.B << (12 - 2);
                const unsigned int cs = (unsigned int)sizeCluster.C << (8 - 1);
                const unsigned int ds = (unsigned int)sizeCluster.D << 0;

                sizeOfDataSegment = as + bs + cs + ds;
            }

#if ID3Debug
            printf("[ID3][Version 2.x] Size:%i\n", sizeOfDataSegment);
#endif

            switch(version)
            {
                case BF::ID3Version::v2x0:
                    break;
                case BF::ID3Version::v2x2:
                    break;
                case BF::ID3Version::v2x3:
                case BF::ID3Version::v2x4:
                {
                    const size_t posCurrent = dataStream.DataSize;
                    const size_t posExpectedMax = dataStream.DataCursorPosition + sizeOfDataSegment;

                    dataStream.DataSize = (posCurrent < posExpectedMax) ? posCurrent : posExpectedMax;

                    while(!dataStream.IsAtEnd()) // size
                    {
                        // Read 4 byte indexes
                        ClusterInt indentifier;
                        unsigned int frameSize = 0;
                        unsigned short frameFlags = 0;

                        dataStream.Read(indentifier.Data, 4u);
                        dataStream.Read(frameSize, Endian::Big);
                        dataStream.Read(frameFlags, Endian::Big);

                        const ID3v2xFrameTag frameTag = ConvertID3v2xFrameTag(indentifier.Value);
                        const bool unkownTag = frameTag == ID3v2xFrameTag::Invalid;

                        if(unkownTag)
                        {
                            const bool emptyDataDertected = unkownTag && (frameSize == 0);

                            if(emptyDataDertected)
                            {
                                dataStream.CursorToEnd();
                                break; // Cancel while loop, as there is nothing else to parse.
                            }
                        }

#if ID3Debug
                        printf
                        (
                            "[Chunk %c%c%c%c] %i Bytes\n",
                            indentifier.A,
                            indentifier.B,
                            indentifier.C,
                            indentifier.D,
                            frameSize
                         );
#endif

                        size_t posAfterChunk = dataStream.DataCursorPosition + frameSize;


#if 0 // Skip
                        dataStream.CursorAdvance(frameSize);
#else

                        switch(frameTag)
                        {
                            case BF::ID3v2xFrameTag::AudioEncryption:
                                break;
                            case BF::ID3v2xFrameTag::AttachedPicture:
                                break;
                            case BF::ID3v2xFrameTag::Comments:
                            {
                                unsigned char textEncoding = 0;
                                char language[3];

                                dataStream.Read(textEncoding);
                                dataStream.Read(language, 3u);

                                size_t insertOffset = 0;

                                while(dataStream.DataCursorPosition < posAfterChunk) // There can be multible comments, but only one language.
                                {
                                    char stringEncoding[2];

                                    dataStream.Read(stringEncoding, 2u);

                                    dataStream.ReadUntil(Comment + insertOffset, frameSize - 3, L'\0');
                                }

                                break;
                            }
                            case BF::ID3v2xFrameTag::CommercialFrame:
                                break;
                            case BF::ID3v2xFrameTag::EncryptionMethodRegistration:
                                break;
                            case BF::ID3v2xFrameTag::Equalization:
                                break;
                            case BF::ID3v2xFrameTag::EventTimingCodes:
                                break;
                            case BF::ID3v2xFrameTag::GeneralEncapsulatedObject:
                                break;
                            case BF::ID3v2xFrameTag::GroupIdentificationRegistration:
                                break;
                            case BF::ID3v2xFrameTag::InvolvedPeopleList:
                                break;
                            case BF::ID3v2xFrameTag::LinkedInformation:
                                break;
                            case BF::ID3v2xFrameTag::MusicCDIdentifier:
                                break;
                            case BF::ID3v2xFrameTag::MPEGLocationLookupTable:
                                break;
                            case BF::ID3v2xFrameTag::OwnershipFrame:
                                break;
                            case BF::ID3v2xFrameTag::PrivateFrame:
                            {
                                break;
                            }
                            case BF::ID3v2xFrameTag::PlayCounter:
                                break;
                            case BF::ID3v2xFrameTag::Popularimeter:
                            {
                                const Byte* emailToUser = dataStream.CursorCurrentAdress();
                                const size_t emailToUserSize = Text::Length((char*)emailToUser); //frameSize - 6u;
                                unsigned char rating = 0;
                                // counter?

                                // Copy

                                dataStream.CursorAdvance(emailToUserSize+1);
                                dataStream.Read(rating);

                                break;
                            }
                            case BF::ID3v2xFrameTag::PositionSynchronisationFrame:
                                break;
                            case BF::ID3v2xFrameTag::RecommendedBufferSize:
                                break;
                            case BF::ID3v2xFrameTag::RelativeVolumeAdjustment:
                                break;
                            case BF::ID3v2xFrameTag::Reverb:
                                break;
                            case BF::ID3v2xFrameTag::SynchronizedLyric:
                                break;
                            case BF::ID3v2xFrameTag::SynchronizedTempocodes:
                                break;
                            case BF::ID3v2xFrameTag::Album:
                            {
                                dataStream.CursorAdvance(3u);
                                dataStream.Read(Album, frameSize-3);

                                break;
                            }
                            case BF::ID3v2xFrameTag::BeatsPerMinute:
                            {
                                // Is text, convert to int
                                BeatsPerMinute = 0;
                                break;
                            }
                            case BF::ID3v2xFrameTag::Composer:
                            {
                                dataStream.CursorAdvance(3u);
                                dataStream.Read(Composer, frameSize - 3);
                                break;
                            }
                            case BF::ID3v2xFrameTag::ContentType:
                            {
                                // GenreString -> enum
                                break;
                            }
                            case BF::ID3v2xFrameTag::CopyrightMessage:
                                break;
                            case BF::ID3v2xFrameTag::Date:
                                break;
                            case BF::ID3v2xFrameTag::PlaylistDelay:
                                break;
                            case BF::ID3v2xFrameTag::EncodedBy:
                                break;
                            case BF::ID3v2xFrameTag::Lyricist:
                                break;
                            case BF::ID3v2xFrameTag::FileType:
                                break;
                            case BF::ID3v2xFrameTag::Time:
                                break;
                            case BF::ID3v2xFrameTag::ContentGroupDescription:
                                break;
                            case BF::ID3v2xFrameTag::Title:
                            {
                                dataStream.CursorAdvance(3u);
                                dataStream.Read(Title, frameSize - 3);
                                break;
                            }
                            case BF::ID3v2xFrameTag::Subtitle:
                            {
                                break;
                            }
                            case BF::ID3v2xFrameTag::InitialKey:
                                break;
                            case BF::ID3v2xFrameTag::Language:
                                break;
                            case BF::ID3v2xFrameTag::Length:
                                break;
                            case BF::ID3v2xFrameTag::MediaType:
                                break;
                            case BF::ID3v2xFrameTag::OriginalAlbum:
                                break;
                            case BF::ID3v2xFrameTag::OriginalFilename:
                                break;
                            case BF::ID3v2xFrameTag::OriginalLyricist:
                                break;
                            case BF::ID3v2xFrameTag::OriginalArtist:
                                break;
                            case BF::ID3v2xFrameTag::OriginalReleaseYear:
                                break;
                            case BF::ID3v2xFrameTag::FileOwner:
                                break;
                            case BF::ID3v2xFrameTag::LeadPerformer:
                            {
                                dataStream.CursorAdvance(3u);
                                dataStream.Read(Artist, frameSize-3);
                                break;
                            }
                            case BF::ID3v2xFrameTag::Band:
                            {

                                break;
                            }
                            case BF::ID3v2xFrameTag::Conductor:
                            {
                                dataStream.CursorAdvance(3u);
                                dataStream.Read(Album, frameSize-3);
                                break;
                            }
                            case BF::ID3v2xFrameTag::InterpretedBy:
                                break;
                            case BF::ID3v2xFrameTag::PartOfASet:
                                break;
                            case BF::ID3v2xFrameTag::Publisher:
                                break;
                            case BF::ID3v2xFrameTag::TrackNumber:
                                break;
                            case BF::ID3v2xFrameTag::RecordingDates:
                                break;
                            case BF::ID3v2xFrameTag::InternetRadioStationName:
                                break;
                            case BF::ID3v2xFrameTag::InternetRadioStationOwner:
                                break;
                            case BF::ID3v2xFrameTag::Size:
                                break;
                            case BF::ID3v2xFrameTag::InternationalStandardRecordingCode:
                                break;
                            case BF::ID3v2xFrameTag::SoftwareHardwaresettingsUsedForEncoding:
                                break;
                            case BF::ID3v2xFrameTag::Year:
                                break;
                            case BF::ID3v2xFrameTag::UserDefinedText:
                                break;
                            case BF::ID3v2xFrameTag::UniqueFileIdentifier:
                                break;
                            case BF::ID3v2xFrameTag::TermsOfUse:
                                break;
                            case BF::ID3v2xFrameTag::UnsychronizedLyric:
                                break;
                            case BF::ID3v2xFrameTag::CommercialInformation:
                                break;
                            case BF::ID3v2xFrameTag::CopyrightLegalInformation:
                                break;
                            case BF::ID3v2xFrameTag::OfficialAudioFileWebpage:
                                break;
                            case BF::ID3v2xFrameTag::OfficialArtistPerformerWebpage:
                                break;
                            case BF::ID3v2xFrameTag::OfficialAudioSourceWebpage:
                                break;
                            case BF::ID3v2xFrameTag::InternetRadioStationHomepage:
                                break;
                            case BF::ID3v2xFrameTag::Payment:
                                break;
                            case BF::ID3v2xFrameTag::PublishersOfficialWebpage:
                                break;
                            case BF::ID3v2xFrameTag::UserDefinedURLLinkFrame:
                                break;

                            case BF::ID3v2xFrameTag::Invalid:
                                break;
                        }
#endif
                        if(dataStream.DataCursorPosition < posAfterChunk)
                        {
                            printf("Unhandle chunk detected!\n");

                            dataStream.DataCursorPosition = posAfterChunk;
                        }
                    }

                    break;
                }
            }
        }
    }

    return dataStream.DataCursorPosition;
}
