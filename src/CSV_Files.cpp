//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Global.h"
#include "CSV_Files.h"
#include <stdio.h>
//----------------------------------------------------------------------------

/***************************************

****************************************/
bool WriteTeacherCSV( char *filename )
{
    int i, w, t, n, cnt;
    PTeacherData tt;
    TScheduleDataCell *sc;
    int cc;
    String tempStr;
    int f;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }

    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
      tempStr = "(" + GetWeekStr(w) + ")\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      tempStr = "이름, 1교시, 2교시, 3교시, 4교시, 5교시, 6교시, 7교시, 8교시, 시수\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
      tempStr = "==================================================================\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      for( t = 0; t < g_iTeacherCount; t++ ) {
        tt = GetTeacherData( t );

        FileWrite( f, tt->TeacherName, StrLen(tt->TeacherName) );
        tempStr = ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        cc = 0;
        for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
          sc = GetScheduleDataCell( t, w, n );
          if( sc->ClassType == CT_SPECIAL ){
//            tempStr = g_School.SPC[sc->ClassNo[0]-1].Name; // 실제적으로는 이 조건이 걸일 일이 없음.
          } else {
            tempStr = "";
			cnt = GetClassCount(t, w, n);
          	for( i = 0; i < cnt; i++ ){
			  if( tempStr != "" ) tempStr = tempStr + " ";
              int classno = GetClassNo( t, w, n, i );
              tempStr = tempStr + IntToStr(sc->Classes.Part.Year) + "-" + IntToStr(GET_CLASS_CLASS(classno));
              cc++;
       		}
          }

          tempStr = "=T(\"" + tempStr + "\")";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
          tempStr = ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }

        tempStr = IntToStr(cc);
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
        tempStr = "\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }

      tempStr = "\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}


/***************************************

****************************************/
bool WriteClassesCSV( char *filename )
{
    int i;
    String tempStr;
    int f;
    int t, w, y, c, n;
    TScheduleDataCell *sc;
    TTeacherSubject *tsbj;
    TSubject *sbj;
    WORD year;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }

    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
      tempStr = "(" + GetWeekStr(w) + ")\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      tempStr = "학년-반, 1교시, 2교시, 3교시, 4교시, 5교시, 6교시, 7교시, 8교시\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
      tempStr = "===============================================================\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      for( y = atYEAR_1; y <= atYEAR_3; y++ ) {
        for( c = atCLASS_1; c <= GetLimitClass(y); c++ ) {
          tempStr = "=T(\"" + IntToStr(y) + "-" + IntToStr(c) + "\")";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
          tempStr = ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );

          for( n = atLESSON_1; n <= GetWeekLimit(y,w); n++ ) {
            tempStr = "";

            for( i = 0; i < g_School.SPC_Count; i++ ) {
              if( ((g_School.SPC[i].Years & SPC_CLASS_MASK_LST[y-atYEAR_BASE]) != 0) &&
                 (g_School.SPC[i].Pos[y-atYEAR_BASE].week == w) && (g_School.SPC[i].Pos[y-atYEAR_BASE].lesson == n) ){
                tempStr = g_School.SPC[i].Name;
                break;
              }
            }

            if( tempStr == "" ){
              for( t = 0; t < g_iTeacherCount; t++ ) {
                sc = GetScheduleDataCell( t, w, n );
                if( (sc->ClassType != CT_NORMAL) && (sc->ClassType != CT_FIXED) && (sc->ClassType != CT_MOVELESSON) ) continue; 
                if( IsEmbededClassNo( t, w, n, MAKE_CLASS_NO(y,c) ) ){
                  if( (sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED) ){
                    tsbj = GetTeacherSubject( t, sc->ClassInfo );
                    sbj = FindSubjectByCode( tsbj->SubjectCode );
                    tempStr = sbj->ShortName;
                  } else if( sc->ClassType == CT_MOVELESSON ){
                    sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                    tempStr = sbj->ShortName;
                  }
                  break;
                }
              }
            }

            FileWrite( f, tempStr.c_str(), tempStr.Length() );
            tempStr = ",";
            FileWrite( f, tempStr.c_str(), tempStr.Length() );
          }

          tempStr = "\n";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }
      }

      tempStr = "\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}
//---------------------------------------------------------------------------


