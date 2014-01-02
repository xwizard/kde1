/*
    KTop, the KDE Task Manager
   
    Copyright (C) 1997 Bernd Johannes Wuebben
                       wuebben@math.cornell.edu

    Copyright (C) 1998 Nicolas Leclercq
                       nicknet@planete.net
    
	Copyright (c) 1999 Chris Schlaeger
	                   cs@kde.org
    
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

// $Id: TaskMan.cpp,v 1.11 1999/03/11 08:22:41 cschlaeg Exp $

#include <qtabbar.h>
#include <qmessagebox.h>

#include <kapp.h>

#include "ktop.h"
#include "ReniceDlg.h"
#include "ProcListPage.h"
#include "OSProcessList.h"
#include "TaskMan.moc"

#define NONE -1

/*
 * This constructor creates the actual QTabDialog. It is a modeless dialog,
 * using the toplevel widget as its parent, so the dialog won't get its own
 * window.
 */
TaskMan::TaskMan(QWidget* parent, const char* name, int sfolder)
	: QTabDialog(parent, name, FALSE, 0)
{
	pages[0] = pages[1] = NULL;

    // Delete the OK button, it is created by default by the constructor.
	setOkButton(0);

	connect(tabBar(), SIGNAL(selected(int)), SLOT(tabBarSelected(int)));
	connect(this, SIGNAL(enableRefreshMenu(bool)),
			MainMenuBar, SLOT(enableRefreshMenu(bool)));
						 

    /*
     * set up page 0 (process list viewer)
     */
    pages[0] = procListPage = new ProcListPage(this, "ProcListPage");
    CHECK_PTR(procListPage);
	
	/*
	 * set up page 1 (performance monitor)
	 */
    pages[1] = perfMonPage = new PerfMonPage(this, "PerfMonPage");
    CHECK_PTR(perfMonPage);

	currentPage = PAGE_PLIST;

	// setting from config file can be overidden by command line option
	if (sfolder >= 0)
		currentPage = sfolder;

    // add pages...
    addTab(procListPage, i18n("Processes &List"));
    addTab(perfMonPage, i18n("Performance &Meter"));

    move(0,0);
}

void 
TaskMan::raiseStartUpPage()
{
    // startup_page settings...
	currentPage = Kapp->getConfig()->readNumEntry("StartUpPage", currentPage);

	// tell QTabDialog to raise the specified startup page
	showPage(pages[currentPage]);
} 

void 
TaskMan::tabBarSelected(int tabIndx)
{
	switch (tabIndx)
	{
	case PAGE_PLIST:
		procListPage->clearSelection();
		procListPage->setAutoUpdateMode(TRUE);
		procListPage->update();
		emit(enableRefreshMenu(TRUE));
		break;
	case PAGE_PERF:
		procListPage->clearSelection();
		procListPage->setAutoUpdateMode(FALSE);
		emit(enableRefreshMenu(FALSE));
		break;
	}
	currentPage = tabIndx;
}

void 
TaskMan::saveSettings()
{
	QString tmp;

	// save window size, isn't this ancient history?
	tmp.sprintf("%04d:%04d:%04d:%04d",
				parentWidget()->x(), parentWidget()->y(),
				parentWidget()->width(), parentWidget()->height());
	Kapp->getConfig()->writeEntry("G_Toplevel", tmp);

	// save startup page (tab)
	Kapp->getConfig()->writeEntry("StartUpPage", currentPage, TRUE);

	// save process list settings
	procListPage->saveSettings();

	Kapp->getConfig()->sync();
}
