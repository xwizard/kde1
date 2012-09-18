//
// KDE Display color scheme setup module
//
// Copyright (c)  Mark Donohoe 1997
//
// Converted to a kcc module by Matthias Hoelzer 1997
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <qgrpbox.h>
#include <qbttngrp.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpushbt.h>
#include <qfiledlg.h>
#include <qslider.h>
#include <qradiobt.h>
#include <qmsgbox.h>
#include <qscrbar.h>
#include <qdrawutl.h>
#include <qchkbox.h>
#include <qcombo.h>
#include <kapp.h>
#include <kmsgbox.h>

#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "kcolordlg.h"

#include "kwmcom.h"
#include "colorscm.h"
#include "colorscm.moc"

#define SUPPLIED_SCHEMES 5
#define SCROLLBAR_SIZE 16

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


int dropError(Display *, XErrorEvent *)
{
  return 0;
}

WidgetCanvas::WidgetCanvas( QWidget *parent)
  : QWidget( parent  )
{
}

void WidgetCanvas::paintEvent(QPaintEvent *)
{
  bitBlt( this, 0,0, &smplw ); 
}

void WidgetCanvas::mousePressEvent( QMouseEvent *me )
{
  for ( int i = 0; i < MAX_HOTSPOTS; i++ )
    if ( hotspots[i].rect.contains( me->pos() ) )
    {
      emit widgetSelected( hotspots[i].number );
      return;
    }
}

void WidgetCanvas::paletteChange(const QPalette &)
{
  drawSampleWidgets();
}


