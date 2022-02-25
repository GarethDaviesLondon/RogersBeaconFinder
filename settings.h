#ifndef __SETTINGSH
#define __SETTINGSH TRUE
#include <EEPROM.h>

#define CHECKEEPROMVERSION 0x7 //This is to check that the settings in the EEPROM are valid
                              //If this were critical could also do a checksum calculation on the data, but it's probably not


struct eepromData {
      unsigned char checkversion;
      char HomeCall[8];
      char HomeLocator[6];
      unsigned int lastBand;
      unsigned int sort1296;
      unsigned int index1296;
      unsigned int sort144;
      unsigned int index144;
      unsigned int sort50;
      unsigned int index50;
      unsigned int Degree0 ;
      unsigned int Degree90 ;
      unsigned int Degree180 ;
      unsigned int Degree270 ;
      unsigned int Degree360 ;
      unsigned int Degree450 ;
      unsigned int SlowApproachDegrees ;
      unsigned int BacklashDegrees ;
      unsigned int AcceptableMargin ;
      unsigned int SlowStartDegrees ;
      unsigned int SlowSpeed ;
      unsigned int FastSpeed ;
      unsigned int TS_MINX ; //Clibration points found by trial and error
      unsigned int TS_MAXX ;
      unsigned int TS_MINY ;
      unsigned int TS_MAXY ;
};


class eepromSettings {

    public:
        eepromSettings(int);
        static  eepromData data;
        static void load();
        static void save();
        static bool valid();
        static void report();
        static void reset();
    private:
        static void _resetValues();
  
};





#endif
