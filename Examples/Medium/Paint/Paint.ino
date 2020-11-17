/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2020.
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
********************************************************/

#include <SMARTGPU2.h>      //include the SMARTGPU2 library!

SMARTGPU2 lcd;              //create our object called LCD

SG_AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution
 
#define PENSIZE 1           //size of the drawing pen 

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
    SG_POINT point;
    SG_NUMBEROFBYTES nb;

    lcd.baudChange(SG_BAUD6); //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!

    //front cover
    lcd.setTextColour(SG_YELLOW);
    lcd.setTextSize(SG_FONT4);    
    lcd.string(85,50,LCD_WIDTH-1,LCD_HEIGHT-1,"Mini Paint",&nb);        
    lcd.setTextColour(SG_BLUE);
    lcd.setTextSize(SG_FONT3);        
    lcd.string(70,95,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch on corner \nto erase screen",&nb);
    lcd.setTextColour(SG_MAGENTA);
    lcd.setTextSize(SG_FONT2);        
    lcd.string(50,170,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch screen to begin",&nb);
    
    while(lcd.touchScreen(&point)==SG_INVALID);                       // Wait for a touch on the screen to start
    lcd.erase();
    lcd.objButton(LCD_WIDTH-1-40,0,LCD_WIDTH-1,25,SG_DESELECTED,"clear");
    delay(500);
    
    while(1){                                                         // Loop forever
      if(lcd.touchScreen(&point)==SG_VALID){                          // If we receive a touch on the screen
        if((point.x > (LCD_WIDTH-1-40)) && (point.y < 25)){           // if touch on clear button
          lcd.erase();
          lcd.objButton(LCD_WIDTH-1-40,0,LCD_WIDTH-1,25,SG_DESELECTED,"clear");
          delay(200);
        }else{                                                        // touch anywhere on the screen
          lcd.drawCircle(point.x,point.y,PENSIZE,SG_YELLOW,SG_FILL);  // Draw circle on touched coordinates          
        }
      }
    }
}
