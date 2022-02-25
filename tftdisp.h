#ifndef __TFTDISPH
#define __TFTDISPH TRUE
#include "settings.h"

// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// This demo code returns raw readings, public domain
#include "TouchScreen.h"
#include <arduino.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


// These are the pins for the shield!
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin



#define SCREENROTATION 1




void  statusMsg(String msg);


//struct pageListMember {txtBox* Member; txtBox* Previous; txtBox* Next;};

class tftDISP{
  public:
    tftDISP();
    void init();
    void report();
    int backgroundcolor=BLACK;
    int ROTATION = 1;
    void fillRect(int ,int , int , int , int );
    void drawRect(int ,int , int , int , int );
    void setCursor (int , int );
    void setTextColor (int , int );
    void setTextSize (int );
    void print (String );
  private:
    void disconectTouch();
  
};


class myTS {
  public:
    myTS(tftDISP*, eepromSettings*);
    TSPoint pressDetected();
    TSPoint orientPoint(TSPoint p);
    void getPoints();
    void releasePins();
    eepromSettings* touchSettings;
     int calXmin;
     int calXmax;
     int calYmin;
     int calYmax;

#ifdef DEBUG
    void checkByRef (eepromSettings* s);
#endif

  private: 
    tftDISP* d;
    bool myAbortRotate();

};

/*  int myTS::calXmin=0;
  int myTS::calYmin=0;
  int myTS::calXmax=0;
  int myTS::calYmax=0;
*/


class txtBox{
  //friend class page;
  public:
    txtBox(tftDISP*,myTS*);
    txtBox();
    void init(tftDISP* ,myTS* );
    tftDISP *d;
    myTS* t;
    int x=0;
    int y=0;
    int height=20;
    int width=100;
    boolean border=false;
    String message="test";
    int fontsize=1;
    int txtcolor=WHITE;
    int fillcolor=BLACK;
    int bordercolor=WHITE;
    int topmargin=5;
    int leftmargin=5;
    int id=0;
    txtBox* nextBox=NULL;

    void show();
    void hide();
    void clr();
    void changetext();
    void redraw();
    boolean valid=false;
};


class txtButton : public txtBox
{
public:  
    txtButton(tftDISP*,myTS*);
    txtButton();
    boolean wasitMe(TSPoint);
}; 


class page{
  public:
    tftDISP *d;
    myTS *t;
    page(tftDISP*, myTS*);
    page();
    

    boolean active(void);
    int backgroundcolor = BLACK;
    void addtxtBox(txtBox*);
    void addtxtButton(txtButton*);
    void makeActive();
    void deActive();
    int show();
    int hide();
    int waitforClick();

    boolean _active = false; //should be protected I guess
    
   protected:
    txtBox* firstBox=NULL;
    txtBox* lastBox=NULL;
    txtButton* firstButton=NULL;
    txtButton* lastButton=NULL;
};


#endif
