//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "STC_File_ver3_old.h"
//----------------------------------------------------------------------------

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


static int MyAddSubject( char *tempStr1, char *tempStr2 )
{
    TSubject *sbj;
	int id;

    if(  g_iSubjectCount > 0 ){ 
  	  sbj = GetSubject(g_iSubjectCount-1);
	  id = sbj->SubjectCode + 1;
      ReallocSubjectData(g_iSubjectCount+1);
    } else {
	  id = 1;
	  InitSubjectData(1);
    }
	
	sbj = GetSubject(g_iSubjectCount-1);
    sbj->SubjectCode = id;
	sbj->TargetYear = 0;
	strcpy( sbj->FullName, tempStr1 );
	strcpy( sbj->ShortName, tempStr2 );

	return id;
}


/***********************************
  .STC 파일을 로드한다. (Ver 3)
************************************/
bool LoadTeacherData_ver3_old( FILE *fp )
{
    int t, i;
	int cnt;
    PScheduleData ts;
    PTeacherData tt;
    TTeacherSubject *tsbj;
    TSubject *sbj;
//    TSCD_TeacherData_ver3 teacher_data_ver3;
    TSCD_TeacherData_xxx teacher_data_ver3;
    int tc;
    char tmpStr1[50], tmpStr2[50];

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
        strncpy( tmpStr1, teacher_data_ver3.Subject[i].Name, 8 );
        tmpStr1[8] = '\0';

        if( tmpStr1[0] == '\0' ) continue;

        tsbj = GetTeacherSubject( t, i );
        tsbj->Attr = teacher_data_ver3.Subject[i].Attr;

        strncpy( tmpStr2, teacher_data_ver3.Subject[i].SubName, 4 );
        tmpStr2[4] = '\0';

        sbj = FindSubjectByName( tmpStr1 );
        if( sbj ){
          tsbj->SubjectCode = sbj->SubjectCode;
        } else {
          tsbj->SubjectCode = MyAddSubject( tmpStr1, tmpStr2 );
        }

        tsbj->Times = teacher_data_ver3.Subject[i].Times;
        tsbj->Classes.FullValue = teacher_data_ver3.Subject[i].Classes.FullValue;
        tsbj->TargetWeeks = teacher_data_ver3.Subject[i].TargetWeeks;
        tsbj->TargetLessons = teacher_data_ver3.Subject[i].TargetLessons;
      }
	  tt->ChargeClass = teacher_data_ver3.ChargeClass;
	  tt->Etc = teacher_data_ver3.Etc;
	  for( i = 0; i < 4; i++ ) 	tt->StressFactor[i] = teacher_data_ver3.StressFactor[i];
    }

    InitScheduleData();

    return true;
}

