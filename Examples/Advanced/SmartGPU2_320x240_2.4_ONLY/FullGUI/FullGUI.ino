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

SG_AXIS MAX_X_PORTRAIT, MAX_Y_PORTRAIT, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE;

//defines for GUI
#define HALFX       LCD_HEIGHT/2
#define HALFY       LCD_WIDTH/2
#define ICONSPACING (((MAX_X_PORTRAIT+1)-(((MAX_X_PORTRAIT+1)/50)*50))/(((MAX_X_PORTRAIT+1)/50)+1))

//declare our structures POINT and ICON
SG_POINT point;
SG_ICON icon;

//Global variables
//Start time: hours = 2, minutes = 19, seconds = 33;
int clockTime= (2*(60*60)) + (19*60) + (33); //In seconds
       
//array to store file names 25 characters max, also used as working file array
char name[25];

//Array with the names of the icons under "FullGUI/Ics" folder, names of 25 characters max
const char iconNames[][25]={"backlight","calculator","clock","games","maps","media","notes","photos","wifi","settings","calls","music","wall"};

//array used by games
#define MOLEHOLE 3        //position of the array where mole hole image is contained
#define HITMOLE  4        //position of the array where hit mole image is contained
#define MISSMOLE 5        //position of the array where miss mole image is contained
const char moleType[6][9]={"MoleHap","MoleSee","MoleBad","MoleHole","MolePun","MoleMiss"}; //array containing the names of the different called images    

//General/Miscellaneous Functions
/**************************************************/
/**************************************************/
/**************************************************/
unsigned char getTouchIconMainMenu(void){
  unsigned int icPress;  

  while(lcd.touchScreen(&point)==SG_INVALID);      //wait for a touch  
  //PROCEDURE TO DIVIDE THE TOUCHSCREEN AREA IN X x Y EQUAL PARTS------------------------------------
  //Divide screen into X equal horizontal parts for icons
  icPress= (point.x/((MAX_X_PORTRAIT+1)/((MAX_X_PORTRAIT+1)/50)))+1; //LCD_HEIGHT    
  //Divide Screen into Y equal vertical parts for icons
  icPress = icPress+(((point.y-20)/((MAX_Y_PORTRAIT+1)/((MAX_Y_PORTRAIT+1)/50)))*((MAX_X_PORTRAIT+1)/50)); //LCD_WIDTH
  //------------------------------------------------------------------------------------------------- 
  return icPress; //return decoded coordinate from 1 to X icons
}

//obtain from EEPROM FLASH memory the name of the current stored wallpaper on the "name" array
void getCurrentWallFromEEPROM(void){
  lcd.fillBuffFromEEPROMPage(SG_PAGE0); //copy SG_PAGE0 to EEPROM RAM buffer
  lcd.readEEPROMBuff(name,0,14,0);      //read 14 bytes of the EEPROM RAM buffer to name array, wallpapers must not exceed 14 chars in name lenght
  if(strstr(name, 0x00) != 0x00){       //find a null character in name, if not find, add the 0x00 NULL character
    name[0] = 0x00;
  }
}

//save current contents of "name" array on EEPROM SG_PAGE0 at address 0x0000
void saveWallpaperToEEPROM(void){
  lcd.initClearEEPROMBuff();                     //Initialize EEPROM RAM Buffer
  lcd.writeEEPROMBuff(name,0,sizeof(name),0);    //write all the contents of "name" array to EEPROM RAM Buffer
  lcd.eraseEEPROMPage(SG_PAGE0);                 //erase all contents on the PAGE0
  lcd.saveBuffToEEPROMPage(SG_PAGE0);            //now save to EEPROM PAGE0 the contents of the EEPROM RAM Buffer(the name array + 0xFFs)
}

/**************************************************/
void drawHeader(char *text){
  unsigned int batteryPercentage = 65;                     //can be global variable to display the real battery consumption
  //draw header and text
  lcd.drawRectangle(0,0,MAX_X_PORTRAIT,13,SG_BLACK,SG_FILL);     //draw upper bar
  lcd.setTextSize(SG_FONT0);
  lcd.setTextColour(SG_WHITE);
  lcd.setTextBackFill(SG_TRANS);
  lcd.string(2,0,MAX_X_PORTRAIT,20,"Vizic",0);             //draw Vizic string
  lcd.string((LCD_HEIGHT/2)-35,0,MAX_X_PORTRAIT,20,text,0); //draw string
  //draw battery icon according to the battery percentage variable
  lcd.drawRectangle(MAX_X_PORTRAIT-25,0,(MAX_X_PORTRAIT-25)+((batteryPercentage*15)/100),10,SG_GREEN,SG_FILL);
  lcd.drawRectangle(MAX_X_PORTRAIT-25,0,MAX_X_PORTRAIT-10,10,SG_WHITE,SG_UNFILL);
  lcd.drawRectangle(MAX_X_PORTRAIT-10,4,MAX_X_PORTRAIT-8,6,SG_WHITE,SG_FILL);  
}

