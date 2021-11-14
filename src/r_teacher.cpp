//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "r_teacher.h"
//----------------------------------------------------------------------------
#pragma resource "*.dfm"
TqrTeachers *qrTeachers;

#include "Global.h"

//----------------------------------------------------------------------------
__fastcall TqrTeachers::TqrTeachers(TComponent* Owner)
    : TQuickRep(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TqrTeachers::QuickRepBeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    rc = 0;
    Week = atWEEK_MON;
    QRLabel19->Caption = "¿ù";
}
//---------------------------------------------------------------------------
void __fastcall TqrTeachers::QuickRepNeedData(TObject *Sender,
      bool &MoreData)
{
    int i;
    PTeacherData tt;
    WORD TempNum, TempNum2, TempNum3, TempYear;
//    BYTE TempType;
    String TempStr;

    if( (Week <= atWEEK_SAT) ) {
      if( (rc >= g_iTeacherCount) ) {
        QRLabel19->Caption = GetWeekStr(Week);
        this->NewColumn();
        rc = 0;
      }

      tt = GetTeacherData( rc );

      QRLabel1->Caption = tt->TeacherName;

      for( i = 1; i <= 8; i++ ) {
        TempNum = GetClassNo( rc, Week, i, 0 );
#if MAX_MULTILESSON_CLASS >= 2
        TempNum2 = GetClassNo( rc, Week, i, 1 );
#endif
#if MAX_MULTILESSON_CLASS >= 3
        TempNum3 = GetClassNo( rc, Week, i, 2 );
#endif
#if MAX_MULTILESSON_CLASS >= 4
        TempNum3 = GetClassNo( rc, Week, i, 3 );
#endif
//        TempType = GetClassType( rc, Week, i );

        if( TempNum > 0 ) {
          TempStr = Format( "%d-%d", ARRAYOFCONST(( GET_CLASS_YEAR(TempNum), GET_CLASS_CLASS(TempNum) )) );
          if( TempNum2 != 0 ) {
            TempStr = TempStr + Format( ",%d-%d", ARRAYOFCONST(( GET_CLASS_YEAR(TempNum2), GET_CLASS_CLASS(TempNum2) )) );
          }
          if( TempNum3 != 0 ) {
            TempStr = TempStr + Format( ",%d-%d", ARRAYOFCONST(( GET_CLASS_YEAR(TempNum3), GET_CLASS_CLASS(TempNum3) )) );
          }
        } else {
          TempStr = "";
        }
        switch( i ){
            case 1 : QRLabel2->Caption = TempStr; break;
            case 2 : QRLabel3->Caption = TempStr; break;
            case 3 : QRLabel4->Caption = TempStr; break;
            case 4 : QRLabel5->Caption = TempStr; break;
            case 5 : QRLabel6->Caption = TempStr; break;
            case 6 : QRLabel7->Caption = TempStr; break;
            case 7 : QRLabel8->Caption = TempStr; break;
            case 8 : QRLabel9->Caption = TempStr; break;
        }
      }

      rc++;
      if( (rc >= g_iTeacherCount) ) {
//        rc = 0;
        Week++;
        if( Week <= atWEEK_SAT ) {
//          Self.NewPage();
//          Self.NewColumn();
        } else {
          MoreData = false;
          return;
        }
      }
      MoreData = true;
    } else {
      MoreData = false;
    }
}
//---------------------------------------------------------------------------

