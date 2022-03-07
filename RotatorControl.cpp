#include <arduino.h>
#include "RotatorControl.h"
#include "rotatepage.h"
#include "settings.h"


Rotator::Rotator()
{
    RotateRight =_RotateRight;
    RotateLeft =_RotateLeft;
    SpeedControl =_SpeedControl;
    ROTORHEADINGPIN =_ROTORHEADINGPIN;
    pinMode(A15,INPUT);
    pinMode(RotateLeft,OUTPUT);
    digitalWrite(RotateLeft,LOW);
    pinMode(RotateRight,OUTPUT);
    digitalWrite(RotateRight,LOW);
    
    init();

}

void Rotator::init()
{
      Degree0 =eepromSettings::data.Degree0;
    Degree90 =eepromSettings::data.Degree90;
    Degree180 =eepromSettings::data.Degree180;
    Degree270 =eepromSettings::data.Degree270;
    Degree360 =eepromSettings::data.Degree360;
    Degree450 =eepromSettings::data.Degree450;
    
    SlowApproachDegrees =eepromSettings::data.SlowApproachDegrees;
    BacklashDegrees =eepromSettings::data.BacklashDegrees;
    AcceptableMargin =eepromSettings::data.AcceptableMargin;
    SlowStartDegrees =eepromSettings::data.SlowStartDegrees;
    SlowSpeed =eepromSettings::data.SlowSpeed;
    FastSpeed =eepromSettings::data.FastSpeed;
}

void Rotator::_setupRotator()
{
}


int Rotator::BeamHeading()
{
  current=_DegreesFromReading(Voltage());
  return current;
}

int Rotator::Voltage()
{
  return _RotatorReading();
}



void Rotator::_SerialOutput(char *pos)
{
  Serial.println(pos);
}


int Rotator::RotateTo(int t)
    {
      _RotateTo(t,_SerialOutput);
      return BeamHeading();
    }

int Rotator::RotateTo(int target, void *reportPosition (char*))
{
  reportPosition("It Worked");
  delay (2000);
}
    
int Rotator::Abort()
    {
      _AllStop();
      _AbortRotate();
    }

int Rotator::ConvertToVoltage(int b)
{
   return _ReadingFromDegrees (b);
}

int Rotator::ConvertToDegrees(int v)
{
  return _DegreesFromReading (v);
}


bool Rotator::_AbortRotate()
{
  return Aborted;
}



int Rotator::_RotatorReading(void)
{
  return analogRead(ROTORHEADINGPIN);
}

int Rotator::_getErrorReading(int target)
{
  int current,e;
  current = _DegreesFromReading(_RotatorReading());
      
   GoRight=false;
   CONTROLPIN=RotateLeft;
   NOTCONTROLPIN=RotateRight;
   e= current-target;
      
   if (target>current)
      {
        NOTCONTROLPIN=CONTROLPIN;
        CONTROLPIN=RotateRight;
        e=target-current;
        GoRight=true;
      }
   return e;
}




void Rotator::_RotateTo(int target,void *reportPosition (char*) )
{
      reportPosition("Moving to target ");
      reportPosition(target);
             
      int ControlPin,e;
      int start;

      Aborted=false;
      _AllStop();
      _rotateFast(target);
      _rotateSlow(target);
      delay(2000);
      _rotateBacklash(target); 
      _AllStop(); //Just to make sure
;
}



void Rotator::_rotateBacklash(int target)
{
     if (Aborted) return;
     int current,start,e;
     _SetSpeedSlow();
 
      while(_getErrorReading(target) > AcceptableMargin)
      {      
            digitalWrite(NOTCONTROLPIN,LOW);
            digitalWrite(CONTROLPIN,HIGH);
            if (_AbortRotate()==true) return;
      }
      _AllStop();
      delay(250);//to get an accurate reading

 }

void Rotator::_rotateSlow(int target)
{
     if (Aborted) return;
     int current,start,e;
     _SetSpeedSlow();

      
      while(_getErrorReading(target) > BacklashDegrees)
      {      
            digitalWrite(NOTCONTROLPIN,LOW);
            digitalWrite(CONTROLPIN,HIGH);
            if (_AbortRotate()==true) return;
      }
      _AllStop();
 }

void Rotator::_rotateFast(int target)
{
      if (Aborted) return;
      int current,start,e;
      current = _DegreesFromReading(_RotatorReading());
      start=current;

      while(_getErrorReading(target) > SlowApproachDegrees)
      {      
      if ( abs(current-start) < SlowStartDegrees)
            {
              _SetSpeedSlow();
            } else {
              _SetSpeedFast();
            }
            digitalWrite(NOTCONTROLPIN,LOW);
            digitalWrite(CONTROLPIN,HIGH);
            current = _DegreesFromReading(_RotatorReading());
            if (_AbortRotate()==true) return;
      }
      _AllStop();
}

void Rotator::_AllStop()
{
        digitalWrite(RotateLeft,LOW);
        digitalWrite(RotateRight,LOW);
        if (!Aborted) return;
}


void Rotator::_SetSpeedSlow()
{
  analogWrite(SpeedControl,SlowSpeed);
}

void Rotator::_SetSpeedFast()
{
  analogWrite(SpeedControl,FastSpeed);
}


double Rotator::_DegreesFromReading(int red)
{
  double degs;
  double reading=(double)red;
  if (reading < Degree90) 
  {
    degs = (reading-Degree0)/(Degree90-Degree0) * 90;
  } else {
    if (reading < Degree180)
    {
      degs = ( (reading-Degree90) / (Degree180-Degree90) * 90 ) + 90;
    } else {
      if (reading < Degree270)
      {   
        degs = ( (reading-Degree180) / (Degree270-Degree180) * 90 ) + 180; 
      } else {
        if (reading <Degree360)
        {
          degs = ( (reading-Degree270) / (Degree360-Degree270) * 90 ) + 270; 
        } else {
          degs = ( (reading-Degree360) / (Degree450-Degree360) * 90 ) + 360;
        }
      }
    }
  }
  return(degs);
}
      

int Rotator::_ReadingFromDegrees(double degs)
{
  double d;
  if (degs > 0 & degs <90)
  {
    d = ((double)Degree90-(double)Degree0)/90.0;
    d= d*(double)degs+(double)Degree0;
    return( (int)d);
  }
  
  if (degs >= 90 & degs <180)
  {
    degs=degs-90;
    d = ((double)Degree180-(double)Degree90)/90.0;
    d= d*(double)degs+(double)Degree90;
    return( (int)d);    
  }

  if (degs >= 180 & degs <270)
  {
    degs=degs-180;
    d = ((double)Degree270-(double)Degree180)/90.0;
    d= d*(double)degs+(double)Degree180;
    return( (int)d);
  }

  if (degs >= 270 & degs <360)
  {
    degs=degs-270;
    d = ((double)Degree360-(double)Degree270)/90.0;
    d= d*(double)degs+(double)Degree270;
    return( (int)d);
  }

  if (degs >= 360 & degs <450)
  {
    degs=degs-360;
    d = ((double)Degree450-(double)Degree360)/90.0;
    d= d*(double)degs+(double)Degree360;
    return( (int)d);
  }
  return (-1);  
}