//Cuts the .ext and updates the name
void cutFileExtension(char *name, char *ext){
  char *pch;
  pch=strstr(name,ext);        //find the .ext extension to the name
  strncpy(pch,0x00,1);         //cut/replace the .ext extension for the NULL 0x00 character      
}

 //function used by music
void drawControlRR(SG_ACTIVE state){
  //draw button
  lcd.objButton(0,LCD_WIDTH-55,(LCD_HEIGHT/3)-1,LCD_WIDTH-5,state,"");
  //draw symbol
  lcd.drawTriangle(0+10,(LCD_WIDTH-55)+(((LCD_WIDTH-5)-(LCD_WIDTH-55))/2),0+((LCD_HEIGHT/6)-1),(LCD_WIDTH-55)+10,0+((LCD_HEIGHT/6)-1),(LCD_WIDTH-5)-10,SG_BLACK,SG_FILL);
  lcd.drawTriangle(0+((LCD_HEIGHT/6)-1),(LCD_WIDTH-55)+(((LCD_WIDTH-5)-(LCD_WIDTH-55))/2),0+((LCD_HEIGHT/3)-1)-10,(LCD_WIDTH-55)+10,0+((LCD_HEIGHT/3)-1)-10,(LCD_WIDTH-5)-10,SG_BLACK,SG_FILL);
}

//function used by music
void drawControlFF(SG_ACTIVE state){
  //draw button  
  lcd.objButton(((LCD_HEIGHT/3)*2),LCD_WIDTH-55,MAX_X_PORTRAIT,LCD_WIDTH-5,state,"");    
  //draw symbol
  lcd.drawTriangle(LCD_HEIGHT-(((LCD_HEIGHT/3)-1)-10),(LCD_WIDTH-55)+10,LCD_HEIGHT-(((LCD_HEIGHT/3)-1)-10),(LCD_WIDTH-5)-10,LCD_HEIGHT-((LCD_HEIGHT/6)-1),(LCD_WIDTH-55)+(((LCD_WIDTH-5)-(LCD_WIDTH-55))/2),SG_BLACK,SG_FILL);  
  lcd.drawTriangle(LCD_HEIGHT-((LCD_HEIGHT/6)-1),(LCD_WIDTH-55)+10,LCD_HEIGHT-((LCD_HEIGHT/6)-1),(LCD_WIDTH-5)-10,LCD_HEIGHT-10,(LCD_WIDTH-55)+(((LCD_WIDTH-5)-(LCD_WIDTH-55))/2),SG_BLACK,SG_FILL);  
} 

//function used by music
void drawControlPLAY(char symbol){
  //draw button  
  lcd.objButton((LCD_HEIGHT/3),LCD_WIDTH-55,((LCD_HEIGHT/3)*2)-1,LCD_WIDTH-5,SG_SELECTED,"");  
  //draw symbol
  if(symbol){      //PLAY
    lcd.drawTriangle((LCD_HEIGHT/3)+10,(LCD_WIDTH-55)+10,(LCD_HEIGHT/3)+10,(LCD_WIDTH-5)-10,((LCD_HEIGHT/3)*2)-10,(LCD_WIDTH-55)+(((LCD_WIDTH-5)-(LCD_WIDTH-55))/2),SG_BLACK,SG_FILL);
  }else{           //PAUSE
    lcd.drawRectangle((LCD_HEIGHT/3)+10,(LCD_WIDTH-55)+10,(LCD_HEIGHT/3)+(LCD_HEIGHT/8),(LCD_WIDTH-5)-10,SG_BLACK,SG_FILL);
    lcd.drawRectangle(((LCD_HEIGHT/3)*2)-(LCD_HEIGHT/8),(LCD_WIDTH-55)+10,((LCD_HEIGHT/3)*2)-10,(LCD_WIDTH-5)-10,SG_BLACK,SG_FILL);
  }
}

