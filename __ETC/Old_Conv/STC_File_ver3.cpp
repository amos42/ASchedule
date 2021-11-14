//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "STC_File_ver3.h"
//----------------------------------------------------------------------------

/*
#pragma pack(push, 1)
typedef struct __TSCD_TeacherSubject_xxx {
	unsigned long Attr;
	char Name[8];
	char SubName[4];
	TClasses_ver3 Classes;
	long Times;
	unsigned short TargetWeeks;
	unsigned short TargetLessons;
} TSCD_TeacherSubject_xxx;

typedef struct __TSCD_TeacherData_xxx {
	long TeacherNo;
	char TeacherName[SCD_TEACHER_NAME_SIZE_VER3];
	long SubjectCount;
	TSCD_TeacherSubject_xxx Subject[SCD_TEACHER_SUBJECT_COUNT_VER3];
	WORD ChargeClass;
	WORD Etc;
	BYTE StressFactor[4];  // 1. 5교시이상, 2. 3교시연속, 3. 점심전후, 4.기타 => 총합이 100 이하가 되도록...
} TSCD_TeacherData_xxx;
#pragma pack(pop)
*/

/***********************************
  .STC 파일을 로드한다. (Ver 3)
************************************/
/*
bool LoadTeacherData_ver3( FILE *fp )
{
    int t, i;
	int cnt;
    PScheduleData ts;
    PTeacherData tt;
    TTeacherSubject *sbj;
//    TSCD_TeacherData_ver3 teacher_data_ver3;
    TSCD_TeacherData_xxx teacher_data_ver3;
    int tc;

    // 교사 수 읽기
    fread( &tc, sizeof(long), 1, fp );

    // 교사수만큼 메모리 할당
	InitTeacherData( tc );

    // 교사 읽기
    for( t = 0; t < g_iTeacherCount; t++ ) {
//      fread( &teacher_data_ver3, sizeof(TSCD_TeacherData_ver3), 1, fp );
      fread( &teacher_data_ver3, sizeof(TSCD_TeacherData_xxx), 1, fp );

      tt = GetTeacherData( t );
      tt->TeacherNo = teacher_data_ver3.TeacherNo;
      strncpy( tt->TeacherName, teacher_data_ver3.TeacherName, 12 );
      tt->TeacherName[12] = '\0';
	  tt->SubjectCount = teacher_data_ver3.SubjectCount;
      ClearTeacherSubject( t );
	  cnt = MIN( MAX_TEACHER_SUBJECT, SCD_TEACHER_SUBJECT_COUNT_VER3 );
      for( i = 0; i < cnt; i++ ) {
        sbj = GetTeacherSubject( t, i );
        sbj->Attr = teacher_data_ver3.Subject[i].Attr;
        strncpy( sbj->Name, teacher_data_ver3.Subject[i].Name, 20 );
        sbj->Name[20] = '\0';
        strncpy( sbj->SubName, teacher_data_ver3.Subject[i].SubName, 8 );
        sbj->SubName[8] = '\0';
        sbj->Times = teacher_data_ver3.Subject[i].Times;
        sbj->Classes.FullValue = teacher_data_ver3.Subject[i].Classes.FullValue;
        sbj->TargetWeeks = teacher_data_ver3.Subject[i].TargetWeeks;
        sbj->TargetLessons = teacher_data_ver3.Subject[i].TargetLessons;
      }
	  tt->ChargeClass = teacher_data_ver3.ChargeClass;
	  tt->Etc = teacher_data_ver3.Etc;
	  for( i = 0; i < 4; i++ ) 	tt->StressFactor[i] = teacher_data_ver3.StressFactor[i];
    }

    // 시간표 데이터 할당 (교사수만큼)
	InitScheduleData();

    return true;
}
*/
bool LoadTeacherData_ver3( FILE *fp )
{
    int t, i;
	int cnt;
    PScheduleData ts;
    PTeacherData tt;
    TTeacherSubject *tsbj;
    TSCD_TeacherData_ver3 teacher_data_ver3;
    int tc;

    // 교사 수 읽기
    fread( &tc, sizeof(long), 1, fp );

    // 교사수만큼 메모리 할당
	InitTeacherData( tc );

    // 교사 읽기
    for( t = 0; t < g_iTeacherCount; t++ ) {
      fread( &teacher_data_ver3, sizeof(TSCD_TeacherData_ver3), 1, fp );

      tt = GetTeacherData( t );
      tt->TeacherNo = teacher_data_ver3.TeacherNo;
      strncpy( tt->TeacherName, teacher_data_ver3.TeacherName, SCD_TEACHER_NAME_SIZE_VER3 );
      tt->TeacherName[SCD_TEACHER_NAME_SIZE_VER3] = '\0';
	  tt->SubjectCount = teacher_data_ver3.SubjectCount;
      ClearTeacherSubject( t );
	  cnt = MIN( MAX_TEACHER_SUBJECT, SCD_TEACHER_SUBJECT_COUNT_VER3 );
      for( i = 0; i < cnt; i++ ) {
        tsbj = GetTeacherSubject( t, i );
        tsbj->Attr = teacher_data_ver3.Subject[i].Attr;
        tsbj->SubjectCode = teacher_data_ver3.Subject[i].SubjectCode;
        tsbj->Times = teacher_data_ver3.Subject[i].Times;
        tsbj->Classes.FullValue = teacher_data_ver3.Subject[i].Classes.FullValue;
        tsbj->TargetWeeks = teacher_data_ver3.Subject[i].TargetWeeks;
        tsbj->TargetLessons = teacher_data_ver3.Subject[i].TargetLessons;
      }
	  tt->ChargeClass = teacher_data_ver3.ChargeClass;
	  tt->Etc = teacher_data_ver3.Etc;
	  for( i = 0; i < 4; i++ ) 	tt->StressFactor[i] = teacher_data_ver3.StressFactor[i];
    }

    // 시간표 데이터 할당 (교사수만큼)
	InitScheduleData();
	
    return true;
}


