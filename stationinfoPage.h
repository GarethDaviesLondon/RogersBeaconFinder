#ifndef __STATIONINFOH
#define __STATIONINFOH TRUE
#include "tftdisp.h"
#include "settings.h"
#include "stationinfoPage.h"

/*These are the Button IDs used by the page object to return button presses*/

#define IDCALLSIGN 1
#define IDLOCATOR 2
#define IDEXITBUTTON 3

class stationinfoPage : public  page
{
  public:
      stationinfoPage(tftDISP*, myTS*);

      txtBox* title;
      txtButton* BtnCall;
      txtButton* BtnLocator;
      txtButton* BtnExit;
      int loop();
};



#endif
