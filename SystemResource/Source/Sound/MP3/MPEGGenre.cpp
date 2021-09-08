#include "MPEGGenre.hpp"

BF::MPEGGenre BF::MPEGGenreConvert(unsigned char mpegGenre)
{
	switch (mpegGenre)
	{
		case MPEGGenreIDBlues:
			return BF::MPEGGenre::Blues;

		case MPEGGenreIDClassicRock:
			return BF::MPEGGenre::ClassicRock;

		case MPEGGenreIDCountry:
			return BF::MPEGGenre::Country;

		case MPEGGenreIDDance:
			return BF::MPEGGenre::Dance;

		case MPEGGenreIDDisco:
			return BF::MPEGGenre::Disco;

		case MPEGGenreIDFunk:
			return BF::MPEGGenre::Funk;

		case MPEGGenreIDGrunge:
			return BF::MPEGGenre::Grunge;

		case MPEGGenreIDHipHop:
			return BF::MPEGGenre::HipHop;

		case MPEGGenreIDJazz:
			return  BF::MPEGGenre::Jazz;

		case MPEGGenreIDMetal:
			return  BF::MPEGGenre::Metal;

		case MPEGGenreIDNewAge:
			return  BF::MPEGGenre::NewAge;

		case MPEGGenreIDOldies:
			return  BF::MPEGGenre::Oldies;

		case MPEGGenreIDOther:
			return  BF::MPEGGenre::Other;

		case MPEGGenreIDPop:
			return  BF::MPEGGenre::Pop ;

		case MPEGGenreIDRAndB:
			return  BF::MPEGGenre::RAndB;

			/*
		case MPEGGenreIDRap 15:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDReggae 16:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDRock 17:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDTechno 18:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDIndustrial 19:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAlternative 20:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSka 21:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDDeathMetal 22:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPranks 23:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSoundtrack 24:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDEuroTechno 25:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAmbient 26:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDTripHop 27:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDVocal 28:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDJazzFunk 29:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDFusion 30:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDTrance 31:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDClassical 32:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDInstrumental 33:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAcid 34:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDHouse 35:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDGame 36:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSoundClip 37:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDGospel 38:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDNoise 39:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAlternRock 40:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDBass 41:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSoul 42:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPunk 43:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSpace 44:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDMeditative 45:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDInstrumentalPop 46:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDInstrumentalRock 47:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDEthnic 48:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDGothic 49:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDDarkwave 50:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDTechnoIndustrial 51:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDElectronic 52:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPopFolk 53:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDEurodance 54:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDDream 55:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSouthernRock 56:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDComedy 57:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDCult 58:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDGangsta 59:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDTop40 60:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDChristianRap 61:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPopFunk 62:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDJungle 63:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDNativeAmerican 64:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDCabaret 65:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDNewWave 66:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPsychadelic 67:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDRave 68:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDShowtunes 69:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDTrailer 70:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDLoFi 71:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDTribal 72:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAcidPunk 73:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAcidJazz 74:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPolka 75:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDRetro 76:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDMusical 77:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDRockAndRoll 78:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDHardRock 79:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDFolk 80:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDFolkRock 81:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDNationalFolk 82:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSwing 83:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDFastFusion 84:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDBebob 85:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDLatin 86:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDRevival 87:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDCeltic 88:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDBluegrass 89:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAvantgarde 90:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDGothicRock 91:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDProgressiveRock 92:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPsychedelicRock 93:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSymphonicRock 94:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSlowRock 95:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDBigBand 96:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDChorus 97:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDEasyListening 98:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDAcoustic 99:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDHumour 100:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSpeech 101:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDChanson 102:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDOpera 103:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDChamberMusic 104:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSonata 105:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSymphony 106:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDBootyBrass 107:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPrimus 108:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDPornGroove 109:
			return  BF::MPEGGenre : ;

		case MPEGGenreIDSatire 110:
			return  BF::MPEGGenre : ;
			*/

		case MPEGGenreIDSlowJam:
			return  BF::MPEGGenre::SlowJam;

		case MPEGGenreIDClub:
			return  BF::MPEGGenre::Club;

		case MPEGGenreIDTango:
			return  BF::MPEGGenre::Tango;

		case MPEGGenreIDSamba:
			return  BF::MPEGGenre::Samba;

		case MPEGGenreIDFolklore:
			return  BF::MPEGGenre::Folklore;

		case MPEGGenreIDBallad:
			return  BF::MPEGGenre::Ballad;

		case MPEGGenreIDPoweerBallad:
			return  BF::MPEGGenre::PoweerBallad;

		case MPEGGenreIDRhytmicSoul:
			return  BF::MPEGGenre::RhytmicSoul;

		case MPEGGenreIDFreestyle:
			return  BF::MPEGGenre::Freestyle;

		case MPEGGenreIDDuet:
			return  BF::MPEGGenre::Duet;

		case MPEGGenreIDPunkRock:
			return  BF::MPEGGenre::PunkRock;

		case MPEGGenreIDDrumSolo:
			return  BF::MPEGGenre::DrumSolo;

		case MPEGGenreIDACapela:
			return  BF::MPEGGenre::ACapela;

		case MPEGGenreIDEuroHouse:
			return  BF::MPEGGenre::EuroHouse;

		case MPEGGenreIDDanceHall:
			return MPEGGenre::DanceHall;

			default:
				return BF::MPEGGenre::Unknown;

	}
}

