//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SSC_File_ver3.h"
//----------------------------------------------------------------------------

/***********************************
  .STC 파일을 로드한다. (Ver 3)
************************************/
bool LoadSchoolData_ver3( FILE *fp )
{
    int y, w, i, cnt;
    TSCD_SchoolData_ver3 school_ver3;

    // 학교 기초 데이터 읽기
    fread( &school_ver3, sizeof(TSCD_SchoolData_ver3), 1, fp );
	strncpy( g_School.SchoolName, school_ver3.SchoolName, SCHOOL_NAME_SIZE );
	g_School.SchoolName[SCHOOL_NAME_SIZE] = '\0';
	
    for( y = 0; y < 3; y ++ ) {  // 1학년~3학년
      g_School.ClassCount[y] = school_ver3.ClassCount[y];
      for( w = 0; w < 6; w++ ) // 월요일~토요일
        g_School.WeekLimit[y][w] = school_ver3.WeekLimit[y][w];
      g_School.SPC_Count = school_ver3.SPC_Count;
	  cnt = MIN( MAX_SPC_COUNT, SCD_MAX_SPC_COUNT_VER3 );
      for( i = 0; i < cnt; i++ ) {
        StrCopy( g_School.SPC[i].Name, school_ver3.SPC[i].Name );
        g_School.SPC[i].Years = school_ver3.SPC[i].Years;
        g_School.SPC[i].Pos[y].week = school_ver3.SPC[i].Pos[y].week;
        g_School.SPC[i].Pos[y].lesson = school_ver3.SPC[i].Pos[y].lesson;
      }
	  
	  g_School.LunchTime[y] = school_ver3.LunchTime[y];
    }

	return TRUE;
}


/***********************************
  .SCD 파일로 쓴다. (Ver 3)
************************************/
bool SaveSchoolData_ver3( FILE *fp )
{
    int y, w, i, cnt;
    TSCD_SchoolData_ver3 school_ver3;

    // 학교 정보 데이터 쓰기
    memset( &school_ver3, 0, sizeof(TSCD_SchoolData_ver3) );
	strncpy( school_ver3.SchoolName, g_School.SchoolName, SCD_SCHOOL_NAME_SIZE_VER3 );

    for( y = 0; y < 3; y ++ ) {  // 1학년~3학년
      school_ver3.ClassCount[y] = g_School.ClassCount[y];
      for( w = 0; w < 6; w++ ) // 월요일~토요일
        school_ver3.WeekLimit[y][w] = g_School.WeekLimit[y][w];
      school_ver3.SPC_Count = g_School.SPC_Count;
	  cnt = MIN( MAX_SPC_COUNT, SCD_MAX_SPC_COUNT_VER3 );
      for( i = 0; i < cnt; i++ ) {
        StrCopy( school_ver3.SPC[i].Name, g_School.SPC[i].Name );
        school_ver3.SPC[i].Years = g_School.SPC[i].Years;
        school_ver3.SPC[i].Pos[y].week = g_School.SPC[i].Pos[y].week;
        school_ver3.SPC[i].Pos[y].lesson = g_School.SPC[i].Pos[y].lesson;
      }
	  
	  school_ver3.LunchTime[y] = g_School.LunchTime[y];
    }
	
    fwrite( &school_ver3, sizeof(TSCD_SchoolData_ver3), 1, fp );

    return TRUE;
}
