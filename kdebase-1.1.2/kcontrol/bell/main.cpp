/*
  main.cpp - A sample KControl Application

  written 1997 by Matthias Hoelzer
  
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


#include "kcontrol.h"
#include "bell.h"


class KBellApplication : public KControlApplication
{
public:

  KBellApplication(int &argc, char **arg, const char *name);

  void init();
  void apply();
  void defaultValues();

private:

  KBellConfig *bell;
};


KBellApplication::KBellApplication(int &argc, char **argv, const char *name)
  : KControlApplication(argc, argv, name)
{
  bell = 0;

  if (runGUI())
    {
      if (!pages || pages->contains("bell"))
        addPage(bell = new KBellConfig(dialog, "bell", FALSE), 
		klocale->translate("&Bell"), "bell-1.html");

      if (bell)
        dialog->show();
      else
        {
          fprintf(stderr, klocale->translate("usage: kcmbell [-init | bell]\n"));
	  justInit = TRUE;
        }
    }
}


void KBellApplication::init()
{
  KBellConfig *bellconfig = new KBellConfig(0, 0, TRUE);
  delete bellconfig;
}


void KBellApplication::apply()
{
  if (bell)
    bell->applySettings();
}


void KBellApplication::defaultValues()
{
  if (bell)
    bell->defaultSettings();
}


int main(int argc, char **argv)
{
  KBellApplication app(argc, argv, "kcmbell");
  app.setTitle(klocale->translate("Bell settings"));
  
  if (app.runGUI())
    return app.exec();
  else
    {
      app.init();
      return 0;
    }
}
