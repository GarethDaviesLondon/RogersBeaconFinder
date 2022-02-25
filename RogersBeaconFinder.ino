
#include <math.h>
#include "RotatorControl.h"
#include "beacons.h"
#include "tftdisp.h"
#include "beaconpage.h"
#include "bandpage.h"
#include "rotatepage.h"
#include "rotatecalibratepage.h"
#include "setupvectorpage.h"
#include "stationinfoPage.h"
#include "settings.h"


/*Wanted to bury this in the class but passing by reference somewhere buggers it up*/
int size1296 = sizeof(B1296) / sizeof(Beacon);
int size144 = sizeof(B144) / sizeof(Beacon);
int size50 = sizeof(B50) / sizeof(Beacon);

eepromData eepromSettings::data;

myTS* T;
stationinfoPage* sip;
rotatorCalibratePage* rcp;
eepromSettings* settings;


void setup(void) {
  
   Serial.begin(9600);
   delay(100); // so Serial is ready
   Serial.println("Starting Up Rotator Control Program");
   
   settings = new eepromSettings(1); 
   tftDISP S;
   Rotator R;
   T= new myTS(&S,settings);
   S.init();
   beaconTable b(B1296,size1296,B144,size144,B50,size50);
   beaconPage pg1=beaconPage(&S,T,&b,&R);
   bandPage pg2=bandPage(&S,T,&b);

   
   //sip = new stationinfoPage(&S,T);                      //Running into memory management issues     
   //rcp = new rotatorCalibratePage(&S,T,&R);
   //setupvectorPage pg4 = setupvectorPage(&S,T, rcp, sip);
   
   rotatorCalibratePage pg4 =  rotatorCalibratePage(&S,T,&R);
   //stationinfoPage pg4= stationinfoPage(&S,T);

   b.setActiveBand(eepromSettings::data.lastBand);    

   pg1.makeActive();
   pg1.show();
   while (1){
       int cd = pg1.loop();
       pg1.deActive();
       Serial.print("Button Pressed returned ID ");Serial.println(cd);
       switch(cd)
       {

          case SETUPID:
               
                Serial.println("Button Pressed Identified as Setup");
                pg4.makeActive();
                pg4.show();
                pg4.loop();
                pg4.hide();
                pg4.deActive();
                break;
                
           case SORTID:
                Serial.println("Button Pressed Identified as Band Switch");
                
                 
                pg2.makeActive();
                pg2.show();
                pg2.loop();
                pg2.hide();
                pg2.deActive();

                
                break;
                
           case ROTATEID:
           
                //don't move this next line outside the while loop!
                rotatePage pg3=rotatePage(&S,T,&b,b.beacon(),&R,(eepromSettings *)&settings); //Important to remain in the case statement and not outside
                                                                                              //as the constructore sets the current beacon information.
                pg3.makeActive();
                pg3.show();
                pg3.loop();
                pg3.hide();
                pg3.deActive();
                break;
                
 
       }
       pg1.makeActive();
       pg1.show();
   }
}


void loop(void) {
  
}
