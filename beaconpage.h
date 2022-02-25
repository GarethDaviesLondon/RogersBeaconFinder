#ifndef __BEACONPAGEH
#define __BEACONPAGEH TRUE
#include "tftdisp.h"
#include "beacons.h"
#include "RotatorControl.h"
#include "settings.h"

/*These are the Button IDs used by the page object to return button presses*/

#define SETUPID 11
#define PREVID 2
#define NEXTID 3
#define SORTID 4
#define ROTATEID 5 


class beaconPage : public  page
{
  public:
      beaconPage(tftDISP* disp, myTS* tp,beaconTable* ,Rotator *);
      beaconTable* b;
      txtBox* call;
      txtBox* freq;
      txtBox* bearing;
      txtBox* range;
      txtBox* locator;
      txtBox* statusMessage;
      txtBox* currentHeading;
      txtBox* currentHeadingTitle;
      txtButton* BtnSort;
      txtButton* BtnRotate;
      txtButton* BtnNext;
      txtButton* BtnPrev;
      txtButton* BtnSetup;
      eepromSettings* settings;
      void makeActive();
      void setBeaconInfo();
      void scroll();
      int loop();
      void redrawBeacon();
      void clrBeacon();
      void checkByRef (eepromSettings* s);
      int waitforClick();
      tftDISP *dp;
      myTS *t;
      Rotator *r;
    
};



#endif