/***************************************

****************************************/
bool WriteTeacherCSV_2( char *filename )
{
    int i, w, t, n, cnt;
    PTeacherData tt;
    TScheduleDataCell *sc;
    int cc;
    String tempStr;
    int f;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }


    tempStr = "이름,";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
      tempStr = "(" + GetWeekStr(w) + "),,,,,,,,|,";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }
    tempStr = "시수\n";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );

    tempStr = "이름,";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
      tempStr = "1교시,2교시,3교시,4교시,5교시,6교시,7교시,8교시,|,";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }
    tempStr = "시수\n";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );

    tempStr = "==================================================================\n";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );

    for( t = 0; t < g_iTeacherCount; t++ ) {
      tt = GetTeacherData( t );

      FileWrite( f, tt->TeacherName, StrLen(tt->TeacherName) );
      tempStr = ",";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      cc = 0;
      for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {

//        cc = 0;
        for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
          sc = GetScheduleDataCell( t, w, n );
          if( sc->ClassType == CT_SPECIAL ){
//            tempStr = g_School.SPC[sc->ClassNo[0]-1].Name; // 실제적으로는 이 조건이 걸일 일이 없음.
          } else {
            tempStr = "";
			cnt = GetClassCount(t, w, n);
          	for( i = 0; i < cnt; i++ ){
			  if( tempStr != "" ) tempStr = tempStr + " ";
              int classno = GetClassNo( t, w, n, i );
              tempStr = tempStr + IntToStr(sc->Classes.Part.Year) + "-" + IntToStr(GET_CLASS_CLASS(classno));
              cc++;
       		}
          }

          tempStr = "=T(\"" + tempStr + "\")";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
          tempStr = ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }

//        tempStr = IntToStr(cc);
//        FileWrite( f, tempStr.c_str(), tempStr.Length() );
//        tempStr = "\n";
//        FileWrite( f, tempStr.c_str(), tempStr.Length() );
        tempStr = "|,";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }

      tempStr = IntToStr(cc);
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      tempStr = "\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}


/***************************************

****************************************/
bool WriteClassesCSV_2( char *filename )
{
    int i;
    String tempStr;
    int f;
    int t, w, y, c, n;
    TScheduleDataCell *sc;
    TTeacherSubject *tsbj;
    TSubject *sbj;
    WORD year;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }

    tempStr = "학반,";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
      tempStr = "(" + GetWeekStr(w) + "),,,,,,,,|,";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }
    tempStr = "\n";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );

    tempStr = "학반,";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
      tempStr = "1교시,2교시,3교시,4교시,5교시,6교시,7교시,8교시,|,";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }
    tempStr = "\n";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );

    tempStr = "==================================================================\n";
    FileWrite( f, tempStr.c_str(), tempStr.Length() );

    for( y = atYEAR_1; y <= atYEAR_3; y++ ) {
      for( c = atCLASS_1; c <= GetLimitClass(y); c++ ) {
        tempStr = "=T(\"" + IntToStr(y) + "-" + IntToStr(c) + "\")";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
        tempStr = ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
//          for( n = atWEEK_MON; n <= GetWeekLimit(y,w); n++ ) {
          for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
            tempStr = "";

            for( i = 0; i < g_School.SPC_Count; i++ ) {
              if( ((g_School.SPC[i].Years & SPC_CLASS_MASK_LST[y-atYEAR_BASE]) != 0) &&
                 (g_School.SPC[i].Pos[y-atYEAR_BASE].week == w) && (g_School.SPC[i].Pos[y-atYEAR_BASE].lesson == n) ){
                tempStr = g_School.SPC[i].Name;
                break;
              }
            }

            if( tempStr == "" ){
              for( t = 0; t < g_iTeacherCount; t++ ) {
                sc = GetScheduleDataCell( t, w, n );
                if( (sc->ClassType != CT_NORMAL) && (sc->ClassType != CT_FIXED) && (sc->ClassType != CT_MOVELESSON) ) continue; 
                if( IsEmbededClassNo( t, w, n, MAKE_CLASS_NO(y,c) ) ){
                  if( (sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED) ){
                    tsbj = GetTeacherSubject( t, sc->ClassInfo );
                    sbj = FindSubjectByCode( tsbj->SubjectCode );
                    tempStr = sbj->ShortName;
                  } else if( sc->ClassType == CT_MOVELESSON ){
                    sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                    tempStr = sbj->ShortName;
                  }
                  break;
                }
              }
            }

            FileWrite( f, tempStr.c_str(), tempStr.Length() );
            tempStr = ",";
            FileWrite( f, tempStr.c_str(), tempStr.Length() );
          }

          tempStr = "|,";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }
        tempStr = "\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }

//      tempStr = "\n";
//      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}
//---------------------------------------------------------------------------