//function that draws buttons and current progress bar - used by media
void drawButtonsAndProgress(unsigned long currFrame, unsigned long totFrames){
  lcd.objButton(0,LCD_HEIGHT-40,(LCD_WIDTH/2)-1,LCD_HEIGHT-10,SG_DESELECTED,"Continue");
  lcd.objButton((LCD_WIDTH/2)+1,LCD_HEIGHT-40,MAX_X_LANDSCAPE,LCD_HEIGHT-10,SG_DESELECTED,"Return...");
  lcd.drawRectangle(0,(LCD_WIDTH/2)+10,(currFrame*MAX_X_LANDSCAPE)/(totFrames),(LCD_WIDTH/2)+30,SG_RED,SG_FILL);                 //scale currentFrame value to 0-LCD_WIDTH pixels
  lcd.drawRectangle((currFrame*MAX_X_LANDSCAPE)/(totFrames),(LCD_WIDTH/2)+10,MAX_X_LANDSCAPE,(LCD_WIDTH/2)+30,SG_BLACK,SG_FILL); //scale currentFrame value to 0-LCD_WIDTH pixels 
}

//Main applications, the next applications are called by the main loop menu
/**************************************************/
/**************************************************/
/**************************************************/
//draws Main Menu
void drawMainMenu(void){  
  unsigned int i=0, j=0, k=0, xJump=ICONSPACING, yJump=20;
  SG_REPLY res;
  char aux[25];

  strcpy(aux,"Wall/");  	                //copy to name the string "Wall/"
  getCurrentWallFromEEPROM();                   //fill global "name" array with the current EEPROM Stored name
  strcat(aux,name);                             //concatenate the currentWall name to "Wall/"
  if(lcd.imageBMPSD(0,0,aux)!=SG_OK) lcd.erase();  //try to draw WallPaper Image, if fail(not Wall set by user), just erase screen
  //now draw all top icons
  lcd.SDFopenDir("Ics");                     //open the folder with the icons
  for(i=0;i<((MAX_Y_PORTRAIT+1)/50);i++){
    for(j=0;j<((MAX_X_PORTRAIT+1)/50);j++){  
      lcd.imageBMPSD(xJump,yJump,(char*)iconNames[k++]);  //try to draw icon;  
      xJump+=50+ICONSPACING;
    }
    xJump=ICONSPACING;
    yJump+=50+ICONSPACING;
  }
  lcd.SDFopenDir("..");                      //return/go up to parent dir one level
  drawHeader("Main Menu");
  delay(350);                                //A little delay to avoid fast image changing   
}

/**************************************************/
void backlight(void){
  static unsigned char currentBacklightValue=100; //0-100
  
  lcd.drawGradientRect(0,0,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,SG_BLACK,SG_MAGENTA,SG_VERTICAL); //draw a fullscreen gradient rectangle
  lcd.setTextSize(SG_FONT3);
  lcd.setTextColour(SG_WHITE);
  lcd.setTextBackFill(SG_TRANS);
  lcd.string((MAX_X_PORTRAIT+1)/6,(MAX_Y_PORTRAIT+1)/4,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,"Brightness Bar",0);
  lcd.objSlider(10,(MAX_Y_PORTRAIT+1)/4,MAX_X_PORTRAIT-10,((MAX_Y_PORTRAIT+1)/4)*2,currentBacklightValue,101,SG_HORIZONTAL);
  lcd.objButton(10,MAX_Y_PORTRAIT-40,MAX_X_PORTRAIT-10,MAX_Y_PORTRAIT-10,SG_DESELECTED,"Return");
  drawHeader("Adjustments:");  
  while(1){
    while(lcd.touchScreen(&point)==SG_INVALID);//wait for a touch on screen to do something
    if((point.x>10) && (point.x<MAX_X_PORTRAIT-10) && (point.y>((MAX_X_PORTRAIT+1)/4)) && (point.y<(((MAX_Y_PORTRAIT+1)/4)*2))){     //if touch inside brightness bar
      currentBacklightValue= ((point.x-10)*100)/(MAX_X_PORTRAIT-10-10);                                                              //scale obtained touch value to 0-100
      lcd.objSlider(10,(MAX_Y_PORTRAIT+1)/4,MAX_X_PORTRAIT-10,((MAX_Y_PORTRAIT+1)/4)*2,currentBacklightValue,101,SG_HORIZONTAL);     //update slider
      lcd.bright(currentBacklightValue);                                                                                             //set new brightness value
      delay(150);
    }
    if(point.y>(MAX_Y_PORTRAIT-40)){                                                                                              //if touch inside return button
      lcd.objButton(10,MAX_Y_PORTRAIT-40,MAX_X_PORTRAIT-10,MAX_Y_PORTRAIT-10,SG_SELECTED,"Return");
      delay(300);
      return;                                                                                                                     //exit function
    }     
  }
}

