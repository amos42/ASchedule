#ifndef __SCD_FILE_VER3_H_
#define __SCD_FILE_VER3_H_

#include <windows.h>
#include <stdio.h>


#include "SSC_File_ver3.h"
#include "STC_File_ver3.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SCD_WEEK_COUNT_VER3       6
#define SCD_MAX_LESSON_VER3         8
#define SCD_MOVELESSON_NAME_SIZE_VER3    20

#define SCD_MAX_MOVELESSON_TEACHERS_VER3 10
#define SCD_MAX_MOVELESSON_TIMES_VER3    (6*8)


#pragma pack(push, 1)
typedef struct __TSCD_ScheduleInfo_ver3 {
	char ScheduleTitle[32];
	char AuthorName[20];
	char AuthorDate[20];
	char Memo[64];
} TSCD_ScheduleInfo_ver3;
#pragma pack(pop)

#ifndef TCLASSES_VER3
#define TCLASSES_VER3
#pragma pack(push, 1)
typedef union __TClasses_ver3 {
	unsigned long FullValue;
	struct {
		unsigned long Classes	: 28;  // 하위 28비트. 최대 28개반 표현 가능
		unsigned long Year		: 4;   // 상위 4비트. 최대 16개 학년 표현 가능
	} Part;
} TClasses_ver3;
#pragma pack(pop)
#endif

#pragma pack(push, 1)
typedef struct __TSCD_MoveLessonData_ver3 {
	char LessonName[SCD_MOVELESSON_NAME_SIZE_VER3];
	char SubjectName[SCD_SUBJECT_NAME_SIZE_VER3];
	TClasses Classes;
	long TeacherCount;
	long Teachers[SCD_MAX_MOVELESSON_TEACHERS_VER3];
	long Times;
	TClassPos pos[SCD_MAX_MOVELESSON_TIMES_VER3];
} TSCD_MoveLessonData_ver3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_ScheduleDataCell_ver3 {
    TClasses_ver3 Classes;
	BYTE ClassType;
	BYTE ClassInfo;
	char dummy[2];
} TSCD_ScheduleDataCell_ver3;
#pragma pack(pop)

typedef TSCD_ScheduleDataCell_ver3 TSCD_ScheduleData_ver3[SCD_WEEK_COUNT_VER3][SCD_MAX_LESSON_VER3];


bool LoadScheduleData_ver3_old( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
