//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "SCD_File_ver200.h"
//----------------------------------------------------------------------------

static int ConvClassInfo( int t, int classinfo )
{
    int cnf = classinfo / 10;
    int cnt = classinfo % 10;
    int cc = 0;

    if( classinfo == 0 ) return -1;
    for( int i = 0 ; i < MAX_TEACHER_SUBJECT; i ++ ){
       TTeacherSubject *sbj = GetTeacherSubject( t, i );
       if( sbj->Classes.Part.Year == (unsigned)cnf ){
          cc++;
          if( cc == cnt ) return i;
       }
    }

    return -1;
}


static int MyAddSubject( char *tempStr )
{
    TSubject *sbj;
	int id;

    if(  g_iSubjectCount > 0 ){ 
  	  sbj = GetSubject(g_iSubjectCount-1);
	  id = sbj->SubjectCode + 1;
      ReallocSubjectData(g_iSubjectCount+1);
    } else {
	  id = 1;
	  InitSubjectData(1);
    }
	
	sbj = GetSubject(g_iSubjectCount-1);
    sbj->SubjectCode = id;
	sbj->TargetYear = 0;
	strcpy( sbj->FullName, tempStr );
	strcpy( sbj->ShortName, tempStr );

	return id;
}


/***********************************
  .SCD ������ �ε��Ѵ�. (Ver 2)
************************************/
bool LoadScheduleData_ver200( FILE *fp )
{
    int t, y, w, n, i, x, c;
    TSCD_ScheduleFileHeader hdr;
    PScheduleData ts;
    TSubject *sbj;
    PTeacherData tt;
    TTeacherSubject *tsbj;
    TSCD_SchoolData_ver200 school_ver200;
    TSCD_TeacherData_ver200 teacher_data_ver200;
    TSCD_ScheduleData_ver200 schedule_data_ver200;
    char tmpStr[32];
    int tc;
    int idx;

    // �б� ���� ������ �б�
    fread( &school_ver200, sizeof(TSCD_SchoolData_ver200), 1, fp );
    for( y = 0; y < 3; y ++ ) {  // 1�г�~3�г�
      g_School.ClassCount[y] = school_ver200.ClassCount[y];
      for( w = 0; w < 6; w++ ) // ������~�����
        g_School.WeekLimit[y][w] = school_ver200.WeekLimit[y][w];
      g_School.SPC_Count = school_ver200.SPC_Count;
      for( i = 0; i < MAX_SPC_COUNT_ver200; i++ ) {
        StrCopy( g_School.SPC[i].Name, school_ver200.SPC[i].Name );
        g_School.SPC[i].Years = school_ver200.SPC[i].Years;
        g_School.SPC[i].Pos[y].week = school_ver200.SPC[i].Pos[y].week;
        g_School.SPC[i].Pos[y].lesson = school_ver200.SPC[i].Pos[y].lesson;
      }
      g_School.LunchTime[y] = school_ver200.LunchTime;
    }

    // ���� �� �б�
    fread( &tc, sizeof(long), 1, fp );

    // �������ŭ �޸� �Ҵ�
	InitTeacherData( tc );

    // ���� �б�
    for( t = 0; t < g_iTeacherCount; t++ ) {
      fread( &teacher_data_ver200, sizeof(TSCD_TeacherData_ver200), 1, fp );

      tt = GetTeacherData( t );
      tt->TeacherNo = teacher_data_ver200.TeacherNo;
      strncpy( tt->TeacherName, teacher_data_ver200.TeacherName, 8 );
      tt->TeacherName[8] = '\0';
      idx = 0;
      ClearTeacherSubject( t );
      for( y = 0; y < 3; y++ ) {
        for( i = 0; i < 4; i++ ) {
          if( (String)teacher_data_ver200.Subject[y][i].Name != "" ){
            tsbj = GetTeacherSubject( t, idx++ );
			tsbj->Attr = 0x0000;
            strncpy( tmpStr, teacher_data_ver200.Subject[y][i].Name, 4 );
            tmpStr[4] = '\0';
            sbj = FindSubjectByName( tmpStr );
            if( sbj ){
              tsbj->SubjectCode = sbj->SubjectCode;
            } else {
              tsbj->SubjectCode = MyAddSubject( tmpStr );
            }
            tsbj->Times = teacher_data_ver200.Subject[y][i].Times;
            tsbj->Classes.Part.Year = y + atYEAR_BASE;
            unsigned long v = 0;
            for( c = GET_CLASS_CLASS(teacher_data_ver200.Subject[y][i].StartClass); c <= GET_CLASS_CLASS(teacher_data_ver200.Subject[y][i].EndClass); c++ ){
               v |= 1 << (c-atCLASS_BASE);
            }
            tsbj->Classes.Part.Classes = v;
            tsbj->LimitWeeks = 0x00;
            tsbj->LimitLessons = 0x00;
          }
        }
      }
      tt->SubjectCount = idx;
    }

    // �ð�ǥ ������ �Ҵ� (�������ŭ)
	InitScheduleData();
	
    // �ð�ǥ ������ �б�
    for( t = 0; t < g_iTeacherCount; t++ ) {
      fread( &schedule_data_ver200, sizeof(TSCD_ScheduleData_ver200), 1, fp );

      for( w = 0; w < 6; w++ ){
        for( n = 0; n < 8; n++ ){
          SetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver200[w][n].ClassType );
		  AddClassNo( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver200[w][n].ClassNo );
//          SetClassNo( t, w+atWEEK_BASE, n+atLESSON_BASE, 0, schedule_data_ver200[w][n].ClassNo );
#if MAX_MULTILESSON_CLASS >= 2
		    AddClassNo( t, w+atWEEK_BASE, n+atLESSON_BASE, schedule_data_ver200[w][n].ClassNo2 );
#endif
//            SetClassNo( t, w+atWEEK_BASE, n+atLESSON_BASE, 1, schedule_data_ver200[w][n].ClassNo2 );
          x = ConvClassInfo( t, schedule_data_ver200[w][n].ClassInfo );
          SetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE, x );
        }
      }
    }

    return TRUE;
}


