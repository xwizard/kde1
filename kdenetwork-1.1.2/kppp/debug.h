/*
 *        kPPP: A pppd front end for the KDE project
 *
 * $Id: debug.h,v 1.4.2.1 1999/03/11 15:15:06 porten Exp $
 *            Copyright (C) 1997  Bernd Wuebben
 *                 wuebben@math.cornel.edu
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _DEBUGWIDGET_
#define _DEBUGWIDGET_

#include <stdlib.h>

#include <qdialog.h>
#include <qfont.h>
#include <qstring.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qmlined.h>
#include <qpushbt.h>


class myMultiEdit : public QMultiLineEdit {
public:

  myMultiEdit(QWidget *parent=0, const char *name=0);

  void newLine();
  void  insertChar(unsigned char c);
};


class DebugWidget : public QDialog {
  Q_OBJECT
public:
  DebugWidget(QWidget *parent=0, const char *name=0);

  void clear();

public slots:
  void statusLabel(const char *);
  void statusLabel(QString);
  void toggleVisibility();
  void addChar(unsigned char);

private slots:
  void hideit();

private:
  void resizeEvent(QResizeEvent *e);

private:
  void enter();
  QFrame *fline;
  QPushButton *dismiss;
  myMultiEdit *text_window;

  QLabel *statuslabel;
};

#endif

