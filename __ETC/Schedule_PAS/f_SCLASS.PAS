unit f_SCLASS;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, StdCtrls, Buttons,
  Global;

const
  GrdSizeX = 26;
  GrdSizeY = 22;
  GrdRowX = 16;
  GrdColY = 21;

type
  TClasses = record
    SubjectType: byte;
    Subject: string[4];
    TeacherName: string[8];
  end;

  TfrmClass = class(TForm)
    Panel3: TPanel;
    pntTeacher: TPaintBox;
    Panel1: TPanel;
    btnYear1: TSpeedButton;
    btnYear2: TSpeedButton;
    btnYear3: TSpeedButton;
    lstClass: TListBox;
    pnlInfo: TPanel;
    edtInfo: TEdit;
    procedure DispClassData( hDC: HDC; w, n: integer );
    procedure pntTeacherPaint(Sender: TObject);
    procedure btnYear1Click(Sender: TObject);
    procedure btnYear2Click(Sender: TObject);
    procedure btnYear3Click(Sender: TObject);
    procedure lstClassClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure pntTeacherMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
  public
    { Public declarations }
    ViewData: array [MON..SAT, 1..8] of TClasses;
    ViewClass: word;
  end;

var
  frmClass: TfrmClass;

implementation

{$R *.DFM}



(***********************************
  지정된 위치에 클래스 출력
************************************)
procedure TfrmClass.DispClassData( hDC: HDC; w, n: integer );
var
  px, py: integer;
  Rect: TRECT;
  TempType: byte;
  TempStr: string;
  StrData: array[0..255] of char;
  tc: TColor;
  hOldBrush, hNewBrush: HBRUSH;

begin
  px := (w - 1) * (GrdSizeX + 1) + GrdRowX + 2;
  py := (n - 1) * (GrdSizeY + 1) + GrdColY + 2;
  Rect.Top := py;
  Rect.Left := px;
  Rect.Bottom := py + GrdSizeY;
  Rect.Right := px + GrdSizeX;

  TempType := ViewData[w, n].SubjectType;
  TempStr := ViewData[w, n].Subject;

  Case TempType of
    CT_NORMAL  : tc := gConfig.Colors.CellBackground;
    CT_FIXED   : tc := gConfig.Colors.FixedCell;
    CT_SPECIAL : tc := gConfig.Colors.SpecialCell;
    CT_ETC     : tc := gConfig.Colors.GrayCell;
    else         tc := clDkGray;
  end;

  hNewBrush := CreateSolidBrush( tc );
  hOldBrush := SelectObject( hDC, hNewBrush );
  SetBkColor( hDC, tc );

  FillRect( hDC, Rect, hNewBrush );

  if TempStr <> '' then begin
    StrPCopy( StrData, TempStr );
    DrawText( hDC, StrData, lstrlen(StrData), Rect, DT_CENTER or DT_SINGLELINE or DT_VCENTER );
  end;

  SelectObject( hDC, hOldBrush );
  DeleteObject( hNewBrush );
end;


procedure TfrmClass.pntTeacherPaint(Sender: TObject);
var
    pnt: TPaintBox;
    dc: HDC;
    i, j: integer;
    Rect: TRect;
    StrData: array [0..255] of char;
    hOldPen, hNewPen1, hNewPen2: HPEN;
    hOldFont, hSFont: HFONT;

begin
    pnt := TPaintBox(Sender);
    dc := pnt.Canvas.Handle;

    (* 최좌상단 *)
    Rect.Top := 1;
    Rect.Bottom := GrdColY;
    Rect.Left := 1;
    Rect.Right := GrdRowX;
    DrawButtonLine( dc, Rect );
  
    (* 좌측(1~8교시) *)
    Rect.Top := GrdColY + 1 + 1;
    Rect.Bottom := GrdColY + GrdSizeY + 1;
  
    hSFont := CreateFont( -13, 10, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, '돋움체' );
    hOldFont := SelectObject( dc, hSFont );
    SetTextColor( dc, gConfig.Colors.CellText );
  
    for i := 1 to 8 do begin
      DrawButtonLine( dc, Rect );
      StrPCopy( StrData, IntToStr(i) );
      DrawButtonText( dc, Rect, StrData );
      Rect.Top := Rect.Top + GrdSizeY + 1;
      Rect.Bottom := Rect.Bottom + GrdSizeY + 1;
    end;
  
    (* 상단 (요일) *)
    Rect.Top := 1;
    Rect.Bottom := GrdColY;
    Rect.Left := GrdRowX + 1 + 1;
    Rect.Right := GrdRowX + 1 + GrdSizeX;
  
    for i := MON to SAT do begin
      DrawButtonLine( dc, Rect );
      StrPCopy( StrData, WeekStr[i] );
      DrawButtonText( dc, Rect, StrData );
      Rect.Left := Rect.Left + GrdSizeX + 1;
      Rect.Right := Rect.Right + GrdSizeX + 1;
    end;
    SelectObject( dc, hOldFont );
    DeleteObject( hSFont );
  
    (* 선 *)
    hNewPen1 := CreatePen( PS_SOLID, 1, gConfig.Colors.GridLine );
    hNewPen2 := CreatePen( PS_SOLID, 1, gConfig.Colors.LunchTime );
    hOldPen := SelectObject( dc, hNewPen1 );
  
    for i := MON to SAT do begin
      MoveToEx( dc, GrdRowX + 1 + i*(GrdSizeX + 1), GrdColY + 1, Nil );
      LineTo( dc, GrdRowX + 1 + i*(GrdSizeX + 1), GrdColY + 2 + (GrdSizeY + 1) * 8 );
    end;
    for i := 1 to 8-1 do begin
      MoveToEx( dc, GrdRowX + 1, GrdColY + 1 + i*(GrdSizeY + 1), Nil );
      LineTo( dc, GrdRowX + (GrdSizeX + 1) * SAT, GrdColY + 1 + i*(GrdSizeY + 1) );
    end;
    SelectObject( dc, hNewPen2 );
    MoveToEx( dc, GrdRowX + 1, GrdColY + 1 + 4*(GrdSizeY + 1), Nil );
    LineTo( dc, GrdRowX + (GrdSizeX + 1) * SAT, GrdColY + 1 + 4*(GrdSizeY + 1) );
  
    SelectObject( dc, hOldPen );
    DeleteObject( hNewPen1 );
    DeleteObject( hNewPen2 );
  
    (* 데이터 표시 *)
    for i := MON to SAT do
      for j := 1 to 8 do
        DispClassData( dc, i, j );