/**************************************************/
void clocks(void){
  unsigned int hours=4,mins=48,secs=0,i=0;
  unsigned int xs,ys,xm,ym,xh,yh;
  int angleH,angleM,angleS;
  unsigned int handHour=((MAX_X_PORTRAIT+1)/5);//hand size
  unsigned int handMin =handHour+10; //hand size
  unsigned int handSec =handMin+20; //hand size 
  
  lcd.drawGradientRect(0,0,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,SG_BLACK,SG_MAGENTA,SG_VERTICAL); //draw a fullscreen gradient rectangle
  lcd.objButton(10,MAX_Y_PORTRAIT-40,MAX_X_PORTRAIT-10,MAX_Y_PORTRAIT-10,SG_DESELECTED,"Return");
  drawHeader("Clocks:");    
  //drawClock Body
  lcd.drawCircle(HALFX,HALFY,(MAX_X_PORTRAIT+1)/3,SG_BLACK,SG_FILL);
  lcd.drawCircle(HALFX,HALFY,(MAX_X_PORTRAIT+1)/3,SG_WHITE,SG_UNFILL);  
  
  while(1){
    //time update managing
    hours= ((clockTime+(millis()/1000))/(60*60));
    while(hours >= 12){ hours = hours-12; }  // correct if more than 12 hrs
    mins = (((clockTime+(millis()/1000))%(60*60))/60);
    secs = (((clockTime+(millis()/1000))%(60*60))%60);
      
    //Do some Math to get the second point of the clock hands. (first point is always the center of the clock)
    angleS=secs*6;                           //get the current seconds in angle form, a circle have 360 degrees divided by 60 seconds = 6, then we multiply the 6 by the current seconds to get current angle
    xs=(sin((angleS*3.14)/180)) * handSec;   //get X component of the second's hand
    ys=(cos((angleS*3.14)/180)) * handSec;   //get Y component of the second's hand
    angleM=mins*6;                           //get the current minutes in angle form, a circle have 360 degrees divided by 60 minutes = 6, then we multiply the 6 by the current minutes to get current angle
    xm=(sin((angleM*3.14)/180)) * handMin;   //get X component of the minutes's hand
    ym=(cos((angleM*3.14)/180)) * handMin;   //get Y component of the minutes's hand 
    angleH=hours*30;                         //get the current hours in angle form, a circle have 360 degrees divided by 12 hours = 30, then we multiply the 30 by the current hours to get current angle
    xh=(sin((angleH*3.14)/180)) * handHour;  //get X component of the hours's hand
    yh=(cos((angleH*3.14)/180)) * handHour;  //get Y component of the hours's hand
     
    //Draw current time hands  
    lcd.drawLine(HALFX,HALFY,HALFX+xm,HALFY-ym,SG_WHITE); // Draw the minutes hand, first point is the center of the clock, and the second is the point obtained by doing math
    lcd.drawLine(HALFX,HALFY,HALFX+xh,HALFY-yh,SG_WHITE); // Draw the hours hand, first point is the center of the clock, and the second is the point obtained by doing math
    lcd.drawLine(HALFX,HALFY,HALFX+xs,HALFY-ys,SG_RED);   // Draw the seconds hand, first point is the center of the clock, and the second is the point obtained by doing math
    lcd.drawCircle(HALFX,HALFY,3,SG_RED,SG_FILL);         // Draw the center of the second's hand
 
    for(i=0;i<10;i++){                                 //loop for 10 times a delay of 100ms asking for a touch - this gives a total delay of 1 second
      if(lcd.touchScreen(&point)==SG_VALID){           //ask for a touch on screen to do something
        if(point.y>(MAX_Y_PORTRAIT-40)){               //if touch inside return button
          lcd.objButton(10,MAX_Y_PORTRAIT-40,MAX_X_PORTRAIT-10,MAX_Y_PORTRAIT-10,SG_SELECTED,"Return");
          delay(300);
          return; //exit function
        }    
      }
      delay(100);
    }
                  
    //Erase all hands         
    lcd.drawLine(HALFX,HALFY,HALFX+xs,HALFY-ys,SG_BLACK); // Erase Second's hand
    lcd.drawLine(HALFX,HALFY,HALFX+xm,HALFY-ym,SG_BLACK); // Erase Minute's hand
    lcd.drawLine(HALFX,HALFY,HALFX+xh,HALFY-yh,SG_BLACK); // Erase Hour's hand            
  } 
}  

