//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Global.h"
#include "filefmt/SCD_Files.h"
#include "CSV_Files.h"
#include "GRP_Util.h"
#include "f_Personal.h"
#include "f_Change.h"
#include "f_Sclass.h"
#include "f_Sview.h"
#include "f_Config.h"
#include "f_About.h"
#include "f_ScdInfo.h"
#include "f_School.h"
#include "f_sbj.h"
#include "f_TEACHER.h"
#include "f_MOVLSN.h"
#include "r_schdule.h"
#include "r_classes.h"
#include "r_teacher.h"
#include "A_Util.h"

TfrmMain *frmMain;

#define GrdSizeX 22
#define GrdSizeY 26 /// 32
#define GrdStartX 16
#define GrdStartY 72

static bool  mState;
static int  mStartT, mStartN, mStartW;
static int  curMouseT, curMouseN;

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
    curFileName = "UNTITLED.SCD";
    iCurWork = 0;
}
//---------------------------------------------------------------------------

/***********************************
  지정된 위치에 클래스 출력
************************************/
void DispClassData( HDC hDC, int x, int y, int t, int w, int n )
{
  int i, cnt;
  int px, py;
  TRect Rect;
  WORD TempNum;
  BYTE TempType;
  String TempStr;
  char StrData[256];
  TColor tc;
  HBRUSH hOldBrush, hNewBrush;
  HPEN hOldPen, hNewPen;

  px = (x - 0) * (GrdSizeX + 1) + GrdStartX + 2;
  py = (y - atLESSON_1) * (GrdSizeY + 1) + GrdStartY + 2;
  Rect.Top = py;
  Rect.Left = px;
  Rect.Bottom = py + GrdSizeY;
  Rect.Right = px + GrdSizeX;

  TempNum = 0;
  TempType = GetClassType( t, g_curWeek, n );

  if( g_curYear != atYEAR_ALL ){
    if( n <= GetWeekLimit(g_curYear, g_curWeek) ){
      if( CheckSpcType( g_curYear, w, n, (int *)&TempNum ) ) TempType = CT_SPECIAL;
      if( (TempNum > 0) && (TempType == CT_NORMAL) &&
         (GET_CLASS_YEAR(TempNum) != g_curYear) )
        TempType = CT_INVALID;
    } else
      TempType = CT_INVALID;
  }

  switch( TempType ){
    case CT_NORMAL     : tc = g_Config.Colors.CellBackground; break;
    case CT_FIXED      : tc = g_Config.Colors.FixedCell; break;
    case CT_SPECIAL    : tc = g_Config.Colors.SpecialLesson; break;
    case CT_MOVELESSON : tc = g_Config.Colors.MoveLesson; break;
    case CT_ETC        : tc = g_Config.Colors.GrayCell; break;
    default :            tc = clDkGray; break;
  }

  hNewBrush = CreateSolidBrush( tc );
//  hOldBrush = SelectObject( hDC, hNewBrush );
//  hNewPen = CreatePen( PS_SOLID, 1, tc );
//  hOldPen = SelectObject( hDC, hNewPen );
  SetBkColor( hDC, tc );

  FillRect( hDC, &Rect, hNewBrush );

  switch( TempType ){
    case CT_NORMAL :
    case CT_FIXED :
	  cnt = GetClassCount(t, w, n);
      for( i = 0; i < cnt; i++ ){
        TempNum = GetClassNo(t, w, n, i);
        if( TempStr != "" ) TempStr = TempStr + "\n";
        TempStr = TempStr + Format( "%d-%d", ARRAYOFCONST((GET_CLASS_YEAR(TempNum), GET_CLASS_CLASS(TempNum))) );
      }
      if( TempStr != "" )
        DrawRectText( hDC, Rect, TempStr.c_str() );
      break;
    case CT_MOVELESSON :
      TempNum = GetClassInfo(t, w, n);
      DrawRectText( hDC, Rect, g_pMoveLesson[TempNum].ShortName );
      break;
    case CT_SPECIAL :
      DrawRectText( hDC, Rect, g_School.SPC[TempNum].Name );
      break;
  }

//  SelectObject( hDC, hOldPen );
//  DeleteObject( hNewPen );
//  SelectObject( hDC, hOldBrush );
  DeleteObject( hNewBrush );
}


