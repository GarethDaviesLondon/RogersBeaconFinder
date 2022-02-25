#ifndef __ROTATEPAGEH
#define __ROTATEPAGEH TRUE
#include "tftdisp.h"
#include "beacons.h"
#include "RotatorControl.h"
#include "settings.h"

/*These are the Button IDs used by the page object to return button presses*/



class rotatePage : public  page
{
  public:
      rotatePage(tftDISP* disp, myTS* tp,beaconTable *,Beacon * ,Rotator *, eepromSettings *);
      Rotator *r;
      Beacon *b;
      txtBox* call;
      txtBox* locator;
      txtBox* targetHeading;
      txtBox* currentHeading;
      txtBox* freq;
      eepromSettings* settings;
      int loop();
      void displayHeading(char *);
      tftDISP *dp;
      myTS *t;
      int heading;
    
};



#endif
