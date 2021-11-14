#ifndef __GRP_UTIL_H_
#define __GRP_UTIL_H_

#include <windows.h>

void DrawArrowLine(HDC hDC, int sx, int sy, int ex, int ey);
void DrawButtonLine(HDC hDC, TRect &Rect);
void DrawButtonText(HDC hDC, TRect &Rect, char * StrData);
void DrawRectText( HDC hDC, TRect &Rect, char *StrData );


#endif	// Global
