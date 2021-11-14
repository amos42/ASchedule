unit f_SINIT;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, Spin, Grids, ExtCtrls, Buttons, StdCtrls, DB, DBTables,
  TabNotBk, ComCtrls;

type
  TfrmSInit = class(TForm)
    BitBtn1: TBitBtn;
    tabYear: TTabbedNotebook;
    Panel1: TPanel;
    grdSchedule3: TStringGrid;
    grdSchedule1: TStringGrid;
    grdSchedule2: TStringGrid;
    spnWeek1: TSpinButton;
    spnWeek2: TSpinButton;
    spnWeek3: TSpinButton;
    spnWeek4: TSpinButton;
    spnWeek5: TSpinButton;
    spnWeek6: TSpinButton;
    edtCC1: TSpinEdit;
    edtCC2: TSpinEdit;
    edtCC3: TSpinEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    pnlTotal: TPanel;
    Label4: TLabel;
    spnLunchTime: TSpinEdit;
    Label5: TLabel;
    Label6: TLabel;
    GroupBox1: TGroupBox;
    btnSpcAdd: TSpeedButton;
    btnSpcDel: TSpeedButton;
    btnSpcEdit: TSpeedButton;
    lvSpecial: TListView;
    procedure spnWeekDownClick(Sender: TObject);
    procedure spnWeekUpClick(Sender: TObject);
    procedure grdScheduleClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure tabYearChange(Sender: TObject; NewTab: Integer;
      var AllowChange: Boolean);
    procedure edtCC1Change(Sender: TObject);
    procedure edtCC2Change(Sender: TObject);
    procedure edtCC3Change(Sender: TObject);
    procedure grdSchedule1DrawCell(Sender: TObject; ACol, ARow: Integer;
      Rect: TRect; State: TGridDrawState);
    procedure FormShow(Sender: TObject);
    procedure spnLunchTimeChange(Sender: TObject);
    procedure btnSpcAddClick(Sender: TObject);
    procedure btnSpcDelClick(Sender: TObject);
    procedure btnSpcEditClick(Sender: TObject);
    procedure lvSpecialMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
    grdSchedules: array[1..3] of TStringGrid;
    procedure RecalcTimes();

  public
    { Public declarations }
  end;

var
  frmSInit: TfrmSInit;

implementation

uses Global, A_Util;

{$R *.DFM}

var
  grdSchedule: TStringGrid;


procedure TfrmSInit.RecalcTimes();
var
    i, j, k: Longint;
    Total: Longint;

begin
    Total := 0;

    for i := 1 to 3 do begin
      k := 0;

      for j := MON to SAT do begin
        k := k + gSchool.WeekLimit[i,j];
      end;
      for j := 1 to gSchool.SPC_Count do begin
        if (gSchool.SPC[j].Years and SPC_CLASSES[i]) <> 0 then
          k := k - 1;
      end;

      k := k * gSchool.ClassCount[i];

      Total := Total + k;
    end;

    pnlTotal.Caption := IntToStr(Total);
end;


procedure TfrmSInit.FormCreate(Sender: TObject);
var
  i, j, k: integer;

begin
  for i := 1 to 3 do begin
    case i of
      1 : grdSchedules[i] := grdSchedule1;
      2 : grdSchedules[i] := grdSchedule2;
      3 : grdSchedules[i] := grdSchedule3;
    end;
    grdSchedule := grdSchedules[i];
    
    for j := 1 to 8 do grdSchedule.Cells[0, j] := IntToStr(j);

    for j := MON to SAT do begin
      grdSchedule.Cells[j, 0] := WeekStr[j];
      for k := 1 to gSchool.WeekLimit[i, j] do
        grdSchedule.Cells[j ,k] := '';
      for k := gSchool.WeekLimit[i, j] + 1 to 8 do
        grdSchedule.Cells[j, k] := '==';
    end;
  end;

  edtCC1.Value := gSchool.ClassCount[1];
  edtCC2.Value := gSchool.ClassCount[2];
  edtCC3.Value := gSchool.ClassCount[3];

  grdSchedule := grdSchedule1;
