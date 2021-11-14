//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_SCLASS.h"
#include "Global.h"
#include "GRP_Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define GrdSizeX 42
#define GrdSizeY 28 /// 32
#define GrdStartX 16
#define GrdStartY 22

TfrmClass *frmClass;

//---------------------------------------------------------------------------
__fastcall TfrmClass::TfrmClass(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


/***********************************
  지정된 위치에 클래스 출력
************************************/
void __fastcall TfrmClass::DispClassData(HDC hDC, int w, int n)
{
  int px, py;
  TRect Rect;
  BYTE TempType;
  String tempStr;
  char StrData[256];
  TColor tc;
  HBRUSH hOldBrush, hNewBrush;

  px = (w-atWEEK_BASE) * (GrdSizeX + 1) + GrdStartX + 2;
  py = (n-atLESSON_BASE) * (GrdSizeY + 1) + GrdStartY + 2;
  Rect.Top = py;
  Rect.Left = px;
  Rect.Bottom = py + GrdSizeY;
  Rect.Right = px + GrdSizeX;

  TempType = ViewData[w-atWEEK_BASE][n-atLESSON_BASE].SubjectType;
  tempStr = ViewData[w-atWEEK_BASE][n-atLESSON_BASE].Subject;

  switch( TempType ){
    case CT_NORMAL     : tc = g_Config.Colors.CellBackground; break;
    case CT_FIXED      : tc = g_Config.Colors.FixedCell; break;
    case CT_SPECIAL    : tc = g_Config.Colors.SpecialLesson; break;
    case CT_MOVELESSON : tc = g_Config.Colors.MoveLesson; break;
    case CT_ETC        : tc = g_Config.Colors.GrayCell; break;
    default :            tc = clDkGray; break;
  }

  hNewBrush = CreateSolidBrush( tc );
  hOldBrush = SelectObject( hDC, hNewBrush );
  SetBkColor( hDC, tc );

  FillRect( hDC, &Rect, hNewBrush );

  if( tempStr != "" ) {
    StrPCopy( StrData, tempStr );
    DrawText( hDC, StrData, lstrlen(StrData), &Rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER );
  }

  SelectObject( hDC, hOldBrush );
  DeleteObject( hNewBrush );
}

//---------------------------------------------------------------------------
void __fastcall TfrmClass::lstClassClick(TObject *Sender)
{
  int w, n, i;
  PTeacherData tt;
  WORD year;
  TScheduleDataCell *sc;
  TTeacherSubject *tsbj;
  TSubject *sbj;

  year = GET_CLASS_YEAR(ViewClass);
  ViewClass = MAKE_CLASS_NO( year, lstClass->ItemIndex + 1 );

  pnlClassInfo->Caption = IntToStr(year) + " 학년 " + IntToStr(lstClass->ItemIndex + 1) + " 반";

  for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ) {
    for( n = atLESSON_1; n <= GetWeekLimit(year,w); n++ ) {
      ViewData[w-atWEEK_BASE][n-atLESSON_BASE].SubjectType = CT_NORMAL;
      ViewData[w-atWEEK_BASE][n-atLESSON_BASE].Subject = "";
      ViewData[w-atWEEK_BASE][n-atLESSON_BASE].TeacherName = "";

      for( i = 0; i < g_iTeacherCount; i++ ) {
        sc = GetScheduleDataCell( i, w, n );
        if( (sc->ClassType != CT_NORMAL) && (sc->ClassType != CT_FIXED) && (sc->ClassType != CT_MOVELESSON) ) continue; 

        if( IsEmbededClassNo( i, w, n, ViewClass ) ) {
          tt = GetTeacherData( i );
          ViewData[w-atWEEK_BASE][n-atLESSON_BASE].TeacherName = tt->TeacherName;

          switch( sc->ClassType ){
              case CT_NORMAL :
              case CT_FIXED :
                 tsbj = GetTeacherSubject( i, sc->ClassInfo );
                 sbj = FindSubjectByCode( tsbj->SubjectCode );
                 ViewData[w-atWEEK_BASE][n-atLESSON_BASE].SubjectType = sc->ClassType;
                 ViewData[w-atWEEK_BASE][n-atLESSON_BASE].Subject = sbj->ShortName;
                 break;
              case CT_MOVELESSON :
                 sbj = FindSubjectByCode( g_pMoveLesson[sc->ClassInfo].SubjectCode );
                 ViewData[w-atWEEK_BASE][n-atLESSON_BASE].SubjectType = sc->ClassType;
                 ViewData[w-atWEEK_BASE][n-atLESSON_BASE].Subject = sbj->ShortName;
                 break;
          }
          break;
        }
      }
    }
    for( n = GetWeekLimit(year,w)+1; n <= atLESSON_MAX; n++ ) {
      ViewData[w-atWEEK_BASE][n-atLESSON_BASE].SubjectType = CT_ETC;
      ViewData[w-atWEEK_BASE][n-atLESSON_BASE].Subject = "";
    }
  }

  for( i = 0; i < g_School.SPC_Count; i++ ) {
    if( (g_School.SPC[i].Years & SPC_CLASS_MASK_LST[year-atYEAR_BASE]) != 0 ) {
      ViewData[g_School.SPC[i].Pos[year-atYEAR_BASE].week-atWEEK_BASE][g_School.SPC[i].Pos[year-atYEAR_BASE].lesson-atLESSON_BASE].SubjectType = CT_SPECIAL;
      ViewData[g_School.SPC[i].Pos[year-atYEAR_BASE].week-atWEEK_BASE][g_School.SPC[i].Pos[year-atYEAR_BASE].lesson-atLESSON_BASE].Subject = g_School.SPC[i].Name;
    }
  }

  pntTeacher->Refresh();
}