void WidgetCanvas::drawSampleWidgets()
{
  int textLen;
  int highlightVal, lowlightVal;
	
  // Calculate the highlight and lowloght from contrast value and create
  // color group from color scheme.
	
  highlightVal=100+(2*contrast+4)*16/10;
  lowlightVal=100+(2*contrast+4)*10;
	
  QColorGroup cg( textColor, backgroundColor, 
		  backgroundColor.light(highlightVal),
		  backgroundColor.dark(lowlightVal), 
		  backgroundColor.dark(120),
		  textColor, windowColor );
	
  QColor col = QWidget::backgroundColor(); 

  // We will need this brush.
	
  QBrush brush(SolidPattern);
  brush.setColor( backgroundColor );

  // Create a scrollbar and redirect drawing into a temp. pixmap to save a
  // lot of fiddly drawing later.

  QScrollBar *vertScrollBar = new QScrollBar( QScrollBar::Vertical, this );
  vertScrollBar->setGeometry( 400, 400, SCROLLBAR_SIZE, height());
  vertScrollBar->setRange( 0,  0 );
  vertScrollBar->setPalette( QPalette(cg,cg,cg));
  vertScrollBar->show();
    
  QPixmap pm( vertScrollBar->width(), vertScrollBar->height() );
  pm.fill( backgroundColor );
  QPainter::redirect( vertScrollBar, &pm );
  vertScrollBar->repaint();
  QPainter::redirect( vertScrollBar, 0 );
  vertScrollBar->hide();
	
  // Initialize the pixmap which we draw sample widgets into.

  smplw.resize(width(), height());
  smplw.fill( parentWidget()->backgroundColor() );
	
  // Actually start painting in 
	
  QPainter paint( &smplw );
	
  // Inactive window
	                          
  qDrawWinPanel ( &paint, 0, 0, width()-18, height(), cg, FALSE,
		  &brush);
    
  paint.setBrush( inactiveTitleColor );
  paint.setPen( inactiveTitleColor );
  paint.drawRect( 5, 5, width()-30, 20 );
    
  paint.setFont( QFont("Helvetica", 12, QFont::Bold) );
  paint.setPen( inactiveTextColor );
  paint.drawText( (width()-25)/2-40, 20, i18n("Inactive window") );
  textLen = paint.fontMetrics().width(  i18n("Inactive window") );
    
  hotspots[0] = HotSpot( QRect( (width()-25)/2-40, 8, textLen, 14 ), 1 ); // inactive text
  hotspots[1] = HotSpot( QRect( 5, 5, width()-30, 20 ), 0 ); // inactive title

  // Active window
    
  qDrawWinPanel ( &paint, 20, 25+5, width()-20, height(), cg, FALSE,
		  &brush);
    
  paint.setBrush( activeTitleColor );paint.setPen( activeTitleColor );
  paint.drawRect( 25, 30+5, width()-32, 20 ); 
    
  paint.setFont( QFont("Helvetica", 12, QFont::Bold) );
  paint.setPen( activeTextColor );
  paint.drawText( 30+5+width()-32-(width()-32)/2-50, 45+5,  i18n("Active window") );
  textLen = paint.fontMetrics().width(  i18n("Active window" ));
    
  hotspots[2] = HotSpot( QRect( 30+5+width()-32-(width()-32)/2-50, 38, textLen, 14 ), 3 ); // Active text
  hotspots[3] = HotSpot( QRect( 25, 35, width()-32, 20 ), 2 ); // Active title

  // Menu bar
  
  qDrawShadePanel ( &paint, 25, 55, width()-32, 28, cg, FALSE, 2, &brush);
    
  paint.setFont( QFont("Helvetica", 12, QFont::Normal) );
  paint.setPen(textColor );
  textLen = paint.fontMetrics().width( i18n("File") );
  qDrawShadePanel ( &paint, 30, 52+5+2, textLen + 10, 21, cg, FALSE, 2, &brush);
  paint.drawText( 35, 69+5, i18n("File") );

  hotspots[4] = HotSpot( QRect( 35, 62, textLen, 14 ), 5 ); 
  hotspots[5] = HotSpot( QRect( 27, 52+5, 33, 21 ), 4 ); 
    
  paint.setFont( QFont("Helvetica", 12, QFont::Normal) );
  paint.setPen( textColor );
  paint.drawText( 35 + textLen + 20, 69+5, i18n("Edit") );
  textLen = paint.fontMetrics().width( i18n("Edit") );

  hotspots[6] = HotSpot( QRect( 65, 62, textLen, 14 ), 5 ); // text

  // Frame and window contents
    
  brush.setColor( windowColor );
  qDrawShadePanel ( &paint, 25, 80+5-4, width()-7-25-2, 
		    height(), cg, TRUE, 2, &brush);
    
  paint.setFont( QFont("Helvetica", 14, QFont::Normal) );
  paint.setPen( windowTextColor );
  paint.drawText( 200, 127-10, i18n( "Window text") );
  textLen = paint.fontMetrics().width( i18n("Window text") );

  hotspots[7] = HotSpot( QRect( 200, 113-10, textLen, 14 ), 9 ); // window text
  hotspots[8] = HotSpot( QRect( 116, 87, width()-138, height()-82-5 ), 8 ); // window bg
    
  // Scrollbar
    
  paint.drawPixmap(width()-35+27-16-2,80+5-2,pm);
    
  // Menu
  
  brush.setColor( backgroundColor );
  qDrawShadePanel ( &paint, 30, 80, 84, height(), cg, FALSE, 2, &brush);

  paint.setFont( QFont("Helvetica", 12, QFont::Normal) );
  paint.setPen( lightGray.dark() );
  paint.drawText( 38, 97, i18n("Disabled") );
    
  qDrawShadePanel ( &paint, 32, 101, 80, 25, cg, FALSE, 2,
		    &brush);
   
  paint.setFont( QFont("Helvetica", 12, QFont::Normal) );
  paint.setPen( textColor );
  paint.drawText( 38, 119, i18n("Selected") );
  textLen = paint.fontMetrics().width( i18n("Selected") );

  hotspots[10] = HotSpot( QRect( 38, 105, textLen, 14 ), 5 ); 
  hotspots[11] = HotSpot( QRect( 28, 101, 78, 21 ), 4 ); 
    
  // Valance

  qDrawShadePanel ( &paint, 0, height()-17,width(), 17, cg, FALSE, 2,
		    &brush);
  paint.setPen( col.light() );paint.setBrush( col.light() );
  paint.drawRect( 1, height()-17, width()-3, 15);
	
  // Stop the painting
	
  hotspots[12] = HotSpot( QRect( 0, 0, width(), height() ), 4 );
	
  repaint( FALSE );          
}

