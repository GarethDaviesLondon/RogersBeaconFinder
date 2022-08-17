#include "settings.h"
#include <arduino.h>
//#define DEBUGSETTINGS //Include this in the compile to debug any settings issues with the EEPROM


eepromSettings::eepromSettings(int junk)
{

  if (valid() == true) {
      load();
  } else {
      _resetValues();
      save();
  }
}

void eepromSettings::reset()
{
  _resetValues();
  save();
}
void eepromSettings::_resetValues() //This resets the EEPROM values to defaults in case of issues
{
        data.checkversion=CHECKEEPROMVERSION;

        strncpy(data.HomeCall,HOMECALL,8);
        strncpy(data.HomeLocator,HOMELOCATOR,8);
        
        data.lastBand = 1296;
        data.sort1296 = 1;
        data.index1296=1;
        data.sort144 = 1;
        data.index144=1;
        data.sort50 = 1;
        data.index50=1;
                
        data.Degree0 =26;
        data.Degree90 =191;
        data.Degree180 =372;
        data.Degree270 =550;
        data.Degree360 =721;
        data. Degree450 =900;
        
        data.SlowApproachDegrees =15;
        data.BacklashDegrees =3;
        data.AcceptableMargin =0;
        data.SlowStartDegrees =10;
        data.SlowSpeed =0;
        data.FastSpeed =128;

        data.TS_MINX = 140; //Clibration points found by trial and error
        data.TS_MAXX = 925;
        data.TS_MINY = 130;
        data.TS_MAXY = 926;
}

void eepromSettings::report()
{
#ifdef DEBUGSETTINGS
      Serial.print("unsigned char checkversion ");Serial.println(data.checkversion);
      Serial.print("char HomeCall[8] ");Serial.println(String(data.HomeCall));
      Serial.print("char HomeLocator[8] ");Serial.println(String(data.HomeLocator));
      Serial.print("unsigned int lastBand ");Serial.println(data.lastBand);
      Serial.print("unsigned int sort1296 ");Serial.println(data.sort1296);
      Serial.print("unsigned int index1296 ");Serial.println(data.index1296);
      Serial.print("unsigned int sort144 ");Serial.println(data.sort144);
      Serial.print("unsigned int index144 ");Serial.println(data.index144);
      Serial.print("unsigned int sort50 ");Serial.println(data.sort50);
      Serial.print("unsigned int index50 ");Serial.println(data.index50);
      Serial.print("unsigned int Degree0 ");Serial.println(data.Degree0);
      Serial.print("unsigned int Degree90 ");Serial.println(data.Degree90);
      Serial.print("unsigned int Degree180 ");Serial.println(data.Degree180);
      Serial.print("unsigned int Degree270 ");Serial.println(data.Degree270);
      Serial.print("unsigned int Degree360 ");Serial.println(data.Degree360);
      Serial.print("unsigned int Degree450 ");Serial.println(data.Degree450);
      Serial.print("unsigned int SlowApproachDegrees ");Serial.println(data.SlowApproachDegrees);
      Serial.print("unsigned int BacklashDegrees ");Serial.println(data.BacklashDegrees);
      Serial.print("unsigned int AcceptableMargin ");Serial.println(data.AcceptableMargin);
      Serial.print("unsigned int SlowStartDegrees ");Serial.println(data.SlowStartDegrees);
      Serial.print("unsigned int SlowSpeed ");Serial.println(data.SlowSpeed);
      Serial.print("unsigned int FastSpeed ");Serial.println(data.FastSpeed);
      Serial.print("unsigned int TS_MINX ");Serial.println(data.TS_MINX); //Clibration points found by trial and error
      Serial.print("unsigned int TS_MAXX ");Serial.println(data.TS_MAXX);
      Serial.print("unsigned int TS_MINY ");Serial.println(data.TS_MINY);
      Serial.print("unsigned int TS_MAXY ");Serial.println(data.TS_MAXY);
#endif
}


bool eepromSettings::valid()  // This checks if there is valid data in the EEPROM 
                              // If the byte order etc. are changed then 
{
  byte d;
  d=EEPROM.read(0);
  if ( d==CHECKEEPROMVERSION) return true;
  return false;
  
}


void eepromSettings::load()
{
  #ifdef DEBUGSETTINGS
    Serial.println("Loading EEPROM");
  #endif
  
  int a;
  byte* p = (byte*) &data;
  for (a=0;a<sizeof(data);a++)
  {
    p[a]=EEPROM[a];
  }
  
  #ifdef DEBUGSETTINGS
    Serial.println("Loading EEPROM");
  #endif
  
  report();
}

void eepromSettings::save()
{
  
  #ifdef DEBUGSETTINGS
    Serial.println("Saving EEPROM");
  #endif
  
    int a;
  byte* p = (byte*) &data;
  for (a=0;a<sizeof(data);a++)
  {
    EEPROM.update(a,p[a]);
    //EEPROM[a]=p[a];     //This format of command failed, so went with the original
  }
  
  #ifdef DEBUGSETTINGS
    Serial.println("Saving Settings");
  #endif
  
  report();
}