end;

procedure TfrmClass.btnYear1Click(Sender: TObject);
var
  i: integer;

begin
  lstClass.Clear;

  for i := 1 to gSchool.ClassCount[1] do
    lstClass.Items.Add( IntToStr(i) );

  lstClass.ItemIndex := 0;
  ViewClass := 101;

  lstClassClick(lstClass);
end;

procedure TfrmClass.btnYear2Click(Sender: TObject);
var
  i: integer;

begin
  lstClass.Clear;

  for i := 1 to gSchool.ClassCount[2] do
    lstClass.Items.Add( IntToStr(i) );

  lstClass.ItemIndex := 0;
  ViewClass := 201;

  lstClassClick(lstClass);
end;

procedure TfrmClass.btnYear3Click(Sender: TObject);
var
  i: integer;

begin
  lstClass.Clear;

  for i := 1 to gSchool.ClassCount[3] do
    lstClass.Items.Add( IntToStr(i) );

  lstClass.ItemIndex := 0;
  ViewClass := 301;

  lstClassClick(lstClass);
end;

procedure TfrmClass.lstClassClick(Sender: TObject);
var
  w, n, i: integer;
  tt: PTeacherData;
  ts: PScheduleData;
  year: word;

begin
  year := ViewClass div 100;
  ViewClass := year * 100 + lstClass.ItemIndex + 1;

  for w := MON to SAT do begin
    for n := 1 to gSchool.WeekLimit[year, w] do begin
      ViewData[w, n].SubjectType := CT_NORMAL;
      ViewData[w, n].Subject := '';
      ViewData[w, n].TeacherName := '';

      ts := PSchedules;
      tt := PTeachers;
      for i := 1 to TeacherCount do begin
        if (ts^[w, n].ClassNo = ViewClass) or (ts^[w, n].ClassNo2 = ViewClass) then begin
          ViewData[w, n].SubjectType := CT_NORMAL;
          ViewData[w, n].Subject := tt^.Subject[year, ts^[w, n].ClassInfo mod 10].Name;
          ViewData[w, n].TeacherName := tt^.TeacherName;
          break;
        end;
        inc( ts );
        inc( tt );
      end;
    end;
    for n := gSchool.WeekLimit[year, w] + 1 to 8 do begin
      ViewData[w, n].SubjectType := CT_ETC;
      ViewData[w, n].Subject := '';
    end;
  end;

  for i := 1 to gSchool.SPC_Count do begin
    if (gSchool.SPC[i].Years and SPC_CLASSES[year]) <> 0 then begin
      ViewData[gSchool.SPC[i].Pos[year].w, gSchool.SPC[i].Pos[year].t].SubjectType := CT_SPECIAL;
      ViewData[gSchool.SPC[i].Pos[year].w, gSchool.SPC[i].Pos[year].t].Subject := gSchool.SPC[i].Name;
    end;
  end;

  pntTeacher.Refresh();
end;

procedure TfrmClass.FormCreate(Sender: TObject);
begin
  ViewClass := 101;
{  btnYear1Click(btnYear1);}
end;

procedure TfrmClass.pntTeacherMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  xx, yy: integer;

begin
  if (X > GrdRowX) and (Y > GrdColY) then begin
    xx := (X - GrdRowX - 2) div (GrdSizeX + 1) + 1;
    yy := (Y - GrdColY - 2) div (GrdSizeY + 1) + 1;

    if (xx <= SAT) and (yy <= 8) then begin
      edtInfo.Text := ViewData[xx, yy].TeacherName;
    end;
  end;
end;

end.