/******************************
  작업 아이콘을 사용금지시킨다.
*******************************/
void __fastcall TfrmMain::DisableItems(void)
{
  mnuSave->Enabled = FALSE;
  mnuSaveAs->Enabled = FALSE;
  mnuView->Enabled = FALSE;
  mnuTools->Enabled = FALSE;
  mnuPrint->Enabled = FALSE;

  btnSave->Enabled = FALSE;
  btnPersonal->Enabled = FALSE;
  btnClass->Enabled = FALSE;
  btnPrint->Enabled = FALSE;

  btnTools->Enabled = FALSE;

  pntTeacher->Enabled = FALSE;
}


/*********************************
  작업 아이콘을 사용가능으로 만든다.
**********************************/
void __fastcall TfrmMain::EnableItems(void)
{
  mnuSave->Enabled = TRUE;
  mnuSaveAs->Enabled = TRUE;
  mnuView->Enabled = TRUE;
  mnuTools->Enabled = TRUE;
  mnuPrint->Enabled = TRUE;

  btnSave->Enabled = TRUE;
  btnPersonal->Enabled = TRUE;
  btnClass->Enabled = TRUE;
  btnPrint->Enabled = TRUE;

  btnTools->Enabled = TRUE;

  pntTeacher->Enabled = TRUE;
}


/*********************************

**********************************/
void __fastcall TfrmMain::RefreshScreen(void)
{
    pntTeacher->Refresh();
    pntHTimes->Refresh();
    pntVTimes->Refresh();
}


/*********************************

**********************************/
void __fastcall TfrmMain::RecalcScrollBar(void)
{
    int vc;

    if( g_iTeacherCount <= 0 ) return;

    vc = (pntTeacher->Width - GrdStartX) / (GrdSizeX + 1);
    if( (pntTeacher->Width - GrdStartX) % (GrdSizeX + 1) > 0 ) vc++;

    hsbTeacher->PageSize = vc;
    // 버그 땜시... 쩝...
    hsbTeacherChange(hsbTeacher);
}


void __fastcall TfrmMain::SetTeacherCount( int cnt )
{
    if( cnt > 0 ){
      hsbTeacher->Max = cnt;
      hsbTeacher->Enabled = TRUE;
    } else {
      hsbTeacher->Enabled = FALSE;
    }
}


void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	LoadConfigData();
  	InitScheduleSystem();

  	g_curWeek = atWEEK_MON;
  	g_curYear = atYEAR_ALL;
  	mState = FALSE;

  DisableItems();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
    NewHeight = 496;
    if( NewWidth < 534 ) NewWidth = 534;
}


