//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
//----------------------------------------------------------------------------

#include <IniFiles.hpp>
#include <math.h>

static String WeekStr[6] = { "월", "화", "수", "목", "금", "토" };
unsigned long SPC_CLASS_MASK_LST[3] = {SPC_CLASS1_MASK, SPC_CLASS2_MASK, SPC_CLASS3_MASK};

  TConfig g_Config;
  TScheduleInfo g_ScheduleInfo;
  TSchoolData g_School;
  int g_iSubjectCount;
  TSubject *g_pSubjects;
  int g_iTeacherCount;
  TTeacherData *g_pTeachers;
  int g_iMoveLessonCount;
  TMoveLessonData *g_pMoveLesson;
  PScheduleData g_pSchedules, g_pWorkSchedules;
  PScheduleData g_pCurSchedules;
  int g_curYear, g_curWeek, g_curTeacher;


/***********************************
  스케쥴 데이터를 초기화한다.
************************************/
void InitScheduleSystem(void)
{
    // 기초 자료 초기화
    ZeroMemory( &g_School, sizeof(TSchoolData) );

  	g_iTeacherCount = 0;
	g_iMoveLessonCount = 0;

    SetCurSchedules( 0 );

    ClearScheduleData();
}


/***********************************
  INI 파일에서 설정 값을 읽는다.
************************************/
void LoadConfigData()
{
    TIniFile *ini;

    ini = new TIniFile( ChangeFileExt(Application->ExeName, ".ini") );

    g_Config.MaxChangeCount = ini->ReadInteger( "Config", "MaxChangeCount", 6 );
    if( g_Config.MaxChangeCount < 1 )g_Config.MaxChangeCount = 1;
    if( g_Config.MaxChangeCount > 50 )g_Config.MaxChangeCount = 50;

    g_Config.Colors.CellText = (TColor)ini->ReadInteger( "Colors", "CellText", clBlack );
    g_Config.Colors.CellBackground = (TColor)ini->ReadInteger( "Colors", "CellBackground", clWhite );
    g_Config.Colors.GridLine = (TColor)ini->ReadInteger( "Colors", "GridLine", clGray );
    g_Config.Colors.FixedCell = (TColor)ini->ReadInteger( "Colors", "FixedCell", clYellow );
    g_Config.Colors.FocusCell = (TColor)ini->ReadInteger( "Colors", "FocusCell", clRed );
    g_Config.Colors.GrayCell = (TColor)ini->ReadInteger( "Colors", "GrayCell", clSilver );
    g_Config.Colors.LunchTime = (TColor)ini->ReadInteger( "Colors", "LunchTime", clRed );
    g_Config.Colors.SpecialLesson = (TColor)ini->ReadInteger( "Colors", "SpecialLesson", clLime );
    g_Config.Colors.MoveLesson = (TColor)ini->ReadInteger( "Colors", "MoveLesson", clFuchsia );

    delete ini;
}


/***********************************
  INI 파일에 설정 값을 쓴다.
************************************/
void SaveConfigData()
{
    TIniFile *ini;

    ini = new TIniFile( ChangeFileExt(Application->ExeName, ".ini") );

    ini->WriteString( "Config", "MaxChangeCount", IntToStr(g_Config.MaxChangeCount) );

    ini->WriteString( "Colors", "CellText", "0x"+IntToHex(g_Config.Colors.CellText,8) );
    ini->WriteString( "Colors", "CellBackground", "0x"+IntToHex(g_Config.Colors.CellBackground,8) );
    ini->WriteString( "Colors", "GridLine", "0x"+IntToHex(g_Config.Colors.GridLine,8) );
    ini->WriteString( "Colors", "FixedCell", "0x"+IntToHex(g_Config.Colors.FixedCell,8) );
    ini->WriteString( "Colors", "FocusCell", "0x"+IntToHex(g_Config.Colors.FocusCell,8) );
    ini->WriteString( "Colors", "GrayCell", "0x"+IntToHex(g_Config.Colors.GrayCell,8) );
    ini->WriteString( "Colors", "LunchTime", "0x"+IntToHex(g_Config.Colors.LunchTime,8) );
    ini->WriteString( "Colors", "SpecialLesson", "0x"+IntToHex(g_Config.Colors.SpecialLesson,8) );
    ini->WriteString( "Colors", "MoveLesson", "0x"+IntToHex(g_Config.Colors.MoveLesson,8) );

    delete ini;
}


