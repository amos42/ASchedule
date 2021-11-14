unit f_main;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, Grids, StdCtrls, ExtCtrls, DB, DBTables,
  Buttons, Menus, Tabs, ComCtrls, ImgList, ToolWin, ActnList;

const
  GrdSizeX = 22;  // 그리드 수평 크기
  GrdSizeY = 20;  // 그리드 수직 크기
  GrdStartX = 16;   // 그리드 시작 수평 좌표
  GrdStartY = 72;   // 그리드 시작 수직 좌표

type
  TfrmMain = class(TForm)
    Panel1: TPanel;
    MainMenu1: TMainMenu;
    mnuFile: TMenuItem;
    mnuOpen: TMenuItem;
    mnuSave: TMenuItem;
    N4: TMenuItem;
    mnuClose: TMenuItem;
    hsbTeacher: TScrollBar;
    Panel3: TPanel;
    pntTeacher: TPaintBox;
    tabYear: TTabSet;
    mnuNew: TMenuItem;
    mnuTools: TMenuItem;
    mnuTools0: TMenuItem;
    mnuTools1: TMenuItem;
    mnuTools2: TMenuItem;
    mnuView: TMenuItem;
    mnuPersonal: TMenuItem;
    mnuClass: TMenuItem;
    Panel4: TPanel;
    pntVTimes: TPaintBox;
    Panel5: TPanel;
    pntHTimes: TPaintBox;
    dlgOpen: TOpenDialog;
    dlgSave: TSaveDialog;
    mnuSaveAs: TMenuItem;
    mnuPrint: TMenuItem;
    mnuPrnTeachers: TMenuItem;
    mnuPrnClasses: TMenuItem;
    mnuTools3: TMenuItem;
    mnuTools4: TMenuItem;
    N1: TMenuItem;
    N2: TMenuItem;
    N5: TMenuItem;
    N7: TMenuItem;
    N8: TMenuItem;
    sbStatus: TStatusBar;
    ToolBar1: TToolBar;
    btnNew: TToolButton;
    btnOpen: TToolButton;
    ToolButton3: TToolButton;
    btnSave: TToolButton;
    ToolButton5: TToolButton;
    btnPersonal: TToolButton;
    btnClass: TToolButton;
    ToolButton8: TToolButton;
    ImageList1: TImageList;
    PopupMenu1: TPopupMenu;
    btnTools: TToolButton;
    N9: TMenuItem;
    N10: TMenuItem;
    N11: TMenuItem;
    N12: TMenuItem;
    N13: TMenuItem;
    pnlTools: TPanel;
    ActionList1: TActionList;
    Action1: TAction;
    Action2: TAction;
    Action3: TAction;
    Action4: TAction;
    Action5: TAction;
    btnClose: TToolButton;
    ToolButton2: TToolButton;
    btnPrint: TToolButton;
    ToolButton4: TToolButton;
    PopupMenu2: TPopupMenu;
    N3: TMenuItem;
    N6: TMenuItem;
    N14: TMenuItem;
    mnuConfig: TMenuItem;
    PopupMenu3: TPopupMenu;
    mnuPersonalX: TMenuItem;
    MenuItem2: TMenuItem;
    MenuItem3: TMenuItem;
    MenuItem4: TMenuItem;
    MenuItem5: TMenuItem;
    MenuItem6: TMenuItem;
    MenuItem7: TMenuItem;
    tabWeek: TTabControl;
    CSV1: TMenuItem;
    mnuPrnTeacherCSV: TMenuItem;
    mnuPrnClassesCSV: TMenuItem;
    mnuPrnSchedules: TMenuItem;
    N15: TMenuItem;
    procedure pntTeacherMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure pntTeacherPaint(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure tabYearChange(Sender: TObject; NewTab: Integer;
      var AllowChange: Boolean);
    procedure mnuNewClick(Sender: TObject);
    procedure mnuToolsClick(Sender: TObject);
    procedure pntVTimesPaint(Sender: TObject);
    procedure pntHTimesPaint(Sender: TObject);
    procedure pntTeacherMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure mnuOpenClick(Sender: TObject);
    procedure mnuSaveClick(Sender: TObject);
    procedure mnuSaveAsClick(Sender: TObject);
    procedure mnuPersonalClick(Sender: TObject);
    procedure mnuClassClick(Sender: TObject);
    procedure mnuPrnTeachersClick(Sender: TObject);
    procedure mnuPrnClassesClick(Sender: TObject);
    procedure FormCanResize(Sender: TObject; var NewWidth,
      NewHeight: Integer; var Resize: Boolean);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure N2Click(Sender: TObject);
    procedure N5Click(Sender: TObject);
    procedure N8Click(Sender: TObject);
    procedure hsbTeacherChange(Sender: TObject);
    procedure Panel1Resize(Sender: TObject);
    procedure btnToolsClick(Sender: TObject);
    procedure mnuCloseClick(Sender: TObject);
    procedure mnuConfigClick(Sender: TObject);
    procedure mnuPersonalXClick(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure tabWeekChange(Sender: TObject);
    procedure mnuPrnTeacherCSVClick(Sender: TObject);
    procedure mnuPrnClassesCSVClick(Sender: TObject);
    procedure mnuPrnSchedulesClick(Sender: TObject);
  private
    { Private declarations }
    procedure SetTeacherCount( cnt: Integer );
    procedure RecalcScrollBar();
    procedure RefreshScreen();
    procedure EnableItems();
    procedure DisableItems();

  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;

implementation

uses Global, f_Personal, f_Change, f_Sclass, f_Sview, f_SINIT, f_TEACHER,
  f_about, f_config, r_schdule, r_classes, r_teacher, A_Util;

{$R *.DFM}

var
  curFileName: string[255];
  icurWork: Integer;
  mState: Boolean;
  mStartT, mStartN, mStartW: integer;
  curMouseT, curMouseN: word;

  
(************************************
  해당 위치에 반이 배정될 수 있는가
*************************************)
function IsPutClassNo( t, w, n, ClassNo: word ) : boolean;
begin
    if (GetClassType( t, w, n ) = CT_NORMAL) and
       (GetClassNo( t, w, n ) = 0) and
       (GetClassMulti( t, w, n, ClassNo ) = 0) then
      Result := True
    else
      Result := False;
end;

(********************
  빈 곳을 찾는다.
*********************)
function PutClassToEmpty( t, c, i: integer ) : boolean;
var
  y, w, n, t2, i2: integer;

begin
  y := c div 100;

  // 배치 가능한 곳을 찾는다.
  for n := 1 to 8 do
    for w := MON to SAT do
      if IsPutClassNo( t, w, n, c ) then begin
        SetClassNo( t, w, n, c );
        SetClassInfo( t, w, n, y * 10 + i );
        Result := True;
        Exit;
      end;

  // 배치 가능한 곳이 없으면 옮기기 시작
  for n := 1 to gSchool.WeekLimit[y, w] do
    for w := MON to SAT do
      if GetClassNo( t, w, n ) = 0 then begin
        t2 := GetClassMulti( t, w, n, c );
        if (t2 > 0) and (t2 <= 1000) and (GetClassType( t2, w, n ) = CT_NORMAL) then begin
          SetClassNo( t, w, n, c );
          SetClassType( t, w, n, CT_FIXED );
          SetClassInfo( t, w, n, y * 10 + i );
          i2 := GetClassInfo( t2, w, n );
          SetClassNo( t2, w, n, 0 );
          if PutClassToEmpty( t2, c, i2 mod 10 ) then begin
            SetClassType( t, w, n, CT_NORMAL );
            Result := True;
            Exit;
          end;
        end;
      end;

  Result := False;
end;


(***********************************
  지정된 위치에 클래스 출력
************************************)
procedure DispClassData( hDC: HDC; x, y: integer; t, w, n: integer );
var
  i, px, py: integer;
  Rect: TRECT;
  TempNum, TempNum2, TempYear: word;
  TempType: byte;
  TempStr: string;
  StrData: array[0..255] of char;
  tc: TColor;
  hOldBrush, hNewBrush: HBRUSH;
  hOldPen, hNewPen: HPEN;

begin
  px := (x - 1) * (GrdSizeX + 1) + GrdStartX + 2;
  py := (y - 1) * (GrdSizeY + 1) + GrdStartY + 2;
  Rect.Top := py;
  Rect.Left := px;
  Rect.Bottom := py + GrdSizeY;
  Rect.Right := px + GrdSizeX;

  TempNum := GetClassNo( t, curWeek, n );
  TempNum2 := GetClassNo2( t, curWeek, n );
  TempType := GetClassType( t, curWeek, n );

  if curYear > 0 then begin
    if n <= gSchool.WeekLimit[curYear, curWeek] then begin
      for i := 1 to gSchool.SPC_Count do begin
        if  ((gSchool.SPC[i].Years and SPC_CLASSES[curYear]) <> 0) and
            (w = gSchool.SPC[i].Pos[curYear].w) and (n = gSchool.SPC[i].Pos[curYear].t) then begin
          TempType := CT_SPECIAL;
          TempNum := i;
          break;
        end;
      end;

      if (TempNum > 0) and (TempType = CT_NORMAL) and
         ((TempNum div 100) <> curYear) then
        TempType := CT_ETC;
    end else
      TempType := CT_ETC;
  end;

  Case TempType of
    CT_NORMAL  : tc := gConfig.Colors.CellBackground;
    CT_FIXED   : tc := gConfig.Colors.FixedCell;
    CT_SPECIAL : tc := gConfig.Colors.SpecialCell;
    CT_ETC     : tc := gConfig.Colors.GrayCell;
    else         tc := clDkGray;
  end;

  hNewBrush := CreateSolidBrush( tc );
  hOldBrush := SelectObject( hDC, hNewBrush );
  hNewPen := CreatePen( PS_SOLID, 1, tc );
  hOldPen := SelectObject( hDC, hNewPen );
  FillRect( hDC, Rect, hNewBrush );

  SetBkColor( hDC, tc );

  Case TempType of
    CT_NORMAL, CT_FIXED :
      if TempNum > 0 then begin
        TempStr := Format( '%d-%d', [(TempNum div 100), (TempNum mod 100)] );
        if TempNum2 = 0 then begin
          StrPCopy( StrData, TempStr );
          DrawText( hDC, StrData, StrLen(StrData), Rect, DT_CENTER or DT_SINGLELINE or DT_VCENTER );
        end else begin
          TempStr := TempStr + #13 + Format( '%d-%d', [(TempNum2 div 100), (TempNum2 mod 100)] );
          StrPCopy( StrData, TempStr );
          DrawText( hDC, StrData, StrLen(StrData), Rect, DT_CENTER );
        end;
      end;
    CT_SPECIAL :
      begin
        StrPCopy( StrData, gSchool.SPC[TempNum].Name );
        DrawText( hDC, StrData, StrLen(StrData), Rect, DT_CENTER or DT_SINGLELINE or DT_VCENTER );
      end;
  end;

  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
  SelectObject( hDC, hOldBrush );
  DeleteObject( hNewBrush );
end;


(******************************
  작업 아이콘을 사용금지시킨다.
*******************************)
procedure TfrmMain.DisableItems();
begin
  mnuSave.Enabled := False;
  mnuSaveAs.Enabled := False;
  mnuView.Enabled := False;
  mnuTools.Enabled := False;
  mnuPrint.Enabled := False;

  btnSave.Enabled := False;
  btnPersonal.Enabled := False;
  btnClass.Enabled := False;
  btnPrint.Enabled := False;

  btnTools.Enabled := False;
end;


(*********************************
  작업 아이콘을 사용가능으로 만든다.
**********************************)
procedure TfrmMain.EnableItems();
begin
  mnuSave.Enabled := True;
  mnuSaveAs.Enabled := True;
  mnuView.Enabled := True;
  mnuTools.Enabled := True;
  mnuPrint.Enabled := True;

  btnSave.Enabled := True;
  btnPersonal.Enabled := True;
  btnClass.Enabled := True;
  btnPrint.Enabled := True;

  btnTools.Enabled := True;
end;


(*********************************

**********************************)
procedure TfrmMain.RefreshScreen();
begin
    pntTeacher.Refresh();
    pntHTimes.Refresh();
    pntVTimes.Refresh();
end;


(*********************************

**********************************)
procedure TfrmMain.RecalcScrollBar();
var
    vc: integer;
begin
    if TeacherCount <= 0 then Exit;

    vc := (pntTeacher.Width - GrdStartX) div (GrdSizeX + 1);
    if (pntTeacher.Width - GrdStartX) mod (GrdSizeX + 1) > 0 then inc( vc );

    hsbTeacher.PageSize := vc;
    // 버그 땜시... 쩝...
    hsbTeacherChange(hsbTeacher);
end;


procedure TfrmMain.SetTeacherCount( cnt: Integer );
begin
    if cnt > 0 then begin
      hsbTeacher.Max := cnt;
      hsbTeacher.Enabled := True;
    end else begin
      hsbTeacher.Enabled := False;
    end;
end;


procedure TfrmMain.FormCreate(Sender: TObject);
begin
  InitScheduleSource();
  LoadConfigData();

  TeacherCount := 0;

  curWeek := MON;
  curYear := 0;
  mState := False;
end;


procedure TfrmMain.FormCanResize(Sender: TObject; var NewWidth,
  NewHeight: Integer; var Resize: Boolean);
begin
    NewHeight := 445;
    if NewWidth < 512 then NewWidth := 512;
end;


procedure TfrmMain.pntTeacherPaint(Sender: TObject);
var
    pnt: TPaintBox;
    dc: HDC;
    brs: HBRUSH;
    i, j, xpos: integer;
    tt: PTeacherData;
    Rect: TRect;
    StrData: array [0..255] of char;
    en, sbp: integer;
    hOldPen, hNewPen1, hNewPen2: HPEN;
    hOldFont, hSFont: HFONT;
    vc: integer;

begin
    pnt := TPaintBox(Sender);
    dc := pnt.Canvas.Handle;

    vc := (pnt.Width - GrdStartX) div (GrdSizeX + 1);
    if (pnt.Width - GrdStartX) mod (GrdSizeX + 1) > 0 then inc( vc );

    xpos := pntTeacher.Width div GrdSizeX;
    if pntTeacher.Width mod GrdSizeX <> 0 then xpos := xpos - 1;

    tt := PTeachers;
    sbp := hsbTeacher.Position;
    inc(tt, sbp);

    if (sbp + vc) < TeacherCount then
      en := vc
    else
      en := TeacherCount - sbp;

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
  
    (* 상단 (선생님 명단) *)
    Rect.Top := 1;
    Rect.Bottom := GrdStartY;
    Rect.Left := GrdStartX + 1 + 1;
    Rect.Right := GrdStartX + 1 + GrdSizeX;
  
    for i := 1 to en do begin
      DrawButtonLine( dc, Rect );
      DrawButtonText( dc, Rect, tt^.TeacherName );
      Rect.Left := Rect.Left + GrdSizeX + 1;
      Rect.Right := Rect.Right + GrdSizeX + 1;
      inc( tt );
    end;
  
    SelectObject( dc, hOldFont );
    DeleteObject( hSFont );
  
    (* 선 *)
    hNewPen1 := CreatePen( PS_SOLID, 1, gConfig.Colors.GridLine );
    hNewPen2 := CreatePen( PS_SOLID, 1, gConfig.Colors.LunchTime );
    hOldPen := SelectObject( dc, hNewPen1 );
  
    for i := 1 to en do begin
      MoveToEx( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 1, Nil );
      LineTo( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 2 + (GrdSizeY + 1) * 8 );
    end;
    for i := 1 to 8-1 do begin
      MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + i*(GrdSizeY + 1), Nil );
      LineTo( dc, GrdStartX + (GrdSizeX + 1) * en, GrdStartY + 1 + i*(GrdSizeY + 1) );
    end;
    SelectObject( dc, hNewPen2 );
    MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + gSchool.LunchTime*(GrdSizeY + 1), Nil );
    LineTo( dc, GrdStartX + (GrdSizeX + 1) * en, GrdStartY + 1 + gSchool.LunchTime*(GrdSizeY + 1) );
  
    SelectObject( dc, hOldPen );
    DeleteObject( hNewPen1 );
    DeleteObject( hNewPen2 );
  
    (* 데이터 표시 *)
    for i := 1 to en do
      for j := 1 to 8 do
        DispClassData( dc, i, j, sbp+i, curWeek, j );