void __fastcall TfrmMain::pntTeacherPaint(TObject *Sender)
{
    TPaintBox *pnt;
    HDC dc;
    HBRUSH brs;
    int i, j, xpos;
    PTeacherData tt;
    TRect Rect;
    char StrData[256];
    int en, sbp;
    HPEN hOldPen, hNewPen1, hNewPen2;
    HFONT hOldFont, hSFont;
    int vc;

    pnt = dynamic_cast<TPaintBox *>(Sender);
    dc = pnt->Canvas->Handle;

    vc = (pnt->Width - GrdStartX) / (GrdSizeX + 1);
    if( (pnt->Width - GrdStartX) % (GrdSizeX + 1) > 0 ) vc++;

    xpos = pntTeacher->Width / GrdSizeX;
    if( pntTeacher->Width % GrdSizeX != 0 ) xpos--;

    sbp = hsbTeacher->Position;

    if( (sbp + vc) < g_iTeacherCount )
      en = vc;
    else
      en = g_iTeacherCount - sbp;

    /* 최좌상단 */
    Rect.Top = 1;
    Rect.Bottom = GrdStartY;
    Rect.Left = 1;
    Rect.Right = GrdStartX;
    DrawButtonLine( dc, Rect );

    /* 새로운 폰트 */
    hSFont = CreateFont( -13, 10, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "돋움체" );
    hOldFont = SelectObject( dc, hSFont );
    SetTextColor( dc, g_Config.Colors.CellText );

    /* 좌측(1~8교시) */
    Rect.Top = GrdStartY + 1 + 1;
    Rect.Bottom = GrdStartY + GrdSizeY + 1;
    for( i = atLESSON_1; i <= atLESSON_MAX; i++ ) {
      DrawButtonLine( dc, Rect );
      StrPCopy( StrData, IntToStr(i) );
      DrawButtonText( dc, Rect, StrData );
      Rect.Top = Rect.Top + GrdSizeY + 1;
      Rect.Bottom = Rect.Bottom + GrdSizeY + 1;
    }

    /* 상단 (선생님 명단) */
    Rect.Top = 1;
    Rect.Bottom = GrdStartY;
    Rect.Left = GrdStartX + 1 + 1;
    Rect.Right = GrdStartX + 1 + GrdSizeX;

    for( i = 0; i < en; i++ ) {
      tt = GetTeacherData( sbp + i );
      DrawButtonLine( dc, Rect );
      DrawButtonText( dc, Rect, tt->TeacherName );
      Rect.Left += GrdSizeX + 1;
      Rect.Right += GrdSizeX + 1;
    }

    SelectObject( dc, hOldFont );
    DeleteObject( hSFont );

    /* 선 */
    hNewPen1 = CreatePen( PS_SOLID, 1, g_Config.Colors.GridLine );
    hNewPen2 = CreatePen( PS_SOLID, 1, g_Config.Colors.LunchTime );
    hOldPen = SelectObject( dc, hNewPen1 );

    for( i = 0; i < en; i++ ) {
      MoveToEx( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 1, NULL );
      LineTo( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 2 + (GrdSizeY + 1) * 8 );
    }
    for( i = atLESSON_1; i <= atLESSON_MAX-1; i++ ) {
      MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + i*(GrdSizeY + 1), NULL );
      LineTo( dc, GrdStartX + (GrdSizeX + 1) * en, GrdStartY + 1 + i*(GrdSizeY + 1) );
    }
    SelectObject( dc, hNewPen2 );
    MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + g_School.LunchTime[0]*(GrdSizeY + 1), NULL );
    LineTo( dc, GrdStartX + (GrdSizeX + 1) * en, GrdStartY + 1 + g_School.LunchTime[0]*(GrdSizeY + 1) );

    SelectObject( dc, hOldPen );
    DeleteObject( hNewPen1 );
    DeleteObject( hNewPen2 );

    /* 데이터 표시 */
    for( i = 0; i < en; i++ ) {
      for( j = atLESSON_1; j <= atLESSON_MAX; j++ ) {
        DispClassData( dc, i, j, sbp+i, g_curWeek, j );
      }
    }

    // 현재 이동 처리 중이라면 포커싱
    if( mState ){
      if( (mStartT >= sbp) && (mStartT < (sbp + vc)) ){
        Rect.Top = GrdStartY + 1;
        Rect.Bottom = GrdStartY + 1 + (GrdSizeY + 1) * 8;
        Rect.Left = GrdStartX + 1 + (GrdSizeX + 1) * (mStartT - sbp) + 1;
        Rect.Right = GrdStartX + 1 + (GrdSizeX + 1) * (mStartT - sbp) + 1 + GrdSizeX;
        HBRUSH hBrush = CreateSolidBrush( g_Config.Colors.FocusCell );
        FrameRect( dc, &Rect, hBrush );
        DeleteObject( hBrush );
      }
    }
}



