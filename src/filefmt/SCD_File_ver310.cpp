//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SSC_File_ver300.h"
#include "SSB_File_ver300.h"
#include "STC_File_ver300.h"
#include "SCD_File_ver310.h"
//----------------------------------------------------------------------------


/***********************************
  .SCD ������ �ε��Ѵ�. (Ver 3)
************************************/
bool LoadScheduleData_ver310( FILE *fp )
{
    int t, w, n, i, j;
	int cnt;
    TSCD_ScheduleInfo_ver310 schedule_info_ver310;
    TSCD_MoveLessonData_ver310 movelesson_data_ver310;
    TSCD_ScheduleData_ver310 schedule_data_ver310;
    int tc;

    // �ð�ǥ ���� �б�
    fread( &schedule_info_ver310, sizeof(TSCD_ScheduleInfo_ver310), 1, fp );
    memset( &g_ScheduleInfo, 0, sizeof(TScheduleInfo) );
	strcpy( g_ScheduleInfo.ScheduleTitle, schedule_info_ver310.ScheduleTitle );
	strcpy( g_ScheduleInfo.AuthorName, schedule_info_ver310.AuthorName );
	strcpy( g_ScheduleInfo.AuthorDate, schedule_info_ver310.AuthorDate );
	strcpy( g_ScheduleInfo.Memo, schedule_info_ver310.Memo );

    // �б� ������ �д´�.
    LoadSchoolData_ver300( fp );

    // ���� ������ �д´�.
    LoadSubjectData_ver300( fp );

    // ���� ������ �д´�.
    LoadTeacherData_ver300( fp );

    // �̵����� ���� �б�
    fread( &tc, sizeof(long), 1, fp );
    InitMoveLessonData( tc );
	if( g_iMoveLessonCount > 0 ){
      for( i = 0; i < g_iMoveLessonCount; i++ ){
        memset( &g_pMoveLesson[i], 0, sizeof(TMoveLessonData) );
        fread( &movelesson_data_ver310, sizeof(TSCD_MoveLessonData_ver310), 1, fp );

        strncpy( g_pMoveLesson[i].LessonName, movelesson_data_ver310.LessonName, MOVELESSON_NAME_SIZE );
        g_pMoveLesson[i].LessonName[MOVELESSON_NAME_SIZE] = '\0';
        strncpy( g_pMoveLesson[i].ShortName, movelesson_data_ver310.ShortName, MOVELESSON_SHORTNAME_SIZE );
        g_pMoveLesson[i].ShortName[MOVELESSON_SHORTNAME_SIZE] = '\0';
        g_pMoveLesson[i].SubjectCode = movelesson_data_ver310.SubjectCode;
	    g_pMoveLesson[i].Classes.FullValue = movelesson_data_ver310.Classes.FullValue;
	    g_pMoveLesson[i].TeacherCount = movelesson_data_ver310.TeacherCount;
        for( j = 0; j < movelesson_data_ver310.TeacherCount; j++ )
	      g_pMoveLesson[i].Teachers[j] = movelesson_data_ver310.Teachers[j];
	    g_pMoveLesson[i].Times = movelesson_data_ver310.Times;
        for( j = 0; j < movelesson_data_ver310.Times; j++ ){
	      g_pMoveLesson[i].pos[j].week = movelesson_data_ver310.pos[j].week;
	      g_pMoveLesson[i].pos[j].lesson = movelesson_data_ver310.pos[j].lesson;
        }
      }
	}

    // �ð�ǥ ������ �б�
    if( g_iTeacherCount > 0 ){
      for( t = 0; t < g_iTeacherCount; t++ ) {
        fread( &schedule_data_ver310, sizeof(TSCD_ScheduleData_ver310), 1, fp );

        for( w = 0; w < 6; w++ ){
          for( n = 0; n < 8; n++ ){
            SetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver310[w][n].ClassType );
			SetClassesFull( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver310[w][n].Classes.FullValue );
            SetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver310[w][n].ClassInfo );
          }
        }
      }
    }

    return TRUE;
}


