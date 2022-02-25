#ifndef __BANDPAGEH
#define __BANDPAGEH TRUE
#include "tftdisp.h"
#include "beacons.h"
#include "settings.h"

/*These are the Button IDs used by the page object to return button presses*/

#define ID1296 1296
#define ID50 50
#define ID144 144


class bandPage : public  page
{
  public:
      bandPage(tftDISP* disp, myTS* tp,beaconTable*);
      beaconTable* b;
      txtBox* title;
      txtButton* Btn50;
      txtButton* Btn144;
      txtButton* Btn1296;
      int loop(); 
};



#endif
