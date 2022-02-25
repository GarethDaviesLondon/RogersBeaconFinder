#include <math.h>
#include <maidenhead.h>
#include <arduino.h>
#include "beacons.h"
#include "settings.h"

/*    Settings 
 *    unsigned int lastBand;
      unsigned int sort1296;
      unsigned int index1296;
      unsigned int sort144;
      unsigned int index144;
      unsigned int sort50;
      unsigned int index50;
 */

beaconTable::beaconTable(Beacon* b23,int f23, Beacon* b2, int f2,Beacon* b6, int f6)
{

     size1296 = f23;
     size144 = f2;
     size50 = f6;
     b1296=b23;
     b144=b2;
     b50=b6;
     currentBand=eepromSettings::data.lastBand;
     setActiveBand(currentBand);    
     CurrentBeaconList = b50;
     BeaconListSize = size50;

     char loc2[]="IO83VC"; //create a locator with the appropriate ending of the char* array thing.
     strncpy(loc2,eepromSettings::data.HomeLocator,6);//Copy the first 6 bytes.
     homeLong = mh2lon(loc2);
     homeLat = mh2lat(loc2);   
     orderBeacons(-1); //in the order they were loaded
}

void beaconTable::_saveIndex()
{
  switch(currentBand){
      case 1296:
           eepromSettings::data.index1296=currentIndex;
           break;
      case 144:
           eepromSettings::data.index144=currentIndex;
           break;
      case 50:
           eepromSettings::data.index50=currentIndex;
           break;
     }
     eepromSettings::save();
}

void beaconTable::setActiveBand(int band)
{
  currentBand=band;

  switch(band){
    case 50: 
         CurrentBeaconList = b50;
         BeaconListSize = size50;
         currentIndex=eepromSettings::data.index50;
         orderBeacons(-1); //in the order they were loaded
         break;
    case 144: 
         CurrentBeaconList = b144;
         BeaconListSize = size144;
         currentIndex=eepromSettings::data.index144;
         orderBeacons(-1); //in the order they were loaded
         break;
    case 1296: 
         CurrentBeaconList = b1296;
         BeaconListSize = size1296;
         currentIndex=eepromSettings::data.index1296;
         orderBeacons(-1); //in the order they were loaded
         break;
    default:
        Serial.print("Error setting band - Requested was ");Serial.println(band); 
        break;   
  }
  eepromSettings::data.lastBand=currentBand;
  eepromSettings::save();
  eepromSettings::load();
  eepromSettings::save();
}

    boolean beaconTable::atLast()
    {
      if (currentIndex>=BeaconListSize-1) return true;
      return false;
    }
    
    boolean beaconTable::atFirst()
    {
      if (currentIndex==0) return true;
      return false; 
    }

boolean beaconTable::listIsEmpty()
{
  if (BeaconListSize==0) return true;
  return false;
}

Beacon* beaconTable::reWind()
    {
      currentIndex=0;
      _saveIndex();
    }

Beacon* beaconTable::beacon()
{
  return &CurrentBeaconList[currentIndex];
}

Beacon* beaconTable::next()
{
  if (atLast()==false) {
    currentIndex++;
    _saveIndex();
  }
  return &CurrentBeaconList[currentIndex];
}

Beacon* beaconTable::prev()
{
  if (atFirst()==false) 
  {
    currentIndex--;
    _saveIndex();
  }
  return &CurrentBeaconList[currentIndex];
}

void beaconTable::orderBeacons(int mode)
{
   //currentIndex=0;
   //Not yet implemented
}


double beaconTable::CalcDistance(char * locator)
{
          return  CalcDistance(homeLat,homeLong, mh2lat(locator),mh2lon(locator));
}
    
