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
void loop() { //main loop draw random colour, size and fill Arcs
    POINT point;
    RADIUS radiusx, radiusy;
    COLOUR colour;
    FILLGEOM fill;
    unsigned int quadrant;
    
    lcd.baudChange(BAUD6);           //for fast drawing we need a big baudRate
    
    while(1){//forever
      randomSeed(random(0,65536));   //set different seeds to obtain a good random number 
      point.x=random(0,LCD_WIDTH);   //get a random number 0-319
      point.y=random(0,LCD_HEIGHT);  //get a random number 0-239
      radiusx=random(5,101);         //get a random number 5-100
      radiusy=random(5,101);         //get a random number 5-100
      quadrant=random(1,5);          //get a random number 1-4
      colour=random(0,65536);        //get a random number 0-65535
      fill=(FILLGEOM)random(0,2);    //get a random number 0-1
      
      //draw the Arc
      if(lcd.drawArc(point.x, point.y, radiusx, radiusy, (ARCQUADRANT)quadrant, colour, fill) != 'O'){  //draw an Arc
        while(1);                    //loop forever if different than 'O'--OK
      }      
    }
}
