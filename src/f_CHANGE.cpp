//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_change.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmChange *frmChange;

#include "Global.h"
#include "f_Sview.h"

#define MAXCHANGE 32

typedef struct tagTViewList {
    WORD TeacherNo;
    WORD StartW, EndW;
    WORD StartN, EndN;
    TfrmView *frmView;
} TViewList;

TViewList ViewList[MAXCHANGE];

static int  ChangeCount;
static bool  isAddList;

int ReleaseIdx = 0;



//---------------------------------------------------------------------------
__fastcall TfrmChange::TfrmChange(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

/*************************
  �丮��Ʈ�� �ϳ� �߰��Ѵ�.
**************************/
static void AddChangeList( int t, int sw, int sn, int ew, int en )
{
  TfrmView *tv, *tvo;
  PScheduleData ts;
  PTeacherData tt;
  int temp;

  ViewList[ChangeCount].TeacherNo = t;

  ViewList[ChangeCount].StartW = sw;
  ViewList[ChangeCount].StartN = sn;
  ViewList[ChangeCount].EndW = ew;
  ViewList[ChangeCount].EndN = en;

  ViewList[ChangeCount].frmView = new TfrmView(frmChange);
  tv = ViewList[ChangeCount].frmView;
  if( ChangeCount == 0 ){
    tv->Top = 0;
    tv->Left = 0;
  } else {
    tvo = ViewList[ChangeCount - 1].frmView;
    tv->Top = tvo->Top;
    tv->Left = tvo->Left + tvo->Width;
    if( tv->Left + tv->Width > Screen->Width ) {
      tv->Left = 0;
      tv->Top = tvo->Top + tvo->Height;
    }
  }

  tv->ViewTeacher = t;
  tv->StartPos.week = sw; tv->StartPos.lesson = sn;
  tv->EndPos.week = ew;   tv->EndPos.lesson = en;
  tv->RecalcInvalidInfo();

//  ts = &g_pWorkSchedules[t];  // �۾��ϰ� �ִ� ���� �����ش�.
//  memcpy( (*tv->ViewData), ts, sizeof(TScheduleData) ); // �����ø� �� ������, ������ �������� ���߿� ����...
//  tv->ViewData_src = *GetScheduleData( t ); // �����ø� �� ������, ������ �������� ���߿� ����...
//  (*tv->ViewData) = &*tv->ViewData;
  tv->ViewPage = GetCurSchedules();
//  tv->ViewData = GetScheduleData( t );

  tt = GetTeacherData( t );
  tv->Caption = IntToStr(ChangeCount+1) + "��° : " + tt->TeacherName;

/*
  if( (*tv->ViewData)[sw-atWEEK_BASE][sn-atLESSON_BASE].ClassNo[0] > 0 ) {
    temp = (*tv->ViewData)[sw-atWEEK_BASE][sn-atLESSON_BASE].ClassInfo;
    tv->Change1 = GetWeekStr(sw) + IntToStr(sn) + "\n"
                 + tt->Subject[ temp ].Name;
  } else
    tv->Change1 = "";

  if( (*tv->ViewData)[ew-atWEEK_BASE][en-atLESSON_BASE].ClassNo[0] > 0 ) {
    temp = (*tv->ViewData)[ew-atWEEK_BASE][en-atLESSON_BASE].ClassInfo;
    tv->Change2 = GetWeekStr(ew) + IntToStr(en) + "\n"
				 + tt->Subject[ temp ].Name;
  } else
    tv->Change2 = "";
*/

  if( !IsEmptyClassNo( t, sw, sn ) ){
    temp = GetScheduleDataCell( t, sw, sn )->ClassInfo;
    tv->Change1 = GetWeekStr(sw) + IntToStr(sn) + "\n" + FindSubjectByCode(GetTeacherSubject(t, temp)->SubjectCode)->FullName;
  } else
    tv->Change1 = "";

  if( !IsEmptyClassNo( t, ew, en ) ) {
    temp = GetScheduleDataCell( t, ew, en )->ClassInfo;
    tv->Change2 = GetWeekStr(ew) + IntToStr(en) + "\n" + FindSubjectByCode(GetTeacherSubject(t, temp)->SubjectCode)->FullName;
  } else
    tv->Change2 = "";
}

/*********************
  �� ��带 �̵��Ѵ�.
**********************/
static bool ChangeScheduleNode( int t, int sw, int sn, int ew, int en, bool FirstChange )
{
  int i;
  TScheduleDataCell *c1, *c2;
  TTeacherSubject *sbj1, *sbj2;
  int cnt, cn;

  int t1, t2;
//  WORD y1, y2;
  bool r;

  r = FALSE;

  if( ChangeCount < g_Config.MaxChangeCount ){
	c1 = GetScheduleDataCell( t, sw, sn );
	c2 = GetScheduleDataCell( t, ew, en );

    // �̹� ���� ���� �߿� �ѹ� �ű� ���̸� ����.
    if( (c1->ClassType == CT_TEMP) || (c2->ClassType == CT_TEMP) ) return false;

    // �� �� �ϳ��� �̵� ������ ����.
    if( (c1->ClassType == CT_FIXED) || (c2->ClassType == CT_FIXED) ) return false;

    // �ű� ���� Ư�������� �ɸ��� ������ ����.
//    if( c1->ClassNo[0] > 0 ){
    if( !IsEmptyClassNo(t, sw, sn) ){
//	  if( CheckSpcType(GET_CLASS_YEAR(c1->ClassNo[0]), ew, en, NULL) ) return false;
	  if( CheckSpcType(c1->Classes.Part.Year, ew, en, NULL) ) return false;
    }
//    if( c2->ClassNo[0] > 0 ){
    if( !IsEmptyClassNo(t, ew, en) ){
//	  if( CheckSpcType(GET_CLASS_YEAR(c2->ClassNo[0]), sw, sn, NULL) ) return false;
	  if( CheckSpcType(c2->Classes.Part.Year, sw, sn, NULL) ) return false;
    }

    sbj1 = GetTeacherSubject( t, c1->ClassInfo );
    sbj2 = GetTeacherSubject( t, c2->ClassInfo );

    // ���� �ű� ��ġ�� ��ġ ������ �ɸ��� ������ ����.
    if( sbj1 ){
      if( (sbj1->LimitWeeks & 0x8000) && !IS_WEEKS_IN(ew, sbj1->LimitWeeks) ) return false;
      if( (sbj1->LimitLessons & 0x8000) && !IS_LESSONS_IN(en, sbj1->LimitLessons) ) return false;
    }
    if( sbj2 ){
      if( (sbj2->LimitWeeks & 0x8000) && !IS_WEEKS_IN(sw, sbj2->LimitWeeks) ) return false;
  	  if( (sbj2->LimitLessons & 0x8000) && !IS_LESSONS_IN(sn, sbj2->LimitLessons) ) return false;
    }

    // �ϴ� �ٲ۴�. ���Ŀ� ��ġ�� ���� �Ǵ�...
    if( FirstChange ){
      SwapClass( t, sw, sn, ew, en );
    }
    if( isAddList ) AddChangeList( t, sw, sn, ew, en );
    ChangeCount ++;

	c1 = GetScheduleDataCell( t, sw, sn );
	c2 = GetScheduleDataCell( t, ew, en );

    if( (c1->ClassType == CT_NORMAL) && (c2->ClassType == CT_NORMAL) ){
      // �̵� ����� ������ ǥ��
  	  c1->ClassType = CT_TEMP;
	  c2->ClassType = CT_TEMP;

	  cnt = GetClassCount( t, sw, sn );

	  for( i = 0; i < cnt; i++ ){
//        if( sn <= GetWeekLimit(GET_CLASS_YEAR(c1->ClassNo[i]), sw) ){
        if( sn <= GetWeekLimit(c1->Classes.Part.Year, sw) ){
//          t1 = GetClassOverlapTeacher( t, sw, sn, c1->ClassNo[i] );
          int cl = GetClassNo( t, sw, sn, i );
          t1 = GetClassOverlapTeacher( t, sw, sn, cl );
          if( t1 >= 0 ){
            r = ChangeScheduleNode( t1, sw, sn, ew, en, TRUE );  // ���ȣ��
            if( !r ) return r;
          } else if( t1 == -1 ){
            r = TRUE;
          } else
            r = FALSE;
        } else {
          r = FALSE;
          return r;
        }
      }

	  cnt = GetClassCount( t, ew, en );
      for( i = 0; i < cnt; i++ ){
//        if( en <= GetWeekLimit(GET_CLASS_YEAR(c2->ClassNo[i]), ew) ){
        if( en <= GetWeekLimit(c2->Classes.Part.Year, ew) ){
//          t2 = GetClassOverlapTeacher( t, ew, en, c2->ClassNo[i] );
          int cl = GetClassNo( t, ew, en, i );
          t2 = GetClassOverlapTeacher( t, ew, en, cl );
          if( t2 >= 0 ){
            r = ChangeScheduleNode( t2, ew, en, sw, sn, TRUE );  // ���ȣ��
            if( !r ) return r;
		  } else if( t2 == -1 ){
			 r = TRUE;
		  } else
			 r = FALSE;
        } else {
          r = FALSE;
          return r;
        }
      }
    }
  }

  return r;
}


/**********************************
  �Ű����� ���� ������ ���� ���ɴ�.
***********************************/
bool CanItChange( int t, int sw, int sn, int ew, int en, int *pChangeCount )
{
    bool r;

    if( (sw == ew) && (sn == en) ) return false;

    if( IsOverlapClass( t, sw, sn, ew, en ) ) return false;

    ChangeCount = 0;

    CopyToWorkSchedules();

    SetCurSchedules( 1 );
    r = ChangeScheduleNode( t, sw, sn, ew, en, TRUE );
    SetCurSchedules( 0 );

    if( pChangeCount ){
      *pChangeCount = (r)? ChangeCount : 0;
    }

    return r;
}


/***************************
  �չ��� ������ ���� ���ɴ�.
****************************/
bool CanItMulti( int t, int sw, int sn, int ew, int en, int *pChangeCount )
{
    PScheduleData ts;
    TScheduleDataCell *sc1, *sc2;
    WORD i, y;
    bool r;

    if( (sw == ew) && (sn == en) ) return false;

    if( GetClassCount( t, sw, sn ) >= 2 ) return false;  // �������� ������ 1���� ����. 2�� �̻��� ���� ���߿� ����... --;;
    if( !IsCanAddClassNo( t, ew, en ) ) return false;  // �� ������ ������ ����
    if( GetClassCount( t, ew, en ) <= 0 ) return false;  // �̹� �Ѱ��� ��� ���� ������ ����

    ChangeCount = 0;

    sc1 = GetScheduleDataCell(t, sw, sn);
    sc2 = GetScheduleDataCell(t, ew, en);

    int cl = GetClassNo( t, sw, sn, 0 );
	if( !IsEmbededClassNo( t, ew, en, cl ) &&
	   (sc1->ClassInfo == sc2->ClassInfo) ){
	  // ������ ����ü �ʱ�ȭ
	  CopyToWorkSchedules();

	  SetCurSchedules( 1 );

	  // �չ��� ��Ų��.
	  if( AddClassNo( t, ew, en, cl ) > 0 ){
	    RemoveClassNo( t, sw, sn, cl );

        // ���� �޴� ������ �̵� ����
	    r = ChangeScheduleNode( t, sw, sn, ew, en, FALSE );
      } else
        r = FALSE;

	  SetCurSchedules( 0 );
	} else
	  r = FALSE;

    if( pChangeCount ){
      *pChangeCount = (r)? ChangeCount : 0;
    }

    return r;
}


/***************************
  �չ������� ������ ���� ���ɴ�.
****************************/
bool CanItRelease( int t, int sw, int sn, int ew, int en, int *pChangeCount )
{
    bool r;

    if( (sw == ew) && (sn == en) ) return false;

    if( GetClassCount( t, sw, sn ) < 2 ) return false; // �̹� �Ѱ��� ��� ���� ������ ����
    if( GetClassCount( t, ew, en ) > 0 ) return false;  // ������ ���� ������ 0���� ����. 1�� �̻��� ���� �����ؼ� ���߿� ����... --;;
//    if( GetClassCount( t, ew, en ) >= MAX_MULTILESSON_CLASS ) return false;  // ������ ���� ���� ���ڰ� �ִ� ������ �Ѿ�� ����

    ChangeCount = 0;

    // ������ ����ü �ʱ�ȭ
    CopyToWorkSchedules();

    SetCurSchedules( 1 );

    // �չ��� ������Ų��.
    int cl = GetClassNo( t, sw, sn, ReleaseIdx );
    if( AddClassNo( t, ew, en, cl ) > 0  ){
      RemoveClassNo( t, sw, sn, cl );

      r = ChangeScheduleNode( t, sw, sn, ew, en, FALSE );
    } else
      r = FALSE;

    SetCurSchedules( 0);

    if( pChangeCount ){
      *pChangeCount = (r)? ChangeCount : 0;
    }

    return r;
}


void __fastcall TfrmChange::FormCreate(TObject* Sender)
{
  ChangeCount = 0;
  isAddList = FALSE;
  ChangeType = 0;
}


void __fastcall TfrmChange::FormShow(TObject* Sender)
{
  WORD i;
  TfrmView *tv;
  bool r;

  ChangeCount = 0;
  if( ChangeType > 0 ){
    isAddList = TRUE;
    switch( ChangeType ){
      case 1: r = CanItChange( ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN, NULL ); break;
      case 2: r = CanItMulti( ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN, NULL ); break;
      case 3: r = CanItRelease( ChangeT, ChangeSW, ChangeSN, ChangeEW, ChangeEN, NULL ); break;
      default: r = FALSE; break;
    }
    if( r ){
      for( i = 0; i < ChangeCount; i++ ){
        ViewList[i].frmView->Show();
//        frmChange->Top = ViewList[ChangeCount-1].frmView->Top + ViewList[ChangeCount-1].frmView->Height + 1;
//        frmChange->Left = ViewList[ChangeCount-1].frmView->Left;
      }
    }
    isAddList = FALSE;
    ChangeType = 0;
  }
}


void __fastcall TfrmChange::OKBtnClick(TObject* Sender)
{
    CopyFromWorkSchedules();
    Close();
}


void __fastcall TfrmChange::CancelBtnClick(TObject* Sender)
{
    Close();
}


void __fastcall TfrmChange::FormClose(TObject* Sender, TCloseAction &Action)
{
  int i;

  for( i = 0; i < ChangeCount; i++ )
    delete ViewList[i].frmView;

  ChangeCount = 0;
}