void __fastcall TfrmMain::pntTeacherMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TPaintBox *pnt;
  int xx, yy;
  int tx, t2, t3, tp;
  BYTE ct;
  PTeacherData tt;
  WORD info;
  String TempStr;
  TPoint p;
  int cnt;

  pnt = dynamic_cast<TPaintBox *>(Sender);

  if( Button == mbLeft ){
    if( (X > GrdStartX) && (Y > GrdStartY) ){
      xx = (X - GrdStartX - 2) / (GrdSizeX + 1);
      yy = (Y - GrdStartY - 2) / (GrdSizeY + 1) + atLESSON_1;

      if( (xx < g_iTeacherCount) && (yy <= atLESSON_MAX) ){
        tx = xx + hsbTeacher->Position;
        tt = GetTeacherData( tx );
        switch( iCurWork ){
          // 정보
          case 0:
             tp = GetClassType( tx, g_curWeek, yy );
             TempStr = "";
             switch( tp ){
                case CT_NORMAL:
                case CT_FIXED:
                  if( !IsEmptyClassNo(tx, g_curWeek, yy) ){
                    info = GetClassInfo( tx, g_curWeek, yy );
                    TempStr = (String)tt->TeacherName + " " + GetTeacherSubjectString(tx, info);
                  }
                  break;
                case CT_MOVELESSON:
                  if( !IsEmptyClassNo(tx, g_curWeek, yy) ){
                    info = GetClassInfo(tx, g_curWeek, yy);
                    TempStr = (String)tt->TeacherName + " =이동수업= " + GetMoveLessonString( info );
                  }
                  break;
             }
             sbStatus->SimpleText = TempStr;
             break;

          // 옮기기
          case 1: if( (GetClassType(tx, g_curWeek, yy) == CT_NORMAL) ){
               if( !mState ){
                 if( !IsEmptyClassNo(tx, g_curWeek, yy) ){
                   mStartT = tx; mStartN = yy;
                   mStartW = g_curWeek;
                   mState = TRUE;

                   sbStatus->SimpleText = (String)tt->TeacherName + " : " + GetWeekStr(g_curWeek) + "요일 " + IntToStr(yy) + "교시 => ";
                   pnt->Cursor = crNo;
                   pnt->Refresh();
                 }
               } else {
                 if( (mStartT == tx) && ((yy != mStartN) || (g_curWeek != mStartW)) ){
                   if( CanItChange( tx, mStartW, mStartN, g_curWeek, yy, NULL ) ){
                     frmChange->ChangeT = tx;
                     frmChange->ChangeSW = mStartW;
                     frmChange->ChangeSN = mStartN;
                     frmChange->ChangeEW = g_curWeek;
                     frmChange->ChangeEN = yy;
                     frmChange->ChangeType = 1;
                     frmChange->ShowModal();
                     RefreshScreen();
                   }
                   mState = FALSE;

                   sbStatus->SimpleText = sbStatus->SimpleText + GetWeekStr(g_curWeek) + "요일 " + IntToStr(yy) + "교시";
                   pnt->Cursor = crDefault;
                   pnt->Refresh();
                 }
               }
             }
             break;

          // 고정/해제
          case 2: if( GetClassType( tx, g_curWeek, yy ) == CT_NORMAL ){
               SetClassType( tx, g_curWeek, yy, CT_FIXED );
               DispClassData( pnt->Canvas->Handle, xx, yy, tx, g_curWeek, yy );
             } else if( GetClassType( tx, g_curWeek, yy ) == CT_FIXED ){
               SetClassType( tx, g_curWeek, yy, CT_NORMAL );
               DispClassData( pnt->Canvas->Handle, xx, yy, tx, g_curWeek, yy );
             }
             break;

          // 합반처리
          case 3: if( GetClassType(tx, g_curWeek, yy) == CT_NORMAL ){
               if( !mState ){
			   	 int cnt = GetClassCount(tx, g_curWeek, yy);
				 if( ( cnt > 0) && (cnt < MAX_MULTILESSON_CLASS) ){
                   mStartT = tx; mStartN = yy;
                   mStartW = g_curWeek;
                   mState = TRUE;

                   sbStatus->SimpleText = (String)tt->TeacherName + " : " + GetWeekStr(g_curWeek) + "요일 " + IntToStr(yy) + "교시 + ";
                   pnt->Cursor = crNo;
                   pnt->Refresh();
                 }
               } else {
                 if( (mStartT == tx) && ((yy != mStartN) || (g_curWeek != mStartW)) ){
                   if( CanItMulti( tx, mStartW, mStartN, g_curWeek, yy, NULL ) ){
                     frmChange->ChangeT = tx;
                     frmChange->ChangeSW = mStartW;
                     frmChange->ChangeSN = mStartN;
                     frmChange->ChangeEW = g_curWeek;
                     frmChange->ChangeEN = yy;
                     frmChange->ChangeType = 2;
                     frmChange->ShowModal();
                     RefreshScreen();
                   }
                   mState = FALSE;

                   sbStatus->SimpleText = sbStatus->SimpleText + GetWeekStr(g_curWeek) + "요일 " + IntToStr(yy) + "교시";
                   pnt->Cursor = crDefault;
                   pnt->Refresh();
                 }
               }
             }
             break;

          // 힙반해제
          case 4: if( (GetClassType(tx, g_curWeek, yy) == CT_NORMAL) ){
               if( !mState ){
			   	 cnt = GetClassCount(tx, g_curWeek, yy);
                 if( cnt >= 2 ){
                   mStartT = tx; mStartN = yy;
                   mStartW = g_curWeek;
                   mState = TRUE;
                   sbStatus->SimpleText = (String)tt->TeacherName + " : " + GetWeekStr(g_curWeek) + "요일 " + IntToStr(yy) + "교시 => ";
                   pnt->Cursor = crNo;
                   pnt->Refresh();
                 }
               } else {
                 if( (mStartT == tx) && ((yy != mStartN) || (g_curWeek != mStartW)) ){
                   if( CanItRelease( tx, mStartW, mStartN, g_curWeek, yy, NULL ) ){
                     frmChange->ChangeT = tx;
                     frmChange->ChangeSW = mStartW;
                     frmChange->ChangeSN = mStartN;
                     frmChange->ChangeEW = g_curWeek;
                     frmChange->ChangeEN = yy;
                     frmChange->ChangeType = 3;
                     frmChange->ShowModal();
                     RefreshScreen();
                   }
                   mState = FALSE;

                   sbStatus->SimpleText = sbStatus->SimpleText + GetWeekStr(g_curWeek) + "요일 " + IntToStr(yy) + "교시";
                   pnt->Cursor = crDefault;
                   pnt->Refresh();
                 }
               }
             }
             break;
        }
      }
    }
  } else {
    if( mState ){
      pnt->Cursor = crDefault;
      mState = FALSE;
      pnt->Refresh();
    } else {
      if( g_iTeacherCount > 0 ){
        if( (X > GrdStartX) && (Y > GrdStartY) ){
          xx = (X - GrdStartX - 2) / (GrdSizeX + 1);
          xx = xx + hsbTeacher->Position;
          tt = GetTeacherData( xx );

          mnuPersonalX->Caption = (String)"개인별(" + tt->TeacherName + ") 시간표";
          mnuPersonalX->Tag = xx;
          p.x = X; p.y = Y;
          p = pnt->ClientToScreen( p );
          pnt->PopupMenu->Popup( p.x, p.y );
        }
      }
    }
  }

}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::tabYearChange(TObject *Sender, int NewTab,
      bool &AllowChange)
{
    g_curYear = NewTab;
    RefreshScreen();
}


