unit Global;

interface

uses
  WinTypes, WinProcs, Graphics, SysUtils;

const
  MON = 1;
  TUE = 2;
  WED = 3;
  THU = 4;
  FRI = 5;
  SAT = 6;
  WeekStr: array [MON..SAT] of string = ('월', '화', '수', '목', '금', '토' );

  CT_NONE    = 0;
  CT_NORMAL  = 0;
  CT_FIXED   = 1;
  CT_SPECIAL = 2;
  CT_FOCUS   = 3;
  CT_ETC     = 4;
  CT_ETC2    = 5;

  // 한 교사당 최대 수업 갯수
  MAX_TEACHER_SUBJECT = 4;
  
  // 최대 특별 수업 갯수
  MAX_SPC_COUNT = 10;

  // 특별 수업 학년
  SPC_CLASS1 = $1;
  SPC_CLASS2 = $2;
  SPC_CLASS3 = $4;
  SPC_CLASSES: array[1..3] of byte = (
     SPC_CLASS1, SPC_CLASS2, SPC_CLASS3
  );

type
  // 환경 설정 데이터
  TConfigColors = record
    CellText, CellBackground, GridLine,
    SpecialCell, FixedCell, FocusCell,
    GrayCell,
    LunchTime : TColor;
  end;
  TConfig = record
    MaxChangeCount: Integer;
    Colors: TConfigColors;
  end;

  // 시간표 위치 구조체
  TClassPos = packed record
    w, t: Word;  // (요일, 교시)
  end;
  // 특별 수업
  TSpcClass = packed record
    Name: array[0..3] of char;
    Years: Word;
    Pos: array[1..3] of TClassPos;
  end;
  // 학교 데이터 옛날 버전 (ver 1)
  TSchoolData_ver1 = packed record
    ClassCount: array[1..3] of word;
    WeekLimit : array[1..3, MON..SAT] of byte;
    SPC_Count: Integer;
    SPC_Name: array[1..MAX_SPC_COUNT] of array[0..3] of char;
    SPC: array[1..MAX_SPC_COUNT, 1..3] of TClassPos;
    LunchTime: Word;
  end;
  // 학교 데이터
  TSchoolData = packed record
    ClassCount: array[1..3] of word;
    WeekLimit : array[1..3, MON..SAT] of byte;
    SPC_Count : word;
    SPC       : array[1..MAX_SPC_COUNT] of TSpcClass;
    LunchTime: Word;
  end;

  // 교사 데이터 옛날 버전 (ver 1)
  TTeacherData_ver1 = packed record
    TeacherNo : word;
    TeacherName : array [0..7] of char;
    Subject : array [1..3, 1..3] of array [0..3] of char;
    StartClass : array [1..3, 1..3] of word;
    EndClass : array [1..3, 1..3] of word;
    Times : array[1..3, 1..3] of word;
  end;
  // 교사 당 수업 데이터
  TTeacherSubject = packed record
    Name        : array [0..3] of char;
    StartClass,
    EndClass    : word;
    Times       : word;
  end;
  // 교사 데이터
  TTeacherData = packed record
    TeacherNo : word;
    TeacherName : array [0..7] of char;
    Subject : array [1..3, 1..MAX_TEACHER_SUBJECT] of TTeacherSubject;
  end;
  PTeacherData = ^TTeacherData;

  // 시간표 데이터
  TScheduleDataCell = packed record
    ClassNo, ClassNo2 : word;
    ClassType : byte;
    ClassInfo : word;
  end;
  PScheduleDataCell = ^TScheduleDataCell;
  TScheduleData = array [MON..SAT, 1..8] of TScheduleDataCell;
  PScheduleData = ^TScheduleData;

  // SCD 파일 헤더
  TScheduleFileHeader = packed record
    HeaderStr: array[0 .. 20-1] of char;
    Version:   LongInt;
    Reserved:  array[0 .. 64 - (20+4) -1] of byte;
  end;
  PScheduleFileHeader = ^TScheduleFileHeader;

var
  gConfig: TConfig;
  gSchool: TSchoolData;
  TeacherCount: integer;
  pTeachers: PTeacherData;
  pSchedules, pWorkSchedules: PScheduleData;
  pCurSchedules: PScheduleData;
  curYear, curWeek, curTeacher: integer;

