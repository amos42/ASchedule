//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "A_Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <Buttons.hpp>
#ifndef max
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

/*
extern PACKAGE AnsiString DecodeStr(bool opt, AnsiString truestr, AnsiString falsestr);
extern PACKAGE int DecodeVal(bool opt, int trueval, int falseval);
extern PACKAGE int MessageDlg2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx);
extern PACKAGE int MessageDlgPos2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx, int X, int Y);
extern PACKAGE int MessageDlgPosHelp2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx, int X, int Y, const AnsiString HelpFileName);
extern PACKAGE bool InputQuery2(const AnsiString ACaption, const AnsiString APrompt, AnsiString &Value);
extern PACKAGE AnsiString InputBox2(const AnsiString ACaption, const AnsiString APrompt, const AnsiString ADefault);
*/

/************************
  조건에 따라 문자열 리턴
*************************/
AnsiString DecodeStr(bool opt, AnsiString truestr, AnsiString falsestr)
{
    if( opt ) return truestr; else return falsestr;
}


/************************
  조건에 따라 정수값 리턴
*************************/
int DecodeVal(bool opt, int trueval, int falseval)
{
    if( opt ) return trueval; else return falseval;
}


/************************
  파일 복사
*************************/
void CopyFile( String SrcFile, String DesFile )
{
  int i;
  int sf, df;
  int fs;
  BYTE TempData;

  sf = FileOpen( SrcFile, fmOpenRead );
  df = FileCreate( DesFile );
  fs = FileSeek( sf, 0, 2 );
  FileSeek( sf, 0, 0 );

  for( i = 0; i < fs; i++ ) {
    FileRead( sf, &TempData, 1 );
    FileWrite( df, &TempData, 1 );
  }

  FileClose( sf );
  FileClose( df );
}





TSize GetAveCharSize(TCanvas *Canvas)
{
    int i;
    char Buffer[52];
    TSize Result;

    for( i = 0; i < 26; i++ ) Buffer[i] = i + 'A';
    for( i = 0; i < 26; i++ ) Buffer[i+26] = i + 'a';
    GetTextExtentPoint(Canvas->Handle, Buffer, 52, &Result);

    Result.cx /= 52;

    return Result;
}


/*
class TMessageForm : public TForm
{
  private:
    void __fastcall HelpButtonClick(TObject *Sender);

  public:
    virtual __fastcall TMessageForm(TComponent *AOwner);// reintroduce;
    virtual __fastcall ~TMessageForm();
};

__fastcall TMessageForm::TMessageForm(TComponent *AOwner) : TForm(AOwner)
{
  TNonClientMetrics NonClientMetrics;

//  TForm::TForm(AOwner);
//  inherited->CreateNew(AOwner);

  NonClientMetrics.cbSize = sizeof(NonClientMetrics);
  if( SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NonClientMetrics, 0) )
    Font->Handle = CreateFontIndirect(&NonClientMetrics.lfMessageFont);
}

__fastcall TMessageForm::~TMessageForm()
{
}

void __fastcall TMessageForm::HelpButtonClick(TObject *Sender)
{
  Application->HelpContext(HelpContext);
}
*/

/*
void *Captions[MsgDlgType] = {
     &SMsgDlgWarning, &SMsgDlgError, &SMsgDlgInformation, &SMsgDlgConfirm,
     NULL
};
*/

char *IconIDs[/*TMsgDlgType*/5] = {
     IDI_EXCLAMATION, IDI_HAND,
     IDI_ASTERISK, IDI_QUESTION,
     NULL
};

String ButtonNames[/*TMsgDlgBtn*/11] = {
    "Yes", "No", "OK", "Cancel", "Abort", "Retry", "Ignore", "All", "NoToAll",
    "YesToAll", "Help"
};