end;


procedure TfrmMain.pntTeacherMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  xx, yy: integer;
  tx, t2, t3: integer;
  cnf, cnf2, cnt, cnt2: word;
  ct: byte;
  tt: PTeacherData;
  info: word;
  TempStr: string;
  p : TPoint;

begin
  if Button = mbLeft then begin
    if (X > GrdStartX) and (Y > GrdStartY) then begin
      xx := (X - GrdStartX - 2) div (GrdSizeX + 1) + 1;
      yy := (Y - GrdStartY - 2) div (GrdSizeY + 1) + 1;

//      if (xx <= MAXTEACHER) and (xx <= TeacherCount) and (yy <= 8) then begin
      if (xx <= TeacherCount) and (yy <= 8) then begin
        tx := xx + hsbTeacher.Position;
        tt := PTeachers;
        case iCurWork of
          (* 정보 *)
          0: if (GetClassType( tx, curWeek, yy ) <> CT_SPECIAL) and
                (GetClassNo( tx, curWeek, yy ) > 0) then begin
               inc( tt, tx - 1 );
               info := GetClassInfo( tx, curWeek, yy );
               cnf := info div 10;
               cnt := info mod 10;
               TempStr := tt^.TeacherName + '(' + tt^.Subject[cnf, cnt].Name + ') : ';
               TempStr := TempStr + IntToStr(cnf) + '-' + IntToStr(tt^.Subject[cnf, cnt].StartClass) + ' ~ ';
               TempStr := TempStr + IntToStr(cnf) + '-' + IntToStr(tt^.Subject[cnf, cnt].EndClass);
               sbStatus.SimpleText := TempStr;
             end;

          (* 옮기기 *)
          1: if (GetClassType(tx, curWeek, yy) = CT_NORMAL) then begin
               if not mState then begin
                 if GetClassNo(tx, curWeek, yy) > 0 then begin
                   mStartT := tx; mStartN := yy;
                   mStartW := curWeek;
                   inc( tt, tx - 1 );
                   TempStr := tt^.TeacherName + ' : ' + WeekStr[curWeek] + '요일 ' + IntToStr(yy) + '교시 => ';
                   sbStatus.SimpleText := TempStr;
                   pntTeacher.Cursor := crDrag;
                   mState := True;
                 end;
               end else begin
                 if (mStartT = tx) and ((yy <> mStartN) or (curWeek <> mStartW)) then begin
                   if CanItChange( tx, mStartW, mStartN, curWeek, yy ) then begin
                     ChangeT := tx;
                     ChangeSW := mStartW;
                     ChangeSN := mStartN;
                     ChangeEW := curWeek;
                     ChangeEN := yy;
                     ChangeType := 1;
                     frmChange.ShowModal();
                   end;

                   RefreshScreen();

                   sbStatus.SimpleText := sbStatus.SimpleText + WeekStr[curWeek] + '요일 ' + IntToStr(yy) + '교시';

                   mState := False;
                   pntTeacher.Cursor := crDefault;
                 end;
               end;
             end;

          (* 고정/해제 *)
          2: if GetClassType( tx, curWeek, yy ) = CT_NORMAL then begin
               SetClassType( tx, curWeek, yy, CT_FIXED );
               DispClassData( pntTeacher.Canvas.Handle, xx, yy, tx, curWeek, yy );
             end else if GetClassType( tx, curWeek, yy ) = CT_FIXED then begin
               SetClassType( tx, curWeek, yy, CT_NORMAL );
               DispClassData( pntTeacher.Canvas.Handle, xx, yy, tx, curWeek, yy );
             end;

          (* 합반처리 *)
          3: if (GetClassType(tx, curWeek, yy) = CT_NORMAL) and
                (GetClassNo(tx, curWeek, yy) > 0) and
                (GetClassNo2(tx, curWeek, yy) = 0) then begin
               if not mState then begin
                 mStartT := tx; mStartN := yy;
                 mStartW := curWeek;
                 inc( tt, tx - 1 );
                 TempStr := tt^.TeacherName + ' : ' + WeekStr[curWeek] + '요일 ' + IntToStr(yy) + '교시 + ';
                 sbStatus.SimpleText := TempStr;
                 pntTeacher.Cursor := crDrag;
                 mState := True;
               end else begin
                 if (mStartT = tx) and ((yy <> mStartN) or (curWeek <> mStartW)) then begin
                   if CanItMulti( tx, mStartW, mStartN, curWeek, yy ) then begin
                     ChangeT := tx;
                     ChangeSW := mStartW;
                     ChangeSN := mStartN;
                     ChangeEW := curWeek;
                     ChangeEN := yy;
                     ChangeType := 2;
                     frmChange.ShowModal;
                   end;

                   RefreshScreen();

                   sbStatus.SimpleText := sbStatus.SimpleText + WeekStr[curWeek] + '요일 ' + IntToStr(yy) + '교시';

                   mState := False;
                   pntTeacher.Cursor := crDefault;
                 end;
               end;
             end;
          (* 힙반해제 *)
          4: if (GetClassType(tx, curWeek, yy) = CT_NORMAL) then begin
               if not mState then begin
                 if (GetClassNo(tx, curWeek, yy) > 0) and
                    (GetClassNo2(tx, curWeek, yy) > 0) then begin
                   mStartT := tx; mStartN := yy;
                   mStartW := curWeek;
                   inc( tt, tx - 1 );
                   TempStr := tt^.TeacherName + ' : ' + WeekStr[curWeek] + '요일 ' + IntToStr(yy) + '교시 => ';
                   sbStatus.SimpleText := TempStr;
                   pntTeacher.Cursor := crDrag;
                   mState := True;
                 end;
               end else begin
                 if (mStartT = tx) and ((yy <> mStartN) or (curWeek <> mStartW)) then begin
                   if CanItRelease( tx, mStartW, mStartN, curWeek, yy ) then begin
                     ChangeT := tx;
                     ChangeSW := mStartW;
                     ChangeSN := mStartN;
                     ChangeEW := curWeek;
                     ChangeEN := yy;
                     ChangeType := 3;
                     frmChange.ShowModal;
                   end;

                   RefreshScreen();

                   sbStatus.SimpleText := sbStatus.SimpleText + WeekStr[curWeek] + '요일 ' + IntToStr(yy) + '교시';

                   mState := False;
                   pntTeacher.Cursor := crDefault;
                 end;
               end;
             end;
        end;
      end;
    end;
  end else begin
    if mState then begin
      pntTeacher.Cursor := crDefault;
      mState := False;
    end;
    if TeacherCount > 0 then begin
      if (X > GrdStartX) and (Y < GrdStartY) then begin
        xx := (X - GrdStartX - 2) div (GrdSizeX + 1);
        xx := xx + hsbTeacher.Position;
        tt := pTeachers;
        inc( tt, xx );

        mnuPersonalX.Caption := '개인별(' + tt^.TeacherName + ') 시간표';
        mnuPersonalX.Tag := xx + 1;
        p.X := X; p.Y := Y;
        p := TPaintBox(Sender).ClientToScreen( p );
        PopupMenu3.Popup( p.X, p.Y );
      end;
    end;
  end;
