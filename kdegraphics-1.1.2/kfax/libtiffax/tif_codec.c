/* $Header: /home/kde/kdegraphics/kfax/libtiffax/tif_codec.c,v 1.2 1997/10/06 03:22:21 wuebben Exp $ */

/*
 * Copyright (c) 1988-1995 Sam Leffler
 * Copyright (c) 1991-1995 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

/*
 * TIFF Library
 *
 * Builtin Compression Scheme Configuration Support.
 */
#include "tiffiop.h"

static	int NotConfigured(TIFF*, int);

#ifndef	LZW_SUPPORT
#define	TIFFInitLZW		NotConfigured
#endif
#ifndef	PACKBITS_SUPPORT
#define	TIFFInitPackbits	NotConfigured
#endif
#ifndef	THUNDER_SUPPORT
#define	TIFFInitThunderScan	NotConfigured
#endif
#ifndef	NEXT_SUPPORT
#define	TIFFInitNeXT		NotConfigured
#endif
#ifndef	JPEG_SUPPORT
#define	TIFFInitJPEG		NotConfigured
#endif
#ifndef	OJPEG_SUPPORT
#define	TIFFInitOJPEG		NotConfigured
#endif
#ifndef	CCITT_SUPPORT
#define	TIFFInitCCITTRLE	NotConfigured
#define	TIFFInitCCITTRLEW	NotConfigured
#define	TIFFInitCCITTFax3	NotConfigured
#define	TIFFInitCCITTFax4	NotConfigured
#endif
#ifndef JBIG_SUPPORT
#define	TIFFInitJBIG		NotConfigured
#endif
#ifndef	ZIP_SUPPORT
#define	TIFFInitZIP		NotConfigured
#endif

/*
 * Compression schemes statically built into the library.
 */
#ifdef VMS
const TIFFCodec _TIFFBuiltinCODECS[] = {
#else
TIFFCodec _TIFFBuiltinCODECS[] = {
#endif
    { "Null",		COMPRESSION_NONE,	TIFFInitDumpMode },
    { "LZW",		COMPRESSION_LZW,	TIFFInitLZW },
    { "PackBits",	COMPRESSION_PACKBITS,	TIFFInitPackBits },
    { "ThunderScan",	COMPRESSION_THUNDERSCAN,TIFFInitThunderScan },
    { "NeXT",		COMPRESSION_NEXT,	TIFFInitNeXT },
    { "JPEG",		COMPRESSION_JPEG,	TIFFInitJPEG },
    { "Old-style JPEG",	COMPRESSION_OJPEG,	TIFFInitOJPEG },
    { "CCITT RLE",	COMPRESSION_CCITTRLE,	TIFFInitCCITTRLE },
    { "CCITT RLE/W",	COMPRESSION_CCITTRLEW,	TIFFInitCCITTRLEW },
    { "CCITT Group3",	COMPRESSION_CCITTFAX3,	TIFFInitCCITTFax3 },
    { "CCITT Group4",	COMPRESSION_CCITTFAX4,	TIFFInitCCITTFax4 },
    { "ISO JBIG",	COMPRESSION_JBIG,	TIFFInitJBIG },
    { "Deflate",	COMPRESSION_DEFLATE,	TIFFInitZIP },
    { NULL },
};

static int
NotConfigured(TIFF* tif, int scheme)
{
	const TIFFCodec* c = TIFFFindCODEC(scheme);
	
	TIFFError(tif->tif_name,
	    "%s compression support is not configured", c->name);
	return (0);
}
