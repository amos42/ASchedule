// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'A_Util.pas' rev: 6.00

#ifndef A_UtilHPP
#define A_UtilHPP

#include <Dialogs.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString DecodeStr(bool opt, AnsiString truestr, AnsiString falsestr);
extern PACKAGE int DecodeVal(bool opt, int trueval, int falseval);
extern PACKAGE void CopyFile(AnsiString SrcFile, AnsiString DesFile);
extern PACKAGE int MessageDlg2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx);
extern PACKAGE int MessageDlgPos2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx, int X, int Y);
extern PACKAGE int MessageDlgPosHelp2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx, int X, int Y, const AnsiString HelpFileName);
extern PACKAGE bool InputQuery2(const AnsiString ACaption, const AnsiString APrompt, AnsiString &Value);
extern PACKAGE AnsiString InputBox2(const AnsiString ACaption, const AnsiString APrompt, const AnsiString ADefault);

//-- end unit ----------------------------------------------------------------
#endif	// A_Util