/***************************************

****************************************/
bool WriteTeacherOnWeekCSV( char *filename )
{
    int i, w, t, n, cnt;
    PTeacherData tt;
    TScheduleDataCell *sc;
TTeacherSubject *tsbj;
TSubject *sbj;
    int cc;
    String tempStr, tempStr2;
    int f;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }

    for( t = 0; t < g_iTeacherCount; t++ ){
      tt = GetTeacherData( t );

      tempStr = (String)tt->TeacherName + " 시간표\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      tempStr = ",";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
      for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
        tempStr = (String)GetWeekStr(w) + ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }
      tempStr = "\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
        tempStr = IntToStr(n) + ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
          sc = GetScheduleDataCell( t, w, n );


          if( sc->ClassType == CT_SPECIAL ){
//            tempStr = g_School.SPC[sc->ClassNo[0]-1].Name; // 실제적으로는 이 조건이 걸일 일이 없음.
          } else {
            tempStr = "";
			cnt = GetClassCount(t, w, n);
          	for( i = 0; i < cnt; i++ ){
			  if( tempStr != "" ) tempStr = tempStr + " ";
              int classno = GetClassNo( t, w, n, i );
              tempStr = tempStr + IntToStr(sc->Classes.Part.Year) + "-" + IntToStr(GET_CLASS_CLASS(classno));
       		}
          }

          tempStr2 = "";
          if( tempStr != "" ){
            switch( sc->ClassType ){
              case CT_NORMAL :
              case CT_FIXED :
                 tsbj = GetTeacherSubject( t, sc->ClassInfo );
                 sbj = FindSubjectByCode( tsbj->SubjectCode );
                 tempStr2 = sbj->ShortName;
                 break;
              case CT_MOVELESSON :
                 sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                 tempStr2 = sbj->ShortName;
                 break;
              default :
                 break;
            }
            tempStr = "=T(\"" + tempStr + " (" + tempStr2 + ")" + "\")";
            FileWrite( f, tempStr.c_str(), tempStr.Length() );
          }

          tempStr = ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }

        tempStr = "\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }

      tempStr = "\n\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}


/***************************************

****************************************/
bool WriteClassesOnWeekCSV( char *filename )
{
    int i;
    String tempStr;
    int f;
    int t, w, y, c, n;
    TScheduleDataCell *sc;
    TTeacherData *tt;
    TTeacherSubject *tsbj;
    TSubject *sbj;
    WORD year;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }

    for( y = atYEAR_1; y <= atYEAR_3; y++ ) {
      for( c = atCLASS_1; c <= GetLimitClass(y); c++ ) {
        tempStr = Format("%d학년 %d반 시간표\n", ARRAYOFCONST((y,c)));
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        tempStr = ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
        for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
          tempStr = (String)GetWeekStr(w) + ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }
        tempStr = "\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );


        for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
          tempStr = IntToStr(n) + ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );

          for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
            tempStr = "";

            for( i = 0; i < g_School.SPC_Count; i++ ) {
              if( ((g_School.SPC[i].Years & SPC_CLASS_MASK_LST[y-atYEAR_BASE]) != 0) &&
                 (g_School.SPC[i].Pos[y-atYEAR_BASE].week == w) && (g_School.SPC[i].Pos[y-atYEAR_BASE].lesson == n) ){
                tempStr = g_School.SPC[i].Name;
                break;
              }
            }

            if( tempStr == "" ){
              for( t = 0; t < g_iTeacherCount; t++ ) {
                sc = GetScheduleDataCell( t, w, n );
                if( (sc->ClassType != CT_NORMAL) && (sc->ClassType != CT_FIXED) && (sc->ClassType != CT_MOVELESSON) ) continue;
                if( IsEmbededClassNo( t, w, n, MAKE_CLASS_NO(y,c) ) ){
                  if( (sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED) ){
                    tsbj = GetTeacherSubject( t, sc->ClassInfo );
                    sbj = FindSubjectByCode( tsbj->SubjectCode );
                    tempStr = sbj->ShortName;
                  } else if( sc->ClassType == CT_MOVELESSON ){
                    sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                    tempStr = sbj->ShortName;
                  }
                  tt = GetTeacherData(t);
                  tempStr = tempStr + " (" + tt->TeacherName +")";
                  break;
                }
              }
            }

            FileWrite( f, tempStr.c_str(), tempStr.Length() );
            tempStr = ",";
            FileWrite( f, tempStr.c_str(), tempStr.Length() );
          }

          tempStr = "\n";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }

        tempStr = "\n\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }

//      tempStr = "\n";
//      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}