end;


procedure TfrmSInit.FormShow(Sender: TObject);
var
  i, j, k: integer;
  li: TListItem;

begin
  lvSpecial.Items.Clear();
  for i := 1 to gSchool.SPC_Count do begin
    li := lvSpecial.Items.Add();
    li.Caption := gSchool.SPC[i].Name;
    if (gSchool.SPC[i].Years and SPC_CLASS1) <> 0 then
      li.SubItems.Add('√')
    else
      li.SubItems.Add('');
    if (gSchool.SPC[i].Years and SPC_CLASS2) <> 0 then
      li.SubItems.Add('√')
    else
      li.SubItems.Add('');
    if (gSchool.SPC[i].Years and SPC_CLASS3) <> 0 then
      li.SubItems.Add('√')
    else
      li.SubItems.Add('');
  end;

  for i := 1 to 3 do begin
    for j := 1 to 8 do grdSchedules[i].Cells[0, j] := IntToStr(j);

    for j := MON to SAT do begin
      grdSchedules[i].Cells[j, 0] := WeekStr[j];
      for k := 1 to gSchool.WeekLimit[i, j] do
        grdSchedules[i].Cells[j ,k] := '';
      for k := gSchool.WeekLimit[i, j] + 1 to 8 do
        grdSchedules[i].Cells[j, k] := '==';
    end;

    for j := 1 to gSchool.SPC_Count do begin
      if (gSchool.SPC[j].Years and SPC_CLASSES[i]) <> 0 then
        grdSchedules[i].Cells[ gSchool.SPC[j].Pos[i].w, gSchool.SPC[j].Pos[i].t ] := gSchool.SPC[j].Name;
    end;
  end;

  edtCC1.Value := gSchool.ClassCount[1];
  edtCC2.Value := gSchool.ClassCount[2];
  edtCC3.Value := gSchool.ClassCount[3];

  spnLunchTime.Value := gSchool.LunchTime;

  grdSchedule := grdSchedule1;

  RecalcTimes();
end;


procedure TfrmSInit.grdSchedule1DrawCell(Sender: TObject; ACol,
  ARow: Integer; Rect: TRect; State: TGridDrawState);
var
    cnv: TCanvas;
    i, j, k: integer;

begin
    if ACol <= 0 then Exit;

    i := tabYear.PageIndex + 1;
    cnv := TStringGrid(Sender).Canvas;

    if ARow > gSchool.WeekLimit[i, ACol] then begin
      FillRect( cnv.Handle, Rect, GetStockObject(GRAY_BRUSH) );
    end;
end;

procedure TfrmSInit.spnWeekDownClick(Sender: TObject);
var
  i, j, k: integer;

begin
  i := tabYear.PageIndex + 1;
  if      Sender = spnWeek1 then j := MON
  else if Sender = spnWeek2 then j := TUE
  else if Sender = spnWeek3 then j := WED
  else if Sender = spnWeek4 then j := THU
  else if Sender = spnWeek5 then j := FRI
  else if Sender = spnWeek6 then j := SAT;

  inc( gSchool.WeekLimit[i, j] );
  if gSchool.WeekLimit[i, j] > 8 then
    gSchool.WeekLimit[i, j] := 8
  else
    grdSchedule.Cells[j, gSchool.WeekLimit[i, j]] := '';

  RecalcTimes();
end;

procedure TfrmSInit.spnWeekUpClick(Sender: TObject);
var
  i, j, k, l: integer;

begin
  i := tabYear.PageIndex + 1;
  if      Sender = spnWeek1 then j := MON
  else if Sender = spnWeek2 then j := TUE
  else if Sender = spnWeek3 then j := WED
  else if Sender = spnWeek4 then j := THU
  else if Sender = spnWeek5 then j := FRI
  else if Sender = spnWeek6 then j := SAT;

  dec( gSchool.WeekLimit[i, j] );
  if gSchool.WeekLimit[i, j] < 0 then
    gSchool.WeekLimit[i, j] := 0
  else begin
    for l := 1 to gSchool.SPC_Count do begin
      if (gSchool.SPC[l].Pos[i].w = j) and (gSchool.SPC[l].Pos[i].t = k) then begin
        dec( gSchool.SPC[l].Pos[i].t );
      end;
    end;
    grdSchedule.Cells[j, gSchool.WeekLimit[i, j] + 1] := '==';
  end;

  RecalcTimes();
