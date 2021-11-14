//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SSC_File_ver300.h"
//----------------------------------------------------------------------------

/***********************************
  .STC ������ �ε��Ѵ�. (Ver 3)
************************************/
bool LoadSchoolData_ver300( FILE *fp )
{
    int y, w, i, cnt;
    TSCD_SchoolData_ver300 school_ver300;

    // �б� ���� ������ �б�
    fread( &school_ver300, sizeof(TSCD_SchoolData_ver300), 1, fp );
	strncpy( g_School.SchoolName, school_ver300.SchoolName, SCHOOL_NAME_SIZE );
	g_School.SchoolName[SCHOOL_NAME_SIZE] = '\0';
	
    for( y = 0; y < 3; y ++ ) {  // 1�г�~3�г�
      g_School.ClassCount[y] = school_ver300.ClassCount[y];
      for( w = 0; w < 6; w++ ) // ������~�����
        g_School.WeekLimit[y][w] = school_ver300.WeekLimit[y][w];
      g_School.SPC_Count = school_ver300.SPC_Count;
	  cnt = MIN( MAX_SPC_COUNT, SCD_MAX_SPC_COUNT_ver300 );
      for( i = 0; i < cnt; i++ ) {
        StrCopy( g_School.SPC[i].Name, school_ver300.SPC[i].Name );
        g_School.SPC[i].Years = school_ver300.SPC[i].Years;
        g_School.SPC[i].Pos[y].week = school_ver300.SPC[i].Pos[y].week;
        g_School.SPC[i].Pos[y].lesson = school_ver300.SPC[i].Pos[y].lesson;
      }
	  
	  g_School.LunchTime[y] = school_ver300.LunchTime[y];
    }

	return TRUE;
}


/***********************************
  .SCD ���Ϸ� ����. (Ver 3)
************************************/
bool SaveSchoolData_ver300( FILE *fp )
{
    int y, w, i, cnt;
    TSCD_SchoolData_ver300 school_ver300;

    // �б� ���� ������ ����
    memset( &school_ver300, 0, sizeof(TSCD_SchoolData_ver300) );
	strncpy( school_ver300.SchoolName, g_School.SchoolName, SCD_SCHOOL_NAME_SIZE_ver300 );

    for( y = 0; y < 3; y ++ ) {  // 1�г�~3�г�
      school_ver300.ClassCount[y] = g_School.ClassCount[y];
      for( w = 0; w < 6; w++ ) // ������~�����
        school_ver300.WeekLimit[y][w] = g_School.WeekLimit[y][w];
      school_ver300.SPC_Count = g_School.SPC_Count;
	  cnt = MIN( MAX_SPC_COUNT, SCD_MAX_SPC_COUNT_ver300 );
      for( i = 0; i < cnt; i++ ) {
        StrCopy( school_ver300.SPC[i].Name, g_School.SPC[i].Name );
        school_ver300.SPC[i].Years = g_School.SPC[i].Years;
        school_ver300.SPC[i].Pos[y].week = g_School.SPC[i].Pos[y].week;
        school_ver300.SPC[i].Pos[y].lesson = g_School.SPC[i].Pos[y].lesson;
      }
	  
	  school_ver300.LunchTime[y] = g_School.LunchTime[y];
    }
	
    fwrite( &school_ver300, sizeof(TSCD_SchoolData_ver300), 1, fp );

    return TRUE;
}
