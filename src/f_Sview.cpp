//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_SVIEW.h"
#include "Global.h"
#include "GRP_Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//-- var, const, procedure ---------------------------------------------------
#define GrdSizeX 22
#define GrdSizeY 26
#define GrdStartX 16
#define GrdStartY 22

//---------------------------------------------------------------------------
__fastcall TfrmView::TfrmView(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/***********************************

************************************/
void TfrmView::RecalcInvalidInfo(void)
{
	int tp = SetCurSchedules( ViewPage );


int t, sn, w, n, n2, tc;
TScheduleDataCell *sc1, *sc2, *sc;
int cc;

memset( yyy, 0, 50*50*4 );

t = ViewTeacher;

for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
  for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
    sc1 = GetScheduleDataCell( t, w, n );
    if( ((sc1->ClassType == CT_NORMAL) || (sc1->ClassType == CT_FIXED)) ){
      int cnt = GetClassCount( t, w, n );
      for( int c = 0; c < cnt; c++ ){
        tc = GetClassNo( t, w, n, c );
        for( n2 = atLESSON_1; n2 <= atLESSON_MAX; n2++ ){
          if( n2 == n ) continue;
          sc2 = GetScheduleDataCell( t, w, n2 );
          if( ((sc2->ClassType == CT_NORMAL) || (sc2->ClassType == CT_FIXED)) &&
            IsEmbededClassNo( t, w, n2, tc) ){
            yyy[w][n] |= 0x01;
            yyy[w][n2] |= 0x01;
          }
        }
      }
    }
  }
}
for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
  cc = 0;
  for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
    sc = GetScheduleDataCell( t, w, n );
    if( ((sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED))
       && !IsEmptyClassNo( t, w, n ) ){
      cc++;
      if( cc == 3 ){
        yyy[w][n-1] |= 0x02;
        yyy[w][n-2] |= 0x02;
      }
      if( cc >= 3 ){
        yyy[w][n] |= 0x02;
      }
    } else
      cc = 0;
  }
}
for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
  cc = 0;
  for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
    sc = GetScheduleDataCell( t, w, n );
    if( ((sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED))
       && !IsEmptyClassNo( t, w, n ) ){
      cc++;
      if( cc >= 5 ){
        sc = GetScheduleDataCell( t, w, n2 );
        for( n2 = atLESSON_1; n2 <= atLESSON_MAX; n2++ ){
          if( ((sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED))
              && !IsEmptyClassNo( t, w, n2 ) ){
            yyy[w][n2] |= 0x04;
          }
        }
        break;
      }
    }
  }
}



    SetCurSchedules(tp);

}



/***********************************
  지정된 위치에 클래스 출력
************************************/
void TfrmView::DispClassData( HDC hDC, int w, int n )
{
  int i, cnt;
  int px, py;
  TRect Rect;
  int TempNum; //, TempNum2;
  BYTE TempType;
  String tempStr;
  char StrData[256];
  TColor tc;
  HBRUSH hOldBrush, hNewBrush;

  px = (w - 1) * (GrdSizeX + 1) + GrdStartX + 2;
  py = (n - 1) * (GrdSizeY + 1) + GrdStartY + 2;
  Rect.Top = py;
  Rect.Left = px;
  Rect.Bottom = py + GrdSizeY;
  Rect.Right = px + GrdSizeX;

/*
  cnt = 0;
  for( i = 0; i < MAX_MULTILESSON_CLASS; i++ ){
//    if( (*ViewData)[w-atWEEK_BASE][n-atLESSON_BASE].ClassNo[i] != 0 ) cnt++;
  	if( GetClassNo(ViewTeacher, w, n, i) ) cnt++;
  }
*/
  cnt = GetClassCount( ViewTeacher, w, n );
//  TempType = (*ViewData)[w-atWEEK_BASE][n-atLESSON_BASE].ClassType;
  TempType = GetClassType(ViewTeacher, w, n);

  // 이동하는 것은 붉은 색으로... 
  if( ((w == StartPos.week) && (n == StartPos.lesson)) ||
     ((w == EndPos.week) && (n == EndPos.lesson)) )
    TempType = CT_FOCUS;

  switch( TempType ){
    case CT_NORMAL     : tc = g_Config.Colors.CellBackground; break;
    case CT_FIXED      : tc = g_Config.Colors.FixedCell; break;
    case CT_SPECIAL    : tc = g_Config.Colors.SpecialLesson; break;
    case CT_MOVELESSON : tc = g_Config.Colors.MoveLesson; break;
    case CT_ETC        : tc = g_Config.Colors.GrayCell; break;
    case CT_FOCUS      : tc = g_Config.Colors.FocusCell; break;
    case CT_TEMP       : tc = g_Config.Colors.CellBackground; break; // 이동 중 임시..
    default :            tc = clDkGray; break;
  }

  hNewBrush = CreateSolidBrush( tc );
//  hOldBrush = SelectObject( hDC, hNewBrush );
  SetBkColor( hDC, tc );

  FillRect( hDC, &Rect, hNewBrush );

  switch( TempType ){
    case CT_NORMAL :
    case CT_FIXED :
    case CT_FOCUS :
		for( i = 0; i < cnt; i++ ){
		  TempNum = GetClassNo( ViewTeacher, w, n, i );
		  if( tempStr != "" ) tempStr = tempStr + "\n";
		  tempStr = tempStr + Format( "%d-%d", ARRAYOFCONST((GET_CLASS_YEAR(TempNum), GET_CLASS_CLASS(TempNum))) );
		}
		if( tempStr != "" )
		  DrawRectText( hDC, Rect, tempStr.c_str() );
      break;

    case CT_MOVELESSON :
      TempNum = GetClassInfo(ViewTeacher, w, n);
      DrawRectText( hDC, Rect, g_pMoveLesson[TempNum].ShortName );
      break;

    case CT_SPECIAL :
  	  DrawRectText( hDC, Rect, g_School.SPC[TempNum].Name );
      break;
  }

//  SelectObject( hDC, hOldBrush );
  DeleteObject( hNewBrush );


HPEN hNewPen, hOldPen;
hOldBrush = SelectObject( hDC, GetStockObject(NULL_BRUSH) );
if( yyy[w][n] & 0x01 ){
  hNewPen = CreatePen( PS_SOLID, 1, clRed );
  hOldPen = SelectObject( hDC, hNewPen );
  Ellipse( hDC, Rect.Left+1, Rect.Top+1, Rect.Right-1, Rect.Bottom-1 );
  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
}
if( yyy[w][n] & 0x02 ){
  hNewPen = CreatePen( PS_SOLID, 1, clGreen );
  hOldPen = SelectObject( hDC, hNewPen );
  RoundRect( hDC, Rect.Left+1, Rect.Top+1, Rect.Right-1, Rect.Bottom-1, 5, 5 );
  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
}
if( yyy[w][n] & 0x04 ){
  hNewPen = CreatePen( PS_SOLID, 1, clBlue );
  hOldPen = SelectObject( hDC, hNewPen );
  Rectangle( hDC, Rect.Left, Rect.Top, Rect.Right, Rect.Bottom );
  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
}
SelectObject( hDC, hOldBrush );


}


