//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SCD_File_ver100.h"
//----------------------------------------------------------------------------

/***********************************
  .SCD 파일을 로드한다. (Ver 1)
************************************/
bool LoadScheduleData_ver100( FILE *fp )
{
#if 0
    int f;
    int i, j, k, t, w, n, x;
    TSCD_ScheduleFileHeader hdr;
    PScheduleData ts;
    PTeacherData tt;
    TSCD_SchoolData_ver100 school_ver100;
    TSCD_TeacherData_ver100 *pTeacher2, *tt2;
    TSCD_ScheduleData_ver100 schedule_data_ver100;
    int tc;

    f = FileOpen( filename, fmOpenRead );

    // 헤더 읽기
    FileRead( f, &hdr, sizeof(TSCD_ScheduleFileHeader) );
    if( StrComp(hdr.HeaderStr, "Amos Schedule Data;") != 0 ){
      FileClose( f );
      return false;
    }
    if( hdr.Version != 1 ){
      FileClose( f );
      return false;
    }

    FileRead( f, &school_ver100, sizeof(TSCD_SchoolData_ver100) );
    for( i = 0; i < 3; i ++ ) {
      g_School.ClassCount[i] = school_ver100.ClassCount[i];
      for( j = atWEEK_MON; j <= atWEEK_SAT; j++ )
        g_School.WeekLimit[i][j] = school_ver100.WeekLimit[i][j];
      g_School.SPC_Count = school_ver100.SPC_Count;
      for( j = 0; j < MAX_SPC_COUNT_ver100; j++ ) {
        StrCopy( g_School.SPC[j].Name, school_ver100.SPC_Name[j] );
        g_School.SPC[j].Years = SPC_CLASS1_MASK | SPC_CLASS2_MASK | SPC_CLASS3_MASK;
        g_School.SPC[j].Pos[i].week = school_ver100.SPC[j][i].week;
        g_School.SPC[j].Pos[i].lesson = school_ver100.SPC[j][i].lesson;
      }
    }
    g_School.LunchTime = school_ver100.LunchTime;

    // 교사 수 읽기
    FileRead( f, &tc, sizeof(long) );

    // 교사수만큼 메모리 할당
    AllocScheduleData( tc );

    pTeacher2 = (TSCD_TeacherData_ver100 *)malloc( sizeof(TSCD_TeacherData_ver100) * g_iTeacherCount );
    tt2 = pTeacher2;
    tt = g_pTeachers;
    for( i = 0; i < g_iTeacherCount; i++ ) {
      FileRead( f, tt2, sizeof(TSCD_TeacherData_ver100) );

      tt->TeacherNo = tt2->TeacherNo;
      StrCopy( tt->TeacherName, tt2->TeacherName );
      for( j = 0; j < 3; j++ ) {
        for( k = 0; j < 3; k++ ) {
          StrCopy( tt->Subject[j][k].Name, tt2->Subject[j][k] );
          tt->Subject[j][k].StartClass = tt2->StartClass[j][k];
          tt->Subject[j][k].EndClass = tt2->EndClass[j][k];
          tt->Subject[j][k].Times = tt2->Times[j][k];
        }
      }

      tt2++;
      tt++;
    }
    free( pTeacher2 );

    // 시간표 데이터 읽기
    for( t = 0; t < g_iTeacherCount; t++ ) {
      FileRead( f, &schedule_data_ver100, sizeof(TSCD_ScheduleData_ver100) );

      for( w = 0; w < 7; w++ ){
        for( n = 0; n < 8; n++ ){
          SetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver100[w][n].ClassType );
          SetClassNo1( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver100[w][n].ClassNo );
          SetClassNo2( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver100[w][n].ClassNo2 );
          x = schedule_data_ver100[w][n].ClassInfo;
          if( x > 0 ) x -= 1; // 버전 탓... --;
          SetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE, x );
        }
      }
    }

    FileClose(f);

    return TRUE;
#else
    return FALSE;
#endif
}


/*******************************************
  .SCD 파일로 쓴다. (Ver 1)
  과거 파일 읽기 위해 만든 모듈이기 때문에,
  쓰기 기능은 필요 없어서 구현 안 함.
********************************************/
bool SaveScheduleData_ver100( FILE *fp )
{
    return FALSE;
}

