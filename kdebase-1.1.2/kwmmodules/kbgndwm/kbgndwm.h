/*
 * kbgndwm.h.  Part of the KDE Project.
 *
 * Copyright (C) 1997 Martin Jones
 *               1998 Matej Koss
 *
 */

#ifndef __KBGNDWM_H__
#define __KBGNDWM_H__

//----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <kwmmapp.h>
#include <drag.h>

#include <X11/X.h>
#include <X11/Xlib.h>

#include "bg.h"

//----------------------------------------------------------------------------

#define MAX_DESKTOPS 8

//----------------------------------------------------------------------------


class KBGndManager: public QWidget
{

  Q_OBJECT

public:
  KBGndManager( KWMModuleApplication * );

protected:
  void applyDesktop( int d );
  void cacheDesktop();
  void readSettings();

  void paintEvent(QPaintEvent *e);

public slots:
  void desktopChange( int );
  void commandReceived( QString );
  void toggleOneDesktop();

  void timeclick();
  void slotDropEvent( KDNDDropZone * );
  void slotModeSelected( int mode );
  void setUndock();

private slots:
  void mousePressEvent(QMouseEvent *e);
  void displaySettings();
  void settings();
  void dock();
  void undock();

private:
  KWMModuleApplication* kwmmapp;
  QPopupMenu *popup_m;
  QPopupMenu *modePopup;
  QPixmap pixmap;

  KBackground *desktops;
  int current;

  bool oneDesktopMode;
  int desktop;

  bool docked;

  int o_id;

  QString wallpaper;
};



//----------------------------------------------------------------------------

#endif
