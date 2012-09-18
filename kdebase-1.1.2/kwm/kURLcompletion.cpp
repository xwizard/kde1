/* 
 * KURLCompletion
 * Completion of URL's (currently just files), to
 * be connected to KLined() which emits signals for completion (Tab/Ctrl-S)
 * and rotation (Ctrl-D)
 *
 * 10/1997 Henner Zeller <zeller@think.de>
 * This code is based on Torben Weis' KFileEntry
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "kURLcompletion.moc"
#include <qapp.h>
#include <qkeycode.h>

#include <string.h>
#include <sys/types.h>
#include <dirent.h>      
#include <unistd.h>
#include <sys/stat.h>

KURLCompletion::KURLCompletion( const char *dir) 
{
	directory = dir;
	possibilityList.clear();
	new_guess = true;
	self_update = false;
	the_text = "";
}

KURLCompletion::~KURLCompletion()
{ 
  /* nope */ 
}

/* public slot */
void KURLCompletion::edited (const char *text)
{
	the_text = text;
	if (!self_update)
		new_guess = true;
}

/* public slot */
void KURLCompletion::make_completion ()
{
	QString dir = the_text, match;
	bool ambigous;

	dir.detach();
	if (!is_fileurl (dir, ambigous))
		return;
	
	if (completed_dir || new_guess)
		GetList(dir, match);
	else 
		match = dir;
	
	if (possibilityList.count() != 1)
		QApplication::beep();
	else
		completed_dir = CompleteDir (match);
	
	new_guess = false;

	// url was ambigous and we actually did not find any
	// matching file -> leave it at it is
	if (!ambigous || !possibilityList.isEmpty()) {
		match.prepend ("file:"); // set to file-protocol
		self_update = true;
		emit setText (match);
		self_update = false;
	}
}

/* public slot */
void KURLCompletion::make_rotation ()
{
	QString dir = the_text, match, guess;
	bool ambigous;
	const char * item = 0L;

	dir.detach();
	if (!is_fileurl (dir, ambigous))
		return;
	
	if (new_guess) {
		GetList(dir, match);
		possibilityList.last(); // next entry will be the first ..
	}
	
	if (!possibilityList.isEmpty()) {
		if ((item = possibilityList.next()) == 0L)
			item = possibilityList.first();
		match = item;
		match.prepend (qual_dir);
	} 
	else {
		match = dir;
		QApplication::beep();
	}
	
	completed_dir = CompleteDir (match);
	new_guess = false;
	if (!ambigous || !possibilityList.isEmpty()) {
		match.prepend ("file:");  // set to file-protocol
		self_update = true;
		emit setText (match);
		self_update = false;
	}
}

void KURLCompletion::GetList (QString dir, QString & match)
{
	DIR *dp;
	struct dirent *ep;
	QString guess;
	
	qual_dir = dir;
	int pos = dir.findRev ("/");
	qual_dir = dir.left (pos);
	if (qual_dir == "")
		qual_dir = "/";
	guess = dir.right (dir.length() - pos - 1);
	
	dp = opendir( qual_dir.data() );
	if ( dp == NULL )
	{
		QApplication::beep();
		match = dir;
		return;
	}

	int len = guess.length();
	bool multiple = false;
	bool anymatch = false;
	QString max;
	possibilityList.clear();
	
	// Loop thru all directory entries
	while ( ( ep = readdir( dp ) ) != 0L ) {
		if (strcmp (ep->d_name, ".") == 0 || 
		    strcmp (ep->d_name, "..") == 0)
			continue;
		
		if ( strncmp( ep->d_name, guess.data(), len ) == 0L ) {
			possibilityList.inSort( ep->d_name );
			
			// More than one possibility ?
			if ( anymatch )
			{
				// Find maximum overlapping
				int i = 0;
				while ( max.data() [i] != 0 && 
					ep->d_name [i] != 0 && 
					max.data() [i] == ep->d_name[i] ) 
					i++;
				max = (i > 0) ? max.left(i).data() : "";
				if (!multiple) {
					QApplication::beep();
					multiple = true;
				}
			}
			else
				max = ep->d_name;
			anymatch = true;
		}
	}
	
	(void) closedir( dp );

	if (qual_dir.right(1) != "/")
		qual_dir += "/";

	if (anymatch)
		match = qual_dir + max;
	else
		match = qual_dir + guess; // leave it as it is
}
	
bool KURLCompletion::is_fileurl (QString &url, bool &ambigous_beginning) const
{
	bool starts_with_file = (url.left(5) == "file:");
	
	if ( !starts_with_file && // no fileprotocol .. but
	     url.find( ":/" ) != -1) // .. actually another protocol specified
		return false;

	// ambigous if there is no file: or / at the beginning
	// (consider 'home' -> okey but 'http' -> file or protocol?)
	ambigous_beginning = (!starts_with_file && 
			      (url.left(1) != "/"));

        if ( starts_with_file )
		url = url.data() + 5;
	
	// Get the currently entered full qualified path
	if ( url.data()[ 0 ] != '/' )
	{
		QString dir = directory.data();
		if ( dir.right(1) != "/" )
			dir += "/";
		url.prepend (dir);
	}
	return true;
}


bool KURLCompletion::CompleteDir (QString &dir)
{
	struct stat sbuff;
	if (stat ( dir.data(), &sbuff) == 0 &&
	    S_ISDIR (sbuff.st_mode)) {
		dir += "/";
		return true;
	}
	return false;
}