end;


procedure TfrmMain.tabYearChange(Sender: TObject; NewTab: Integer;
  var AllowChange: Boolean);
begin
    curYear := NewTab;
    RefreshScreen();
end;


procedure TfrmMain.mnuCloseClick(Sender: TObject);
begin
    Close();
end;


procedure TfrmMain.mnuConfigClick(Sender: TObject);
begin
    frmConfig.ShowModal();
    RefreshScreen();
end;


procedure TfrmMain.mnuNewClick(Sender: TObject);
label
  ExitSub;

var
  t, y, i, j, c: integer;
  s, e: integer;
  tn: integer;
  tt: PTeacherData;

begin
  ClearScheduleData();

  tt := PTeachers;

  for t := 1 to TeacherCount do begin
    for y := 1 to 3 do
      for i := 1 to MAX_TEACHER_SUBJECT do
        if tt^.Subject[y, i].Name <> '' then begin
          s := tt^.Subject[y, i].StartClass;
          e := tt^.Subject[y, i].EndClass;
          for j := 1 to tt^.Subject[y, i].Times do begin
            for c := s to e do begin
              if not PutClassToEmpty( t, y*100 + c, i ) then begin
//              ShowMessage( IntToStr(t) + ', ' + IntToStr(y) + ', ' + IntToStr(y) + ',' + IntToStr(c) + ',' + IntToStr(i) );
                MessageBeep( MB_ICONEXCLAMATION );
                MessageDlg( '초기베치에 실패했습니다. 문제를 해결한 후에 다시 시도하십시요.', mtWarning, [mbOk], 0 );
                ClearScheduleData();
                DisableItems();
                Goto ExitSub;
              end;
            end;
          end;
        end; {if}
    inc( tt );
  end; {t}

  curFileName := 'UNTITLED.SCD';
  EnableItems;

