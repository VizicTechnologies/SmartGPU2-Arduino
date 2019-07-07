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

char message[]="Hello World";

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
    delay(1000);                                                                                     //wait some time 
    lcd.drawLine(50,50,150,200,WHITE);                                                               //draw a line
    delay(1000);
    lcd.drawRectangle(10,10,200,180,RED,UNFILL);                                                     //draw a rectangle
    delay(1000);
    lcd.drawCircle(160,120,50,GREEN,UNFILL);                                                         //draw a circle
    delay(1000);
    lcd.drawTriangle(15,15,200,210,180,70,BLUE,UNFILL);                                              //draw a triangle
    delay(1000);    
    //config strings
    lcd.setTextColour(YELLOW);
    lcd.setTextSize(FONT2);
    lcd.string(10,10,300,220,"This is the string test \nfor SMARTGPU2 processori",0);                 //write a string on the screen
    delay(2000);    
    //config strings
    lcd.setTextColour(GREEN);
    lcd.setTextSize(FONT3);
    lcd.string(10,80,300,220,message,0);                                                             //write the string previously created (char message[]="Hello World";)
    delay(1000);
    //config strings
    lcd.setTextColour(MAGENTA);    
    lcd.putLetter(100,150,'E',0);                                                                    //write a single letter 'E'
    delay(1000);
    lcd.putPixel(300,200,CYAN);                                                                      //draw a pixel
    delay(3000);
    lcd.imageBMPSD(0,0,"hydrangeas");                                                                //call the image "hydrangeas.bmp" previously stored on the micro SD card
    delay(1000);    
    lcd.stringSD(5,50,300,230,BEGINNING,ALLCONTENTS,"text file 1",0);                                //call the text file "text file 1.txt" previously stored on the micro SD card
    delay(2000);   
    lcd.drawRectangle(10,10,200,180,RED,FILL);                                                       //draw a rectangle
    delay(1000);
    lcd.drawCircle(160,120,50,GREEN,FILL);                                                           //draw a circle
    delay(1000);
    lcd.drawTriangle(15,15,200,210,180,70,BLUE,FILL);                                                //draw a triangle 
    delay(3000);
    lcd.erase();                                                                                     //erase screen
}