void __fastcall TfrmClass::FormCreate(TObject *Sender)
{
    ViewClass = MAKE_CLASS_NO(atYEAR_1, atCLASS_1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmClass::pntTeacherPaint(TObject *Sender)
{
    TPaintBox *pnt;
    HDC dc;
    int i, j;
    TRect Rect;
    char StrData[256];
    HPEN hOldPen, hNewPen1, hNewPen2;
    HFONT hOldFont, hSFont;

    pnt = dynamic_cast<TPaintBox *>(Sender);
    dc = pnt->Canvas->Handle;

    /* 최좌상단 */
    Rect.Top = 1;
    Rect.Bottom = GrdStartY;
    Rect.Left = 1;
    Rect.Right = GrdStartX;
    DrawButtonLine( dc, Rect );
  
    /* 좌측(1~8교시) */
    Rect.Top = GrdStartY + 1 + 1;
    Rect.Bottom = GrdStartY + GrdSizeY + 1;
  
    hSFont = CreateFont( -13, 10, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "돋움체" );
    hOldFont = SelectObject( dc, hSFont );
    SetTextColor( dc, g_Config.Colors.CellText );
  
    for( i = atLESSON_1; i <= atLESSON_MAX; i++ ) {
      DrawButtonLine( dc, Rect );
      StrPCopy( StrData, IntToStr(i) );
      DrawButtonText( dc, Rect, StrData );
      Rect.Top = Rect.Top + GrdSizeY + 1;
      Rect.Bottom = Rect.Bottom + GrdSizeY + 1;
    }
  
    /* 상단 (요일) */
    Rect.Top = 1;
    Rect.Bottom = GrdStartY;
    Rect.Left = GrdStartX + 1 + 1;
    Rect.Right = GrdStartX + 1 + GrdSizeX;
  
    for( i = atWEEK_MON; i <= atWEEK_SAT; i++ ) {
      DrawButtonLine( dc, Rect );
      StrPCopy( StrData, GetWeekStr(i) );
      DrawButtonText( dc, Rect, StrData );
      Rect.Left = Rect.Left + GrdSizeX + 1;
      Rect.Right = Rect.Right + GrdSizeX + 1;
    }
    SelectObject( dc, hOldFont );
    DeleteObject( hSFont );

    /* 선 */
    hNewPen1 = CreatePen( PS_SOLID, 1, g_Config.Colors.GridLine );
    hNewPen2 = CreatePen( PS_SOLID, 1, g_Config.Colors.LunchTime );
    hOldPen = SelectObject( dc, hNewPen1 );

    for( i = atWEEK_MON; i <= atWEEK_SAT; i++ ) {
      MoveToEx( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 1, NULL );
      LineTo( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 2 + (GrdSizeY + 1) * 8 );
    }
    for( i = 0; i < 8-1; i++ ) {
      MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + i*(GrdSizeY + 1), NULL );
      LineTo( dc, GrdStartX + (GrdSizeX + 1) * atWEEK_SAT, GrdStartY + 1 + i*(GrdSizeY + 1) );
    }
    SelectObject( dc, hNewPen2 );
    MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + 4*(GrdSizeY + 1), NULL );
    LineTo( dc, GrdStartX + (GrdSizeX + 1) * atWEEK_SAT, GrdStartY + 1 + 4*(GrdSizeY + 1) );

    SelectObject( dc, hOldPen );
    DeleteObject( hNewPen1 );
    DeleteObject( hNewPen2 );

    /* 데이터 표시 */
    for( i = atWEEK_MON; i <= atWEEK_SAT; i++ )
      for( j = atLESSON_1; j <= atLESSON_MAX; j++ )
        DispClassData( dc, i, j );
}
//---------------------------------------------------------------------------

