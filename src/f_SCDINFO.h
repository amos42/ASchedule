// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_SINIT.pas' rev: 6.00

#ifndef f_SCDINFOHPP
#define f_SCDINFOHPP

#include <ComCtrls.hpp>	// Pascal unit
#include <TabNotBk.hpp>	// Pascal unit
#include <DBTables.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Spin.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>
#include <Mask.hpp>	// Pascal unit

class TfrmScheduleInfo : public Forms::TForm
{
	typedef Forms::TForm inherited;
	
__published:
    TBitBtn *btnClose;
    TEdit *edtScheduleName;
    TLabel *Label7;
    TEdit *edtAuthorName;
    TLabel *Label1;
    TLabel *Label2;
    TMemo *memMemo;
    TLabel *Label3;
    TMaskEdit *mskAuthorDate;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);
	
public:
        __fastcall TfrmScheduleInfo(TComponent* Owner);

private:

public:
};


extern PACKAGE TfrmScheduleInfo* frmScheduleInfo;


#endif	// f_SINIT