/**************************************************/
void photos(void){
  unsigned int pics=0;
  static unsigned int i=0;                             //static to save last image position even we exit function
  
  lcd.orientation(SG_LANDSCAPE_LEFT);                     //set orientation as landscape
  lcd.setTextColour(SG_WHITE);
  lcd.setTextSize(SG_FONT3);
  lcd.setTextBackFill(SG_TRANS);
  lcd.drawGradientRect(0,0,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,SG_BLACK,SG_MAGENTA,SG_VERTICAL);
  lcd.string((MAX_X_LANDSCAPE+1)/3,(MAX_Y_LANDSCAPE+1)/3,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,"Photo Gallery",0);
  lcd.setTextSize(SG_FONT2);  
  delay(1000);
  lcd.SDFopenDir("Photos");                            //open the folder with the photos
  lcd.SDFgetList(0,&pics);                             //get number of files/Pics under the current folder "Photos"
  
  while(1){  
    lcd.SDFgetFileName(i,name);                        //get the name of the pic file number i
    cutFileExtension(name,".bmp");                     //cut to name the .bmp extension
    lcd.imageBMPSD(0,0,name);                          //Load image from SD card, all images must be full screen so we load them from top left corner X:0,Y:0
    delay(200);                                        //A little delay to avoid fast image changing    
    lcd.string((MAX_X_LANDSCAPE+1)/4,MAX_Y_LANDSCAPE-20,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,"<Tap center to Exit>",0); //Show text
    while(lcd.touchScreen(&point)==SG_INVALID);        //wait for a touch to do something    
    //check if we go to the next image, or to the previous one
    if(point.x>(MAX_X_LANDSCAPE-100)){                 //if the received touch was on the right corner of the screen we advance the image, else we decrease and go to previous image
      i++;                                             //decrease image selector
      if(i>=pics){                                     //if we reach the position of the last image, we restart to image 0
        i=0;                 
      }        
    }
    else if(point.x<100){
      if(i>0){                                         //if we can decrease i
        i--;    
      }else{                                           //if we decrease i will be less than zero, so we move to last image instead
        i=pics-1;  
      }
    }
    else{                                              //touch on center, EXIT      
      break;
    }   
  }
  lcd.SDFopenDir("..");                                //return/go up to parent dir one level
  lcd.orientation(SG_PORTRAIT_LOW);                    //change to portrait mode    
  delay(300);
}

