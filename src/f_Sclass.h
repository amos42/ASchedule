// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_SCLASS.pas' rev: 6.00

#ifndef f_SCLASSHPP
#define f_SCLASSHPP

#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>

class TfrmClass : public Forms::TForm
{
	typedef Forms::TForm inherited;

__published:
        TPanel *Panel3;
        TPaintBox *pntTeacher;
        TPanel *Panel1;
        TSpeedButton *btnYear1;
        TSpeedButton *btnYear2;
        TSpeedButton *btnYear3;
        TListBox *lstClass;
        TPanel *pnlInfo;
        TEdit *edtInfo;
    TLabel *Label1;
    TImageList *ImageList1;
    TToolBar *ToolBar2;
    TToolButton *btnClose;
    TToolButton *ToolButton1;
    TPanel *pnlClassInfo;
	void __fastcall DispClassData(HDC hDC, int w, int n);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall pntTeacherPaint(TObject *Sender);
        void __fastcall pntTeacherMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnYear1Click(TObject *Sender);
        void __fastcall btnYear2Click(TObject *Sender);
        void __fastcall btnYear3Click(TObject *Sender);
        void __fastcall lstClassClick(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);

public:
        __fastcall TfrmClass(TComponent* Owner);

public:
    struct TViewClasses {
    	int SubjectType;
	    System::SmallString<4>  Subject;
	    System::SmallString<8>  TeacherName;
    } ;

	TViewClasses ViewData[atWEEK_MAX-atWEEK_BASE+1][atLESSON_MAX-atLESSON_BASE+1];
	WORD ViewClass;

};

extern PACKAGE TfrmClass* frmClass;

#endif	// f_SCLASS
