//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_splash.h"
#include "f_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmSplash *frmSplash;

//---------------------------------------------------------------------------
__fastcall TfrmSplash::TfrmSplash(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmSplash::FormCreate(TObject *Sender)
{
    HRGN rgn;

    rgn = CreateRoundRectRgn( 0, 0, Width, Height, 30, 30 );
    SetWindowRgn( Handle, rgn, TRUE );
    DeleteObject( rgn );
}
//---------------------------------------------------------------------------
void __fastcall TfrmSplash::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = FALSE;
    this->Close();
    this->Free();
}
//---------------------------------------------------------------------------