procedure InitScheduleSource();
procedure LoadConfigData();
procedure SaveConfigData();
procedure ClearScheduleData();

function LoadScheduleData( filename: string ): boolean;
function SaveScheduleData( filename: string ): boolean;

procedure CopyToWorkSchedules();
procedure CopyFromWorkSchedules();
procedure SetCurSchedules( p: integer );

procedure DrawArrowLine( hDC: HDC; sx, sy, ex, ey: LongInt );
procedure DrawButtonLine( hDC: HDC; Rect: TRect );
Procedure DrawButtonText( hDC: HDC; Rect: TRect; StrData: PChar );
Procedure SetClassType( t, w, n: word; ClassType: byte );
procedure SetClassNo( t, w, n: word; ClassNo: word );
procedure SetClassNo2( t, w, n: word; ClassNo: word );
Procedure SetClassInfo( t, w, n: word; ClassInfo: word );
function GetClassType( t, w, n: word ): byte;
function GetClassNo( t, w, n: word ): word;
function GetClassNo2( t, w, n: word ): word;
function GetClassInfo( t, w, n: word ): word;
function GetClassMulti( t, w, n, c: word ) : word;

function GetTotalTeacherTimes() : Longint;

procedure SwapClass( t, sw, sn, ew, en: word );

procedure CopyFile( SrcFile, DesFile: string );


implementation

uses
  forms, inifiles;


(***********************************
  스케쥴 데이터를 초기화한다.
************************************)
procedure InitScheduleSource();
begin
    // 기초 자료 초기화
    ZeroMemory( @gSchool, sizeof(TSchoolData) );

    SetCurSchedules( 0 );

    ClearScheduleData();
end;


(***********************************
  INI 파일에서 설정 값을 읽는다.
************************************)
procedure LoadConfigData();
var
    ini: TIniFile;
begin
    ini := TIniFile.Create( ChangeFileExt(Application.ExeName, '.ini') );

    gConfig.MaxChangeCount := ini.ReadInteger( 'Config', 'MaxChangeCount', 6 );
    if gConfig.MaxChangeCount < 1 then gConfig.MaxChangeCount := 1;
    if gConfig.MaxChangeCount > 50 then gConfig.MaxChangeCount := 50;

    gConfig.Colors.CellText := ini.ReadInteger( 'Colors', 'CellText', clBlack );
    gConfig.Colors.CellBackground := ini.ReadInteger( 'Colors', 'CellBackground', clWhite );
    gConfig.Colors.GridLine := ini.ReadInteger( 'Colors', 'GridLine', clGray );
    gConfig.Colors.SpecialCell := ini.ReadInteger( 'Colors', 'SpecialCell', clLime );
    gConfig.Colors.FixedCell := ini.ReadInteger( 'Colors', 'FixedCell', clYellow );
    gConfig.Colors.FocusCell := ini.ReadInteger( 'Colors', 'FocusCell', clRed );
    gConfig.Colors.GrayCell := ini.ReadInteger( 'Colors', 'GrayCell', clSilver );
    gConfig.Colors.LunchTime := ini.ReadInteger( 'Colors', 'LunchTime', clRed );

    ini.Free();
end;


(***********************************
  INI 파일에 설정 값을 쓴다.
************************************)
procedure SaveConfigData();
var
    ini: TIniFile;
begin
    ini := TIniFile.Create( ChangeFileExt(Application.ExeName, '.ini') );

    ini.WriteString( 'Config', 'MaxChangeCount', IntToStr(gConfig.MaxChangeCount) );

    ini.WriteString( 'Colors', 'CellText', '0x'+IntToHex(gConfig.Colors.CellText,8) );
    ini.WriteString( 'Colors', 'CellBackground', '0x'+IntToHex(gConfig.Colors.CellBackground,8) );
    ini.WriteString( 'Colors', 'GridLine', '0x'+IntToHex(gConfig.Colors.GridLine,8) );
    ini.WriteString( 'Colors', 'SpecialCell', '0x'+IntToHex(gConfig.Colors.SpecialCell,8) );
    ini.WriteString( 'Colors', 'FixedCell', '0x'+IntToHex(gConfig.Colors.FixedCell,8) );
    ini.WriteString( 'Colors', 'FocusCell', '0x'+IntToHex(gConfig.Colors.FocusCell,8) );
    ini.WriteString( 'Colors', 'GrayCell', '0x'+IntToHex(gConfig.Colors.GrayCell,8) );
    ini.WriteString( 'Colors', 'LunchTime', '0x'+IntToHex(gConfig.Colors.LunchTime,8) );

    ini.Free();
