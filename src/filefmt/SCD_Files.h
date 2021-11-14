#ifndef __SCD_FILES_H_
#define __SCD_FILES_H_

#include <windows.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


#ifndef __TSCD_COMMON_HEADER
#define __TSCD_COMMON_HEADER
#pragma pack(push, 1)
typedef struct __TSCD_ScheduleFileHeader
{
	char HeaderStr[20];
	long Version;
	char SubHeaderStr[12];
	long SubVersion;
	
	char Reserved[64 - (20+4+12+4)];
} TSCD_ScheduleFileHeader;
#pragma pack(pop)
#endif

bool LoadSchoolData( char *filename );
bool SaveSchoolData( char *filename );

bool LoadSubjectData( char *filename );
bool SaveSubjectData( char *filename );

bool LoadTeacherData( char *filename );
bool SaveTeacherData( char *filename );

bool LoadScheduleData( char *filename );
bool SaveScheduleData( char *filename );


#ifdef __cplusplus
};
#endif


#endif