end;

procedure TfrmSInit.grdScheduleClick(Sender: TObject);
var
    i, j, x, y: integer;

begin
    i := tabYear.PageIndex + 1;

    x := grdSchedule.Col;
    y := grdSchedule.Row;

    if grdSchedule.Cells[x, y] = '' then begin
      if lvSpecial.ItemIndex >= 0 then begin
        j := lvSpecial.ItemIndex + 1;

        if (gSchool.SPC[j].Years and SPC_CLASSES[i]) <> 0 then begin
          grdSchedule.Cells[gSchool.SPC[j].Pos[i].w, gSchool.SPC[j].Pos[i].t] := '';
          grdSchedule.Cells[x, y] := gSchool.SPC[j].Name;
          gSchool.SPC[j].Pos[i].w := x;
          gSchool.SPC[j].Pos[i].t := y;

          RecalcTimes();
        end;
      end;
    end;
end;

procedure TfrmSInit.BitBtn1Click(Sender: TObject);
begin
    Close();
end;

procedure TfrmSInit.tabYearChange(Sender: TObject; NewTab: Integer;
  var AllowChange: Boolean);
begin
  grdSchedule := grdSchedules[NewTab+1];
end;

procedure TfrmSInit.edtCC1Change(Sender: TObject);
begin
    if edtCC1.Text <> '' then
      gSchool.ClassCount[1] := edtCC1.Value
    else
      gSchool.ClassCount[1] := 0;
    RecalcTimes();
end;

procedure TfrmSInit.edtCC2Change(Sender: TObject);
begin
    if edtCC2.Text <> '' then
      gSchool.ClassCount[2] := edtCC2.Value
    else
      gSchool.ClassCount[2] := 0;
    RecalcTimes();
end;

procedure TfrmSInit.edtCC3Change(Sender: TObject);
begin
    if edtCC3.Text <> '' then
      gSchool.ClassCount[3] := edtCC3.Value
    else
      gSchool.ClassCount[3] := 0;
    RecalcTimes();
end;

procedure TfrmSInit.spnLunchTimeChange(Sender: TObject);
begin
    gSchool.LunchTime := spnLunchTime.Value;
    if gSchool.LunchTime > 8 then gSchool.LunchTime := 4;
    if gSchool.LunchTime < 1 then gSchool.LunchTime := 4;
end;

procedure TfrmSInit.btnSpcAddClick(Sender: TObject);
var
    str: String;
    i: integer;
    li: TListItem;
begin
    if gSchool.SPC_Count >= MAX_SPC_COUNT then Exit;

    str := InputBox2('', '특별 수업 명칭을 입력하세요.', '');
    if str <> '' then begin
      if Length(str) > 3 then begin
        MessageDlg('글자수는 영문3자로 제한됩니다.', mtWarning, [mbOk], 0 );
        Exit;
      end;

      li := lvSpecial.Items.Add();
      li.Caption := str;
      li.SubItems.Add('√');
      li.SubItems.Add('√');
      li.SubItems.Add('√');

      i := lvSpecial.Items.Count;
      gSchool.SPC_Count := i;
      StrPCopy( gSchool.SPC[i].Name, str );
      gSchool.SPC[i].Years := SPC_CLASS1 or SPC_CLASS2 or SPC_CLASS3;
      gSchool.SPC[i].Pos[1].w := 0; gSchool.SPC[i].Pos[1].t := 0;
      gSchool.SPC[i].Pos[2].w := 0; gSchool.SPC[i].Pos[2].t := 0;
      gSchool.SPC[i].Pos[3].w := 0; gSchool.SPC[i].Pos[3].t := 0;

      RecalcTimes();
    end;
