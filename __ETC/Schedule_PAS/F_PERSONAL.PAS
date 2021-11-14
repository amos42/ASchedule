unit f_PERSONAL;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, Buttons, StdCtrls, Menus, ActnList, ImgList,
  ComCtrls, ToolWin;

const
  GrdSizeX = 22;
  GrdSizeY = 20;
  GrdStartX = 16;
  GrdStartY = 21;

type
  TfrmPersonal = class(TForm)
    Panel3: TPanel;
    pntTeacher: TPaintBox;
    lstTeacher: TListBox;
    MainMenu1: TMainMenu;
    mnuClose: TMenuItem;
    mnuTools0: TMenuItem;
    mnuTools1: TMenuItem;
    mnuTools2: TMenuItem;
    pnlInfo: TPanel;
    edtInfo: TEdit;
    mnuTools3: TMenuItem;
    mnuTools4: TMenuItem;
    N5: TMenuItem;
    mnuFindMulti: TMenuItem;
    mnuFind4and5: TMenuItem;
    mnuFind3Cont: TMenuItem;
    mnuFindOver5: TMenuItem;
    N3: TMenuItem;
    mnuClass: TMenuItem;
    N2: TMenuItem;
    mnuFindFirst: TMenuItem;
    ImageList1: TImageList;
    PopupMenu1: TPopupMenu;
    N9: TMenuItem;
    N10: TMenuItem;
    N13: TMenuItem;
    N11: TMenuItem;
    N12: TMenuItem;
    ActionList1: TActionList;
    Action1: TAction;
    Action2: TAction;
    Action3: TAction;
    Action4: TAction;
    Action5: TAction;
    ToolBar2: TToolBar;
    btnClose: TToolButton;
    ToolButton4: TToolButton;
    btnClass: TToolButton;
    ToolButton10: TToolButton;
    pnlTools: TPanel;
    btnTools: TToolButton;
    ImageList2: TImageList;
    ToolBar1: TToolBar;
    ToolButton1: TToolButton;
    ToolButton3: TToolButton;
    ToolButton6: TToolButton;
    ToolButton7: TToolButton;
    ToolButton8: TToolButton;
    btnFindFirst: TToolButton;
    procedure pntTeacherPaint(Sender: TObject);
    procedure mnuCloseClick(Sender: TObject);
    procedure pntTeacherMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure lstTeacherClick(Sender: TObject);
    procedure pntTeacherMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure mnuFind4and5Click(Sender: TObject);
    procedure mnuFind3ContClick(Sender: TObject);
    procedure mnuFindMultiClick(Sender: TObject);
    procedure mnuFindOver5Click(Sender: TObject);
    procedure mnuClassClick(Sender: TObject);
    procedure mnuFindFirstClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure mnuTools(Sender: TObject);
    procedure btnToolsClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure RefreshTeachers();
    procedure SetTeacherNo( idx: Integer );
  end;

var
  frmPersonal: TfrmPersonal;

implementation

{$R *.DFM}

uses
    Global, f_Change, f_SClass;

var
  icurWork: Integer;
  mState: Boolean;
  mStartW, mStartN: integer;
  curMouseW, curMouseN: word;
  DispTeacher: integer;


(***********************************
  지정된 위치에 클래스 출력
************************************)
procedure DispClassData( hDC: HDC; w, n: integer );
var
  px, py: integer;
  Rect: TRECT;
  TempNum, TempNum2: integer;
  TempType: byte;
  TempStr: string;
  StrData: array[0..255] of char;
  tc: TColor;
  hOldBrush, hNewBrush: HBRUSH;
  hOldPen, hNewPen: HPEN;

