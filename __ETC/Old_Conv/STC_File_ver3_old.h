#ifndef __STC_FILE_VER3_H_
#define __STC_FILE_VER3_H_

#include <windows.h>
#include <stdio.h>


#include "Global.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SCD_TEACHER_NAME_SIZE_VER3    	  12
//#define SCD_SPCIEL_SUBJECT_NAME_SIZE_VER3   8
#define SCD_SUBJECT_NAME_SIZE_VER3    	  20
#define SCD_SUBJECT_SUBNAME_SIZE_VER3    8

#define SCD_TEACHER_SUBJECT_COUNT_VER3  12


#ifndef TCLASSES_VER3
#define TCLASSES_VER3
#pragma pack(push, 1)
typedef union __TClasses_ver3 {
	unsigned long FullValue;
	struct {
		unsigned long Classes	: 28;  // ���� 28��Ʈ. �ִ� 28���� ǥ�� ����
		unsigned long Year		: 4;   // ���� 4��Ʈ. �ִ� 16�� �г� ǥ�� ����
	} Part;
} TClasses_ver3;
#pragma pack(pop)
#endif

#pragma pack(push, 1)
typedef struct __TSCD_TeacherSubject_ver3 {
	unsigned long Attr;
	char Name[SCD_SUBJECT_NAME_SIZE_VER3];
	char SubName[SCD_SUBJECT_SUBNAME_SIZE_VER3];
	TClasses_ver3 Classes;
	long Times;
	unsigned short TargetWeeks;
	unsigned short TargetLessons;
} TSCD_TeacherSubject_ver3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct __TSCD_TeacherData_ver3 {
	long TeacherNo;
	char TeacherName[SCD_TEACHER_NAME_SIZE_VER3];
	long SubjectCount;
	TSCD_TeacherSubject_ver3 Subject[SCD_TEACHER_SUBJECT_COUNT_VER3];
	WORD ChargeClass;
	WORD Etc;
	BYTE StressFactor[4];  // 1. 5�����̻�, 2. 3���ÿ���, 3. ��������, 4.��Ÿ => ������ 100 ���ϰ� �ǵ���...
} TSCD_TeacherData_ver3;
#pragma pack(pop)

bool LoadTeacherData_ver3_old( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