end;


(***********************************
  .SCD 파일을 로드한다. (Ver 1, 2)
************************************)
function LoadScheduleData( filename: string ): boolean;
var
    f: integer;
    i, j, k: integer;
    hdr: TScheduleFileHeader;
    ts: PScheduleData;
    tt: PTeacherData;
    school_ver1: TSchoolData_ver1;
    pTeacher2, tt2: ^TTeacherData_ver1;

begin
    f := FileOpen( filename, fmOpenRead );

    // 헤더 읽기
    FileRead( f, hdr, sizeof(TScheduleFileHeader) );
    if StrComp(hdr.HeaderStr, 'Amos Schedule Data;') <> 0 then begin
      FileClose( f );
      Result := false;
      Exit;
    end;

    // 학교 기초 데이터 읽기
    if hdr.Version = 2 then begin
      FileRead( f, gSchool, sizeof(TSchoolData) );
    end else if hdr.Version = 1 then begin
      // 파일 버전 1을 대비... (나중에 지울 것임)
      FileRead( f, school_ver1, sizeof(TSchoolData_ver1) );
      for i := 1 to 3 do begin
        gSchool.ClassCount[i] := school_ver1.ClassCount[i];
        for j := MON to SAT do
          gSchool.WeekLimit[i][j] := school_ver1.WeekLimit[i][j];
        gSchool.SPC_Count := school_ver1.SPC_Count;
        for j := 1 to MAX_SPC_COUNT do begin
          StrCopy( gSchool.SPC[j].Name, school_ver1.SPC_Name[j] );
          gSchool.SPC[j].Years := SPC_CLASS1 or SPC_CLASS2 or SPC_CLASS3;
          gSchool.SPC[j].Pos[i] := school_ver1.SPC[j,i];
        end;
      end;
      gSchool.LunchTime := school_ver1.LunchTime;
    end else begin
      FileClose( f );
      Result := false;
      Exit;
    end;

    // 교사 수 읽기
    FileRead( f, TeacherCount, sizeof(LongInt) );

    // 교사수만큼 메모리 할당
    if pTeachers <> nil then FreeMem( pTeachers );
    if pSchedules <> nil then FreeMem( pSchedules );
    if pWorkSchedules <> nil then FreeMem( pWorkSchedules );
    if TeacherCount > 0 then begin
      pTeachers := AllocMem( Sizeof(TTeacherData) * TeacherCount );
      pSchedules := AllocMem( Sizeof(TScheduleData) * TeacherCount );
      pWorkSchedules := AllocMem( Sizeof(TScheduleData) * TeacherCount );
    end else begin
      pTeachers := nil;
      pSchedules := nil;
      pWorkSchedules := nil;
    end;

    // 교사 읽기
    if hdr.Version = 2 then begin
      tt := pTeachers;
      for i := 1 to TeacherCount do begin
        FileRead( f, tt^, sizeof(TTeacherData) );
        inc( tt );
      end;
    end else if hdr.Version = 1 then begin
      // 파일 버전 1을 대비... (나중에 지울 것임)
      pTeacher2 := AllocMem( Sizeof(TTeacherData_ver1) * TeacherCount );
      tt2 := pTeacher2;
      tt := pTeachers;
      for i := 1 to TeacherCount do begin
        FileRead( f, tt2^, sizeof(TTeacherData_ver1) );

        tt^.TeacherNo := tt2^.TeacherNo;
        StrCopy( tt^.TeacherName, tt2^.TeacherName );
        for j := 1 to 3 do begin
          for k := 1 to 3 do begin
            StrCopy( tt^.Subject[j,k].Name, tt2^.Subject[j,k] );
            tt^.Subject[j,k].StartClass := tt2^.StartClass[j,k];
            tt^.Subject[j,k].EndClass := tt2^.EndClass[j,k];
            tt^.Subject[j,k].Times := tt2^.Times[j,k];
          end;
        end;

        inc( tt2 );
        inc( tt );
      end;
      FreeMem( pTeacher2 );
    end;

    // 시간표 데이터 읽기
    ts := PSchedules;
    for i := 1 to TeacherCount do begin
      FileRead( f, ts^, sizeof(TScheduleData) );
      inc( ts );
    end;

    FileClose(f);

    SetCurSchedules( 0 );

    Result := true;
