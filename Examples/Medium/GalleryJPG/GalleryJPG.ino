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
  SG_POINT point;
  char pic=0;
  unsigned char i=0;
  SG_FILERESULT res;
  SG_NUMBEROFBYTES nb;

  lcd.string(10,10,LCD_WIDTH-10,LCD_HEIGHT-10,"Gallery JPG DEMO\nBe sure to insert uSD with loaded .jpg images",&nb);
  
  delay(3000);

  lcd.erase();

  lcd.SDFopenDir("JPG Images");            // Open the JPG Images that contains the images

  //Throw error message if could't read microSD card
  if(res != SG_F_OK){
    lcd.string(10,50,LCD_WIDTH-10,LCD_HEIGHT-10,"Not inserted uSD card!",&nb);
    while(1);
  }

  //strings config
  lcd.setTextColour(SG_GREEN);
  lcd.setTextSize(SG_FONT1);  
  
  while(1){   //Loop forever in the slide show!
    for(i=0;i<4;i++){
      lcd.imageJPGSD(i*(LCD_WIDTH/4),(LCD_HEIGHT/8),SG_SCALE1_4,imagesOnSDCard[i]);     //Load image from SD card            
    }
    for(i=0;i<4;i++){
      lcd.imageJPGSD(i*(LCD_WIDTH/4),(LCD_HEIGHT/8)*5,SG_SCALE1_4,imagesOnSDCard[i+4]); //Load image from SD card            
    }
    
    lcd.string(LCD_WIDTH/5,10,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch image to load!",&nb);
    while(lcd.touchScreen(&point)==SG_INVALID);  //Wait for a touch on the screen to show next or previous picture    
    lcd.erase();
    
    if(point.y<(LCD_HEIGHT/2)){    //touch on upper part
       lcd.imageJPGSD(0,0,SG_SCALE1_1,imagesOnSDCard[point.x/(LCD_WIDTH/4)]); //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0        
    }else{                       //touch on upper part
       lcd.imageJPGSD(0,0,SG_SCALE1_1,imagesOnSDCard[(point.x/(LCD_WIDTH/4))+4]); //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0                    
    }
    
    lcd.string(LCD_WIDTH/5,LCD_HEIGHT-25,LCD_WIDTH-1,LCD_HEIGHT-1,"Touch image to exit!",&nb);
    delay(100);
    while(lcd.touchScreen(&point)==SG_INVALID);  //Wait for a touch on the screen to show next or previous picture    
    lcd.erase();
  }
}
