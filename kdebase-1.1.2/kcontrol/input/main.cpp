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


#include <kcontrol.h>
#include "mouse.h"
#include "keyboard.h"


class KInputApplication : public KControlApplication
{
public:

  KInputApplication(int &argc, char **arg, const char *name);

  void init();
  void apply();
  void defaultValues();

private:

  MouseConfig *mouse;
  KeyboardConfig *keyboard;
};


KInputApplication::KInputApplication(int &argc, char **argv, const char *name)
  : KControlApplication(argc, argv, name)
{
  mouse = 0; keyboard = 0;

  if (runGUI())
    {
      if (!pages || pages->contains("mouse"))
	addPage(mouse = new MouseConfig(dialog, "mouse", FALSE), 
		klocale->translate("&Mouse"), "input-2.html");
      if (!pages || pages->contains("keyboard"))
	addPage(keyboard = new KeyboardConfig(dialog, "keyboard", FALSE), 
		klocale->translate("&Keyboard"), "input-1.html");

      if (mouse || keyboard)
        dialog->show();
      else
        {
          fprintf(stderr, klocale->translate("usage: kcminput [-init | {mouse,keyboard}]\n"));
          justInit = TRUE;
        }

    }
}


void KInputApplication::init()
{
  MouseConfig *mouse = new MouseConfig(0, 0, TRUE);
  mouse->applySettings();
  delete mouse;

  KeyboardConfig *keyboard = new KeyboardConfig(0, 0, TRUE);
  keyboard->applySettings();
  delete keyboard;
}


void KInputApplication::apply()
{
  if (mouse)
    mouse->applySettings();
  if (keyboard)
    keyboard->applySettings();
}


void KInputApplication::defaultValues()
{
  if (mouse)
    mouse->defaultSettings();
  if (keyboard)
    keyboard->defaultSettings();
}


int main(int argc, char **argv)
{
  KInputApplication app(argc, argv, "kcminput");
  app.setTitle(klocale->translate("Input Devices Properties"));
  
  if (app.runGUI())
    return app.exec();
  else
    {
      app.init();
      return 0;
    }
}
