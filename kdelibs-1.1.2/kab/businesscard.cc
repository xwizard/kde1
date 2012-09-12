/* -*- C++ -*-
 * This file implements the businesscard-like central display
 * of the selected address.
 * 
 * the KDE addressbook.
 * copyright:  (C) Mirko Sucker, 1998
 * license:    GNU Public License, Version 2
 * mail to:    Mirko Sucker <mirko.sucker@unibw-hamburg.de>
 * requires:   C++-compiler, STL, string class,
 *             Nana for debugging
 * $Revision: 1.11 $
 */

#include <string>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qtooltip.h>
#include <kurllabel.h>
#include "businesscard.h"

extern "C" {
#include <stdio.h>
	   }

#include "debug.h"

const int BusinessCard::Grid=5;

BusinessCard::BusinessCard(QWidget* parent, const char* name)
  : QWidget(parent, name),
    tile(false),
    bgColor(lightGray),
    background(0)
{
  register bool GUARD; GUARD=false;
  // ############################################################################
  LG(GUARD, "BusinessCard constructor: creating object.\n");
  urlEmail=new KURLLabel(this);
  CHECK(urlEmail!=0);
  urlEmail->setAutoResize(true);
  urlEmail->setTransparentMode(true);
  urlEmail->setFloat(true);
  urlEmail->setUnderline(false);
  urlEmail->setLineWidth(0);
  urlEmail->setMidLineWidth(0);
  urlHome=new KURLLabel(this);
  CHECK(urlHome!=0);
  urlHome->setAutoResize(true);
  urlHome->setTransparentMode(true);
  urlHome->setFloat(true);
  urlHome->setUnderline(false);
  urlHome->setLineWidth(0);
  urlHome->setMidLineWidth(0);
  // -----
  connect(urlEmail, SIGNAL(leftClickedURL(const char*)),
	  SLOT(mailURLClicked(const char*)));
  connect(urlHome, SIGNAL(leftClickedURL(const char*)),
	  SLOT(homeURLClicked(const char*)));
  resize(310, 160);
  // ############################################################################
}

BusinessCard::~BusinessCard()
{
  register bool GUARD; GUARD=false;
  // ############################################################################
  if(background!=0) delete background;
  LG(GUARD, "BusinessCard destructor: object removed.\n");
  // ############################################################################
}
  
