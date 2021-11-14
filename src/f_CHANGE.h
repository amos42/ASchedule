// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_CHANGE.pas' rev: 6.00

#ifndef f_CHANGEHPP
#define f_CHANGEHPP

#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

class TfrmChange : public Forms::TForm
{
	typedef Forms::TForm inherited;

__published:
        TBitBtn *OKBtn;
        TBitBtn *CancelBtn;
	void __fastcall OKBtnClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall CancelBtnClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction &Action);

public:
        __fastcall TfrmChange(TComponent* Owner);

public:
	WORD  ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN;
	WORD  ChangeType;
//	WORD  ChangeCount;
//	bool  isAddList;
};


extern PACKAGE TfrmChange* frmChange;

bool CanItChange(int t, int sw, int sn, int ew, int en, int *pChangeCount);
bool CanItMulti(int t, int sw, int sn, int ew, int en, int *pChangeCount);
bool CanItRelease(int t, int sw, int sn, int ew, int en, int *pChangeCount);


#endif	// f_CHANGE
