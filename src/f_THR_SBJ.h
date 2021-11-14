// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_TEACHER.pas' rev: 6.00

#ifndef f_THR_SBJHPP
#define f_THR_SBJHPP

#include <ComCtrls.hpp>	// Pascal unit
#include <dblookup.hpp>	// Pascal unit
#include <DBGrids.hpp>	// Pascal unit
#include <TabNotBk.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Mask.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

#include "Global.h"

class TfrmTeacherSubject : public Forms::TForm
{
	typedef Forms::TForm inherited;
	
__published:
    TBitBtn *btnCancel;
        TPanel *pnlTeacherInfo;
    TEdit *edtTimes;
    TLabel *Label1;
    TLabel *Label2;
    TBitBtn *btnOK;
    TComboBox *cbYear;
    TLabel *Label3;
    TGroupBox *GroupBox1;
    TCheckBox *chkClass1;
    TCheckBox *chkClass2;
    TCheckBox *chkClass3;
    TCheckBox *chkClass4;
    TCheckBox *chkClass5;
    TCheckBox *chkClass6;
    TCheckBox *chkClass7;
    TCheckBox *chkClass8;
    TCheckBox *chkClass9;
    TCheckBox *chkClass10;
    TCheckBox *chkClass11;
    TCheckBox *chkClass12;
    TCheckBox *chkClass13;
    TCheckBox *chkClass14;
    TCheckBox *chkClass15;
    TCheckBox *chkClass16;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TGroupBox *GroupBox2;
    TLabel *Label25;
    TLabel *Label26;
    TLabel *Label27;
    TLabel *Label28;
    TLabel *Label29;
    TLabel *Label30;
    TLabel *Label31;
    TCheckBox *chkWeek1;
    TCheckBox *chkWeek2;
    TCheckBox *chkWeek3;
    TCheckBox *chkWeek4;
    TCheckBox *chkWeek5;
    TCheckBox *chkWeek6;
    TCheckBox *chkWeek7;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label32;
    TLabel *Label33;
    TLabel *Label34;
    TLabel *Label35;
    TLabel *Label36;
    TCheckBox *chkLesson1;
    TCheckBox *chkLesson2;
    TCheckBox *chkLesson3;
    TCheckBox *chkLesson4;
    TCheckBox *chkLesson5;
    TCheckBox *chkLesson6;
    TCheckBox *chkLesson7;
    TCheckBox *chkLesson8;
    TLabel *Label37;
    TCheckBox *chkMoveLesson;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label38;
    TLabel *Label39;
    TCheckBox *chkClass17;
    TCheckBox *chkClass18;
    TCheckBox *chkClass19;
    TCheckBox *chkClass20;
    TComboBox *cboSubject;
    TRadioButton *rbLimitWeek0;
    TRadioButton *rbLimitWeek1;
    TPanel *pnlLimitWeeks;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnOKClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall rbLimitWeek0Click(TObject *Sender);
    void __fastcall rbLimitWeek1Click(TObject *Sender);
    void __fastcall cbYearClick(TObject *Sender);
	
private:
    TCheckBox *chkClasses[atCLASS_MAX-atCLASS_BASE+1];
    TCheckBox *chkWeeks[7];
    TCheckBox *chkLessons[8];

public:
        __fastcall TfrmTeacherSubject(TComponent* Owner);

public:
        int teacher_no, subject_idx;
        void SetTeacherSubjectNo( int teacher_no, int subject_idx );
};


extern PACKAGE TfrmTeacherSubject* frmTeacherSubject;

#endif	// f_TEACHER
