
//
// KDE Display background setup module
//
// Copyright (c)  Martin R. Jones 1996
//
// Converted to a kcc module by Matthias Hoelzer 1997
//

#ifdef HAVE_CONFIG
#include <config.h>
#endif

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <qimage.h>
#include <qgrpbox.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qfiledlg.h>
#include <qradiobt.h>
#include <qchkbox.h>
#include <qpainter.h>
#include <qlayout.h>
#include <qmsgbox.h>

#include <kapp.h>
#include <kwm.h>
#include <kiconloader.h>
#include <ksimpleconfig.h>
#include <kbuttonbox.h>

#include <X11/Xlib.h>

#include "kaccel.h"


#include "global.h"
#include "global.moc"


//----------------------------------------------------------------------------

KGlobalConfig::KGlobalConfig( QWidget *parent, const char *name )
	: KConfigWidget( parent, name )
{

	globalDict = new QDict<int> ( 37, false );
	globalDict->setAutoDelete( true );
	
	dict.setAutoDelete( false );
	keys = new KAccel( this );
	
	keys->insertItem(i18n("Switch to next window"), "ALT+Tab");
	keys->insertItem(i18n("Switch to previous window"), "SHIFT+ALT+Tab");
	keys->insertItem(i18n("Switch to next desktop"), "CTRL+Tab");
	keys->insertItem(i18n("Switch to previous desktop"), "SHIFT+CTRL+Tab");
	keys->insertItem(i18n("Task manager"), "CTRL+Escape");
	keys->insertItem(i18n("Toggle kill mode"), "CTRL+ALT+Escape");
	keys->insertItem(i18n("Execute command"), "ALT+F2");
	keys->insertItem(i18n("Pop-up window operations menu"), "ALT+F3");
	keys->insertItem(i18n("Close window"), "ALT+F4");
	keys->insertItem(i18n("Iconify window"), "");
	keys->insertItem(i18n("Resize window"), "");
	keys->insertItem(i18n("Move window"), "");
	keys->insertItem(i18n("Make window sticky"), "");
	keys->insertItem(i18n("Pop-up system menu"), "ALT+F1");
	
	keys->insertItem(i18n("Switch to first desktop"), "CTRL+F1");
	keys->insertItem(i18n("Switch to second desktop"), "CTRL+F2");
	keys->insertItem(i18n("Switch to third desktop"), "CTRL+F3");
	keys->insertItem(i18n("Switch to fourth desktop"), "CTRL+F4");
	keys->insertItem(i18n("Switch to fifth desktop"), "CTRL+F5");
	keys->insertItem(i18n("Switch to sixth desktop"), "CTRL+F6");
	keys->insertItem(i18n("Switch to seventh desktop"), "CTRL+F7");
	keys->insertItem(i18n("Switch to eighth desktop"), "CTRL+F8");
	
	debug("inserted keys");
	
	keys->setConfigGlobal( true );
	keys->setConfigGroup( "Global Keys" );
	keys->readSettings();
	
	debug("read settings");
	
	QBoxLayout *topLayout = new QVBoxLayout( this, 10 );
	
	QBoxLayout *pushLayout = new QHBoxLayout( 5 );
	
	topLayout->addLayout( pushLayout );
	
	QBoxLayout *stackLayout = new QVBoxLayout( 4 );
	
	pushLayout->addLayout( stackLayout, 20 );
	
	sFileList = new QStrList(); 
	sList = new QListBox( this );
	
	sList->clear();
	sFileList->clear();
	sList->insertItem( i18n("Current scheme"), 0 );
	sFileList->append( "Not a  kcsrc file" );
	sList->insertItem( i18n("KDE default"), 1 );
	sFileList->append( "Not a kcsrc file" );
	readSchemeNames();
	sList->setCurrentItem( 0 );
	connect( sList, SIGNAL( highlighted( int ) ),
			SLOT( slotPreviewScheme( int ) ) );
	
	QLabel *label = new QLabel( sList, "&Key scheme", this );
	label->adjustSize();
	label->setFixedHeight( label->height() );
	
	stackLayout->addWidget( label );
	stackLayout->addWidget( sList );
	
	stackLayout = new QVBoxLayout( 5 );
	
	pushLayout->addLayout( stackLayout, 10 );
	
	addBt = new QPushButton(  i18n("&Add ..."), this );
	addBt->adjustSize();
	addBt->setFixedHeight( addBt->height() );
	addBt->setMinimumWidth( addBt->width() );
	connect( addBt, SIGNAL( clicked() ), SLOT( slotAdd() ) );
	
	QBoxLayout *push2Layout = new QHBoxLayout( 5 );
	
	stackLayout->addStretch( 10 );
	stackLayout->addLayout( push2Layout );
	
	push2Layout->addWidget( addBt, 10 );
	
	removeBt = new QPushButton(  i18n("&Remove"), this );
	removeBt->adjustSize();
	removeBt->setFixedHeight( removeBt->height() );
	removeBt->setMinimumWidth( removeBt->width() );
	removeBt->setEnabled(FALSE);
	connect( removeBt, SIGNAL( clicked() ), SLOT( slotRemove() ) );
	
	push2Layout->addWidget( removeBt, 10 );
	
	saveBt = new QPushButton(  i18n("&Save changes"), this );
	saveBt->adjustSize();
	saveBt->setFixedHeight( saveBt->height() );
	saveBt->setMinimumWidth( saveBt->width());
	saveBt->setEnabled(FALSE);
	connect( saveBt, SIGNAL( clicked() ), SLOT( slotSave() ) );
	
	stackLayout->addWidget( saveBt );
	
	sList->setMinimumHeight( 2*saveBt->height() + 10 );
	
	QFrame* tmpQFrame;
	tmpQFrame = new QFrame( this );
	tmpQFrame->setFrameStyle( QFrame::HLine | QFrame::Sunken );
	tmpQFrame->setMinimumHeight( tmpQFrame->sizeHint().height() );
	
	topLayout->addWidget( tmpQFrame );
	
	dict = keys->keyDict();
	
	debug("got key dict");
	
	kc =  new KKeyChooser( &dict, this );
	connect( kc, SIGNAL( keyChange() ), this, SLOT( slotChanged() ) );
	
	debug("Make key chooser");
	
	readScheme();
	
	topLayout->addWidget( kc, 10 );
	
	topLayout->activate();
	
	//keys->setKeyDict( dave );
}