void BusinessCard::paintEvent(QPaintEvent*)
{
  register bool GUARD; GUARD=false;
  LG(GUARD, "BusinessCard::paintEvent: repainting.\n");
  // ############################################################################
  QFont original, font;
  QRect rect;
  QPixmap pm(width(), height());
  QPainter p;     
  bool drawSeparator=false, useTile;
  int posSeparator=0, cy, addressHeight, contactHeight;
  string temp;
  // ----- initialize painter and draw background:
  p.begin(&pm);
  useTile=(background==0 ? false : (!background->isNull() && tile));
  if(useTile)
    {
      CHECK(background!=0 && !background->isNull());
      p.drawTiledPixmap(0, 0, width(), height(), *background);
    } else {
      p.setPen(bgColor);
      p.setBrush(bgColor);
      p.drawRect(0, 0, width(), height());
      p.setPen(black);
    }
  // ----- now draw on the background:
  original=p.font();
  font.setFamily(original.family());
  font.setPointSize(10);
  p.setFont(font);
  // ----- print the birthday in the upper right corner 
  //       if it has been entered:
  if(current.birthday.isValid())
    { //       by now I do not take care if there is enough space left
      p.drawText
	(width()-Grid-p.fontMetrics().width(current.birthday.toString()),
	 Grid+p.fontMetrics().ascent(), current.birthday.toString());
    }
  // ----- now draw the contact data:
  cy=height()-Grid;
  if(!current.URL.empty())
    {
      temp=(string)"URL: "+current.URL;
      urlHome->setFont(font);
      urlHome->setText(temp.c_str());
      urlHome->move(Grid, cy+3-urlHome->height());
      urlHome->show();
      cy-=urlHome->height();
      drawSeparator=true;
      temp="";
    } else {
      urlHome->hide();
    }
  if(!current.emails.empty())
    {
      temp=(string)"email: "+current.emails.front();
      urlEmail->setFont(font);
      urlEmail->setText(temp.c_str());
      urlEmail->move(Grid, cy+3-urlEmail->height());
      urlEmail->show();
      cy-=urlEmail->height();
      drawSeparator=true;
      temp="";
    } else {
      urlEmail->hide();
    }
  if(!current.telephone.empty())
    {
      temp+=(string)"tel: "+current.telephone;
    }
  if(!current.fax.empty())
    {
      if(!temp.empty()) temp+=", ";
      temp+=(string)"fax: "+current.fax;
    }
  if(!current.modem.empty())
    {
      if(!temp.empty()) temp+=", ";
      temp+=(string)"modem: "+current.modem;
    }
  if(!temp.empty())
    {
      p.drawText(Grid, cy, temp.c_str());
      cy-=p.fontMetrics().height();
      drawSeparator=true;
      temp="";
    }
  if(drawSeparator)
    {
      posSeparator=cy;
      cy-=Grid;
    } 
  contactHeight=height()-cy;
  CHECK(contactHeight>0);
  if(drawSeparator)
    {
      p.drawLine(Grid, posSeparator, width()-Grid, posSeparator);
    }
  // ----- draw the address
  cy=Grid; // begin at top
  font.setPointSize(12);
  p.setFont(font);
  if(!current.fn.empty())
    {
      temp=current.fn;
    } else {
      if(!current.title.empty())
	{
	  if(!temp.empty()) temp+=" ";
	  temp+=current.title;
	}
      if(!current.namePrefix.empty())
	{
	  if(!temp.empty()) temp+=" ";
	  temp+=current.namePrefix;
	}
      if(!current.firstname.empty())
	{
	  if(!temp.empty()) temp+=" ";
	  temp+=current.firstname;
	}
      if(!current.additionalName.empty())
	{
	  if(!temp.empty()) temp+=" ";
	  temp+=current.additionalName;
	}
      if(!current.name.empty())
	{
	  if(!temp.empty()) temp+=" ";
	  temp+=current.name;
	}
    }
  if(!temp.empty())
    {
      font.setItalic(true);
      p.setFont(font);
      p.setPen(blue);
      p.drawText(2*Grid, cy+p.fontMetrics().height(), temp.c_str());
      font.setItalic(false);
      p.setFont(font);
      p.setPen(black);
      cy+=p.fontMetrics().height();
    }
  if(!current.role.empty())
    {
      p.drawText(2*Grid, cy+p.fontMetrics().height(), current.role.c_str());
      cy+=p.fontMetrics().height();
    }        
  if(!current.address.empty())
    {
      p.drawText(2*Grid, cy+p.fontMetrics().height(), current.address.c_str());
      cy+=p.fontMetrics().height();
    }

  temp = "";
  if(!current.town.empty())
    {
      temp+=current.town;
    } 
  if(!current.state.empty())
    {
      if (!temp.empty()) temp += " ";
      temp+=current.state;
    }
  if (!current.zip.empty())
    {
      if (!temp.empty()) temp += " ";
      temp += current.zip;
      p.drawText(2*Grid, cy+p.fontMetrics().height(), temp.c_str());
      cy+=p.fontMetrics().height();
    }

  if(!current.country.empty())
    {
      p.drawText(2*Grid, cy+p.fontMetrics().height(), current.country.c_str());
      cy+=p.fontMetrics().height();
    }        
  addressHeight=cy+Grid;
  // ----- now draw the comment:
  if(!current.comment.empty())
    {
      if(height()-addressHeight-contactHeight > p.fontMetrics().height())
	{
	  cy=height()-addressHeight-contactHeight;
	  addressHeight+=cy%p.fontMetrics().height();
	  cy-=cy%p.fontMetrics().height();
	  p.drawText(Grid, addressHeight, width()-2*Grid, cy,
		     AlignHCenter | AlignBottom | WordBreak,
		     current.comment.c_str(), -1, &rect);
	}
    }
  // ----- finish painting:
  p.end();
  bitBlt(this, 0, 0, &pm);
  // ############################################################################
}

void BusinessCard::currentChanged(AddressBook::Entry entry)
{
  register bool GUARD; GUARD=false;
  // ############################################################################
  LG(GUARD, "BusinessCard::currentChanged: updating and repainting.\n");
  current=entry;
  repaint(false);
  // ############################################################################
}

void BusinessCard::setBackground(QPixmap* pixmap)
{
  register bool GUARD; GUARD=false;
  // ############################################################################
  LG(GUARD, "BusinessCard::setBackground: background pixmap changed.\n");
  if(background==0)
    {
      background=new QPixmap;
    }
  CHECK(background!=0);
  *background=*pixmap;
  // ############################################################################
}

void BusinessCard::setBackground(const string& path)
{
  register bool GUARD; GUARD=false;
  // ############################################################################
  QPixmap pixmap;
  if(!pixmap.load(path.c_str()))
    {
      //      QMessageBox::information
      //	(this, "Image load failure", "Could not load background image!");
      return;
    }
  LG(GUARD, "BusinessCard::setBackground: loaded image from file \"%s\".\n", 
     path.c_str());
  filename=path;
  setBackground(&pixmap);
  useTile(true); // WORK_TO_DO: respect settings!
  // ############################################################################
}

void BusinessCard::useTile(bool what)
{
  // ############################################################################
  tile=what;
  if(tile && background!=0) 
    {
      setBackgroundPixmap(*background);
    } else {
      QPixmap dummy;
      setBackgroundPixmap(dummy);
    }
  repaint(false);
  // ############################################################################
}

void BusinessCard::mailURLClicked(const char*)
{
  // ############################################################################
  emit(mailURLActivated());
  // ############################################################################
}

void BusinessCard::homeURLClicked(const char*)
{
  // ############################################################################
  emit(homeURLActivated());
  // ############################################################################
}

// #############################################################################
// MOC OUTPUT FILES:
#include "businesscard.moc"
// #############################################################################

