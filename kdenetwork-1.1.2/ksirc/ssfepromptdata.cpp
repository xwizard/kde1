/**********************************************************************

	--- Qt Architect generated file ---

	File: ssfepromptdata.cpp
	Last generated: Thu Jan 15 21:21:29 1998

	DO NOT EDIT!!!  This file will be automatically
	regenerated by qtarch.  All changes will be lost.

 *********************************************************************/

#include "ssfepromptdata.h"

#define Inherited QDialog

#include <qpushbt.h>

ssfepromptdata::ssfepromptdata
(
	QWidget* parent,
	const char* name
)
	:
	Inherited( parent, name, TRUE, 20480 )
{
	prompt = new("QLabel") QLabel( this, "Label_1" );
	prompt->setGeometry( 10, 10, 220, 30 );
	prompt->setMinimumSize( 10, 10 );
	prompt->setMaximumSize( 32767, 32767 );
	prompt->setText( "" );
	prompt->setAlignment( 289 );
	prompt->setMargin( -1 );

	SLine = new("QLineEdit") QLineEdit( this, "LineEdit_1" );
	SLine->setGeometry( 240, 10, 100, 30 );
	SLine->setMinimumSize( 10, 10 );
	SLine->setMaximumSize( 32767, 32767 );
	connect( SLine, SIGNAL(returnPressed()), SLOT(terminate()) );
	SLine->setText( "" );
	SLine->setMaxLength( 32767 );
	SLine->setEchoMode( QLineEdit::Normal );
	SLine->setFrame( TRUE );

	QPushButton* dlgedit_PushButton_1;
	dlgedit_PushButton_1 = new("QPushButton") QPushButton( this, "PushButton_1" );
	dlgedit_PushButton_1->setGeometry( 240, 50, 100, 30 );
	dlgedit_PushButton_1->setMinimumSize( 10, 10 );
	dlgedit_PushButton_1->setMaximumSize( 32767, 32767 );
	connect( dlgedit_PushButton_1, SIGNAL(clicked()), SLOT(terminate()) );
	dlgedit_PushButton_1->setText( "&OK" );
	dlgedit_PushButton_1->setAutoRepeat( FALSE );
	dlgedit_PushButton_1->setAutoResize( FALSE );
	dlgedit_PushButton_1->setAutoDefault( TRUE );

	resize( 350,90 );
	setMinimumSize( 350, 90 );
	setMaximumSize( 350, 90 );
}


ssfepromptdata::~ssfepromptdata()
{
}
void ssfepromptdata::terminate()
{
}
#include "ssfepromptdata.moc"
