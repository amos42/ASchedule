//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
//----------------------------------------------------------------------------

#include <IniFiles.hpp>
#include <math.h>

static String WeekStr[6] = { "��", "ȭ", "��", "��", "��", "��" };
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

static int num1[atLESSON_MAX+1];
static int wek1[atWEEK_MAX+1];


/***********************************
  ������ �����͸� �ʱ�ȭ�Ѵ�.
************************************/
void InitScheduleSystem(void)
{
	int i, j, n;
	
    // ���� �ڷ� �ʱ�ȭ
    ZeroMemory( &g_School, sizeof(TSchoolData) );

  	g_iTeacherCount = 0;
	g_iMoveLessonCount = 0;

    SetCurSchedules( 0 );

    ClearScheduleData();
	
	for( i = atLESSON_1; i <= atLESSON_MAX; i++ ){
		while(1){
		   n = random(atLESSON_MAX-atLESSON_BASE+1) + atLESSON_BASE;
		   for( j = atLESSON_1; j < i; j++ ){
			  if( num1[j] == n ) break;
		   }
		   if( i == j ){
			 num1[i] = n;
			 break;
		   }
		}
	}
	for( i = atWEEK_MON; i <= atWEEK_MAX; i++ ){
		while(1){
		   n = random(atWEEK_MAX-atWEEK_BASE+1) + atWEEK_BASE;
		   for( j = atWEEK_MON; j < i; j++ ){
			  if( wek1[j] == n ) break;
		   }
		   if( i == j ){
			 wek1[i] = n;
			 break;
		   }
		}
	}

}


/***********************************
  INI ���Ͽ��� ���� ���� �д´�.
************************************/
void LoadConfigData(void)
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
  INI ���Ͽ� ���� ���� ����.
************************************/
void SaveConfigData(void)
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
  ������ �����͸� �Ҵ��Ѵ�.
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
  ������ �����͸� �Ҵ��Ѵ�.
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
  ������ �����͸� �Ҵ��Ѵ�.
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
  ������ �����͸� ���Ҵ��Ѵ�.
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
  �̵����� �����͸� �Ҵ��Ѵ�.
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
  �̵����� �����͸� ���Ҵ��Ѵ�.
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
 
************************************/
String GetMoveLessonString( int info )
{
    TMoveLessonData *ml;
    TSubject *sbj;
    String s;

    if( (info < 0) || (info >= g_iMoveLessonCount) ) return "";

    ml = &g_pMoveLesson[info];

    sbj = GetSubject( ml->SubjectCode );
    s = (String)"(" + ((sbj)?sbj->FullName:"<<null>>") + ") ";
    s += IntToStr(ml->Classes.Part.Year) + "�г� :";

    for( int i = atCLASS_1; i < atCLASS_MAX; i++ ){
       if( IS_CLASSES_IN( i, ml->Classes.Part.Classes ) )
         s += " " + IntToStr(i);
    }

    return s;
}


/***********************************
  ������ �����͸� �Ҵ��Ѵ�.
************************************/
bool InitScheduleData(void)
{
    if( g_pWorkSchedules != NULL ) free( g_pWorkSchedules );
    if( g_pSchedules != NULL ) free( g_pSchedules );

    if( g_iTeacherCount > 0 ){
      g_pSchedules = (PScheduleData)malloc( sizeof(TScheduleData) * g_iTeacherCount );
	  memset( g_pSchedules, 0, sizeof(TScheduleData) * g_iTeacherCount );
      g_pWorkSchedules = (PScheduleData)malloc( sizeof(TScheduleData) * g_iTeacherCount );
      // memset( g_pWorkSchedules, 0, sizeof(TScheduleData) * g_iTeacherCount ); // ���� ���� �ʿ������...
    } else {
      g_pSchedules = NULL;
      g_pWorkSchedules = NULL;
    }

	g_pCurSchedules = g_pSchedules;

	return true;
}


