/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2014.
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

/*
  This sketch demostrates the difference of a manual draw window and an internal SmartGPU2 object window
*/

#include <SMARTGPU2.h>     //include the SMARTGPU2 library!

SMARTGPU2 lcd;             //create our object called LCD

//FUNCTION THAT DRAWS A MANUAL WINDOW
unsigned char createWindow(AXIS x1, AXIS y1, AXIS x2, AXIS y2, COLOUR top, COLOUR text, char *name){
  AXIS aux;
  
  lcd.setTextSize(FONT3);
  lcd.drawRectangle(x1,y1,x2,y2,0xDEFB,FILL); //draw grey 0xDEFB back
  aux = ((y2-y1) * 20) / 100;
  if(aux<10) aux=10;
  lcd.drawGradientRect(x1,y1,x2-1,y1+aux,top,WHITE,VERTICAL); //draw top
  lcd.drawLine(x1,y1,x2,y1,WHITE);
  lcd.drawLine(x1,y2,x2,y2,BLACK);  
  lcd.drawLine(x1,y1,x1,y2,WHITE);  
  lcd.drawLine(x2,y1,x2,y2,BLACK);  
  lcd.string(x1+5,y1+5,x2,y2,name,0);
}

/*********************************************************/
/*********************************************************/
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU2 support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU2 support
  lcd.start(); //initialize the SMARTGPU2 processor
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/
void loop() { //main loop draw random colour and size lines
    
  lcd.setEraseBackColour(GREEN); //set the erase background colour  

  while(1){//forever
    //erase screen
    lcd.erase();    
    //draw the manual window 
    createWindow(20,20,300,200,BLUE,WHITE,"window 1");
    //wait
    delay(3000);
    
    //erase screen
    lcd.erase();    
    //draw the internal SmartGPU2 object window     
    lcd.objWindow(20,20,300,200,FONT2,SELECTEDGRAY,"window 1");
    //wait
    delay(3000);
  }
}
