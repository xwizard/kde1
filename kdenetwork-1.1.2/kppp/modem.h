/*
 *              kPPP: A pppd Front End for the KDE project
 *
 * $Id: modem.h,v 1.8.2.6 1999/08/08 15:07:58 porten Exp $
 *
 *              Copyright (C) 1997 Bernd Johannes Wuebben
 *                      wuebben@math.cornell.edu
 * 
 * This file was added by Harri Porten <porten@tu-harburg.de>
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

#ifndef _MODEM_H_
#define _MODEM_H_

#include <qdir.h>

#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

#include <qsocknot.h>

#include <config.h>

void    alarm_handler(int);

class Modem : public QObject {
  Q_OBJECT
public:
  Modem();
  ~Modem();

  bool opentty();
  bool closetty();
  bool hangup();
  bool writeChar(unsigned char);
  bool writeLine(const char *);
  bool dataMode() const { return data_mode; }
  void setDataMode(bool set) { data_mode = set; }
  const char *modemMessage() const;  
  speed_t modemspeed();
  static QString parseModemSpeed(const QString &);
  void notify(const QObject *, const char *);
  void stop();
  void flush();

  int     lockdevice();
  void    unlockdevice();

public:
  static Modem *modem;

signals:
  void charWaiting(unsigned char);

private slots:
  void startNotifier();
  void stopNotifier();
  void resumeNotifier();
  void readtty(int);  

private:
  void escape_to_command_mode();

private:
  int modemfd;
  QSocketNotifier *sn;
  bool data_mode;
  QString errmsg;
  struct termios initial_tty;
  struct termios tty;
  bool modem_is_locked;
};

#ifndef HAVE_USLEEP
void usleep (long);
#endif

#endif


