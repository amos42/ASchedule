// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_main.pas' rev: 6.00

#ifndef f_mainHPP
#define f_mainHPP

#include <ActnList.hpp>	// Pascal unit
#include <ToolWin.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Tabs.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <DBTables.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
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


class TfrmMain : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
        TTabControl *tabWeek;
        TPanel *Panel1;
        TScrollBar *hsbTeacher;
        TPanel *Panel3;
        TPaintBox *pntTeacher;
        TPanel *Panel4;
        TPaintBox *pntVTimes;
        TPanel *Panel5;
        TPaintBox *pntHTimes;
        TTabSet *tabYear;
        TStatusBar *sbStatus;
        TToolBar *ToolBar1;
        TToolButton *btnClose;
        TToolButton *ToolButton2;
        TToolButton *btnNew;
        TToolButton *ToolButton3;
        TToolButton *btnOpen;
        TToolButton *btnSave;
        TToolButton *ToolButton5;
        TToolButton *btnPrint;
        TToolButton *ToolButton4;
        TToolButton *btnPersonal;
        TToolButton *btnClass;
        TToolButton *ToolButton8;
        TToolButton *btnTools;
        TPanel *pnlTools;
        TMainMenu *MainMenu1;
        TMenuItem *mnuFile;
        TMenuItem *mnuNew;
        TMenuItem *mnuOpen;
        TMenuItem *mnuSave;
        TMenuItem *mnuSaveAs;
        TMenuItem *N4;
        TMenuItem *mnuClose;
        TMenuItem *mnuView;
        TMenuItem *mnuPersonal;
        TMenuItem *mnuClass;
        TMenuItem *mnuTools;
        TMenuItem *mnuTools0;
        TMenuItem *mnuTools1;
        TMenuItem *mnuTools2;
        TMenuItem *mnuTools3;
        TMenuItem *mnuTools4;
        TMenuItem *mnuPrint;
        TMenuItem *mnuPrnTeachers;
        TMenuItem *mnuPrnClasses;
        TMenuItem *mnuPrnSchedules;
        TMenuItem *CSV1;
        TMenuItem *mnuPrnTeacherCSV;
        TMenuItem *mnuPrnClassesCSV;
        TMenuItem *N1;
    TMenuItem *mnuSchoolInfo;
    TMenuItem *mnuTeacherInfo;
        TMenuItem *N14;
        TMenuItem *mnuConfig;
        TMenuItem *N7;
        TMenuItem *N8;
        TOpenDialog *dlgOpen;
        TSaveDialog *dlgSave;
        TImageList *ImageList1;
        TPopupMenu *PopupMenu1;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N13;
        TMenuItem *N11;
        TMenuItem *N12;
        TActionList *ActionList1;
        TAction *Action1;
        TAction *Action2;
        TAction *Action3;
        TAction *Action4;
        TAction *Action5;
    TPopupMenu *PopupMenu3;
        TMenuItem *N3;
        TMenuItem *N6;
        TMenuItem *N15;
    TPopupMenu *PopupMenu4;
        TMenuItem *mnuPersonalX;
        TMenuItem *MenuItem2;
        TMenuItem *MenuItem3;
        TMenuItem *MenuItem4;
        TMenuItem *MenuItem5;
        TMenuItem *MenuItem6;
        TMenuItem *MenuItem7;
    TPopupMenu *PopupMenu2;
    TMenuItem *N16;
    TMenuItem *N17;
    TMenuItem *N18;
    TMenuItem *mnuInitAllocAll;
    TMenuItem *mnuInitAllocExcFixed;
    TMenuItem *mnuScheduleInfo;
    TMenuItem *mnuMoveLessonSet;
    TMenuItem *mnuSubjectInfo;
    TMenuItem *N2;
    TMenuItem *N5;
    TMenuItem *N19;
    TMenuItem *N20;
    TMenuItem *N21;
    TMenuItem *N22;
	void __fastcall pntTeacherPaint(TObject* Sender);
	void __fastcall mnuToolsClick(TObject* Sender);
	void __fastcall pntVTimesPaint(TObject* Sender);
	void __fastcall pntHTimesPaint(TObject* Sender);
	void __fastcall pntTeacherMouseMove(TObject* Sender, TShiftState Shift, int X, int Y);
	void __fastcall mnuOpenClick(TObject* Sender);
	void __fastcall mnuSaveClick(TObject* Sender);
	void __fastcall mnuSaveAsClick(TObject* Sender);
	void __fastcall mnuPersonalClick(TObject* Sender);
	void __fastcall mnuClassClick(TObject* Sender);
	void __fastcall mnuPrnTeachersClick(TObject* Sender);
	void __fastcall mnuPrnClassesClick(TObject* Sender);
	void __fastcall mnuSchoolInfoClick(TObject* Sender);
	void __fastcall mnuTeacherInfoClick(TObject* Sender);
	void __fastcall N8Click(TObject* Sender);
	void __fastcall hsbTeacherChange(TObject* Sender);
	void __fastcall Panel1Resize(TObject* Sender);
	void __fastcall btnDropdownClick(TObject* Sender);
	void __fastcall mnuCloseClick(TObject* Sender);
	void __fastcall mnuConfigClick(TObject* Sender);
	void __fastcall mnuPersonalXClick(TObject* Sender);
	void __fastcall tabWeekChange(TObject* Sender);
	void __fastcall mnuPrnTeacherCSVClick(TObject* Sender);
	void __fastcall mnuPrnClassesCSVClick(TObject* Sender);
	void __fastcall mnuPrnSchedulesClick(TObject* Sender);
        void __fastcall FormCanResize(TObject *Sender, int &NewWidth,
          int &NewHeight, bool &Resize);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall pntTeacherMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall tabYearChange(TObject *Sender, int NewTab,
          bool &AllowChange);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall mnuInitAllocAllClick(TObject *Sender);
    void __fastcall mnuScheduleInfoClick(TObject *Sender);
    void __fastcall mnuMoveLessonSetClick(TObject *Sender);
    void __fastcall mnuSubjectInfoClick(TObject *Sender);
    void __fastcall N2Click(TObject *Sender);
    void __fastcall N5Click(TObject *Sender);
    void __fastcall N19Click(TObject *Sender);
    void __fastcall N20Click(TObject *Sender);
    void __fastcall N21Click(TObject *Sender);
    void __fastcall N22Click(TObject *Sender);

public:
        __fastcall TfrmMain(TComponent* Owner);

private:
    String curFileName;
    int  iCurWork;

	void __fastcall SetTeacherCount(int cnt);
	void __fastcall RecalcScrollBar(void);
	void __fastcall RefreshScreen(void);
	void __fastcall EnableItems(void);
	void __fastcall DisableItems(void);
};


extern PACKAGE TfrmMain* frmMain;


#endif	// f_main
