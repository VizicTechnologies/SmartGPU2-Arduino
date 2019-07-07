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
********************************************************/

#include <SMARTGPU2.h>      //include the SMARTGPU2 library!

SMARTGPU2 lcd;              //create our object called LCD

AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution
 
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
    POINT point;
    
    lcd.baudChange(BAUD6);                      // Set a fast baud!, always that we use touch functions is recommended to use fast baud rates

    //front cover
    lcd.setTextColour(YELLOW);
    lcd.setTextSize(FONT4);    
    lcd.string(85,50,LCD_WIDTH-1,LCD_HEIGHT-1,"Mini Paint",0);        
    lcd.setTextColour(BLUE);
    lcd.setTextSize(FONT3);        
    lcd.string(70,95,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch on corner \nto erase screen",0);
    lcd.setTextColour(MAGENTA);
    lcd.setTextSize(FONT2);        
    lcd.string(50,170,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch screen to begin",0);
    
    while(lcd.touchScreen(&point)==INVALID);                    // Wait for a touch on the screen to start
    lcd.erase();
    lcd.objButton(LCD_WIDTH-1-40,0,LCD_WIDTH-1,25,DESELECTED,"clear");
    delay(500);
    
    while(1){                                                   // Loop forever
      if(lcd.touchScreen(&point)==VALID){                       // If we receive a touch on the screen
        if((point.x > (LCD_WIDTH-1-40)) && (point.y < 25)){ // if touch on clear button
          lcd.erase();
          lcd.objButton(LCD_WIDTH-1-40,0,LCD_WIDTH-1,25,DESELECTED,"clear");
          delay(200);
        }else{                                                  // touch anywhere on the screen
          lcd.drawCircle(point.x,point.y,PENSIZE,YELLOW,FILL);  // Draw circle on touched coordinates          
        }
      }
    }
}
