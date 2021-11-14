// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Global.pas' rev: 6.00

#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <SysUtils.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit


#define GET_ADDSIZE_FOR_ALIGN(a)      ((4-((a) % 4))%4)
//#define GET_ADDSIZE_FOR_ALIGN2(a,b)  (((sizeof(b) * (a)) % 4) / sizeof(b))
#ifndef MIN
#define MIN(a,b) ( ((a) > (b))? (b):(a) )
#endif
#ifndef MAX
#define MAX(a,b) ( ((a) > (b))? (a):(b) )
#endif

#define SCHOOL_NAME_SIZE 			32
#define TEACHER_NAME_SIZE 		12
#define SUBJECT_NAME_SIZE 		20
#define SUBJECT_SHORTNAME_SIZE 	8
#define MOVELESSON_NAME_SIZE    20
#define MOVELESSON_SHORTNAME_SIZE    4

#define YEAR_COUNT 				3
#define WEEK_COUNT 				6
#define MAX_LESSON					8
#define MAX_TEACHER_SUBJECT 		12  /// (YEAR_COUNT*4) Ver3 이전예전 버전 호환을 위해, 차차 줄일 예정
#define MAX_SPC_COUNT 			10
#define MAX_MULTILESSON_CLASS 	4
#define MAX_SPC_COUNT        		10
#define MAX_MOVELESSON_TEACHERS 10
#define MAX_MOVELESSON_TIMES     (6*8)


//-- type declarations -------------------------------------------------------

#define MAKE_CLASS_NO(y,c) ((y)*100 + (c))
#define GET_CLASS_YEAR(cn) ((cn) / 100)
#define GET_CLASS_CLASS(cn) ((cn) % 100)

#define IS_CLASSES_IN(a, b)  	((b) & (1 << ((a)-atCLASS_BASE)))
#define IS_WEEKS_IN(a, b)  	((b) & (1 << ((a)-atWEEK_BASE)))
#define IS_LESSONS_IN(a, b)  	((b) & (1 << ((a)-atLESSON_BASE)))


typedef enum __atYEAR {
	atYEAR_ALL,
	atYEAR_BASE = 1,
	atYEAR_1 = atYEAR_BASE,
	atYEAR_2,
	atYEAR_3,
	atYEAR_MAX = atYEAR_3
} atYEAR;

typedef enum __atWEEK { 
	atWEEK_NONE = 0, 
	atWEEK_BASE = 1,
	//atWEEK_SUN,
	atWEEK_MON = atWEEK_BASE,
	atWEEK_TUE,
	atWEEK_WED,
	atWEEK_THU,
	atWEEK_FRI,
	atWEEK_SAT,
	atWEEK_MAX = atWEEK_SAT
} atWEEK;

typedef enum __atLESSON {
	atLESSON_NONE = 0,
	atLESSON_BASE = 1,
	atLESSON_1 = atLESSON_BASE,
	atLESSON_2,
	atLESSON_3,
	atLESSON_4,
	atLESSON_5,
	atLESSON_6,
	atLESSON_7,
	atLESSON_8,
	atLESSON_MAX = atLESSON_8
} atLESSON;

typedef enum __atCLASS {
	atCLASS_NONE = 0,
	atCLASS_BASE = 1,
	atCLASS_1 = atCLASS_BASE,
	atCLASS_2,
	atCLASS_3,
	atCLASS_4,
	atCLASS_5,
	atCLASS_6,
	atCLASS_7,
	atCLASS_8,
	atCLASS_9,
	atCLASS_10,
	atCLASS_11,
	atCLASS_12,
	atCLASS_13,
	atCLASS_14,
	atCLASS_15,
	atCLASS_16,
	atCLASS_17,
	atCLASS_18,
	atCLASS_19,
	atCLASS_20,
	atCLASS_MAX = atCLASS_20
} atCLASS;


#define CT_NONE 			0x00
#define CT_NORMAL 			0x00
#define CT_FIXED 			0x01
#define CT_SPECIAL 		0x02
#define CT_MOVELESSON 	0x03
#define CT_SPECIAL2 		0x04
#define CT_SPECIAL3 		0x05
#define CT_FOCUS 			0x06
#define CT_ETC 			0x07
#define CT_ETC2 			0x08
#define CT_TEMP 			0x09
#define CT_INVALID			0x7F