/***********************************
  스케줄 데이터를 할당한다.
************************************/
bool InitSubjectData( int iSubjectCount )
{
    if( g_pSubjects != NULL ) free( g_pSubjects );

    if( iSubjectCount > 0 ){
      g_pSubjects = (TSubject *)malloc( sizeof(TSubject) * iSubjectCount );
	  memset( g_pSubjects, 0, sizeof(TSubject) * iSubjectCount );
    } else {
      g_pSubjects = NULL;
    }

	g_iSubjectCount = iSubjectCount;

	return true;
}

/***********************************
  스케줄 데이터를 할당한다.
************************************/
bool ReallocSubjectData( int iSubjectCount )
{
    if( iSubjectCount > 0 ){
      g_pSubjects = (TSubject *)realloc( g_pSubjects, sizeof(TSubject) * iSubjectCount );
	  if( iSubjectCount > g_iSubjectCount ){
	  	 memset( &g_pSubjects[g_iSubjectCount], 0, sizeof(TSubject) * (iSubjectCount-g_iSubjectCount) );
	  }
    } else {
	  if( g_pSubjects != NULL ) free( g_pSubjects );
      g_pSubjects = NULL;
    }

	g_iSubjectCount = iSubjectCount;

	return true;
}


/***********************************
  스케줄 데이터를 할당한다.
************************************/
bool InitTeacherData( int iTeacherCount )
{
    if( g_pTeachers != NULL ) free( g_pTeachers );

    if( iTeacherCount > 0 ){
      g_pTeachers = (TTeacherData *)malloc( sizeof(TTeacherData) * iTeacherCount );
	  memset( g_pTeachers, 0, sizeof(TTeacherData) * iTeacherCount );
    } else {
      g_pTeachers = NULL;
    }

	g_iTeacherCount = iTeacherCount;

	return true;
}


/***********************************
  스케줄 데이터를 재할당한다.
************************************/
bool ReallocTeacherData( int iTeacherCount )
{
    if( iTeacherCount > 0 ){
      g_pTeachers = (TTeacherData *)realloc( g_pTeachers, sizeof(TTeacherData) * iTeacherCount );
	  if( iTeacherCount > g_iTeacherCount ){
	  	 memset( &g_pTeachers[g_iTeacherCount], 0, sizeof(TTeacherData) * (iTeacherCount-g_iTeacherCount) );
	  }
    } else {
	  if( g_pTeachers != NULL ) free( g_pTeachers );
      g_pTeachers = NULL;
    }

	g_iTeacherCount = iTeacherCount;

	return true;
}

/***********************************
  이동수업 데이터를 할당한다.
************************************/
bool InitMoveLessonData( int iMoveLessonCount )
{
    if( g_pMoveLesson != NULL ) free( g_pMoveLesson );

    if( iMoveLessonCount > 0 ){
      g_pMoveLesson = (TMoveLessonData *)malloc( sizeof(TMoveLessonData) * iMoveLessonCount );
	  memset( g_pMoveLesson, 0, sizeof(TMoveLessonData) * iMoveLessonCount );
    } else {
      g_pMoveLesson = NULL;
    }

	g_iMoveLessonCount = iMoveLessonCount;

	return true;
}

/***********************************
  이동수업 데이터를 재할당한다.
************************************/
bool ReallocMoveLessonData( int iMoveLessonCount )
{
    if( iMoveLessonCount > 0 ){
      g_pMoveLesson = (TMoveLessonData *)realloc( g_pMoveLesson, sizeof(TMoveLessonData) * iMoveLessonCount );
	  if( iMoveLessonCount > g_iMoveLessonCount ){
	  	 memset( &g_pMoveLesson[g_iMoveLessonCount], 0, sizeof(TMoveLessonData) * (iMoveLessonCount-g_iMoveLessonCount) );
	  }
    } else {
	  if( g_pMoveLesson != NULL ) free( g_pMoveLesson );
      g_pMoveLesson = NULL;
    }

	g_iMoveLessonCount = iMoveLessonCount;

	return true;
}

