/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2019.
THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
OR OTHER SIMILAR COSTS.
*********************************************************/

/********************************************************
 IMPORTANT : This Example is created for the Arduino 1.0 Software IDE
 
 THIS DEMO REQUIRES A 32.768Khz CRYSTAL OSCILLATOR MOUNTED/SOLDERED ON THE SMARTGPU2 BOARD
 ON THE PADS LABELED AS "OSC32K", IF THE CRYSTAL ISN'T MOUNTED, THIS DEMO WON'T WORK
 
 THIS DEMO USES THE CURRENT RTC TIME TO UPDATE THE CLOCK HANDS
********************************************************/

#include <SMARTGPU2.h>      //include the SMARTGPU2 library!

SMARTGPU2 lcd;              //create our object called LCD

AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution

#define CLOCKBODYCOLOUR  BLACK        //colour for the body clock
#define CLOCKEDGECOLOUR  GREEN        //colour for the edge of the clock
#define SECCOL           YELLOW       //seconds hand colour
#define MINCOL           MAGENTA      //minutes hand colour
#define HOURCOL          RED          //hours hand colour
#define HALFX            LCD_WIDTH/2  //this point represent the x center of the clock where math is done
#define HALFY            LCD_HEIGHT/2 //this point represent the y center of the clock where math is done

/*********************************************************/
/*********************************************************/
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU2 support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU2 support
  lcd.start(); //initialize the SMARTGPU2 processor
  
  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/
void loop() { //main loop
  POINT secP,minsP,hourP;
  STATE state;
  TIME currentTime;        //struct that holds the seconds,minutes, and hours
  int angleH,angleM,angleS;
  unsigned int handHour=LCD_WIDTH/6;//hand size
  unsigned int handMin=LCD_WIDTH/5; //hand size
  unsigned int handSec=LCD_WIDTH/4; //hand size  
  unsigned char currentSecond=0;

  lcd.baudChange(BAUD4);                               //set high baud for fast drawing  
  lcd.setupRTC(&state);                                //try to setup and enable RTC
  if(state!=ENABLE) while(1);                          //if clock wasn't successfully enabled, means that no 32Khz crystal is mounted
  //up to here clock is setup and running...
  lcd.getRTCTimeDate(&currentTime);                    //obtain time from RTC clock
  currentSecond=currentTime.second;                    //get in currentSecond the currentTime.second value
  
  //draw clock
  lcd.drawCircle(LCD_WIDTH/2,LCD_HEIGHT/2,(LCD_HEIGHT/2)-15,CLOCKBODYCOLOUR,FILL);    //draw clock body
  lcd.drawCircle(LCD_WIDTH/2,LCD_HEIGHT/2,(LCD_HEIGHT/2)-15,CLOCKEDGECOLOUR,UNFILL);  //draw clock edge
  
  //config strings
  lcd.setTextColour(CLOCKEDGECOLOUR);
  lcd.setTextSize(FONT5);
  lcd.setTextBackFill(TRANS);
  
 while(1){
  //Do some Math to get the second point of the clock hands. (first point is always the center of the clock)  
  angleS=currentTime.second*6;                 //get the current seconds in angle form, a circle have 360 degrees divided by 60 seconds = 6, then we multiply the 6 by the current seconds to get current angle
  secP.x=(sin((angleS*3.14)/180)) * handSec;   //get X component of the second's hand
  secP.y=(cos((angleS*3.14)/180)) * handSec;   //get Y component of the second's hand
  angleM=currentTime.minute*6;                 //get the current minutes in angle form, a circle have 360 degrees divided by 60 minutes = 6, then we multiply the 6 by the current minutes to get current angle
  minsP.x=(sin((angleM*3.14)/180)) * handMin;  //get X component of the minutes's hand
  minsP.y=(cos((angleM*3.14)/180)) * handMin;  //get Y component of the minutes's hand 
  angleH= (currentTime.hour>12) ? (currentTime.hour-12) : currentTime.hour; //if hours are more than 12(24 hour format) substract 12 to convert to 12 hour format
  angleH*=30;                                  //get the current hours in angle form, a circle have 360 degrees divided by 12 hours = 30, then we multiply the 30 by the current hours to get current angle
  hourP.x=(sin((angleH*3.14)/180)) * handHour; //get X component of the hours's hand
  hourP.y=(cos((angleH*3.14)/180)) * handHour; //get Y component of the hours's hand
    
  lcd.string((LCD_WIDTH/2)-15,LCD_HEIGHT/10,LCD_WIDTH-1,LCD_HEIGHT-1,"12",0);  //Draw the 12
  
  //Draw current time hands  
  lcd.drawLine(HALFX,HALFY,HALFX+minsP.x,HALFY-minsP.y,MINCOL);  // Draw the minutes hand, first point is the center of the clock, and the second is the point obtained by doing math
  lcd.drawLine(HALFX,HALFY,HALFX+hourP.x,HALFY-hourP.y,HOURCOL); // Draw the hours hand, first point is the center of the clock, and the second is the point obtained by doing math
  lcd.drawLine(HALFX,HALFY,HALFX+secP.x,HALFY-secP.y,SECCOL);    // Draw the seconds hand, first point is the center of the clock, and the second is the point obtained by doing math
  lcd.drawCircle(HALFX,HALFY,5,SECCOL,FILL);                     // Draw the center of the second's hand
  
  //wait for a second by comparing the currentSecond variable with the new currentTime.second
  do{
    lcd.getRTCTimeDate(&currentTime);            //obtain time from RTC clock
    delay(500);                                  //a little delay to avoid serial port overloading, checking each half second is enough to update a second
  }while(currentTime.second == currentSecond);
  currentSecond=currentTime.second;              //update currentSecond with the new currentTime.second value
 
  //Erase all hands         
  lcd.drawLine(HALFX,HALFY,HALFX+secP.x,HALFY-secP.y,CLOCKBODYCOLOUR);   // Erase Second's hand
  lcd.drawLine(HALFX,HALFY,HALFX+minsP.x,HALFY-minsP.y,CLOCKBODYCOLOUR); // Erase Minute's hand
  lcd.drawLine(HALFX,HALFY,HALFX+hourP.x,HALFY-hourP.y,CLOCKBODYCOLOUR); // Erase Hour's hand            
 }
}
