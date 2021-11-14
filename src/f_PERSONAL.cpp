//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "f_PERSONAL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Global.h"
#include "A_Util.h"
#include "GRP_Util.h"
#include "f_Change.h"
#include "f_SClass.h"

//---------------------------------------------------------------------------
__fastcall TfrmPersonal::TfrmPersonal(TComponent* Owner)
        : TForm(Owner)
{
    iCurWork = 0;
    DispTeacher = -1;
    mState = FALSE;
    mStartW = mStartN = 0;
}
//---------------------------------------------------------------------------

#define GrdSizeX 26
#define GrdSizeY 26 /// 32
#define GrdStartX 16
#define GrdStartY 22


TfrmPersonal *frmPersonal;

static WORD  curMouseW, curMouseN;

static unsigned char pattern_img1[16] = {
  0x77, 0x00,
  0xFF, 0x00,
  0xDD, 0x00,
  0xFF, 0x00,
  0x77, 0x00,
  0xFF, 0x00,
  0xDD, 0x00,
  0xFF, 0x00
};
static unsigned char pattern_img2[16] = {
  0x55, 0x00,
  0xAA, 0x00,
  0x55, 0x00,
  0xAA, 0x00,
  0x55, 0x00,
  0xAA, 0x00,
  0x55, 0x00,
  0xAA, 0x00
};
static HBITMAP hPatternBrush1, hPatternBrush2;



