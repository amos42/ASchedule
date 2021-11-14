unit f_SVIEW;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, StdCtrls, Buttons,
  Global;

const
  GrdSizeX = 22;
  GrdSizeY = 20;
  GrdStartX = 16;
  GrdStartY = 21;

type
  TfrmView = class(TForm)
    Panel3: TPanel;
    pntTeacher: TPaintBox;
    pntChange1: TPaintBox;
    pntChange2: TPaintBox;
    procedure pntTeacherPaint(Sender: TObject);
    procedure DispClassData( hDC: HDC; w, n: integer );
    procedure FormShow(Sender: TObject);
    procedure pntChange1Paint(Sender: TObject);
    procedure pntChange2Paint(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    ViewData: TScheduleData;
    ViewTeacher: word;
    StartPos, EndPos: TClassPos;
    Change1, Change2: string[10];
  end;

var
  frmView: TfrmView;

implementation

{$R *.DFM}

(***********************************
  지정된 위치에 클래스 출력
************************************)
procedure TfrmView.DispClassData( hDC: HDC; w, n: integer );
var
  px, py: integer;
  Rect: TRECT;
  TempNum, TempNum2: integer;
  TempType: byte;
  TempStr: string;
  StrData: array[0..255] of char;
  tc: TColor;
  hOldBrush, hNewBrush: HBRUSH;

begin
  px := (w - 1) * (GrdSizeX + 1) + GrdStartX + 2;
  py := (n - 1) * (GrdSizeY + 1) + GrdStartY + 2;
  Rect.Top := py;
  Rect.Left := px;
  Rect.Bottom := py + GrdSizeY;
  Rect.Right := px + GrdSizeX;

  TempNum := ViewData[w,n].ClassNo;
  TempNum2 := ViewData[w,n].ClassNo2;
  TempType := ViewData[w,n].ClassType;

  // 이동하는 것은 붉은 색으로... 
  if ((w = StartPos.w) and (n = StartPos.t)) or
     ((w = EndPos.w) and (n = EndPos.t)) then
    TempType := CT_FOCUS;

  Case TempType of
    CT_NORMAL  : tc := gConfig.Colors.CellBackground;
    CT_FIXED   : tc := gConfig.Colors.FixedCell;
    CT_SPECIAL : tc := gConfig.Colors.SpecialCell;
    CT_ETC     : tc := gConfig.Colors.GrayCell;
    CT_FOCUS   : tc := gConfig.Colors.FocusCell;
    else         tc := clDkGray;
  end;

  hNewBrush := CreateSolidBrush( tc );
  hOldBrush := SelectObject( hDC, hNewBrush );
  SetBkColor( hDC, tc );

  FillRect( hDC, Rect, hNewBrush );

  Case TempType of
    CT_NORMAL, CT_FIXED, CT_FOCUS :
      if TempNum > 0 then begin
        if TempNum2 = 0 then begin
          TempStr := IntToStr(TempNum div 100) + '-' + IntToStr(TempNum mod 100);
          StrPCopy( StrData, TempStr );
          DrawText( hDC, StrData, lstrlen(StrData), Rect, DT_CENTER or DT_SINGLELINE or DT_VCENTER );
        end else begin
          TempStr := IntToStr(TempNum div 100) + '-' + IntToStr(TempNum mod 100);
          TempStr := TempStr + #13 + IntToStr(TempNum2 div 100) + '-' + IntToStr(TempNum2 mod 100);
          StrPCopy( StrData, TempStr );
          DrawText( hDC, StrData, lstrlen(StrData), Rect, DT_CENTER );
        end;
      end;
    CT_SPECIAL :
      begin
        StrPCopy( StrData, gSchool.SPC[TempNum].Name );
        DrawText( hDC, StrData, lstrlen(StrData), Rect, DT_CENTER or DT_SINGLELINE or DT_VCENTER );
      end;
  end;

  SelectObject( hDC, hOldBrush );
  DeleteObject( hNewBrush );
end;


procedure TfrmView.pntTeacherPaint(Sender: TObject);
var
    pnt: TPaintBox;
    dc: HDC;
    i, j, xpos: integer;
    Rect: TRect;
    StrData: array [0..255] of char;
    hOldPen, hNewPen1, hNewPen2, hNewPen3: HPEN;
    hOldFont, hSFont: HFONT;

begin
    pnt := TPaintBox(Sender);
    dc := pnt.Canvas.Handle;

    xpos := pntTeacher.Width div GrdSizeX;
    if pntTeacher.Width mod GrdSizeX <> 0 then xpos := xpos - 1;
  
    (* 최좌상단 *)
    Rect.Top := 1;
    Rect.Bottom := GrdStartY;
    Rect.Left := 1;
    Rect.Right := GrdStartX;
    DrawButtonLine( dc, Rect );
  
    (* 새로운 폰트 *)
    hSFont := CreateFont( -13, 10, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, '돋움체' );
    hOldFont := SelectObject( dc, hSFont );
    SetTextColor( dc, gConfig.Colors.CellText );
  
    (* 좌측(1~8교시) *)
    Rect.Top := GrdStartY + 1 + 1;
    Rect.Bottom := GrdStartY + GrdSizeY + 1;
    for i := 1 to 8 do begin
      DrawButtonLine( dc, Rect );
      StrPCopy( StrData, IntToStr(i) );
      DrawButtonText( dc, Rect, StrData );
      Rect.Top := Rect.Top + GrdSizeY + 1;
      Rect.Bottom := Rect.Bottom + GrdSizeY + 1;
    end;

    (* 상단 (요일) *)
    Rect.Top := 1;
    Rect.Bottom := GrdStartY;
    Rect.Left := GrdStartX + 1 + 1;
    Rect.Right := GrdStartX + 1 + GrdSizeX;
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
//    hNewPen3 := CreatePen( PS_SOLID, 1, clBlue );
    hOldPen := SelectObject( dc, hNewPen1 );

    for i := MON to FRI do begin
      MoveToEx( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 1, Nil );
      LineTo( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 2 + (GrdSizeY + 1) * 8 );
    end;
    for i := 1 to 8-1 do begin
      MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + i*(GrdSizeY + 1), Nil );
      LineTo( dc, GrdStartX + (GrdSizeX + 1) * SAT, GrdStartY + 1 + i*(GrdSizeY + 1) );
    end;
    SelectObject( dc, hNewPen2 );
    MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + gSchool.LunchTime*(GrdSizeY + 1), Nil );
    LineTo( dc, GrdStartX + (GrdSizeX + 1) * SAT, GrdStartY + 1 + gSchool.LunchTime*(GrdSizeY + 1) );

    (* 데이터 표시 *)
    for i := MON to SAT do
      for j := 1 to 8 do
        DispClassData( dc, i, j );