ExitSub:
    RefreshScreen();
end;


procedure TfrmMain.mnuToolsClick(Sender: TObject);
begin
    if mState then begin
      pntTeacher.Cursor := crDefault;
      mState := False;
    end;
  
    TAction(Sender).Checked := True;
    iCurWork := TAction(Sender).Tag;
    pnlTools.Caption := TAction(Sender).Caption;
end;


procedure TfrmMain.pntVTimesPaint(Sender: TObject);
var
    pnt: TPaintBox;
    dc: HDC;
    brs: HBRUSH;
    t, n, s, y: integer;
    StrData: array[0..255] of char;

begin
    pnt := TPaintBox(Sender);
    dc := pnt.Canvas.Handle;

    brs := CreateSolidBrush( GetSysColor(COLOR_BTNFACE) );
    FillRect( dc, pnt.Canvas.ClipRect, brs );
    DeleteObject( brs );

    for n := 1 to 8 do begin
      s := 0;
      for t := 1 to TeacherCount do
        if (GetClassType( t, curWeek, n ) in [CT_NORMAL, CT_FIXED]) and (GetClassNo( t, curWeek, n ) > 0) then begin
          inc( s );
          if GetClassNo2( t, curWeek, n ) > 0 then inc( s );
        end;
      y := (n - 1) * (GrdSizeY + 1) + 2;
      StrPCopy( StrData, Format( '%3d', [s] ) );
      TextOut( dc, 1, y, StrData, StrLen(StrData) );
    end;