/**************************************************/
void media(){
  unsigned int i=0, row=0, vids=0;
  unsigned long currentFrame=0, currentSecond=0;
  SG_VIDDATA videoData;
  
  lcd.orientation(SG_LANDSCAPE_LEFT);     //set orientation as landscape
  lcd.setTextColour(SG_WHITE);
  lcd.setTextSize(SG_FONT3);
  lcd.setTextBackFill(SG_TRANS);
  lcd.drawGradientRect(0,0,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,SG_BLACK,SG_MAGENTA,SG_VERTICAL);
  lcd.string((MAX_X_LANDSCAPE+1)/3,(MAX_Y_LANDSCAPE+1)/3,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,"Video Player",0);  
  lcd.stopWAVFile();                   //stop current playing song if any   
  delay(1000);
  lcd.SDFopenDir("Videos");            //open the folder with the videos
  lcd.setTextSize(SG_FONT2);

  while(1){
    lcd.drawGradientRect(0,0,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,SG_BLACK,SG_MAGENTA,SG_VERTICAL);
    lcd.string(5,0,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,"Available Videos:      (EXIT)",0);
    i=0; row=1; vids=0;
    while(1){                          //list names
      lcd.SDFgetFileName(i++,name);    //get the name of the vid file number i
      if(name[0]==0x00) break;         //if name is invalid, meand end of files 
      if(strstr(name,".vid")!=0x00){   //if .vid extension is found in the file name: print      
        lcd.objButton(15,(row*30),MAX_X_LANDSCAPE-15,30+(row*30),SG_DESELECTED,name);  row++;
        vids++;  
      }//else ignore name/file
    }
    
    while(lcd.touchScreen(&point)==SG_INVALID); //wait for a touch to perform action
    row=point.y/30;                    //decode touch point by dividing it by 30 (240/8) which gives the 30 pixels spacing between buttons
    if(row==0){                        //touch on header (EXIT);
      lcd.SDFopenDir("..");            //return/go up to parent dir one level
      lcd.orientation(SG_PORTRAIT_LOW);//change to portrait mode     
      delay(300); 
      return;                          //EXIT media()
    }else if(row > vids) continue;     //if touch on invalid row, where no button is present, go to top while(1)
    i=0;
    while(row){ //get name of obtained row
      lcd.SDFgetFileName(i++,name);    //get the name of the vid file number i  
      if(strstr(name,".vid")!=0x00) row--;   //if .vid extension is found in the file name: decrease row variable
    }
    //Try to play video
    cutFileExtension(name,".vid");    //cut to name the .vid extension  
    if(lcd.allocateVideoSD(name,&videoData)!=SG_OK) continue; //try to allocate video, if fail, continue to top while(1)
    //up to here video is successfully allocated..
    currentFrame=0;  currentSecond=0; //reset variables
    lcd.playWAVFile(name,0);          //open audio if any, must be named the same as the video expept for the .extension
    while(1){
      if(lcd.playVideoSD(0,0,videoData.framesPerSec)!=SG_OK) break; //play video for 1 second(this equal the obtained frames per second parameter) break if error
      currentSecond++; currentFrame+=videoData.framesPerSec;
      if(lcd.touchScreen(&point)==SG_VALID){  //check about each ~1 second for a touch, if Valid:
        lcd.pauseWAVFile();           //stop audio
        //draw buttons and progress bar
        drawButtonsAndProgress(currentFrame, videoData.totalFrames);
        delay(300);
        while(1){
          while(lcd.touchScreen(&point)==SG_INVALID || point.y<170); //while no valid touch or touch outside buttons
          if(point.y > 200) break;                              //if touch on buttons, break while(1) and go to next ifs
          //advance file to received touch in progress bar value...
          currentFrame=((unsigned long)point.x * (unsigned long)videoData.totalFrames) / MAX_X_LANDSCAPE; //obtain new current frame value 0-319
          currentFrame= (currentFrame/(unsigned long)videoData.framesPerSec)*((unsigned long)videoData.framesPerSec); //convert currentFrame to a factor of videoData.framesPerSecond
          currentSecond=(currentFrame/(unsigned long)videoData.framesPerSec);
          lcd.setFrameVideoSD(currentFrame);                    //set new obtained frame
          lcd.playVideoSD(0,0,1);                               //show new frame
          lcd.advanceWAVFile(currentSecond);                    //set new value to audio file
          //update buttons and progress bar
          drawButtonsAndProgress(currentFrame, videoData.totalFrames);
          delay(50);
        }
        if(point.x < 160){           //touch on continue button
          lcd.objButton(0,200,159,230,SG_SELECTED,"Continue");
          delay(300);
          lcd.pauseWAVFile();        //resume audio
        }else{                       //touch on return button
          lcd.objButton(161,200,319,230,SG_SELECTED,"Return...");
          lcd.stopWAVFile();
          delay(300);
          break;                     //exit playback        
        }
      }
    }          
  }
}

/**************************************************/
void notes(){
  lcd.imageBMPSD(0,0,"Misc/notes");          //load notes design
  lcd.objButton(10,MAX_Y_PORTRAIT-40,MAX_X_PORTRAIT-10,MAX_Y_PORTRAIT-10,SG_DESELECTED,"Return");
  drawHeader("Adjustments:");
  delay(200);                                //A little delay to avoid fast image changing

  while(1){    
    while(lcd.touchScreen(&point)==SG_INVALID); //wait for a touch to do something    
    if(point.y<65){                          //Touch on upper Icons
      //clear note block
      lcd.imageBMPSD(0,0,"Misc/notes");      //load notes design
      lcd.objButton(10,MAX_Y_PORTRAIT-40,MAX_X_PORTRAIT-10,MAX_Y_PORTRAIT-10,SG_DESELECTED,"Return");
      drawHeader("Note pad:");
    }else if(point.y<(MAX_Y_PORTRAIT-40)){   //touch on notepad
      lcd.drawCircle(point.x,point.y,1,SG_BLACK,SG_FILL); //draw
    }else{                                   //touch on return button
      lcd.objButton(10,MAX_Y_PORTRAIT-40,MAX_X_PORTRAIT-10,MAX_Y_PORTRAIT-10,SG_SELECTED,"Return");    
      delay(300);
      return;                                //exit
    }                                
  }                                 
}

/**************************************************/
void games(){

}

/**************************************************/
void settings(){
  
}

