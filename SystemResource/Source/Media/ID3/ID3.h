#pragma once

#include <cstddef>

#define ID3TitleSize 30
#define ID3ArtistSize 30
#define ID3AlbumSize 30
#define ID3YearSize 4
#define ID3CommentSize 30

namespace BF
{
	struct ID3
	{
		// Version 1.0
		wchar_t Title[ID3TitleSize +1];
		wchar_t Artist[ID3ArtistSize+1];
		wchar_t Album[ID3AlbumSize+1];
		wchar_t Year[ID3YearSize+1];
		wchar_t Comment[ID3CommentSize+1];
		unsigned char Genre;

		// Version 1.1
		unsigned char TrackID;

		// Version 2.x
		unsigned int BeatsPerMinute;
		wchar_t Composer[ID3ArtistSize + 1];

		ID3();

		size_t Parse(const unsigned char* data, const size_t dataSize);
	};
}
