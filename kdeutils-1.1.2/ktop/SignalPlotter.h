/*
    KTop, the KDE Task Manager
   
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

// $Id: SignalPlotter.h,v 1.2 1999/03/05 09:53:30 cschlaeg Exp $

#ifndef _SignalPlotter_h_
#define _SignalPlotter_h_

#include <qwidget.h>
#include <qarray.h>
#include <qbrush.h>

class QColor;

#define MAXBEAMS 5

class SignalPlotter : public QWidget
{
	Q_OBJECT

public:
	SignalPlotter(QWidget* parent = 0, const char* name = 0, int min = 0,
				  int max = 100);
	~SignalPlotter();

	bool addBeam(QColor col);
	void addSample(int s0, int s1 = 0, int s2 = 0, int s3 = 0, int s4 = 0);

	void setLowPass(bool lp)
	{
		lowPass = lp;
	}

protected:
	virtual void resizeEvent(QResizeEvent*);
	virtual void paintEvent(QPaintEvent*);

private:
	int minValue;
	int maxValue;
	bool lowPass;
	int* beamData[MAXBEAMS];
	QColor beamColor[MAXBEAMS];
	int beams;
} ;

#endif
