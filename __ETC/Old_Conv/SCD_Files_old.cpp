//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SCD_Files_old.h"
#include "STC_File_ver3_old.h"
#include "SCD_File_ver3_old.h"
#include <stdio.h>
//----------------------------------------------------------------------------

/***********************************
  .SCD 파일을 로드한다. (Ver 1, 2, 3)
************************************/
bool LoadScheduleData_old( char *filename )
{
    TSCD_ScheduleFileHeader hdr;
    FILE *fp;
	int p;
    bool r;

    fp = fopen( filename, "rb" );
    if( fp == NULL ) return false;
    // 헤더 읽기
    fread( &hdr, sizeof(TSCD_ScheduleFileHeader), 1, fp );
    if( strcmp(hdr.HeaderStr, "Amos Schedule Data;") != 0 ){
      fclose( fp );
      return false;
    }

    p = SetCurSchedules(0);

    if( hdr.Version == 3 ){
	  if( (strcmp(hdr.SubHeaderStr, "Schedule") == 0) && (hdr.SubVersion == 1) )
        r = LoadScheduleData_ver3_old( fp );
	  else
	  	r = false;
    } else
      r = false;

    SetCurSchedules( p );

	fclose( fp );

    return r;
}

/***********************************
  .STC 파일을 로드한다. (Ver 3)
************************************/
bool LoadTeacherData_old( char *filename )
{
    TSCD_ScheduleFileHeader hdr;
    FILE *fp;
    bool r;

    fp = fopen( filename, "rb" );
    if( fp == NULL ) return false;
	
    // 헤더 읽기
    fread( &hdr, sizeof(TSCD_ScheduleFileHeader), 1, fp );
    if( strcmp(hdr.HeaderStr, "Amos Schedule Data;") != 0 ){
      fclose( fp );
      return false;
    }
    if( strcmp(hdr.SubHeaderStr, "Teacher") != 0 ){
      fclose( fp );
      return false;
    }

    if( hdr.Version == 3 && hdr.SubVersion == 1 )
      r = LoadTeacherData_ver3_old( fp );
    else
      r = false;

	fclose( fp );

    return r;
}
