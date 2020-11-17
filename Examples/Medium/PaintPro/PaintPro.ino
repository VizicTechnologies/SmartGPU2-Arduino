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

char pixelArray[3];                     //Array to store the RGB888 pixel obtained with memoryRead()


/**************************************************/
//Funcion to convert a 3 byte array to an int RGB565
int RGB888ToRGB565(char pixBuffer[]){   //get an array of 3 bytes( red, green, blue), and convert them to RGB565 returned in an int
  unsigned char R,G,B;
  unsigned int col;
  unsigned long colour;
  
  R=pixBuffer[0];
  G=pixBuffer[1];
  B=pixBuffer[2]; 
  ((unsigned char *) &colour)[1]=(R & 0xF8);
  R=G;
  G=G>>5;
  ((unsigned char *) &colour)[1]|=G;
  G=(R<<3)& 0xE0;
  ((unsigned char *) &colour)[0]=B;
  ((unsigned char *) &colour)[0]=((unsigned char *) &colour)[0]>>3;  
  ((unsigned char *) &colour)[0]|=G;
  col=colour;
  return col;
}

/************************************************/
/************************************************/
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
  
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
    unsigned char penSize=1;
    SG_COLOUR colour = SG_BLACK;
    char pen[4]={'x','0','1',0x00};         //Array that show the current penSize
    SG_NUMBEROFBYTES nb;
 
    lcd.baudChange(SG_BAUD6);               //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!
    
    //Load paint design
    lcd.imageBMPSD(0,0,"paint");    
    //strings config
    lcd.setTextColour(SG_GREEN);
    lcd.setTextSize(SG_FONT0);
    lcd.setTextBackFill(SG_FILLED);     
    lcd.string(7,54,48,65,"Erase",&nb);    //draw Erase word
    lcd.string(77,54,110,65,pen,&nb);      //draw penSize 
  
    while(1){   //Start the Paint application    
      while(!lcd.touchScreen(&point));                      //Wait for a touch on the screen to do something      
      //Once we get a touch somewhere on the screen:
      if((point.y-penSize)<67){                             //the touch was on the menu
        if(point.x<45){                                     //touch on erase circle
          lcd.drawRectangle(0,67,319,239,SG_WHITE,SG_FILL); //Draw a white rectangle on drawing area
        }else if(point.x<75){                               //touch to select the eraser
          colour=SG_WHITE;
          lcd.drawCircle(25,34,14,colour,SG_FILL);          //draw WHITE colour circle on top left corner           
        }else if(point.x<108){                              //touch to change pen Size 
          penSize=penSize*2;                                //double the penSize
          if(penSize==16){                                  //maximum pen size = 8, if we reach 16 we set to 1.
            penSize=1;
          }          
          pen[1]=(penSize/10)+0x30;                         //get the tens of penSize and convert them to ascii
          pen[2]=(penSize%10)+0x30;                         //get the ones of penSize and convert them to ascii
          lcd.string(77,54,110,65,pen,&nb);                 //draw penSize 
          delay(500);                                       //delay to avoid fast penSize changing            
        }else if(point.x<312 & point.y>20 & point.y<59){//touch on the colours bar                  
          lcd.getImageFromMemory(point.x,point.y,point.x,point.y,pixelArray);  //assign new colour based on touch coordinates and memory read, this function return a 24 bit pixel array, 
          colour=RGB888ToRGB565(pixelArray);
          lcd.drawCircle(25,34,14,colour,SG_FILL);          //draw new selected colour on top left corner           
        }                
      }else{                                                //Touch on drawing area
        lcd.drawCircle(point.x,point.y,penSize,colour,SG_FILL);                    //Draw
      }
    }
}