#define SPC_CLASS1_MASK 0x0001
#define SPC_CLASS2_MASK 0x0002
#define SPC_CLASS3_MASK 0x0004


typedef struct __TConfigColors {
	TColor CellText;
	TColor CellBackground;
	TColor GridLine;
	TColor FixedCell;
	TColor FocusCell;
	TColor GrayCell;
	TColor LunchTime;
	TColor SpecialLesson;
	TColor MoveLesson;
} TConfigColors;

typedef struct __TConfig {
	int MaxChangeCount;
	TConfigColors Colors;
} TConfig;


typedef struct __TScheduleInfo {
	char ScheduleTitle[32];
	char AuthorName[20];
	char AuthorDate[20];
	char Memo[64];
} TScheduleInfo;

typedef struct __TClassPos {
	unsigned short week;
	unsigned short lesson;
} TClassPos;

typedef union __TClasses {
	unsigned long FullValue;
	struct {
		unsigned long Classes	: 28;  // 하위 28비트. 최대 28개반 표현 가능
		unsigned long Year		: 4;   // 상위 4비트. 최대 16개 학년 표현 가능
	} Part;
} TClasses;

typedef struct __TSpcClass {
	char Name[TEACHER_NAME_SIZE+1 + GET_ADDSIZE_FOR_ALIGN(TEACHER_NAME_SIZE+1)]; // add '\0' and dummy
	unsigned long Years;
	TClassPos Pos[YEAR_COUNT];
} TSpcClass;

typedef struct __TSchoolData {
    char SchoolName[SCHOOL_NAME_SIZE+1 + GET_ADDSIZE_FOR_ALIGN(SCHOOL_NAME_SIZE+1)]; // add '\0' and dummy
	long ClassCount[YEAR_COUNT];
	long WeekLimit[YEAR_COUNT][WEEK_COUNT];
	long SPC_Count;
	TSpcClass SPC[MAX_SPC_COUNT];
	long LunchTime[YEAR_COUNT];
} TSchoolData;

typedef struct __TSubject {
	unsigned short SubjectCode;
	unsigned short TargetYear;
	char FullName[SUBJECT_NAME_SIZE+1 + GET_ADDSIZE_FOR_ALIGN(SUBJECT_NAME_SIZE+1)]; // add '\0' and dummy
	char ShortName[SUBJECT_SHORTNAME_SIZE+1 + GET_ADDSIZE_FOR_ALIGN(SUBJECT_SHORTNAME_SIZE+1)]; // add '\0' and dummy
} TSubject;

typedef struct __TTeacherSubject {
	unsigned long Attr;					// 속성 (이동수업 등...)
	unsigned short SubjectCode;		// 과목 코드
	short Times;						// 주당 시수
	TClasses Classes;					// 대상 학반
	unsigned short LimitWeeks;			// 제한 요일 (최상위 비트 True/False)
	unsigned short LimitLessons;		// 제한 시간 (최상위 비트 True/False)
} TTeacherSubject;

typedef struct __TTeacherData {
	unsigned long Attr;					// 속성 (이동수업 등...)
	unsigned short TeacherNo;
	char TeacherName[TEACHER_NAME_SIZE+1 + GET_ADDSIZE_FOR_ALIGN(TEACHER_NAME_SIZE+1)]; // add '\0' and dummy
	unsigned short ChargeClass;
	long SubjectCount;
	TTeacherSubject Subject[MAX_TEACHER_SUBJECT];
	WORD Etc;
	BYTE StressFactor[4];  // 1. 5교시이상, 2. 3교시연속, 3. 점심전후, 4.기타 => 총합이 100 이하가 되도록...
} TTeacherData;
typedef TTeacherData *PTeacherData;

typedef struct __TMoveLessonData {
	char LessonName[MOVELESSON_NAME_SIZE+1 + GET_ADDSIZE_FOR_ALIGN(MOVELESSON_NAME_SIZE+1)];
	char ShortName[MOVELESSON_SHORTNAME_SIZE+1 + GET_ADDSIZE_FOR_ALIGN(MOVELESSON_SHORTNAME_SIZE+1)];
	short SubjectCode; char dummy[2];
	TClasses Classes;
	long TeacherCount;
	long Teachers[MAX_MOVELESSON_TEACHERS];
	long Times;
	TClassPos pos[MAX_MOVELESSON_TIMES];
} TMoveLessonData;