KColorScheme::KColorScheme( QWidget *parent, int mode, int desktop )
  : KDisplayModule( parent, mode, desktop )
{	
  changed=FALSE;
  ss = NULL;
  schemeList = 0L;

  // if we are just initialising we don't need to create setup widget
  if ( mode == Init )
    return;
	
  kde_display = x11Display();
  KDEChangePalette = XInternAtom( kde_display, "KDEChangePalette", False);
  screen = DefaultScreen(kde_display);
  root = RootWindow(kde_display, screen);
    
  setName( i18n("Color Scheme") );
	
  sampleWidgets = new WidgetCanvas( this );

  schemeList = new QStrList(); 
	
  readSettings();
  sampleWidgets->setGeometry( 20, 15, 400, 145 );
  sampleWidgets->drawSampleWidgets();
  connect( sampleWidgets, SIGNAL( widgetSelected( int ) ), 
	   SLOT( slotWidgetColor( int ) ) );

  QGroupBox *group = new QGroupBox( i18n("Color Scheme"), this );
  group->setGeometry( 210, 170, 245, 150 );

  sList = new QListBox( group );
  sList->setGeometry( 10, 20, 120, 120 );
  initSchemeList();
  connect( sList, SIGNAL( highlighted( int ) ),
	   SLOT( slotPreviewScheme( int ) ) );

  saveBt = new QPushButton(  i18n("Save"), group );
  saveBt->setGeometry( 140, 35, 95, 25 );
  connect( saveBt, SIGNAL( clicked() ), SLOT( slotSave() ) );
  ss = new SaveScm( 0,  "save scheme" );
		
  removeBt = new QPushButton(  i18n("Remove"), group );
  removeBt->setGeometry( 140, 70, 95, 25 );
  removeBt->setEnabled(FALSE);

  QPushButton *button = new QPushButton(  i18n("Help"), group );
  button->setGeometry( 140, 105, 95, 25 );
  connect( button, SIGNAL( clicked() ), SLOT( slotHelp() ) );

  group = new QGroupBox(  i18n("Widget color"), this );
  group->setGeometry( 15, 170, 180, 95 );

  wcCombo = new QComboBox( group );
  wcCombo->setGeometry( 10, 20, 160, 25 );
  wcCombo->insertItem(  i18n("Inactive title bar") );
  wcCombo->insertItem(  i18n("Inactive title text") );
  wcCombo->insertItem(  i18n("Active title bar") );
  wcCombo->insertItem(  i18n("Active title text") );
  wcCombo->insertItem(  i18n("Background") );
  wcCombo->insertItem(  i18n("Text") );
  wcCombo->insertItem(  i18n("Select background") );
  wcCombo->insertItem(  i18n("Select text") );
  wcCombo->insertItem(  i18n("Window background") );
  wcCombo->insertItem(  i18n("Window text") );
  connect( wcCombo, SIGNAL( activated(int) ),
	   SLOT( slotWidgetColor(int)  )  );
	
  colorButton = new KColorButton( group );
  colorButton->setGeometry( 70, 55, 100, 30 );
  colorButton->setColor( sampleWidgets->inactiveTitleColor );
  colorPushColor = sampleWidgets->inactiveTitleColor;
  connect( colorButton, SIGNAL( changed(const QColor &) ),
	   SLOT( slotSelectColor(const QColor &) ) );
	
  group = new QGroupBox(  i18n("Contrast"), this );
  group->setGeometry( 15, 270, 180, 50 );
	
  sb = new QSlider( QSlider::Horizontal,group,"Slider" );
  sb->setGeometry( 60, 20, 60, 20 );
  sb->setRange( 0, 10 );
  sb->setValue(sampleWidgets->contrast);
  sb->setFocusPolicy( QWidget::StrongFocus ); 
  connect( sb, SIGNAL(valueChanged(int)), SLOT(sliderValueChanged(int)) );

    
  QLabel *label = new QLabel( group );
  label->setGeometry( 10, 20, 45, 20 );
  label->setText( i18n("Low"));
    
  label = new QLabel( group );
  label->setGeometry( 130, 20, 40, 20 );
  label->setText(  i18n("High"));    
	
  kwmcom_init( qt_xdisplay(), 0 );
}

void KColorScheme::sliderValueChanged( int val )
{
  sampleWidgets->contrast = val;
  sampleWidgets->drawSampleWidgets();
}

void KColorScheme::slotSave()
{
  // Prepare the ss dialog.
	
  ss->setCaption( i18n("Save scheme"));
  ss->nameLine->setFocus();
	
  int ind = sList->currentItem();
	
	// Supplied schemes cannot be changed
	
  if(ind <= SUPPLIED_SCHEMES) {
    ss->nameLine->setText("");
  } else {
    ss->nameLine->setText(sList->text(ind));
    ss->nameLine->selectAll();
  }
	
  if( ss->exec() ) {
    QString str = ss->nameLine->text();
		
    QString t = str.stripWhiteSpace();
    if ( t.isEmpty() )
      return;
			
    str = str.simplifyWhiteSpace();
		
    //printf("New name %s\n", str.data());
    QStrListIterator it( *schemeList );
		
    // Using the str list iterator gives us a bit more protection
    // against dereferencing null pointers
		
    if ( str == "KDE Default" ) {
      KMsgBox::message(0,  i18n("Error"), 
		       i18n( "You have chosen a name used by a supplied color scheme"), 2 );
      return;
    }
		
    int i;
    for ( i = 1; it.current(); ++it ) {
      if ( str == it.current() && i <= SUPPLIED_SCHEMES) {
	KMsgBox::message(0, i18n("Error"), 
	i18n( "You have chosen a name used by a supplied color scheme"), 2 );
	return;
      }
      i++;
    }
		
    it.toFirst();
		
    for ( i = 1; it.current(); ++it ) {
      if ( str == it.current()) {
	schemeFile.sprintf(str);
	writeScheme();
	return; 
      }
      i++;
    }
		
    schemeFile.sprintf(str);
		
    KConfig *config = kapp->getConfig();
    config->setGroup( "ColorSchemeInfo" );
		
    str.sprintf("%d", schemeList->count()+1 );
    config->writeEntry( "Number", str );
		
    str.sprintf("Scheme%d", schemeList->count()+1 );
    config->writeEntry( str.data(), schemeFile );
    config->sync();
		
    writeScheme();
    schemeList->append(schemeFile);
    sList->clear();
    initSchemeList();
  } 
		
}