end;


procedure TfrmMain.pntHTimesPaint(Sender: TObject);
var
    pnt: TPaintBox;
    dc: HDC;
    t, n, s, x, sbp, vc, en: integer;
    StrData: array[0..255] of char;
    ts: PScheduleData;

begin
    pnt := TPaintBox(Sender);
    dc := pnt.Canvas.Handle;

    vc := (pnt.Width - GrdStartX) div (GrdSizeX + 1);
    if (pnt.Width - GrdStartX) mod (GrdSizeX + 1) > 0 then inc( vc );

    ts := PSchedules;
    sbp := hsbTeacher.Position;
    inc( ts, sbp );

    if (sbp + vc) < TeacherCount then
      en := vc
    else
      en := TeacherCount - sbp;

    for t := 1 to en do begin
      s := 0;
      for n := 1 to 8 do
        if (ts^[curWeek, n].ClassType in [CT_NORMAL, CT_FIXED]) and (ts^[curWeek, n].ClassNo > 0) then begin
          inc( s );
          if ts^[curWeek, n].ClassNo2 > 0 then inc( s );
        end;
      x := (t - 1) * (GrdSizeX + 1) + 5;
      StrPCopy( StrData, Format( '%2d', [s] ) );
      TextOut( dc, x, 1, StrData, StrLen(StrData) );

      inc( ts );
    end;
