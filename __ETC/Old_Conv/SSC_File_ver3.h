#ifndef __SCC_FILE_VER3_H_
#define __SCC_FILE_VER3_H_

#include <windows.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SCD_SCHOOL_NAME_SIZE_VER3 			32

#define SCD_SPCIEL_SUBJECT_NAME_SIZE_VER3   8
//#define SCD_SUBJECT_NAME_SIZE_VER3    		  8

#define SCD_YEAR_COUNT_VER3       3
#define SCD_WEEK_COUNT_VER3       6
//#define SCD_MAX_LESSON_VER3         8

#define SCD_MAX_SPC_COUNT_VER3 10


#pragma pack(push, 1)
typedef struct __TSCD_ClassPos_ver3 {
	WORD week;
	WORD lesson;
} TSCD_ClassPos_ver3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SpcClass_ver3 {
	char Name[SCD_SPCIEL_SUBJECT_NAME_SIZE_VER3];
	WORD Years;
	TSCD_ClassPos_ver3 Pos[SCD_YEAR_COUNT_VER3];
} TSCD_SpcClass_ver3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SchoolData_ver3 {
	char 			SchoolName[SCD_SCHOOL_NAME_SIZE_VER3];
	long            ClassCount[SCD_YEAR_COUNT_VER3];
	long            WeekLimit[SCD_YEAR_COUNT_VER3][SCD_WEEK_COUNT_VER3];
	long            SPC_Count;
	TSCD_SpcClass_ver3   SPC[SCD_MAX_SPC_COUNT_VER3];
	long            LunchTime[SCD_YEAR_COUNT_VER3];
} TSCD_SchoolData_ver3;
#pragma pack(pop)

bool LoadSchoolData_ver3( FILE *fp );
bool SaveSchoolData_ver3( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
