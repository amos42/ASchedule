#ifndef __SCC_FILE_ver300_H_
#define __SCC_FILE_ver300_H_

#include <windows.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SCD_SCHOOL_NAME_SIZE_ver300 			32

#define SCD_SPCIEL_SUBJECT_NAME_SIZE_ver300   8
//#define SCD_SUBJECT_NAME_SIZE_ver300    		  8

#define SCD_YEAR_COUNT_ver300       3
#define SCD_WEEK_COUNT_ver300       6
//#define SCD_MAX_LESSON_ver300         8

#define SCD_MAX_SPC_COUNT_ver300 10


#pragma pack(push, 1)
typedef struct __TSCD_ClassPos_ver300 {
	WORD week;
	WORD lesson;
} TSCD_ClassPos_ver300;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SpcClass_ver300 {
	char Name[SCD_SPCIEL_SUBJECT_NAME_SIZE_ver300];
	WORD Years;
	TSCD_ClassPos_ver300 Pos[SCD_YEAR_COUNT_ver300];
} TSCD_SpcClass_ver300;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_SchoolData_ver300 {
	char 			SchoolName[SCD_SCHOOL_NAME_SIZE_ver300];
	long            ClassCount[SCD_YEAR_COUNT_ver300];
	long            WeekLimit[SCD_YEAR_COUNT_ver300][SCD_WEEK_COUNT_ver300];
	long            SPC_Count;
	TSCD_SpcClass_ver300   SPC[SCD_MAX_SPC_COUNT_ver300];
	long            LunchTime[SCD_YEAR_COUNT_ver300];
} TSCD_SchoolData_ver300;
#pragma pack(pop)

bool LoadSchoolData_ver300( FILE *fp );
bool SaveSchoolData_ver300( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
