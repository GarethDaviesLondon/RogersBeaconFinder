#ifndef __SETUPVECTORH
#define __SETUPVECTORH TRUE
#include "tftdisp.h"
#include "settings.h"
#include "rotatecalibratepage.h"
#include "stationinfoPage.h"

/*These are the Button IDs used by the page object to return button presses*/

#define IDAZIMUTH 1
#define IDSTATION 2
#define IDEXITSETUP 3


class setupvectorPage : public  page
{
  public:
      setupvectorPage(tftDISP*, myTS*,rotatorCalibratePage*,stationinfoPage*);

      txtBox* title;
      txtButton* BtnAzimuth;
      txtButton* BtnStation;
      txtButton* BtnExit;
      eepromSettings* settings;
      rotatorCalibratePage* rcp;
      stationinfoPage *station;
      Rotator* r;
      int loop();
};



#endif