/***********************************
  스케줄 데이터를 할당한다.
************************************/
bool InitScheduleData(void)
{
    if( g_pWorkSchedules != NULL ) free( g_pWorkSchedules );
    if( g_pSchedules != NULL ) free( g_pSchedules );

    if( g_iTeacherCount > 0 ){
      g_pSchedules = (PScheduleData)malloc( sizeof(TScheduleData) * g_iTeacherCount );
	  memset( g_pSchedules, 0, sizeof(TScheduleData) * g_iTeacherCount );
      g_pWorkSchedules = (PScheduleData)malloc( sizeof(TScheduleData) * g_iTeacherCount );
      // memset( g_pWorkSchedules, 0, sizeof(TScheduleData) * g_iTeacherCount ); // 굳이 지울 필요까지는...
    } else {
      g_pSchedules = NULL;
      g_pWorkSchedules = NULL;
    }

	g_pCurSchedules = g_pSchedules;

	return true;
}


/***********************************
  스케줄 데이터를 청소한다.
************************************/
void ClearScheduleData()
{
    WORD t, w, n;
//    TScheduleDataCell *sc;

  // 데이터 구조체 초기화
  for( t = 0; t < g_iTeacherCount; t++ ) {
    for( w = atWEEK_MON; w <= atWEEK_MAX; w++ )
      for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
//        sc = GetScheduleDataCell( t, w, n );
	    SetClassType( t, w, n, CT_NORMAL );
	  	ClearClasses( t, w, n );
      }
  }
}


/************************

*************************/
TSubject *GetSubject( int idx )
{
    if( idx < 0 ) return NULL;
    if( idx >= g_iSubjectCount ) return NULL;
	
	return &g_pSubjects[idx];
}


/************************

*************************/
TSubject *FindSubjectByCode( short subjectcode )
{
    int i;
	TSubject *sbj;

	for( i = 0; i < g_iSubjectCount; i++ ){
		sbj = &g_pSubjects[i];
		if( sbj->SubjectCode == subjectcode ){
			return sbj;
		}
	}

	return NULL;
}


/************************

*************************/
TSubject *FindSubjectByName( const char *subjecname )
{
    int i;
	TSubject *sbj;

	for( i = 0; i < g_iSubjectCount; i++ ){
		sbj = &g_pSubjects[i];
		if( strcmp( sbj->FullName, subjecname) == 0 ){
			return sbj;
		}
	}

	return NULL;
}


/************************
  스케줄 데이터를
  작업 영역으로 복사
*************************/
void CopyToWorkSchedules()
{
    if( g_pWorkSchedules != NULL )
      CopyMemory( g_pWorkSchedules, g_pSchedules, sizeof(TScheduleData)*g_iTeacherCount );
}


/************************
  작업 영역에서
  스케줄 데이터를 복사
*************************/
void CopyFromWorkSchedules()
{
    int t, w, n;
	TScheduleData *ts;
	
    if( g_pWorkSchedules != NULL ){
      CopyMemory( g_pSchedules, g_pWorkSchedules, sizeof(TScheduleData)*g_iTeacherCount );
	  
	  ts = g_pSchedules;
	  for( t = 0; t < g_iTeacherCount; t++ ){
	  	for( w = atWEEK_MON; w <= atWEEK_MAX; w++ )
          for( n = atLESSON_1; n <= atLESSON_MAX; n++ )
		    if( (*ts)[w - atWEEK_BASE][n - atLESSON_BASE].ClassType == CT_TEMP )
              (*ts)[w - atWEEK_BASE][n - atLESSON_BASE].ClassType = CT_NORMAL;
		ts++;
	  }
    }
}


/************************
  현재 작업 대상인
  스케줄 데이터 얻기
*************************/
int GetCurSchedules(void)
{
    if( g_pCurSchedules == g_pSchedules ) return 0;
	else if( g_pCurSchedules == g_pWorkSchedules ) return 1;
	else return -1;
}

/************************
  현재 작업 대상인
  스케줄 데이터 지정
*************************/
int SetCurSchedules( int p )
{
    int r;
	
    r = GetCurSchedules();

    if( p == 0 )
      g_pCurSchedules = g_pSchedules;
    else if( p == 1 )
      g_pCurSchedules = g_pWorkSchedules;
    else
      g_pCurSchedules = NULL;

	return r;
}