void __fastcall TfrmMain::mnuCloseClick(TObject *Sender)
{
    Close();
}


void __fastcall TfrmMain::mnuConfigClick(TObject *Sender)
{
    frmConfig->ShowModal();
    RefreshScreen();
}


void __fastcall TfrmMain::mnuMoveLessonSetClick(TObject *Sender)
{
    frmMoveLesson->ShowModal();
	if( frmMoveLesson->IsChange ){
	  ClearScheduleData();
      RefreshScreen();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuToolsClick(TObject *Sender)
{
    if( mState ){
      pntTeacher->Cursor = crDefault;
      mState = FALSE;
    }

    dynamic_cast<TAction *>(Sender)->Checked = TRUE;
    iCurWork = dynamic_cast<TAction *>(Sender)->Tag;
    pnlTools->Caption = dynamic_cast<TAction *>(Sender)->Caption;
}


void __fastcall TfrmMain::pntVTimesPaint(TObject *Sender)
{
    TPaintBox *pnt;
    HDC dc;
    HBRUSH brs;
    int t, n, s, y;
    char StrData[256];

    pnt = dynamic_cast<TPaintBox *>(Sender);
    dc = pnt->Canvas->Handle;

    brs = CreateSolidBrush( GetSysColor(COLOR_BTNFACE) );
    FillRect( dc, &(pnt->Canvas->ClipRect), brs );
    DeleteObject( brs );

    for( n = atLESSON_1; n <= atLESSON_MAX; n++ ) {
      s = 0;
      for( t = 0; t < g_iTeacherCount; t++ )
        if( ((GetClassType( t, g_curWeek, n ) == CT_NORMAL) || (GetClassType( t, g_curWeek, n ) == CT_FIXED)) && !IsEmptyClassNo( t, g_curWeek, n ) ){
          s += GetClassCount( t, g_curWeek, n );
        }
      y = (n - atLESSON_BASE) * (GrdSizeY + 1) + 8;
      StrPCopy( StrData, Format( "%3d", ARRAYOFCONST((s)) ) );
      TextOut( dc, 1, y, StrData, StrLen(StrData) );
    }
}


void __fastcall TfrmMain::pntHTimesPaint(TObject *Sender)
{
    TPaintBox *pnt;
    HDC dc;
    int t, n, s, x, sbp, vc, en;
    char StrData[256];
    TScheduleDataCell *sc;

    pnt = dynamic_cast<TPaintBox *>(Sender);
    dc = pnt->Canvas->Handle;

    vc = (pnt->Width - GrdStartX) / (GrdSizeX + 1);
    if( (pnt->Width - GrdStartX) % (GrdSizeX + 1) > 0 ) vc++;

    sbp = hsbTeacher->Position;

    if( (sbp + vc) < g_iTeacherCount )
      en = vc;
    else
      en = g_iTeacherCount - sbp;

    for( t = 0; t < en; t++ ) {
      s = 0;
      for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
         s += GetClassCount(sbp+t, g_curWeek, n);
      }
      x = (t) * (GrdSizeX + 1) + 5;
      StrPCopy( StrData, Format( "%2d", ARRAYOFCONST((s)) ) );
      TextOut( dc, x, 1, StrData, StrLen(StrData) );
    }
}

void __fastcall TfrmMain::pntTeacherMouseMove(TObject *Sender,
  TShiftState Shift, int X, int Y)
{
  int tt, nn, tx;

  if( mState ){
    if( (X > GrdStartX) && (Y > GrdStartY) ){
      tt = (X - GrdStartX - 2) / (GrdSizeX + 1);
      nn = (Y - GrdStartY - 2) / (GrdSizeY + 1) + atLESSON_1;

      if( (tt != curMouseT) || (nn != curMouseN) ){
        if( (tt < g_iTeacherCount) && (nn <= atLESSON_MAX) ){
          tx = tt + hsbTeacher->Position;
          switch( iCurWork ){
            // 옮기기
            case 1 : if( (tx == mStartT) && CanItChange( mStartT, mStartW, mStartN, g_curWeek, nn, NULL ) )
                  pntTeacher->Cursor = crMultiDrag;
                else
                  pntTeacher->Cursor = crNo;
                break;
            // 합반 처리
            case 3 : if( (tx == mStartT) && CanItMulti( mStartT, mStartW, mStartN, g_curWeek, nn, NULL ) )
                  pntTeacher->Cursor = crMultiDrag;
                else
                  pntTeacher->Cursor = crNo;
                break;
            // 합반 해제
            case 4 : if( (tx == mStartT) && CanItRelease( mStartT, mStartW, mStartN, g_curWeek, nn, NULL ) )
                  pntTeacher->Cursor = crMultiDrag;
                else
                  pntTeacher->Cursor = crNo;
                break;
          }
        } else
          pntTeacher->Cursor = crNoDrop;
        curMouseT = tt;
        curMouseN = nn;
      }
    } else pntTeacher->Cursor = crNoDrop;
  }
}


void __fastcall TfrmMain::mnuOpenClick(TObject *Sender)
{
    if( dlgOpen->Execute() ){
      curFileName = dlgOpen->FileName;

      if( ! LoadScheduleData( curFileName.c_str() ) ){
        MessageDlg2( "파일 열기에 실패했습니다.\n\n"
                    "잘못된 파일이거나 구버전 파일 형식입니다.", "에러",
                    mtWarning, TMsgDlgButtons() << mbOK, 0 );
        return;
      }

      if( g_iTeacherCount > 0 ){
        btnNew->Enabled = TRUE;
        EnableItems();
      } else {
        btnNew->Enabled = FALSE;
        DisableItems();
      }
  
      SetTeacherCount(g_iTeacherCount);
      RecalcScrollBar();
      RefreshScreen();
      frmPersonal->RefreshTeachers();
    }
}


void __fastcall TfrmMain::mnuSaveClick(TObject *Sender)
{
    if( curFileName == "UNTITLED.SCD" )
      mnuSaveAs->Click();
    else {
      SaveScheduleData( curFileName.c_str() );
      MessageDlg2( "저장되었습니다.", "정보", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    }
}


void __fastcall TfrmMain::mnuSaveAsClick(TObject *Sender)
{
    if( dlgSave->Execute() ){
      curFileName = dlgSave->FileName;
      SaveScheduleData( curFileName.c_str() );
      MessageDlg2( "저장되었습니다.", "정보", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    }
}


void __fastcall TfrmMain::mnuPersonalClick(TObject *Sender)
{
    frmPersonal->ShowModal();
    RefreshScreen();
}


void __fastcall TfrmMain::mnuClassClick(TObject *Sender)
{
    frmClass->ShowModal();
    RefreshScreen();
}


void __fastcall TfrmMain::mnuPrnTeachersClick(TObject *Sender)
{
    qrTeachers->Preview();
}


void __fastcall TfrmMain::mnuPrnClassesClick(TObject *Sender)
{
    qrClasses->Preview();
}


void __fastcall TfrmMain::mnuPrnSchedulesClick(TObject *Sender)
{
    qrSchedules->Preview();
}

void __fastcall TfrmMain::mnuInitAllocAllClick(TObject *Sender)
{
  int i, j, k, si, cnt;
  int t, y, s, c;
  TMoveLessonData *ml;
  TScheduleDataCell *sc;
  TTeacherData *tt;
  TTeacherSubject *tsbj;
  TSubject *sbj;

  ClearScheduleData();

  for( i = 0; i < g_iMoveLessonCount; i++ ){
    ml = &g_pMoveLesson[i];
    cnt = ml->TeacherCount;
    for( j = 0; j < cnt; j++ ){
      t = ml->Teachers[j];
      for( k = 0; k < ml->Times; k++ ){
        sc = GetScheduleDataCell( t, ml->pos[k].week, ml->pos[k].lesson );
        sc->ClassType = CT_MOVELESSON;
        sc->Classes = ml->Classes;
        sc->ClassInfo = i;
      }
    }
  }

  for( t = 0; t < g_iTeacherCount; t++ ){
      cnt = GetTeacherSubjectCount( t );
      for( si = 0; si < cnt; si++ ){
        tsbj = GetTeacherSubject( t, si ); // 해당 교사의 과목을 얻는다.
        if( (tsbj->SubjectCode != 0) && !(tsbj->Attr & 0x01)){  // 과목이 있고 이동수업이 아니라면...
          s = tsbj->Classes.Part.Classes;
          y = tsbj->Classes.Part.Year;     // 과목에 해당 학년 반 데이터를 얻어...
          for( i = 0; i < tsbj->Times; i++ ) {  // 해당 시수만큼 반복...
            for( c = atCLASS_1; c <= atCLASS_MAX; c++ ) {
              if( IS_CLASSES_IN( c, s ) ){  // 해당되는 반이 있으면...
                if( !PutClassToEmpty( t, MAKE_CLASS_NO(y,c), si, 0 ) ){  // 배치 시도...
                  tt = GetTeacherData( t );
                  sbj = FindSubjectByCode( tsbj->SubjectCode );
                  MessageBeep( MB_ICONEXCLAMATION );
                  MessageDlg2( "초기배치에 실패했습니다.\n문제를 해결한 후에 다시 시도하십시요.\n\n"
                               +Format("※ 배치에 실패한 교사 : %s (%d학년 %s)", ARRAYOFCONST((tt->TeacherName, (int)tsbj->Classes.Part.Year, sbj->FullName))),
                               "경고", mtWarning, TMsgDlgButtons() << mbOK, 0 );
//                  ClearScheduleData();        // 잠시... 임시로 막음.
//                  DisableItems();             // 잠시... 임시로 막음.
                  goto ExitSub;
                }
              }
            }
          }
        } //if
      }
  } //t

  EnableItems();
  curFileName = "UNTITLED.SCD";

ExitSub:
    RefreshScreen();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( MessageDlg2( "정말 끝내시겠습니까?", "종료 확인",
                   mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0 ) != mrYes ){
      CanClose = FALSE;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuScheduleInfoClick(TObject *Sender)
{
    frmScheduleInfo->ShowModal();    
//    RefreshScreen();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuSchoolInfoClick(TObject *Sender)
{
    frmSchool->ShowModal();
    RefreshScreen();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuSubjectInfoClick(TObject *Sender)
{
   frmSubject->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTeacherInfoClick(TObject *Sender)
{
    int iOldTeacherCount;

    iOldTeacherCount = g_iTeacherCount;
    frmTeacher->ShowModal();
	if( frmTeacher->IsChange ){
	    if( iOldTeacherCount != g_iTeacherCount ){
		  InitScheduleData();
	    } else {
		  ClearScheduleData();
        }
        RefreshScreen();
    }

    SetTeacherCount(g_iTeacherCount);
    RecalcScrollBar();
    frmPersonal->RefreshTeachers();

    if( g_iTeacherCount > 0 ){
      btnNew->Enabled = TRUE;
    } else {
      btnNew->Enabled = FALSE;
    }
}


void __fastcall TfrmMain::N8Click(TObject *Sender)
{
    frmAbout->ShowModal();
}


void __fastcall TfrmMain::hsbTeacherChange(TObject *Sender)
{
    // 원래 불필요하나, 스크롤바 버그 탓으로 넣음
    if( hsbTeacher->Position > hsbTeacher->Max - hsbTeacher->PageSize ){
      hsbTeacher->Position = hsbTeacher->Max - hsbTeacher->PageSize + 1;
    }

    pntTeacher->Refresh();
    pntHTimes->Refresh();
}


void __fastcall TfrmMain::Panel1Resize(TObject *Sender)
{
    RecalcScrollBar();
}


void __fastcall TfrmMain::btnDropdownClick(TObject *Sender)
{
    TPoint p;
    TToolButton *btn;

    btn = dynamic_cast<TToolButton *>(Sender);
    p.x = btn->Left + 3;
    p.y = btn->Top + btn->Height + 3;
    p = this->ClientToScreen( p );
    btn->DropdownMenu->Popup( p.x, p.y );
}


void __fastcall TfrmMain::mnuPersonalXClick(TObject *Sender)
{
    frmPersonal->SetTeacherNo( dynamic_cast<TMenuItem *>(Sender)->Tag );
    mnuPersonal->Click();
}


void __fastcall TfrmMain::FormKeyPress(TObject *Sender, char &Key)
{
    switch( Key ){
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7': tabWeek->TabIndex = Key - '1';
                tabWeekChange(tabWeek);
                break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tabWeekChange(TObject *Sender)
{
    g_curWeek = tabWeek->TabIndex + 1;
    RefreshScreen();
}

void __fastcall TfrmMain::mnuPrnTeacherCSVClick(TObject *Sender)
{
    bool r = WriteTeacherCSV( "TR_PRN.CSV" );

    if( r )
      MessageDlg2( "TR_PRN.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "TR_PRN.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}

void __fastcall TfrmMain::mnuPrnClassesCSVClick(TObject *Sender)
{
    bool r = WriteClassesCSV( "CL_PRN.CSV" );

    if( r )
      MessageDlg2( "CL_PRN.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "CL_PRN.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N2Click(TObject *Sender)
{
    bool r = WriteTeacherCSV_2( "TR_PRN_2.CSV" );

    if( r )
      MessageDlg2( "TR_PRN_2.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "TR_PRN_2.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N5Click(TObject *Sender)
{
    bool r = WriteClassesCSV_2( "CL_PRN_2.CSV" );

    if( r )
      MessageDlg2( "CL_PRN_2.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "CL_PRN_2.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N19Click(TObject *Sender)
{
    bool r = WriteTeacherOnWeekCSV( "TR_PRN_3.CSV" );

    if( r )
      MessageDlg2( "TR_PRN_3.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "TR_PRN_3.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N20Click(TObject *Sender)
{
    bool r = WriteClassesOnWeekCSV( "CL_PRN_3.CSV" );

    if( r )
      MessageDlg2( "CL_PRN_3.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "CL_PRN_3.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N21Click(TObject *Sender)
{
    bool r = WriteTeacherOnWeekCSV_2( "TR_PRN_4.CSV" );

    if( r )
      MessageDlg2( "TR_PRN_4.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "TR_PRN_4.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N22Click(TObject *Sender)
{
    bool r = WriteClassesOnWeekCSV_2( "CL_PRN_4.CSV" );

    if( r )
      MessageDlg2( "CL_PRN_4.CSV 파일 출력이 끝났습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
    else
      MessageDlg2( "CL_PRN_4.CSV 파일 출력 오류입니다.", "메시지", mtWarning, TMsgDlgButtons() << mbOK, 0 );
}
//---------------------------------------------------------------------------