void KGlobalConfig::slotRemove()
{
	QString kksPath = getenv( "HOME" );
	kksPath += "/.kde/share/apps/kcmkeys/global";
	
	QDir d( kksPath );
	if (!d.exists()) // what can we do?
	  return;

	d.setFilter( QDir::Files );
	d.setSorting( QDir::Name );
	d.setNameFilter("*.kksrc");
	
	uint ind = sList->currentItem();
	
	if ( !d.remove( sFileList->at( ind ) ) ) {
		QMessageBox::critical( 0, i18n("Error removing scheme"),
		      i18n("This key scheme could not be removed.\n"
			   "Perhaps you do not have permission to alter the file\n"
			   "system where the key scheme is stored." ) );
		return;
	}
	
	sList->removeItem( ind );
	sFileList->remove( ind );
}

void KGlobalConfig::slotChanged( )
{
	if ( removeBt->isEnabled() )
		saveBt->setEnabled( TRUE );
	else
		saveBt->setEnabled( FALSE );
}

void KGlobalConfig::slotSave( )
{
	KSimpleConfig *config = 
			new KSimpleConfig( sFileList->at( sList->currentItem() ) );
				
	config->setGroup( "Global Key Scheme" );
	
	kc->aIt->toFirst();
	while ( kc->aIt->current() ) {
		config->writeEntry( kc->aIt->currentKey(), 
			keyToString( kc->aIt->current()->aCurrentKeyCode ) );
		++ ( *kc->aIt );
	}
	
	config->sync();
	
	saveBt->setEnabled( FALSE );
}

void KGlobalConfig::resizeEvent( QResizeEvent * )
{
 
}

void KGlobalConfig::readSettings( )
{
  
}

