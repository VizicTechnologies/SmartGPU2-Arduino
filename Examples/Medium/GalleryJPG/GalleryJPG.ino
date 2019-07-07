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

char imagesOnSDCard[8][30]={"Penguins","Koala","Hydrangeas","Light House","Jellyfish","Tulips","Desert","Flower"}; //array containing the names of the different called images

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
  char pic=0;
  unsigned char i=0;

  lcd.baudChange(BAUD6);                   // Set a fast baud!, always that we use touch functions is recommended to use fast baud rates

  lcd.SDFopenDir("JPG Images");            // Open the JPG Images that contains the images
  
  //strings config
  lcd.setTextColour(GREEN);
  lcd.setTextSize(FONT1);  
  
  while(1){   //Loop forever in the slide show!
    for(i=0;i<4;i++){
      lcd.imageJPGSD(i*(LCD_WIDTH/4),(LCD_HEIGHT/8),SCALE1_4,imagesOnSDCard[i]);     //Load image from SD card            
    }
    for(i=0;i<4;i++){
      lcd.imageJPGSD(i*(LCD_WIDTH/4),(LCD_HEIGHT/8)*5,SCALE1_4,imagesOnSDCard[i+4]); //Load image from SD card            
    }
    
    lcd.string(LCD_WIDTH/5,10,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch image to load!",0);
    while(lcd.touchScreen(&point)==INVALID);  //Wait for a touch on the screen to show next or previous picture    
    lcd.erase();
    
    if(point.y<(LCD_HEIGHT/2)){    //touch on upper part
       lcd.imageJPGSD(0,0,SCALE1_1,imagesOnSDCard[point.x/(LCD_WIDTH/4)]); //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0        
    }else{                       //touch on upper part
       lcd.imageJPGSD(0,0,SCALE1_1,imagesOnSDCard[(point.x/(LCD_WIDTH/4))+4]); //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0                    
    }
    
    lcd.string(LCD_WIDTH/5,LCD_HEIGHT-25,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch image to exit!",0);
    while(lcd.touchScreen(&point)==INVALID);  //Wait for a touch on the screen to show next or previous picture    
    lcd.erase();
  }
}