begin
  px := (w - 1) * (GrdSizeX + 1) + GrdStartX + 2;
  py := (n - 1) * (GrdSizeY + 1) + GrdStartY + 2;
  Rect.Top := py;
  Rect.Left := px;
  Rect.Bottom := py + GrdSizeY;
  Rect.Right := px + GrdSizeX;

  TempNum := GetClassNo( DispTeacher, w, n );
  TempNum2 := GetClassNo2( DispTeacher, w, n );
  TempType := GetClassType( DispTeacher, w, n );

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
  SetBkColor( hDC, tc );

  FillRect( hDC, Rect, hNewBrush );

  Case TempType of
    CT_NORMAL, CT_FIXED:
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

  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
  SelectObject( hDC, hOldBrush );
  DeleteObject( hNewBrush );
end;


(***********************************

************************************)
procedure TfrmPersonal.SetTeacherNo( idx: Integer );
begin
    if idx <= TeacherCount then begin
      lstTeacher.ItemIndex := idx - 1;
      lstTeacherClick(lstTeacher);
    end;
end;


(***********************************

************************************)
procedure TfrmPersonal.RefreshTeachers();
var
    i: integer;
    tt: PTeacherData;
begin
    // 교사 데이터
    lstTeacher.Items.BeginUpdate();
    lstTeacher.Items.Clear();
    tt := pTeachers;
    for i := 1 to TeacherCount do begin
      lstTeacher.Items.Add( tt^.TeacherName );
      inc( tt );
    end;
    lstTeacher.Items.EndUpdate();
end;


procedure TfrmPersonal.FormShow(Sender: TObject);
begin
//
end;


procedure TfrmPersonal.pntTeacherPaint(Sender: TObject);
var
    pnt: TPaintBox;
    dc: HDC;
    i, j: integer;
    Rect: TRect;
    StrData: array [0..255] of char;
    hOldPen, hNewPen1, hNewPen2: HPEN;
    hOldFont, hSFont: HFONT;

begin
    if DispTeacher = 0 then Exit;

    pnt := TPaintBox(Sender);
    dc := pnt.Canvas.Handle;

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
  
    SelectObject( dc, hOldPen );
    DeleteObject( hNewPen1 );
    DeleteObject( hNewPen2 );
  
    (* 데이터 표시 *)
    for i := MON to SAT do
      for j := 1 to 8 do
        DispClassData( dc, i, j );
end;

procedure TfrmPersonal.mnuCloseClick(Sender: TObject);
begin
    Close();
end;

procedure TfrmPersonal.pntTeacherMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  xx, yy: integer;
  t2, t3: integer;
  cnf, cnf2, cnt, cnt2: word;
  ct: byte;
  tt: PTeacherData;
  info: word;
  TempStr: string;

