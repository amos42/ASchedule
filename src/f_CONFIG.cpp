//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_config.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmConfig* frmConfig;

#include "Global.h"

//---------------------------------------------------------------------------
__fastcall TfrmConfig::TfrmConfig(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TfrmConfig::FormShow(TObject* Sender)
{
    edtMaxChangeCount->Text = IntToStr(g_Config.MaxChangeCount);

    colCellText->Selected = g_Config.Colors.CellText;
    colCellBackground->Selected = g_Config.Colors.CellBackground;
    colGridLine->Selected = g_Config.Colors.GridLine;
    colFixedCell->Selected = g_Config.Colors.FixedCell;
    colFocusCell->Selected = g_Config.Colors.FocusCell;
    colGrayCell->Selected = g_Config.Colors.GrayCell;
    colLunchTime->Selected = g_Config.Colors.LunchTime;
    colSpecialLesson->Selected = g_Config.Colors.SpecialLesson;
    colMoveLesson->Selected = g_Config.Colors.MoveLesson;
}

void __fastcall TfrmConfig::btnOkClick(TObject* Sender)
{
    g_Config.MaxChangeCount = StrToInt(edtMaxChangeCount->Text);
    if( g_Config.MaxChangeCount < 1 ) g_Config.MaxChangeCount = 1;
    if( g_Config.MaxChangeCount > 50 ) g_Config.MaxChangeCount = 50;

    g_Config.Colors.CellText = colCellText->Selected;
    g_Config.Colors.CellBackground = colCellBackground->Selected;
    g_Config.Colors.GridLine = colGridLine->Selected;
    g_Config.Colors.FixedCell = colFixedCell->Selected;
    g_Config.Colors.FocusCell = colFocusCell->Selected;
    g_Config.Colors.GrayCell = colGrayCell->Selected;
    g_Config.Colors.LunchTime = colLunchTime->Selected;
    g_Config.Colors.SpecialLesson = colSpecialLesson->Selected;
    g_Config.Colors.MoveLesson = colMoveLesson->Selected;

    SaveConfigData();
}
