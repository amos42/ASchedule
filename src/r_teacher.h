// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'r_teacher.pas' rev: 6.00

#ifndef r_teacherHPP
#define r_teacherHPP

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\QuickRpt.hpp>
#include <vcl\QRCtrls.hpp>
#include <ExtCtrls.hpp>

class TqrTeachers : public TQuickRep
{
	typedef Quickrpt::TQuickRep inherited;

__published:
        TQRBand *PageHeaderBand1;
        TQRLabel *QRLabel19;
        TQRBand *DetailBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRBand *PageFooterBand1;
        TQRBand *ColumnHeaderBand1;
        TQRShape *QRShape1;
        TQRShape *QRShape2;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRShape *QRShape5;
        TQRShape *QRShape6;
        TQRShape *QRShape7;
        TQRShape *QRShape8;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel16;
        TQRLabel *QRLabel17;
        TQRLabel *QRLabel18;
        void __fastcall QuickRepBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
        void __fastcall QuickRepNeedData(TObject *Sender, bool &MoreData);
	
private:
	int rc;
	int Week;
	
public:
   __fastcall TqrTeachers::TqrTeachers(TComponent* Owner);
	
};


extern PACKAGE TqrTeachers* qrTeachers;


#endif	// r_teacher
