//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SSB_File_ver3.h"
//----------------------------------------------------------------------------

/***********************************
  .SSB 파일을 로드한다. (Ver 3)
************************************/
bool LoadSubjectData_ver3( FILE *fp )
{
    int i;
    TSubject *sbj;
    TSCD_Subject_ver3 subject_data_ver3;
    int tc;

    // 과목 수 읽기
    fread( &tc, sizeof(long), 1, fp );

    // 과목수만큼 메모리 할당
	InitSubjectData( tc );

    // 과목 읽기
    for( i = 0; i < g_iSubjectCount; i++ ) {
      fread( &subject_data_ver3, sizeof(TSCD_Subject_ver3), 1, fp );

      sbj = GetSubject( i );
      memset( sbj, 0, sizeof(TSubject) );

      sbj->SubjectCode = subject_data_ver3.SubjectCode;
	  sbj->TargetYear = subject_data_ver3.TargetYear;

      strncpy( sbj->FullName, subject_data_ver3.FullName, SUBJECT_NAME_SIZE );
      sbj->FullName[SUBJECT_NAME_SIZE] = '\0';
      
      strncpy( sbj->ShortName, subject_data_ver3.ShortName, SUBJECT_SHORTNAME_SIZE );
      sbj->ShortName[SUBJECT_SHORTNAME_SIZE] = '\0';
    }
	
    return true;
}


/***********************************
  .SSB 파일로 쓴다. (Ver 3)
************************************/
bool SaveSubjectData_ver3( FILE *fp )
{
    int i;
    TSubject *sbj;
    TSCD_Subject_ver3 subject_data_ver3;

    // 과목 수 쓰기
    fwrite( &g_iSubjectCount, sizeof(long), 1, fp );

    if( g_iSubjectCount > 0 ){
      // 과목 쓰기
      for( i = 0; i < g_iSubjectCount; i++ ) {
        memset( &subject_data_ver3, 0, sizeof(TSCD_Subject_ver3) );

        sbj = GetSubject( i );

        subject_data_ver3.SubjectCode = sbj->SubjectCode;
	    subject_data_ver3.TargetYear = sbj->TargetYear;

        strncpy( subject_data_ver3.FullName, sbj->FullName, SCD_SUBJECT_NAME_SIZE_VER3 );

        strncpy( subject_data_ver3.ShortName, sbj->ShortName, SCD_SUBJECT_SHORTNAME_SIZE_VER3 );

        fwrite( &subject_data_ver3, sizeof(TSCD_Subject_ver3), 1, fp );
	  }
    }

    return TRUE;
}
