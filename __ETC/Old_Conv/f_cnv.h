//---------------------------------------------------------------------------

#ifndef f_cnvH
#define f_cnvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TEdit *edtSTC_SRC;
    TEdit *edtSCD_SRC;
    TButton *Button1;
    TButton *Button2;
    TLabel *Label1;
    TLabel *Label2;
    TOpenDialog *OpenDialog1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TEdit *edtSCD_DES;
    TEdit *edtSTC_DES;
    TEdit *edtSSB_DES;
    TOpenDialog *OpenDialog2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
