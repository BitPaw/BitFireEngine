#include "ID3.h"

#include <File/ParsingStream.h>
#include <Text/Text.h>
#include <Container/ClusterInt.h>

#define ID3HeaderSignature {'I','D','3'}
#define ID3Debug 0

#if ID3Debug
#include <cstdio>
#endif

ID3v2xFrameTag ConvertID3v2xFrameTag(const unsigned int id3v2xFrameTagID)
{
    switch(id3v2xFrameTagID)
    {
        case MakeInt('A', 'E', 'N', 'C'): return AudioEncryption;
        case MakeInt('A', 'P', 'I', 'C'): return AttachedPicture;
        case MakeInt('C', 'O', 'M', 'M'): return Comments;
        case MakeInt('C', 'O', 'M', 'R'): return CommercialFrame;
        case MakeInt('E', 'N', 'C', 'R'): return EncryptionMethodRegistration;
        case MakeInt('E', 'Q', 'U', 'A'): return Equalization;
        case MakeInt('E', 'T', 'C', 'O'): return EventTimingCodes;
        case MakeInt('G', 'E', 'O', 'B'): return GeneralEncapsulatedObject;
        case MakeInt('G', 'R', 'I', 'D'): return GroupIdentificationRegistration;
        case MakeInt('I', 'P', 'L', 'S'): return InvolvedPeopleList;
        case MakeInt('L', 'I', 'N', 'K'): return LinkedInformation;
        case MakeInt('M', 'C', 'D', 'I'): return MusicCDIdentifier;
        case MakeInt('M', 'L', 'L', 'T'): return MPEGLocationLookupTable;
        case MakeInt('O', 'W', 'N', 'E'): return OwnershipFrame;
        case MakeInt('P', 'R', 'I', 'V'): return PrivateFrame;
        case MakeInt('P', 'C', 'N', 'T'): return PlayCounter;
        case MakeInt('P', 'O', 'P', 'M'): return Popularimeter;
        case MakeInt('P', 'O', 'S', 'S'): return PositionSynchronisationFrame;
        case MakeInt('R', 'B', 'U', 'F'): return RecommendedBufferSize;
        case MakeInt('R', 'V', 'A', 'D'): return RelativeVolumeAdjustment;
        case MakeInt('R', 'V', 'R', 'B'): return Reverb;
        case MakeInt('S', 'Y', 'L', 'T'): return SynchronizedLyric;
        case MakeInt('S', 'Y', 'T', 'C'): return SynchronizedTempocodes;
        case MakeInt('T', 'A', 'L', 'B'): return Album;
        case MakeInt('T', 'B', 'P', 'M'): return BeatsPerMinute;
        case MakeInt('T', 'C', 'O', 'M'): return Composer;
        case MakeInt('T', 'C', 'O', 'N'): return ContentType;
        case MakeInt('T', 'C', 'O', 'P'): return CopyrightMessage;
        case MakeInt('T', 'D', 'A', 'T'): return Date;
        case MakeInt('T', 'D', 'L', 'Y'): return PlaylistDelay;
        case MakeInt('T', 'E', 'N', 'C'): return EncodedBy;
        case MakeInt('T', 'E', 'X', 'T'): return Lyricist;
        case MakeInt('T', 'F', 'L', 'T'): return FileType;
        case MakeInt('T', 'I', 'M', 'E'): return Time;
        case MakeInt('T', 'I', 'T', '1'): return ContentGroupDescription;
        case MakeInt('T', 'I', 'T', '2'): return Title;
        case MakeInt('T', 'I', 'T', '3'): return Subtitle;
        case MakeInt('T', 'K', 'E', 'Y'): return InitialKey;
        case MakeInt('T', 'L', 'A', 'N'): return Language;
        case MakeInt('T', 'L', 'E', 'N'): return Length;
        case MakeInt('T', 'M', 'E', 'D'): return MediaType;
        case MakeInt('T', 'O', 'A', 'L'): return OriginalAlbum;
        case MakeInt('T', 'O', 'F', 'N'): return OriginalFilename;
        case MakeInt('T', 'O', 'L', 'Y'): return OriginalLyricist;
        case MakeInt('T', 'O', 'P', 'E'): return OriginalArtist;
        case MakeInt('T', 'O', 'R', 'Y'): return OriginalReleaseYear;
        case MakeInt('T', 'O', 'W', 'N'): return FileOwner;
        case MakeInt('T', 'P', 'E', '1'): return LeadPerformer;
        case MakeInt('T', 'P', 'E', '2'): return Band;
        case MakeInt('T', 'P', 'E', '3'): return Conductor;
        case MakeInt('T', 'P', 'E', '4'): return InterpretedBy;
        case MakeInt('T', 'P', 'O', 'S'): return PartOfASet;
        case MakeInt('T', 'P', 'U', 'B'): return Publisher;
        case MakeInt('T', 'R', 'C', 'K'): return TrackNumber;
        case MakeInt('T', 'R', 'D', 'A'): return RecordingDates;
        case MakeInt('T', 'R', 'S', 'N'): return InternetRadioStationName;
        case MakeInt('T', 'R', 'S', 'O'): return InternetRadioStationOwner;
        case MakeInt('T', 'S', 'I', 'Z'): return Size;
        case MakeInt('T', 'S', 'R', 'C'): return InternationalStandardRecordingCode;
        case MakeInt('T', 'S', 'S', 'E'): return SoftwareHardwaresettingsUsedForEncoding;
        case MakeInt('T', 'Y', 'E', 'R'): return Year;
        case MakeInt('T', 'X', 'X', 'X'): return UserDefinedText;
        case MakeInt('U', 'F', 'I', 'D'): return UniqueFileIdentifier;
        case MakeInt('U', 'S', 'E', 'R'): return TermsOfUse;
        case MakeInt('U', 'S', 'L', 'T'): return UnsychronizedLyric;
        case MakeInt('W', 'C', 'O', 'M'): return CommercialInformation;
        case MakeInt('W', 'C', 'O', 'P'): return CopyrightLegalInformation;
        case MakeInt('W', 'O', 'A', 'F'): return OfficialAudioFileWebpage;
        case MakeInt('W', 'O', 'A', 'R'): return OfficialArtistPerformerWebpage;
        case MakeInt('W', 'O', 'A', 'S'): return OfficialAudioSourceWebpage;
        case MakeInt('W', 'O', 'R', 'S'): return InternetRadioStationHomepage;
        case MakeInt('W', 'P', 'A', 'Y'): return Payment;
        case MakeInt('W', 'P', 'U', 'B'): return PublishersOfficialWebpage;
        case MakeInt('W', 'X', 'X', 'X'): return UserDefinedURLLinkFrame;

        default:
            return ID3v2xFrameTagInvalid;
    }
}