void KGlobalConfig::readScheme( int index )
{
	KConfigBase* config;
	
	if( index == 1 ) {
		kc->allDefault();
		return;
	} if ( index == 0 ) {
		config  = kapp->getConfig();
	} else {
		config = 
			new KSimpleConfig( sFileList->at( index ), true );
	}
	
	KEntryIterator *gIt;
	
	if ( index == 0 )
		gIt = config->entryIterator( "Global Keys" );
	else
		gIt = config->entryIterator( "Global Key Scheme" );
		
	int *keyCode;
	
	gIt->toFirst();
	while ( gIt->current() ) {
		keyCode = new int;
		*keyCode = stringToKey( gIt->current()->aValue );
		globalDict->insert( gIt->currentKey(), keyCode);
		//debug( " %s, %d", gIt->currentKey(), *keyCode );
		++(*gIt);
	}
	
	kc->aIt->toFirst();
	while ( kc->aIt->current() ) {
		if ( globalDict->find( kc->aIt->currentKey() ) ) {
			kc->aIt->current()->aConfigKeyCode = *globalDict->find( kc->aIt->currentKey() );
			kc->aIt->current()->aCurrentKeyCode = kc->aIt->current()->aConfigKeyCode;
			debug("Change: %s", kc->aIt->currentKey() );
		}
		++ ( *kc->aIt );
	}
	
	kc->listSync();
}

void KGlobalConfig::slotAdd()
{
	SaveScm *ss = new SaveScm( 0,  "save scheme" );
	
	bool nameValid;
	QString sName;
	QString sFile; 
	
	do {
	
	nameValid = TRUE;
	
	if ( ss->exec() ) {
		sName = ss->nameLine->text();
		if ( sName.stripWhiteSpace().isEmpty() )
			return;
			
		sName = sName.simplifyWhiteSpace();
		sFile.sprintf(sName);
		
		int ind = 0;
		while ( ind < (int) sFile.length() ) {
			
			// parse the string for first white space
			
			ind = sFile.find(" ");
			if (ind == -1) {
				ind = sFile.length();
				break;
			}
		
			// remove from string
		
			sFile.remove( ind, 1);
			
			// Make the next letter upper case 
			
			QString s = sFile.mid( ind, 1 );
			s = s.upper();
			sFile.replace( ind, 1, s.data() );
			
		}
		
		for ( int i = 0; i < (int) sList->count(); i++ ) {
			if ( sName == sList->text( i ) ) {
				nameValid = FALSE;
				QMessageBox::critical( 0, i18n( "Naming conflict" ),
					i18n( "Please choose a unique name for the new key\n"\
							"scheme. The one you entered already appears\n"\
							"in the key scheme list." ) );
			}
		}
	} else return;
	
	} while ( nameValid == FALSE );
	
	disconnect( sList, SIGNAL( highlighted( int ) ), this,
			SLOT( slotPreviewScheme( int ) ) );
	
	sList->insertItem( sName.data() );
	sList->setFocus();
	sList->setCurrentItem( sList->count()-1 );
	
	QString kksPath( getenv( "HOME" ) );
	
	kksPath += "/.kde/share/apps/kcmkeys/";
	
	QDir d( kksPath.data() );
	if ( !d.exists() )
		if ( !d.mkdir( kksPath.data() ) ) {
			warning("KGlobalConfig: Could not make directory to store user info.");
			return;
		}
	
	kksPath += "global/";
	
	d.setPath( kksPath.data() );
	if ( !d.exists() )
		if ( !d.mkdir( kksPath.data() ) ) {
			warning("KGlobalConfig: Could not make directory to store user info.");
			return;
		}
	
	sFile.prepend( kksPath );
	sFile += ".kksrc";
	sFileList->append( sFile.data() );
	
	KSimpleConfig *config = 
			new KSimpleConfig( sFile.data() );
			
	config->setGroup( "Global Key Scheme" );
	config->writeEntry( "SchemeName", sName );
	delete config;
	
	slotSave();
	
	connect( sList, SIGNAL( highlighted( int ) ), this,
			SLOT( slotPreviewScheme( int ) ) );
			
	slotPreviewScheme( sList->currentItem() );
}

