#ifndef __SSB_FILE_VER300_H_
#define __SSB_FILE_VER300_H_

#include <windows.h>
#include <stdio.h>


#include "Global.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SCD_SUBJECT_NAME_SIZE_ver300    	  20
#define SCD_SUBJECT_SHORTNAME_SIZE_ver300    8


#pragma pack(push, 1)
typedef struct __TSCD_Subject_ver300 {
	short SubjectCode;
	unsigned short TargetYear;
	char FullName[SCD_SUBJECT_NAME_SIZE_ver300];
	char ShortName[SCD_SUBJECT_SHORTNAME_SIZE_ver300];
} TSCD_Subject_ver300;
#pragma pack(pop)


bool LoadSubjectData_ver300( FILE *fp );
bool SaveSubjectData_ver300( FILE *fp );


#ifdef __cplusplus
};
#endif


#endif	// Global
