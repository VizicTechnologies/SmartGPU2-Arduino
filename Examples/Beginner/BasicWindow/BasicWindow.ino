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

/*
  This sketch demostrates the difference of a manual draw window and an internal SmartGPU2 object window
*/

#include <SMARTGPU2.h>     //include the SMARTGPU2 library!

SMARTGPU2 lcd;             //create our object called LCD

//FUNCTION THAT DRAWS A MANUAL WINDOW
unsigned char createWindow(SG_AXIS x1, SG_AXIS y1, SG_AXIS x2, SG_AXIS y2, SG_COLOUR top, SG_COLOUR text, char *names){
  SG_AXIS aux;
  SG_NUMBEROFBYTES nb;
  
  lcd.setTextSize(SG_FONT3);
  lcd.drawRectangle(x1,y1,x2,y2,0xDEFB,SG_FILL); //draw grey 0xDEFB back
  aux = ((y2-y1) * 20) / 100;
  if(aux<10) aux=10;
  lcd.drawGradientRect(x1,y1,x2-1,y1+aux,top,SG_WHITE,SG_VERTICAL); //draw top
  lcd.drawLine(x1,y1,x2,y1,SG_WHITE);
  lcd.drawLine(x1,y2,x2,y2,SG_BLACK);  
  lcd.drawLine(x1,y1,x1,y2,SG_WHITE);  
  lcd.drawLine(x2,y1,x2,y2,SG_BLACK);  
  lcd.string(x1+5,y1+5,x2,y2,names,&nb);
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
    
  lcd.setEraseBackColour(SG_GREEN); //set the erase background colour  

  while(1){//forever
    //erase screen
    lcd.erase();    
    //draw the manual window 
    createWindow(20,20,300,200,SG_BLUE,SG_WHITE,"window 1");
    //wait
    delay(3000);
    
    //erase screen
    lcd.erase();    
    //draw the internal SmartGPU2 object window     
    lcd.objWindow(20,20,300,200,SG_FONT2,SG_SELECTEDGRAY,"window 1");
    //wait
    delay(3000);
  }
}
