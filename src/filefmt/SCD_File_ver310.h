#ifndef __SCD_FILE_VER310_H_
#define __SCD_FILE_VER310_H_

#include <windows.h>
#include <stdio.h>


#include "SSC_File_ver300.h"
#include "SSB_File_ver300.h"
#include "STC_File_ver300.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SCD_WEEK_COUNT_ver310       6
#define SCD_MAX_LESSON_ver310         8
#define SCD_MOVELESSON_NAME_SIZE_ver310    20
#define SCD_MOVELESSON_SHORTNAME_SIZE_ver310    8

#define SCD_MAX_MOVELESSON_TEACHERS_ver310 10
#define SCD_MAX_MOVELESSON_TIMES_ver310    (6*8)


#pragma pack(push, 1)
typedef struct __TSCD_ScheduleInfo_ver310 {
	char ScheduleTitle[32];
	char AuthorName[20];
	char AuthorDate[20];
	char Memo[64];
} TSCD_ScheduleInfo_ver310;
#pragma pack(pop)

#ifndef TCLASSES_ver310
#define TCLASSES_ver310
#pragma pack(push, 1)
typedef union __TClasses_ver310 {
	unsigned long FullValue;
	struct {
		unsigned long Classes	: 28;  // 하위 28비트. 최대 28개반 표현 가능
		unsigned long Year		: 4;   // 상위 4비트. 최대 16개 학년 표현 가능
	} Part;
} TClasses_ver310;
#pragma pack(pop)
#endif

#pragma pack(push, 1)
typedef struct __TSCD_MoveLessonData_ver310 {
	char LessonName[SCD_MOVELESSON_NAME_SIZE_ver310];
	char ShortName[SCD_MOVELESSON_SHORTNAME_SIZE_ver310];
	short SubjectCode; char dummy[2];
	TClasses Classes;
	long TeacherCount;
	long Teachers[SCD_MAX_MOVELESSON_TEACHERS_ver310];
	long Times;
	TClassPos pos[SCD_MAX_MOVELESSON_TIMES_ver310];
} TSCD_MoveLessonData_ver310;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_ScheduleDataCell_ver310 {
    TClasses_ver310 Classes;
	BYTE ClassType;
	BYTE ClassInfo;
	char dummy[2];
} TSCD_ScheduleDataCell_ver310;
#pragma pack(pop)

typedef TSCD_ScheduleDataCell_ver310 TSCD_ScheduleData_ver310[SCD_WEEK_COUNT_ver310][SCD_MAX_LESSON_ver310];


bool LoadScheduleData_ver310( FILE *fp );
bool SaveScheduleData_ver310( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