void KColorScheme::writeScheme()
{
  QString str;
	
  KConfig *config = kapp->getConfig();
  config->setGroup( schemeFile.data() );

  str.sprintf("#%02x%02x%02x", sampleWidgets->backgroundColor.red(), sampleWidgets->backgroundColor.green(), sampleWidgets->backgroundColor.blue());
  config->writeEntry("BackgroundColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->selectColor.red(), sampleWidgets->selectColor.green(), sampleWidgets->selectColor.blue());
  config->writeEntry("SelectColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->textColor.red(),
	      sampleWidgets->textColor.green(), sampleWidgets->textColor.blue());
  config->writeEntry("TextColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->activeTextColor.red(), sampleWidgets->activeTextColor.green(), sampleWidgets->activeTextColor.blue());
  config->writeEntry("ActiveTitleTextColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->inactiveTitleColor.red(), sampleWidgets->inactiveTitleColor.green(), sampleWidgets->inactiveTitleColor.blue());
  config->writeEntry("InactiveTitleBarColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->activeTitleColor.red(), sampleWidgets->activeTitleColor.green(), sampleWidgets->activeTitleColor.blue());
  config->writeEntry("ActiveTitleBarColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->inactiveTextColor.red(), sampleWidgets->inactiveTextColor.green(), sampleWidgets->inactiveTextColor.blue());
  config->writeEntry("InactiveTitleTextColor",str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->windowTextColor.red(), sampleWidgets->windowTextColor.green(), sampleWidgets->windowTextColor.blue());
  config->writeEntry("WindowTextColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->windowColor.red(), sampleWidgets->windowColor.green(), sampleWidgets->windowColor.blue());
  config->writeEntry("WindowColor", str);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->selectTextColor.red(), sampleWidgets->selectTextColor.green(), sampleWidgets->selectTextColor.blue());
  config->writeEntry("SelectTextColor", str);
	
  str.sprintf("%d", sampleWidgets->contrast);
  config->writeEntry("Contrast", str);
	
  config->sync();
}

void KColorScheme::initSchemeList()
{
  sList->clear();

  sList->insertItem( i18n("KDE Default"), 0 );
	
  QStrListIterator it( *schemeList );
  int i;
  for ( i = 1; it.current(); ++it ) {
    sList->insertItem( it.current(), i );
    i++;
  }

  it.toFirst();
	
  // When you set current item you emit a signal that changes the sample
  // widgets preview. Only do it once here or you'll get color flashing.
	
  bool FoundScheme = FALSE;

  for ( i = 1; it.current(); ++it ) {
    if ( schemeFile == it.current() ) {
      sList->setCurrentItem( i );
      FoundScheme = TRUE;
    }
    i++;
  }
	
  if( !FoundScheme )
    sList->setCurrentItem( 0 );
}

void KColorScheme::slotSelectColor( const QColor &col )
{
  colorPushColor = col;
	
  int selection;
  selection = wcCombo->currentItem()+1;
  switch(selection) {
  case 1:	sampleWidgets->inactiveTitleColor=colorPushColor;
    break;
  case 2:	sampleWidgets->inactiveTextColor=colorPushColor;
    break;
  case 3:	sampleWidgets->activeTitleColor=colorPushColor;
    break;
  case 4:	sampleWidgets->activeTextColor=colorPushColor;
    break;
  case 5:	sampleWidgets->backgroundColor=colorPushColor;
    break;
  case 6:	sampleWidgets->textColor=colorPushColor;
    break;
  case 7:	sampleWidgets->selectColor=colorPushColor;
    break;
  case 8:	sampleWidgets->selectTextColor=colorPushColor;
    break;
  case 9:	sampleWidgets->windowColor=colorPushColor;
    break;
  case 10:	sampleWidgets->windowTextColor=colorPushColor;
    break;
  }
	
  sampleWidgets->drawSampleWidgets();

  changed=TRUE;
}

void KColorScheme::slotWidgetColor( int indx )
{
  int selection;
  QColor col;
	
  if ( wcCombo->currentItem() != indx )
    wcCombo->setCurrentItem( indx );

  selection = indx + 1;
  switch(selection) {
  case 1:	col=sampleWidgets->inactiveTitleColor;
    break;
  case 2:	col=sampleWidgets->inactiveTextColor;
    break;
  case 3:	col=sampleWidgets->activeTitleColor;
    break;
  case 4:	col=sampleWidgets->activeTextColor;
    break;
  case 5:	col=sampleWidgets->backgroundColor;
    break;
  case 6:	col=sampleWidgets->textColor;
    break;
  case 7:	col=sampleWidgets->selectColor;
    break;
  case 8:	col=sampleWidgets->selectTextColor;
    break;
  case 9:	col=sampleWidgets->windowColor;
    break;
  case 10:	col=sampleWidgets->windowTextColor;
    break;
  }

  colorButton->setColor( col );
  colorPushColor=col;	
}

void KColorScheme::installSchemes()
{
  KConfig *config = kapp->getConfig();
	
  /* config->setGroup( "Background" );

     config->writeEntry( "Color1", "#326284" );
     config->writeEntry( "Color2", "#d6d6d6" );
     config->writeEntry( "ColorMode", "Gradient" );
     config->writeEntry( "OrientationMode", "Portrait" ); */
			
  // Write color scheme settings
	
  config->setGroup( "ColorSchemeInfo" );

  config->writeEntry( "Number", "5" );
  config->writeEntry( "Scheme1", "Atlas Green" );
  config->writeEntry( "Scheme2", "Blue Slate" );
  config->writeEntry( "Scheme3", "Windows 95" );
  config->writeEntry( "Scheme4", "CDE" );
  config->writeEntry( "Scheme5", "Pale Gray" );
	
  config->setGroup( "ColorScheme" );

  config->writeEntry( "Scheme", "KDE Default" );
	
  config->setGroup( "Atlas Green" );

  config->writeEntry("BackgroundColor","#afb49f");
  config->writeEntry("SelectColor","#6f7a63");
  config->writeEntry("TextColor","#000000");
  config->writeEntry("ActiveTitleTextColor","#ffffff");
  config->writeEntry("InactiveTitleBarColor","#000000");
  config->writeEntry("ActiveTitleBarColor","#6f7a63");
  config->writeEntry("InactiveTitleTextColor","#afb49f");
  config->writeEntry("WindowTextColor","#000000");
  config->writeEntry("WindowColor","#ffffff");
  config->writeEntry("SelectTextColor","#ffffff");
  config->writeEntry("Contrast","5");
	
  config->setGroup( "Blue Slate" );

  config->writeEntry("BackgroundColor","#9db9c8");
  config->writeEntry("SelectColor","#558097");
  config->writeEntry("TextColor","#000000");
  config->writeEntry("ActiveTitleTextColor","#ffffff");
  config->writeEntry("InactiveTitleBarColor","#9c9c9c");
  config->writeEntry("ActiveTitleBarColor","#558097");
  config->writeEntry("InactiveTitleTextColor","#d6d6d6");
  config->writeEntry("WindowTextColor","#000000");
  config->writeEntry("WindowColor","#c3c3c3");
  config->writeEntry("SelectTextColor","#ffffff");
  config->writeEntry("Contrast","5");
	
  config->setGroup( "Windows 95" );

  config->writeEntry("BackgroundColor","#c3c3c3");
  config->writeEntry("SelectColor","#000080");
  config->writeEntry("TextColor","#000000");
  config->writeEntry("ActiveTitleTextColor","#ffffff");
  config->writeEntry("InactiveTitleBarColor","#9c9c9c");
  config->writeEntry("ActiveTitleBarColor","#000080");
  config->writeEntry("InactiveTitleTextColor","#d6d6d6");
  config->writeEntry("WindowTextColor","#000000");
  config->writeEntry("WindowColor","#ffffff");
  config->writeEntry("SelectTextColor","#ffffff");
  config->writeEntry("Contrast","7");
	
  config->setGroup( "CDE" );

  config->writeEntry("BackgroundColor","#999999");
  config->writeEntry("SelectColor","#326284");
  config->writeEntry("TextColor","#ffffff");
  config->writeEntry("ActiveTitleTextColor","#ffffff");
  config->writeEntry("InactiveTitleBarColor","#818181");
  config->writeEntry("ActiveTitleBarColor","#326284");
  config->writeEntry("InactiveTitleTextColor","#ffffff");
  config->writeEntry("WindowTextColor","#ffffff");
  config->writeEntry("WindowColor","#818181");
  config->writeEntry("SelectTextColor","#ffffff");
  config->writeEntry("Contrast","7");
	
  config->setGroup( "Pale Gray" );

  config->writeEntry("BackgroundColor","#d6d6d6");
  config->writeEntry("SelectColor","#000000");
  config->writeEntry("TextColor","#000000");
  config->writeEntry("ActiveTitleTextColor","#ffffff");
  config->writeEntry("InactiveTitleBarColor","#a0a0a0");
  config->writeEntry("ActiveTitleBarColor","#000000");
  config->writeEntry("InactiveTitleTextColor","#d6d6d6");
  config->writeEntry("WindowTextColor","#000000");
  config->writeEntry("WindowColor","#ffffff");
  config->writeEntry("SelectTextColor","#ffffff");
  config->writeEntry("Contrast","3");
	
  config->sync();
}

KColorScheme::~KColorScheme()
{
  delete schemeList;
  if (ss != NULL)
    delete ss;
}


void KColorScheme::readSettings( int )
{
  QString str;
  QString str2;
  int schemes=0;
  QColor col;
  col.setRgb(192,192,192);

  schemeFile = NULL;
  KConfig *config;
  config = kapp->getConfig();
  config->setGroup( "ColorSchemeInfo" );
  str = config->readEntry( "Number" );

  schemeList->clear();

  if ( !str.isNull() )
    schemes = atoi(str.data());
  else {
    schemes = 0;
    if(
       QMessageBox::query(i18n("Display Setup"),
			  i18n("No desktop color schemes were found.\nDo you want to install the default color schemes now ?"), 
			  i18n("Yes"), 
			  i18n("No") )
       ) {
      installSchemes();
      config = KApplication::getKApplication()->getConfig();
      config->setGroup( "ColorSchemeInfo" );
      str = config->readEntry( "Number" );
      if ( !str.isNull() )
	schemes = atoi(str.data());
    }
			
  }
  for(int i=0;i<schemes;i++) {
    str2.sprintf("Scheme%d", i+1);
    str = config->readEntry( str2.data() );
    if ( !str.isNull() ) {
      schemeList->append(str.data());
    }
  }
	
  config->setGroup( "ColorScheme" );

  str = config->readEntry( "Scheme" );
  if ( !str.isNull() )
    schemeFile = str;
		
  config->setGroup( schemeFile.data() );
  str = config->readEntry( "InactiveTitleBarColor" );
  if ( !str.isNull() )
    sampleWidgets->inactiveTitleColor.setNamedColor( str );
  else
    sampleWidgets->inactiveTitleColor = col ;
		
  str = config->readEntry( "InactiveTitleTextColor" );
  if ( !str.isNull() )
    sampleWidgets->inactiveTextColor.setNamedColor( str );
  else
    sampleWidgets->inactiveTextColor = darkGray;
		
  str = config->readEntry( "ActiveTitleBarColor" );
  if ( !str.isNull() )
    sampleWidgets->activeTitleColor.setNamedColor( str );
  else
    sampleWidgets->activeTitleColor = darkBlue;
		
  str = config->readEntry( "ActiveTitleTextColor" );
  if ( !str.isNull() )
    sampleWidgets->activeTextColor.setNamedColor( str );
  else
    sampleWidgets->activeTextColor = white;
		
  str = config->readEntry( "TextColor" );
  if ( !str.isNull() )
    sampleWidgets->textColor.setNamedColor( str );
  else
    sampleWidgets->textColor = black;
		
  str = config->readEntry( "BackgroundColor" );
  if ( !str.isNull() )
    sampleWidgets->backgroundColor.setNamedColor( str );
  else
    sampleWidgets->backgroundColor = col;
		
  str = config->readEntry( "SelectColor" );
  if ( !str.isNull() )
    sampleWidgets->selectColor.setNamedColor( str );
  else
    sampleWidgets->selectColor = black;	
	
  str = config->readEntry( "SelectTextColor" );
  if ( !str.isNull() )
    sampleWidgets->selectTextColor.setNamedColor( str );
  else
    sampleWidgets->selectTextColor = white;
		
  str = config->readEntry( "WindowColor" );
  if ( !str.isNull() )
    sampleWidgets->windowColor.setNamedColor( str );
  else
    sampleWidgets->windowColor = white;
		
  str = config->readEntry( "WindowTextColor" );
  if ( !str.isNull() )
    sampleWidgets->windowTextColor.setNamedColor( str );
  else
    sampleWidgets->windowTextColor = black;
	
  str = config->readEntry( "Contrast" );
  if ( !str.isNull() )
    sampleWidgets->contrast = atoi( str.data() );
  else
    sampleWidgets->contrast = 7;
}

void KColorScheme::writeSettings()
{
  if ( !changed )
    return;
	
  QString str;
	
  KConfig* systemConfig = kapp->getConfig();
  systemConfig->setGroup( "Color Scheme" );

  str.sprintf("#%02x%02x%02x", sampleWidgets->backgroundColor.red(), sampleWidgets->backgroundColor.green(), sampleWidgets->backgroundColor.blue());
  systemConfig->writeEntry("BackgroundColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->selectColor.red(), sampleWidgets->selectColor.green(), sampleWidgets->selectColor.blue());
  systemConfig->writeEntry("SelectColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->textColor.red(),
	      sampleWidgets->textColor.green(), sampleWidgets->textColor.blue());
  systemConfig->writeEntry("TextColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->activeTextColor.red(), sampleWidgets->activeTextColor.green(), sampleWidgets->activeTextColor.blue());
  systemConfig->writeEntry("ActiveTitleTextColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->inactiveTitleColor.red(), sampleWidgets->inactiveTitleColor.green(), sampleWidgets->inactiveTitleColor.blue());
  systemConfig->writeEntry("InactiveTitleBarColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->activeTitleColor.red(), sampleWidgets->activeTitleColor.green(), sampleWidgets->activeTitleColor.blue());
  systemConfig->writeEntry("ActiveTitleBarColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->inactiveTextColor.red(), sampleWidgets->inactiveTextColor.green(), sampleWidgets->inactiveTextColor.blue());
  systemConfig->writeEntry("InactiveTitleTextColor",str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->windowTextColor.red(), sampleWidgets->windowTextColor.green(), sampleWidgets->windowTextColor.blue());
  systemConfig->writeEntry("WindowTextColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->windowColor.red(), sampleWidgets->windowColor.green(), sampleWidgets->windowColor.blue());
  systemConfig->writeEntry("WindowColor", str, true, true);
	
  str.sprintf("#%02x%02x%02x", sampleWidgets->selectTextColor.red(), sampleWidgets->selectTextColor.green(), sampleWidgets->selectTextColor.blue());
  systemConfig->writeEntry("SelectTextColor", str, true, true);
	
  str.sprintf("%d", sampleWidgets->contrast);
  systemConfig->writeEntry("Contrast", str, true, true);
  systemConfig->sync();
	
  systemConfig->setGroup( "ColorScheme" );
  if( schemeFile != NULL )
    systemConfig->writeEntry( "Scheme", schemeFile );
  else {
    schemeFile.sprintf("KDE Default");
    systemConfig->writeEntry( "Scheme", schemeFile );
    schemeFile = NULL;
  }
  systemConfig->sync();
}

void KColorScheme::slotApply()
{
  writeSettings();
  apply();
	
}

//Matthias
static int _getprop(Window w, Atom a, Atom type, long len, unsigned char **p){
  Atom real_type;
  int format;
  unsigned long n, extra;
  int status;
  
  status = XGetWindowProperty(qt_xdisplay(), w, a, 0L, len, False, type, &real_type, &format, &n, &extra, p);
  if (status != Success || *p == 0)
    return -1;
  if (n == 0)
    XFree((void*) *p);
  return n;
}
//Matthias
static bool getSimpleProperty(Window w, Atom a, long &result){
  long *p = 0;
  
  if (_getprop(w, a, a, 1L, (unsigned char**)&p) <= 0){
    return FALSE;
  }
  
  result = p[0];
  XFree((char *) p);
  return TRUE;
}

void KColorScheme::apply( bool  )
{
  if ( !changed )
    return;
	
  XEvent ev;
  unsigned int i, nrootwins;
  Window dw1, dw2, *rootwins;
  int (*defaultHandler)(Display *, XErrorEvent *);


  defaultHandler=XSetErrorHandler(dropError);
	
  XQueryTree(kde_display, root, &dw1, &dw2, &rootwins, &nrootwins);
	
  // Matthias
  Atom a = XInternAtom(qt_xdisplay(), "KDE_DESKTOP_WINDOW", False);
  for (i = 0; i < nrootwins; i++) {
    long result = 0;
    getSimpleProperty(rootwins[i],a, result);
    if (result){
      ev.xclient.type = ClientMessage;
      ev.xclient.display = kde_display;
      ev.xclient.window = rootwins[i];
      ev.xclient.message_type = KDEChangePalette;
      ev.xclient.format = 32;
	    
      XSendEvent(kde_display, rootwins[i] , False, 0L, &ev);
    }
  }

  XFlush(kde_display);
  XSetErrorHandler(defaultHandler);
	
  XFree((void *) rootwins);
	
  changed=FALSE;
}


void KColorScheme::slotPreviewScheme( int indx )
{
  QString str;
	
  if ( indx == 0 )
  {
    schemeFile = NULL;
    QColor col;
    col.setRgb(192,192,192);
		
    sampleWidgets->inactiveTitleColor = col;
    sampleWidgets->inactiveTextColor = darkGray;
    sampleWidgets->activeTitleColor = darkBlue;
    sampleWidgets->activeTextColor = white;
    sampleWidgets->textColor = black;
    sampleWidgets->backgroundColor = col;
    sampleWidgets->selectColor = black;	
    sampleWidgets->selectTextColor = white;
    sampleWidgets->windowColor = white;
    sampleWidgets->windowTextColor = black;
    sampleWidgets->contrast = 7;
	
  }
  else
  {
    QStrListIterator it( *schemeList );
    it += indx-1;
    schemeFile = it.current();
		
    KConfig *config = kapp->getConfig();

    config->setGroup( schemeFile.data() );
    str = config->readEntry( "InactiveTitleBarColor" );
    if ( !str.isNull() )
      sampleWidgets->inactiveTitleColor.setNamedColor( str );
    else
      sampleWidgets->inactiveTitleColor = lightGray;

    str = config->readEntry( "InactiveTitleTextColor" );
    if ( !str.isNull() )
      sampleWidgets->inactiveTextColor.setNamedColor( str );
    else
      sampleWidgets->inactiveTextColor = darkGray;

    str = config->readEntry( "ActiveTitleBarColor" );
    if ( !str.isNull() )
      sampleWidgets->activeTitleColor.setNamedColor( str );
    else
      sampleWidgets->activeTitleColor = black;

    str = config->readEntry( "ActiveTitleTextColor" );
    if ( !str.isNull() )
      sampleWidgets->activeTextColor.setNamedColor( str );
    else
      sampleWidgets->activeTextColor = white;

    str = config->readEntry( "TextColor" );
    if ( !str.isNull() )
      sampleWidgets->textColor.setNamedColor( str );
    else
      sampleWidgets->textColor = black;

    str = config->readEntry( "BackgroundColor" );
    if ( !str.isNull() )
      sampleWidgets->backgroundColor.setNamedColor( str );
    else
      sampleWidgets->backgroundColor = lightGray;

    str = config->readEntry( "SelectColor" );
    if ( !str.isNull() )
      sampleWidgets->selectColor.setNamedColor( str );
    else
      sampleWidgets->selectColor = black;	

    str = config->readEntry( "SelectTextColor" );
    if ( !str.isNull() )
      sampleWidgets->selectTextColor.setNamedColor( str );
    else
      sampleWidgets->selectTextColor = white;

    str = config->readEntry( "WindowColor" );
    if ( !str.isNull() )
      sampleWidgets->windowColor.setNamedColor( str );
    else
      sampleWidgets->windowColor = white;

    str = config->readEntry( "WindowTextColor" );
    if ( !str.isNull() )
      sampleWidgets->windowTextColor.setNamedColor( str );
    else
      sampleWidgets->windowTextColor = black;
			
    str = config->readEntry( "Contrast" );
    if ( !str.isNull() ) 
      sampleWidgets->contrast = atoi( str.data() );
    else
      sampleWidgets->contrast = 7;	
  }
	
  sb->setValue( sampleWidgets->contrast );
  sampleWidgets->drawSampleWidgets();
  int i=0;
  slotWidgetColor(i);
  changed=TRUE;
}

void KColorScheme::slotHelp()
{
  kapp->invokeHTMLHelp( "kdisplay/kdisplay-5.html", "" );
}

void KColorScheme::loadSettings()
{
  readSettings();
	
  sampleWidgets->drawSampleWidgets();

  colorButton->setColor( sampleWidgets->inactiveTitleColor );
  colorPushColor = sampleWidgets->inactiveTitleColor;
	
  sb->setValue(sampleWidgets->contrast);

  QStrListIterator it( *schemeList );
  int i;
  it.toFirst();
  bool FoundScheme = FALSE;

  for ( i = 1; it.current(); ++it ) {
    if ( schemeFile == it.current() ) {
      sList->setCurrentItem( i );
      FoundScheme = TRUE;
    }
    i++;
  }
	
  if( !FoundScheme )
    sList->setCurrentItem( 0 );
}

void KColorScheme::applySettings()
{
  writeSettings();
  apply();
}