void KGlobalConfig::slotPreviewScheme( int indx )
{
	readScheme( indx );
	
	// Set various appropriate for the scheme
	
	if ( indx < nSysSchemes ) {
		removeBt->setEnabled( FALSE );
		saveBt->setEnabled( FALSE );
	} else
		removeBt->setEnabled( TRUE );
	changed = TRUE;
}

void KGlobalConfig::readSchemeNames( )
{
	QString kksPath( kapp->kde_datadir() );
	kksPath += "/kcmkeys/global";
	
	QDir d;
	d.setPath( kksPath );
	
	if( d.exists() ) {
		d.setFilter( QDir::Files );
		d.setSorting( QDir::Name );
		d.setNameFilter("*.kksrc");

		if ( const QFileInfoList *sysList = d.entryInfoList() ) {
			QFileInfoListIterator sysIt( *sysList );
			QFileInfo *fi;

			// Always a current and a default scheme 
			nSysSchemes = 2;

			QString str;

			// This for system files
			while ( ( fi = sysIt.current() ) ) { 

				KSimpleConfig *config =
						new KSimpleConfig( fi->filePath(), true );
				config->setGroup( "Global Key Scheme" );
				str = config->readEntry( "SchemeName" );

				sList->insertItem( str.data() );
				sFileList->append( fi->filePath() );

				++sysIt;
				nSysSchemes++;

				delete config;
			}
		}
	}
	
	kksPath.sprintf( getenv( "HOME" ) );
	kksPath += "/.kde/share/apps/kcmkeys/global";
	
	d.setPath( kksPath );
	if( d.exists() ) {
		d.setFilter( QDir::Files );
		d.setSorting( QDir::Name );
		d.setNameFilter("*.kksrc");

		if ( const QFileInfoList *userList = d.entryInfoList() ) {
			QFileInfoListIterator userIt( *userList );
			QFileInfo *fi;
			QString str;

			// This for users files
			while ( ( fi = userIt.current() ) ) {

				KSimpleConfig config( fi->filePath(), true );
				config.setGroup( "Global Key Scheme" );
				str = config.readEntry( "SchemeName" );

				sList->insertItem( str.data() );
				sFileList->append( fi->filePath() );

				++userIt;
			}
		}
	}
		
}

void KGlobalConfig::writeSettings(  )
{
	debug("Writing key settings");
	keys->writeSettings();
}

void KGlobalConfig::getDeskNameList()
{
   
}

void KGlobalConfig::setDesktop( int desk )
{
   
}

void KGlobalConfig::showSettings()
{ 
   
}

void KGlobalConfig::slotApply()
{
	writeSettings();
}

void KGlobalConfig::apply( bool force )
{
	
}

void KGlobalConfig::retainResources() {
	
}

void KGlobalConfig::setMonitor()
{
   
    
}

// Attempts to load the specified wallpaper and creates a centred/scaled
// version if necessary.
// Note that centred pixmaps are placed on a full screen image of background
// color1, so if you want to save memory use a small tiled pixmap.
//
int KGlobalConfig::loadWallpaper( const char *name, bool useContext )
{
	
}

void KGlobalConfig::slotSelectColor1( const QColor &col )
{
	
}

void KGlobalConfig::slotSelectColor2( const QColor &col )
{

}

void KGlobalConfig::slotBrowse()
{
	
}

void KGlobalConfig::slotWallpaper( const char *filename )
{
   
}

void KGlobalConfig::slotWallpaperMode( int m )
{

}

void KGlobalConfig::slotColorMode( int m )
{
	
}

void KGlobalConfig::slotSetup2Color()
{
   
}

void KGlobalConfig::slotStyleMode( int m )
{
   
}

void KGlobalConfig::slotSwitchDesk( int num )
{
   
}

void KGlobalConfig::slotRenameDesk()
{
   
}

void KGlobalConfig::slotHelp()
{

}

void KGlobalConfig::loadSettings()
{
   
}

void KGlobalConfig::applySettings()
{
	debug("apply settings");
	debug("No. of items in dict %d", dict.count() );
	keys->setKeyDict( dict );
	debug("set key dict");
    writeSettings();
}