TBitBtnKind ButtonKinds[/*TMsgDlgBtn*/ 11] = {
    bkYes, bkNo, bkOK, bkCancel, bkAbort, bkRetry, bkIgnore, bkAll, bkNo,
    bkAll, bkHelp
};

String ButtonCaptions[/*TMsgDlgBtn*/11] = {
    "예", "아니요", "확인", "취소", "중지", "다시", "무시", "모두", "모두 아니오",
    "모두 예", "도움말"
};

int ModalResults[/*TMsgDlgBtn*/11] = {
    mrYes, mrNo, mrOk, mrCancel, mrAbort, mrRetry, mrIgnore, mrAll, mrNoToAll,
    mrYesToAll, 0
};

int ButtonWidths[/*TMsgDlgBtn*/11];  // initialized; zero

/************************

*************************/
TForm *CreateMessageDialog2(const String Msg, const String ACaption, TMsgDlgType DlgType, TMsgDlgButtons Buttons )
{
  const mcHorzMargin = 8;
  const mcVertMargin = 8;
  const mcHorzSpacing = 10;
  const mcVertSpacing = 10;
  const mcButtonWidth = 50;
  const mcButtonHeight = 16;
  const mcButtonSpacing = 4;

  TSize DialogUnits;
  int HorzMargin, VertMargin, HorzSpacing, VertSpacing, ButtonWidth,
  ButtonHeight, ButtonSpacing, ButtonCount, ButtonGroupWidth,
  IconTextWidth, IconTextHeight, X, ALeft;
//  TMsgDlgBtn B, DefaultButton, CancelButton;
  TMsgDlgBtn DefaultButton, CancelButton; int B;
  char *IconID;
  TRect TextRect;
  TForm *Result;

//  Result = new TMessageForm(Application);
  Result = new TForm(Application);
//  TNonClientMetrics NonClientMetrics;
//  NonClientMetrics.cbSize = sizeof(NonClientMetrics);
//  if( SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NonClientMetrics, 0) )
//    Result->Font->Handle = CreateFontIndirect(&NonClientMetrics.lfMessageFont);
  Result->Font->Handle = GetStockObject(DEFAULT_GUI_FONT);

  Result->BiDiMode = Application->BiDiMode;
  Result->BorderStyle = bsDialog;
  Result->Canvas->Font = Result->Font;
  DialogUnits = GetAveCharSize(Result->Canvas);
  Result->Caption     = ACaption;
    HorzMargin = MulDiv(mcHorzMargin, DialogUnits.cx, 4);
    VertMargin = MulDiv(mcVertMargin, DialogUnits.cy, 8);
    HorzSpacing = MulDiv(mcHorzSpacing, DialogUnits.cx, 4);
    VertSpacing = MulDiv(mcVertSpacing, DialogUnits.cy, 8);
    ButtonWidth = MulDiv(mcButtonWidth, DialogUnits.cx, 4);

    ButtonCount = 0;
    for( B = 0; B < 11; B++ ) {
      if( Buttons.Contains( (TMsgDlgBtn)B ) ){
        ButtonCount++;
        if( ButtonWidths[B] == 0 ){
          TextRect = Rect(0,0,0,0);
          DrawText( Result->Canvas->Handle,
            Result->Caption.c_str(), -1,
            &TextRect, DT_CALCRECT | DT_LEFT | DT_SINGLELINE |
            Result->DrawTextBiDiModeFlagsReadingOnly() );
          ButtonWidths[B] = TextRect.Right - TextRect.Left + 8;
        }
        if( ButtonWidths[B] > ButtonWidth )
          ButtonWidth = ButtonWidths[B];
      }
    }
    ButtonHeight = MulDiv(mcButtonHeight, DialogUnits.cy, 8);
    ButtonSpacing = MulDiv(mcButtonSpacing, DialogUnits.cx, 4);
    SetRect(&TextRect, 0, 0, Screen->Width / 2, 0);
    DrawText(Result->Canvas->Handle, Msg.c_str(), Msg.Length(), &TextRect,
      DT_EXPANDTABS | DT_CALCRECT | DT_WORDBREAK |
      Result->DrawTextBiDiModeFlagsReadingOnly() );
    IconID = IconIDs[DlgType];
    IconTextWidth = TextRect.Right;
    IconTextHeight = TextRect.Bottom;
    if( IconID != NULL )
    {
      IconTextWidth += 32 + HorzSpacing;
      if( IconTextHeight < 32 ) IconTextHeight = 32;
    }
//    ButtonCount = 0;
//    for( B = 0; B < 11; B++ )
//      if( Buttons.Contains((TMsgDlgBtn)B) ) ButtonCount++;
    ButtonGroupWidth = 0;
    if( ButtonCount != 0 )
      ButtonGroupWidth = ButtonWidth * ButtonCount +
        ButtonSpacing * (ButtonCount - 1);
    Result->ClientWidth = max(IconTextWidth, ButtonGroupWidth) + HorzMargin * 2;
    Result->ClientHeight = IconTextHeight + ButtonHeight + VertSpacing +
      VertMargin * 2;
    Result->Left = (Screen->Width / 2) - (Result->Width / 2);
    Result->Top = (Screen->Height / 2) - (Result->Height / 2);

    if( IconID != NULL ){
      TImage *image = new TImage(Result);
      image->Name = "Image";
      image->Parent = Result;
      image->Picture->Icon->Handle = LoadIcon(0, IconID);
      image->SetBounds(HorzMargin, VertMargin, 32, 32);
    }

    {
      TLabel *lbl = new TLabel(Result);
      lbl->Name = "Message";
      lbl->Parent = Result;
      lbl->WordWrap = True;
      lbl->Caption = Msg;
      lbl->BoundsRect = TextRect;
      lbl->BiDiMode = Result->BiDiMode;
      ALeft = IconTextWidth - TextRect.Right + HorzMargin;
      if( Result->UseRightToLeftAlignment() )
        ALeft = Result->ClientWidth - ALeft - Result->Width;
      lbl->SetBounds(ALeft, VertMargin,
        TextRect.Right, TextRect.Bottom);
    }
    if( Buttons.Contains(mbOK) ) DefaultButton = mbOK; else
      if( Buttons.Contains(mbYes) )DefaultButton = mbYes; else
        DefaultButton = mbRetry;
    if( Buttons.Contains(mbCancel) )CancelButton = mbCancel; else
      if( Buttons.Contains(mbNo)  )CancelButton = mbNo; else
        CancelButton = mbOK;
    X = (Result->ClientWidth - ButtonGroupWidth) / 2;
    for( B = 0; B < 11; B++ )
      if( Buttons.Contains((TMsgDlgBtn)B) ){
        TBitBtn *btn = new TBitBtn(Result);
        btn->Name = ButtonNames[B];
        btn->Parent = Result;
        btn->Kind = ButtonKinds[B];
        btn->Caption = ButtonCaptions[B];
        btn->ModalResult = ModalResults[B];
        if( B == DefaultButton ) btn->Default = True;
        if( B == CancelButton ) btn->Cancel = True;
        btn->SetBounds(X, IconTextHeight + VertMargin + VertSpacing,
            ButtonWidth, ButtonHeight);
        X += ButtonWidth + ButtonSpacing;
//        if( B == mbHelp )
//          btn->OnClick = dynamic_cast<TMessageForm *>(Result)->HelpButtonClick;
      }
//  }

  return Result;
}