end;


(***********************************
  .SCD 파일로 쓴다. (Ver 2)
************************************)
function SaveScheduleData( filename: string ): boolean;
var
    f, i, j: integer;
    hdr: TScheduleFileHeader;
    ts: PScheduleData;
    tt: PTeacherData;

begin
    f := FileOpen( filename, fmOpenWrite );

    // 헤더 쓰기
    ZeroMemory( @hdr, sizeof(TScheduleFileHeader) );
    StrPCopy( hdr.HeaderStr, 'Amos Schedule Data;' );
    hdr.Version := 2;  // Format Ver 2
    FileWrite( f, hdr, sizeof(TScheduleFileHeader) );

    // 기초 데이터 쓰기
    FileWrite( f, gSchool, sizeof(TSchoolData) );

    // 교사 수 쓰기
    FileWrite( f, TeacherCount, sizeof(LongInt) );

    if TeacherCount > 0 then begin
      // 교사 쓰기
      tt := PTeachers;
      for i := 1 to TeacherCount do begin
        FileWrite( f, tt^, sizeof(TTeacherData) );
        inc( tt );
      end;

      // 시간표 데이터 쓰기
      ts := PSchedules;
      for i := 1 to TeacherCount do begin
        FileWrite( f, ts^, sizeof(TScheduleData) );
        inc( ts );
      end;
    end;

    FileClose(f);

    Result := true;
end;


(***********************************
  스케줄 데이터를 청소한다.
************************************)
procedure ClearScheduleData();
var
  i, y, t, c, w, n: word;
  ts: PScheduleData;
begin
  // 데이터 구조체 초기화
  ts := PSchedules;
  for t := 1 to TeacherCount do begin
    for w := MON to SAT do
      for n := 1 to 8 do begin
        ts^[w, n].ClassType := CT_NORMAL;
        ts^[w, n].ClassNo := 0;
        ts^[w, n].ClassNo2 := 0;
      end;
    inc( ts );
  end;
end;


(************************
  스케줄 데이터를
  작업 영역으로 복사
*************************)
procedure CopyToWorkSchedules();
begin
    if pWorkSchedules <> nil then
      CopyMemory( pWorkSchedules, pSchedules, sizeof(TScheduleData)*TeacherCount );
end;


(************************
  작업 영역에서
  스케줄 데이터를 복사
*************************)
procedure CopyFromWorkSchedules();
begin
    if pWorkSchedules <> nil then
      CopyMemory( pSchedules, pWorkSchedules, sizeof(TScheduleData)*TeacherCount );
end;


(************************
  현재 작업 대상인
  스케줄 데이터 지정
*************************)
procedure SetCurSchedules( p: integer );
begin
    if p = 0 then
      pCurSchedules := pSchedules
    else
      pCurSchedules := pWorkSchedules;
end;


(************************
  파일 복사
*************************)
procedure CopyFile( SrcFile, DesFile: string );
var
  i: longint;
  sf, df: integer;
  fs: longint;
  TempData: byte;

begin
  sf := FileOpen( SrcFile, fmOpenRead );
  df := FileCreate( DesFile );
  fs := FileSeek( sf, 0, 2 );
  FileSeek( sf, 0, 0 );

  for i := 1 to fs do begin
    FileRead( sf, TempData, 1 );
    FileWrite( df, TempData, 1 );
  end;

  FileClose( sf );
  FileClose( df );
end;


(************************
  화살표 모양을 그려준다.
  (우... 만들다 말았음.)
*************************)
procedure DrawArrowLine( hDC: HDC; sx, sy, ex, ey: LongInt );
var
    aa, xx: extended;
    nx, ny: LongInt;