/***********************************

************************************/
String GetWeekStr(int week)
{
    return WeekStr[week-atWEEK_BASE];
}

/***********************************
  총 몇교시까지 있는지 얻는다.
************************************/
int GetWeekLimit( int year, int week )
{
    return g_School.WeekLimit[year-atYEAR_BASE][week-atWEEK_BASE];
}

/***********************************

************************************/
int GetLimitClass( int year )
{
    return g_School.ClassCount[year-atYEAR_BASE] - 1 + atCLASS_BASE;
}

/***********************************

************************************/
TTeacherData *GetTeacherData( int t )
{
    PTeacherData tt;

    tt = &g_pTeachers[t];

    return tt;
}

/***********************************

************************************/
void ClearTeacherData( int t )
{
    PTeacherData tt;

    tt = &g_pTeachers[t];

	memset( tt, 0, sizeof(TTeacherData) );
}

/***********************************

************************************/
TTeacherSubject *GetTeacherSubject( int t, int idx )
{
    PTeacherData tt;

    if( idx == -1 ) return NULL;

    tt = GetTeacherData( t );

    return &tt->Subject[idx];
}

/***********************************

************************************/
int GetTeacherSubjectCount( int t )
{
    int i, cnt;
    PTeacherData tt;

    tt = GetTeacherData( t );

    cnt = 0;
    for( i = 0; i < MAX_TEACHER_SUBJECT; i++ )
    	if( tt->Subject[i].SubjectCode != 0 ) cnt++;
//    	if( tt->Subject[i].Name[0] != '\0' ) cnt++;

	return cnt;
}

/***********************************

************************************/
void ClearTeacherSubject( int t )
{
    PTeacherData tt;

    tt = GetTeacherData( t );

    memset( tt->Subject, 0, sizeof(TTeacherSubject) * MAX_TEACHER_SUBJECT );
}

/***********************************
  지정된 위치에 클래스 번호 정리
************************************/
void PackTeacherSubject( WORD t )
{
    int i, j;
    PTeacherData tt;

    tt = GetTeacherData( t );

	for( i = 0; i < MAX_TEACHER_SUBJECT-1; i++ ){
	  if( tt->Subject[i].SubjectCode == 0 ){
	   	for( j = i+1; j < MAX_TEACHER_SUBJECT; j++ ){
		  if( tt->Subject[j].SubjectCode != 0 ){
            tt->Subject[i] = tt->Subject[j];
            tt->Subject[j].SubjectCode = 0; 
		  	break;
		  }
	    }
	  }
	}
}


/***********************************

************************************/
String GetTeacherSubjectString( int t, int idx )
{
    TTeacherSubject *tsbj;
    TSubject *sbj;
    String s;

    tsbj = GetTeacherSubject(t, idx);
    sbj = FindSubjectByCode( tsbj->SubjectCode );

    s = (String)"(" + ((sbj)?sbj->FullName:"<<null>>") + ") ";
    s += IntToStr(tsbj->Classes.Part.Year) + "학년 :";

    for( int i = atCLASS_1; i < atCLASS_MAX; i++ ){
       if( IS_CLASSES_IN( i, tsbj->Classes.Part.Classes ) )
         s += " " + IntToStr(i);
    }

    return s;
}

/***********************************

************************************/
TScheduleData *GetScheduleData( int t )
{
    return &g_pCurSchedules[t];
}


/***********************************

************************************/
TScheduleDataCell *GetScheduleDataCell( int t, int week, int num )
{
	PScheduleData ts;

    ts = GetScheduleData( t );

    return &(*ts)[week - atWEEK_BASE][num - atLESSON_BASE];
}


/***********************************
  특별수업 여부 판다.
************************************/
bool CheckSpcType( int year, int week, int num, int *pNum )
{
    int i;

    for( i = 0; i < g_School.SPC_Count; i++ ) {
      if(  ((g_School.SPC[i].Years & SPC_CLASS_MASK_LST[year-atYEAR_BASE]) != 0) &&
          (week == g_School.SPC[i].Pos[year-atYEAR_BASE].week) && (num == g_School.SPC[i].Pos[year-atYEAR_BASE].lesson) ){
        if( pNum ) *pNum = i;
        return TRUE;
      }
    }

    return FALSE;
}

