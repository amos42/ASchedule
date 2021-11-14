unit f_config;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls, ComCtrls;

type
  TfrmConfig = class(TForm)
    btnOk: TBitBtn;
    btnCancel: TBitBtn;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    GroupBox1: TGroupBox;
    TabSheet2: TTabSheet;
    GroupBox2: TGroupBox;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    GroupBox3: TGroupBox;
    colCellBackground: TColorBox;
    colSpecialCell: TColorBox;
    colFixedCell: TColorBox;
    colFocusCell: TColorBox;
    colCellText: TColorBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    colGrayCell: TColorBox;
    Label6: TLabel;
    colLunchTime: TColorBox;
    Label7: TLabel;
    colGridLine: TColorBox;
    Label8: TLabel;
    edtMaxChangeCount: TLabeledEdit;
    procedure FormShow(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmConfig: TfrmConfig;

implementation

uses Global;

{$R *.dfm}

procedure TfrmConfig.FormShow(Sender: TObject);
begin
    edtMaxChangeCount.Text := IntToStr(gConfig.MaxChangeCount);

    colCellText.Selected := gConfig.Colors.CellText;
    colCellBackground.Selected := gConfig.Colors.CellBackground;
    colGridLine.Selected := gConfig.Colors.GridLine;
    colSpecialCell.Selected := gConfig.Colors.SpecialCell;
    colFixedCell.Selected := gConfig.Colors.FixedCell;
    colFocusCell.Selected := gConfig.Colors.FocusCell;
    colGrayCell.Selected := gConfig.Colors.GrayCell;
    colLunchTime.Selected := gConfig.Colors.LunchTime;
end;

procedure TfrmConfig.btnOkClick(Sender: TObject);
begin
    gConfig.MaxChangeCount := StrToInt(edtMaxChangeCount.Text);
    if gConfig.MaxChangeCount < 1 then gConfig.MaxChangeCount := 1;
    if gConfig.MaxChangeCount > 50 then gConfig.MaxChangeCount := 50;

    gConfig.Colors.CellText := colCellText.Selected;
    gConfig.Colors.CellBackground := colCellBackground.Selected;
    gConfig.Colors.GridLine := colGridLine.Selected;
    gConfig.Colors.SpecialCell := colSpecialCell.Selected;
    gConfig.Colors.FixedCell := colFixedCell.Selected;
    gConfig.Colors.FocusCell := colFocusCell.Selected;
    gConfig.Colors.GrayCell := colGrayCell.Selected;
    gConfig.Colors.LunchTime := colLunchTime.Selected;

    SaveConfigData();
end;

end.
