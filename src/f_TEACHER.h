// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_TEACHER.pas' rev: 6.00

#ifndef f_TEACHERHPP
#define f_TEACHERHPP

#include <ComCtrls.hpp>	// Pascal unit
#include <dblookup.hpp>	// Pascal unit
#include <DBGrids.hpp>	// Pascal unit
#include <TabNotBk.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Mask.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <DBTables.hpp>	// Pascal unit
#include <DBCtrls.hpp>	// Pascal unit
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

class TfrmTeacher : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
        TSpeedButton *btnAdd;
        TSpeedButton *btnDelete;
        TSpeedButton *btnModify;
        TBitBtn *btnClose;
        TPanel *pnlTeacherInfo;
        TLabel *Label38;
        TLabel *Label37;
        TEdit *edtTeacher;
        TPanel *pnlTotal;
        TPanel *pnlTeacherNo;
        TPanel *pnlTeachers;
        TSpeedButton *btnItemUp;
        TSpeedButton *btnItemDown;
    TListView *lvSubjects;
    TSpeedButton *btnNewSubject;
    TSpeedButton *btnDeleteSubject;
    TSpeedButton *btnModifySubject;
    TLabel *Label39;
    TPanel *pnlTotalAll;
    TListBox *lstTeacher;
    TPanel *Panel1;
    TCheckBox *cbCharge;
    TEdit *edtCharge;
    TComboBox *cbStress1;
    TComboBox *cbStress2;
    TComboBox *cbStress3;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TSpeedButton *btnImport;
    TSpeedButton *btnExport;
    TSaveDialog *dlgSave;
    TOpenDialog *dlgOpen;
    TLabel *Label4;
    TPanel *pnlTotalClass;
    TButton *btnCancel;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnDeleteClick(TObject *Sender);
        void __fastcall btnModifyClick(TObject *Sender);
        void __fastcall btnItemUpClick(TObject *Sender);
        void __fastcall btnItemDownClick(TObject *Sender);
    void __fastcall lstTeacherClick(TObject *Sender);
    void __fastcall btnNewSubjectClick(TObject *Sender);
    void __fastcall btnImportClick(TObject *Sender);
    void __fastcall btnExportClick(TObject *Sender);
    void __fastcall btnModifySubjectClick(TObject *Sender);
    void __fastcall btnDeleteSubjectClick(TObject *Sender);
    void __fastcall lvSubjectsSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall lvSubjectsCustomDrawSubItem(TCustomListView *Sender,
          TListItem *Item, int SubItem, TCustomDrawState State,
          bool &DefaultDraw);
    void __fastcall btnCancelClick(TObject *Sender);

private:
    TColor curListColor;
    void EnableTeacherList( bool tf );
	void EnableTeacherItems( bool tf );
    void ClearTeacherItems(void);

public:
        __fastcall TfrmTeacher(TComponent* Owner);
    bool IsChange;
};


extern PACKAGE TfrmTeacher* frmTeacher;

#endif	// f_TEACHER