/***********************************
  특별수업 여부 판다.
************************************/
/*
bool CheckClass( int idx, int classes )
{

	for( c = atCLASS_1; c <= atCLASS_MAX; c++ ) {
	  if( s & (1 << (c-atCLASS_BASE)) ){

    int i;

    for( i = 0; i < g_School.SPC_Count; i++ ) {
      if(  ((g_School.SPC[i].Years & SPC_CLASS_MASK_LST[year-atYEAR_BASE]) != 0) &&
          (week == g_School.SPC[i].Pos[year-atYEAR_BASE].week) && (num == g_School.SPC[i].Pos[year-atYEAR_BASE].lesson) ){
        if( pNum ) *pNum = i;
        return TRUE;
      }
    }

    return FALSE;
}
*/

/***********************************
  지정된 위치에 클래스 타입 세트
************************************/
void SetClassType( WORD t, WORD w, WORD n, BYTE ClassType )
{
    GetScheduleDataCell( t, w, n )->ClassType = ClassType;
}


/***********************************
  지정된 위치에 클래스 번호 세트
************************************/
void SetClassNo( WORD t, WORD w, WORD n, WORD ClassNo )
{
    TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );
	
    sc->Classes.Part.Year = GET_CLASS_YEAR(ClassNo);
    sc->Classes.Part.Classes = 1 << (GET_CLASS_CLASS(ClassNo)-atCLASS_BASE);
}

/***********************************
  지정된 위치에 클래스 번호 세트
************************************/
void SetClassesFull( WORD t, WORD w, WORD n, unsigned long ClassNoFull )
{
    GetScheduleDataCell( t, w, n )->Classes.FullValue = ClassNoFull;
}

/***********************************
  지정된 위치에 클래스 번호 세트
************************************/
unsigned long GetClassesFull( WORD t, WORD w, WORD n )
{
    return GetScheduleDataCell( t, w, n )->Classes.FullValue;
}

/***********************************
  지정된 위치에 클래스 번호 리셋
************************************/
void RemoveClassNo( WORD t, WORD w, WORD n, WORD ClassNo )
{
//    GetScheduleDataCell( t, w, n )->Classes.Part.Year = GET_CLASS_YEAR(ClassNo);
    TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );
    sc->Classes.Part.Classes &= ~(1 << (GET_CLASS_CLASS(ClassNo)-atCLASS_BASE));
	if( sc->Classes.Part.Classes == 0) sc->Classes.Part.Year = 0; // 학급이 다 지워지면 학년도 없앤다.
}


/***********************************
  지정된 위치의 클래스 번호 추가
************************************/
int AddClassNo( WORD t, WORD w, WORD n, WORD ClassNo )
{
/*
 	int i;
	WORD *cls = GetScheduleDataCell( t, w, n )->ClassNo;

	for( i = 0; i < MAX_MULTILESSON_CLASS; i++ ){
		if( cls[i] == 0 ){
			cls[i] = ClassNo;
			return i;
		}
	}
*/
    int cnt = GetClassCount(t,w,n);
    if( cnt >= MAX_MULTILESSON_CLASS ) return -1;

	TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );

    if( cnt > 0 ){
      if( sc->Classes.Part.Year != GET_CLASS_YEAR(ClassNo) ) return -2;
    }  else {
		sc->Classes.Part.Year = GET_CLASS_YEAR(ClassNo);
    }
    sc->Classes.Part.Classes |= 1 << (GET_CLASS_CLASS(ClassNo)-atCLASS_BASE);

	return cnt + 1;
}

/***********************************
  지정된 위치에 클래스 번호 삭제
************************************/
void ClearClasses( WORD t, WORD w, WORD n )
{
/*
    int i;
	for( i = 0; i < MAX_MULTILESSON_CLASS; i++ )
		SetClassNo( t, w, n, i, 0 );
*/		
	SetClassesFull( t, w, n, 0 );
}