unsigned char BF::MPEGGenreConvert(MPEGGenre mpegGenre)
{
	switch (mpegGenre)
	{
		case BF::MPEGGenre::Blues:
			return MPEGGenreIDBlues;

		case BF::MPEGGenre::ClassicRock:
			return MPEGGenreIDClassicRock;

		case BF::MPEGGenre::Country:
			break;
		case BF::MPEGGenre::Dance:
			break;
		case BF::MPEGGenre::Disco:
			break;
		case BF::MPEGGenre::Funk:
			break;
		case BF::MPEGGenre::Grunge:
			break;
		case BF::MPEGGenre::HipHop:
			break;
		case BF::MPEGGenre::Jazz:
			break;
		case BF::MPEGGenre::Metal:
			break;
		case BF::MPEGGenre::NewAge:
			break;
		case BF::MPEGGenre::Oldies:
			break;
		case BF::MPEGGenre::Other:
			break;
		case BF::MPEGGenre::Pop:
			break;
		case BF::MPEGGenre::RAndB:
			break;
		case BF::MPEGGenre::Rap:
			break;
		case BF::MPEGGenre::Reggae:
			break;
		case BF::MPEGGenre::Rock:
			break;
		case BF::MPEGGenre::Techno:
			break;
		case BF::MPEGGenre::Industrial:
			break;
		case BF::MPEGGenre::Alternative:
			break;
		case BF::MPEGGenre::Ska:
			break;
		case BF::MPEGGenre::DeathMetal:
			break;
		case BF::MPEGGenre::Pranks:
			break;
		case BF::MPEGGenre::Soundtrack:
			break;
		case BF::MPEGGenre::EuroTechno:
			break;
		case BF::MPEGGenre::Ambient:
			break;
		case BF::MPEGGenre::TripHop:
			break;
		case BF::MPEGGenre::Vocal:
			break;
		case BF::MPEGGenre::JazzFunk:
			break;
		case BF::MPEGGenre::Fusion:
			break;
		case BF::MPEGGenre::Trance´:
			break;
		case BF::MPEGGenre::Classical:
			break;
		case BF::MPEGGenre::Instrumental:
			break;
		case BF::MPEGGenre::Acid:
			break;
		case BF::MPEGGenre::House:
			break;
		case BF::MPEGGenre::Game:
			break;
		case BF::MPEGGenre::SoundClip:
			break;
		case BF::MPEGGenre::Gospel:
			break;
		case BF::MPEGGenre::Noise:
			break;
		case BF::MPEGGenre::AlternRock:
			break;
		case BF::MPEGGenre::Bass:
			break;
		case BF::MPEGGenre::Soul:
			break;
		case BF::MPEGGenre::Punk:
			break;
		case BF::MPEGGenre::Space:
			break;
		case BF::MPEGGenre::Meditative:
			break;
		case BF::MPEGGenre::InstrumentalPop:
			break;
		case BF::MPEGGenre::InstrumentalRock:
			break;
		case BF::MPEGGenre::Ethnic:
			break;
		case BF::MPEGGenre::Gothic:
			break;
		case BF::MPEGGenre::Darkwave:
			break;
		case BF::MPEGGenre::TechnoIndustrial:
			break;
		case BF::MPEGGenre::Electronic:
			break;
		case BF::MPEGGenre::PopFolk:
			break;
		case BF::MPEGGenre::Eurodance:
			break;
		case BF::MPEGGenre::Dream:
			break;
		case BF::MPEGGenre::SouthernRock:
			break;
		case BF::MPEGGenre::Comedy:
			break;
		case BF::MPEGGenre::Cult:
			break;
		case BF::MPEGGenre::Gangsta:
			break;
		case BF::MPEGGenre::Top40:
			break;
		case BF::MPEGGenre::ChristianRap:
			break;
		case BF::MPEGGenre::PopFunk:
			break;
		case BF::MPEGGenre::Jungle:
			break;
		case BF::MPEGGenre::NativeAmerican:
			break;
		case BF::MPEGGenre::Cabaret:
			break;
		case BF::MPEGGenre::NewWave:
			break;
		case BF::MPEGGenre::Psychadelic:
			break;
		case BF::MPEGGenre::Rave:
			break;
		case BF::MPEGGenre::Showtunes:
			break;
		case BF::MPEGGenre::Trailer:
			break;
		case BF::MPEGGenre::LoFi:
			break;
		case BF::MPEGGenre::Tribal:
			break;
		case BF::MPEGGenre::AcidPunk:
			break;
		case BF::MPEGGenre::AcidJazz:
			break;
		case BF::MPEGGenre::Polka:
			break;
		case BF::MPEGGenre::Retro:
			break;
		case BF::MPEGGenre::Musical:
			break;
		case BF::MPEGGenre::RockAndRoll:
			break;
		case BF::MPEGGenre::HardRock:
			break;
		case BF::MPEGGenre::Folk:
			break;
		case BF::MPEGGenre::FolkRock:
			break;
		case BF::MPEGGenre::NationalFolk:
			break;
		case BF::MPEGGenre::Swing:
			break;
		case BF::MPEGGenre::FastFusion:
			break;
		case BF::MPEGGenre::Bebob:
			break;
		case BF::MPEGGenre::Latin:
			break;
		case BF::MPEGGenre::Revival:
			break;
		case BF::MPEGGenre::Celtic:
			break;
		case BF::MPEGGenre::Bluegrass:
			break;
		case BF::MPEGGenre::Avantgarde:
			break;
		case BF::MPEGGenre::GothicRock:
			break;
		case BF::MPEGGenre::ProgressiveRock:
			break;
		case BF::MPEGGenre::PsychedelicRock:
			break;
		case BF::MPEGGenre::SymphonicRock:
			break;
		case BF::MPEGGenre::SlowRock:
			break;
		case BF::MPEGGenre::BigBand:
			break;
		case BF::MPEGGenre::Chorus:
			break;
		case BF::MPEGGenre::EasyListening:
			break;
		case BF::MPEGGenre::Acoustic:
			break;
		case BF::MPEGGenre::Humour:
			break;
		case BF::MPEGGenre::Speech:
			break;
		case BF::MPEGGenre::Chanson:
			break;
		case BF::MPEGGenre::Opera:
			break;
		case BF::MPEGGenre::ChamberMusic:
			break;
		case BF::MPEGGenre::Sonata:
			break;
		case BF::MPEGGenre::Symphony:
			break;
		case BF::MPEGGenre::BootyBrass:
			break;
		case BF::MPEGGenre::Primus:
			break;
		case BF::MPEGGenre::PornGroove:
			break;
		case BF::MPEGGenre::Satire:
			break;
		case BF::MPEGGenre::SlowJam:
			break;
		case BF::MPEGGenre::Club:
			break;
		case BF::MPEGGenre::Tango:
			break;
		case BF::MPEGGenre::Samba:
			break;
		case BF::MPEGGenre::Folklore:
			break;
		case BF::MPEGGenre::Ballad:
			break;
		case BF::MPEGGenre::PoweerBallad:
			break;
		case BF::MPEGGenre::RhytmicSoul:
			break;
		case BF::MPEGGenre::Freestyle:
			break;
		case BF::MPEGGenre::Duet:
			break;
		case BF::MPEGGenre::PunkRock:
			break;
		case BF::MPEGGenre::DrumSolo:
			break;
		case BF::MPEGGenre::ACapela:
			break;
		case BF::MPEGGenre::EuroHouse:
			break;
		case BF::MPEGGenre::DanceHall:
			return -1;

		case BF::MPEGGenre::Unknown:
		default:
			return -1;
	}

	return -1;
}
