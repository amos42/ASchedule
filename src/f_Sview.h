// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_SVIEW.pas' rev: 6.00

#ifndef f_SVIEWHPP
#define f_SVIEWHPP

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

class TfrmView : public Forms::TForm
{
	typedef Forms::TForm inherited;

__published:
        TPaintBox *pntChange1;
        TPaintBox *pntChange2;
        TPanel *Panel3;
        TPaintBox *pntTeacher;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall pntTeacherPaint(TObject *Sender);
        void __fastcall pntChange1Paint(TObject *Sender);
        void __fastcall pntChange2Paint(TObject *Sender);

public:
        __fastcall TfrmView(TComponent* Owner);

public:
	int ViewPage;
//	TScheduleData *ViewData;
    int yyy[50][50];

	WORD ViewTeacher;
	TClassPos StartPos;
	TClassPos EndPos;

	SmallString<10>  Change1;
	SmallString<10>  Change2;

	void DispClassData(HDC hDC, int w, int n);
    void RecalcInvalidInfo(void);
};


extern PACKAGE TfrmView* frmView;


#endif	// f_SVIEW
