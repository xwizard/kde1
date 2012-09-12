
#include <qpushbt.h>
#include <qlined.h>

#include <kapp.h>
#include <kiconloader.h>
#include <kiconloaderdialog.h>

#include "kiconloadertestmain.h"
#include "kiconloadertestmain.h"

MyMain::MyMain()
{
  initMetaObject();
  icon_sel = new KIconLoaderDialog;
  test = new QPushButton("test", this);
  test->setPixmap(KApplication::getKApplication()->getIconLoader()->loadIcon("exec.xpm"));
  test->setGeometry(0,0,50,50);
  connect(test, SIGNAL(clicked()), this, SLOT(changePix()));
  le_dir = new QLineEdit(this);
  le_dir->setGeometry( 10, 70, 300, 24 );
  connect( le_dir, SIGNAL(returnPressed()), this, SLOT(insertPath()) );
  le_dir->show();
  test->show();
}

void MyMain::changePix()
{
  QString name;
  QPixmap pix = icon_sel->selectIcon( name, "*" );
  if( !pix.isNull() )
    {
      debug("name = %s", (const char *) name );
      test->setPixmap(pix);
    }
}

void MyMain::insertPath()
{
  KApplication::getKApplication()->getIconLoader()->insertDirectory(3, le_dir->text() );
  delete icon_sel;
  icon_sel = new KIconLoaderDialog();
}
