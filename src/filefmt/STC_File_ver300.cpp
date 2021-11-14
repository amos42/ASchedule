//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "STC_File_ver300.h"
//----------------------------------------------------------------------------


/***********************************
  .STC ������ �ε��Ѵ�. (Ver 3)
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

    // ���� �� �б�
    fread( &tc, sizeof(long), 1, fp );

    // �������ŭ �޸� �Ҵ�
	InitTeacherData( tc );

    // ���� �б�
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

    // �ð�ǥ ������ �Ҵ� (�������ŭ)
	InitScheduleData();
	
    return true;
}


/***********************************
  .STC ���Ϸ� ����. (Ver 3)
************************************/
bool SaveTeacherData_ver300( FILE *fp )
{
    int t, i;
    int cnt;
    TTeacherSubject *tsbj;
    TSCD_TeacherData_ver300 teacher_data_ver300;
    PTeacherData tt;

    // ���� �� ����
    fwrite( &g_iTeacherCount, sizeof(long), 1, fp );

    if( g_iTeacherCount > 0 ){
      // ���� ����
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
