/*********************************************************
 * VIZIC TECHNOLOGIES. COPYRIGHT 2020.
 * THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
 * VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
 * ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
 * LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
 * ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
 * ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
 * OR OTHER SIMILAR COSTS.
 *********************************************************/

/********************************************************
 * IMPORTANT : This Example is created for the Arduino 1.0 Software IDE
 * Be sure that the video files contained in the "Videos" directory, are small enough in resolution (320x240, 480x320, etc)
 * to fit in your selected SmartGPU2 board under the LANDSCAPE mode 
 ********************************************************/

#include <SMARTGPU2.h>       //include the SMARTGPU2 library!

SMARTGPU2 lcd;               //create our object called LCD      

SG_AXIS LCD_WIDTH, LCD_HEIGHT;  //Variables to handle the screen resolution
SG_AXIS MAX_X, MAX_Y;

char videosOnSDCard[20]={0}; //array containing the names of the different called videos, up to 20 characters including .vid extension

/**************************************************/
//looks in the current directory for .vid files and returns the name without .vid extension in the *fileName given array
void findNextVideoFile(char *fileName){
  SG_NUMBEROFBYTES nb;
  static unsigned int i=0;
  char *pch;
  while(1){
    if(lcd.SDFgetFileName(i++,fileName) == SG_F_INVALID_PARAMETER) i=0; //if the function throws invalid parameter, then reset i
    pch=strstr(fileName,".vid"); //find the .vid extension in the name
    if(pch != 0){                //if .vid extension is present in the name
      strncpy(pch,0x00,1);       //cut/replace the .vid extension for the NULL 0x00 character
      lcd.erase();
      return;                    //exit
    }                            //if no .vid extension is found, then continue with the while(1) loop
    lcd.string(0,0,MAX_X,MAX_Y,"No Video File Found",&nb);
  }
}

/**************************************************/
//function that draws buttons and current progress bar - used by media
void drawButtonsAndProgress(unsigned long currFrame, unsigned long totFrames){
  lcd.objButton(0,LCD_HEIGHT-40,(LCD_WIDTH/2)-1,LCD_HEIGHT-10,SG_DESELECTED,"Continue");
  lcd.objButton((LCD_WIDTH/2)+1,LCD_HEIGHT-40,MAX_X,LCD_HEIGHT-10,SG_DESELECTED,"Next...");
  lcd.drawRectangle(0,LCD_HEIGHT-80,(currFrame*MAX_X)/(totFrames),LCD_HEIGHT-60,SG_RED,SG_FILL);                 //scale currentFrame value to 0-LCD_WIDTH pixels
  lcd.drawRectangle((currFrame*MAX_X)/(totFrames),LCD_HEIGHT-80,MAX_X,LCD_HEIGHT-60,SG_BLACK,SG_FILL); //scale currentFrame value to 0-LCD_WIDTH pixels 
}

/**************************************************/
/**************************************************/
//Initial setup
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU2 support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU2 support
  lcd.start(); //initialize the SMARTGPU2 processor
  
  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);

  MAX_X = LCD_WIDTH-1;
  MAX_Y = LCD_HEIGHT-1;
}

