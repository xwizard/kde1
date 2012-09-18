    /*

    $Id: main.cpp,v 1.15 1998/02/24 18:01:39 kulow Exp $

    Requires the Qt widget libraries, available at no cost at 
    http://www.troll.no
       
    Copyright (C) 1997 Bernd Johannes Wuebben   
                       wuebben@math.cornell.edu


    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    */
 


#include <qstrlist.h> 
#include <qtabdlg.h>

#include <kapp.h>

#include "kfontmanager.h"
#include "kfontlist.h"
#include "kfontexplorer.h"
#include <kfontdialog.h>
#include "version.h"
#include <klocale.h>

char PICS_PATH[256];



int main( int argc, char *argv[] ){


	KApplication a( argc, argv, "kfontmanager" );
// KApplication's general font should be used or charset properly set	
//	a.setFont(QFont("Helvetica",12,QFont::Normal),TRUE);

	sprintf( PICS_PATH, "%s/kfontmanager/pics", KApplication::kde_datadir().data() );

	QTabDialog* mainWindow = new QTabDialog( 0, 0, TRUE );

	QString str;
	str = i18n("KDE Font Manager");
	str += ' ';
	str += KFONTMANAGERVERSION;

	mainWindow->setCaption(str.data());
	mainWindow->setCancelButton(i18n("Cancel"));
	mainWindow->setApplyButton(i18n("Apply"));

	KFontManager manager(mainWindow,"manager");
	KFontExplorer explorer(mainWindow,"explorer");
	
	KFontList list(mainWindow,"list");

	mainWindow->addTab( &manager, i18n("KDE Fonts") );
	mainWindow->addTab( &explorer,i18n("Font Explorer"));
	mainWindow->addTab( &list, i18n("Raw X11 Font List") );
   
        a.enableSessionManagement(true);
        a.setWmCommand(argv[0]);      
   
        a.setTopWidget(mainWindow);
       	mainWindow->resize( 430, 450 );
	mainWindow->exec();
   	return 0;
}



