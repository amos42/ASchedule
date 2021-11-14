//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SSC_File_ver3.h"
#include "SSB_File_ver3.h"
#include "STC_File_ver3.h"
#include "SCD_File_ver3.h"
//----------------------------------------------------------------------------


/*
#pragma pack(push, 1)
typedef struct __TMoveLessonData_xxx {
	char LessonName[20+1 + 1];
	char SubjectName[4+1 + 1]; // add '\0' and dummy
	TClasses Classes;
	long TeacherCount;
	long Teachers[SCD_MAX_MOVELESSON_TEACHERS_VER3];
	long Times;
	TClassPos pos[SCD_MAX_MOVELESSON_TIMES_VER3];
} TMoveLessonData_xxx;
#pragma pack(pop)
*/

/***********************************
  .SCD ������ �ε��Ѵ�. (Ver 3)
************************************/
/*
bool LoadScheduleData_ver3( FILE *fp )
{
    int t, w, n, i, j;
	int cnt;
    TSCD_ScheduleInfo_ver3 schedule_info_ver3;
//    TSCD_MoveLessonData_ver3 movelesson_data_ver3;
    TMoveLessonData_xxx movelesson_data_ver3;
    TSCD_ScheduleData_ver3 schedule_data_ver3;
    int tc;

    // �ð�ǥ ���� �б�
    fread( &schedule_info_ver3, sizeof(TSCD_ScheduleInfo_ver3), 1, fp );
    memset( &g_ScheduleInfo, 0, sizeof(TScheduleInfo) );
	strcpy( g_ScheduleInfo.ScheduleTitle, schedule_info_ver3.ScheduleTitle );
	strcpy( g_ScheduleInfo.AuthorName, schedule_info_ver3.AuthorName );
	strcpy( g_ScheduleInfo.AuthorDate, schedule_info_ver3.AuthorDate );
	strcpy( g_ScheduleInfo.Memo, schedule_info_ver3.Memo );

    // �б� ������ �д´�.
    LoadSchoolData_ver3( fp );

    // ���� ������ �д´�.
    LoadTeacherData_ver3( fp );

    // �̵����� ���� �б�
    fread( &tc, sizeof(long), 1, fp );
    InitMoveLessonData( tc );
	if( g_iMoveLessonCount > 0 ){
      for( i = 0; i < g_iMoveLessonCount; i++ ){
        memset( &g_pMoveLesson[i], 0, sizeof(TMoveLessonData) );
//        fread( &movelesson_data_ver3, sizeof(TSCD_MoveLessonData_ver3), 1, fp );
        fread( &movelesson_data_ver3, sizeof(TMoveLessonData_xxx), 1, fp );

        strncpy( g_pMoveLesson[i].LessonName, movelesson_data_ver3.LessonName, MOVELESSON_NAME_SIZE );
        g_pMoveLesson[i].LessonName[MOVELESSON_NAME_SIZE] = '\0';
        strncpy( g_pMoveLesson[i].SubjectName, movelesson_data_ver3.SubjectName, SUBJECT_SHORTNAME_SIZE );
        g_pMoveLesson[i].SubjectName[SUBJECT_SHORTNAME_SIZE] = '\0';
	    g_pMoveLesson[i].Classes.FullValue = movelesson_data_ver3.Classes.FullValue;
	    g_pMoveLesson[i].TeacherCount = movelesson_data_ver3.TeacherCount;
        for( j = 0; j < movelesson_data_ver3.TeacherCount; j++ )
	      g_pMoveLesson[i].Teachers[j] = movelesson_data_ver3.Teachers[j];
//	    g_pMoveLesson[i].Times = movelesson_data_ver3.Times;
g_pMoveLesson[i].Times = 0;
//        for( j = 0; j < movelesson_data_ver3.Times; j++ ){
for( j = 0; j < SCD_MAX_MOVELESSON_TIMES_VER3; j++ ){
	      g_pMoveLesson[i].pos[j].week = movelesson_data_ver3.pos[j].week;
	      g_pMoveLesson[i].pos[j].lesson = movelesson_data_ver3.pos[j].lesson;
if( g_pMoveLesson[i].pos[j].week != 0 ) g_pMoveLesson[i].Times++;
        }
      }
	}

    // �ð�ǥ ������ �б�
    if( g_iTeacherCount > 0 ){
      for( t = 0; t < g_iTeacherCount; t++ ) {
        fread( &schedule_data_ver3, sizeof(TSCD_ScheduleData_ver3), 1, fp );

        for( w = 0; w < 6; w++ ){
          for( n = 0; n < 8; n++ ){
            SetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver3[w][n].ClassType );
			SetClassesFull( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver3[w][n].Classes.FullValue );
            SetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver3[w][n].ClassInfo );
          }
        }
      }
    }

    return TRUE;
}
*/
bool LoadScheduleData_ver3( FILE *fp )
{
    int t, w, n, i, j;
	int cnt;
    TSCD_ScheduleInfo_ver3 schedule_info_ver3;
    TSCD_MoveLessonData_ver3 movelesson_data_ver3;
    TSCD_ScheduleData_ver3 schedule_data_ver3;
    int tc;

    // �ð�ǥ ���� �б�
    fread( &schedule_info_ver3, sizeof(TSCD_ScheduleInfo_ver3), 1, fp );
    memset( &g_ScheduleInfo, 0, sizeof(TScheduleInfo) );
	strcpy( g_ScheduleInfo.ScheduleTitle, schedule_info_ver3.ScheduleTitle );
	strcpy( g_ScheduleInfo.AuthorName, schedule_info_ver3.AuthorName );
	strcpy( g_ScheduleInfo.AuthorDate, schedule_info_ver3.AuthorDate );
	strcpy( g_ScheduleInfo.Memo, schedule_info_ver3.Memo );

    // �б� ������ �д´�.
    LoadSchoolData_ver3( fp );

    // ���� ������ �д´�.
    LoadSubjectData_ver3( fp );

    // ���� ������ �д´�.
    LoadTeacherData_ver3( fp );

    // �̵����� ���� �б�
    fread( &tc, sizeof(long), 1, fp );
    InitMoveLessonData( tc );
	if( g_iMoveLessonCount > 0 ){
      for( i = 0; i < g_iMoveLessonCount; i++ ){
        memset( &g_pMoveLesson[i], 0, sizeof(TMoveLessonData) );
        fread( &movelesson_data_ver3, sizeof(TSCD_MoveLessonData_ver3), 1, fp );

        strncpy( g_pMoveLesson[i].LessonName, movelesson_data_ver3.LessonName, MOVELESSON_NAME_SIZE );
        g_pMoveLesson[i].LessonName[MOVELESSON_NAME_SIZE] = '\0';
        g_pMoveLesson[i].SubjectCode = movelesson_data_ver3.SubjectCode;
	    g_pMoveLesson[i].Classes.FullValue = movelesson_data_ver3.Classes.FullValue;
	    g_pMoveLesson[i].TeacherCount = movelesson_data_ver3.TeacherCount;
        for( j = 0; j < movelesson_data_ver3.TeacherCount; j++ )
	      g_pMoveLesson[i].Teachers[j] = movelesson_data_ver3.Teachers[j];
	    g_pMoveLesson[i].Times = movelesson_data_ver3.Times;
        for( j = 0; j < movelesson_data_ver3.Times; j++ ){
	      g_pMoveLesson[i].pos[j].week = movelesson_data_ver3.pos[j].week;
	      g_pMoveLesson[i].pos[j].lesson = movelesson_data_ver3.pos[j].lesson;
        }
      }
	}

    // �ð�ǥ ������ �б�
    if( g_iTeacherCount > 0 ){
      for( t = 0; t < g_iTeacherCount; t++ ) {
        fread( &schedule_data_ver3, sizeof(TSCD_ScheduleData_ver3), 1, fp );

        for( w = 0; w < 6; w++ ){
          for( n = 0; n < 8; n++ ){
            SetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver3[w][n].ClassType );
			SetClassesFull( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver3[w][n].Classes.FullValue );
            SetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver3[w][n].ClassInfo );
          }
        }
      }
    }

    return TRUE;
}


