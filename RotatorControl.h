#ifndef __ROTATECONTROLH
#define __ROTATECONTROLH TRUE
#include "settings.h"

        
#define _RotateRight 53; //Pin Number
#define _RotateLeft 51; //Pin Number      
#define _SpeedControl 45; //Pin Number
#define _ROTORHEADINGPIN 15;//Pin Number


class Rotator {

public:

    Rotator();
    int BeamHeading();
    int Voltage();
    int RotateTo(int);
    int RotateTo(int target, void *function  (char* s)); //this includes a funtion for call back to display progress
    int Abort();
    int ConvertToVoltage(int b);
    int ConvertToDegrees(int v);
    void init();

private:
    
    bool GoRight,Aborted;
    long int target;
    long int current;
    int CONTROLPIN,NOTCONTROLPIN;

    bool _AbortRotate();
    void _setupRotator();
    int _RotatorReading(void);
    int _getErrorReading(int target);
    //void _RotateTo(int target);
    void _RotateTo(int target, void *function  (char* s)); //this includes a funtion for call back to display progress
    void _rotateBacklash(int target);
    void _rotateSlow(int target);
    void _rotateFast(int target);
    void _AllStop();
    void _SetSpeedSlow();
    void _SetSpeedFast();
    static void _SerialOutput(char *pos);
    double _DegreesFromReading(int red);
    int _ReadingFromDegrees(double degs);

    int Degree0 =26;
    int Degree90 =191;
    int Degree180 =372;
    int Degree270 =550;
    int Degree360 =721;
    int Degree450 =900;
    int RotateRight =53;
    int RotateLeft =51;
    int SpeedControl =45;
    int ROTORHEADINGPIN =15;
      
    int SlowApproachDegrees =15;
    int BacklashDegrees =3;
    int AcceptableMargin =0;
    int SlowStartDegrees =10;
    int SlowSpeed =0;
    int FastSpeed =128;

    
};


#endif
