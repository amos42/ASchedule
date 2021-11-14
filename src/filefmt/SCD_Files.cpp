//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SCD_Files.h"
#include "SSC_File_ver300.h"
#include "SSB_File_ver300.h"
#include "STC_File_ver300.h"
#include "SCD_File_ver100.h"
#include "SCD_File_ver200.h"
#include "SCD_File_ver300.h"
#include "SCD_File_ver310.h"
#include <stdio.h>
//----------------------------------------------------------------------------

/***********************************
  .SCD 파일을 로드한다. (Ver 1, 2, 3)
************************************/
bool LoadScheduleData( char *filename )
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

    if( hdr.Version == 1 )
      r = LoadScheduleData_ver100( fp );
    else if( hdr.Version == 2 )
      r = LoadScheduleData_ver200( fp );
    else if( hdr.Version == 3 ){
	  if( (strcmp(hdr.SubHeaderStr, "Schedule") == 0) && (hdr.SubVersion == 1) )
        r = LoadScheduleData_ver300( fp );
	  else
	  	r = false;
    } else if( hdr.Version == 0x310 ){
	  if( (strcmp(hdr.SubHeaderStr, "Schedule") == 0) && (hdr.SubVersion == 0x100) )
        r = LoadScheduleData_ver310( fp );
	  else
	  	r = false;
    } else
      r = false;

    SetCurSchedules( p );

	fclose( fp );

    return r;
}


/***********************************
  .SCD 파일로 쓴다. (Ver 3)
************************************/
bool SaveScheduleData( char *filename )
{
    TSCD_ScheduleFileHeader hdr;
    FILE *fp;
	int p;
    bool r;
	
    fp = fopen( filename, "wb" );
    if( fp == NULL ) return false;
	
    // 헤더 쓰기
    memset(&hdr, 0, sizeof(TSCD_ScheduleFileHeader) );
    strcpy(hdr.HeaderStr, "Amos Schedule Data;");
	hdr.Version = 0x310;
    strcpy(hdr.SubHeaderStr, "Schedule");
	hdr.SubVersion = 0x100;
	fwrite( &hdr, sizeof(TSCD_ScheduleFileHeader), 1, fp );

    p = SetCurSchedules(0);
	
    if( hdr.Version == 0x310 )
      r = SaveScheduleData_ver310( fp );
    else
      r = false;

    SetCurSchedules( p );

	fclose( fp );
	
	return r;
}


/***********************************
  .SSC 파일을 로드한다. (Ver 3)
************************************/
bool LoadSchoolData( char *filename )
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
    if( strcmp(hdr.SubHeaderStr, "School") != 0 ){
      fclose( fp );
      return false;
    }

    if( hdr.Version == 3 && hdr.SubVersion == 1 )
      r = LoadSchoolData_ver300( fp );
    else
      r = false;

	fclose( fp );

    return r;
}


/***********************************
  .SSC 파일로 쓴다. (Ver 3)
************************************/
bool SaveSchoolData( char *filename )
{
    TSCD_ScheduleFileHeader hdr;
    FILE *fp;
	int p;
    bool r;
	
    fp = fopen( filename, "wb" );
    if( fp == NULL ) return false;

    // 헤더 읽기
    memset( &hdr, 0, sizeof(TSCD_ScheduleFileHeader) );
    strcpy(hdr.HeaderStr, "Amos Schedule Data;");
	hdr.Version = 3;
    strcpy(hdr.SubHeaderStr, "School");
	hdr.SubVersion = 1;
	fwrite( &hdr, sizeof(TSCD_ScheduleFileHeader), 1, fp );

    if( hdr.Version == 3 )
      r = SaveSchoolData_ver300( fp );
    else
      r = false;

	fclose( fp );
	
	return r;
}


/***********************************
  .SSB 파일을 로드한다. (Ver 3)
************************************/
bool LoadSubjectData( char *filename )
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
    if( strcmp(hdr.SubHeaderStr, "Subject") != 0 ){
      fclose( fp );
      return false;
    }

    if( hdr.Version == 3 && hdr.SubVersion == 1 )
      r = LoadSubjectData_ver300( fp );
    else
      r = false;

	fclose( fp );

    return r;
}


/***********************************
  .SSB 파일로 쓴다. (Ver 3)
************************************/
bool SaveSubjectData( char *filename )
{
    TSCD_ScheduleFileHeader hdr;
    FILE *fp;
	int p;
    bool r;
	
    fp = fopen( filename, "wb" );
    if( fp == NULL ) return false;

    // 헤더 읽기
    memset( &hdr, 0, sizeof(TSCD_ScheduleFileHeader) );
    strcpy(hdr.HeaderStr, "Amos Schedule Data;");
	hdr.Version = 3;
    strcpy(hdr.SubHeaderStr, "Subject");
	hdr.SubVersion = 1;
	fwrite( &hdr, sizeof(TSCD_ScheduleFileHeader), 1, fp );

    if( hdr.Version == 3 )
      r = SaveSubjectData_ver300( fp );
    else
      r = false;

	fclose( fp );
	
	return r;
}


/***********************************
  .STC 파일을 로드한다. (Ver 3)
************************************/
bool LoadTeacherData( char *filename )
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
      r = LoadTeacherData_ver300( fp );
    else
      r = false;

	fclose( fp );

    return r;
}


/***********************************
  .STC 파일로 쓴다. (Ver 3)
************************************/
bool SaveTeacherData( char *filename )
{
    TSCD_ScheduleFileHeader hdr;
    FILE *fp;
	int p;
    bool r;
	
    fp = fopen( filename, "wb" );
    if( fp == NULL ) return false;

    // 헤더 쓰기
    memset( &hdr, 0, sizeof(TSCD_ScheduleFileHeader) );
    strcpy(hdr.HeaderStr, "Amos Schedule Data;");
	hdr.Version = 3;
    strcpy(hdr.SubHeaderStr, "Teacher");
	hdr.SubVersion = 1;
	fwrite( &hdr, sizeof(TSCD_ScheduleFileHeader), 1, fp );

    if( hdr.Version == 3 )
      r = SaveTeacherData_ver300( fp );
    else
      r = false;

	fclose( fp );
	
	return r;
}


