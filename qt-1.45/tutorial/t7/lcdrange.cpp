/****************************************************************
**
** Implementation of LCDRange class, Qt tutorial 7
**
****************************************************************/

#include "lcdrange.h"

#include <qscrollbar.h>
#include <qlcdnumber.h>

LCDRange::LCDRange( QWidget *parent, const char *name )
        : QWidget( parent, name )
{
    lcd  = new QLCDNumber( 2, this, "lcd"  );
    lcd->move( 0, 0 );
    sBar = new QScrollBar( 0, 99,		       	// range
			   1, 10, 			// line/page steps
			   0, 				// inital value
			   QScrollBar::Horizontal, 	// orientation
                           this, "scrollbar" );
    connect( sBar, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)) );
    connect( sBar, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)) );

}

int LCDRange::value() const
{
    return sBar->value();
}

void LCDRange::setValue( int value )
{
    sBar->setValue( value );
}

void LCDRange::resizeEvent( QResizeEvent * )
{
    lcd->resize( width(), height() - 16 - 5 );
    sBar->setGeometry( 0, lcd->height() + 5, width(), 16 );
}
