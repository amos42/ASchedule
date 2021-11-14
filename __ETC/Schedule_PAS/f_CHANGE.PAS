unit f_CHANGE;

interface

uses WinTypes, WinProcs, SysUtils, Classes, Graphics, Forms, Controls, Buttons,
     StdCtrls, ExtCtrls;

const
  MAXCHANGE = 50;

type
  TfrmChange = class(TForm)
    OKBtn: TBitBtn;
    CancelBtn: TBitBtn;
    procedure OKBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure CancelBtnClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmChange: TfrmChange;
  ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN: word;
  ChangeCount: word;
  ChangeType: word;
  IsAddList: boolean;

function CanItChange( t, sw, sn, ew, en: word ): boolean;
function CanItMulti( t, sw, sn, ew, en: word ): boolean;
function CanItRelease( t, sw, sn, ew, en: word ): boolean;

implementation

{$R *.DFM}

uses
    Global, f_Sview;

type
  TViewList = record
    TeacherNo: word;
    StartW, EndW: word;
    StartN, EndN: word;
    frmView: TfrmView;
  end;

var
  ViewList: array [1..MAXCHANGE] of TViewList;


(*************************
  뷰리스트를 하나 추가한다.
**************************)
procedure AddChangeList( t, sw, sn, ew, en: word );
var
  tv, tvo: ^TfrmView;
  ts: PScheduleData;
  tt: PTeacherData;
  temp: word;

begin
  ViewList[ChangeCount].TeacherNo := t;

  ViewList[ChangeCount].StartW := sw;
  ViewList[ChangeCount].StartN := sn;
  ViewList[ChangeCount].EndW := ew;
  ViewList[ChangeCount].EndN := en;

  ViewList[ChangeCount].frmView := TfrmView.Create(frmChange);
  tv := @ViewList[ChangeCount].frmView;
  if ChangeCount = 1 then begin
    tv^.Top := 0;
    tv^.Left := 0;
  end else begin
    tvo := @ViewList[ChangeCount - 1].frmView;
    tv^.Top := tvo^.Top;
    tv^.Left := tvo^.Left + tvo^.Width;
    if tv^.Left + tv^.Width > Screen.Width then begin
      tv^.Left := 0;
      tv^.Top := tvo^.Top + tvo^.Height;
    end;
  end;

  tv^.ViewTeacher := t;
  tv^.StartPos.w := sw; tv^.StartPos.t := sn;
  tv^.EndPos.w := ew;   tv^.EndPos.t := en;

  ts := pWorkSchedules;  // 작업하고 있던 것을 보여준다.
  inc( ts, t - 1 );
  tv^.ViewData := ts^;

  tt := pTeachers;
  inc( tt, t - 1 );
  tv^.Caption := IntToStr(ChangeCount) + '번째 : ' + tt^.TeacherName;

  if tv^.ViewData[sw, sn].ClassNo > 0 then begin
    Temp := tv^.ViewData[sw, sn].ClassInfo;
    tv^.Change1 := WeekStr[sw] + IntToStr(sn) + #13
                 + tt^.Subject[Temp div 10, Temp mod 10].Name;
  end else
    tv^.Change1 := '';

  if tv^.ViewData[ew, en].ClassNo > 0 then begin
    Temp := tv^.ViewData[ew, en].ClassInfo;
    tv^.Change2 := WeekStr[ew] + IntToStr(en) + #13
                 + tt^.Subject[Temp div 10, Temp mod 10].Name;
  end else
    tv^.Change2 := '';
end;

(*********************
  한 노드를 이동한다.
**********************)
function ChangeScheduleNode( t, sw, sn, ew, en: word ): boolean;
var
  i: integer;
  ts: PScheduleData;
  c1, c2: TScheduleDataCell;
  t1, t2: word;
  y1, y2: word;