double beaconTable::CalcDistance(double lat1, double long1, double lat2, double long2)
{
  //main code inside the class
  double dlat1 = lat1 * (M_PI / 180);

  double dlong1 = long1 * (M_PI / 180);
  double dlat2 = lat2 * (M_PI / 180);
  double dlong2 = long2 * (M_PI / 180);

  double dLong = dlong1 - dlong2;
  double dLat = dlat1 - dlat2;

  double aHarv = pow(sin(dLat / 2.0), 2.0) + cos(dlat1)*cos(dlat2)*pow(sin(dLong / 2), 2);
  double cHarv = 2 * atan2(sqrt(aHarv), sqrt(1.0 - aHarv));
  //earth's radius from wikipedia varies between 6,356.750 km � 6,378.135 km (�3,949.901 � 3,963.189 miles)
  //The IUGG value for the equatorial radius of the Earth is 6378.137 km (3963.19 mile)
  const double earth = 3963.19;//I am doing miles, just change this to radius in kilometers to get distances in km
  double distance = earth * cHarv;
  return distance;
}


int beaconTable::CalcBearing(char * locator)
{
          double lat = mh2lat(locator);
          double lon = mh2lon(locator);
          String msg = "Lat "+String(lat)+"Long " + String(lon);
          Serial.println(msg);
          return  CalcBearing(homeLat,homeLong,lat,lon);
}
    
int beaconTable::CalcBearing(double latdeg1, double longdeg1, double latdeg2, double longdeg2)
{
  /*
  https://www.movable-type.co.uk/scripts/latlong.html
  */
  double lat1 = latdeg1 * PI / 180;
  double lat2 = latdeg2 * PI / 180;
  double long1 = longdeg1 * PI / 180;
  double long2 = longdeg2 * PI / 180;
  
  double del = long2-long1;
  
  double x = sin(del) * cos(lat2);
  double y = cos(lat1)*sin(lat2) -
    (sin(lat1)*cos(lat2)*cos(del));



  
  double radbearing = atan2(x,y);

  
  double bearing = (radbearing * 180 / PI) + 360;

  
  while (bearing >= 360)
  {
    bearing = bearing - 360;
  }
  return (int)round(bearing);
}

int beaconTable::BeaconSortFreq(const void *v1, const void *v2)
{
  const Beacon *p1 = (Beacon *)v1;
  const Beacon *p2 = (Beacon *)v2;
  if (p1->Mhz < p2->Mhz)
    return -1;
  else if (p1->Mhz > p2->Mhz)
    return 1;
  else
    return 0;
}

int beaconTable::BeaconSortCall(const void *v1, const void *v2)
{
  const Beacon *p1 = (Beacon *)v1;
  const Beacon *p2 = (Beacon *)v2;

  if (p1->Name != p2->Name)
  {
    if (p1->Name > p2->Name)
      return 1;
    else
      return -1;
  }
  else
    return 0;
}

int beaconTable::BeaconSortDistanceFromHome(const void *v1, const void *v2)
{
  const Beacon *p1 = (Beacon *)v1;
  const Beacon *p2 = (Beacon *)v2;
  
  double lat1,lon1,lat2,lon2;
  lon1=mh2lon(p1->Locator);
  lat1=mh2lat(p1->Locator);
  lon2=mh2lon(p2->Locator);
  lat2=mh2lat(p2->Locator);
  double d1 = CalcDistance(lat1, lon1, homeLat, homeLong);
  double d2 = CalcDistance(lat2, lon2, homeLat, homeLong);
  
  if (d1 != d2)
  {
    if (d1 > d2)
      return 1;
    else
      return -1;
  }
  else
    return 0;
}

int beaconTable::BeaconSortBearingFromHome(const void *v1, const void *v2)
{
  const Beacon *p1 = (Beacon *)v1;
  const Beacon *p2 = (Beacon *)v2;

  double lat1,lon1,lat2,lon2;
  lon1=mh2lon(p1->Locator);
  lat1=mh2lat(p1->Locator);
  lon2=mh2lon(p2->Locator);
  lat2=mh2lat(p2->Locator);
  double d1 = CalcBearing(homeLat, homeLong,lat1, lon1);
  double d2 = CalcBearing(homeLat, homeLong,lat2, lon2);
  
  if (d1 != d2)
  {
    if (d1 > d2)
      return 1;
    else
      return -1;
  }
  else
    return 0;
}


void beaconTable::processArray()
{

}

int test()
{

}


void beaconTable::loadArray()
{

}
