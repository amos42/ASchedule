#ifndef __SCD_FILE_VER200_H_
#define __SCD_FILE_VER200_H_

#include <windows.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


#define SCD_WEEK_COUNT_ver200       6
#define SCD_MAX_TIME_ver200         8

#define MAX_TEACHER_SUBJECT_ver200  4
#define MAX_SPC_COUNT_ver200        10


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
typedef struct __TSCD_ClassPos_ver200
{
	WORD week;
	WORD lesson;
} TSCD_ClassPos_ver200;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SpcClass_ver200
{
	char Name[4];
	WORD Years;
	TSCD_ClassPos_ver200 Pos[3];
} TSCD_SpcClass_ver200;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SchoolData_ver200
{
	WORD            ClassCount[3];
	BYTE            WeekLimit[3][6];
	WORD            SPC_Count;
	TSCD_SpcClass_ver200   SPC[10];
	WORD            LunchTime;
} TSCD_SchoolData_ver200;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_TeacherSubject_ver200
{
	char Name[4];
	WORD StartClass;
	WORD EndClass;
	WORD Times;
} TSCD_TeacherSubject_ver200;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_TeacherData_ver200
{
	WORD TeacherNo;
	char TeacherName[8];
	TSCD_TeacherSubject_ver200 Subject[3][4];
} TSCD_TeacherData_ver200;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_ScheduleDataCell_ver200
{
	WORD ClassNo;
	WORD ClassNo2;
	Byte ClassType;
	WORD ClassInfo;
} TSCD_ScheduleDataCell_ver200;
#pragma pack(pop)

typedef TSCD_ScheduleDataCell_ver200 TSCD_ScheduleData_ver200[SCD_WEEK_COUNT_ver200][SCD_MAX_TIME_ver200];


bool LoadScheduleData_ver200( FILE *fp );
bool SaveScheduleData_ver200( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
