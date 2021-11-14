// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_SINIT.pas' rev: 6.00

#ifndef f_SINITHPP
#define f_SINITHPP

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

class TfrmSchool : public Forms::TForm
{
	typedef Forms::TForm inherited;
	
__published:
        TLabel *Label4;
        TBitBtn *BitBtn1;
        TTabbedNotebook *tabYear;
        TStringGrid *grdSchedule1;
        TLabel *Label2;
        TStringGrid *grdSchedule2;
        TStringGrid *grdSchedule3;
        TPanel *Panel1;
        TUpDown *spnWeek1;
        TUpDown *spnWeek2;
        TUpDown *spnWeek3;
        TUpDown *spnWeek4;
        TUpDown *spnWeek5;
        TUpDown *spnWeek6;
        TPanel *pnlTotal;
        TGroupBox *GroupBox1;
        TSpeedButton *btnSpcAdd;
        TSpeedButton *btnSpcDel;
        TSpeedButton *btnSpcEdit;
        TListView *lvSpecial;
        TMaskEdit *edtCC1;
        TMaskEdit *edtCC2;
    TMaskEdit *edtCC3;
    TEdit *edtSchoolName;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label8;
    TLabel *Label9;
    TMaskEdit *mskLunch1;
    TMaskEdit *mskLunch2;
    TMaskEdit *mskLunch3;
    TLabel *Label1;
    TLabel *Label3;
    TLabel *Label5;
    TLabel *Label7;
    TSpeedButton *btnImport;
    TSpeedButton *btnExport;
    TSaveDialog *dlgSave;
    TOpenDialog *dlgOpen;
	void __fastcall grdScheduleClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall BitBtn1Click(TObject* Sender);
	void __fastcall tabYearChange(TObject* Sender, int NewTab, bool &AllowChange);
	void __fastcall edtCC1Change(TObject* Sender);
	void __fastcall edtCC2Change(TObject* Sender);
	void __fastcall edtCC3Change(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall btnSpcAddClick(TObject* Sender);
	void __fastcall btnSpcDelClick(TObject* Sender);
	void __fastcall btnSpcEditClick(TObject* Sender);
	void __fastcall lvSpecialMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall spnWeekClick(TObject *Sender, TUDBtnType Button);
    void __fastcall btnImportClick(TObject *Sender);
    void __fastcall btnExportClick(TObject *Sender);
    void __fastcall edtSchoolNameChange(TObject *Sender);
    void __fastcall grdScheduleDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall mskLunchChange(TObject *Sender);
	
public:
        __fastcall TfrmSchool(TComponent* Owner);

private:
	Grids::TStringGrid* grdSchedules[3];
	void __fastcall RecalcTimes(void);

    int g_curYear;
    TStringGrid *grdSchedule;

    void PutCellData( int y, int w, int n, String str );
    void PutCurCellData( int w, int n, String str );

public:
};


extern PACKAGE TfrmSchool* frmSchool;


#endif	// f_SINIT