void __fastcall TfrmClass::pntTeacherMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  int xx, yy;
  String TempStr;

  if( (X > GrdStartX) && (Y > GrdStartY) ) {
    xx = (X - GrdStartX - 2) / (GrdSizeX + 1) + 1;
    yy = (Y - GrdStartY - 2) / (GrdSizeY + 1) + 1;

    if( (xx <= atWEEK_SAT) && (yy <= atLESSON_MAX) ) {
      TempStr = ViewData[xx-atWEEK_BASE][yy-atLESSON_BASE].TeacherName;
      TempStr = TempStr + " : " + ViewData[xx-atWEEK_BASE][yy-atLESSON_BASE].Subject;
      edtInfo->Text = TempStr;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmClass::btnYear1Click(TObject *Sender)
{
  int i;

  lstClass->Clear();

  for( i = atCLASS_1; i <= GetLimitClass(atYEAR_1); i++ )
    lstClass->Items->Add( IntToStr(i) );

  lstClass->ItemIndex = 0;
  ViewClass = MAKE_CLASS_NO(atYEAR_1, atCLASS_1);

  lstClassClick(lstClass);
}
//---------------------------------------------------------------------------

void __fastcall TfrmClass::btnYear2Click(TObject *Sender)
{
  int i;

  lstClass->Clear();

  for( i = atCLASS_1; i <= GetLimitClass(atYEAR_2); i++ )
    lstClass->Items->Add( IntToStr(i) );

  lstClass->ItemIndex = 0;
  ViewClass = MAKE_CLASS_NO(atYEAR_2, atCLASS_1);

  lstClassClick(lstClass);
}
//---------------------------------------------------------------------------

void __fastcall TfrmClass::btnYear3Click(TObject *Sender)
{
  int i;

  lstClass->Clear();

  for( i = atCLASS_1; i <= GetLimitClass(atYEAR_3); i++ )
    lstClass->Items->Add( IntToStr(i) );

  lstClass->ItemIndex = 0;
  ViewClass = MAKE_CLASS_NO(atYEAR_3, atCLASS_1);

  lstClassClick(lstClass);
}
//---------------------------------------------------------------------------

void __fastcall TfrmClass::btnCloseClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