/***********************************
  .SCD ���Ϸ� ����. (Ver 3)
************************************/
bool SaveScheduleData_ver3( FILE *fp )
{
    int t, w, n, i, j;
    int cnt;
    TSCD_ScheduleInfo_ver3 schedule_info_ver3;
    TSCD_MoveLessonData_ver3 movelesson_data_ver3;
    TSCD_ScheduleData_ver3 schedule_data_ver3;

    // �ð�ǥ ���� ����
    memset( &schedule_info_ver3, 0, sizeof(TSCD_ScheduleInfo_ver3) );
	strcpy( schedule_info_ver3.ScheduleTitle, g_ScheduleInfo.ScheduleTitle );
	strcpy( schedule_info_ver3.AuthorName, g_ScheduleInfo.AuthorName );
	strcpy( schedule_info_ver3.AuthorDate, g_ScheduleInfo.AuthorDate );
	strcpy( schedule_info_ver3.Memo, g_ScheduleInfo.Memo );
    fwrite( &schedule_info_ver3, sizeof(TSCD_ScheduleInfo_ver3), 1, fp );

    // �б� ������ ����.
    SaveSchoolData_ver3( fp );

    // ���� ������ ����.
    SaveSubjectData_ver3( fp );

    // ���� ������ ����.
    SaveTeacherData_ver3( fp );

    // �̵����� ���� ����
    fwrite( &g_iMoveLessonCount, sizeof(long), 1, fp );
	if( g_iMoveLessonCount > 0 ){
      for( i = 0; i < g_iMoveLessonCount; i++ ){
        memset( &movelesson_data_ver3, 0, sizeof(TSCD_MoveLessonData_ver3) );

        strncpy( movelesson_data_ver3.LessonName, g_pMoveLesson[i].LessonName, SCD_MOVELESSON_NAME_SIZE_VER3 );
        movelesson_data_ver3.SubjectCode = g_pMoveLesson[i].SubjectCode;
	    movelesson_data_ver3.Classes.FullValue = g_pMoveLesson[i].Classes.FullValue;
	    movelesson_data_ver3.TeacherCount = g_pMoveLesson[i].TeacherCount;
        for( j = 0; j < movelesson_data_ver3.TeacherCount; j++ )
        movelesson_data_ver3.Teachers[j] = g_pMoveLesson[i].Teachers[j];
	    movelesson_data_ver3.Times = g_pMoveLesson[i].Times;
        for( j = 0; j < movelesson_data_ver3.Times; j++ ){
	      movelesson_data_ver3.pos[j].week = g_pMoveLesson[i].pos[j].week;
	      movelesson_data_ver3.pos[j].lesson = g_pMoveLesson[i].pos[j].lesson;
        }

        fwrite( &movelesson_data_ver3, sizeof(TSCD_MoveLessonData_ver3), 1, fp );
      }
	}

    // �ð�ǥ ������ ����
    if( g_iTeacherCount > 0 ){
	  for( t = 0; t < g_iTeacherCount; t++ ) {
        memset( &schedule_data_ver3, 0, sizeof(TSCD_ScheduleData_ver3) );
		for( w = 0; w < 6; w++ ){
		  for( n = 0; n < 8; n++ ){
//            PackClassNo( t, w+atWEEK_BASE, n+atLESSON_BASE );
			schedule_data_ver3[w][n].ClassType = GetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE );
		    schedule_data_ver3[w][n].Classes.FullValue = GetClassesFull( t, w+atWEEK_BASE, n+atLESSON_BASE );
			schedule_data_ver3[w][n].ClassInfo = GetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE );
		  }
		}

        fwrite( &schedule_data_ver3, sizeof(TSCD_ScheduleData_ver3), 1, fp );
      }
    }

    return TRUE;
}
