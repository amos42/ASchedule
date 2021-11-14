//----------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "GRP_Util.h"
//----------------------------------------------------------------------------

#include <math.h>
#define PI ((double)3.1415926537)

#define Trunc(a) a
/************************
  화살표 모양을 그려준다.
*************************/
void DrawArrowLine( HDC hDC, int sx, int sy, int ex, int ey )
{
    HPEN hOldPen, hYellowPen;
    double v, v2;
    int nx, ny;

    hYellowPen = CreatePen( PS_SOLID, 1, RGB(0,255,0) );
    hOldPen = SelectObject( hDC, hYellowPen );

    v = atan2( ey-sy, ex-sx ) / PI * 180;

/*
    v2 = (v) / 180 * PI;
    sx += cos( v2 ) * 10;
    sy += + sin( v2 ) * 10;

    v2 = (-v) / 180 * PI;
    ex += + cos( v2 ) * 10;
    ey += + sin( v2 ) * 10;
*/

    MoveToEx( hDC, sx, sy, NULL );
    LineTo( hDC, ex, ey );

    v2 = (v-180-30) / 180 * PI;

    nx = ex + cos( v2 ) * 10;
    ny = ey + sin( v2 ) * 10;

    MoveToEx( hDC, ex, ey, NULL );
    LineTo( hDC, nx, ny );

    v2 = (v-180+30) / 180 * PI;

    nx = ex + cos( v2 ) * 10;
    ny = ey + sin( v2 ) * 10;

    MoveToEx( hDC, ex, ey, NULL );
    LineTo( hDC, nx, ny );

    SelectObject( hDC, hOldPen );
    DeleteObject( hYellowPen );
}


/************************
  버튼 모양을 그려준다.
*************************/
void DrawButtonLine( HDC hDC, TRect &Rect )
{
    HBRUSH brs;
    TPoint Points[3];
    HPEN hOldPen, hGrayPen, hWhitePen;

    brs = CreateSolidBrush( GetSysColor(COLOR_BTNFACE) );
    FillRect( hDC, &Rect, brs );
    DeleteObject( brs );

    Points[0].x = Rect.Right;
    Points[0].y = Rect.Top;
    Points[1].x = Rect.Right;
    Points[1].y = Rect.Bottom;
    Points[2].x = Rect.Left;
    Points[2].y = Rect.Bottom;

    hGrayPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) );
    hOldPen = SelectObject( hDC, hGrayPen );
    Polyline( hDC, Points, 3 );
    SelectObject( hDC, hOldPen );
    DeleteObject( hGrayPen );

    Points[1].x = Rect.Left;
    Points[1].y = Rect.Top;
  
    hWhitePen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) );
    hOldPen = SelectObject( hDC, hWhitePen );
    Polyline( hDC, Points, 3 );
    SelectObject( hDC, hOldPen );
    DeleteObject( hWhitePen );
}


/************************
  버튼 안에 글을 쓴다.(세로로)
*************************/
void DrawButtonText( HDC hDC, TRect &Rect, char *StrData )
{
    int ChrCount, l;
    char *nextptr, *ptr;
    int step;
    TRect dRect;
    TSize ts;
    int Rop;

    if( StrData[0] == '\0' ) return;

    GetTextExtentPoint32( hDC, "주", 2, &ts );

    /* 글자의 갯수를 알아낸다. */
    ChrCount = 0;
    ptr = StrData;
    while( *ptr != '\0' ) {
      ChrCount++;
      ptr = AnsiNext(ptr);
    }

    dRect.Top = Rect.Top + 2;
    dRect.Left = Rect.Left + 2;
    dRect.Right = Rect.Right - 2;
  
    /* 글자 사이의 간격을 정한다. */
    if( ChrCount > 1 ){
      step = (Rect.Bottom - Rect.Top - ts.cy - 4) / (ChrCount - 1);
      dRect.Bottom = Rect.Top + 2 + ts.cy;
      Rop = DT_CENTER | DT_VCENTER;
    } else {
      dRect.Bottom = Rect.Bottom - 2;
      Rop = DT_CENTER | DT_SINGLELINE | DT_VCENTER;
    }
  
    /* 글자를 찍는다. */
    SetBkColor( hDC, GetSysColor(COLOR_BTNFACE) );
    ptr = StrData;
    while( *ptr != '\0' ) {
      nextptr = AnsiNext(ptr);
      DrawText( hDC, ptr, nextptr - ptr, &dRect, Rop );
      ptr = nextptr;
      dRect.Top = dRect.Top + step;
      dRect.Bottom = dRect.Bottom + step;
    }
}

/************************
  사각형 안에 글을 쓴다.
*************************/
void DrawRectText( HDC hDC, TRect &Rect, char *StrData )
{
    int i, LineCount, l;
	char *str_idx[10] = {NULL,};// 10라인이 한계
	int str_len[10] = {0,};// 10라인이 한계
    char *nextptr, *ptr;
    int step;
    TRect dRect;
    TSize ts;
    int Rop;

    if( StrData[0] == '\0' ) return;

    GetTextExtentPoint32( hDC, "주", 2, &ts );

    /* 글자의 라인수를 알아낸다. */
    LineCount = 1;
    ptr = StrData;
	str_idx[0] = ptr;
	str_len[0] = 0;
    while( *ptr != '\0' ) {
	  if( *ptr == '\n' ){
	    str_idx[LineCount] = AnsiNext(ptr);
	    str_len[LineCount-1] = ptr - str_idx[LineCount-1];
		LineCount++;
	  }
      ptr = AnsiNext(ptr);
    }
    if( str_idx[LineCount-1] != ptr ){
	    str_len[LineCount-1] = ptr - str_idx[LineCount-1];
    }

    dRect.Left = Rect.Left + 1;
    dRect.Right = Rect.Right - 1;

    /* 글자 사이의 간격을 정한다. */
    if( LineCount > 1 ){
      step = (Rect.Bottom - Rect.Top - (1*2+1) - ts.cy * LineCount) / (LineCount + 1);
      dRect.Top = Rect.Top + 1 + step;
      dRect.Bottom = dRect.Top + ts.cy;
      Rop = DT_CENTER;
    } else {
      dRect.Top = Rect.Top + 1;
      dRect.Bottom = Rect.Bottom - 1;
      step = 0;
      Rop = DT_CENTER | DT_SINGLELINE | DT_VCENTER;
    }

    SetBkMode( hDC, TRANSPARENT	);

    /* 글자를 찍는다. */
	for( i = 0; i < LineCount; i++ ){
      DrawText( hDC, str_idx[i], str_len[i], &dRect, Rop );
      dRect.Top = dRect.Top + step + ts.cy;
      dRect.Bottom = dRect.Bottom + step + ts.cy;
    }
}

