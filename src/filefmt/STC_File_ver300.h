#ifndef __STC_FILE_VER300_H_
#define __STC_FILE_VER300_H_

#include <windows.h>
#include <stdio.h>


#include "Global.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SCD_TEACHER_NAME_SIZE_ver300    	  12
//#define SCD_SPCIEL_SUBJECT_NAME_SIZE_ver300   8
#define SCD_SUBJECT_NAME_SIZE_ver300    	  20
#define SCD_SUBJECT_SHORTNAME_SIZE_ver300    8

#define SCD_TEACHER_SUBJECT_COUNT_ver300  12


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
typedef struct __TSCD_TeacherSubject_ver300 {
	unsigned long Attr;
	long SubjectCode;
	TClasses_ver300 Classes;
	long Times;
	unsigned short LimitWeeks;
	unsigned short LimitLessons;
} TSCD_TeacherSubject_ver300;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_TeacherData_ver300 {
	long TeacherNo;
	char TeacherName[SCD_TEACHER_NAME_SIZE_ver300];
	long SubjectCount;
	TSCD_TeacherSubject_ver300 Subject[SCD_TEACHER_SUBJECT_COUNT_ver300];
	WORD ChargeClass;
	WORD Etc;
	BYTE StressFactor[4];  // 1. 5교시이상, 2. 3교시연속, 3. 점심전후, 4.기타 => 총합이 100 이하가 되도록...
} TSCD_TeacherData_ver300;
#pragma pack(pop)

bool LoadTeacherData_ver300( FILE *fp );
bool SaveTeacherData_ver300( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