typedef struct __TScheduleDataCell {
//	int ClassNo[MAX_MULTILESSON_CLASS + GET_ADDSIZE_FOR_ALIGN2(MAX_MULTILESSON_CLASS,WORD)]; // add dummy for dword align
	TClasses Classes;
	char ClassType;
	char ClassInfo;
	char dummy[2];
} TScheduleDataCell, *PScheduleDataCell;

typedef TScheduleDataCell TScheduleData[WEEK_COUNT][MAX_LESSON];
typedef TScheduleData *PScheduleData;


//AnsiString WeekStr[6];
extern unsigned long SPC_CLASS_MASK_LST[YEAR_COUNT];

extern TConfig g_Config;
extern TScheduleInfo g_ScheduleInfo;
extern TSchoolData g_School;
extern int g_iSubjectCount;
extern TSubject *g_pSubjects;
extern int g_iTeacherCount;
extern TTeacherData *g_pTeachers;
extern int g_iMoveLessonCount;
extern TMoveLessonData *g_pMoveLesson;
extern PScheduleData g_pSchedules;
extern PScheduleData g_pWorkSchedules;
extern PScheduleData g_pCurSchedules;

extern int g_curYear;
extern int g_curWeek;
extern int g_curTeacher;

void InitScheduleSystem(void);
void LoadConfigData(void);
void SaveConfigData(void);

bool InitSubjectData( int iSubjectCount );
bool ReallocSubjectData( int iSubjectCount );

bool InitTeacherData( int iTeacherCount );
bool ReallocTeacherData( int iTeacherCount );

bool InitScheduleData(void);

bool InitMoveLessonData( int iMoveLessonCount );
bool ReallocMoveLessonData( int iMoveLessonCount );

String GetMoveLessonString( int info );

TSubject *GetSubject( int idx );  
TSubject *FindSubjectByCode( short subjectcode );
TSubject *FindSubjectByName( const char *subjecname );

void ClearScheduleData(void);
void CopyToWorkSchedules(void);
void CopyFromWorkSchedules(void);
int GetCurSchedules(void);
int SetCurSchedules(int p);

String GetWeekStr(int week);
int GetWeekLimit( int year, int week );
bool CheckSpcType( int year, int week, int num, int *pNum );
int GetLimitClass( int year );

TTeacherData *GetTeacherData( int t );
void ClearTeacherData( int t );
int GetTeacherSubjectCount( int t );
TTeacherSubject *GetTeacherSubject( int t, int idx );
void ClearTeacherSubject( int t );
void PackTeacherSubject( int t );
String GetTeacherSubjectString( int t, int idx );

TScheduleData *GetScheduleData( int t );
TScheduleDataCell *GetScheduleDataCell( int t, int week, int num );
void SetClassType(int t, int w, int n, int ClassType);
void ClearClasses( int t, int w, int n );
void SetClassNo(int t, int w, int n, int ClassNo);
void SetClassesFull( int t, int w, int n, unsigned long ClassNoFull );
unsigned long GetClassesFull( int t, int w, int n );
void RemoveClassNo( int t, int w, int n, int ClassNo );
int AddClassNo( int t, int w, int n, int ClassNo );
void PackClassNo( int t, int w, int n );
void SetClassInfo(int t, int w, int n, int ClassInfo);
int GetClassType(int t, int w, int n);
int GetClassCount(int t, int w, int n);
WORD GetClassNo(int t, int w, int n, int idx);
WORD GetClassInfo(int t, int w, int n);

bool IsOverlapClass( int t, int sw, int sn, int ew, int en );
bool IsEmptyClassNo( int t, int w, int n );
bool IsCanAddClassNo( int t, int w, int n );
bool IsEmbededClassNo( int t, int w, int n, int ClassNo );
int GetClassOverlapTeacher(int t, int w, int n, WORD c);
void SwapClass(int t, int sw, int sn, int ew, int en);

long GetTeacherTimes( int t, bool isEmbedMovelesson );
long GetTotalTeacherTimes(void);
long GetTotalClassTimes(void);
long GetTotalMoveLessonTimes(void);

bool IsPutClassNo( int t, int w, int n, int ClassNo );
bool PutClassToEmpty( int t, int c, int si, int opt );


#endif	// Global
