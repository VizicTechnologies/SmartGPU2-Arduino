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

/************************************************/
/************************************************/
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU2 support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU2 support
  lcd.start(); //initialize the SMARTGPU2 processor
  
  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);
}


/************************************************/
/************************************************/
/************************************************/
/************************************************/
void loop() { //main loop
  SG_POINT point;
  SG_NUMBEROFBYTES nb;
  SG_REPLY reply;
  SG_FILERESULT res;
  char pic;
  
  lcd.string(10,10,LCD_WIDTH-10,LCD_HEIGHT-10,"PHOTOFRAME DEMO\nBe sure to insert uSD with loaded .bmp images",&nb);
  
  delay(3000);
  
  res=lcd.SDFopenDir("BMP Images");             //Open the BMP Images that contains the images

  //Throw error message if could't read microSD card
  if(res != SG_F_OK){
    lcd.string(10,50,LCD_WIDTH-10,LCD_HEIGHT-10,"Not inserted uSD card!",&nb);
    while(1);
  }
    
  while(1){   //Loop forever in the slide show!
    reply=lcd.imageBMPSD(0,0,imagesOnSDCard[pic]);     //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.imageBMPSD(3,LCD_HEIGHT-20,"previous");        //Load the previous icon        
    lcd.imageBMPSD(LCD_WIDTH-20,LCD_HEIGHT-20,"next"); //Load the next icon

    //Throw error message if could't found image or no microSD card
    if(reply != SG_OK){
      lcd.string(10,10,LCD_WIDTH,LCD_HEIGHT,"NO .bmp image found...",&nb);
    }
    delay(100);                                 //A little delay to avoid fast image changing
    while(lcd.touchScreen(&point)==SG_INVALID); //Wait for a touch on the screen to show next or previous picture
    
    //check if we go to the next image, or to the previous one
    if(point.x>(LCD_WIDTH/2)){                  //if the received touch was on the right middle of the screen we advance the image, else we decrease and go to previous image
      pic++;                                    //decrease image selector
      if(pic>7){                                //if we reach the position of the last image, we restart to image 0
        pic=0;                 
      }        
    }else{
      pic--;    
      if(pic<0){                                //if we reach the position of the first image, we move to image 7
        pic=7;  
      }    
    }   
  }
}
