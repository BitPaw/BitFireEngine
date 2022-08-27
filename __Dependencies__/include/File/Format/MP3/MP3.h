#ifndef MP3Include
#define MP3Include

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Format/ID3/ID3.h>

#define MP3Debug 1

#ifdef __cplusplus
extern "C"
{
#endif
	typedef enum MPEGGenre_
	{
		MPEGGenreUnknown,

		Blues,
		ClassicRock,
		Country,
		Dance,
		Disco,
		Funk,
		Grunge,
		HipHop,
		Jazz,
		Metal,
		NewAge,
		Oldies,
		Other,
		Pop,
		RAndB,
		Rap,
		Reggae,
		Rock,
		Techno,
		Industrial,
		Alternative,
		Ska,
		DeathMetal,
		Pranks,
		Soundtrack,
		EuroTechno,
		Ambient,
		TripHop,
		Vocal,
		JazzFunk,
		Fusion,
		Trance,
		Classical,
		Instrumental,
		Acid,
		House,
		Game,
		SoundClip,
		Gospel,
		Noise,
		AlternRock,
		Bass,
		Soul,
		Punk,
		Space,
		Meditative,
		InstrumentalPop,
		InstrumentalRock,
		Ethnic,
		Gothic,
		Darkwave,
		TechnoIndustrial,
		Electronic,
		PopFolk,
		Eurodance,
		Dream,
		SouthernRock,
		Comedy,
		Cult,
		Gangsta,
		Top40,
		ChristianRap,
		PopFunk,
		Jungle,
		NativeAmerican,
		Cabaret,
		NewWave,
		Psychadelic,
		Rave,
		Showtunes,
		Trailer,
		LoFi,
		Tribal,
		AcidPunk,
		AcidJazz,
		Polka,
		Retro,
		Musical,
		RockAndRoll,
		HardRock,
		Folk,
		FolkRock,
		NationalFolk,
		Swing,
		FastFusion,
		Bebob,
		Latin,
		Revival,
		Celtic,
		Bluegrass,
		Avantgarde,
		GothicRock,
		ProgressiveRock,
		PsychedelicRock,
		SymphonicRock,
		SlowRock,
		BigBand,
		Chorus,
		EasyListening,
		Acoustic,
		Humour,
		Speech,
		Chanson,
		Opera,
		ChamberMusic,
		Sonata,
		Symphony,
		BootyBrass,
		Primus,
		PornGroove,
		Satire,
		SlowJam,
		Club,
		Tango,
		Samba,
		Folklore,
		Ballad,
		PoweerBallad,
		RhytmicSoul,
		Freestyle,
		Duet,
		PunkRock,
		DrumSolo,
		ACapela,
		EuroHouse,
		DanceHall
	}
	MPEGGenre;

	typedef struct MPEGAudioTag
	{
		// char[3] == TAG
		char Title[30];
		char Artist[30];
		char Album[30];
		char Year[4];
		char Comment[30];
		MPEGGenre Genre;
	};

	typedef enum MP3ChannelMode_
	{
		MP3ChannelStereo,
		MP3ChannelJointStereo,
		MP3ChannelDual,
		MP3ChannelSingle
	}
	MP3ChannelMode;


	typedef enum MP3Emphasis_
	{
		MP3EmphasisReserved,
		MP3EmphasisNone,
		MP3Emphasisms5015,
		MP3EmphasisCCITJ17,
	}
	MP3Emphasis;


	typedef enum MP3Layer_
	{
		MP3LayerReserved,
		MP3LayerI,
		MP3LayerII,
		MP3LayerIII
	}
	MP3Layer;

	typedef enum MP3MPEGVersion_
	{
		MPEGVersionReserved,
		MPEGVersion1,
		MPEGVersion2,
		MPEGVersion25
	}MP3MPEGVersion;

	typedef struct MP3Header_
	{
		MP3MPEGVersion MPEGVersion;
		MP3Layer Layer;
		unsigned char CRCErrorProtection;

		unsigned int BitRate;
		unsigned short SampleRate;
		unsigned char UsePadding;
		unsigned char IsPrivate; // Unused
		MP3ChannelMode ChannelMode;
		unsigned char AudioModeIntensity;
		unsigned char AudioModeMS;

		unsigned char Copyrighted;
		unsigned char CopyOfOriginal;
		MP3Emphasis Emphasis;

		unsigned int FrameLength;
	}
	MP3Header;

	typedef struct MP3_
	{
		ID3 ID3Info;
		MP3Header Header;
	}
	MP3;

	
	static MPEGGenre ConvertMPEGToGenre(const unsigned char mpegGenre);
	static unsigned char ConvertMPEGFromGenre(const MPEGGenre mpegGenre);
	static ActionResult MP3HeaderParse(MP3Header* mp3Header, const unsigned char* data, const size_t dataSize, size_t* dataRead);

	extern ActionResult MP3Parse(MP3* mp3, const void* data, const size_t dataSize, size_t* dataRead);


#ifdef __cplusplus
}
#endif

#endif