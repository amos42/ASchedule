//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "r_schdule.h"
//----------------------------------------------------------------------------
#pragma resource "*.dfm"
TqrSchedules *qrSchedules;
//----------------------------------------------------------------------------
__fastcall TqrSchedules::TqrSchedules(TComponent* Owner)
    : TQuickRep(Owner)
{
}
//---------------------------------------------------------------------------

#include "Global.h"

void __fastcall TqrSchedules::QuickRepBeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    year = 1;
    cls  = 1;
}
//---------------------------------------------------------------------------

void __fastcall TqrSchedules::QuickRepNeedData(TObject *Sender,
      bool &MoreData)
{
    int i, w, n;
    BYTE TempType;
    String TempStr = "";
    int ViewClass;
    TQRLabel *lbl;
TScheduleDataCell *sc;
TTeacherSubject *tsbj;
TSubject *sbj;

    if( (year <= 3) ) {
      if( cls > g_School.ClassCount[year-atYEAR_BASE] ) {
        this->NewPage();
        cls = 1;
      }

      qrlClass->Caption = Format("%d-%d", ARRAYOFCONST((year, cls)) );

  ViewClass = MAKE_CLASS_NO( year, cls );

  for( w = atWEEK_MON; w <= atWEEK_MAX; w++ ) {
    for( n = atLESSON_1; n <= GetWeekLimit(year,w); n++ ) {
      for( i = 0; i < g_iTeacherCount; i++ ) {
        sc = GetScheduleDataCell( i, w, n );
        if( IsEmbededClassNo( i, w, n, ViewClass ) ){
          switch( sc->ClassType ){
              case CT_NORMAL :
              case CT_FIXED :
                 tsbj = GetTeacherSubject( i, sc->ClassInfo );
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
      lbl = dynamic_cast<TQRLabel *>( this->FindComponent(Format("qrlSubject%d_%d",ARRAYOFCONST((w,n)))) );
      lbl->Caption = TempStr;
    }
    for( n = GetWeekLimit(year,w)+1; n <= atLESSON_MAX; n++ ) {
      lbl = dynamic_cast<TQRLabel *>( this->FindComponent(Format("qrlSubject%d_%d",ARRAYOFCONST((w,n)))) );
      lbl->Caption = "";
    }
  }

  for( i = 0; i < g_School.SPC_Count; i++ ) {
    if( g_School.SPC[i].Years & SPC_CLASS_MASK_LST[year-atYEAR_BASE] ) {
      w = g_School.SPC[i].Pos[year-atYEAR_BASE].week;
      n = g_School.SPC[i].Pos[year-atYEAR_BASE].lesson;
      lbl = dynamic_cast<TQRLabel *>( this->FindComponent(Format("qrlSubject%d_%d",ARRAYOFCONST((w,n)))) );
      lbl->Caption = g_School.SPC[i].Name;
    }
  }

      cls++;
      if( (cls > g_School.ClassCount[year]) ) {
        cls = 1;
        year++;
      }
      MoreData = true;
    } else {
      MoreData = false;
    }
}
//---------------------------------------------------------------------------

