unit f_TEACHER;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, DBCtrls, DBTables, DB, Grids,
  StdCtrls, Buttons, Mask, Menus, TabNotBk,
  DBGrids, DBLookup, ComCtrls;

type
  TfrmTeacher = class(TForm)
    btnClose: TBitBtn;
    pnlTotalAll: TPanel;
    btnAdd: TSpeedButton;
    btnDelete: TSpeedButton;
    btnModify: TSpeedButton;
    pnlTeacherInfo: TPanel;
    edtTeacher: TEdit;
    Label38: TLabel;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    edtSubject1_1: TEdit;
    edtStart1_1: TEdit;
    edtSubject1_2: TEdit;
    edtStart1_2: TEdit;
    edtSubject1_3: TEdit;
    edtStart1_3: TEdit;
    edtEnd1_1: TEdit;
    edtEnd1_2: TEdit;
    edtEnd1_3: TEdit;
    edtTimes1_1: TEdit;
    edtTimes1_2: TEdit;
    edtTimes1_3: TEdit;
    GroupBox2: TGroupBox;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    edtSubject2_1: TEdit;
    edtStart2_1: TEdit;
    edtSubject2_2: TEdit;
    edtStart2_2: TEdit;
    edtSubject2_3: TEdit;
    edtStart2_3: TEdit;
    edtEnd2_1: TEdit;
    edtEnd2_2: TEdit;
    edtEnd2_3: TEdit;
    edtTimes2_1: TEdit;
    edtTimes2_2: TEdit;
    edtTimes2_3: TEdit;
    GroupBox3: TGroupBox;
    Label25: TLabel;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    Label29: TLabel;
    Label30: TLabel;
    Label31: TLabel;
    Label32: TLabel;
    Label33: TLabel;
    Label34: TLabel;
    Label35: TLabel;
    Label36: TLabel;
    edtSubject3_1: TEdit;
    edtStart3_1: TEdit;
    edtSubject3_2: TEdit;
    edtStart3_2: TEdit;
    edtSubject3_3: TEdit;
    edtStart3_3: TEdit;
    edtEnd3_1: TEdit;
    edtEnd3_2: TEdit;
    edtEnd3_3: TEdit;
    edtTimes3_1: TEdit;
    edtTimes3_2: TEdit;
    edtTimes3_3: TEdit;
    pnlTotal: TPanel;
    Label37: TLabel;
    Label39: TLabel;
    pnlTeachers: TPanel;
    btnItemUp: TSpeedButton;
    btnItemDown: TSpeedButton;
    lvTeachers: TListView;
    pnlTeacherNo: TPanel;
    Label40: TLabel;
    Label41: TLabel;
    Label42: TLabel;
    Label43: TLabel;
    edtSubject1_4: TEdit;
    edtStart1_4: TEdit;
    edtEnd1_4: TEdit;
    edtTimes1_4: TEdit;
    Label44: TLabel;
    Label45: TLabel;
    Label46: TLabel;
    Label47: TLabel;
    edtSubject2_4: TEdit;
    edtStart2_4: TEdit;
    edtEnd2_4: TEdit;
    edtTimes2_4: TEdit;
    Label48: TLabel;
    Label49: TLabel;
    Label50: TLabel;
    Label51: TLabel;
    edtSubject3_4: TEdit;
    edtStart3_4: TEdit;
    edtEnd3_4: TEdit;
    edtTimes3_4: TEdit;
    procedure DBEditChange(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
    procedure lvTeachersSelectItem(Sender: TObject; Item: TListItem;
      Selected: Boolean);
    procedure FormCreate(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnItemUpClick(Sender: TObject);
    procedure btnItemDownClick(Sender: TObject);
    procedure btnModifyClick(Sender: TObject);
  private
    { Private declarations }
    procedure EnableItems( tf: boolean );
  public
    { Public declarations }
  end;

var
  frmTeacher: TfrmTeacher;

implementation

{$R *.DFM}

uses
    Global;

var
    edtSubject: array [1..3, 1..MAX_TEACHER_SUBJECT] of TEdit;
    edtStartClass: array[1..3, 1..MAX_TEACHER_SUBJECT] of TEdit;
    edtEndClass: array[1..3, 1..MAX_TEACHER_SUBJECT] of TEdit;
    edtTimes: array[1..3, 1..MAX_TEACHER_SUBJECT] of TEdit;

procedure TfrmTeacher.EnableItems( tf: boolean );
var
    i, j: integer;
    tc: TColor;

begin
    pnlTeacherInfo.Enabled := tf;

    if tf then
      tc := clWindow
    else
      tc := clBtnFace;

    edtTeacher.Color := tc;
    for i := 1 to 3 do begin
      for j := 1 to MAX_TEACHER_SUBJECT do begin
        edtSubject[i,j].Color := tc;
        edtStartClass[i,j].Color := tc;
        edtEndClass[i,j].Color := tc;
        edtTimes[i,j].Color := tc;
      end;
    end;
end;

procedure TfrmTeacher.FormCreate(Sender: TObject);
var
    i, j: integer;
begin
    for i := 1 to 3 do begin
      for j := 1 to MAX_TEACHER_SUBJECT do begin
        edtSubject[i,j] := TEdit(Self.FindComponent(Format('edtSubject%d_%d',[i,j])));
        edtStartClass[i,j] := TEdit(Self.FindComponent(Format('edtStart%d_%d',[i,j])));
        edtEndClass[i,j] := TEdit(Self.FindComponent(Format('edtEnd%d_%d',[i,j])));
        edtTimes[i,j] := TEdit(Self.FindComponent(Format('edtTimes%d_%d',[i,j])));
      end;
    end;
end;

procedure TfrmTeacher.FormShow(Sender: TObject);
var
  i, j: integer;
  tt: PTeacherData;
  li: TListItem;
  tc: TColor;
begin
    // 교사 데이터
    lvTeachers.Items.BeginUpdate();
    lvTeachers.Items.Clear();
    tt := PTeachers;
    for i := 1 to TeacherCount do begin
      li := lvTeachers.Items.Add();
      li.Caption := tt^.TeacherName;
      inc( tt );
    end;
    lvTeachers.Items.EndUpdate();

    btnAdd.Enabled := True;
    if TeacherCount > 0 then begin
      btnDelete.Enabled := True;
      btnModify.Enabled := True;
    end else begin
      btnDelete.Enabled := False;
      btnModify.Enabled := False;
    end;
    btnModify.Caption := '편집';
    btnModify.Tag := 0;
    pnlTeachers.Enabled := true;
    lvTeachers.Color := clWindow;

    pnlTotalAll.Caption := IntToStr( GetTotalTeacherTimes() );
    pnlTeacherNo.Caption := '0 / ' + IntToStr(TeacherCount);

    EnableItems( false );
end;

procedure TfrmTeacher.FormClose(Sender: TObject; var Action: TCloseAction);
begin
    SetCurSchedules( 0 );
end;

procedure TfrmTeacher.DBEditChange(Sender: TObject);
var
  i, j, k: integer;
  Total: integer;
  tt: PTeacherData;

begin
  ToTal := 0;

  if (edtSubject1_1.Text <> '') and (edtStart1_1.Text <> '') and (edtEnd1_1.Text <> '') and (edtTimes1_1.Text <> '') then
    Total := ToTal + (StrToInt(edtEnd1_1.Text) - StrToInt(edtStart1_1.Text) + 1) * StrToInt(edtTimes1_1.Text);
  if (edtSubject1_2.Text <> '') and (edtStart1_2.Text <> '') and (edtEnd1_2.Text <> '') and (edtTimes1_2.Text <> '') then
    Total := Total + (StrToInt(edtEnd1_2.Text) - StrToInt(edtStart1_2.Text) + 1) * StrToInt(edtTimes1_2.Text);
  if (edtSubject1_3.Text <> '') and (edtStart1_3.Text <> '') and (edtEnd1_3.Text <> '') and (edtTimes1_3.Text <> '') then
    Total := Total + (StrToInt(edtEnd1_3.Text) - StrToInt(edtStart1_3.Text) + 1) * StrToInt(edtTimes1_3.Text);
  if (edtSubject1_4.Text <> '') and (edtStart1_4.Text <> '') and (edtEnd1_4.Text <> '') and (edtTimes1_4.Text <> '') then
    Total := Total + (StrToInt(edtEnd1_4.Text) - StrToInt(edtStart1_4.Text) + 1) * StrToInt(edtTimes1_4.Text);

  if (edtSubject2_1.Text <> '') and (edtStart2_1.Text <> '') and (edtEnd2_1.Text <> '') and (edtTimes2_1.Text <> '') then
    Total := Total + (StrToInt(edtEnd2_1.Text) - StrToInt(edtStart2_1.Text) + 1) * StrToInt(edtTimes2_1.Text);
  if (edtSubject2_2.Text <> '') and (edtStart2_2.Text <> '') and (edtEnd2_2.Text <> '') and (edtTimes2_2.Text <> '') then
    Total := Total + (StrToInt(edtEnd2_2.Text) - StrToInt(edtStart2_2.Text) + 1) * StrToInt(edtTimes2_2.Text);
  if (edtSubject2_3.Text <> '') and (edtStart2_3.Text <> '') and (edtEnd2_3.Text <> '') and (edtTimes2_3.Text <> '') then
    Total := Total + (StrToInt(edtEnd2_3.Text) - StrToInt(edtStart2_3.Text) + 1) * StrToInt(edtTimes2_3.Text);
  if (edtSubject2_4.Text <> '') and (edtStart2_4.Text <> '') and (edtEnd2_4.Text <> '') and (edtTimes2_4.Text <> '') then
    Total := Total + (StrToInt(edtEnd2_4.Text) - StrToInt(edtStart2_4.Text) + 1) * StrToInt(edtTimes2_4.Text);

  if (edtSubject3_1.Text <> '') and (edtStart3_1.Text <> '') and (edtEnd3_1.Text <> '') and (edtTimes3_1.Text <> '') then
    Total := Total + (StrToInt(edtEnd3_1.Text) - StrToInt(edtStart3_1.Text) + 1) * StrToInt(edtTimes3_1.Text);
  if (edtSubject3_2.Text <> '') and (edtStart3_2.Text <> '') and (edtEnd3_2.Text <> '') and (edtTimes3_2.Text <> '') then
    Total := Total + (StrToInt(edtEnd3_2.Text) - StrToInt(edtStart3_2.Text) + 1) * StrToInt(edtTimes3_2.Text);
  if (edtSubject3_3.Text <> '') and (edtStart3_3.Text <> '') and (edtEnd3_3.Text <> '') and (edtTimes3_3.Text <> '') then
    Total := Total + (StrToInt(edtEnd3_3.Text) - StrToInt(edtStart3_3.Text) + 1) * StrToInt(edtTimes3_3.Text);
  if (edtSubject3_4.Text <> '') and (edtStart3_4.Text <> '') and (edtEnd3_4.Text <> '') and (edtTimes3_4.Text <> '') then
    Total := Total + (StrToInt(edtEnd3_4.Text) - StrToInt(edtStart3_4.Text) + 1) * StrToInt(edtTimes3_4.Text);

  pnlTotal.Caption := IntToStr( Total );
end;

procedure TfrmTeacher.lvTeachersSelectItem(Sender: TObject;
  Item: TListItem; Selected: Boolean);
var
    i, j: integer;
    tt: PTeacherData;
    li: TListItem;
begin
    if lvTeachers.Selected <> nil then begin
      tt := PTeachers;
      inc( tt, lvTeachers.Selected.Index );

      edtTeacher.Text := tt^.TeacherName;

      for i := 1 to 3 do begin
        for j := 1 to MAX_TEACHER_SUBJECT do begin
          edtSubject[i,j].Text := tt^.Subject[i,j].Name;
          edtStartClass[i,j].Text := IntToStr(tt^.Subject[i,j].StartClass);
          edtEndClass[i,j].Text := IntToStr(tt^.Subject[i,j].EndClass);
          edtTimes[i,j].Text := IntToStr(tt^.Subject[i,j].Times);
        end;
      end;

      pnlTeacherNo.Caption := IntToStr(lvTeachers.Selected.Index+1) + ' / ' + IntToStr(TeacherCount);

      btnDelete.Enabled := True;
      btnModify.Enabled := True;
      btnItemUp.Enabled := True;
      btnItemDown.Enabled := True;
    end else begin
      btnDelete.Enabled := False;
      btnModify.Enabled := False;
      btnItemUp.Enabled := False;
      btnItemDown.Enabled := False;
    end;
end;

procedure TfrmTeacher.btnAddClick(Sender: TObject);
var
    li: TListItem;
    tt: PTeacherData;
    ts: PScheduleData;

begin
    // 교사 하나 추가
    inc( TeacherCount );

    // 추가된만큼 메모리 재할당
    ReallocMem( pTeachers, Sizeof(TTeacherData) * TeacherCount );
    ReallocMem( pSchedules, Sizeof(TScheduleData) * TeacherCount );

    if pWorkSchedules <> nil then begin
      FreeMem( pWorkSchedules );
      pWorkSchedules := AllocMem( Sizeof(TScheduleData) * TeacherCount );
    end;

    tt := pTeachers;
    inc( tt, TeacherCount-1 );
    ZeroMemory( tt, sizeof(TTeacherData) );
    ts := pSchedules;
    inc( ts, TeacherCount-1 );
    ZeroMemory( ts, sizeof(TScheduleData) );

    li := lvTeachers.Items.Add();
    lvTeachers.Selected := li;
    li.MakeVisible(true);

    pnlTeacherNo.Caption := IntToStr(TeacherCount) + ' / ' + IntToStr(TeacherCount);

    btnModify.Click();
end;

procedure TfrmTeacher.btnDeleteClick(Sender: TObject);
var
    i, j : integer;
    ptr, tt, tt2 : PTeacherData;
begin
    if lvTeachers.Selected = nil then exit;

    if MessageDlg( '정말 삭제하시겠습니까?',
                   mtConfirmation, [mbYes, mbNo], 0 ) <> mrYes then begin
      Exit;
    end;

    i := lvTeachers.Selected.Index;

    ptr := AllocMem( Sizeof(TTeacherData) * (TeacherCount-1) );

    tt := PTeachers;
    CopyMemory( ptr, tt, i*sizeof(TTeacherData) );
    inc( tt, i + 1 );
    tt2 := ptr;
    inc( tt2, i );
    CopyMemory( tt2, tt, (TeacherCount-1-i)*sizeof(TTeacherData) );

    FreeMem( PTeachers );
    PTeachers := ptr;

    dec( TeacherCount );

    lvTeachers.DeleteSelected();

    edtTeacher.Text := '';
    for i := 1 to 3 do begin
      for j := 1 to MAX_TEACHER_SUBJECT do begin
        edtSubject[i,j].Text := '';
        edtStartClass[i,j].Text := '';
        edtEndClass[i,j].Text := '';
        edtTimes[i,j].Text := '';
      end;
    end;

    if pWorkSchedules <> nil then begin
      FreeMem( pWorkSchedules );
      if TeacherCount > 0 then
        pWorkSchedules := AllocMem( Sizeof(TScheduleData) * TeacherCount )
      else
        pWorkSchedules := nil;
    end;

    pnlTeacherNo.Caption := IntToStr(0) + ' / ' + IntToStr(TeacherCount);
    pnlTotalAll.Caption := IntToStr( GetTotalTeacherTimes() );
end;

procedure TfrmTeacher.btnItemUpClick(Sender: TObject);
var
    i: integer;
    tt, tt2: PTeacherData;
    tmp: TTeacherData;
    ss: string;
begin
    if lvTeachers.Selected = nil then exit;

    i := lvTeachers.Selected.Index;
    if i <= 0 then exit;

    tt := PTeachers;
    inc( tt, i );
    tt2 := PTeachers;
    inc( tt2, i-1 );

    tmp := tt^;
    tt^ := tt2^;
    tt2^ := tmp;

    ss := lvTeachers.Items[i].Caption;
    lvTeachers.Items[i].Caption := lvTeachers.Items[i-1].Caption;
    lvTeachers.Items[i-1].Caption := ss;

    lvTeachers.Selected := lvTeachers.Items[i-1];
end;

procedure TfrmTeacher.btnItemDownClick(Sender: TObject);
var
    i: integer;
    tt, tt2: PTeacherData;
    tmp: TTeacherData;
    ss: string;
begin
    if lvTeachers.Selected = nil then exit;

    i := lvTeachers.Selected.Index;
    if i >= lvTeachers.Items.Count-1 then exit;

    tt := PTeachers;
    inc( tt, i );
    tt2 := PTeachers;
    inc( tt2, i+1 );

    tmp := tt^;
    tt^ := tt2^;
    tt2^ := tmp;

    ss := lvTeachers.Items[i].Caption;
    lvTeachers.Items[i].Caption := lvTeachers.Items[i+1].Caption;
    lvTeachers.Items[i+1].Caption := ss;

    lvTeachers.Selected := lvTeachers.Items[i+1];
end;

procedure TfrmTeacher.btnModifyClick(Sender: TObject);
var
  i, j: integer;
  tt: PTeacherData;
  Total: Longint;
begin
    if btnModify.Tag = 0 then begin
      pnlTeachers.Enabled := false;
      lvTeachers.Color := clBtnFace;
      btnAdd.Enabled := false;
      btnDelete.Enabled := false;
      EnableItems( true );

      btnModify.Caption := '갱신';
      btnModify.Tag := 1;
    end else begin
      tt := pTeachers;
      inc( tt, lvTeachers.Selected.Index );

      StrPCopy(tt^.TeacherName, edtTeacher.Text);

      for i := 1 to 3 do begin
        for j := 1 to MAX_TEACHER_SUBJECT do begin
          StrPCopy( tt^.Subject[i,j].Name, edtSubject[i,j].Text );
          tt^.Subject[i,j].StartClass := StrToInt(edtStartClass[i,j].Text);
          tt^.Subject[i,j].EndClass   := StrToInt(edtEndClass[i,j].Text);
          tt^.Subject[i,j].Times      := StrToInt(edtTimes[i,j].Text) ;
        end;
      end;

      pnlTotalAll.Caption := IntToStr( GetTotalTeacherTimes() );

      lvTeachers.Selected.Caption := edtTeacher.Text;

      pnlTeachers.Enabled := true;
      lvTeachers.Color := clWindow;
      btnAdd.Enabled := true;
      btnDelete.Enabled := true;
      EnableItems( false );

      btnModify.Caption := '편집';
      btnModify.Tag := 0;
    end;
end;

end.

