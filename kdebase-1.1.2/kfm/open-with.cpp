#include <qfile.h>
#include <qdir.h>
#include <qdialog.h>
#include <qpixmap.h>

#include <kapp.h>
#include <ksimpleconfig.h>
#include <ktreelist.h>
#include <ktopwidget.h>
#include <kiconloader.h>

#include <string.h>
#include <stdio.h>

#include "open-with.moc"

#define SORT_SPEC (QDir::DirsFirst | QDir::Name | QDir::IgnoreCase)

// ----------------------------------------------------------------------

KAppTreeListItem::KAppTreeListItem( const char *name, QPixmap *pixmap, 
     bool d, bool parse, bool dir, QString p, QString c )
    : KTreeListItem( name, pixmap )
{
  dummy = d;
  parsed = parse;
  directory = dir;
  path = p;
  c.simplifyWhiteSpace();
  int pos;
  if( (pos = c.find( ' ')) > 0 )
    exec = c.left( pos );
  else
    exec = c;
  appname = name;
}

// ----------------------------------------------------------------------

KApplicationTree::KApplicationTree( QWidget *parent ) : QWidget( parent )
{
  tree = new KTreeList( this );
  tree->setSmoothScrolling( true );
  setFocusProxy( tree );
  
  QString personal = KApplication::localkdedir().copy();
  personal += "/share/applnk";
  QString global   = KApplication::kde_appsdir().copy();
  
  parseKdelnkDir( QDir(personal), tree );
  parseKdelnkDir( QDir(global), tree );
  
  tree->show();
  connect( tree, SIGNAL( expanded(int) ), SLOT( expanded(int) ) );
  connect( tree, SIGNAL( highlighted(int) ), SLOT( highlighted(int) ) );
  connect( tree, SIGNAL( selected(int) ), SLOT( selected(int) ) );
}

bool KApplicationTree::isKdelnkFile( const char* filename )
{
  FILE *f;
  f = fopen( filename, "rb" );
  if ( f == 0L )
    return false;

  char buff[ 100 ];
  buff[ 0 ] = 0;
  fgets( buff, 100, f );
  fclose( f );
	  
  if ( strncmp( buff, "# KDE Config File", 17 ) != 0L )
    return false;

  return true;
}

void KApplicationTree::parseKdelnkFile( QFileInfo *fi, KTreeList *tree, KAppTreeListItem *item )
{
  QPixmap pixmap;
  QString text_name, pixmap_name, mini_pixmap_name, big_pixmap_name, command_name, comment;

  QString file = fi->absFilePath();

  if( fi->isDir() ) 
  {
    text_name = fi->fileName();
    file += "/.directory";
  }
  else
  {
    int pos = fi->fileName().find( ".kdelnk" );
    if( pos >= 0 )
      text_name = fi->fileName().left( pos );
    else
      text_name = fi->fileName();
  }

  QFile config( file );

  if( config.exists() )
  {
    KSimpleConfig kconfig( file, true );
    kconfig.setGroup("KDE Desktop Entry");
    command_name      = kconfig.readEntry("Exec");
    mini_pixmap_name  = kconfig.readEntry("MiniIcon");
    big_pixmap_name   = kconfig.readEntry("Icon");
    comment           = kconfig.readEntry("Comment");
    text_name         = kconfig.readEntry("Name", text_name);

    if( !mini_pixmap_name.isEmpty() )
      pixmap = KApplication::getKApplication()->getIconLoader()->loadApplicationMiniIcon(mini_pixmap_name, 16, 16);
    if( pixmap.isNull() && !big_pixmap_name.isEmpty() )
      pixmap = KApplication::getKApplication()->getIconLoader()->loadApplicationMiniIcon(big_pixmap_name, 16, 16);
    if( pixmap.isNull() )
      pixmap = KApplication::getKApplication()->getIconLoader()->loadApplicationMiniIcon("mini-default.xpm", 16, 16);	
  }
  else
  {
     command_name = text_name;
     pixmap = KApplication::getKApplication()->getIconLoader()->loadApplicationMiniIcon("mini-default.xpm", 16, 16); 
  }

  it2 = new KAppTreeListItem( text_name.data(), &pixmap, false, false, fi->isDir(), fi->absFilePath(), command_name );	

    if( item == 0 )
      tree->insertItem( it2 );
    else
      item->appendChild( it2 );

  if( fi->isDir() )
  {
    dummy = new KAppTreeListItem( i18n("This group is empty!"), 0, true, false, false, "", "" );	
    it2->appendChild( dummy );
  }
}

short KApplicationTree::parseKdelnkDir( QDir d, KTreeList *tree, KAppTreeListItem *item)
{
  if( !d.exists() )
    return -1;

  d.setSorting( SORT_SPEC );
  QList <QString> item_list;
	
  const QFileInfoList *list = d.entryInfoList();
  QFileInfoListIterator it( *list );
  QFileInfo *fi;

  if( it.count() < 3 )
    return -1;

  while( ( fi = it.current() ) )
  {
    if( fi->fileName() == "." || fi->fileName() == ".." )
    {
      ++it;
      continue;
    }
    if( fi->isDir() )
    {
      parseKdelnkFile( fi, tree, item );
    }
    else 
    {
      if( !isKdelnkFile( fi->absFilePath() ) )
      {
	++it;
	continue;
      }
      parseKdelnkFile( fi, tree, item );
    } 
    ++it;
  }
  
  return 0;
}

void KApplicationTree::expanded(int index)
{
  KAppTreeListItem *item = (KAppTreeListItem *)tree->itemAt( index );

  if( !item->parsed && !(item->dummy ) )
  {
     parseKdelnkDir( QDir(item->path), tree, item );
     item->parsed = true;
     if( item->childCount() > 1 )
        item->removeChild( item->getChild() );
  }
}


void KApplicationTree::highlighted(int index)
{

  KAppTreeListItem *item = (KAppTreeListItem *)tree->itemAt( index );

  if( ( !item->directory ) && 
      !( item->exec.isEmpty() ) && 
      !( item->appname.isEmpty() ) )

    emit highlighted( item->appname.data(), item->exec.data() ); 

}


void KApplicationTree::selected(int index)
{
  KAppTreeListItem *item = (KAppTreeListItem *)tree->itemAt( index );

  if( ( !item->directory ) && !( item->exec.isEmpty() ) && !( item->appname.isEmpty() ) )
     emit selected( item->appname.data(), item->exec.data() ); 
  else
    tree->expandOrCollapseItem( index );
}

void KApplicationTree::resizeEvent( QResizeEvent * )
{
  tree->setGeometry( 0, 0, width(), height() );
}
