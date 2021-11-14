// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'r_schdule.pas' rev: 6.00

#ifndef r_schduleHPP
#define r_schduleHPP

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

class TqrSchedules : public TQuickRep 
{
	typedef Quickrpt::TQuickRep inherited;
	
__published:
        TQRBand *PageHeaderBand1;
        TQRBand *DetailBand1;
        TQRShape *QRShape1;
        TQRLabel *QRLabel1;
        TQRLabel *qrlSubject1_1;
        TQRLabel *qrlSubject2_1;
        TQRLabel *qrlSubject3_1;
        TQRLabel *qrlSubject4_1;
        TQRLabel *qrlSubject5_1;
        TQRLabel *qrlSubject6_1;
        TQRShape *QRShape9;
        TQRShape *QRShape2;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRShape *QRShape5;
        TQRShape *QRShape6;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel16;
        TQRLabel *QRLabel17;
        TQRLabel *qrlClass;
        TQRShape *QRShape7;
        TQRShape *QRShape8;
        TQRLabel *QRLabel8;
        TQRLabel *qrlSubject1_2;
        TQRLabel *qrlSubject2_2;
        TQRLabel *qrlSubject3_2;
        TQRLabel *qrlSubject4_2;
        TQRLabel *qrlSubject5_2;
        TQRLabel *qrlSubject6_2;
        TQRShape *QRShape10;
        TQRLabel *QRLabel22;
        TQRLabel *qrlSubject1_3;
        TQRLabel *qrlSubject2_3;
        TQRLabel *qrlSubject3_3;
        TQRLabel *qrlSubject4_3;
        TQRLabel *qrlSubject5_3;
        TQRLabel *qrlSubject6_3;
        TQRShape *QRShape11;
        TQRLabel *QRLabel29;
        TQRLabel *qrlSubject1_4;
        TQRLabel *qrlSubject2_4;
        TQRLabel *qrlSubject3_4;
        TQRLabel *qrlSubject4_4;
        TQRLabel *qrlSubject5_4;
        TQRLabel *qrlSubject6_4;
        TQRShape *QRShape12;
        TQRLabel *QRLabel36;
        TQRLabel *qrlSubject1_5;
        TQRLabel *qrlSubject2_5;
        TQRLabel *qrlSubject3_5;
        TQRLabel *qrlSubject4_5;
        TQRLabel *qrlSubject5_5;
        TQRLabel *qrlSubject6_5;
        TQRShape *QRShape13;
        TQRLabel *QRLabel43;
        TQRLabel *qrlSubject1_6;
        TQRLabel *qrlSubject2_6;
        TQRLabel *qrlSubject3_6;
        TQRLabel *qrlSubject4_6;
        TQRLabel *qrlSubject5_6;
        TQRLabel *qrlSubject6_6;
        TQRShape *QRShape14;
        TQRLabel *QRLabel50;
        TQRLabel *qrlSubject1_7;
        TQRLabel *qrlSubject2_7;
        TQRLabel *qrlSubject3_7;
        TQRLabel *qrlSubject4_7;
        TQRLabel *qrlSubject5_7;
        TQRLabel *qrlSubject6_7;
        TQRShape *QRShape15;
        TQRLabel *QRLabel57;
        TQRLabel *qrlSubject1_8;
        TQRLabel *qrlSubject2_8;
        TQRLabel *qrlSubject3_8;
        TQRLabel *qrlSubject4_8;
        TQRLabel *qrlSubject5_8;
        TQRLabel *qrlSubject6_8;
        TQRShape *QRShape16;
        TQRShape *QRShape17;
        TQRBand *PageFooterBand1;
        void __fastcall QuickRepBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
        void __fastcall QuickRepNeedData(TObject *Sender, bool &MoreData);
	
private:
	int year;
	int cls;

public:
        __fastcall TqrSchedules(TComponent* Owner);
};


extern PACKAGE TqrSchedules* qrSchedules;


#endif	// r_schdule
