//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_cnv.h"
#include "scd_files.h"
#include "scd_files_old.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
    if( OpenDialog1->Execute() ){
      edtSTC_SRC->Text = OpenDialog1->FileName;
      edtSTC_DES->Text = OpenDialog1->FileName;
      edtSSB_DES->Text = ChangeFileExt( OpenDialog1->FileName, ".SSB" );
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
    if( OpenDialog2->Execute() ){
      edtSCD_SRC->Text = OpenDialog2->FileName;
      edtSCD_DES->Text = OpenDialog2->FileName;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    LoadTeacherData_old( edtSTC_SRC->Text.c_str() );

    SaveSubjectData( edtSTC_DES->Text.c_str() );
    SaveTeacherData( edtSSB_DES->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    LoadScheduleData_old( edtSCD_SRC->Text.c_str() );

    SaveScheduleData( edtSCD_DES->Text.c_str() );
}
//---------------------------------------------------------------------------