/***********************************
  지정된 위치에 클래스 번호 정리
************************************/
/*
void PackClassNo( WORD t, WORD w, WORD n )
{
    int i, j;
	int no, no2;
	
	for( i = 0; i < MAX_MULTILESSON_CLASS-1; i++ ){
		no = GetClassNo( t, w, n, i );
		if( no == 0 ){
			for( j = i+1; j < MAX_MULTILESSON_CLASS; j++ ){
				no2 = GetClassNo( t, w, n, j );
				if( no2 != 0 ){
					SetClassNo( t, w, n, i, no2 );
					SetClassNo( t, w, n, j, MAKE_CLASS_NO(0,0) );
					break;
				}
			}
		}
	}
}
*/	


/***********************************
  지정된 위치에 클래스 정보 세트
************************************/
void SetClassInfo( WORD t, WORD w, WORD n, WORD ClassInfo )
{
    GetScheduleDataCell( t, w, n )->ClassInfo = ClassInfo;
}


/***********************************
  지정된 위치의 클래스 타입 리턴
************************************/
int GetClassType( WORD t, WORD w, WORD n )
{
    return GetScheduleDataCell( t, w, n )->ClassType;
}


/***********************************
  지정된 위치의 클래스 번호 갯수 리턴
************************************/
int GetClassCount( WORD t, WORD w, WORD n )
{
/*
 	int i, cnt;
	WORD *cls = GetScheduleDataCell( t, w, n )->ClassNo;

	cnt = 0;
	for( i = 0; i < MAX_MULTILESSON_CLASS; i++ ){
		if( cls[i] != 0 ) cnt++;
	}
	
    return cnt;
*/    
 	int i, cnt;
	TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );
	
	cnt = 0;
	for( i = atCLASS_1; i <= atCLASS_MAX; i++ ){
		if( IS_CLASSES_IN(i, sc->Classes.Part.Classes) ) cnt++;
	}
	
    return cnt;
}

/***********************************
  지정된 위치의 클래스 번호 추가 가능한가
************************************/
bool IsEmptyClassNo( WORD t, WORD w, WORD n )
{
/*
 	int i;
	WORD *cls = GetScheduleDataCell( t, w, n )->ClassNo;

	for( i = 0; i < MAX_MULTILESSON_CLASS; i++ ){
		if( cls[i] != 0 ) return false;
	}

	return true;
*/	
	TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );

    if( sc->Classes.Part.Classes == 0 ) return TRUE; else return FALSE;
}

/***********************************
  지정된 위치의 클래스 번호 추가 가능한가
************************************/
bool IsCanAddClassNo( WORD t, WORD w, WORD n )
{
/*
 	int i;
	WORD *cls = GetScheduleDataCell( t, w, n )->ClassNo;

	for( i = 0; i < MAX_MULTILESSON_CLASS; i++ ){
		if( cls[i] == 0 ) return true;
	}

	return false;
*/	
 	int i, cnt;
	TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );
	
	cnt = 0;
	for( i = atCLASS_1; i <= atCLASS_MAX; i++ ){
		if( IS_CLASSES_IN(i, sc->Classes.Part.Classes) ){
			cnt++;
			if( cnt >= MAX_MULTILESSON_CLASS ) return FALSE;
		}
	}
	
    return TRUE;
}

/***********************************
  지정된 위치의 클래스 번호가 포함되어 있나.
************************************/
bool IsEmbededClassNo( WORD t, WORD w, WORD n, WORD ClassNo )
{
/*
 	int i;
	WORD *cls = GetScheduleDataCell( t, w, n )->ClassNo;

	for( i = 0; i < MAX_MULTILESSON_CLASS; i++ ){
		if( cls[i] == ClassNo ) return true;
	}

	return false;
*/	
	TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );

    if( (sc->Classes.Part.Year == GET_CLASS_YEAR(ClassNo)) && 
		IS_CLASSES_IN( GET_CLASS_CLASS(ClassNo), sc->Classes.Part.Classes) ) return TRUE; else return FALSE;
}

