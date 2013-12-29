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


//#include <kapp.h>
//#include <qobject.h>
#include <kslider.h>

#include <kcontrol.h>
#include "standard.h"
#include "global.h"


class KDisplayApplication : public KControlApplication
{
public:

  KDisplayApplication(int &argc, char **arg, const char *name);

  void init();
  void apply();

private:

  KStdConfig *standard;
  KGlobalConfig *global;
};


KDisplayApplication::KDisplayApplication(int &argc, char **argv, const char *name)
  : KControlApplication(argc, argv, name)
{
  standard = 0;
  global = 0;

  if (runGUI())
    {
    
      if (!pages || pages->contains("standard"))
        addPage(standard = new KStdConfig(dialog), 
		klocale->translate("&Standard shortcuts"), "kdisplay-3.html");
	if (!pages || pages->contains("global"))
        addPage(global = new KGlobalConfig(dialog), 
		klocale->translate("&Global shortcuts"), "kdisplay-3.html");
     
      
      if (standard)
        dialog->show();
      else
        {
          fprintf(stderr, klocale->translate("usage: kcmdisplay [-init | {standard,screensaver,colors,style}]\n"));
          justInit = TRUE;
        }
      
    }
}


void KDisplayApplication::init()
{
 
  KStdConfig *standard =  new KStdConfig(0);
  delete standard;
  
  KGlobalConfig *global =  new KGlobalConfig(0);
  delete global;
 
}


void KDisplayApplication::apply()
{

  if (standard)
    standard->applySettings();
if (global)
    global->applySettings();

}

int main(int argc, char **argv)
{
  
  KDisplayApplication app(argc, argv, "kcmkeys");
  app.setTitle(klocale->translate("Key binding settings"));
  
  if (app.runGUI())
    return app.exec();
  else
    { 
      app.init();
      return 0;
    }
}
