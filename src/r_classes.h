// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'r_classes.pas' rev: 6.00

#ifndef r_classesHPP
#define r_classesHPP

#include <QRCtrls.hpp>	// Pascal unit
#include <QuickRpt.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

class TqrClasses : public TQuickRep 
{
	typedef Quickrpt::TQuickRep inherited;
	
__published:
        TQRBand *PageHeaderBand1;
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
        TQRShape *QRShape9;
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
        TQRLabel *QRLabel19;
        void __fastcall QuickRepBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
        void __fastcall QuickRepNeedData(TObject *Sender, bool &MoreData);
	
private:
	int year;
	int cls;
	int Week;
	
public:
        __fastcall TqrClasses(TComponent* Owner);
};


extern PACKAGE TqrClasses* qrClasses;


#endif	// r_classes
