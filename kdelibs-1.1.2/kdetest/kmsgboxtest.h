/*
 * $Id: kmsgboxtest.h,v 1.3 1999/01/15 08:59:29 kulow Exp $
 *
 * $Log: kmsgboxtest.h,v $
 * Revision 1.3  1999/01/15 08:59:29  kulow
 * use seperate moc.cpp files - did you know that most header files herein are
 * complete hacks? ;)
 *
 * Revision 1.2  1997/07/24 21:04:01  kalle
 * Kalle: Patches for SGI
 * 	New ktoolbartest (for newtoolbar 0.6)
 *
 * Revision 1.1  1997/04/13 17:49:43  kulow
 * Sources imported
 *
 * Revision 1.1  1997/03/15 21:40:24  kalle
 * Initial revision
 *
 * Revision 1.3.2.1  1997/01/10 19:48:33  alex
 * public release 0.1
 *
 * Revision 1.3  1997/01/10 19:44:33  alex
 * *** empty log message ***
 *
 * Revision 1.2.4.1  1997/01/10 16:46:33  alex
 * rel 0.1a, not public
 *
 * Revision 1.2  1997/01/10 13:05:52  alex
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1997/01/10 13:05:21  alex
 * imported
 *
 */

/// Toplevel
/** create a toplevel widget
 */

#ifndef _KMSGBOXTEST_H
#define _KMSGBOXTEST_H

#include <qwidget.h>

class QListBox;
class QPushButton;

class TopLevel : public QWidget
{
    Q_OBJECT
public:

    TopLevel( QWidget *parent=0, const char *name=0 );
protected:
    void resizeEvent(QResizeEvent *);
    QListBox *e;
    QPushButton *ok;
public slots:
    void okPressed();
    void tabChanged(int);
    void doMsgBox();
    void showMsgBox(int);
};

#endif

