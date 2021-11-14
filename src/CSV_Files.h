#ifndef __CSV_FILES_H_
#define __CSV_FILES_H_

#include <windows.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


bool WriteTeacherCSV( char *filename );
bool WriteClassesCSV( char *filename );

bool WriteTeacherCSV_2( char *filename );
bool WriteClassesCSV_2( char *filename );

bool WriteTeacherOnWeekCSV( char *filename );
bool WriteClassesOnWeekCSV( char *filename );

bool WriteTeacherOnWeekCSV_2( char *filename );
bool WriteClassesOnWeekCSV_2( char *filename );

#ifdef __cplusplus
};
#endif


#endif