end;

procedure TfrmSInit.btnSpcDelClick(Sender: TObject);
var
    i, j: integer;
begin
    if MessageDlg2( '정말 삭제하시겠습니까?', '삭제 확인',
                   mtConfirmation, [mbYes, mbNo], 0 ) <> mrYes then begin
      Exit;
    end;

    i := lvSpecial.ItemIndex;
    if i >= 0 then begin
      lvSpecial.Items.Delete( i );
      i := i + 1;

      if (gSchool.SPC[i].Years and SPC_CLASS1) <> 0 then
        grdSchedule1.Cells[ gSchool.SPC[i].Pos[1].w, gSchool.SPC[i].Pos[1].t ] := '';
      if (gSchool.SPC[i].Years and SPC_CLASS2) <> 0 then
        grdSchedule2.Cells[ gSchool.SPC[i].Pos[2].w, gSchool.SPC[i].Pos[2].t ] := '';
      if (gSchool.SPC[i].Years and SPC_CLASS3) <> 0 then
        grdSchedule3.Cells[ gSchool.SPC[i].Pos[3].w, gSchool.SPC[i].Pos[3].t ] := '';

      gSchool.SPC_Count := lvSpecial.Items.Count;
      if gSchool.SPC_Count > 0 then begin
        for j := i to gSchool.SPC_Count do begin
          gSchool.SPC[j] := gSchool.SPC[j+1];
        end;
      end;

      RecalcTimes();
    end;
end;

procedure TfrmSInit.btnSpcEditClick(Sender: TObject);
var
    str: String;
    i, j: integer;
begin
    i := lvSpecial.ItemIndex;
    if i < 0 then Exit;

    str := lvSpecial.Items[i].Caption;
    str := InputBox2('', '특별 수업 명칭을 입력하세요.', str);
    if str <> '' then begin
      if Length(str) > 3 then begin
        MessageDlg('글자수는 영문3자로 제한됩니다.', mtWarning, [mbOk], 0 );
        Exit;
      end;

      StrPCopy( gSchool.SPC[i+1].Name, str );

      lvSpecial.Items[i].Caption := str;
      i := i + 1;
      grdSchedule1.Cells[ gSchool.SPC[i].Pos[1].w, gSchool.SPC[i].Pos[1].t ] := str;
      grdSchedule2.Cells[ gSchool.SPC[i].Pos[2].w, gSchool.SPC[i].Pos[2].t ] := str;
      grdSchedule3.Cells[ gSchool.SPC[i].Pos[3].w, gSchool.SPC[i].Pos[3].t ] := str;
    end;
end;

procedure TfrmSInit.lvSpecialMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
    li: TListItem;
    xx, ww: Longint;
    i, si: integer;

begin
    li := lvSpecial.GetItemAt(X,Y);
    if li = nil then exit;

    si := -1;
    xx := 2;
    for i := 0 to lvSpecial.Columns.Count-1 do begin
      ww := lvSpecial.Columns.Items[i].Width;
      if (X > xx) and (X < xx+ww) then begin
        si := i;
        break;
      end;
      inc( xx, ww );
    end;

    i := li.Index + 1;
    if (si >= 1) and (si <= 3) then begin
      if (gSchool.SPC[i].Years and SPC_CLASSES[si]) <> 0 then begin
        gSchool.SPC[i].Years := gSchool.SPC[i].Years and (not SPC_CLASSES[si]);
        li.SubItems[si-1] := '';
        grdSchedules[si].Cells[gSchool.SPC[i].Pos[si].w, gSchool.SPC[i].Pos[si].t] := '';
      end else begin
        gSchool.SPC[i].Years := gSchool.SPC[i].Years or SPC_CLASSES[si];
        gSchool.SPC[i].Pos[si].w := 0; gSchool.SPC[i].Pos[si].t := 0;
        li.SubItems[si-1] := '√';
      end;

      RecalcTimes();
    end;
end;

end.
