#ifndef __SCD_FILES_OLD_H_
#define __SCD_FILES_OLD_H_

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

bool LoadTeacherData_old( char *filename );
bool SaveTeacherData_old( char *filename );

bool LoadScheduleData_old( char *filename );
bool SaveScheduleData_old( char *filename );


#ifdef __cplusplus
};
#endif


#endif
