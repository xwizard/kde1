/* This file is part of the KDE Display Manager Configuration package
    Copyright (C) 1997 Thomas Tanghus (tanghus@earthling.net)

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/  

#include "utils.h"
#include "kdm-font.moc"



// Destructor
KDMFontWidget::~KDMFontWidget()
{
  if(gui)
  {
    delete fontcombo;
    delete fontlabel;
  }
}


KDMFontWidget::KDMFontWidget(QWidget *parent, const char *name, bool init)
  : KConfigWidget(parent, name)
{
      gui = !init;
      loadSettings();
      if(gui)
        setupPage(parent);
}

void KDMFontWidget::setupPage(QWidget *)
{
      QGroupBox *tGroup = new QGroupBox( 
            klocale->translate("Select fonts"), this );
      QGroupBox *bGroup = new QGroupBox( 
            klocale->translate("Example"), this );
      QPushButton *fontbtn = 
             new QPushButton(klocale->translate("Change font..."), tGroup);
      connect(fontbtn, SIGNAL(clicked()), SLOT(slotGetFont()));
      fontbtn->setFixedSize(fontbtn->sizeHint());
      fontcombo = new QComboBox( FALSE, tGroup );
      connect(fontcombo, SIGNAL(highlighted(int)), SLOT(slotSetFont(int)));
      fontcombo->insertItem(klocale->translate("Greeting"), 0);
      fontcombo->insertItem(klocale->translate("Fail"), 1);
      fontcombo->insertItem(klocale->translate("Standard"), 2);
      fontcombo->setFixedSize(fontcombo->sizeHint());
      fontlabel = new QLabel( bGroup );
      //fontlabel->setAutoResize(true);
      fontlabel->setFrameStyle(QFrame::WinPanel|QFrame::Sunken);
      //fontlabel->adjustSize();

      QBoxLayout *ml = new QVBoxLayout(this, 10);

      QBoxLayout *tLayout = new QVBoxLayout(tGroup, 10);
      QBoxLayout *bLayout = new QVBoxLayout(bGroup, 10);
      tLayout->addSpacing(tGroup->fontMetrics().height());
      bLayout->addSpacing(bGroup->fontMetrics().height());

      QBoxLayout *tLayout2 = new QHBoxLayout();
      tLayout->addLayout(tLayout2, 1);
      tLayout2->addWidget(fontbtn);
      tLayout2->addWidget(fontcombo);
      tLayout2->addStretch();

      bLayout->addWidget(fontlabel);

      ml->addWidget(tGroup);
      ml->addWidget(bGroup, 3);
      ml->addStretch(2);

      tLayout->activate();
      bLayout->activate();
      ml->activate();

      slotSetFont(0);
}

void KDMFontWidget::applySettings()
{
  //debug("KDMFontWidget::applySettings()");
  QString fn(CONFIGFILE);
  KSimpleConfig *c = new KSimpleConfig(fn);

  c->setGroup("KDM");
  // write font
  c->writeEntry("StdFont", stdfont, true);
  c->writeEntry("GreetFont", greetfont, true);
  c->writeEntry("FailFont", failfont, true);

  delete c;
}

void KDMFontWidget::loadSettings()
{
  QString fn(CONFIGFILE), str;
  
  // Get config object
  KSimpleConfig *c = new KSimpleConfig(fn);
  c->setGroup("KDM");

  // Read the fonts
  stdfont.setFamily("Helvetica");
  stdfont = c->readFontEntry("StdFont", &stdfont);
  failfont.setFamily("Courier");
  failfont = c->readFontEntry("FailFont", &failfont);
  greetfont.setFamily("Helvetica");
  greetfont = c->readFontEntry("GreetFont", &greetfont);

  delete c;
}

void KDMFontWidget::slotGetFont()
{
  QApplication::setOverrideCursor( waitCursor );

  KFontDialog *fontdlg = new KFontDialog(0L, 0L, TRUE, 0L);
  QApplication::restoreOverrideCursor( );
  fontdlg->getFont(tmpfont);
  switch (fontcombo->currentItem())
  {
    case 0:
      greetfont = tmpfont;
      break;
    case 1:
      failfont = tmpfont;
      break;
    case 2:
      stdfont = tmpfont;
      break;
  }
  fontlabel->setFont(tmpfont);
  //fontlabel->setFixedSize(fontlabel->sizeHint());
  delete fontdlg;
}

void KDMFontWidget::slotSetFont(int id)
{
  QApplication::setOverrideCursor( waitCursor );
  switch (id)
  {
    case 0:
      tmpfont = greetfont;
      fontlabel->setText(i18n("Greeting font"));
      break;
    case 1:
      tmpfont = failfont;
      fontlabel->setText(i18n("Fail font"));
      break;
    case 2:
      tmpfont = stdfont;
      fontlabel->setText(i18n("Standard font"));
      break;
  }
  fontlabel->setFont(tmpfont);
  //fontlabel->adjustSize();
  QApplication::restoreOverrideCursor( );
}



