//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SSC_File_ver3.h"
#include "STC_File_ver3_old.h"
#include "SCD_File_ver3_old.h"
//----------------------------------------------------------------------------


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

/***********************************
  .SCD 파일을 로드한다. (Ver 3)
************************************/
bool LoadScheduleData_ver3_old( FILE *fp )
{
    int t, w, n, i, j;
	int cnt;
    TSCD_ScheduleInfo_ver3 schedule_info_ver3;
//    TSCD_MoveLessonData_ver3 movelesson_data_ver3;
    TMoveLessonData_xxx movelesson_data_ver3;
    TSCD_ScheduleData_ver3 schedule_data_ver3;
    int tc;
    TSubject *sbj;
    char tmpStr[50];

    // 시간표 정보 읽기
    fread( &schedule_info_ver3, sizeof(TSCD_ScheduleInfo_ver3), 1, fp );
    memset( &g_ScheduleInfo, 0, sizeof(TScheduleInfo) );
	strcpy( g_ScheduleInfo.ScheduleTitle, schedule_info_ver3.ScheduleTitle );
	strcpy( g_ScheduleInfo.AuthorName, schedule_info_ver3.AuthorName );
	strcpy( g_ScheduleInfo.AuthorDate, schedule_info_ver3.AuthorDate );
	strcpy( g_ScheduleInfo.Memo, schedule_info_ver3.Memo );

    // 학교 정보를 읽는다.
    LoadSchoolData_ver3( fp );

    // 교사 정보를 읽는다.
    LoadTeacherData_ver3_old( fp );

    // 이동수업 정보 읽기
    fread( &tc, sizeof(long), 1, fp );
    InitMoveLessonData( tc );
	if( g_iMoveLessonCount > 0 ){
      for( i = 0; i < g_iMoveLessonCount; i++ ){
        memset( &g_pMoveLesson[i], 0, sizeof(TMoveLessonData) );
//        fread( &movelesson_data_ver3, sizeof(TSCD_MoveLessonData_ver3), 1, fp );
        fread( &movelesson_data_ver3, sizeof(TMoveLessonData_xxx), 1, fp );

        strncpy( g_pMoveLesson[i].LessonName, movelesson_data_ver3.LessonName, MOVELESSON_NAME_SIZE );
        g_pMoveLesson[i].LessonName[MOVELESSON_NAME_SIZE] = '\0';

        strncpy( tmpStr, movelesson_data_ver3.SubjectName, 4 );
        tmpStr[4] = '\0';
        sbj = FindSubjectByName(tmpStr);
        if( sbj )
          g_pMoveLesson[i].SubjectCode = sbj->SubjectCode;
        else
          g_pMoveLesson[i].SubjectCode = 0;

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

    // 시간표 데이터 읽기
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

