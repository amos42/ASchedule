// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_SINIT.pas' rev: 6.00

#ifndef f_SBJH
#define f_SBJH

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
#include <Mask.hpp>
#include <CheckLst.hpp>
#include <Menus.hpp>	// Pascal unit

class TfrmSubject : public Forms::TForm
{
	typedef Forms::TForm inherited;
	
__published:
        TBitBtn *BitBtn1;
    TPanel *pnlLessonInfo;
    TEdit *edtName;
    TEdit *edtSubName;
    TLabel *Label2;
    TLabel *Label3;
    TPanel *pnlSubjects;
    TSpeedButton *btnItemUp;
    TSpeedButton *btnItemDown;
    TListBox *lstSubject;
    TSpeedButton *btnAdd;
    TSpeedButton *btnDelete;
    TSpeedButton *btnModify;
    TButton *btnCancel;
    TLabel *Label1;
    TEdit *edtSubjectCode;
    TSpeedButton *SpeedButton1;
    TLabel *Label4;
    TCheckBox *chkYear1;
    TCheckBox *chkYear2;
    TCheckBox *chkYear3;
    TSpeedButton *btnImport;
    TSpeedButton *btnExport;
    TSaveDialog *dlgSave;
    TOpenDialog *dlgOpen;
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall BitBtn1Click(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall btnSpcDelClick(TObject* Sender);
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall btnDeleteClick(TObject *Sender);
    void __fastcall btnModifyClick(TObject *Sender);
    void __fastcall lstSubjectClick(TObject *Sender);
    void __fastcall btnItemUpClick(TObject *Sender);
    void __fastcall btnItemDownClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnExportClick(TObject *Sender);
    void __fastcall btnImportClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
	
public:
        __fastcall TfrmSubject(TComponent* Owner);

private:
    void EnableSubjectList( bool tf );
    void EnableSubjectItems( bool tf );
    void ClearSubjectItems( void );

public:
    bool IsChange;
};


extern PACKAGE TfrmSubject* frmSubject;


#endif	// f_SINIT