begin
  Result := False;

  inc( ChangeCount );
  if ChangeCount <= gConfig.MaxChangeCount then begin
    SwapClass( t, sw, sn, ew, en );
    if isAddList then AddChangeList( t, sw, sn, ew, en );

    ts := pCurSchedules;
    inc( ts, t - 1 );
    c1 := ts^[sw, sn];
    c2 := ts^[ew, en];

    if c1.ClassNo > 0 then begin
      y1 := c1.ClassNo div 100;
      for i := 1 to gSchool.SPC_Count do begin
        if ((gSchool.SPC[i].Years and SPC_CLASSES[y1]) <> 0) and
           (gSchool.SPC[i].Pos[y1].w = sw) and (gSchool.SPC[i].Pos[y1].t = sn) then Exit;
      end;
    end;
    if c2.ClassNo > 0 then begin
      y2 := c2.ClassNo div 100;
      for i := 1 to gSchool.SPC_Count do begin
        if ((gSchool.SPC[i].Years and SPC_CLASSES[y2]) <> 0) and
           (gSchool.SPC[i].Pos[y2].w = ew) and (gSchool.SPC[i].Pos[y2].t = en) then Exit;
      end;
    end;

    if (c1.ClassType = CT_NORMAL) and (c2.ClassType = CT_NORMAL) then begin
      if c1.ClassNo > 0 then begin
        if sn <= gSchool.WeekLimit[c1.ClassNo div 100, sw] then begin
          t1 := GetClassMulti( t, sw, sn, c1.ClassNo );
          if (t1 > 0) and (t1 <= 1000) then begin
            Result := ChangeScheduleNode( t1, sw, sn, ew, en );
            if not Result then Exit;
          end else
            Result := True;
        end else begin
          Result := False;
          Exit;
        end;
      end;
      if c1.ClassNo2 > 0 then begin
        if sn <= gSchool.WeekLimit[c1.ClassNo2 div 100, sw] then begin
          t1 := GetClassMulti( t, sw, sn, c1.ClassNo2 );
          if (t1 > 0) and (t1 <= 1000) then begin
            Result := ChangeScheduleNode( t1, sw, sn, ew, en );
            if not Result then Exit;
          end else
            Result := True;
        end else begin
          Result := False;
          Exit;
        end;
      end;
      if c2.ClassNo > 0 then begin
        if en <= gSchool.WeekLimit[c2.ClassNo div 100, ew] then begin
          t2 := GetClassMulti( t, ew, en, c2.ClassNo );
          if (t2 > 0) and (t2 <= 1000) then begin
            Result := ChangeScheduleNode( t2, ew, en, sw, sn );
            if not Result then Exit;
          end else
            Result := True;
        end else begin
          Result := False;
          Exit;
        end;
      end;
      if c2.ClassNo2 > 0 then begin
        if en <= gSchool.WeekLimit[c2.ClassNo2 div 100, ew] then begin
          t2 := GetClassMulti( t, ew, en, c2.ClassNo2 );
          if (t2 > 0) and (t2 <= 1000) then begin
            Result := ChangeScheduleNode( t2, ew, en, sw, sn );
            if not Result then Exit;
          end else
            Result := True;
        end else begin
          Result := False;
          Exit;
        end;
      end;
    end;
  end;
end;


(**********************************
  옮겨지는 것이 가능한 가를 살핀다.
***********************************)
function CanItChange( t, sw, sn, ew, en: word ): boolean;
var
  ts: PScheduleData;
  y: word;
  c1, c12, c2, c22: word;

begin
  ts := pSchedules;
  inc( ts, t - 1 );
  c1 := ts^[sw, sn].ClassNo;
  c12 := ts^[sw, sn].ClassNo2;
  c2 := ts^[ew, en].ClassNo;
  c22 := ts^[ew, en].ClassNo2;

  if ((c1 <> c2) or ((c1 = c2) and (ts^[sw, sn].ClassInfo <> ts^[ew, en].ClassInfo))) and
     ((c1 = 0) or (c1 <> c22)) and
     ((c2 = 0) or (c2 <> c12)) and
     ((c12 = 0) or (c12 <> c22)) then begin
    ChangeCount := 0;

    CopyToWorkSchedules();

    SetCurSchedules( 1 );
    Result := ChangeScheduleNode( t, sw, sn, ew, en );
    SetCurSchedules( 0 );
  end else
    Result := False;
