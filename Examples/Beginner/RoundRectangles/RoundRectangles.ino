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
void loop() { //main loop draw random colour and size rectangles
  SG_POINT p1, p2;
  SG_COLOUR colour;
  SG_RADIUS radius;
  SG_FILLGEOM fill;

  lcd.baudChange(SG_BAUD6);         //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!

  randomSeed(12345);    
    
  while(1){//forever
    p1.x=random(0,LCD_WIDTH);       //get a random number 0-319
    p1.y=random(0,LCD_HEIGHT);      //get a random number 0-239
    p2.x=random(0,LCD_WIDTH);       //get a random number 0-319
    p2.y=random(0,LCD_HEIGHT);      //get a random number 0-239     
    radius=random(1,40);            //get a random number 1-39
    colour=random(0,65536);         //get a random number 0-65535
    fill=(SG_FILLGEOM)random(0,2);  //get a random number 0-1           
      
    //draw the round rectangle
    lcd.drawRoundRect(p1.x,p1.y,p2.x,p2.y,radius,colour,fill); //draw a round rectangle
  }
}
