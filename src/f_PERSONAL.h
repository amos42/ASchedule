// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'f_PERSONAL.pas' rev: 6.00

#ifndef f_PERSONALHPP
#define f_PERSONALHPP

#include <ToolWin.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <ActnList.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
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

class TfrmPersonal : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
        TPanel *Panel3;
        TPaintBox *pntTeacher;
        TListBox *lstTeacher;
        TPanel *pnlInfo;
        TEdit *edtInfo;
        TToolBar *ToolBar2;
        TToolButton *btnClose;
        TToolButton *ToolButton4;
        TToolButton *btnClass;
        TToolButton *ToolButton10;
        TToolButton *btnTools;
        TPanel *pnlTools;
        TMainMenu *MainMenu1;
        TMenuItem *N5;
        TMenuItem *mnuClose;
        TMenuItem *N3;
        TMenuItem *mnuClass;
        TMenuItem *N7;
        TMenuItem *mnuTools0;
        TMenuItem *mnuTools1;
        TMenuItem *mnuTools2;
        TMenuItem *mnuTools3;
        TMenuItem *mnuTools4;
        TMenuItem *N1;
        TMenuItem *mnuFindMulti;
        TMenuItem *mnuFind4and5;
        TMenuItem *mnuFind3Cont;
        TMenuItem *mnuFindOver5;
        TMenuItem *N2;
        TMenuItem *mnuFindFirst;
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
    TPanel *Panel1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TCheckBox *chkFindFirst;
	void __fastcall pntTeacherPaint(TObject* Sender);
	void __fastcall mnuCloseClick(TObject* Sender);
	void __fastcall pntTeacherMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall lstTeacherClick(TObject* Sender);
	void __fastcall pntTeacherMouseMove(TObject* Sender, TShiftState Shift, int X, int Y);
	void __fastcall mnuFind4and5Click(TObject* Sender);
	void __fastcall mnuFind3ContClick(TObject* Sender);
	void __fastcall mnuFindMultiClick(TObject* Sender);
	void __fastcall mnuFindOver5Click(TObject* Sender);
	void __fastcall mnuClassClick(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall mnuTools(TObject* Sender);
	void __fastcall btnToolsClick(TObject* Sender);
    void __fastcall mnuFindFirstClick(TObject *Sender);
    void __fastcall chkFindFirstClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);

public:
        __fastcall TfrmPersonal(TComponent* Owner);

private:
    int  iCurWork;
    int  DispTeacher;
    bool  mState;
    int  mStartW, mStartN;

public:
    int xxx[50][50];
    int yyy[50][50];
	void RefreshTeachers(void);
	void SetTeacherNo(int idx);
    void RecalcInvalidInfo(void);

};


extern PACKAGE TfrmPersonal* frmPersonal;


#endif	// f_PERSONAL