/***********************************
  .SCD ���Ϸ� ����. (Ver 2)
************************************/
bool SaveScheduleData_ver200( FILE *fp )
{
#if 0  /// �ٲ� ������ ���� ��, ���� ���� �κ� ������ ������ �����Ƽ� ����. ������ ������ �� �� ����.
    int i, t, y, w, n, x;
    TSCD_ScheduleFileHeader hdr;
    TTeacherSubject *sbj;
    TSCD_SchoolData_ver200 school_ver200;
    TSCD_TeacherData_ver200 teacher_data_ver200;
    TSCD_ScheduleData_ver200 schedule_data_ver200;
//    PScheduleData ts;
    PTeacherData tt;

    // ���� ������ ����
    for( y = 0; y < 3; y ++ ) {  // 1�г�~3�г�
      school_ver200.ClassCount[y] = g_School.ClassCount[y];
      for( w = 0; w < 6; w++ ) // ������~�����
        school_ver200.WeekLimit[y][w] = g_School.WeekLimit[y][w];
      school_ver200.SPC_Count = g_School.SPC_Count;
      for( i = 0; i < MAX_SPC_COUNT_ver200; i++ ) {
        StrCopy( school_ver200.SPC[i].Name, g_School.SPC[i].Name );
        school_ver200.SPC[i].Years = g_School.SPC[i].Years;
        school_ver200.SPC[i].Pos[y].week = g_School.SPC[i].Pos[y].week;
        school_ver200.SPC[i].Pos[y].lesson = g_School.SPC[i].Pos[y].lesson;
      }
    }
    school_ver200.LunchTime = g_School.LunchTime;
    FileWrite( f, &school_ver200, sizeof(TSCD_SchoolData_ver200) );

    // ���� �� ����
    FileWrite( f, &g_iTeacherCount, sizeof(long) );

    if( g_iTeacherCount > 0 ){
      // ���� ����
	  for( t = 0; t < g_iTeacherCount; t++ ) {
        memset( &teacher_data_ver200, 0, sizeof(TSCD_TeacherData_ver200) );

		tt = GetTeacherData( t );
		teacher_data_ver200.TeacherNo = tt->TeacherNo;
		strncpy( teacher_data_ver200.TeacherName, tt->TeacherName, 8 );

/*
        // �� �κ��� ���� ������ ���� ������ ��� �����ϴ�. ���� ���������� �̷� �������� ������ �Ұ��ϴ�.
        // (���� �Ұ��� �ƴ�����... ������ ������ �� �� �����̶� �������� �ʾҴ�.)
		for( y = 0; y < 3; y++ ) {
		  for( i = 0; i < 4; i++ ) {
			sbj = GetTeacherSubject( t, y+atYEAR_BASE, i );
			strncpy( teacher_data_ver200.Subject[y][i].Name, sbj->SubName, 4 ); // ĭ�� ���� ������ SubName����...
			teacher_data_ver200.Subject[y][i].StartClass = sbj->StartClass;
			teacher_data_ver200.Subject[y][i].EndClass = sbj->EndClass;
			teacher_data_ver200.Subject[y][i].Times = sbj->Times;
            // sbj->TargetWeeks�� �ش� �ʵ� ����.
		  }
		}
*/

        FileWrite( f, &teacher_data_ver200, sizeof(TSCD_TeacherData_ver200) );
	  }
  
	  // �ð�ǥ ������ ����
	  for( t = 0; t < g_iTeacherCount; t++ ) {
        memset( &schedule_data_ver200, 0, sizeof(TSCD_ScheduleData_ver200) );
		for( w = 0; w < 6; w++ ){
		  for( n = 0; n < 8; n++ ){
			schedule_data_ver200[w][n].ClassType = GetClassType( t, w+atWEEK_BASE, n+atLESSON_BASE );
			schedule_data_ver200[w][n].ClassNo = GetClassNo1( t, w+atWEEK_BASE, n+atLESSON_BASE );
            if( MAX_MULTILESSON_CLASS >= 2 )
			  schedule_data_ver200[w][n].ClassNo2 = GetClassNo2( t, w+atWEEK_BASE, n+atLESSON_BASE );
            x = GetClassInfo( t, w+atWEEK_BASE, n+atLESSON_BASE );
            if( x > 0 ) x += 1; // ���� ſ... --;
			schedule_data_ver200[w][n].ClassInfo = x;
		  }
		}
        FileWrite( f, &schedule_data_ver200, sizeof(TSCD_ScheduleData_ver200) );
      }
    }

    return TRUE;
#else
    return FALSE;
#endif
}
