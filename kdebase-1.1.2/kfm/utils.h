/**
 * This file contains varoius C functions for
 * almost every purpose.
 */

#ifndef _utils_h
#define _utils_h

#include <qstring.h>
#include <qstrlist.h>

#include <kurl.h>

#include "kbind.h"

/**
 * Opens the documents in '_urlList' using '_cmd' as command.
 * The files in '_urlList' are URLs or filenames. The filenames
 * are NOT shell quoted, but '_cmd' has to be shell quoted.
 *
 * This command is only useful for old applications which dont
 * understand URLs themselves. If there are URLs, then kfmexec
 * is used to handle the network stuff for this old application.
 * If all files are local, then everything is as usual.
 *
 * The filenames are just appended to '_cmd' if '_cmd' does not
 * contain "%f" somewhere.
 */
void openWithOldApplication( const char *_cmd, QStrList& _urlList, const char *_workdir=0L );

QString displayName();

/**
 * @return -1 on error, 0 if the URLs are nor nested neither equal
 *         1 if '_src' is a child of '_dest' and 2 if '_src' and '_dest'
 *         are equal.
 */
int testNestedURLs( const char *_src, const char *_dest );

/**
 * @param str A string to squeeze if necessary
 * @param maxlen The maximum length of the string returned
 * @return A string containing str if its length is < maxlen, and
 * containing '...' in the middle of it if its length was > maxlen.
 */
QString stringSqueeze( const char *str, unsigned int maxlen );

void encodeFileName( QString& fn );
void decodeFileName( QString& fn );

#endif
