#ifndef __SCD_FILE_VER100_H_
#define __SCD_FILE_VER100_H_

#include <windows.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


#define SCD_WEEK_COUNT_ver100       6
#define SCD_MAX_TIME_ver100         8

#define MAX_TEACHER_SUBJECT_ver100  4
#define MAX_SPC_COUNT_ver100        10


#ifndef __TSCD_COMMON_HEADER
#define __TSCD_COMMON_HEADER
#pragma pack(push, 1)
typedef struct __TSCD_ScheduleFileHeader
{
	char HeaderStr[20];
	long Version;
	BYTE Reserved[40];
} TSCD_ScheduleFileHeader;
#pragma pack(pop)
#endif


#pragma pack(push, 1)
typedef struct __TSCD_ClassPos_ver100
{
	WORD week;
	WORD lesson;
} TSCD_ClassPos_ver100;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SpcClass_ver100
{
	char Name[4];
	WORD Years;
	TSCD_ClassPos_ver100 Pos[3];
} TSCD_SpcClass_ver100;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SchoolData_ver100
{
	WORD            ClassCount[3];
	BYTE            WeekLimit[3][6];
	long            SPC_Count;
	char            SPC_Name[10][4];
	TSCD_ClassPos_ver100   SPC[10][3];
	WORD            LunchTime;
} TSCD_SchoolData_ver100;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_TeacherData_ver100
{
	WORD TeacherNo;
	char TeacherName[8];
	char Subject[3][3][4];
	WORD StartClass[3][3];
	WORD EndClass[3][3];
	WORD Times[3][3];
} TSCD_TeacherData_ver100;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_ScheduleDataCell_ver100
{
	WORD ClassNo;
	WORD ClassNo2;
	Byte ClassType;
	WORD ClassInfo;
} TSCD_ScheduleDataCell_ver100;
#pragma pack(pop)

typedef TSCD_ScheduleDataCell_ver100 TSCD_ScheduleData_ver100[SCD_WEEK_COUNT_ver100][SCD_MAX_TIME_ver100];


bool LoadScheduleData_ver100( FILE *fp );
bool SaveScheduleData_ver100( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