/***********************************
  지정된 위치의 클래스 번호 리턴
************************************/
WORD GetClassNo( WORD t, WORD w, WORD n, int idx )
{
	//	  return GetScheduleDataCell( t, w, n )->ClassNo[idx];
 	int i, cnt;
	TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );
	
	cnt = 0;
	for( i = atCLASS_1; i <= atCLASS_MAX; i++ ){
		if( IS_CLASSES_IN(i, sc->Classes.Part.Classes) ){
			if( cnt == idx ) return MAKE_CLASS_NO(sc->Classes.Part.Year, i);
			cnt++;
		}
	}
	
    return 0;
}

/***********************************
  지정된 위치의 클래스 정보 리턴
************************************/
WORD GetClassInfo( WORD t, WORD w, WORD n )
{
    return GetScheduleDataCell( t, w, n )->ClassInfo;
}

/***************************************************
  해당 교사의 해당 클래스와 중복되는 교사를 구한다.
****************************************************/
int GetClassOverlapTeacher( WORD t, WORD w, WORD n, WORD c )
{
    WORD i, y;

    y = GET_CLASS_YEAR(c);
    if( n > GetWeekLimit(y,w) ){
      return -2;
    }
    if( CheckSpcType( y, w, n, NULL ) )
 	  return -3;

    for( i = 0; i < g_iTeacherCount; i++ ) {
	  if( i == t ) continue;
	  if( IsEmbededClassNo( i, w, n, c ) )
        return i;
    }

    return -1;
}


/****************************
  두 반과 해당 교사를 바꾼다.
*****************************/
void SwapClass( WORD t, WORD sw, WORD sn, WORD ew, WORD en )
{
    TScheduleDataCell *sc1, *sc2, temp;

    sc1 = GetScheduleDataCell( t, sw, sn );
    sc2 = GetScheduleDataCell( t, ew, en );

    temp = *sc1;
    *sc1 = *sc2;
    *sc2 = temp;
}


/****************************
  해당 교사 시수를 구한다.
*****************************/
long GetTeacherTimes( int t, bool isEmbedMovelesson )
{
    int i, c;
    long sbjcnt, cnt, Total;
    TTeacherSubject *sbj;

    Total = 0;
	sbjcnt = GetTeacherSubjectCount(t);
    for( i = 0; i < sbjcnt; i++ ) {
      sbj = GetTeacherSubject( t, i );
      if( !isEmbedMovelesson && (sbj->Attr & 0x01) ) continue;

      cnt = 0;
      for( c = atCLASS_1; c <= atCLASS_MAX; c++ )
        if( IS_CLASSES_IN( c, sbj->Classes.Part.Classes  ) )
          cnt++;
		
      Total += cnt * sbj->Times;
    }

    return Total;
}

/****************************
  전체 교사 시수를 구한다.
  (이동수업 제외)
*****************************/
long GetTotalTeacherTimes(void)
{
    int i;
    long Total;

    Total = 0;
    for( i = 0; i < g_iTeacherCount; i++ ) {
		Total += GetTeacherTimes( i, false );
    }

    return Total;
}

/****************************
  전체 학급 시수를 구한다.
*****************************/
long GetTotalClassTimes(void)
{
    int y, w, i, v;
    long Total;

    Total = 0;

    for( y = atYEAR_1; y <= atYEAR_MAX; y++ ){
      v = 0;

      for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
        v += GetWeekLimit(y,w) - atWEEK_BASE + 1;
      }
      for( i = 0; i < g_School.SPC_Count; i++ ){
        if( g_School.SPC[i].Years & SPC_CLASS_MASK_LST[y-atYEAR_BASE] ) v--;
      }

      v *= GetLimitClass(y) - atCLASS_BASE + 1;

      Total += v;
    }

	return Total;
}

/************************************
  해당 위치의 반이 중복되었는가?
*************************************/
bool IsOverlapClass( WORD t, WORD sw, WORD sn, WORD ew, WORD en )
{
	int i, cnt;
	TScheduleDataCell *sc1, *sc2;
	WORD cl;
	
	sc1 = GetScheduleDataCell(t, sw, sn);
	sc2 = GetScheduleDataCell(t, ew, en);

	if( sc1->ClassInfo == sc2->ClassInfo ){
	  cnt = GetClassCount( t, sw, sn );
	  for( i = 0; i < cnt; i++ ){
		cl = GetClassNo( t, sw, sn, i );
		if( (cl != 0) && IsEmbededClassNo( t, ew, en, cl ) ) return true;
	  }
	}

    return false;
}

