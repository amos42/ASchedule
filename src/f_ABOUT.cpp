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
             "�ð�ǥ �ۼ� Ver 1.0\n"
             "Programming by �ְ��\n"
             "�����ֽź�: ������/������ ������";
}
//---------------------------------------------------------------------------