begin
    MoveToEx( hDC, sx, sy, Nil );
    LineTo( hDC, ex, ey );
//    AngleArc( hDC, ex, ey, 10, 0, 360 );

    xx := (ey-sy)/(ex-sx);
    aa := arctan( xx );

    if xx >= 0 then begin // 1, 3 사분면
      // 3 사분면
      if (ex-ey) < 0 then begin
        aa := aa + 2*PI;
      end;
    end else begin // 2, 4 사분면
      // 4 사분면
      if (ex-ey) < 0 then begin
        aa := aa + 1*PI;
      end else begin
      aa := aa - 1*PI;
      end;
    end;
    nx := Trunc( cos( aa - 1/2 ) * 10 );
    ny := Trunc( sin( aa - 1/2 ) * 10 );
    MoveToEx( hDC, ex, ey, Nil );
    LineTo( hDC, ex + nx, ey + ny );
    nx := Trunc( cos( aa + 1/2 ) * 10 );
    ny := Trunc( sin( aa + 1/2 ) * 10 );
    MoveToEx( hDC, ex, ey, Nil );
    LineTo( hDC, ex + nx, ey + ny );
end;


(************************
  버튼 모양을 그려준다.
*************************)
procedure DrawButtonLine( hDC: HDC; Rect: TRect );
var
    brs: HBRUSH;
    Points: array [0..2] of TPoint;
    hOldPen, hGrayPen, hWhitePen: HPEN;

begin
    brs := CreateSolidBrush( GetSysColor(COLOR_BTNFACE) );
    FillRect( hDC, Rect, brs );
    DeleteObject( brs );

    Points[0].x := Rect.Right;
    Points[0].y := Rect.Top;
    Points[1].x := Rect.Right;
    Points[1].y := Rect.Bottom;
    Points[2].x := Rect.Left;
    Points[2].y := Rect.Bottom;
  
    hGrayPen := CreatePen( PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) );
    hOldPen := SelectObject( hDC, hGrayPen );
    Polyline( hDC, Points, 3 );
    SelectObject( hDC, hOldPen );
    DeleteObject( hGrayPen );
  
    Points[1].x := Rect.Left;
    Points[1].y := Rect.Top;
  
    hWhitePen := CreatePen( PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) );
    hOldPen := SelectObject( hDC, hWhitePen );
    Polyline( hDC, Points, 3 );
    SelectObject( hDC, hOldPen );
    DeleteObject( hWhitePen );
end;


(************************
  버튼 안에 글을 쓴다.(세로로)
*************************)
Procedure DrawButtonText( hDC: HDC; Rect: TRect; StrData: PChar );
var
    ChrCount, l: integer;
    nextptr, ptr: PChar;
    step: word;
    dRect: TRECT;
    ts: TSize;
    Rop: integer;

begin
    GetTextExtentPoint32( hDC, '주', 2, ts );
  
    (* 글자의 갯수를 알아낸다. *)
    ChrCount := 0;
    ptr := StrData;
    while ptr^ <> #0 do begin
      inc(ChrCount);
      ptr := AnsiNext(ptr);
    end;
  
    dRect.Top := Rect.Top + 2;
    dRect.Left := Rect.Left + 2;
    dRect.Right := Rect.Right - 2;
  
    (* 글자 사이의 간격을 정한다. *)
    if ChrCount > 1 then begin
      step := (Rect.Bottom - Rect.Top - ts.cy - 4) div (ChrCount - 1);
      dRect.Bottom := Rect.Top + 2 + ts.cy;
      Rop := DT_CENTER;
    end else begin
      dRect.Bottom := Rect.Bottom - 2;
      Rop := DT_CENTER or DT_SINGLELINE or DT_VCENTER;
    end;
  
    (* 글자를 찍는다. *)
    SetBkColor( hDC, GetSysColor(COLOR_BTNFACE) );
    ptr := StrData;
    while ptr^ <> #0 do begin
      nextptr := AnsiNext(ptr);
      DrawText( hDC, ptr, nextptr - ptr, dRect, Rop );
      ptr := nextptr;
      dRect.Top := dRect.Top + step;
      dRect.Bottom := dRect.Bottom + step;
    end;