end;

procedure TfrmMain.pntTeacherMouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
var
  tt, nn, tx: word;

begin
  if mState then begin
    if (X > GrdStartX) and (Y > GrdStartY) then begin
      tt := (X - GrdStartX - 2) div (GrdSizeX + 1) + 1;
      nn := (Y - GrdStartY - 2) div (GrdSizeY + 1) + 1;

      if (tt <> curMouseT) or (nn <> curMouseN) then begin
//        if (tt <= MAXTEACHER) and (tt <= TeacherCount) and (nn <= 8) then begin
        if (tt <= TeacherCount) and (nn <= 8) then begin
          tx := tt + hsbTeacher.Position;
          case iCurWork of
            // 옮기기
            1 : if (tx = mStartT) and CanItChange( mStartT, mStartW, mStartN, curWeek, nn ) then
                  pntTeacher.Cursor := crMultiDrag
                else
                  pntTeacher.Cursor := crDrag;
            // 합반 처리
            3 : if (tx = mStartT) and CanItMulti( mStartT, mStartW, mStartN, curWeek, nn ) then
                  pntTeacher.Cursor := crMultiDrag
                else
                  pntTeacher.Cursor := crDrag;
            // 합반 해제
            4 : if (tx = mStartT) and CanItRelease( mStartT, mStartW, mStartN, curWeek, nn ) then
                  pntTeacher.Cursor := crMultiDrag
                else
                  pntTeacher.Cursor := crDrag;
          end;
        end else pntTeacher.Cursor := crNoDrop;
        curMouseT := tt;
        curMouseN := nn;
      end;
    end else pntTeacher.Cursor := crNoDrop;
  end;
end;