/***********************************
  .SCD ���Ϸ� ����. (Ver 3)
************************************/
bool SaveScheduleData_ver310( FILE *fp )
{
    int t, w, n, i, j;
    int cnt;
    TSCD_ScheduleInfo_ver310 schedule_info_ver310;
    TSCD_MoveLessonData_ver310 movelesson_data_ver310;
    TSCD_ScheduleData_ver310 schedule_data_ver310;

    // �ð�ǥ ���� ����
    memset( &schedule_info_ver310, 0, sizeof(TSCD_ScheduleInfo_ver310) );
	strcpy( schedule_info_ver310.ScheduleTitle, g_ScheduleInfo.ScheduleTitle );
	strcpy( schedule_info_ver310.AuthorName, g_ScheduleInfo.AuthorName );
	strcpy( schedule_info_ver310.AuthorDate, g_ScheduleInfo.AuthorDate );
	strcpy( schedule_info_ver310.Memo, g_ScheduleInfo.Memo );
    fwrite( &schedule_info_ver310, sizeof(TSCD_ScheduleInfo_ver310), 1, fp );

    // �б� ������ ����.
    SaveSchoolData_ver300( fp );

    // ���� ������ ����.
    SaveSubjectData_ver300( fp );

    // ���� ������ ����.
    SaveTeacherData_ver300( fp );

    // �̵����� ���� ����
    fwrite( &g_iMoveLessonCount, sizeof(long), 1, fp );
	if( g_iMoveLessonCount > 0 ){
      for( i = 0; i < g_iMoveLessonCount; i++ ){
        memset( &movelesson_data_ver310, 0, sizeof(TSCD_MoveLessonData_ver310) );

        strncpy( movelesson_data_ver310.LessonName, g_pMoveLesson[i].LessonName, SCD_MOVELESSON_NAME_SIZE_ver310 );
        strncpy( movelesson_data_ver310.ShortName, g_pMoveLesson[i].ShortName, SCD_MOVELESSON_SHORTNAME_SIZE_ver310 );
        movelesson_data_ver310.SubjectCode = g_pMoveLesson[i].SubjectCode;
	    movelesson_data_ver310.Classes.FullValue = g_pMoveLesson[i].Classes.FullValue;
	    movelesson_data_ver310.TeacherCount = g_pMoveLesson[i].TeacherCount;
        for( j = 0; j < movelesson_data_ver310.TeacherCount; j++ )
	      movelesson_data_ver310.Teachers[j] = g_pMoveLesson[i].Teachers[j];
	    movelesson_data_ver310.Times = g_pMoveLesson[i].Times;
        for( j = 0; j < movelesson_data_ver310.Times; j++ ){
	      movelesson_data_ver310.pos[j].week = g_pMoveLesson[i].pos[j].week;
	      movelesson_data_ver310.pos[j].lesson = g_pMoveLesson[i].pos[j].lesson;
        }

        fwrite( &movelesson_data_ver310, sizeof(TSCD_MoveLessonData_ver310), 1, fp );
      }
	}

    // �ð�ǥ ������ ����
    if( g_iTeacherCount > 0 ){
	  for( t = 0; t < g_iTeacherCount; t++ ) {
        memset( &schedule_data_ver310, 0, sizeof(TSCD_ScheduleData_ver310) );
		for( w = 0; w < 6; w++ ){
		  for( n = 0; n < 8; n++ ){
//            PackClassNo( t, w+atWEEK_BASE, n+atLESSON_BASE );
			schedule_data_ver310[w][n].ClassType = GetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE );
		    schedule_data_ver310[w][n].Classes.FullValue = GetClassesFull( t, w+atWEEK_BASE, n+atLESSON_BASE );
			schedule_data_ver310[w][n].ClassInfo = GetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE );
		  }
		}

        fwrite( &schedule_data_ver310, sizeof(TSCD_ScheduleData_ver310), 1, fp );
      }
    }

    return TRUE;
}