/***********************************
  지정된 위치에 클래스 출력
************************************/
void DispClassData( HDC hDC, int t, int w, int n )
{
  int i, cnt;
  int px, py;
  TRect Rect;
  int TempNum; //, TempNum2, TempNum3;
  BYTE TempType;
  String TempStr;
  TColor tc;
  HBRUSH hOldBrush, hNewBrush;
  HPEN hOldPen, hNewPen;

  px = (w - atWEEK_BASE) * (GrdSizeX + 1) + GrdStartX + 2;
  py = (n - atLESSON_BASE) * (GrdSizeY + 1) + GrdStartY + 2;
  Rect.Top = py;
  Rect.Left = px;
  Rect.Bottom = py + GrdSizeY;
  Rect.Right = px + GrdSizeX;

  TempNum = 0;
  TempType = GetClassType( t, w, n );

  switch( TempType ){
    case CT_NORMAL     : tc = g_Config.Colors.CellBackground; break;
    case CT_FIXED      : tc = g_Config.Colors.FixedCell; break;
    case CT_SPECIAL    : tc = g_Config.Colors.SpecialLesson; break;
    case CT_MOVELESSON : tc = g_Config.Colors.MoveLesson; break;
    case CT_ETC        : tc = g_Config.Colors.GrayCell; break;
    default :            tc = clDkGray; break;
  }

if( frmPersonal->xxx[w][n] == 0 ){
  hNewBrush = CreateSolidBrush( tc );
} else if( frmPersonal->xxx[w][n] == 1 ){
  hNewBrush = CreatePatternBrush( hPatternBrush1 );
} else if( frmPersonal->xxx[w][n] == 2 ){
  hNewBrush = CreatePatternBrush( hPatternBrush2 );
} else if( frmPersonal->xxx[w][n] == 3 ){
  hNewBrush = CreateSolidBrush( clAqua );
}

//  hNewBrush = CreateSolidBrush( tc );
//  hOldBrush = SelectObject( hDC, hNewBrush );
//  hNewPen = CreatePen( PS_SOLID, 1, tc );
//  hOldPen = SelectObject( hDC, hNewPen );
  SetBkColor( hDC, tc );

  FillRect( hDC, &Rect, hNewBrush );

  switch( TempType ){
    case CT_NORMAL:
    case CT_FIXED:
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


hOldBrush = SelectObject( hDC, GetStockObject(NULL_BRUSH) );
if( frmPersonal->yyy[w][n] & 0x01 ){
  hNewPen = CreatePen( PS_SOLID, 1, clRed );
  hOldPen = SelectObject( hDC, hNewPen );
  Ellipse( hDC, Rect.Left+1, Rect.Top+1, Rect.Right-1, Rect.Bottom-1 );
  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
}
if( frmPersonal->yyy[w][n] & 0x02 ){
  hNewPen = CreatePen( PS_SOLID, 1, clGreen );
  hOldPen = SelectObject( hDC, hNewPen );
  RoundRect( hDC, Rect.Left+1, Rect.Top+1, Rect.Right-1, Rect.Bottom-1, 5, 5 );
  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
}
if( frmPersonal->yyy[w][n] & 0x04 ){
  hNewPen = CreatePen( PS_SOLID, 1, clBlue );
  hOldPen = SelectObject( hDC, hNewPen );
  Rectangle( hDC, Rect.Left, Rect.Top, Rect.Right, Rect.Bottom );
  SelectObject( hDC, hOldPen );
  DeleteObject( hNewPen );
}
SelectObject( hDC, hOldBrush );

}


/***********************************

************************************/
void TfrmPersonal::SetTeacherNo( int idx )
{
    if( idx <= g_iTeacherCount ){
      lstTeacher->ItemIndex = idx;
      lstTeacherClick(lstTeacher);
    }
}


/***********************************

************************************/
void TfrmPersonal::RefreshTeachers(void)
{
    int i;
    PTeacherData tt;

    // 교사 데이터
    lstTeacher->Items->BeginUpdate();
    lstTeacher->Items->Clear();
    tt = (PTeacherData)g_pTeachers;
    for( i = 0; i < g_iTeacherCount; i++ ){
      lstTeacher->Items->Add( tt->TeacherName );
      tt++;
    }
    lstTeacher->Items->EndUpdate();
}

/***********************************

************************************/
void TfrmPersonal::RecalcInvalidInfo(void)
{


int t, sn, w, n, n2, tc;
TScheduleDataCell *sc1, *sc2, *sc;
int cc;

t = DispTeacher;

memset( yyy, 0, 50*50*4 );

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




}


//---------------------------------------------------------------------------

void __fastcall TfrmPersonal::FormCreate(TObject *Sender)
{
    hPatternBrush1 = CreateBitmap( 8, 8, 1, 1, pattern_img1 );
    hPatternBrush2 = CreateBitmap( 8, 8, 1, 1, pattern_img2 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPersonal::FormDestroy(TObject *Sender)
{
    DeleteObject( hPatternBrush1 );
    hPatternBrush1 = NULL;
    DeleteObject( hPatternBrush2 );
    hPatternBrush2 = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPersonal::FormShow(TObject *Sender)
{
    mState = FALSE;
    pntTeacher->Cursor = crDefault;

memset( xxx, 0, 50*50*4 );
memset( yyy, 0, 50*50*4 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPersonal::pntTeacherPaint(TObject *Sender)
{
    TPaintBox *pnt;
    HDC dc;
    int i, j;
    TRect Rect;
    HPEN hOldPen, hNewPen1, hNewPen2;
    HFONT hOldFont, hSFont;

    if( DispTeacher == -1 )  return;

    pnt = dynamic_cast<TPaintBox *>(Sender);
    dc = pnt->Canvas->Handle;

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
    for( i = atLESSON_1; i <= atLESSON_MAX; i++ ){
      DrawButtonLine( dc, Rect );
      DrawButtonText( dc, Rect, IntToStr(i).c_str() );
      Rect.Top = Rect.Top + GrdSizeY + 1;
      Rect.Bottom = Rect.Bottom + GrdSizeY + 1;
    }

    /* 상단 (요일) */
    Rect.Top = 1;
    Rect.Bottom = GrdStartY;
    Rect.Left = GrdStartX + 1 + 1;
    Rect.Right = GrdStartX + 1 + GrdSizeX;
    for( i = atWEEK_MON; i <= atWEEK_MAX; i++ ){
      DrawButtonLine( dc, Rect );
      DrawButtonText( dc, Rect, GetWeekStr(i).c_str() );
      Rect.Left = Rect.Left + GrdSizeX + 1;
      Rect.Right = Rect.Right + GrdSizeX + 1;
    }

    SelectObject( dc, hOldFont );
    DeleteObject( hSFont );

    /* 선 */
    hNewPen1 = CreatePen( PS_SOLID, 1, g_Config.Colors.GridLine );
    hNewPen2 = CreatePen( PS_SOLID, 1, g_Config.Colors.LunchTime );
    hOldPen = SelectObject( dc, hNewPen1 );

    for( i = atWEEK_MON; i <= atWEEK_MAX-1; i++ ){
      MoveToEx( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 1, NULL );
      LineTo( dc, GrdStartX + 1 + i*(GrdSizeX + 1), GrdStartY + 2 + (GrdSizeY + 1) * 8 );
    }
    for( i = atLESSON_1; i <= atLESSON_MAX-1; i++ ){
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
    for( i = atWEEK_MON; i <= atWEEK_MAX; i++ )
      for( j = atLESSON_1; j <= atLESSON_MAX; j++ )
        DispClassData( dc, DispTeacher, i, j );
}

void __fastcall TfrmPersonal::mnuCloseClick(TObject *Sender)
{
    Close();
}

void __fastcall TfrmPersonal::pntTeacherMouseDown(TObject* Sender,
        TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TPaintBox *pnt;
  int xx, yy;
  int t2, t3;
  BYTE ct;
  PTeacherData tt;
  TTeacherSubject *sbj;
  WORD info;
  String tempStr;

  pnt = dynamic_cast<TPaintBox *>(Sender);

  if( Button == mbLeft ){
    if( (X > GrdStartX) && (Y > GrdStartY) ){
      xx = (X - GrdStartX - 2) / (GrdSizeX + 1) + 1;
      yy = (Y - GrdStartY - 2) / (GrdSizeY + 1) + 1;

      if( (xx <= atWEEK_SAT) && (yy <= atLESSON_MAX) ){
        tt = GetTeacherData( DispTeacher );
		info = GetClassInfo( DispTeacher, xx, yy );
        sbj = GetTeacherSubject( DispTeacher, info );

        switch( iCurWork ){
          // 정보
          case 0: if( (GetClassType( DispTeacher, xx, yy ) != CT_SPECIAL) &&
                !IsEmptyClassNo( DispTeacher, xx, yy ) ){
               tempStr = (String)tt->TeacherName + GetTeacherSubjectString(DispTeacher, info);
               edtInfo->Text = tempStr;
             } else {
               edtInfo->Text = "";
             }
             break;

          // 옮기기
          case 1: if( (GetClassType(DispTeacher, xx, yy) == CT_NORMAL) ){
               if( !mState ){
                 if( !IsEmptyClassNo(DispTeacher, xx, yy) ){
                   mStartW = xx;
                   mStartN = yy;
//                   tempStr = (String)sbj->Name + " : " + GetWeekStr(xx) + "요일 " + IntToStr(yy) + "교시 => ";
                   edtInfo->Text = tempStr;
                   pntTeacher->Cursor = crDrag;

for( int w = 1; w <= 6; w++ )
  for( int n = 1; n <= 8; n++ ){
    int cc;
    if( CanItChange( DispTeacher, mStartW, mStartN, w, n, &cc ) ){
      xxx[w][n] = ( cc > g_Config.MaxChangeCount/2 )? 1 : 0;
    } else {
      xxx[w][n] = 2;
    }
  }
xxx[mStartW][mStartN] = 3;
pntTeacher->Cursor = crNo;
pntTeacher->Refresh();

                   mState = TRUE;
                 }
               } else {
                 if( (yy != mStartN) || (xx != mStartW) ){
                   if( CanItChange( DispTeacher, mStartW, mStartN, xx, yy, NULL ) ){
                     frmChange->ChangeT = DispTeacher;
                     frmChange->ChangeSW = mStartW;
                     frmChange->ChangeSN = mStartN;
                     frmChange->ChangeEW = xx;
                     frmChange->ChangeEN = yy;
                     frmChange->ChangeType = 1;
                     frmChange->ShowModal();
                     pntTeacher->Refresh();
                   }

                   edtInfo->Text = edtInfo->Text + GetWeekStr(xx) + "요일 " + IntToStr(yy) + "교시";

                   mState = FALSE;
                   pntTeacher->Cursor = crDefault;
RecalcInvalidInfo();
memset( xxx, 0, 50*50*4 );
pntTeacher->Refresh();
                 }
               }
             }
             break;

          // 고정/해제
          case 2: if( GetClassType( DispTeacher, xx, yy ) == CT_NORMAL ){
               SetClassType( DispTeacher, xx, yy, CT_FIXED );
               DispClassData( pntTeacher->Canvas->Handle, DispTeacher, xx, yy );
             } else if( GetClassType( DispTeacher, xx, yy ) == CT_FIXED ){
               SetClassType( DispTeacher, xx, yy, CT_NORMAL );
               DispClassData( pntTeacher->Canvas->Handle, DispTeacher, xx, yy );
             }
             break;

          // 힙반처리
          case 3: if( (GetClassType(DispTeacher, xx, yy) == CT_NORMAL) ){
//                IsCanAddClassNo(DispTeacher, xx, yy) ){
               if( !mState ){
			   	   int cnt = GetClassCount(DispTeacher, xx, yy);
				   if( ( cnt > 0) && (cnt < MAX_MULTILESSON_CLASS) ){
                 	 mStartW = xx;
                 	 mStartN = yy;
//                 	 tempStr = (String)sbj->Name + " : " + GetWeekStr(xx) + "요일 " + IntToStr(yy) + "교시 + ";
                     edtInfo->Text = tempStr;
                     pntTeacher->Cursor = crDrag;

for( int w = 1; w <= 6; w++ )
  for( int n = 1; n <= 8; n++ ){
    int cc;
    if( CanItMulti( DispTeacher, mStartW, mStartN, w, n, &cc ) ){
      xxx[w][n] = ( cc > g_Config.MaxChangeCount/2 )? 1 : 0;
    } else {
      xxx[w][n] = 2;
    }
  }
xxx[mStartW][mStartN] = 3;
pntTeacher->Cursor = crNo;
pntTeacher->Refresh();
                     mState = TRUE;
				  }
               } else {
                 if( (yy != mStartN) || (xx != mStartW) ){
                   if( CanItMulti( DispTeacher, mStartW, mStartN, xx, yy, NULL ) ){
                     frmChange->ChangeT = DispTeacher;
                     frmChange->ChangeSW = mStartW;
                     frmChange->ChangeSN = mStartN;
                     frmChange->ChangeEW = xx;
                     frmChange->ChangeEN = yy;
                     frmChange->ChangeType = 2;
                     frmChange->ShowModal();
                     pntTeacher->Refresh();
                   }

                   edtInfo->Text = edtInfo->Text + GetWeekStr(xx) + "요일 " + IntToStr(yy) + "교시";

                   mState = FALSE;
                   pntTeacher->Cursor = crDefault;
RecalcInvalidInfo();
memset( xxx, 0, 50*50*4 );
pntTeacher->Refresh();
                 }
               }
             }
             break;

          // 힙반해제
          case 4: if( (GetClassType(DispTeacher, xx, yy) == CT_NORMAL) ){
               if( !mState ){
                 if( GetClassCount(DispTeacher, xx, yy) >= 2 ){
                   mStartW = xx;
                   mStartN = yy;
//                   tempStr = (String)sbj->Name + " : " + GetWeekStr(xx) + "요일 " + IntToStr(yy) + "교시 => ";
                   edtInfo->Text = tempStr;
                   pntTeacher->Cursor = crDrag;
for( int w = 1; w <= 6; w++ )
  for( int n = 1; n <= 8; n++ ){
    int cc;
    if( CanItRelease( DispTeacher, mStartW, mStartN, w, n, &cc ) ){
      xxx[w][n] = ( cc > g_Config.MaxChangeCount/2 )? 1 : 0;
    } else {
      xxx[w][n] = 2;
    }
  }
xxx[mStartW][mStartN] = 3;
pntTeacher->Cursor = crNo;
pntTeacher->Refresh();
                   mState = TRUE;
                 }
               } else {
                 if( (yy != mStartN) || (xx != mStartW) ){
                   if( CanItRelease( DispTeacher, mStartW, mStartN, xx, yy, NULL ) ){
                     frmChange->ChangeT = DispTeacher;
                     frmChange->ChangeSW = mStartW;
                     frmChange->ChangeSN = mStartN;
                     frmChange->ChangeEW = xx;
                     frmChange->ChangeEN = yy;
                     frmChange->ChangeType = 3;
                     frmChange->ShowModal();
                     pntTeacher->Refresh();
                   }

                   edtInfo->Text = edtInfo->Text + GetWeekStr(g_curWeek) + "요일 " + IntToStr(yy) + "교시";

                   mState = FALSE;
                   pntTeacher->Cursor = crDefault;
RecalcInvalidInfo();
memset( xxx, 0, 50*50*4 );
pntTeacher->Refresh();
                 }
               }
             }
             break;
        }
      }
    }
  } else {
    if( mState ){
      pntTeacher->Cursor = crDefault;
memset( xxx, 0, 50*50*4 );
pntTeacher->Refresh();
      mState = FALSE;
    } else {
      TPoint p;
      if( (X > GrdStartX) && (Y > GrdStartY) ){
        p.x = X; p.y = Y;
        p = pnt->ClientToScreen( p );
        pnt->PopupMenu->Popup( p.x, p.y );
      }
    }
  }
}


void __fastcall TfrmPersonal::lstTeacherClick(TObject *Sender)
{
  DispTeacher = lstTeacher->ItemIndex;
  mState = FALSE;

  RecalcInvalidInfo();

  pntTeacher->Refresh();
}


void __fastcall TfrmPersonal::pntTeacherMouseMove(TObject* Sender,
        TShiftState Shift, int X, int Y)
{
  int ww, nn;

  if( mState ){
    if( (X > GrdStartX) && (Y > GrdStartY) ){
      ww = (X - GrdStartX - 2) / (GrdSizeX + 1) + 1;
      nn = (Y - GrdStartY - 2) / (GrdSizeY + 1) + 1;

      if( (ww != curMouseW) || (nn != curMouseN) ){
        if( (ww <= atWEEK_MAX) && (nn <= atLESSON_MAX) ){
          switch( iCurWork ){
/*
            case 1 : if( CanItChange( DispTeacher, mStartW, mStartN, ww, nn ) )
                  pntTeacher->Cursor = crMultiDrag;
                else
                  pntTeacher->Cursor = crDrag;
                break;
            case 3 : if( CanItMulti( DispTeacher, mStartW, mStartN, ww, nn ) )
                  pntTeacher->Cursor = crMultiDrag;
                else
                  pntTeacher->Cursor = crDrag;
                break;
            case 4 : if( CanItRelease( DispTeacher, mStartW, mStartN, ww, nn ) )
                  pntTeacher->Cursor = crMultiDrag;
                else
                  pntTeacher->Cursor = crDrag;
                break;
*/
            case 1 : 
            case 3 :
            case 4 :
                if( xxx[ww][nn] == 0 )
                  pntTeacher->Cursor = crDrag;
                else if( xxx[ww][nn] == 1 )
                  pntTeacher->Cursor = crMultiDrag;
                else
                  pntTeacher->Cursor = crNo;
                break;
          }
        } else
          pntTeacher->Cursor = crNoDrop;

        curMouseW = ww;
        curMouseN = nn;
      }
    } else
      pntTeacher->Cursor = crNoDrop;
  }
}

void __fastcall TfrmPersonal::mnuFind4and5Click(TObject *Sender)
{
  int t, sn, w;
  TScheduleDataCell *sc1, *sc2;

  if( chkFindFirst->Checked ){
    sn = 0;
  } else {
    sn = lstTeacher->ItemIndex + 1;
  }

  for( t = sn; t < g_iTeacherCount; t++ ){
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
      sc1 = GetScheduleDataCell( t, w, g_School.LunchTime[0] );
      sc2 = GetScheduleDataCell( t, w, g_School.LunchTime[0]+1 );

      if( ((sc1->ClassType == CT_NORMAL) || (sc1->ClassType == CT_FIXED))
         && !IsEmptyClassNo( t, w, g_School.LunchTime[0] ) 
         && ((sc2->ClassType == CT_NORMAL) || (sc2->ClassType == CT_FIXED))
         && !IsEmptyClassNo( t, w, g_School.LunchTime[0]+1 )
        ){
        lstTeacher->ItemIndex = t;
        lstTeacherClick(lstTeacher);
        goto ExitSub;
      }
    }
  }

  MessageDlg2( "점심시간 전후로 인접한 교사는 없습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );

ExitSub:
}

void __fastcall TfrmPersonal::mnuFind3ContClick(TObject *Sender)
{
  int t, sn, w, n, cc;
  TScheduleDataCell *sc;

  if( chkFindFirst->Checked )
    sn = 0;
  else {
    sn = lstTeacher->ItemIndex + 1;
  }

  for( t = sn; t < g_iTeacherCount; t++ ){
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
      cc = 0;
      for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
        sc = GetScheduleDataCell( t, w, n );
        if( ((sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED)) 
           && !IsEmptyClassNo( t, w, n ) ){
          cc++;
          if( cc >= 3 ){
            lstTeacher->ItemIndex = t;
            lstTeacherClick(lstTeacher);
            goto ExitSub;
          }
        } else
          cc = 0;
      }
    }
  }

  MessageDlg2( "3교시가 연속된 교사는 없습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );

ExitSub:
}

void __fastcall TfrmPersonal::mnuFindMultiClick(TObject *Sender)
{
  int t, sn, w, n, n2, tc;
  TScheduleDataCell *sc1, *sc2;

  if( chkFindFirst->Checked ){
    sn = 0;
  } else {
    sn = lstTeacher->ItemIndex + 1;
  }

  for( t = sn; t <= g_iTeacherCount; t++ ){
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
                lstTeacher->ItemIndex = t;
                lstTeacherClick(lstTeacher);
                return;
              }
            }
          }
        }
      }
    }
  }

  MessageDlg2( "같은 반이 중복된 교사는 없습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
}

void __fastcall TfrmPersonal::mnuFindOver5Click(TObject *Sender)
{
  int t, sn, w, n, cc;
  TScheduleDataCell *sc;

  if( chkFindFirst->Checked ){
    sn = 0;
  } else {
    sn = lstTeacher->ItemIndex + 1;
  }

  for( t = sn; t < g_iTeacherCount; t++ ){
    for( w = atWEEK_MON; w <= atWEEK_SAT; w++ ){
      cc = 0;
      for( n = atLESSON_1; n <= atLESSON_MAX; n++ ){
        sc = GetScheduleDataCell( t, w, n );
        if( ((sc->ClassType == CT_NORMAL) || (sc->ClassType == CT_FIXED)) &&
           !IsEmptyClassNo(t, w, n) ){
          cc++;
          if( cc >= 5 ){
            lstTeacher->ItemIndex = t;
            lstTeacherClick(lstTeacher);
            return;
          }
        }
      }
    }
  }

  MessageDlg2( "하루 5시간 이상 수업하는 교사는 없습니다.", "메시지", mtInformation, TMsgDlgButtons() << mbOK, 0 );
}


void __fastcall TfrmPersonal::mnuClassClick(TObject *Sender)
{
  frmClass->ShowModal();
}


void __fastcall TfrmPersonal::mnuTools(TObject *Sender)
{
  if( mState ){
    pntTeacher->Cursor = crDefault;
    mState = FALSE;
  }

  dynamic_cast<TAction *>(Sender)->Checked = TRUE;
  iCurWork = dynamic_cast<TAction *>(Sender)->Tag;
  pnlTools->Caption = dynamic_cast<TAction *>(Sender)->Caption;
}

void __fastcall TfrmPersonal::btnToolsClick(TObject *Sender)
{
    TPoint p;
    TToolButton *btn;

    btn = dynamic_cast<TToolButton *>(Sender);
    p.x = btn->Left;
    p.y = btn->Top + btn->Height;
    p = this->ClientToScreen( p );
    PopupMenu1->Popup( p.x, p.y );
}

void __fastcall TfrmPersonal::mnuFindFirstClick(TObject *Sender)
{
    mnuFindFirst->Checked = !mnuFindFirst->Checked;
    chkFindFirst->Checked = mnuFindFirst->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPersonal::chkFindFirstClick(TObject *Sender)
{
    mnuFindFirst->Checked = chkFindFirst->Checked;
}
//---------------------------------------------------------------------------