/**************************************************/
void music(){
  SG_STATE state; static char pause=1;
  unsigned int songs=0;
  static unsigned int currentSong=0, volume=100;//static to save current song and volume even we exit function

  lcd.SDFopenDir("Music");          //Open the folder that contains the songs in .wav format
  lcd.SDFgetList(0,&songs);         //get number of files/songs under the current folder "Music"
  
  lcd.setTextColour(SG_WHITE);
  lcd.setTextSize(SG_FONT3);
  lcd.setTextBackFill(SG_TRANS);
  lcd.drawGradientRect(0,0,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,SG_BLACK,SG_MAGENTA,SG_VERTICAL);
  lcd.string((MAX_X_PORTRAIT+1)/4,(MAX_Y_PORTRAIT+1)/2,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,"Music Player",0);
  delay(1000);
  lcd.erase();  
  drawHeader("Music:");
  lcd.getWAVPlayState(&state);      //get playing state
  if(state==SG_DISABLE) pause=1;    //if not playing, set pause to active
  drawControlPLAY(pause);           //draw button according to pause
  drawControlRR(SG_DESELECTED);
  drawControlFF(SG_DESELECTED); 
  //draw current volume bar
  lcd.drawRectangle(0,245,(volume*MAX_X_PORTRAIT)/(100),260,SG_YELLOW,SG_FILL);  //scale volume value to 0-239 pixels
  lcd.drawRectangle((volume*MAX_X_PORTRAIT)/(100),245,MAX_X_PORTRAIT,260,SG_BLACK,SG_FILL); //scale volume value to 0-239 pixels 
    
  while(1){
    lcd.getWAVPlayState(&state);                            //get playing state  
    if(state==SG_DISABLE){pause=1; drawControlPLAY(pause);} //if not playing, set pause to active and update button
    if(pause==0) lcd.drawGradientRect(0,70,MAX_X_PORTRAIT,240,random(0,65536),random(0,65536),SG_HORIZONTAL);
    
    delay(100);
    if(lcd.touchScreen(&point)==SG_VALID){        //ask for touch and if valid..
      if(point.y>265){                            //Touch on controls
        if(point.x<80){                           //touch on << icon
          drawControlRR(SG_SELECTED);
          lcd.advanceWAVFile(0);                  //rewind song to beginning
          delay(300);                             //wait                    
          drawControlRR(SG_DESELECTED);
        }else if(point.x<160){                    //touch on Play/Pause icon
          if(state == SG_ENABLE){                 //if playing
            lcd.pauseWAVFile();                   //pause playing
            pause=!pause;
          }else{                                  //begin to play any song
            lcd.SDFgetFileName(currentSong,name); //get the name of the song file number currentSong
            cutFileExtension(name,".wav");        //cut to name the .wav extension
            lcd.playWAVFile(name,0);              //play file 
            lcd.drawRectangle(0,25,MAX_X_PORTRAIT,70,SG_BLACK,SG_FILL);   //erase previous name
            lcd.string(10,30,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,name,0); //print new name
            pause=0; 
          }        
          delay(300);          
        }else{ //point.x<240                      //touch on >> icon
          drawControlFF(SG_SELECTED);
          lcd.stopWAVFile();                      //stop current playing song if any
          currentSong++;                          //advance current song
          if(currentSong>=songs) currentSong=0;   //check
          lcd.SDFgetFileName(currentSong,name);   //get the name of the song file number currentSong
          cutFileExtension(name,".wav");          //cut to name the .wav extension
          lcd.playWAVFile(name,0);                //play file
          lcd.drawRectangle(0,25,MAX_X_PORTRAIT,70,SG_BLACK,SG_FILL);   //erase previous name
          lcd.string(10,30,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,name,0); //print new name         
          pause=0;
          delay(300);                             //wait          
          drawControlFF(SG_DESELECTED);
        }
        drawControlPLAY(pause);                   //update button        
      }else if(point.y>240){                      //Touch on volume bar
        volume=(point.x*100)/MAX_X_PORTRAIT;      //obtain new volume parameter by scaling to 0-239 pixels
        lcd.setVolumeWAV(volume);                 //set new volume to SmartGPU Audio
        //update volume bar
        lcd.drawRectangle(0,245,(volume*MAX_X_PORTRAIT)/(100),260,SG_YELLOW,SG_FILL);             //scale volume value to 0-239 pixels
        lcd.drawRectangle((volume*MAX_X_PORTRAIT)/(100),245,MAX_X_PORTRAIT,260,SG_BLACK,SG_FILL); //scale volume value to 0-239 pixels         
        delay(50);
      }else if(point.y<20){                       //if touch on main header, go to main menu
        lcd.SDFopenDir("..");                     //return/go up to parent dir one level
        delay(300);      
        return;
      }
    } 
  }
}