//---------------------------------------------------------------------------
void __fastcall TfrmView::pntTeacherPaint(TObject *Sender)
{
    TPaintBox *pnt;
    HDC dc;
    int i, j, xpos;
    TRect Rect;
    char StrData[256];
    HPEN hOldPen, hNewPen1, hNewPen2;
    HFONT hOldFont, hSFont;

    pnt = dynamic_cast<TPaintBox *>(Sender);
    dc = pnt->Canvas->Handle;

    xpos = pntTeacher->Width / GrdSizeX;
    if( pntTeacher->Width % GrdSizeX != 0 ) xpos--;

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

    for( i = atWEEK_MON; i <= atWEEK_MAX-1; i++ ) {
      MoveToEx( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 1, NULL );
      LineTo( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 2 + (GrdSizeY + 1) * 8 );
    }
    for( i = atLESSON_1; i <= atLESSON_MAX-1; i++ ) {
      MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + i*(GrdSizeY + 1), NULL );
      LineTo( dc, GrdStartX + (GrdSizeX + 1) * atWEEK_SAT, GrdStartY + 1 + i*(GrdSizeY + 1) );
    }
    SelectObject( dc, hNewPen2 );
    MoveToEx( dc, GrdStartX + 1, GrdStartY + 1 + g_School.LunchTime[0]*(GrdSizeY + 1), NULL );
    LineTo( dc, GrdStartX + (GrdSizeX + 1) * atWEEK_SAT, GrdStartY + 1 + g_School.LunchTime[0]*(GrdSizeY + 1) );

    SelectObject( dc, hOldPen );
    DeleteObject( hNewPen1 );
    DeleteObject( hNewPen2 );

    /* 데이터 표시 */
	int tp = SetCurSchedules( ViewPage );
    for( i = atWEEK_MON; i <= atWEEK_MAX; i++ )
      for( j = atLESSON_1; j <= atLESSON_MAX; j++ )
        DispClassData( dc, i, j );
    SetCurSchedules(tp);

    // 움직이는 방향으로 화살표 그리는 것...
    DrawArrowLine( dc, GrdStartX+2 + StartPos.week * GrdSizeX-(GrdSizeX / 2),
                       GrdStartY+2 + StartPos.lesson * GrdSizeY-(GrdSizeY / 2),
                       GrdStartX+2 + EndPos.week * GrdSizeX-(GrdSizeX / 2),
                       GrdStartY+2 + EndPos.lesson * GrdSizeY-(GrdSizeY / 2) );

}

//---------------------------------------------------------------------------
void __fastcall TfrmView::FormShow(TObject *Sender)
{
/*
  ts: PScheduleData;
  tt: PTeacherData;

  tt = PTeachers;
  inc( tt, ViewTeacher - 1 );
  pnlTeacher.Caption = tt->TeacherName;

  ts = PSchedules2;
  inc( ts, ViewTeacher - 1 );
  ViewData = ts^;
*/
}

//---------------------------------------------------------------------------
void __fastcall TfrmView::pntChange1Paint(TObject *Sender)
{
  TRect Rect;
  char StrData[256];

  Rect = pntChange1->Canvas->ClipRect;
  Rect.Right--;
  Rect.Bottom--;
  DrawButtonLine( pntChange1->Canvas->Handle, Rect );

  Rect.Left++;
  Rect.Top += 10;
  Rect.Right--;
  Rect.Bottom--;
  StrPCopy( StrData, Change1 );
  DrawText( pntChange1->Canvas->Handle, StrData, lstrlen(StrData), &Rect, DT_CENTER );
}

//---------------------------------------------------------------------------
void __fastcall TfrmView::pntChange2Paint(TObject *Sender)
{
  TRect Rect;
  char StrData[256];

  Rect = pntChange2->Canvas->ClipRect;
  Rect.Right--;
  Rect.Bottom--;
  DrawButtonLine( pntChange2->Canvas->Handle, Rect );

  Rect.Left++;
  Rect.Top += 10;
  Rect.Right--;
  Rect.Bottom--;
  StrPCopy( StrData, Change2 );
  DrawText( pntChange2->Canvas->Handle, StrData, lstrlen(StrData), &Rect, DT_CENTER );
}


