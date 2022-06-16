#include "ID3v2xFrameTag.h"

#include <Container/ClusterInt.h>

BF::ID3v2xFrameTag BF::ConvertID3v2xFrameTag(const unsigned int id3v2xFrameTagID)
{
    switch(id3v2xFrameTagID)
    {
        case MakeInt('A', 'E', 'N', 'C'): return ID3v2xFrameTag::AudioEncryption;
        case MakeInt('A', 'P', 'I', 'C'): return ID3v2xFrameTag::AttachedPicture;
        case MakeInt('C', 'O', 'M', 'M'): return ID3v2xFrameTag::Comments;
        case MakeInt('C', 'O', 'M', 'R'): return ID3v2xFrameTag::CommercialFrame;
        case MakeInt('E', 'N', 'C', 'R'): return ID3v2xFrameTag::EncryptionMethodRegistration;
        case MakeInt('E', 'Q', 'U', 'A'): return ID3v2xFrameTag::Equalization;
        case MakeInt('E', 'T', 'C', 'O'): return ID3v2xFrameTag::EventTimingCodes;
        case MakeInt('G', 'E', 'O', 'B'): return ID3v2xFrameTag::GeneralEncapsulatedObject;
        case MakeInt('G', 'R', 'I', 'D'): return ID3v2xFrameTag::GroupIdentificationRegistration;
        case MakeInt('I', 'P', 'L', 'S'): return ID3v2xFrameTag::InvolvedPeopleList;
        case MakeInt('L', 'I', 'N', 'K'): return ID3v2xFrameTag::LinkedInformation;
        case MakeInt('M', 'C', 'D', 'I'): return ID3v2xFrameTag::MusicCDIdentifier;
        case MakeInt('M', 'L', 'L', 'T'): return ID3v2xFrameTag::MPEGLocationLookupTable;
        case MakeInt('O', 'W', 'N', 'E'): return ID3v2xFrameTag::OwnershipFrame;
        case MakeInt('P', 'R', 'I', 'V'): return ID3v2xFrameTag::PrivateFrame;
        case MakeInt('P', 'C', 'N', 'T'): return ID3v2xFrameTag::PlayCounter;
        case MakeInt('P', 'O', 'P', 'M'): return ID3v2xFrameTag::Popularimeter;
        case MakeInt('P', 'O', 'S', 'S'): return ID3v2xFrameTag::PositionSynchronisationFrame;
        case MakeInt('R', 'B', 'U', 'F'): return ID3v2xFrameTag::RecommendedBufferSize;
        case MakeInt('R', 'V', 'A', 'D'): return ID3v2xFrameTag::RelativeVolumeAdjustment;
        case MakeInt('R', 'V', 'R', 'B'): return ID3v2xFrameTag::Reverb;
        case MakeInt('S', 'Y', 'L', 'T'): return ID3v2xFrameTag::SynchronizedLyric;
        case MakeInt('S', 'Y', 'T', 'C'): return ID3v2xFrameTag::SynchronizedTempocodes;
        case MakeInt('T', 'A', 'L', 'B'): return ID3v2xFrameTag::Album;
        case MakeInt('T', 'B', 'P', 'M'): return ID3v2xFrameTag::BeatsPerMinute;
        case MakeInt('T', 'C', 'O', 'M'): return ID3v2xFrameTag::Composer;
        case MakeInt('T', 'C', 'O', 'N'): return ID3v2xFrameTag::ContentType;
        case MakeInt('T', 'C', 'O', 'P'): return ID3v2xFrameTag::CopyrightMessage;
        case MakeInt('T', 'D', 'A', 'T'): return ID3v2xFrameTag::Date;
        case MakeInt('T', 'D', 'L', 'Y'): return ID3v2xFrameTag::PlaylistDelay;
        case MakeInt('T', 'E', 'N', 'C'): return ID3v2xFrameTag::EncodedBy;
        case MakeInt('T', 'E', 'X', 'T'): return ID3v2xFrameTag::Lyricist;
        case MakeInt('T', 'F', 'L', 'T'): return ID3v2xFrameTag::FileType;
        case MakeInt('T', 'I', 'M', 'E'): return ID3v2xFrameTag::Time;
        case MakeInt('T', 'I', 'T', '1'): return ID3v2xFrameTag::ContentGroupDescription;
        case MakeInt('T', 'I', 'T', '2'): return ID3v2xFrameTag::Title;
        case MakeInt('T', 'I', 'T', '3'): return ID3v2xFrameTag::Subtitle;
        case MakeInt('T', 'K', 'E', 'Y'): return ID3v2xFrameTag::InitialKey;
        case MakeInt('T', 'L', 'A', 'N'): return ID3v2xFrameTag::Language;
        case MakeInt('T', 'L', 'E', 'N'): return ID3v2xFrameTag::Length;
        case MakeInt('T', 'M', 'E', 'D'): return ID3v2xFrameTag::MediaType;
        case MakeInt('T', 'O', 'A', 'L'): return ID3v2xFrameTag::OriginalAlbum;
        case MakeInt('T', 'O', 'F', 'N'): return ID3v2xFrameTag::OriginalFilename;
        case MakeInt('T', 'O', 'L', 'Y'): return ID3v2xFrameTag::OriginalLyricist;
        case MakeInt('T', 'O', 'P', 'E'): return ID3v2xFrameTag::OriginalArtist;
        case MakeInt('T', 'O', 'R', 'Y'): return ID3v2xFrameTag::OriginalReleaseYear;
        case MakeInt('T', 'O', 'W', 'N'): return ID3v2xFrameTag::FileOwner;
        case MakeInt('T', 'P', 'E', '1'): return ID3v2xFrameTag::LeadPerformer;
        case MakeInt('T', 'P', 'E', '2'): return ID3v2xFrameTag::Band;
        case MakeInt('T', 'P', 'E', '3'): return ID3v2xFrameTag::Conductor;
        case MakeInt('T', 'P', 'E', '4'): return ID3v2xFrameTag::InterpretedBy;
        case MakeInt('T', 'P', 'O', 'S'): return ID3v2xFrameTag::PartOfASet;
        case MakeInt('T', 'P', 'U', 'B'): return ID3v2xFrameTag::Publisher;
        case MakeInt('T', 'R', 'C', 'K'): return ID3v2xFrameTag::TrackNumber;
        case MakeInt('T', 'R', 'D', 'A'): return ID3v2xFrameTag::RecordingDates;
        case MakeInt('T', 'R', 'S', 'N'): return ID3v2xFrameTag::InternetRadioStationName;
        case MakeInt('T', 'R', 'S', 'O'): return ID3v2xFrameTag::InternetRadioStationOwner;
        case MakeInt('T', 'S', 'I', 'Z'): return ID3v2xFrameTag::Size;
        case MakeInt('T', 'S', 'R', 'C'): return ID3v2xFrameTag::InternationalStandardRecordingCode;
        case MakeInt('T', 'S', 'S', 'E'): return ID3v2xFrameTag::SoftwareHardwaresettingsUsedForEncoding;
        case MakeInt('T', 'Y', 'E', 'R'): return ID3v2xFrameTag::Year;
        case MakeInt('T', 'X', 'X', 'X'): return ID3v2xFrameTag::UserDefinedText;
        case MakeInt('U', 'F', 'I', 'D'): return ID3v2xFrameTag::UniqueFileIdentifier;
        case MakeInt('U', 'S', 'E', 'R'): return ID3v2xFrameTag::TermsOfUse;
        case MakeInt('U', 'S', 'L', 'T'): return ID3v2xFrameTag::UnsychronizedLyric;
        case MakeInt('W', 'C', 'O', 'M'): return ID3v2xFrameTag::CommercialInformation;
        case MakeInt('W', 'C', 'O', 'P'): return ID3v2xFrameTag::CopyrightLegalInformation;
        case MakeInt('W', 'O', 'A', 'F'): return ID3v2xFrameTag::OfficialAudioFileWebpage;
        case MakeInt('W', 'O', 'A', 'R'): return ID3v2xFrameTag::OfficialArtistPerformerWebpage;
        case MakeInt('W', 'O', 'A', 'S'): return ID3v2xFrameTag::OfficialAudioSourceWebpage;
        case MakeInt('W', 'O', 'R', 'S'): return ID3v2xFrameTag::InternetRadioStationHomepage;
        case MakeInt('W', 'P', 'A', 'Y'): return ID3v2xFrameTag::Payment;
        case MakeInt('W', 'P', 'U', 'B'): return ID3v2xFrameTag::PublishersOfficialWebpage;
        case MakeInt('W', 'X', 'X', 'X'): return ID3v2xFrameTag::UserDefinedURLLinkFrame;

        default:
            return ID3v2xFrameTag::Invalid;
    }
}
