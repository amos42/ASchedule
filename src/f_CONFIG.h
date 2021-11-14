// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_config.pas' rev: 6.00

#ifndef f_configHPP
#define f_configHPP

#include <ComCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

class TfrmConfig : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
        TBitBtn *btnOk;
        TBitBtn *btnCancel;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TGroupBox *GroupBox1;
        TLabeledEdit *edtMaxChangeCount;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox3;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TColorBox *colCellBackground;
    TColorBox *colSpecialLesson;
        TColorBox *colFixedCell;
        TColorBox *colFocusCell;
        TColorBox *colCellText;
        TColorBox *colGrayCell;
        TColorBox *colLunchTime;
        TColorBox *colGridLine;
    TColorBox *colMoveLesson;
    TLabel *Label9;
	void __fastcall FormShow(TObject* Sender);
	void __fastcall btnOkClick(TObject* Sender);
	
public:
        __fastcall TfrmConfig(TComponent* Owner);
};


extern PACKAGE TfrmConfig* frmConfig;


#endif	// f_config