procedure TfrmMain.mnuOpenClick(Sender: TObject);
begin
    if dlgOpen.Execute then begin
      curFileName := dlgOpen.FileName;
  
      if not LoadScheduleData( curFileName ) then begin
        MessageDlg( '파일 열기에 실패했습니다.' + #13 + #13 +
                    '잘못된 파일이거나 구버전 파일 형식입니다.',
                    mtWarning, [mbOk], 0 );
        exit;
      end;
  
      if TeacherCount > 0 then begin
        btnNew.Enabled := true;
        EnableItems();
      end else begin
        btnNew.Enabled := false;
        DisableItems();
      end;
  
      SetTeacherCount(TeacherCount);
      RecalcScrollBar();
      RefreshScreen();
      frmPersonal.RefreshTeachers();
    end;
end;


procedure TfrmMain.mnuSaveClick(Sender: TObject);
begin
    if curFileName = 'UNTITLED.SCD' then
      mnuSaveAs.Click()
    else begin
      SaveScheduleData( curFileName );
      MessageDlg( '저장되었습니다.', mtInformation, [mbOk], 0 );
    end;
end;


procedure TfrmMain.mnuSaveAsClick(Sender: TObject);
var
    f: integer;
    TempName: string[255];
    r: boolean;

begin
  if dlgSave.Execute then begin
    r := False;
    TempName := dlgSave.FileName;

    if FileExists( TempName ) then begin
      if MessageDlg( '파일이 이미 존재합니다. 겹쳐 쓰시겠씁까?',
         mtConfirmation, [mbYes, mbNo], 0 ) = mrYes then
        r := True;
    end else begin
      f := FileCreate( TempName ); // File selected in dialog
      FileClose( f );
      r := True;
    end;

    if r then begin
      curFileName := TempName;
      SaveScheduleData( curFileName );
      MessageDlg( '저장되었습니다.', mtInformation, [mbOk], 0 );
    end;
  end;
end;


procedure TfrmMain.mnuPersonalClick(Sender: TObject);
begin
    frmPersonal.ShowModal();
    RefreshScreen();
end;


procedure TfrmMain.mnuClassClick(Sender: TObject);
begin
    frmClass.ShowModal();
    RefreshScreen();
end;


procedure TfrmMain.mnuPrnTeachersClick(Sender: TObject);
begin
    qrTeachers.Preview();
end;


procedure TfrmMain.mnuPrnClassesClick(Sender: TObject);
begin
    qrClasses.Preview();
end;


procedure TfrmMain.mnuPrnSchedulesClick(Sender: TObject);
begin
    qrSchedules.Preview();
end;

procedure TfrmMain.FormCloseQuery(Sender: TObject;
  var CanClose: Boolean);
begin
    if MessageDlg2( '정말 끝내시겠습니까?', '종료 확인',
                   mtConfirmation, [mbYes, mbNo], 0 ) <> mrYes then begin
      CanClose := false;
    end;
end;


procedure TfrmMain.N2Click(Sender: TObject);
begin
    frmSInit.ShowModal();
    RefreshScreen();
end;


procedure TfrmMain.N5Click(Sender: TObject);
begin
    frmTeacher.ShowModal();

    SetTeacherCount(TeacherCount);
    RecalcScrollBar();
    frmPersonal.RefreshTeachers();

    if TeacherCount > 0 then begin
      btnNew.Enabled := true;
    end else begin
      btnNew.Enabled := false;
    end;

    RefreshScreen();
end;


procedure TfrmMain.N8Click(Sender: TObject);
begin
    frmAbout.ShowModal();
end;


procedure TfrmMain.hsbTeacherChange(Sender: TObject);
begin
    // 원래 불필요하나, 스크롤바 버그 탓으로 넣음
    if hsbTeacher.Position > hsbTeacher.Max - hsbTeacher.PageSize then begin
      hsbTeacher.Position := hsbTeacher.Max - hsbTeacher.PageSize + 1;
    end;

    pntTeacher.Refresh();
    pntHTimes.Refresh();
end;


procedure TfrmMain.Panel1Resize(Sender: TObject);
begin
    RecalcScrollBar();
end;


procedure TfrmMain.btnToolsClick(Sender: TObject);
var
    p: TPoint;
    btn: TToolButton;
begin
    btn := TToolButton(Sender);
    p.x := btn.Left;
    p.y := btn.Top + btn.Height;
    p := Self.ClientToScreen( p );
    PopupMenu1.Popup( p.x, p.y );
end;


procedure TfrmMain.mnuPersonalXClick(Sender: TObject);
begin
    frmPersonal.SetTeacherNo( TMenuItem(Sender).Tag );
    mnuPersonal.Click();
end;

procedure TfrmMain.FormKeyPress(Sender: TObject; var Key: Char);
begin
    case Key of
      '1'..'7' : begin
                   tabWeek.TabIndex := Ord(Key) - Ord('1');
                   tabWeekChange(tabWeek);
                 end;
    end;
end;

procedure TfrmMain.tabWeekChange(Sender: TObject);
begin
    curWeek := tabWeek.TabIndex + 1;
    RefreshScreen();
end;

procedure TfrmMain.mnuPrnTeacherCSVClick(Sender: TObject);
var
    w, t, n: integer;
    tt: PTeacherData;
    ts: PScheduleData;
    cc: integer;
    tempStr: string;
    f: integer;

