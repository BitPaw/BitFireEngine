#pragma once

struct ZLibStream;

struct StateData
{
	public:
	ZLibStream* strm;             /* pointer back to this zlib stream */
	int wrap;                   /* bit 0 true for zlib, bit 1 true for gzip,
								  bit 2 true to validate check value  bit 1 true for gzip */

    unsigned char* window;
    /* Sliding window. Input bytes are read into the second half of the window,
     * and move to the first half later to keep a dictionary of at least wSize
     * bytes. With this organization, matches are limited to a distance of
     * wSize-MAX_MATCH bytes, but this ensures that IO is always
     * performed with a length multiple of the block size. Also, it limits
     * the window size to 64K, which is quite useful on MSDOS.
     * To do: use the user input buffer as sliding window.
     */
};