/***************************************

****************************************/
bool WriteTeacherOnWeekCSV_2( char *filename )
{
    int i, w, t, n, cnt;
    PTeacherData tt;
    TScheduleDataCell *sc;
TTeacherSubject *tsbj;
TSubject *sbj;
    int cc;
    String tempStr;
    int f;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }

    for( t = 0; t < g_iTeacherCount; t++ ){
      tt = GetTeacherData( t );

      tempStr = (String)tt->TeacherName + " 시간표\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      tempStr = ",";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
      for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
        tempStr = (String)GetWeekStr(w) + ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }
      tempStr = "\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );

      for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
        tempStr = IntToStr(n) + ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
          sc = GetScheduleDataCell( t, w, n );

          if( sc->ClassType == CT_SPECIAL ){
//            tempStr = g_School.SPC[sc->ClassNo[0]-1].Name; // 실제적으로는 이 조건이 걸일 일이 없음.
          } else {
            tempStr = "";
			cnt = GetClassCount(t, w, n);
          	for( i = 0; i < cnt; i++ ){
			  if( tempStr != "" ) tempStr = tempStr + " ";
              int classno = GetClassNo( t, w, n, i );
              tempStr = tempStr + IntToStr(sc->Classes.Part.Year) + "-" + IntToStr(GET_CLASS_CLASS(classno));
       		}
            tempStr = "=T(\"" + tempStr + "\")";
            FileWrite( f, tempStr.c_str(), tempStr.Length() );
          }
          tempStr = ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }
        tempStr = "\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        tempStr = ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
          sc = GetScheduleDataCell( t, w, n );

          tempStr = "";
          if( !IsEmptyClassNo(t, w, n) ){
            switch( sc->ClassType ){
              case CT_NORMAL :
              case CT_FIXED :
                 tsbj = GetTeacherSubject( t, sc->ClassInfo );
                 sbj = FindSubjectByCode( tsbj->SubjectCode );
                 tempStr = sbj->FullName;
                 break;
              case CT_MOVELESSON :
                 sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                 tempStr = sbj->FullName;
                 break;
              default :
                 break;
            }
            FileWrite( f, tempStr.c_str(), tempStr.Length() );
          }
          tempStr = ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }
        tempStr = "\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }

      tempStr = "\n\n";
      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}


/***************************************

****************************************/
bool WriteClassesOnWeekCSV_2( char *filename )
{
    int i;
    String tempStr;
    int f;
    int t, w, y, c, n;
    TScheduleDataCell *sc;
    TTeacherData *tt;
    TTeacherSubject *tsbj;
    TSubject *sbj;
    WORD year;

    f = FileCreate( filename );
    if( f <= 0 ){
      return false;
    }

    for( y = atYEAR_1; y <= atYEAR_3; y++ ) {
      for( c = atCLASS_1; c <= GetLimitClass(y); c++ ) {
        tempStr = Format("%d학년 %d반 시간표\n", ARRAYOFCONST((y,c)));
        FileWrite( f, tempStr.c_str(), tempStr.Length() );

        tempStr = ",";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
        for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
          tempStr = (String)GetWeekStr(w) + ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }
        tempStr = "\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );


        for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
          tempStr = IntToStr(n) + ",";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );

          for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
            tempStr = "";

            for( i = 0; i < g_School.SPC_Count; i++ ) {
              if( ((g_School.SPC[i].Years & SPC_CLASS_MASK_LST[y-atYEAR_BASE]) != 0) &&
                 (g_School.SPC[i].Pos[y-atYEAR_BASE].week == w) && (g_School.SPC[i].Pos[y-atYEAR_BASE].lesson == n) ){
                tempStr = g_School.SPC[i].Name;
                break;
              }
            }

            if( tempStr == "" ){
              for( t = 0; t < g_iTeacherCount; t++ ) {
                sc = GetScheduleDataCell( t, w, n );
                if( (sc->ClassType != CT_NORMAL) && (sc->ClassType != CT_FIXED) && (sc->ClassType != CT_MOVELESSON) ) continue;
                if( IsEmbededClassNo( t, w, n, MAKE_CLASS_NO(y,c) ) ){
                  if( (sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED) ){
                    tsbj = GetTeacherSubject( t, sc->ClassInfo );
                    sbj = FindSubjectByCode( tsbj->SubjectCode );
                    tempStr = sbj->FullName;
                  } else if( sc->ClassType == CT_MOVELESSON ){
                    sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                    tempStr = sbj->FullName;
                  }
                  tt = GetTeacherData(t);
                  tempStr = tempStr + " (" + tt->TeacherName +")";
                  break;
                }
              }
            }

            FileWrite( f, tempStr.c_str(), tempStr.Length() );
            tempStr = ",";
            FileWrite( f, tempStr.c_str(), tempStr.Length() );
          }

          tempStr = "\n";
          FileWrite( f, tempStr.c_str(), tempStr.Length() );
        }

        tempStr = "\n\n";
        FileWrite( f, tempStr.c_str(), tempStr.Length() );
      }

//      tempStr = "\n";
//      FileWrite( f, tempStr.c_str(), tempStr.Length() );
    }

    FileClose( f );

    return true;
}