begin
  if Button = mbLeft then begin
    if (X > GrdStartX) and (Y > GrdStartY) then begin
      xx := (X - GrdStartX - 2) div (GrdSizeX + 1) + 1;
      yy := (Y - GrdStartY - 2) div (GrdSizeY + 1) + 1;

      if (xx <= SAT) and (yy <= 8) then begin
        tt := PTeachers;
        case iCurWork of
          (* 정보 *)
          0: if (GetClassType( DispTeacher, xx, yy ) <> CT_SPECIAL) and
                (GetClassNo( DispTeacher, xx, yy ) > 0) then begin
               inc( tt, DispTeacher - 1 );
               info := GetClassInfo( DispTeacher, xx, yy );
               cnf := info div 10;
               cnt := info mod 10;
               TempStr := tt^.TeacherName + '(' + tt^.Subject[cnf, cnt].Name + ') : ';
               TempStr := TempStr + IntToStr(cnf) + '-' + IntToStr(tt^.Subject[cnf, cnt].StartClass) + ' ~ ';
               TempStr := TempStr + IntToStr(cnf) + '-' + IntToStr(tt^.Subject[cnf, cnt].EndClass);
               edtInfo.Text := TempStr;
             end;
          (* 옮기기 *)
          1: if (GetClassType(DispTeacher, xx, yy) = CT_NORMAL) then begin
               if not mState then begin
                 if GetClassNo(DispTeacher, xx, yy) > 0 then begin
                   mStartW := xx;
                   mStartN := yy;
                   inc( tt, DispTeacher - 1 );
                   TempStr := tt^.TeacherName + ' : ' + WeekStr[xx] + '요일 ' + IntToStr(yy) + '교시 => ';
                   edtInfo.Text := TempStr;
                   pntTeacher.Cursor := crDrag;
                   mState := True;
                 end;
               end else begin
                 if (yy <> mStartN) or (xx <> mStartW) then begin
                   if CanItChange( DispTeacher, mStartW, mStartN, xx, yy ) then begin
                     ChangeT := DispTeacher;
                     ChangeSW := mStartW;
                     ChangeSN := mStartN;
                     ChangeEW := xx;
                     ChangeEN := yy;
                     ChangeType := 1;
                     frmChange.ShowModal;
                   end;

                   pntTeacher.Refresh();

                   edtInfo.Text := edtInfo.Text + WeekStr[xx] + '요일 ' + IntToStr(yy) + '교시';

                   mState := False;
                   pntTeacher.Cursor := crDefault;
                 end;
               end;
             end;
          (* 고정/해제 *)
          2: if GetClassType( DispTeacher, xx, yy ) = CT_NORMAL then begin
               SetClassType( DispTeacher, xx, yy, CT_FIXED );
               DispClassData( pntTeacher.Canvas.Handle, xx, yy );
             end else if GetClassType( DispTeacher, xx, yy ) = CT_FIXED then begin
               SetClassType( DispTeacher, xx, yy, CT_NORMAL );
               DispClassData( pntTeacher.Canvas.Handle, xx, yy );
             end;
          (* 힙반처리 *)
          3: if (GetClassType(DispTeacher, xx, yy) = CT_NORMAL) and
                (GetClassNo(DispTeacher, xx, yy) > 0) and
                (GetClassNo2(DispTeacher, xx, yy) = 0) then begin
               if not mState then begin
                 mStartW := xx;
                 mStartN := yy;
                 inc( tt, DispTeacher - 1 );
                 TempStr := tt^.TeacherName + ' : ' + WeekStr[xx] + '요일 ' + IntToStr(yy) + '교시 + ';
                 edtInfo.Text := TempStr;
                 pntTeacher.Cursor := crDrag;
                 mState := True;
               end else begin
                 if (yy <> mStartN) or (xx <> mStartW) then begin
                   if CanItMulti( DispTeacher, mStartW, mStartN, xx, yy ) then begin
                     ChangeT := DispTeacher;
                     ChangeSW := mStartW;
                     ChangeSN := mStartN;
                     ChangeEW := xx;
                     ChangeEN := yy;
                     ChangeType := 2;
                     frmChange.ShowModal;
                   end;

                   pntTeacher.Refresh();

                   edtInfo.Text := edtInfo.Text + WeekStr[xx] + '요일 ' + IntToStr(yy) + '교시';

                   mState := False;
                   pntTeacher.Cursor := crDefault;
                 end;
               end;
             end;
          (* 힙반해제 *)
          4: if (GetClassType(DispTeacher, xx, yy) = CT_NORMAL) then begin
               if not mState then begin
                 if (GetClassNo(DispTeacher, xx, yy) > 0) and
                    (GetClassNo2(DispTeacher, xx, yy) > 0) then begin
                   mStartW := xx;
                   mStartN := yy;
                   inc( tt, DispTeacher - 1 );
                   TempStr := tt^.TeacherName + ' : ' + WeekStr[xx] + '요일 ' + IntToStr(yy) + '교시 => ';
                   edtInfo.Text := TempStr;
                   pntTeacher.Cursor := crDrag;
                   mState := True;
                 end;
               end else begin
                 if (yy <> mStartN) or (xx <> mStartW) then begin
                   if CanItRelease( DispTeacher, mStartW, mStartN, xx, yy ) then begin
                     ChangeT := DispTeacher;
                     ChangeSW := mStartW;
                     ChangeSN := mStartN;
                     ChangeEW := xx;
                     ChangeEN := yy;
                     ChangeType := 3;
                     frmChange.ShowModal;
                   end;

                   pntTeacher.Refresh();

                   edtInfo.Text := edtInfo.Text + WeekStr[curWeek] + '요일 ' + IntToStr(yy) + '교시';

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
  end;