/**************************************************/
/****************** MAIN LOOP *********************/
/**************************************************/
/**************************************************/
void loop() { //main loop
  //structures and variables
  SG_POINT point;
  SG_ICON icon;
  SG_VIDDATA vidData;
  SG_NUMBEROFBYTES nb;
  unsigned long currentFrame=0, currentSecond=0;
  unsigned int seconds;

  lcd.baudChange(SG_BAUD5);                                                     //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!
  
  lcd.initDACAudio(SG_ENABLE);
  lcd.audioBoost(SG_ENABLE);
  
  lcd.SDFopenDir("Videos");                                                     //Open the "Videos" foldet that contains the .vid files

  while(1){ 
    lcd.erase();    
    findNextVideoFile(videosOnSDCard);
    lcd.string(0,0,MAX_X,MAX_Y, "Trying to allocate:", &nb);
    lcd.string(0,20,MAX_X,MAX_Y, videosOnSDCard, &nb);
   
    if(lcd.allocateVideoSD(videosOnSDCard, &vidData) == SG_OK){                 //if the found video is correctly allocated
      currentFrame=0; currentSecond=0;                                          //reset variables
      //print video statistics
      lcd.string(0,40,MAX_X,MAX_Y, "Video Allocated", &nb);  
      lcd.string(0,60,MAX_X,MAX_Y, "Video Size", &nb);        
      lcd.printNumber(80,60,vidData.width);
      lcd.printNumber(120,60,vidData.height);    
      lcd.string(0,80,MAX_X,MAX_Y, "Frames per Second", &nb);        
      lcd.printNumber(120,80,vidData.framesPerSec);        
      lcd.string(0,100,MAX_X,MAX_Y, "Total Frames", &nb);            
      lcd.printNumber(120,100,vidData.totalFrames);   
      delay(3000); 
      //start playback with audio if any
      lcd.playWAVFile(videosOnSDCard,&seconds);                                 //open audio if any, must be named the same as the video expept for the .wav extension
      
      while(1){
        if(lcd.playVideoSD(0,0,vidData.framesPerSec)!=SG_OK) break;             //play video for 1 second(this equal the obtained frames per second parameter) break while(1) if error
        currentSecond++; currentFrame+=vidData.framesPerSec;                    //advance variables
        if(lcd.touchScreen(&point)==SG_VALID){                                  //check about each ~1 second for a touch, if VALID:
          lcd.pauseWAVFile();                                                   //pause audio
          //draw buttons and progress bar
          drawButtonsAndProgress(currentFrame, vidData.totalFrames);
          delay(300);
          while(1){                                                             //loop until touch on any button
            while(lcd.touchScreen(&point)==SG_INVALID || point.y<(LCD_HEIGHT-80)); //while no valid touch or touch outside buttons and progress bar
            //if touch on buttons - exit while(1)..
            if(point.y > (LCD_HEIGHT-40)) break;                                
            //if touch on progress bar, advance file to received touch in progress bar value...
            currentFrame=((unsigned long)point.x * (unsigned long)vidData.totalFrames) / MAX_X; //obtain new current frame value 0-319
            currentFrame= (currentFrame/(unsigned long)vidData.framesPerSec)*((unsigned long)vidData.framesPerSec); //convert currentFrame to a factor of videoData.framesPerSecond
            currentSecond=(currentFrame/(unsigned long)vidData.framesPerSec);
            lcd.setFrameVideoSD(currentFrame);                                  //set new obtained frame
            lcd.playVideoSD(0,0,1);                                             //show new frame
            lcd.advanceWAVFile(currentSecond);                                  //set new value to audio file
            //update buttons and progress bar
            drawButtonsAndProgress(currentFrame, vidData.totalFrames);
            delay(50);
          }
          //when previous touch was on buttons, process the touch:
          if(point.x < (LCD_WIDTH/2)){                                          //touch on continue button(left side of the screen)
            lcd.objButton(0,LCD_HEIGHT-40,(LCD_WIDTH/2)-1,LCD_HEIGHT-10,SG_SELECTED,"Continue");    
            delay(300);
            lcd.erase();
            lcd.pauseWAVFile();                                                 //resume audio and continue playback
          }else{                                                                //touch on return button(right side of the screen
            lcd.objButton((LCD_WIDTH/2)+1,LCD_HEIGHT-40,MAX_X,LCD_HEIGHT-10,SG_SELECTED,"Next...");
            lcd.stopWAVFile();
            delay(300);
            break;                                                              //exit playback, go to next video...
          }
        }
      }
    }else{
      lcd.string(0,40,MAX_X,MAX_Y, "Video NOT Allocated - Error \n\r Jump to Next Video...", &nb);    
      delay(3000);
    }
  }
}