/***********************************
  ������ �����͸� û���Ѵ�.
************************************/
void ClearScheduleData(void)
{
    int t, w, n;
//    TScheduleDataCell *sc;

  // ������ ����ü �ʱ�ȭ
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
  ������ �����͸�
  �۾� �������� ����
*************************/
void CopyToWorkSchedules(void)
{
    if( g_pWorkSchedules != NULL )
      CopyMemory( g_pWorkSchedules, g_pSchedules, sizeof(TScheduleData)*g_iTeacherCount );
}


/************************
  �۾� ��������
  ������ �����͸� ����
*************************/
void CopyFromWorkSchedules(void)
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
  ���� �۾� �����
  ������ ������ ���
*************************/
int GetCurSchedules(void)
{
    if( g_pCurSchedules == g_pSchedules ) return 0;
	else if( g_pCurSchedules == g_pWorkSchedules ) return 1;
	else return -1;
}

/************************
  ���� �۾� �����
  ������ ������ ����
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
  �� ��ñ��� �ִ��� ��´�.
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
int GetScrambleNum( int n )
{
	return num1[n];
}


/***********************************

************************************/
int GetScrambleWeek( int n )
{
	return wek1[n];
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
  ������ ��ġ�� Ŭ���� ��ȣ ����
************************************/
void PackTeacherSubject( int t )
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
    s += IntToStr(tsbj->Classes.Part.Year) + "�г� :";

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
  Ư������ ���� �Ǵ�.
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
  Ư������ ���� �Ǵ�.
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
  ������ ��ġ�� Ŭ���� Ÿ�� ��Ʈ
************************************/
void SetClassType( int t, int w, int n, int ClassType )
{
    GetScheduleDataCell( t, w, n )->ClassType = ClassType;
}


/***********************************
  ������ ��ġ�� Ŭ���� ��ȣ ��Ʈ
************************************/
void SetClassNo( int t, int w, int n, int ClassNo )
{
    TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );
	
    sc->Classes.Part.Year = GET_CLASS_YEAR(ClassNo);
    sc->Classes.Part.Classes = 1 << (GET_CLASS_CLASS(ClassNo)-atCLASS_BASE);
}

/***********************************
  ������ ��ġ�� Ŭ���� ��ȣ ��Ʈ
************************************/
void SetClassesFull( int t, int w, int n, unsigned long ClassNoFull )
{
    GetScheduleDataCell( t, w, n )->Classes.FullValue = ClassNoFull;
}

/***********************************
  ������ ��ġ�� Ŭ���� ��ȣ ��Ʈ
************************************/
unsigned long GetClassesFull( int t, int w, int n )
{
    return GetScheduleDataCell( t, w, n )->Classes.FullValue;
}

/***********************************
  ������ ��ġ�� Ŭ���� ��ȣ ����
************************************/
void RemoveClassNo( int t, int w, int n, int ClassNo )
{
//    GetScheduleDataCell( t, w, n )->Classes.Part.Year = GET_CLASS_YEAR(ClassNo);
    TScheduleDataCell *sc = GetScheduleDataCell( t, w, n );
    sc->Classes.Part.Classes &= ~(1 << (GET_CLASS_CLASS(ClassNo)-atCLASS_BASE));
	if( sc->Classes.Part.Classes == 0) sc->Classes.Part.Year = 0; // �б��� �� �������� �г⵵ ���ش�.
}


/***********************************
  ������ ��ġ�� Ŭ���� ��ȣ �߰�
************************************/
int AddClassNo( int t, int w, int n, int ClassNo )
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
  ������ ��ġ�� Ŭ���� ��ȣ ����
************************************/
void ClearClasses( int t, int w, int n )
{
/*
    int i;
	for( i = 0; i < MAX_MULTILESSON_CLASS; i++ )
		SetClassNo( t, w, n, i, 0 );
*/		
	SetClassesFull( t, w, n, 0 );
}


/***********************************
  ������ ��ġ�� Ŭ���� ��ȣ ����
************************************/
/*
void PackClassNo( int t, int w, int n )
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
  ������ ��ġ�� Ŭ���� ���� ��Ʈ
************************************/
void SetClassInfo( int t, int w, int n, int ClassInfo )
{
    GetScheduleDataCell( t, w, n )->ClassInfo = ClassInfo;
}


/***********************************
  ������ ��ġ�� Ŭ���� Ÿ�� ����
************************************/
int GetClassType( int t, int w, int n )
{
    return GetScheduleDataCell( t, w, n )->ClassType;
}


/***********************************
  ������ ��ġ�� Ŭ���� ��ȣ ���� ����
************************************/
int GetClassCount( int t, int w, int n )
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
  ������ ��ġ�� Ŭ���� ��ȣ �߰� �����Ѱ�
************************************/
bool IsEmptyClassNo( int t, int w, int n )
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
  ������ ��ġ�� Ŭ���� ��ȣ �߰� �����Ѱ�
************************************/
bool IsCanAddClassNo( int t, int w, int n )
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
  ������ ��ġ�� Ŭ���� ��ȣ�� ���ԵǾ� �ֳ�.
************************************/
bool IsEmbededClassNo( int t, int w, int n, int ClassNo )
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
  ������ ��ġ�� Ŭ���� ��ȣ ����
************************************/
WORD GetClassNo( int t, int w, int n, int idx )
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
  ������ ��ġ�� Ŭ���� ���� ����
************************************/
WORD GetClassInfo( int t, int w, int n )
{
    return GetScheduleDataCell( t, w, n )->ClassInfo;
}

/***************************************************
  �ش� ������ �ش� Ŭ������ �ߺ��Ǵ� ���縦 ���Ѵ�.
****************************************************/
int GetClassOverlapTeacher( int t, int w, int n, WORD c )
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
  �� �ݰ� �ش� ���縦 �ٲ۴�.
*****************************/
void SwapClass( int t, int sw, int sn, int ew, int en )
{
    TScheduleDataCell *sc1, *sc2, temp;

    sc1 = GetScheduleDataCell( t, sw, sn );
    sc2 = GetScheduleDataCell( t, ew, en );

    temp = *sc1;
    *sc1 = *sc2;
    *sc2 = temp;
}


/****************************
  �ش� ���� �ü��� ���Ѵ�.
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
  ��ü ���� �ü��� ���Ѵ�.
  (�̵����� ����)
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
  ��ü �б� �ü��� ���Ѵ�.
  (�̵����� ����)
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

/****************************
  �̵����� �ü��� ���Ѵ�.
*****************************/
long GetTotalMoveLessonTimes(void)
{
    int i;
	TMoveLessonData *ml;
    long Total;

    Total = 0;

    for( i = 0; i < g_iMoveLessonCount; i++ ){
      ml = &g_pMoveLesson[i];

      Total += ml->TeacherCount * ml->Times;
    }

	return Total;
}

/************************************
  �ش� ��ġ�� ���� �ߺ��Ǿ��°�?
*************************************/
bool IsOverlapClass( int t, int sw, int sn, int ew, int en )
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
  �ش� ��ġ�� ���� ������ �� �ִ°�. 
  (�ʱ� ��ġ�ÿ��� ���)
*************************************/
bool IsPutClassNo( int t, int w, int n, int ClassNo )
{
    if( (GetClassType( t, w, n ) == CT_NORMAL) &&
       IsEmptyClassNo( t, w, n ) &&
       (GetClassOverlapTeacher( t, w, n, ClassNo ) == -1) )
      return TRUE;
    else
      return FALSE;
}

/***********************
  �� ���� ã�´�.
 (�ʱ� ��ġ�ÿ��� ���)
************************/
#include <stdlib.h>
bool PutClassToEmpty( int t, int c, int si, int opt )
{
  int w, n, t2, i2;
  int w0, n0;

  if( opt > 5000 ) return FALSE;

//  y = GET_CLASS_YEAR(c);
  TTeacherSubject *sbj = GetTeacherSubject( t, si );

  // ��ġ ������ ���� ã�´�. ���Ϻ��� ����� ������ �ϱ� ���ؼ� ���߷��� ������ ���򿡼� �������� �ٲ��.
  for( n0 = atLESSON_1; n0 <= atLESSON_MAX; n0++ ){
  	n = num1[n0];
//  for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
  	if( (sbj->LimitLessons & 0x8000) && !IS_LESSONS_IN(n, sbj->LimitLessons) ) continue;
    for( w0 = atWEEK_MON; w0 <= atWEEK_MAX; w0++ ){
	  w = wek1[w0];
//	for( w = atWEEK_MON; w <= atWEEK_MAX; w++ ){
	  if( (sbj->LimitWeeks & 0x8000) && !IS_WEEKS_IN(w, sbj->LimitWeeks) ) continue;
	  // �������� ���簡 ���� ������ �� ���� ������...
      if( IsPutClassNo( t, w, n, c ) ){
		ClearClasses( t, w, n );
		AddClassNo( t, w, n, c );
        SetClassInfo( t, w, n, si );
        return TRUE;
      }
    }
  }

  // ��ġ ������ ���� ������ �ű�� ����
  for( n0 = atLESSON_1; n0 <= atLESSON_MAX; n0++ ){
  	n = GetScrambleNum(n0);
  	if( (sbj->LimitLessons & 0x8000) && !IS_LESSONS_IN(n, sbj->LimitLessons) ) continue;
    for( w0 = atWEEK_MON; w0 <= atWEEK_MAX; w0++ ){
	  w = GetScrambleWeek(w0);
	  if( (sbj->LimitWeeks & 0x8000) && !IS_WEEKS_IN(w, sbj->LimitWeeks) ) continue;
      if( IsEmptyClassNo( t, w, n ) ){
	  	// �������� ���ο� ���縦 ���Ѵ�.
        t2 = GetClassOverlapTeacher( t, w, n, c );
        if( t2 < 0 ) continue;
//		if( GetClassType(t2, w, n) == CT_MOVELESSON ) continue;

        // �������� ������ ������ ���ο� ��ġ�� �̵��� �� ���� ��...?
        int si2 = GetClassInfo( t2, w, n );
		TTeacherSubject *sbj2 = GetTeacherSubject( t2, si2 );
  	    if( (sbj2->LimitLessons & 0x8000) && !IS_LESSONS_IN(n, sbj2->LimitLessons) ) continue;
	    if( (sbj2->LimitWeeks & 0x8000) && !IS_WEEKS_IN(w, sbj2->LimitWeeks) ) continue;

        // ��ģ ���� ������ ������ �ű�� ���� ������ ��...
        if( (GetClassType( t2, w, n ) == CT_NORMAL) ){
		  // �ϴ� �� ��� ���� ���� ����.
		  ClearClasses( t, w, n );
	  	  AddClassNo( t, w, n, c );
          SetClassType( t, w, n, CT_TEMP );  // �ٽ� �Ű����� �ʰ� TEMP��...
          SetClassInfo( t, w, n, si );

		  // ��ģ �� ������ ������ �����.
          i2 = GetClassInfo( t2, w, n );
	  	  ClearClasses( t2, w, n );

		  // ���� ���Ӱ� ��ġ�� �ʿ伺�� ���� ��ġ�� �� ���� ������ ��ġ�Ѵ�.
          if( PutClassToEmpty( t2, c, i2, opt+1 ) ){ // ���ȣ��...
            SetClassType( t, w, n, CT_NORMAL ); // ����������... TEMP�� NORMAL��...
            return TRUE;
          }
        }
      }
    }
  }

  return FALSE;
}


