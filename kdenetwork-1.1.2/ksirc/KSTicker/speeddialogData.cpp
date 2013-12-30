/**********************************************************************

	--- Qt Architect generated file ---

	File: speeddialogData.cpp
	Last generated: Sun Dec 21 09:13:46 1997

	DO NOT EDIT!!!  This file will be automatically
	regenerated by qtarch.  All changes will be lost.

 *********************************************************************/

#include "speeddialogData.h"

#define Inherited QDialog

#include <qlabel.h>
#include <qpushbt.h>

speeddialogData::speeddialogData
(
	QWidget* parent,
	const char* name
)
	:
	Inherited( parent, name, 0 )
{
	sliderTick = new("QSlider") QSlider( this, "Slider_1" );
	sliderTick->setGeometry( 90, 10, 100, 20 );
	sliderTick->setMinimumSize( 10, 10 );
	sliderTick->setMaximumSize( 32767, 32767 );
	connect( sliderTick, SIGNAL(valueChanged(int)), SLOT(updateTick(int)) );
	sliderTick->setOrientation( QSlider::Horizontal );
	sliderTick->setRange( 10, 200 );
	sliderTick->setSteps( 10, 50 );
	sliderTick->setValue( 30 );
	sliderTick->setTracking( TRUE );
	sliderTick->setTickmarks( QSlider::NoMarks );
	sliderTick->setTickInterval( 0 );

	sliderStep = new("QSlider") QSlider( this, "Slider_2" );
	sliderStep->setGeometry( 90, 45, 100, 20 );
	sliderStep->setMinimumSize( 10, 10 );
	sliderStep->setMaximumSize( 32767, 32767 );
	connect( sliderStep, SIGNAL(valueChanged(int)), SLOT(updateStep(int)) );
	sliderStep->setOrientation( QSlider::Horizontal );
	sliderStep->setRange( 1, 10 );
	sliderStep->setSteps( 1, 2 );
	sliderStep->setValue( 3 );
	sliderStep->setTracking( TRUE );
	sliderStep->setTickmarks( QSlider::NoMarks );
	sliderStep->setTickInterval( 0 );

	lcdTick = new("QLCDNumber") QLCDNumber( this, "LCDNumber_1" );
	lcdTick->setGeometry( 200, 5, 60, 30 );
	lcdTick->setMinimumSize( 10, 10 );
	lcdTick->setMaximumSize( 32767, 32767 );
	lcdTick->setFrameStyle( 33 );
	lcdTick->setSmallDecimalPoint( FALSE );
	lcdTick->setNumDigits( 3 );
	lcdTick->setMode( QLCDNumber::DEC );
	lcdTick->setSegmentStyle( QLCDNumber::Outline );

	lcdStep = new("QLCDNumber") QLCDNumber( this, "LCDNumber_2" );
	lcdStep->setGeometry( 200, 40, 60, 30 );
	lcdStep->setMinimumSize( 10, 10 );
	lcdStep->setMaximumSize( 32767, 32767 );
	lcdStep->setFrameStyle( 33 );
	lcdStep->setSmallDecimalPoint( FALSE );
	lcdStep->setNumDigits( 3 );
	lcdStep->setMode( QLCDNumber::DEC );
	lcdStep->setSegmentStyle( QLCDNumber::Outline );

	QLabel* dlgedit_Label_1;
	dlgedit_Label_1 = new("QLabel") QLabel( this, "Label_1" );
	dlgedit_Label_1->setGeometry( 10, 5, 80, 30 );
	dlgedit_Label_1->setMinimumSize( 10, 10 );
	dlgedit_Label_1->setMaximumSize( 32767, 32767 );
	dlgedit_Label_1->setText( i18n("Tick Interval") );
	dlgedit_Label_1->setAlignment( 289 );
	dlgedit_Label_1->setMargin( -1 );

	QLabel* dlgedit_Label_2;
	dlgedit_Label_2 = new("QLabel") QLabel( this, "Label_2" );
	dlgedit_Label_2->setGeometry( 10, 40, 80, 30 );
	dlgedit_Label_2->setMinimumSize( 10, 10 );
	dlgedit_Label_2->setMaximumSize( 32767, 32767 );
	dlgedit_Label_2->setText( i18n("Step Size") );
	dlgedit_Label_2->setAlignment( 289 );
	dlgedit_Label_2->setMargin( -1 );

	QPushButton* dlgedit_PushButton_2;
	dlgedit_PushButton_2 = new("QPushButton") QPushButton( this, "PushButton_2" );
	dlgedit_PushButton_2->setGeometry( 140, 80, 120, 30 );
	dlgedit_PushButton_2->setMinimumSize( 10, 10 );
	dlgedit_PushButton_2->setMaximumSize( 32767, 32767 );
	connect( dlgedit_PushButton_2, SIGNAL(pressed()), SLOT(terminate()) );
	dlgedit_PushButton_2->setText( i18n("&Close") );
	dlgedit_PushButton_2->setAutoRepeat( FALSE );
	dlgedit_PushButton_2->setAutoResize( FALSE );

	resize( 270,120 );
	setMinimumSize( 0, 0 );
	setMaximumSize( 32767, 32767 );
}


speeddialogData::~speeddialogData()
{
}
void speeddialogData::updateTick(int)
{
}
void speeddialogData::updateStep(int)
{
}
void speeddialogData::terminate()
{
}
#include "speeddialogData.moc"