//    SelectObject( dc, hNewPen3 );

{ 만들다 말았음. 움직이는 방향으로 화살표 그리는 것... 
    DrawArrowLine( dc, GrdStartX+2 + StartPos.w*GrdSizeX-(GrdSizeX div 2),
                       GrdStartY+2 + StartPos.t*GrdSizeY-(GrdSizeY div 2),
                       GrdStartX+2 + EndPos.w*GrdSizeX-(GrdSizeX div 2),
                       GrdStartY+2 + EndPos.t*GrdSizeY-(GrdSizeY div 2) );
}

    SelectObject( dc, hOldPen );
    DeleteObject( hNewPen1 );
    DeleteObject( hNewPen2 );
//    DeleteObject( hNewPen3 );
end;

procedure TfrmView.FormShow(Sender: TObject);
var
  ts: PScheduleData;
  tt: PTeacherData;

begin
{  tt := PTeachers;
  inc( tt, ViewTeacher - 1 );
  pnlTeacher.Caption := tt^.TeacherName;

  ts := PSchedules2;
  inc( ts, ViewTeacher - 1 );
  ViewData := ts^;}
end;

procedure TfrmView.pntChange1Paint(Sender: TObject);
var
  Rect: TRect;
  StrData: array[0..255] of char;

begin
  Rect := pntChange1.Canvas.ClipRect;
  dec( Rect.Right );
  dec( Rect.Bottom );
  DrawButtonLine( pntChange1.Canvas.Handle, Rect );

  inc( Rect.Left );
  inc( Rect.Top, 10 );
  dec( Rect.Right );
  dec( Rect.Bottom );
  StrPCopy( StrData, Change1 );
  DrawText( pntChange1.Canvas.Handle, StrData, lstrlen(StrData), Rect, DT_CENTER );
end;

procedure TfrmView.pntChange2Paint(Sender: TObject);
var
  Rect: TRect;
  StrData: array[0..255] of char;

begin
  Rect := pntChange1.Canvas.ClipRect;
  dec( Rect.Right );
  dec( Rect.Bottom );
  DrawButtonLine( pntChange2.Canvas.Handle, Rect );

  inc( Rect.Left );
  inc( Rect.Top, 10 );
  dec( Rect.Right );
  dec( Rect.Bottom );
  StrPCopy( StrData, Change2 );
  DrawText( pntChange2.Canvas.Handle, StrData, lstrlen(StrData), Rect, DT_CENTER );
end;

end.
