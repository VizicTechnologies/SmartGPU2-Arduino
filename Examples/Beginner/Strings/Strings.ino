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
  
  while(1){    
    //config strings
    lcd.setTextColour(SG_YELLOW);    
    lcd.setTextSize(SG_FONT0);
    lcd.string(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456789",0);                   //write a string on the screen
    delay(500);    
    lcd.setTextSize(SG_FONT1);
    lcd.string(0,15,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456789",0);                  //write a string on the screen
    delay(500);    
    lcd.setTextSize(SG_FONT2);
    lcd.string(0,34,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456789",0);                  //write a string on the screen
    delay(500);    
    lcd.setTextSize(SG_FONT3);
    lcd.string(0,58,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456789",0);                  //write a string on the screen
    delay(500);    
    lcd.setTextSize(SG_FONT4);
    lcd.string(0,85,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456789",0);                  //write a string on the screen
    delay(500);        
    lcd.setTextSize(SG_FONT5);
    lcd.string(0,120,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456789",0);                 //write a string on the screen
    delay(500);   
    lcd.setTextSize(SG_FONT6);
    lcd.string(0,160,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456789",0);                 //write a string on the screen
    delay(3000);       
    lcd.erase();                                              //erase screen      
    
    lcd.setTextColour(SG_GREEN);        
    lcd.setTextSize(SG_FONT7);
    lcd.string(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,"01234567",0);                     //write a string on the screen
    delay(500);    
    lcd.setTextSize(SG_FONT8);
    lcd.string(0,65,LCD_WIDTH-1,LCD_HEIGHT-1,"0123456",0);                     //write a string on the screen
    delay(500);    
    lcd.setTextSize(SG_FONT9);
    lcd.string(0,133,LCD_WIDTH-1,LCD_HEIGHT-1,"012345",0);                     //write a string on the screen
    delay(3000);       
    lcd.erase();                                              //erase screen 
    
    lcd.setTextColour(SG_BLUE);      
    lcd.setTextSize(SG_FONT10);
    lcd.string(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,"01234",0);                        //write a string on the screen
    delay(2000);       
    lcd.erase();                                              //erase screen  
  }                           
}