/**************************************************/
void wallpaper(){
  unsigned int walls=0, currentWall=0, i=0;
  
  lcd.SDFopenDir("Wall") ;          //Open the folder that contains the wallpaper images
  lcd.SDFgetList(0,&walls);         //get number of files/Pics under the current folder "Wall"
  
  lcd.setTextColour(SG_WHITE);
  lcd.setTextSize(SG_FONT3);
  lcd.setTextBackFill(SG_TRANS);
  lcd.drawGradientRect(0,0,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,SG_BLACK,SG_MAGENTA,SG_VERTICAL);
  lcd.string((MAX_X_PORTRAIT+1)/4,(MAX_Y_PORTRAIT+1)/2,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,"Wallpapers",0);
  delay(1000);
 
  while(1){  
    lcd.SDFgetFileName(i,name);                        //get the name of the wall file number i
    cutFileExtension(name,".bmp");                     //cut to name the .bmp extension
    lcd.imageBMPSD(0,0,name);                          //Load image from SD card, all images are 240x320(full screen) so we load them from top left corner X:0,Y:0
    drawHeader("Wallpapers:");
    delay(200);                                        //A little delay to avoid fast image changing    
    lcd.objButton(10,25,MAX_X_PORTRAIT-10,55,SG_DESELECTED,"Set as Wall");    
    lcd.objButton(10,280,MAX_X_PORTRAIT-10,310,SG_DESELECTED,"Return");
    
    while(lcd.touchScreen(&point)==SG_INVALID);        //wait for a touch to do something    
    
    if(point.y > 280){                                 //if touch on "return" button, break to exit while(1);
      lcd.objButton(10,280,MAX_X_PORTRAIT-10,310,SG_SELECTED,"Return");
      lcd.SDFopenDir("..");                            //return/go up to parent dir one level
      delay(300);      
      return;                                          //EXIT                           
    }
    if(point.y < 60){                                  //if touch on "set as wall" button
      lcd.objButton(10,25,MAX_X_PORTRAIT-10,55,SG_SELECTED,"Set as Wall");
      lcd.setTextSize(SG_FONT2);
      lcd.string(22,140,MAX_X_PORTRAIT,MAX_Y_PORTRAIT,"Saved on EEPROM",0);
      saveWallpaperToEEPROM();                         //Save the current contents of "name" array to EEPROM
      delay(500);
      continue;
    }     
    //check if we go to the next image, or to the previous one
    if(point.x>120){                                   //if the received touch was on the right side of the screen we advance the image, else we decrease and go to previous image
      i++;                                             //decrease image selector
      if(i>=walls){                                    //if we reach the position of the last image, we restart to image 0
        i=0;                 
      }        
    }else{                                             //touch on left side of screen
      if(i>0){                                         //if we can decrease i
        i--;    
      }else{                                           //if we decrease i will be less than zero, so we move to last image instead
        i=walls-1;  
      }
    }   
  }    
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

  MAX_X_PORTRAIT = LCD_HEIGHT-1;
  MAX_Y_PORTRAIT = LCD_WIDTH-1;
  MAX_X_LANDSCAPE= LCD_WIDTH-1;
  MAX_Y_LANDSCAPE= LCD_HEIGHT-1;
}


/**************************************************/
/****************** MAIN LOOP *********************/
/**************************************************/
/**************************************************/
void loop() { //main loop
  unsigned char icons;
  
  lcd.baudChange(SG_BAUD5);           //set high baud for advanced applications
  lcd.orientation(SG_PORTRAIT_LOW);   //set orientation as portrait  
  lcd.initDACAudio(SG_ENABLE);        //Turn on the Audio DACs
  lcd.audioBoost(SG_ENABLE);          //ENABLE boost  
  lcd.SDFopenDir("FullGUI");          //Open the FullGUI folder that contains the images of the Application
    
  while(1){
    //draw MainMenu
    drawMainMenu();
    
    icons=getTouchIconMainMenu();  //ask for a touch on one of the icons of main menu and return icon#
    switch(icons){
      case 1: //case icon 1
        backlight();
      break;  
      case 2: //case icon 2
        //calculator();
      break;
      case 3: //case icon 3
        clocks();
      break;
      case 4: //case icon 4
        games();
      break;
      case 5: //case icon 5
        //maps();
      break;
      case 6: //case icon 6
        media();
      break;
      case 7: //case icon 7
        notes();
      break;
      case 8: //case icon 8
        photos();
      break;
      case 9: //case icon 9
        //wifi();
      break;
      case 10: //case icon 10
        settings();
      break;      
      case 11: //case icon 11
        //calls();
      break; 
      case 12: //case icon 12
        music();
      break; 
      case 13: //case icon 13
        wallpaper();
      break;      
      default:
        //do nothing
      break;       
    }
  }  
}