end;


procedure TfrmPersonal.lstTeacherClick(Sender: TObject);
begin
  DispTeacher := lstTeacher.ItemIndex + 1;
  mState := False;

  pntTeacher.Refresh();
end;


procedure TfrmPersonal.pntTeacherMouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
var
  ww, nn: word;

begin
  if mState then begin
    if (X > GrdStartX) and (Y > GrdStartY) then begin
      ww := (X - GrdStartX - 2) div (GrdSizeX + 1) + 1;
      nn := (Y - GrdStartY - 2) div (GrdSizeY + 1) + 1;

      if (ww <> curMouseW) or (nn <> curMouseN) then begin
        if (ww <= SAT) and (nn <= 8) then begin
          case iCurWork of
            1 : if CanItChange( DispTeacher, mStartW, mStartN, ww, nn ) then
                  pntTeacher.Cursor := crMultiDrag
                else
                  pntTeacher.Cursor := crDrag;
            3 : if CanItMulti( DispTeacher, mStartW, mStartN, ww, nn ) then
                  pntTeacher.Cursor := crMultiDrag
                else
                  pntTeacher.Cursor := crDrag;
            4 : if CanItRelease( DispTeacher, mStartW, mStartN, ww, nn ) then
                  pntTeacher.Cursor := crMultiDrag
                else
                  pntTeacher.Cursor := crDrag;
          end;
        end else pntTeacher.Cursor := crNoDrop;
        curMouseW := ww;
        curMouseN := nn;
      end;
    end else pntTeacher.Cursor := crNoDrop;
  end;
end;

procedure TfrmPersonal.mnuFindFirstClick(Sender: TObject);
var
    b: boolean;
begin
    b := not mnuFindFirst.Checked;
    mnuFindFirst.Checked := b;
    btnFindFirst.Down := b;
end;

procedure TfrmPersonal.mnuFind4and5Click(Sender: TObject);
label
  ExitSub;

var
  t, sn, w: integer;
  ts: PScheduleData;

begin
  ts := PSchedules;

  if mnuFindFirst.Checked then
    sn := 1
  else begin
    sn := lstTeacher.ItemIndex + 2;
    inc( ts, sn - 1 );
  end;

  for t := sn to TeacherCount do begin
    for w := MON to SAT do begin
      if (ts^[w, gSchool.LunchTime].ClassType in [CT_NORMAL, CT_FIXED]) and
         (ts^[w, gSchool.LunchTime].ClassNo > 0) and
         (ts^[w, gSchool.LunchTime+1].ClassType in [CT_NORMAL, CT_FIXED]) and
         (ts^[w, gSchool.LunchTime+1].ClassNo > 0) then begin
        lstTeacher.ItemIndex := t - 1;
        lstTeacherClick(lstTeacher);
        goto ExitSub;
      end;
    end;
    inc( ts );
  end;

  MessageDlg( '점심시간 전후로 인접한 교사는 없습니다.', mtInformation, [mbOk], 0 );

  ExitSub:
end;

procedure TfrmPersonal.mnuFind3ContClick(Sender: TObject);
label
  ExitSub;

var
  t, sn, w, n, cc: integer;
  ts: PScheduleData;

