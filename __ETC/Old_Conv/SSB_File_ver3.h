#ifndef __SSB_FILE_VER3_H_
#define __SSB_FILE_VER3_H_

#include <windows.h>
#include <stdio.h>


#include "Global.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SCD_SUBJECT_NAME_SIZE_VER3    	  20
#define SCD_SUBJECT_SHORTNAME_SIZE_VER3    8


#pragma pack(push, 1)
typedef struct __TSCD_Subject_ver3 {
	short SubjectCode;
	unsigned short TargetYear;
	char FullName[SCD_SUBJECT_NAME_SIZE_VER3];
	char ShortName[SCD_SUBJECT_SHORTNAME_SIZE_VER3];
} TSCD_Subject_ver3;
#pragma pack(pop)


bool LoadSubjectData_ver3( FILE *fp );
bool SaveSubjectData_ver3( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