end;


(***************************
  합반이 가능한 가를 살핀다.
****************************)
function CanItMulti( t, sw, sn, ew, en: word ): boolean;
var
  ts: PScheduleData;
  i, y: word;

begin
  ChangeCount := 0;

  ts := pSchedules;
  inc( ts, t -1 );
  if (ts^[sw, sn].ClassNo <> ts^[ew, en].ClassNo) and
     (ts^[sw, sn].ClassNo2 = 0) and (ts^[ew, en].ClassNo2 = 0) and
     (ts^[sw, sn].ClassInfo = ts^[ew, en].ClassInfo) then begin
    // 데이터 구조체 초기화
    CopyToWorkSchedules();

    (* 미리 하나는 바꾸어 놓음 *)
    ts := pWorkSchedules;
    inc( ts, t - 1 );
    ts^[sw, sn].ClassNo2 := ts^[sw, sn].ClassNo;
    ts^[sw, sn].ClassNo := ts^[ew, en].ClassNo;
    ts^[ew, en].ClassNo := 0;

    SetCurSchedules( 1 );
    Result := ChangeScheduleNode( t, sw, sn, ew, en );
    SetCurSchedules( 0);
  end else
    Result := False;
end;


(***************************
  합반해제가 가능한 가를 살핀다.
****************************)
function CanItRelease( t, sw, sn, ew, en: word ): boolean;
var
  ts: PScheduleData;

begin
  ChangeCount := 0;

  ts := pSchedules;
  inc( ts, t - 1 );
  if (ts^[sw, sn].ClassNo > 0) and (ts^[sw, sn].ClassNo2 > 0) and
     (ts^[ew, en].ClassNo = 0) then begin
    (* 데이터 구조체 초기화 *)
    CopyToWorkSchedules();

    (* 미리 하나는 바꾸어 놓음 *)
    ts := pWorkSchedules;
    inc( ts, t - 1 );
    ts^[ew, en].ClassNo := ts^[sw, sn].ClassNo;
    ts^[sw, sn].ClassNo := ts^[sw, sn].ClassNo2;
    ts^[sw, sn].ClassNo2 := 0;

    SetCurSchedules( 1 );
    Result := ChangeScheduleNode( t, sw, sn, ew, en );
    SetCurSchedules( 0);
  end else
    Result := False;
end;


procedure TfrmChange.FormCreate(Sender: TObject);
begin
  ChangeCount := 0;
  IsAddList := False;
  ChangeType := 0;
end;


procedure TfrmChange.FormShow(Sender: TObject);
var
  i: word;
  tv: ^TfrmView;
  r: boolean;

begin
  if ChangeType > 0 then begin
    IsAddList := True;
    case ChangeType of
      1: r := CanItChange( ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN );
      2: r := CanItMulti( ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN );
      3: r := CanItRelease( ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN );
      else r := False;
    end;
    if r then begin
      for i := 1 to ChangeCount do begin
        ViewList[i].frmView.Show;
{        frmChange.Top := ViewList[ChangeCount].frmView.Top + ViewList[ChangeCount].frmView.Height + 1;
        frmChange.Left := ViewList[ChangeCount].frmView.Left;}
      end;
    end;
    IsAddList := False;
    ChangeType := 0;
  end;
end;


procedure TfrmChange.OKBtnClick(Sender: TObject);
begin
    CopyFromWorkSchedules();
    Close();
end;


procedure TfrmChange.CancelBtnClick(Sender: TObject);
begin
    Close();
end;


procedure TfrmChange.FormClose(Sender: TObject; var Action: TCloseAction);
var
  i: integer;

begin
  for i := 1 to ChangeCount do
    ViewList[i].frmView.Destroy();

  ChangeCount := 0;
end;


end.
