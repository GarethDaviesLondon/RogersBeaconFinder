#ifndef __ROTATORCALIBRATEH
#define __ROTATORCALIBRATEH TRUE
#include "tftdisp.h"
#include "RotatorControl.h"
#include "settings.h"

/*These are the Button IDs used by the page object to return button presses*/

#define IDDEG0 0
#define IDDEG90 90
#define IDDEG180 180
#define IDDEG270 270
#define IDDEG360 360
#define IDDEG450 450
#define IDSAVE 100
#define IDCANCEL 101
#define IDRESET  102


class rotatorCalibratePage : public  page
{
  public:
      rotatorCalibratePage(tftDISP* disp, myTS* tp, Rotator*);
      Rotator* r;
      txtBox* title;
      txtBox* heading;
      txtBox* currentreading;
      txtBox* deg0;
      txtButton* deg0button;
      txtBox* deg90;
      txtButton* deg90button;
      txtBox* deg180;
      txtButton* deg180button;
      txtBox* deg270;
      txtButton* deg270button;
      txtBox* deg360;
      txtButton* deg360button;
      txtBox* deg450;
      txtButton* deg450button;
      txtButton* saveBtn;
      txtButton* cancelBtn;
      txtButton* BtnReset;     
      int loop();
      int waitforClick();
      void updateDegree(int,int);
};



#endif