/***********************************
  .STC 파일로 쓴다. (Ver 3)
************************************/
bool SaveTeacherData_ver3( FILE *fp )
{
    int t, i;
    int cnt;
    TTeacherSubject *tsbj;
    TSCD_TeacherData_ver3 teacher_data_ver3;
    PTeacherData tt;

    // 교사 수 쓰기
    fwrite( &g_iTeacherCount, sizeof(long), 1, fp );

    if( g_iTeacherCount > 0 ){
      // 교사 쓰기
	  for( t = 0; t < g_iTeacherCount; t++ ) {
        memset( &teacher_data_ver3, 0, sizeof(TSCD_TeacherData_ver3) );

		tt = GetTeacherData( t );
		teacher_data_ver3.TeacherNo = tt->TeacherNo;
		strncpy( teacher_data_ver3.TeacherName, tt->TeacherName, SCD_TEACHER_NAME_SIZE_VER3 );
		teacher_data_ver3.SubjectCount = tt->SubjectCount;
	    cnt = MIN( MAX_TEACHER_SUBJECT, SCD_TEACHER_SUBJECT_COUNT_VER3 );
        for( i = 0; i < cnt; i++ ) {
		  tsbj = GetTeacherSubject( t, i );
		  teacher_data_ver3.Subject[i].Attr = tsbj->Attr;
		  teacher_data_ver3.Subject[i].SubjectCode = tsbj->SubjectCode;
		  teacher_data_ver3.Subject[i].Times = tsbj->Times;
		  teacher_data_ver3.Subject[i].Classes.FullValue = tsbj->Classes.FullValue;
		  teacher_data_ver3.Subject[i].TargetWeeks = tsbj->TargetWeeks;
		  teacher_data_ver3.Subject[i].TargetLessons = tsbj->TargetLessons;
		}
		teacher_data_ver3.ChargeClass = tt->ChargeClass;
		teacher_data_ver3.Etc = tt->Etc;
		for( i = 0; i < 4; i++ )  teacher_data_ver3.StressFactor[i] = tt->StressFactor[i];

        fwrite( &teacher_data_ver3, sizeof(TSCD_TeacherData_ver3), 1, fp );
	  }
    }

    return TRUE;
}
