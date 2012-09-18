//
//
// "Misc Options" Tab for KFM configuration
//
// (c) Sven Radej 1998
// (c) David Faure 1998

#include <qlabel.h>
#include <qgroupbox.h>
#include <qlayout.h>//CT - 12Nov1998
#include <kapp.h>

#include "miscopts.h"

#include "../../kfm/config-kfm.h" // include default values directly from kfm

//-----------------------------------------------------------------------------

KMiscOptions::KMiscOptions( QWidget *parent, const char *name )
    : KConfigWidget( parent, name )
{
        QVBoxLayout *lay = new QVBoxLayout(this, 40 /* big border */, 20);
 
        //----------------- "Per-url settings" checkbox ---------
        urlpropsbox = new QCheckBox(i18n("&Allow per-URL settings"),
                                    this);
        urlpropsbox->adjustSize();
        urlpropsbox->setMinimumSize(urlpropsbox->size());
        lay->addWidget(urlpropsbox);
        //-------------------------------
 
        //----------------- "Tree view" checkbox ---------
        treefollowbox = new QCheckBox(i18n("Tree &view follows navigation"),
                                    this);
        treefollowbox->adjustSize();
        treefollowbox->setMinimumSize(treefollowbox->size());
        lay->addWidget(treefollowbox);
        //-------------------------------

        //---------------- "Terminal" lineedit ---------------
        QHBoxLayout *hlay = new QHBoxLayout(10);
        lay->addLayout(hlay);
        QLabel * label = new QLabel(i18n("Terminal"),this);
        label->adjustSize();
        label->setMinimumSize(label->size());
        hlay->addWidget(label, 1);
        
        leTerminal = new QLineEdit(this);
        leTerminal->adjustSize();
        leTerminal->setMinimumSize(leTerminal->size());
        hlay->addWidget(leTerminal, 5);
        //-------------------------------

        //---------------- "Editor" lineedit ---------------
        hlay = new QHBoxLayout(10);
        lay->addLayout(hlay);
        label = new QLabel(i18n("Editor"),this);
        label->adjustSize();
        label->setMinimumSize(label->size());
        hlay->addWidget(label, 1);
        
        leEditor = new QLineEdit(this);
        leEditor->adjustSize();
        leEditor->setMinimumSize(leEditor->size());
        hlay->addWidget(leEditor, 5);
        //-------------------------------

        lay->addStretch(10);
        lay->activate();
 
        loadSettings();
 
        setMinimumSize( 400, 100 );
}

void KMiscOptions::loadSettings()
{
    // *** load ***
    g_pConfig->setGroup( "KFM Misc Defaults" );
    bool bUrlprops = g_pConfig->readBoolEntry( "EnablePerURLProps", false);
    bool bTreeFollow = g_pConfig->readBoolEntry( "TreeFollowsView", false);
    QString sTerminal = g_pConfig->readEntry( "Terminal", DEFAULT_TERMINAL );
    QString sEditor = g_pConfig->readEntry( "Editor", DEFAULT_EDITOR );

    // *** apply to GUI ***

    urlpropsbox->setChecked(bUrlprops);
    treefollowbox->setChecked(bTreeFollow);
    leTerminal->setText(sTerminal);
    leEditor->setText(sEditor);
}

void KMiscOptions::defaultSettings()
{
    urlpropsbox->setChecked(false);
    treefollowbox->setChecked(false);
    leTerminal->setText(DEFAULT_TERMINAL);
    leEditor->setText(DEFAULT_EDITOR);
}

void KMiscOptions::saveSettings()
{
    g_pConfig->setGroup( "KFM Misc Defaults" );
    g_pConfig->writeEntry( "EnablePerURLProps", urlpropsbox->isChecked());
    g_pConfig->writeEntry( "TreeFollowsView", treefollowbox->isChecked());
    g_pConfig->writeEntry( "Terminal", leTerminal->text());
    g_pConfig->writeEntry( "Editor", leEditor->text());
    g_pConfig->sync();
}

void KMiscOptions::applySettings()
{
    saveSettings();
}

#include "miscopts.moc"
