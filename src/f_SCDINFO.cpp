//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_SCDINFO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmScheduleInfo *frmScheduleInfo;

#include "Global.h"
#include "A_Util.h"

//---------------------------------------------------------------------------
__fastcall TfrmScheduleInfo::TfrmScheduleInfo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmScheduleInfo::FormShow(TObject *Sender)
{
    edtScheduleName->Text = g_ScheduleInfo.ScheduleTitle;
    edtAuthorName->Text = g_ScheduleInfo.AuthorName;
    mskAuthorDate->Text = g_ScheduleInfo.AuthorDate;
    memMemo->Text = g_ScheduleInfo.Memo;
}
//---------------------------------------------------------------------------

void __fastcall TfrmScheduleInfo::btnCloseClick(TObject *Sender)
{
    strcpy( g_ScheduleInfo.ScheduleTitle, edtScheduleName->Text.c_str() );
    strcpy( g_ScheduleInfo.AuthorName, edtAuthorName->Text.c_str() );
    strcpy( g_ScheduleInfo.AuthorDate, mskAuthorDate->Text.c_str() );
    strcpy( g_ScheduleInfo.Memo, memMemo->Text.c_str() );

    Close();
}
//---------------------------------------------------------------------------

