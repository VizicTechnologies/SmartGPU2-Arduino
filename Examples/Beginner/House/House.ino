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

#define orange   0xFC0F
#define brown    0xBBCA
#define ligBlue  0x96DD

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
 
    lcd.baudChange(SG_BAUD6);         //for fast drawing we need a big baudRate
     
    //draw a background
    lcd.drawGradientRect(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,SG_BLUE,SG_BLACK,SG_VERTICAL);                   //draw a gradient rectangle
    
    //draw the house
    lcd.drawRectangle(78,134,212,217,orange,SG_FILL);                                                  //draw a rectangle
    lcd.drawRectangle(78,134,212,217,SG_BLACK,SG_UNFILL);                                              //draw a rectangle   
    lcd.drawTriangle(75,133,216,133,146,63,SG_RED,SG_FILL);                                            //draw a triangle     
    lcd.drawTriangle(75,133,216,133,146,63,SG_BLACK,SG_UNFILL);                                        //draw a triangle     
    lcd.drawRectangle(136,167,170,217,brown,SG_FILL);                                                  //draw a rectangle
    lcd.drawRectangle(136,167,170,217,SG_BLACK,SG_UNFILL);                                             //draw a rectangle
    lcd.drawCircle(106,160,15,ligBlue,SG_FILL);                                                        //draw a circle
    lcd.drawCircle(106,160,15,SG_BLACK,SG_UNFILL);                                                     //draw a circle    
    lcd.drawEllipse(195,177,10,15,ligBlue,SG_FILL);                                                    //draw an ellipse
    lcd.drawEllipse(195,177,10,15,SG_BLACK,SG_UNFILL);                                                 //draw an ellipse
    
    //draw left tree
    lcd.drawRectangle(25,157,45,218,brown,SG_FILL);                                                    //draw a rectangle
    lcd.drawRectangle(25,157,45,218,SG_BLACK,SG_UNFILL);                                               //draw a rectangle       
    lcd.drawEllipse(35,120,35,40,SG_GREEN,SG_FILL);                                                    //draw an ellipse
    lcd.drawEllipse(35,120,35,40,SG_BLACK,SG_UNFILL);                                                  //draw an ellipse
    //draw right tree
    lcd.drawRectangle(270,167,283,218,brown,SG_FILL);                                                  //draw a rectangle
    lcd.drawRectangle(270,167,283,218,SG_BLACK,SG_UNFILL);                                             //draw a rectangle       
    lcd.drawCircle(277,134,35,SG_GREEN,SG_FILL);                                                       //draw a circle
    lcd.drawCircle(277,134,35,SG_BLACK,SG_UNFILL);                                                     //draw a circle  
    
    //draw grass
    lcd.drawLine(5,218,314,218,SG_GREEN);                                                              //draw a line    
    
    //loop forever
    while(1);
}