ActionResult ID3Parse(ID3* id3, const void* data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;

    ParsingStreamConstruct(&parsingStream, data, dataSize);

    ID3Version version = ID3VersionInvalid;

    *dataRead = 0;

    //Check header
    {
        // Einen ID3v2-Block erkennt man am Header, dessen erste fünf Bytes aus der Zeichenkette „ID3“ und der ID3v2-Version (z. B. $04 00 für ID3v2.4) bestehen
        const unsigned char signbature[3] = ID3HeaderSignature;
        const size_t signbatureSize = sizeof(signbature);  
        const unsigned char isValidHeader = ParsingStreamReadAndCompare(&parsingStream, signbature, signbatureSize);
        
        if(!isValidHeader)
        {
            return ResultInvalidHeaderSignature;
        }
    }

    // Check Version
    {
        char versionTag[2];

        ParsingStreamReadD(&parsingStream, versionTag, 2);

        switch(versionTag[0])
        {
            case 0x00:
                version = ID3Versionv2x0;
                break;

            case 0x02:
                version = ID3Versionv2x2;
                break;

            case 0x03:
                version = ID3Versionv2x3;
                break;

            case 0x04:
                version = ID3Versionv2x4;
                break;

            default: // Version is probably 1.x
            {
                const unsigned char* trackIDAdress = ParsingStreamCursorPosition(&parsingStream) + ID3CommentSize - 2;
                const unsigned short trackIDSymbol = ((unsigned short)trackIDAdress[0]) << 8 + trackIDAdress[1];
                const unsigned char isVersion1x0 = trackIDSymbol == 0x0000;

                if(isVersion1x0)
                {
                    version = ID3Versionv1x0;
                }
                else
                {
                    version = ID3Versionv1x1;
                }

                //dataStream.CursorRewind(2u); // Go the steps back from the version, as 1.x does not have this field.

                break;
            }
        }

        // Cancel if version is invalid
        {
            const unsigned char isValidVersion = version != ID3VersionInvalid;

            if(!isValidVersion)
            {
                return 0;
            }
        }
    }

    // Parse
    {
        const unsigned char useOldHeader = version == ID3Versionv1x0 || version == ID3Versionv1x1;

        if(useOldHeader)
        {
            const unsigned char hasTrackID = version == ID3Versionv1x1;

            ParsingStreamReadD(&parsingStream, id3->Title, ID3TitleSize);
            ParsingStreamReadD(&parsingStream, id3->Artist, ID3TitleSize);
            ParsingStreamReadD(&parsingStream, id3->Album, ID3TitleSize);
            ParsingStreamReadD(&parsingStream, id3->Year, ID3TitleSize);

            if(hasTrackID)
            {
                ParsingStreamReadD(&parsingStream, id3->Comment, ID3CommentSize - 1);
                ParsingStreamReadC(&parsingStream, &id3->TrackID);
            }
            else
            {
                ParsingStreamReadD(&parsingStream, id3->Comment, ID3CommentSize);
            }

            ParsingStreamReadC(&parsingStream, &id3->Genre);
        }
        else
        {
            unsigned int sizeOfDataSegment = 0;
            unsigned char a = 0;
            unsigned char b = 0;
            unsigned char c = 0;

            // Read flags
            {
                unsigned char flags = 0;

                ParsingStreamReadC(&parsingStream, &flags);

                a = (flags & 0b10000000) >> 7;
                b = (flags & 0b01000000) >> 6;
                c = (flags & 0b00100000) >> 5;
            }

            // read Size
            {
                ClusterInt sizeCluster;

                ParsingStreamReadD(&parsingStream, sizeCluster.Data, 4u);

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
                case ID3Versionv2x0:
                    break;
                case ID3Versionv2x2:
                    break;
                case ID3Versionv2x3:
                case ID3Versionv2x4:
                {
                    const size_t posCurrent = parsingStream.DataSize;
                    const size_t posExpectedMax = parsingStream.DataCursor + sizeOfDataSegment;

                    parsingStream.DataSize = (posCurrent < posExpectedMax) ? posCurrent : posExpectedMax;

                    while(!ParsingStreamIsAtEnd(&parsingStream))
                    {
                        // Read 4 byte indexes
                        ClusterInt indentifier;
                        unsigned int frameSize = 0;
                        unsigned short frameFlags = 0;

                        ParsingStreamReadD(&parsingStream, indentifier.Data, 4u);
                        ParsingStreamReadIU(&parsingStream, frameSize, EndianBig);
                        ParsingStreamReadIU(&parsingStream, frameFlags, EndianBig);
    
                        const ID3v2xFrameTag frameTag = ConvertID3v2xFrameTag(indentifier.Value);
                        const unsigned char unkownTag = frameTag == ID3v2xFrameTagInvalid;

                        if(unkownTag)
                        {
                            const unsigned char emptyDataDertected = unkownTag && (frameSize == 0);

                            if(emptyDataDertected)
                            {
                                ParsingStreamCursorToEnd(&parsingStream);
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

                        size_t posAfterChunk = parsingStream.DataCursor + frameSize;


#if 0 // Skip
                        dataStream.CursorAdvance(frameSize);
#else

                        switch(frameTag)
                        {
                            case AudioEncryption:
                                break;
                            case AttachedPicture:
                                break;
                            case Comments:
                            {
                                unsigned char textEncoding = 0;
                                char language[3];

                                /*
                                dataStream.Read(textEncoding);
                                dataStream.Read(language, 3u);

                                size_t insertOffset = 0;

                                while(dataStream.DataCursor < posAfterChunk) // There can be multible comments, but only one language.
                                {
                                    char stringEncoding[2];

                                    dataStream.Read(stringEncoding, 2u);

                                    dataStream.ReadUntil(Comment + insertOffset, frameSize - 3, L'\0');
                                }
                                */
                                break;
                            }
                            case CommercialFrame:
                                break;
                            case EncryptionMethodRegistration:
                                break;
                            case Equalization:
                                break;
                            case EventTimingCodes:
                                break;
                            case GeneralEncapsulatedObject:
                                break;
                            case GroupIdentificationRegistration:
                                break;
                            case InvolvedPeopleList:
                                break;
                            case LinkedInformation:
                                break;
                            case MusicCDIdentifier:
                                break;
                            case MPEGLocationLookupTable:
                                break;
                            case OwnershipFrame:
                                break;
                            case PrivateFrame:
                            {
                                break;
                            }
                            case PlayCounter:
                                break;
                            case Popularimeter:
                            {
                                const unsigned char* emailToUser = ParsingStreamCursorPosition(&parsingStream);
                                const size_t maximalToRead = ParsingStreamRemainingSize(&parsingStream) - 6u;
                                const size_t emailToUserSize = TextLengthA((char*)emailToUser, maximalToRead);
                                unsigned char rating = 0;
                                // counter?

                                // Copy

                                ParsingStreamCursorAdvance(&parsingStream, emailToUserSize + 1);
                                ParsingStreamReadC(&parsingStream, rating);

                                break;
                            }
                            case PositionSynchronisationFrame:
                                break;
                            case RecommendedBufferSize:
                                break;
                            case RelativeVolumeAdjustment:
                                break;
                            case Reverb:
                                break;
                            case SynchronizedLyric:
                                break;
                            case SynchronizedTempocodes:
                                break;
                            case Album:
                            {
                               // dataStream.CursorAdvance(3u);
                                //dataStream.Read(Album, frameSize - 3);

                                break;
                            }
                            case BeatsPerMinute:
                            {
                                // Is text, convert to int
                                id3->BeatsPerMinute = 0;
                                break;
                            }
                            case Composer:
                            {
                               // dataStream.CursorAdvance(3u);
                               // dataStream.Read(Composer, frameSize - 3);
                                break;
                            }
                            case ContentType:
                            {
                                // GenreString -> enum
                                break;
                            }
                            case CopyrightMessage:
                                break;
                            case Date:
                                break;
                            case PlaylistDelay:
                                break;
                            case EncodedBy:
                                break;
                            case Lyricist:
                                break;
                            case FileType:
                                break;
                            case Time:
                                break;
                            case ContentGroupDescription:
                                break;
                            case Title:
                            {
                               // dataStream.CursorAdvance(3u);
                                //dataStream.Read(Title, frameSize - 3);
                                break;
                            }
                            case Subtitle:
                            {
                                break;
                            }
                            case InitialKey:
                                break;
                            case Language:
                                break;
                            case Length:
                                break;
                            case MediaType:
                                break;
                            case OriginalAlbum:
                                break;
                            case OriginalFilename:
                                break;
                            case OriginalLyricist:
                                break;
                            case OriginalArtist:
                                break;
                            case OriginalReleaseYear:
                                break;
                            case FileOwner:
                                break;
                            case LeadPerformer:
                            {
                                //dataStream.CursorAdvance(3u);
                               // dataStream.Read(Artist, frameSize - 3);
                                break;
                            }
                            case Band:
                            {

                                break;
                            }
                            case Conductor:
                            {
                                //dataStream.CursorAdvance(3u);
                                //dataStream.Read(Album, frameSize - 3);
                                break;
                            }
                            case InterpretedBy:
                                break;
                            case PartOfASet:
                                break;
                            case Publisher:
                                break;
                            case TrackNumber:
                                break;
                            case RecordingDates:
                                break;
                            case InternetRadioStationName:
                                break;
                            case InternetRadioStationOwner:
                                break;
                            case Size:
                                break;
                            case InternationalStandardRecordingCode:
                                break;
                            case SoftwareHardwaresettingsUsedForEncoding:
                                break;
                            case Year:
                                break;
                            case UserDefinedText:
                                break;
                            case UniqueFileIdentifier:
                                break;
                            case TermsOfUse:
                                break;
                            case UnsychronizedLyric:
                                break;
                            case CommercialInformation:
                                break;
                            case CopyrightLegalInformation:
                                break;
                            case OfficialAudioFileWebpage:
                                break;
                            case OfficialArtistPerformerWebpage:
                                break;
                            case OfficialAudioSourceWebpage:
                                break;
                            case InternetRadioStationHomepage:
                                break;
                            case Payment:
                                break;
                            case PublishersOfficialWebpage:
                                break;
                            case UserDefinedURLLinkFrame:
                                break;
                        }
#endif

                        const unsigned char hasUnhandleChunkDetected = parsingStream.DataCursor < posAfterChunk;

                        if(hasUnhandleChunkDetected)
                        {
                            printf("Unhandle chunk detected!\n");

                            parsingStream.DataCursor = posAfterChunk;
                        }
                    }

                    break;
                }
            }
        }
    }

    *dataRead = parsingStream.DataCursor;

    return ResultSuccessful;
}