begin
  ts := PSchedules;

  if mnuFindFirst.Checked then
    sn := 1
  else begin
    sn := lstTeacher.ItemIndex + 2;
    inc( ts, sn - 1 );
  end;

  for t := sn to TeacherCount do begin
    for w := MON to SAT do begin
      cc := 0;
      for n := 1 to 8 do begin
        if (ts^[w, n].ClassType in [CT_NORMAL, CT_FIXED]) and
           (ts^[w, n].ClassNo > 0) then begin
          inc( cc );
          if cc >= 3 then begin
            lstTeacher.ItemIndex := t - 1;
            lstTeacherClick(lstTeacher);
            goto ExitSub;
          end;
        end else
          cc := 0;
      end;
    end;
    inc( ts );
  end;

  MessageDlg( '3교시가 연속된 교사는 없습니다.', mtInformation, [mbOk], 0 );

  ExitSub:
end;

procedure TfrmPersonal.mnuFindMultiClick(Sender: TObject);
var
  t, sn, w, n, n2, tc: integer;
  ts: PScheduleData;

begin
  ts := PSchedules;

  if mnuFindFirst.Checked then
    sn := 1
  else begin
    sn := lstTeacher.ItemIndex + 2;
    inc( ts, sn - 1 );
  end;

  for t := sn to TeacherCount do begin
    for w := MON to SAT do begin
      for n := 1 to 8 do begin
        if ts^[w, n].ClassType in [CT_NORMAL, CT_FIXED] then begin
          tc := ts^[w, n].ClassNo;
          if tc > 0 then
            for n2 := 1 to 8 do begin
              if (n2 <> n) and (ts^[w, n2].ClassType in [CT_NORMAL, CT_FIXED]) and
                 ((tc = ts^[w, n2].ClassNo) or (tc = ts^[w, n2].ClassNo2)) then begin
                lstTeacher.ItemIndex := t - 1;
                lstTeacherClick(lstTeacher);
                Exit;
              end;
            end;

          tc := ts^[w, n].ClassNo2;
          if tc > 0 then
            for n2 := 1 to 8 do begin
              if (n2 <> n) and (ts^[w, n2].ClassType in [CT_NORMAL, CT_FIXED]) and
                 ((tc = ts^[w, n2].ClassNo) or (tc = ts^[w, n2].ClassNo2)) then begin
                lstTeacher.ItemIndex := t - 1;
                lstTeacherClick(lstTeacher);
                Exit;
              end;
            end;
        end;
      end;
    end;
    inc( ts );
  end;

  MessageDlg( '같은 반이 중복된 교사는 없습니다.', mtInformation, [mbOk], 0 );
end;

procedure TfrmPersonal.mnuFindOver5Click(Sender: TObject);
var
  t, sn, w, n, cc: integer;
  ts: PScheduleData;

begin
  ts := PSchedules;

  if mnuFindFirst.Checked then
    sn := 1
  else begin
    sn := lstTeacher.ItemIndex + 2;
    inc( ts, sn - 1 );
  end;

  for t := sn to TeacherCount do begin
    for w := MON to SAT do begin
      cc := 0;
      for n := 1 to 8 do begin
        if (ts^[w, n].ClassType in [CT_NORMAL, CT_FIXED]) and
           (ts^[w, n].ClassNo > 0) then begin
          inc( cc );
          if cc >= 5 then begin
            lstTeacher.ItemIndex := t - 1;
            lstTeacherClick(lstTeacher);
            Exit;
          end;
        end;
      end;
    end;
    inc( ts );
  end;

  MessageDlg( '하루 5시간 이상 수업하는 교사는 없습니다.', mtInformation, [mbOk], 0 );
end;


procedure TfrmPersonal.mnuClassClick(Sender: TObject);
begin
  frmClass.ShowModal();
end;


procedure TfrmPersonal.mnuTools(Sender: TObject);
begin
  if mState then begin
    pntTeacher.Cursor := crDefault;
    mState := False;
  end;

  TAction(Sender).Checked := True;
  iCurWork := TAction(Sender).Tag;
  pnlTools.Caption := TAction(Sender).Caption;
end;

procedure TfrmPersonal.btnToolsClick(Sender: TObject);
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

end.
