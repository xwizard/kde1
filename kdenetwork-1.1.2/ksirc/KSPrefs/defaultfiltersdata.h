/**********************************************************************

	--- Qt Architect generated file ---

	File: defaultfiltersdata.h
	Last generated: Tue Jul 28 02:30:57 1998

	DO NOT EDIT!!!  This file will be automatically
	regenerated by qtarch.  All changes will be lost.

 *********************************************************************/

#ifndef defaultfiltersdata_included
#define defaultfiltersdata_included

#include <qframe.h>
#include <qlabel.h>
#include <qchkbox.h>
#include <qlined.h>
#include <qcombo.h>

class defaultfiltersdata : public QFrame
{
    Q_OBJECT

public:

    defaultfiltersdata
    (
        QWidget* parent = NULL,
        const char* name = NULL
    );

    virtual ~defaultfiltersdata();

public slots:


protected slots:


protected:
    QCheckBox* kSircColours;
    QCheckBox* mircColours;
    QLabel* LabelNickB;
    QLineEdit* SLE_SampleColourNick;
    QLineEdit* SLE_SampleHighlight;
    QComboBox* usHighlightColour;
    QComboBox* NickFColour;
    QComboBox* NickBColour;

};

#endif // defaultfiltersdata_included
