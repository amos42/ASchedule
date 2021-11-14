//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
    ProductName->Caption =
             "시간표 작성 Ver 1.0\n"
             "Programming by 주경민\n"
             "도움주신분: 엄정한/정영태 선생님";
}
//---------------------------------------------------------------------------

