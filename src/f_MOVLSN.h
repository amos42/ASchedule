// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_SINIT.pas' rev: 6.00

#ifndef F_MOVLSNH
#define F_MOVLSNH

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

class TfrmMoveLesson : public Forms::TForm
{
	typedef Forms::TForm inherited;
	
__published:
        TBitBtn *BitBtn1;
    TPanel *pnlLessonInfo;
    TStringGrid *grdSchedule;
    TPanel *Panel2;
    TSpeedButton *btnYear1;
    TSpeedButton *btnYear2;
    TSpeedButton *btnYear3;
    TLabel *Label1;
    TPanel *Panel3;
    TEdit *edtLessonName;
    TLabel *Label2;
    TLabel *Label3;
    TPanel *pnlTeachers;
    TSpeedButton *btnItemUp;
    TSpeedButton *btnItemDown;
    TListBox *lstLesson;
    TSpeedButton *btnAdd;
    TSpeedButton *btnDelete;
    TSpeedButton *btnModify;
    TCheckListBox *lstClass;
    TCheckListBox *lstTeacher;
    TPopupMenu *PopupTeacherSubject;
    TMenuItem *qqq1;
    TButton *btnCancel;
    TComboBox *cboSubject;
    TLabel *Label5;
    TPanel *pnlTotalClass;
    TEdit *edtShortName;
	void __fastcall grdScheduleClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall BitBtn1Click(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall btnSpcDelClick(TObject* Sender);
    void __fastcall grdScheduleDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall btnYearClick(TObject *Sender);
    void __fastcall lstTeacherClickCheck(TObject *Sender);
    void __fastcall lstClassClickCheck(TObject *Sender);
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall btnDeleteClick(TObject *Sender);
    void __fastcall btnModifyClick(TObject *Sender);
    void __fastcall lstLessonClick(TObject *Sender);
    void __fastcall btnItemUpClick(TObject *Sender);
    void __fastcall btnItemDownClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
	
public:
        __fastcall TfrmMoveLesson(TComponent* Owner);

private:
    int curYear;

    void EnableLessonList( bool tf );
    void EnableLessonItems( bool tf );
    void ClearLessonItems( void );

public:
    bool IsChange;
};


extern PACKAGE TfrmMoveLesson* frmMoveLesson;


#endif	// f_SINIT
