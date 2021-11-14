//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "STC_File_ver300.h"
//----------------------------------------------------------------------------


/***********************************
  .STC 파일을 로드한다. (Ver 3)
************************************/
bool LoadTeacherData_ver300( FILE *fp )
{
    int t, i;
	int cnt;
    PScheduleData ts;
    PTeacherData tt;
    TTeacherSubject *tsbj;
    TSCD_TeacherData_ver300 teacher_data_ver300;
    int tc;

    // 교사 수 읽기
    fread( &tc, sizeof(long), 1, fp );

    // 교사수만큼 메모리 할당
	InitTeacherData( tc );

    // 교사 읽기
    for( t = 0; t < g_iTeacherCount; t++ ) {
      fread( &teacher_data_ver300, sizeof(TSCD_TeacherData_ver300), 1, fp );

      tt = GetTeacherData( t );
      tt->TeacherNo = teacher_data_ver300.TeacherNo;
      strncpy( tt->TeacherName, teacher_data_ver300.TeacherName, SCD_TEACHER_NAME_SIZE_ver300 );
      tt->TeacherName[SCD_TEACHER_NAME_SIZE_ver300] = '\0';
	  tt->SubjectCount = teacher_data_ver300.SubjectCount;
      ClearTeacherSubject( t );
	  cnt = MIN( MAX_TEACHER_SUBJECT, SCD_TEACHER_SUBJECT_COUNT_ver300 );
      for( i = 0; i < cnt; i++ ) {
        tsbj = GetTeacherSubject( t, i );
        tsbj->Attr = teacher_data_ver300.Subject[i].Attr;
        tsbj->SubjectCode = teacher_data_ver300.Subject[i].SubjectCode;
        tsbj->Times = teacher_data_ver300.Subject[i].Times;
        tsbj->Classes.FullValue = teacher_data_ver300.Subject[i].Classes.FullValue;
        tsbj->LimitWeeks = teacher_data_ver300.Subject[i].LimitWeeks;
        tsbj->LimitLessons = teacher_data_ver300.Subject[i].LimitLessons;
      }
	  tt->ChargeClass = teacher_data_ver300.ChargeClass;
	  tt->Etc = teacher_data_ver300.Etc;
	  for( i = 0; i < 4; i++ ) 	tt->StressFactor[i] = teacher_data_ver300.StressFactor[i];
    }

    // 시간표 데이터 할당 (교사수만큼)
	InitScheduleData();
	
    return true;
}


/***********************************
  .STC 파일로 쓴다. (Ver 3)
************************************/
bool SaveTeacherData_ver300( FILE *fp )
{
    int t, i;
    int cnt;
    TTeacherSubject *tsbj;
    TSCD_TeacherData_ver300 teacher_data_ver300;
    PTeacherData tt;

    // 교사 수 쓰기
    fwrite( &g_iTeacherCount, sizeof(long), 1, fp );

    if( g_iTeacherCount > 0 ){
      // 교사 쓰기
	  for( t = 0; t < g_iTeacherCount; t++ ) {
        memset( &teacher_data_ver300, 0, sizeof(TSCD_TeacherData_ver300) );

		tt = GetTeacherData( t );
		teacher_data_ver300.TeacherNo = tt->TeacherNo;
		strncpy( teacher_data_ver300.TeacherName, tt->TeacherName, SCD_TEACHER_NAME_SIZE_ver300 );
		teacher_data_ver300.SubjectCount = tt->SubjectCount;
	    cnt = MIN( MAX_TEACHER_SUBJECT, SCD_TEACHER_SUBJECT_COUNT_ver300 );
        for( i = 0; i < cnt; i++ ) {
		  tsbj = GetTeacherSubject( t, i );
		  teacher_data_ver300.Subject[i].Attr = tsbj->Attr;
		  teacher_data_ver300.Subject[i].SubjectCode = tsbj->SubjectCode;
		  teacher_data_ver300.Subject[i].Times = tsbj->Times;
		  teacher_data_ver300.Subject[i].Classes.FullValue = tsbj->Classes.FullValue;
		  teacher_data_ver300.Subject[i].LimitWeeks = tsbj->LimitWeeks;
		  teacher_data_ver300.Subject[i].LimitLessons = tsbj->LimitLessons;
		}
		teacher_data_ver300.ChargeClass = tt->ChargeClass;
		teacher_data_ver300.Etc = tt->Etc;
		for( i = 0; i < 4; i++ )  teacher_data_ver300.StressFactor[i] = tt->StressFactor[i];

        fwrite( &teacher_data_ver300, sizeof(TSCD_TeacherData_ver300), 1, fp );
	  }
    }

    return TRUE;
}
