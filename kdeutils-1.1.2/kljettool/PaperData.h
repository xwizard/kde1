/**********************************************************************

	--- Dlgedit generated file ---

	File: PaperData.h
	Last generated: Tue Jun 24 22:20:20 1997

	DO NOT EDIT!!!  This file will be automatically
	regenerated by dlgedit.  All changes will be lost.

 *********************************************************************/

#ifndef PaperData_included
#define PaperData_included

#include <qdialog.h>
#include <qchkbox.h>
#include <qlined.h>
#include <qradiobt.h>
#include <qcombo.h>
#include "Data.h"

class PaperData : public QDialog
{
    Q_OBJECT

public:

    PaperData
    (
        QWidget* parent = NULL,
        const char* name = NULL
    );

    virtual ~PaperData();

    Data *data;

public slots:


protected slots:

    virtual void ManaulFeedCheckBoxClicked();
    virtual void AutoContinueCheckBoxClicked();
    virtual void LandscapeCheckBoxClicked();
    virtual void ProtraitCheckBoxClicked();
    virtual void FormatSelected(const char*);
    virtual void copiesChanged(const char*);
    virtual void linesChanged(const char*);

protected:

    QComboBox* FormatComboBox;
    QButtonGroup* MiscButtonGroup;
    QButtonGroup* OrientButtonGroup;
    QLineEdit* numberofcopies;
    QLineEdit* LengthEdit;
    QRadioButton* PortraitCheckBox;
    QRadioButton* LandscapeCheckBox;
    QCheckBox* ManualFeedCheckBox;
    QCheckBox* AutoContinueCheckBox;

};

#endif // PaperData_included
