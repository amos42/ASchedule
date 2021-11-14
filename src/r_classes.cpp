//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "r_classes.h"
//----------------------------------------------------------------------------
#pragma resource "*.dfm"
TqrClasses *qrClasses;
//----------------------------------------------------------------------------
__fastcall TqrClasses::TqrClasses(TComponent* Owner)
    : TQuickRep(Owner)
{
}
//---------------------------------------------------------------------------

#include "Global.h"

void __fastcall TqrClasses::QuickRepBeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    year = atYEAR_1;
    cls  = atCLASS_1;
    Week = atWEEK_MON;
    QRLabel19->Caption = "¿ù";
}
//---------------------------------------------------------------------------

void __fastcall TqrClasses::QuickRepNeedData(TObject *Sender,
      bool &MoreData)
{

    int i, n, t;
//    PTeacherData tt;
//    PScheduleData ts;
//    WORD TempNum, TempNum2, TempYear;
//    BYTE TempType;
    String TempStr;
	TScheduleDataCell *sc;
TTeacherSubject *tsbj;
TSubject *sbj;

    if( (Week <= atWEEK_SAT)) {
      if( (year > 3)) {
        QRLabel19->Caption = GetWeekStr(Week);
        this->NewColumn();
        year = atYEAR_1;
      }

      QRLabel1->Caption = Format("%d-%d", ARRAYOFCONST((year, cls)) );

      for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
            TempStr = "";

            for( i = 0; i < g_School.SPC_Count; i++ ) {
              if( ((g_School.SPC[i].Years && SPC_CLASS_MASK_LST[year-atYEAR_BASE]) != 0) &&
                 (g_School.SPC[i].Pos[year-atYEAR_BASE].week == Week) && (g_School.SPC[i].Pos[year-atYEAR_BASE].lesson == n)) {
                TempStr = g_School.SPC[i].Name;
                break;
              }
            }

            if( TempStr == "") {
              for( t = 0; t < g_iTeacherCount; t++ ) {
			  	sc = GetScheduleDataCell( t, Week, n );

        if( IsEmbededClassNo( t, Week, n, MAKE_CLASS_NO(year, cls) ) ){
          switch( sc->ClassType ){
              case CT_NORMAL :
              case CT_FIXED :
                 tsbj = GetTeacherSubject( t, sc->ClassInfo );
                 sbj = FindSubjectByCode( tsbj->SubjectCode );
                 TempStr = sbj->ShortName;
                 break;
              case CT_MOVELESSON :
                 sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                 TempStr = sbj->ShortName;
                 break;
          }
          break;
        }
              }
            }

        switch( n ){
            case atLESSON_1 : QRLabel2->Caption = TempStr; break;
            case atLESSON_2 : QRLabel3->Caption = TempStr; break;
            case atLESSON_3 : QRLabel4->Caption = TempStr; break;
            case atLESSON_4 : QRLabel5->Caption = TempStr; break;
            case atLESSON_5 : QRLabel6->Caption = TempStr; break;
            case atLESSON_6 : QRLabel7->Caption = TempStr; break;
            case atLESSON_7 : QRLabel8->Caption = TempStr; break;
            case atLESSON_8 : QRLabel9->Caption = TempStr; break;
        }
      }

      cls++;
      if( cls > GetLimitClass( year )/*g_School.ClassCount[year-atYEAR_BASE])*/) {
        cls = atCLASS_1;
        year++;
        if( year > atYEAR_3) {
          Week++;
        }
        if( Week <= atWEEK_SAT) {
//          this->NewPage();
//          this->NewColumn();
        } else {
//          MoreData = false;
//          Exit;
        }
      }
      MoreData = true;
    } else {
      MoreData = false;
    }
}
//---------------------------------------------------------------------------