begin
    tempStr := 'TR_PRN.CSV';
    f := FileCreate( tempStr );
    if f <= 0 then begin
      ShowMessage( '파일 생성 실패' );
      Exit;
    end;

    for w := MON to SAT do begin
      tempStr := '(' + WeekStr[w] + ')' + #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );

      tempStr := '이름, 1교시, 2교시, 3교시, 4교시, 5교시, 6교시, 7교시, 8교시, 시수' + #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );
      tempStr := '==================================================================' + #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );

      tt := PTeachers;
      ts := PSchedules;

      for t := 1 to TeacherCount do begin
        FileWrite( f, tt^.TeacherName, StrLen(tt^.TeacherName) );
        TempStr := ',';
        FileWrite( f, PChar(TempStr)^, Length(TempStr) );

        cc := 0;
        for n := 1 to 8 do begin
          if ts^[w, n].ClassType = CT_SPECIAL then
            case ts^[w, n].ClassNo of
              1 : TempStr := 'SE';
              2 : TempStr := 'HR';
              3 : TempStr := 'CA';
            end
          else begin
            if ts^[w, n].ClassNo > 0 then begin
              TempStr := IntToStr(ts^[w, n].ClassNo div 100) + '-' + IntToStr(ts^[w, n].ClassNo mod 100);
              inc( cc );
              if ts^[w, n].ClassNo2 > 0 then begin
                TempStr := TempStr + ' ' + IntToStr(ts^[w, n].ClassNo2 div 100) + '-' + IntToStr(ts^[w, n].ClassNo2 mod 100);
                inc( cc );
              end;
            end else
              TempStr := '';
          end;

          TempStr := '=T("' + TempStr +'")';
          FileWrite( f, PChar(TempStr)^, Length(TempStr) );
          TempStr := ',';
          FileWrite( f, PChar(TempStr)^, Length(TempStr) );
        end;

        TempStr := IntToStr(cc);
        FileWrite( f, PChar(TempStr)^, Length(TempStr) );
        TempStr := #13;
        FileWrite( f, PChar(TempStr)^, Length(TempStr) );

        inc( tt );
        inc( ts );
      end;

      tempStr := #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );
    end;

    FileClose( f );

    MessageDlg( 'TR_PRN.CSV 파일 출력이 끝났습니다.', mtInformation, [mbOk], 0 );
end;

procedure TfrmMain.mnuPrnClassesCSVClick(Sender: TObject);
var
    i: integer;
    tempStr: string;
    f: integer;
    w, y, c, n: integer;
    tt: PTeacherData;
    ts: PScheduleData;
    year: word;

begin
    tempStr := 'CL_PRN.CSV';
    f := FileCreate( tempStr );
    if f <= 0 then begin
      ShowMessage( '파일 생성 실패' );
      Exit;
    end;
  
    for w := MON to SAT do begin
      tempStr := '(' + WeekStr[w] + ')' + #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );
  
      tempStr := '학년-반, 1교시, 2교시, 3교시, 4교시, 5교시, 6교시, 7교시, 8교시' + #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );
      tempStr := '===============================================================' + #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );
  
      tt := PTeachers;
      ts := PSchedules;
  
      for y := 1 to 3 do begin
        for c := 1 to gSchool.ClassCount[y] do begin
          tempStr := '=T("' + IntToStr(y) + '-' + IntToStr(c) + '")';
          FileWrite( f, PChar(TempStr)^, Length(TempStr) );
          TempStr := ',';
          FileWrite( f, PChar(TempStr)^, Length(TempStr) );
  
          for n := 1 to gSchool.WeekLimit[y, w] do begin
            TempStr := '';

            for i := 1 to gSchool.SPC_Count do begin
              if ((gSchool.SPC[i].Years and SPC_CLASSES[y]) <> 0) and
                 (gSchool.SPC[i].Pos[y].w = w) and (gSchool.SPC[i].Pos[y].t = n) then begin
                TempStr := gSchool.SPC[i].Name;
                break;
              end;  
            end;

            if TempStr = '' then begin
              ts := pSchedules;
              tt := pTeachers;
              for i := 1 to TeacherCount do begin
                if (ts^[w, n].ClassNo = y * 100 + c) or
                   (ts^[w, n].ClassNo2 = y * 100 + c) then
                  TempStr := tt^.Subject[y, ts^[w, n].ClassInfo mod 10].Name;

                inc( ts );
                inc( tt );
              end;
            end;
  
            FileWrite( f, PChar(TempStr)^, Length(TempStr) );
            TempStr := ',';
            FileWrite( f, PChar(TempStr)^, Length(TempStr) );
          end;
  
          TempStr := #13;
          FileWrite( f, PChar(TempStr)^, Length(TempStr) );
        end;
      end;
  
      tempStr := #13;
      FileWrite( f, PChar(TempStr)^, Length(TempStr) );
    end;
  
    FileClose( f );

    MessageDlg( 'CL_PRN.CSV 파일 출력이 끝났습니다.', mtInformation, [mbOk], 0 );
end;

end.
