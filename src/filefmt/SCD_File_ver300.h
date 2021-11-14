#ifndef __SCD_FILE_VER300_H_
#define __SCD_FILE_VER300_H_

#include <windows.h>
#include <stdio.h>


#include "SSC_File_ver300.h"
#include "SSB_File_ver300.h"
#include "STC_File_ver300.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SCD_WEEK_COUNT_ver300       6
#define SCD_MAX_LESSON_ver300         8
#define SCD_MOVELESSON_NAME_SIZE_ver300    20

#define SCD_MAX_MOVELESSON_TEACHERS_ver300 10
#define SCD_MAX_MOVELESSON_TIMES_ver300    (6*8)


#pragma pack(push, 1)
typedef struct __TSCD_ScheduleInfo_ver300 {
	char ScheduleTitle[32];
	char AuthorName[20];
	char AuthorDate[20];
	char Memo[64];
} TSCD_ScheduleInfo_ver300;
#pragma pack(pop)

#ifndef TCLASSES_ver300
#define TCLASSES_ver300
#pragma pack(push, 1)
typedef union __TClasses_ver300 {
	unsigned long FullValue;
	struct {
		unsigned long Classes	: 28;  // 하위 28비트. 최대 28개반 표현 가능
		unsigned long Year		: 4;   // 상위 4비트. 최대 16개 학년 표현 가능
	} Part;
} TClasses_ver300;
#pragma pack(pop)
#endif

#pragma pack(push, 1)
typedef struct __TSCD_MoveLessonData_ver300 {
	char LessonName[SCD_MOVELESSON_NAME_SIZE_ver300];
	long SubjectCode;
	TClasses Classes;
	long TeacherCount;
	long Teachers[SCD_MAX_MOVELESSON_TEACHERS_ver300];
	long Times;
	TClassPos pos[SCD_MAX_MOVELESSON_TIMES_ver300];
} TSCD_MoveLessonData_ver300;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_ScheduleDataCell_ver300 {
    TClasses_ver300 Classes;
	BYTE ClassType;
	BYTE ClassInfo;
	char dummy[2];
} TSCD_ScheduleDataCell_ver300;
#pragma pack(pop)

typedef TSCD_ScheduleDataCell_ver300 TSCD_ScheduleData_ver300[SCD_WEEK_COUNT_ver300][SCD_MAX_LESSON_ver300];


bool LoadScheduleData_ver300( FILE *fp );
bool SaveScheduleData_ver300( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