/************************************
  해당 위치에 반이 배정될 수 있는가. 
  (초기 배치시에만 사용)
*************************************/
bool IsPutClassNo( WORD t, WORD w, WORD n, WORD ClassNo )
{
    if( (GetClassType( t, w, n ) == CT_NORMAL) &&
       IsEmptyClassNo( t, w, n ) &&
       (GetClassOverlapTeacher( t, w, n, ClassNo ) == -1) )
      return TRUE;
    else
      return FALSE;
}

/***********************
  빈 곳을 찾는다.
 (초기 배치시에만 사용)
************************/
bool PutClassToEmpty( int t, int c, int si, int opt )
{
  int w, n, t2, i2;

  if( opt > 5000 ) return FALSE;

//  y = GET_CLASS_YEAR(c);
  TTeacherSubject *sbj = GetTeacherSubject( t, si );

  // 배치 가능한 곳을 찾는다. 요일별로 골고루 퍼지게 하기 위해서 다중루프 순서를 수평에서 수직으로 바꿨다.
  for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
  	if( (sbj->TargetLessons & 0x8000) && !IS_LESSONS_IN(n, sbj->TargetLessons) ) continue;
    for( w = atWEEK_MON; w <= atWEEK_MAX; w++ ){
	  if( (sbj->TargetWeeks & 0x8000) && !IS_WEEKS_IN(w, sbj->TargetWeeks) ) continue;
	  // 겹쳐지는 교사가 없는 완전히 빈 곳이 있으면...
      if( IsPutClassNo( t, w, n, c ) ){
		ClearClasses( t, w, n );
		AddClassNo( t, w, n, c );
        SetClassInfo( t, w, n, si );
        return TRUE;
      }
    }
  }

  // 배치 가능한 곳이 없으면 옮기기 시작
  for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
  	if( (sbj->TargetLessons & 0x8000) && !IS_LESSONS_IN(n, sbj->TargetLessons) ) continue;
    for( w = atWEEK_MON; w <= atWEEK_MAX; w++ ){
	  if( (sbj->TargetWeeks & 0x8000) && !IS_WEEKS_IN(w, sbj->TargetWeeks) ) continue;
      if( IsEmptyClassNo( t, w, n ) ){
	  	// 겹쳐지는 새로운 교사를 구한다.
        t2 = GetClassOverlapTeacher( t, w, n, c );
        if( t2 < 0 ) continue;
//		if( GetClassType(t2, w, n) == CT_MOVELESSON ) continue;

        // 겹쳐지는 교사의 수업이 새로운 위치로 이동될 수 없을 땐...?
        int si2 = GetClassInfo( t2, w, n );
		TTeacherSubject *sbj2 = GetTeacherSubject( t2, si2 );
  	    if( (sbj2->TargetLessons & 0x8000) && !IS_LESSONS_IN(n, sbj2->TargetLessons) ) continue;
	    if( (sbj2->TargetWeeks & 0x8000) && !IS_WEEKS_IN(w, sbj2->TargetWeeks) ) continue;

        // 겹친 곳의 교사의 수업이 옮기는 것이 가능할 때...
        if( (GetClassType( t2, w, n ) == CT_NORMAL) ){
		  // 일단 못 썼던 것은 쓰고 본다.
		  ClearClasses( t, w, n );
	  	  AddClassNo( t, w, n, c );
          SetClassType( t, w, n, CT_TEMP );  // 다시 옮겨지지 않게 TEMP로...
//	      SetClassType( t, w, n, CT_NORMAL );
          SetClassInfo( t, w, n, si );

		  // 겹친 곳 교사의 정보를 지운다.
          i2 = GetClassInfo( t2, w, n );
		  ClearClasses( t2, w, n );

		  // 이제 새롭게 배치의 필요성이 생긴 겹치는 곳 교사 수업을 배치한다.
          if( PutClassToEmpty( t2, c, i2, opt+1 ) ){ // 재귀호출...
            SetClassType( t, w, n, CT_NORMAL ); // 성공했으면... TEMP를 NORMAL로...
            return TRUE;
          }
        }
      }
    }
  }

  return FALSE;
}



