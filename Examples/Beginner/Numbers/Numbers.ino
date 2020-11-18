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

#include <SMARTGPU2.h>     //include the SMARTGPU2 library!

SMARTGPU2 lcd;             //create our object called LCD

/********************************************************/
/********************************************************/
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU2 support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU2 support
  lcd.start(); //initialize the SMARTGPU2 processor
}

/********************************************************/
/********************************************************/
/********************************************************/
/********************************************************/
void loop() { //main loop
  float floatNumber=0;
  int intNumber=0;
  
  lcd.baudChange(SG_BAUD6); //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!
  
  //config strings
  lcd.setTextColour(SG_YELLOW);    
  lcd.setTextSize(SG_FONT3); 
  lcd.setTextBackFill(SG_FILLED);

  while(1){
    //print numbers
    lcd.printNumber(0,   0, 514.65);   
    lcd.printNumber(0,  25, 0.0254);   
    lcd.printNumber(0,  50, 46235);   
    lcd.printNumber(0,  75, -6354.85);   
    lcd.printNumber(0, 100, -0.4158);     
    lcd.printNumber(0, 125, 1234567890);     
  
    //print int numbers
    for(intNumber=1000; intNumber<=9000 ; intNumber++){ 
      lcd.printNumber(0, 150, intNumber); 
    }
    
    //print float numbers
    for(floatNumber=1000; floatNumber<=3000 ; floatNumber+= 0.1){ 
      lcd.printNumber(0, 175, floatNumber); 
    }
    
    delay(5000);
    lcd.erase();  
  }
}