end;


(***********************************
  지정된 위치에 클래스 타입 세트
************************************)
procedure SetClassType( t, w, n: word; ClassType: byte );
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    ts^[w, n].ClassType := ClassType;
end;


(***********************************
  지정된 위치에 클래스 번호 세트
************************************)
procedure SetClassNo( t, w, n: word; ClassNo: word );
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    ts^[w, n].ClassNo := ClassNo;
end;


(***********************************
  지정된 위치에 클래스 번호 세트
************************************)
procedure SetClassNo2( t, w, n: word; ClassNo: word );
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    ts^[w, n].ClassNo2 := ClassNo;
end;


(***********************************
  지정된 위치에 클래스 정보 세트
************************************)
procedure SetClassInfo( t, w, n: word; ClassInfo: word );
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    ts^[w, n].ClassInfo := ClassInfo;
end;


(***********************************
  지정된 위치의 클래스 타입 리턴
************************************)
function GetClassType( t, w, n: word ): byte;
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    GetClassType := ts^[w, n].ClassType;
end;


(***********************************
  지정된 위치의 클래스 번호 리턴
************************************)
function GetClassNo( t, w, n: word ): word;
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    GetClassNo := ts^[w, n].ClassNo;
end;


(***********************************
  지정된 위치의 클래스 번호 리턴
************************************)
function GetClassNo2( t, w, n: word ): word;
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    GetClassNo2 := ts^[w, n].ClassNo2;
end;


(***********************************
  지정된 위치의 클래스 정보 리턴
************************************)
function GetClassInfo( t, w, n: word ): word;
var
    ts: PScheduleData;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
  
    GetClassInfo := ts^[w, n].ClassInfo;
end;


(**************************************
  해당 교사의 해당 클래스의 정보를 얻는다.
***************************************)
function GetClassMulti( t, w, n, c: word ) : word;
var
    ts: PScheduleData;
    i, y: word;
    EndClass: word;

begin
    y := c div 100;
    if (gSchool.WeekLimit[y, w] < n) then begin
      Result := 1001;
      Exit;
    end;
    for i := 1 to gSchool.SPC_Count do begin
      if ((gSchool.SPC[i].Years and SPC_CLASSES[y]) <> 0) and
         (gSchool.SPC[i].Pos[y].w = w) and (gSchool.SPC[i].Pos[y].t = n) then begin
        Result := 1001;
        Exit;
      end;
    end;
  
    ts := pCurSchedules;
  
    for i := 1 to t - 1 do begin
      if (ts^[w, n].ClassNo = c) or (ts^[w, n].ClassNo2 = c) then begin
        Result := i;
        Exit;
      end;
      inc( ts );
    end;
  
    inc( ts );
  
    for i := t + 1 to TeacherCount do begin
      if (ts^[w, n].ClassNo = c) or (ts^[w, n].ClassNo2 = c) then begin
        Result := i;
        Exit;
      end;
      inc( ts );
    end;
  
    Result := 0;
end;


(****************************
  두 반과 해당 교사를 바꾼다.
*****************************)
procedure SwapClass( t, sw, sn, ew, en: word );
var
    ts: PScheduleData;
    temp: TScheduleDataCell;

begin
    ts := pCurSchedules;
  
    inc( ts, t - 1 );
    temp := ts^[sw, sn];
    ts^[sw, sn] := ts^[ew, en];
    ts^[ew, en] := temp;
end;


(****************************
  전체 교사 시수를 구한다.
*****************************)
function GetTotalTeacherTimes() : Longint;
var
    i, j, k: integer;
    Total: Longint;
    tt: PTeacherData;
    
begin
    Total := 0;
    tt := pTeachers;
    for i := 1 to TeacherCount do begin
      for j := 1 to 3 do begin
        for k := 1 to MAX_TEACHER_SUBJECT do begin
          if tt^.Subject[j,k].Name <> '' then
            ToTal := Total + (tt^.Subject[j,k].EndClass - tt^.Subject[j,k].StartClass + 1) * tt^.Subject[j,k].Times;
        end;
      end;
      inc( tt );
    end;

    Result := Total;
end;


end.