/************************

*************************/
int MessageDlg2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx)
{
  return MessageDlgPosHelp2(Msg, ACaption, DlgType, Buttons, HelpCtx, -1, -1, "");
}


/************************

*************************/
int MessageDlgPos2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx, int X, int Y)
{
  return MessageDlgPosHelp2(Msg, ACaption, DlgType, Buttons, HelpCtx, X, Y, "");
}


/************************

*************************/
int MessageDlgPosHelp2(const AnsiString Msg, const AnsiString ACaption, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx, int X, int Y, const AnsiString HelpFileName)
{
  TForm *form;
  int r = mrNone;

  form = CreateMessageDialog2(Msg, ACaption, DlgType, Buttons);
//  form = CreateMessageDialog(Msg, DlgType, Buttons);

  __try {
      form->HelpContext = HelpCtx;
      form->HelpFile = HelpFileName;
      if( X >= 0 ) form->Left = X;
      if( Y >= 0 ) form->Top = Y;
      if( (Y < 0) && (X < 0) ) form->Position = poScreenCenter;
      r = form->ShowModal();
  } __finally {
      delete form;
  }

  return r;
}


/************************
  문자열을 입력받는다.
*************************/
bool InputQuery2(const AnsiString ACaption, const AnsiString APrompt, AnsiString &Value)
{
  TForm *Form;
  TLabel *Prompt;
  TEdit *Edit;
  TBitBtn *Button;
  TSize DialogUnits;
  int ButtonTop, ButtonWidth, ButtonHeight;
  bool Result;

  Result = False;
  Form = new TForm(Application);
  __try {
      Form->Font->Name = "굴림";
      Form->Font->Size = 9;

      Form->Canvas->Font = Form->Font;
      DialogUnits = GetAveCharSize(Form->Canvas);
      Form->BorderStyle = bsDialog;
      Form->Caption = ACaption;
      Form->ClientWidth = MulDiv(180, DialogUnits.cx, 4);
      Form->ClientHeight = MulDiv(65, DialogUnits.cy, 8);
      Form->Position = poScreenCenter;

      Prompt = new TLabel(Form);
      {
        Prompt->Parent = Form;
        Prompt->AutoSize = True;
        Prompt->Left = MulDiv(8, DialogUnits.cx, 4);
        Prompt->Top = MulDiv(8, DialogUnits.cy, 8);
        Prompt->Caption = APrompt;
      }
      Edit = new TEdit(Form);
      {
        Edit->Parent = Form;
        Edit->Left = Prompt->Left;
        Edit->Top = MulDiv(19, DialogUnits.cy, 8);
        Edit->Width = MulDiv(164, DialogUnits.cx, 4);
        Edit->MaxLength = 255;
        Edit->Text = Value;
        Edit->SelectAll();
      }
      ButtonTop = MulDiv(41, DialogUnits.cy, 8);
      ButtonWidth = MulDiv(50, DialogUnits.cx, 4);
      ButtonHeight = MulDiv(14, DialogUnits.cy, 7);
      Button = new TBitBtn(Form);
      {
        Button->Parent = Form;
        Button->Kind = bkOK;
        Button->Caption = "확인"; // SMsgDlgOK;
        Button->ModalResult = mrOk;
        Button->Default = True;
        Button->SetBounds(MulDiv(38, DialogUnits.cx, 4), ButtonTop, ButtonWidth,
          ButtonHeight);
      }

      Button = new TBitBtn(Form);
      {
        Button->Parent = Form;
        Button->Kind = bkCancel;
        Button->Caption = "취소"; // SMsgDlgCancel;
        Button->ModalResult = mrCancel;
        Button->Cancel = True;
        Button->SetBounds(MulDiv(92, DialogUnits.cx, 4), ButtonTop, ButtonWidth,
          ButtonHeight);
      }
      if( Form->ShowModal() == mrOk ){
        Value = Edit->Text;
        Result = True;
      }
    } __finally {
      delete Form;
    }

    return Result;
}


/************************
  문자열을 입력받는다.
*************************/
AnsiString InputBox2(const AnsiString ACaption, const AnsiString APrompt, const AnsiString ADefault)
{
  AnsiString Result;

  Result = ADefault;
  InputQuery2(ACaption, APrompt, Result);

  return Result;
}

