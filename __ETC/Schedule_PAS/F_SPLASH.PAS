unit f_splash;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls;

type
  TfrmSplash = class(TForm)
    Image1: TImage;
    Timer1: TTimer;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmSplash: TfrmSplash;

implementation

{$R *.dfm}

procedure TfrmSplash.FormCreate(Sender: TObject);
var
    rgn: HRGN;
begin
    rgn := CreateRoundRectRgn( 0, 0, Width, Height, 30, 30 );
    SetWindowRgn( Self.Handle, rgn, true );
    DeleteObject( rgn );
end;


procedure TfrmSplash.Timer1Timer(Sender: TObject);
begin
    Timer1.Enabled := false;
    Self.Hide();
    Self.Free();
end;


end.
