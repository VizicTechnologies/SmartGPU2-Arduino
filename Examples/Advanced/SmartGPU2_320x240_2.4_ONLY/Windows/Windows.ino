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

SG_AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution

SG_AXIS MAX_X_PORTRAIT, MAX_Y_PORTRAIT, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE;

//Create our structures
SG_POINT point;
SG_ICON icon;

//Global variables
//Start time: hours = 2, minutes = 19, seconds = 33;
int clockTime= (2*(60*60)) + (19*60) + (33); //In seconds

//Array to store the RGB888 pixel obtained with memoryRead()
char pixelArray[3]; 

//Main applications, the next applications are called by the main loop menu
/**************************************************/
/**************************************************/
/**************************************************/
/**************************************************/
//clock application
char clocks(){
  unsigned int hours=4,mins=48,secs=0;
  unsigned int halfx=160 ,halfy=129;
  unsigned int xs,ys,xm,ym,xh,yh,i;
  int angleH,angleM,angleS;
  unsigned int handHour=45;//hand size
  unsigned int handMin=57;//hand size
  unsigned int handSec=62;//hand size 
  unsigned int colBackClk,colHour,colMin,colSec; 
  unsigned char carClk=1,clockNextFlag;
  
  while(1){                         //we loop between clocks until a touch on icons
    switch(carClk){
      case 1:                      
        drawWindowBattery("old clk"); //load the clock face
        colHour=SG_BLACK;              //change the colour of the clock hands
        colMin=SG_BLACK;
        colSec=SG_RED;
        handHour=45;                //hands size
        handMin=57;                 
        handSec=62;
      break;
      case 2:
        drawWindowBattery("cool clk"); //load the clock face
        colHour=SG_RED;               //change the colour of the clock hands
        colMin=SG_BLUE;
        colSec=SG_YELLOW;    
        handHour=58;               //hands size
        handMin=65;
        handSec=70;
      break;
      case 3:
        drawWindowBattery("purple clk"); //load the clock face
        colHour=SG_WHITE;             //change the colour of the clock hands
        colMin=SG_WHITE;
        colSec=SG_WHITE;
        handHour=47;               //hands size
        handMin=55;        
        handSec=64;
      break;
      default:
      break;        
    }
          
    lcd.getImageFromMemory(halfx,halfy,halfx,halfy,pixelArray); //This function return a 24 bit pixel array, 
    colBackClk=RGB888ToRGB565(pixelArray);              //we get the back colour of the clock to erase the hands with the same colour   
    clockNextFlag=0;                                    //turn off next clock flag          
    while(clockNextFlag==0){
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
      lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,colMin);  // Draw the minutes hand, first point is the center of the clock, and the second is the point obtained by doing math
      lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,colHour); // Draw the hours hand, first point is the center of the clock, and the second is the point obtained by doing math
      lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,colSec);  // Draw the seconds hand, first point is the center of the clock, and the second is the point obtained by doing math
      lcd.drawCircle(halfx,halfy,3,colSec,SG_FILL);        // Draw the center of the second's hand
     
      for(i=0;i<100;i++){                                  // loop for about one second delay (we dont need to explain why we're waiting one second, right?)
        if(lcd.touchScreen(&point)==SG_VALID){
          carClk++;                                        // increase clock Counter to select and load next clock
          if(carClk==4){
            carClk=1;
          }                   
          clockNextFlag=1;                                 // turn on flag to change clock
          break;
        }
        if(lcd.touchIcon(&icon)==SG_VALID){                // if we receive a touch on icons we exit
          return 0;                                        // exit
        }
        delay(10);           
      }                   
 
      //Erase all hands         
      lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,colBackClk); // Erase Second's hand
      lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,colBackClk); // Erase Minute's hand
      lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,colBackClk); // Erase Hour's hand            
    }
  }    
}

/**************************************************/
/**************************************************/
//calc application
void calculator(){
  unsigned char auxCalc=0;
  char number=0,sums=0;
  char num1[2]={0}; 
  char num2[2]={0}; 
  char result[4]={0};
  char operation[2]={0};
  
  drawWindowBattery("Calculator");                   //load calculator design
  //strings config
  lcd.setTextColour(SG_BLACK);
  lcd.setTextSize(SG_FONT3);
  lcd.setTextBackFill(SG_TRANS);  
  lcd.string(224,34,255,65,"0",0);   //draw numbers
  lcd.setTextSize(SG_FONT0);     
  lcd.string(80,36,100,55,"0",0);  

  //Start application
  while(1){                               //while touch on screen
    while(lcd.touchScreen(&point)==SG_INVALID && lcd.touchIcon(&icon)==SG_INVALID); //wait for a touch to do something
    if(lcd.touchIcon(&icon)==SG_VALID){           //if the received touch was on any icon we go to main menu 
      break;  
    }         
    if(point.y>73 & point.y<101){        //first row       
      if(point.x>74 & point.x<117){
        auxCalc='E'; 
      }else if(point.x>116 & point.x<161){
        auxCalc='I';
      }else if(point.x>161 & point.x<205){
        auxCalc='/';
      }else if(point.x>204 & point.x<249){
        auxCalc='X';
      }
    }else if(point.y>100 & point.y<130){ //second row
      if(point.x>74 & point.x<117){
        auxCalc=7; 
      }else if(point.x>116 & point.x<161){
        auxCalc=8;
      }else if(point.x>161 & point.x<205){
        auxCalc=9;
      }else if(point.x>204 & point.x<249){
        auxCalc='-';
      }                
    }else if(point.y>129 & point.y<159){ //third row
      if(point.x>74 & point.x<117){
        auxCalc=4; 
      }else if(point.x>116 & point.x<161){
        auxCalc=5;
      }else if(point.x>161 & point.x<205){
        auxCalc=6;
      }else if(point.x>204 & point.x<249){
        auxCalc='+';
      }                     
    }else if(point.y>158 & point.y<188){ //fourth row
      if(point.x>74 & point.x<117){
        auxCalc=1; 
      }else if(point.x>116 & point.x<161){
        auxCalc=2;
      }else if(point.x>161 & point.x<205){
        auxCalc=3;
      }else if(point.x>204 & point.x<249){
        auxCalc='R';
      }         
    }else if(point.y>187 & point.y<215){ //fifth row
      if(point.x>74 & point.x<117){
        auxCalc=0; 
      }else if(point.x>116 & point.x<161){
        auxCalc=0;
      }else if(point.x>204 & point.x<249){
        auxCalc='R';
      } 
    }else{
      auxCalc='N';
    }
    if(number==0){               //get first number
      if(auxCalc<10){
        num1[0]=auxCalc+0x30;               
      }else{
        if(auxCalc=='E'){                  
          num1[0]=0x30;                
        }else{                  
          operation[0]=auxCalc;
          if(operation[0]!='R' & operation[0]!='N' & operation[0]!='I'){
            number++; 
            lcd.drawRectangle(224,34,248,58,0xD6B6,SG_FILL);
            delay(200);
            lcd.setTextSize(SG_FONT0); 
            lcd.string(90,36,100,55,operation,0);
          }                                                     
        }                            
      }
      lcd.drawRectangle(80,36,87,46,0xD6B6,SG_FILL);              
      lcd.drawRectangle(224,34,248,58,0xD6B6,SG_FILL);
      lcd.setTextSize(SG_FONT3); 
      lcd.string(224,34,255,65,num1,0);
      lcd.setTextSize(SG_FONT0); 
      lcd.string(80,36,100,55,num1,0);
      num2[0]=0; 
    }else if (number==1){       //get second number
      if(auxCalc<10){
        num2[0]=auxCalc+0x30;              
      }else{
        if(auxCalc=='E'){
            num2[0]=0x30; 
        }else{                                                         
          if(auxCalc=='R'){
            switch(operation[0]){
              case '+':
                sums=(num1[0]-0x30);
                sums+=(num2[0]-0x30);                          
              break;
              case '-':
                sums=(num1[0]-0x30);
                sums-=(num2[0]-0x30);                          
              break;
              case 'X':
                sums=(num1[0]-0x30);
                sums*=(num2[0]-0x30);                          
              break;
              case '/':
                sums=(num1[0]-0x30);
                sums/=(num2[0]-0x30);                                                  
              break;  
              default:
                sums=(num1[0]-0x30);
                sums+=(num2[0]-0x30); 
              break;                                                               
            }       
            if(sums<0){
              result[0]='-'; 
              result[1]=(-1*(sums/10))+0x30;
              result[2]=(-1*(sums%10))+0x30;
            }else{
              result[0]=' ';                                   
              result[1]=(sums/10)+0x30;
              result[2]=(sums%10)+0x30;
            }       
            lcd.setTextSize(SG_FONT0);             
            lcd.string(100,36,110,55,num2,0);
            lcd.string(110,36,120,55,"=\0",0);
            lcd.drawRectangle(224,34,248,58,0xD6B6,SG_FILL);
            lcd.setTextSize(SG_FONT3); 
            lcd.string(205,34,255,65,result,0);                                              
            number++;    
            delay(200);                                                                  
          }                                                                        
        }                             
      } 
      if(number<2){
        lcd.drawRectangle(100,36,107,46,0xD6B6,SG_FILL);              
        lcd.drawRectangle(224,34,248,58,0xD6B6,SG_FILL);
        lcd.setTextSize(SG_FONT3); 
        lcd.string(224,34,255,65,num2,0);
        lcd.setTextSize(SG_FONT0); 
        lcd.string(100,36,110,55,num2,0);
      }
    }else{
      lcd.drawRectangle(75,34,248,58,0xD6B6,SG_FILL);
      number=0;
    }            
  }     
}

/**************************************************/
/**************************************************/
//notes application
void notes(){
  drawWindowBattery("notes");                 //load notes design
  
  while(1){          
    while(lcd.touchScreen(&point)==SG_INVALID && lcd.touchIcon(&icon)==SG_INVALID); //wait for a touch to do something
    if(lcd.touchIcon(&icon)==SG_VALID){               //if the received touch was on any icon we exit go to main menu 
      break;  
    }    
    lcd.drawCircle(point.x,point.y,2,SG_BLACK,SG_FILL);                          
 }                                 
}

/**************************************************/
/**************************************************/
//pong application
void pong(){
  
  unsigned char radiusBall2=8;
  unsigned char radiusBall1=10;  
  unsigned int speedBall1=2; //ball1 moving speed - amount of pixels that ball move each time
  unsigned int speedBall2=3; //ball2 moving speed - amount of pixels that ball move each time 
  int dirx1=-1;     //xball1 initial negative direction
  int diry1=1;      //yball1 initial positive direction
  int xBall1=200;   //x initial position of ball1
  int yBall1;       //y position of ball1
  int dirx2=1;      //xball2 initial positive direction
  int diry2=-1;     //yball2 initial negative direction
  int xBall2=50;    //x initial position of ball2
  int yBall2;       //y position of ball2
  
  //variables used by Pong data
  char score[7]={0,0,' ','P','T','S',0x00}; //array to save score
  char points=0;            
  char gameOver=0;        //game over flag
  int speedCounter=0;     //Counter that saves the speed 
  char ball1Active=1;     //acrive ball flag
  char ball2Active=1;     //active ball flag 
  int barSize = 60;       //size of bar in pixels 
  int bar=50;             //initial x position of the bar   
  int barCenter = (barSize/2)+bar; //we need to know the center of the bar
  int pongBack=0x6350;    //pong background colour
   
  //define bouncing corners 
  int bottomx1= (25+radiusBall1);
  int topx1   = (319-25-radiusBall1-1);
  int bottomy1= (25+radiusBall1);
  int topy1   = (239-30-radiusBall1-1);
  int bottomx2= (25+radiusBall2);
  int topx2   = (319-25-radiusBall2-1);
  int bottomy2= (25+radiusBall2);
  int topy2   = (239-30-radiusBall2-1);    
  
  unsigned char i;
  char buffer[3];
   
  yBall1=random(25+radiusBall1,120); //y initial position of ball1 
  yBall2=random(25+radiusBall2,120); //y initial position of ball2
    
  drawWindowBattery("pong");                                             //load pong design
  //strings config
  lcd.setTextColour(SG_GREEN);
  lcd.setTextSize(SG_FONT0);
  lcd.setTextBackFill(SG_FILLED);  
  lcd.string(110,100,250,120,"Touch to Begin",0);       //draw instructions
  
  while(lcd.touchScreen(&point)==SG_INVALID);                                //wait a touch to begin
  lcd.drawRectangle(25,25,294,214,pongBack,SG_FILL);                        //draw arena
  lcd.drawRectangle(24,24,295,215,SG_GREEN,SG_UNFILL);                         //corners
  lcd.drawLine(bar,209,bar+barSize,209,SG_WHITE);                           //draw Bar   
  lcd.setTextBackFill(SG_TRANS);     
  lcd.setTextColour(SG_RED);
  lcd.setTextSize(SG_FONT2);  
  
  while(gameOver==0){                                                    //while game over flag is zero                          
    buffer[0]=(points/10)+0x30, buffer[1]=(points%10)+0x30, buffer[2]=0; //fill buffer that counts
    lcd.drawRectangle(0,16,23,34,SG_BLACK,SG_FILL);                            //erase last points
     
    lcd.string(1,16,30,35,buffer,0);                       //display current points
      for(i=0;i<10;i++){                                                 //check 10 times if the player touches the screen
        if(lcd.touchScreen(&point)==SG_VALID){                               //if we receive a touch then we move the bar to touched side
          lcd.drawLine(bar,209,bar+barSize,209,pongBack);                //erase previous Bar    
          if(point.x>barCenter){                                    //if we need to move the bar to the right           
            bar+=8;                                                      //move the bar to the right  8 pixels
            if((bar+barSize)>293){                                       //if the bar reach the right corner
              bar=293-barSize;      
            }              
            barCenter=bar+(barSize/2);                                   //set new center position of the bar
          }else{                                                         //move the bar to the left                                   
            bar-=8;                                                      //move the bar to the left 8 pixels 
            if(bar<25){                                                  //if the bar reach the left corner
              bar=25;  
            }              
            barCenter=bar+(barSize/2);                                   //set new center position of the bar
          }
          lcd.drawLine(bar,209,bar+barSize,209,SG_WHITE);                   //draw the new bar at the new position
        }else{
          delay(1);  
        }
      }
      //we update the balls
      if(ball1Active){                                                   //if we haven't lost the ball1         
        /***************************************************/
        //This its similar as moveBall1() function of pong example
        //update the actual position of the ball1        
        lcd.drawCircle(xBall1,yBall1,radiusBall1,pongBack,SG_UNFILL);  // Erase previous ball position
        xBall1+=(dirx1*speedBall1);                                    // Calculate new x coordinate for ball1 
        yBall1+=(diry1*speedBall1);                                    // Calculate new y coordinate for ball1  
        lcd.drawCircle(xBall1,yBall1,radiusBall1,SG_GREEN,SG_UNFILL);  // Draw new ball position
        if((xBall1+speedBall1)>topx1 | (xBall1-speedBall1)<=bottomx1){ // if ball reaches the left or right corner, we invert moving direction 
         dirx1= dirx1*(-1);
        }
        if((yBall1+speedBall1)>topy1 | (yBall1-speedBall1)<=bottomy1){ // if ball reaches the top or bottom corner, we invert moving direction 
         if((yBall1-speedBall1)<=bottomy1){                            // Bounce on top, only invert moving direction
           diry1= diry1*(-1);                                          // We invert the moving direction by multiplying by -1
         }else{                                                        // Bounce on bottom, check if inside the bar       
           if((xBall1+speedBall1)>bar & (xBall1-speedBall1)<(bar+barSize)){  //if bounce inside the bar
             diry1= diry1*(-1);                                        // We invert the moving direction by multiplying by -1
             points++;                                                 // Increase player current points
             speedCounter++;                                           // Increase the speed counter
             if(speedCounter>9){                                       // If we reach 10 counts we increase the ball1 bouncing speed
               speedBall1++;          
               speedCounter=0;                                          // Reset the counter
             }                           
           }else{                                                      // Bounce outside the bar
             ball1Active=0;                                            // Clear ball1 active flag
             lcd.drawCircle(xBall1,yBall1,radiusBall1,pongBack,SG_UNFILL);// Delete this ball because bounce outside of the bar        
             if(ball1Active==0 & ball2Active==0){                      // if we have lost both balls     
              gameOver=1;                                              // Set game over flag
             }         
          }
        }
       }          
      }
      if(ball2Active){                                                 //if we haven't lost the ball2
        /***************************************************/
        //This its similar as moveBall2() function of pong example
        //update the actual position of the ball2          
        lcd.drawCircle(xBall2,yBall2,radiusBall2,pongBack,SG_FILL);    // Erase previous ball position
        xBall2+=(dirx2*speedBall2);                                    // Calculate new x coordinate for ball2 
        yBall2+=(diry2*speedBall2);                                    // Calculate new y coordinate for ball2
        lcd.drawCircle(xBall2,yBall2,radiusBall2,SG_MAGENTA,SG_FILL);  // Draw new ball position
        if((xBall2+speedBall2)>topx2 | (xBall2-speedBall2)<=bottomx2){ // if ball reaches the left or right corner, we invert moving direction 
         dirx2= dirx2*(-1);
        }
        if((yBall2+speedBall2)>topy2 | (yBall2-speedBall2)<=bottomy2){ // if ball reaches the top or bottom corner, we invert moving direction 
         if((yBall2-speedBall2)<=bottomy2){                            // Bounce on top, only invert moving direction
           diry2= diry2*(-1);        
         }else{                                                        // Bounce on bottom, check if inside the bar       
           if((xBall2+radiusBall2)>bar & (xBall2-radiusBall2)<(bar+barSize)){  //if bounce inside the bar
             diry2= diry2*(-1);                                        // We invert the moving direction by multiplying by -1
             points++;                                                 // Increase player current points
             speedCounter++;                                           // Increase the speed counter
             if(speedCounter>9){                                       // If we reach 10 counts we increase the ball1 bouncing speed
               speedBall2++;          
               speedCounter=0;                                         // Reset the counter
             }                            
           }else{                                                      // Bounce outside the bar
             ball2Active=0;                                            // Clear ball1 active flag
             lcd.drawCircle(xBall2,yBall2,radiusBall2,pongBack,SG_FILL);  // Delete this ball because bounce outside of the bar        
             if(ball1Active==0 & ball2Active==0){                      // if we have lost both balls     
               gameOver=1;                                             // Set game over flag
             }         
           }
         }
       } 
     }
  }
  //game over - proceed to show final score
  lcd.setTextSize(SG_FONT4);  
  lcd.string(70,80,272,140,"Game Over",0);
  score[0]=(points/10)+0x30;                                            //convert points to ascii format and store them on the score buffer
  score[1]=(points%10)+0x30;                                            //convert points to ascii format and store them on the score buffer
  lcd.setTextColour(SG_YELLOW);
  lcd.setTextSize(SG_FONT3);  
  lcd.string(113,110,272,140,score,0);
  lcd.setTextColour(SG_GREEN);
  lcd.setTextSize(SG_FONT1);  
  lcd.string(100,135,250,180,"Touch to Exit",0);          
  delay(1000);
  while(lcd.touchScreen(&point)==SG_INVALID);                           //wait for a touch to exit
}


/**************************************************/
/**************************************************/
//slide show application
void slideShow(){
  char imagesOnSDCard[8][30]={"Penguins","Koala","Hydrangeas","Light House","Jellyfish","Tulips","Desert","Flower"}; //array containing the names of the different called images
  char pic=0;
  
  while(1){   //Loop forever in the slide show!
    drawWindowBattery(imagesOnSDCard[pic]);    //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.imageBMPSD(3,219,"previous");             //Load the previous icon        
    lcd.imageBMPSD(300,219,"next");               //Load the next icon
    
    while(lcd.touchScreen(&point)==SG_INVALID && lcd.touchIcon(&icon)==SG_INVALID); //wait for a touch to do something
    if(lcd.touchIcon(&icon)==SG_VALID){                //if the received touch was on any icon we exit go to main menu 
      break;  
    } 
    
    //check if we go to the next image, or to the previous one
    if(point.x>160){                  //if the received touch was on the right middle of the screen we advance the image, else we decrease and go to previous image
      pic++;                                //decrease image selector
      if(pic>7){                            //if we reach the position of the last image, we restart to image 0
        pic=0;                 
      }        
    }else{
      pic--;    
      if(pic<0){                            //if we reach the position of the first image, we move to image 7
        pic=7;  
      }    
    }   
  }
} 

/**************************************************/
/**************************************************/
//settings application, brightness adjust
void settings(){
  static int bright=127;                                       //Maximum bright is set by default  133 min 14
  static int buttonCen=271;                                    //button center, static variables to avoid losing the parameters even if we go to main menu
  
    drawWindowBattery("Bright");                               //Load image from SD card, image is 320x240(full screen) so we load it from top left corner X:0,Y:0   
    
  while(1){   //Loop forever in the settings!    
    lcd.drawRectangle(40,64,(bright*2)+12,66,0x4C7C,SG_FILL);  //draw brightness bar  266 max  40 min 
    lcd.drawRectangle((bright*2)+12,64,266,66,SG_WHITE,SG_FILL); //fill the rest of the bar with white     
    lcd.imageBMPSD((bright*2)+12,57,"button");                 //Load the button icon   266 max pos X, 40 min X pos   
    delay(100);                                                //delay to avoid fast change and flickering
    
    while(lcd.touchScreen(&point)==SG_INVALID && lcd.touchIcon(&icon)==SG_INVALID); //wait for a touch to do something
    if(lcd.touchIcon(&icon)==SG_VALID){                                //if the received touch was on any icon we exit go to main menu 
      break;  
    }
    
    //touch on Screen, change brightness and draw button icon
    if(point.y>55 & point.y<85 ){                  //if the previous touch was on active area
      lcd.imageBMPSD((bright*2)+12,57,"clear Bar");                  //clear the button icon       
           
      //check where to move left or right
      if(point.x>buttonCen){                             //if we need to move the bar to the right        
        bright+=10;                                            //increase the brightness
        buttonCen+=22;                                         //increase the center of the button
        if(bright>127){                                        //if the button reach the right corner
          bright=127;                                          //set maximum bright
          buttonCen=271;                                       //set maximum button center          
        }              
      }else{                                                   //move the bar to the left                                          
        bright-=10;                                            //decrease the brightness
        buttonCen-=22;                                         //decrease the center of the button
        if(bright<14){                                         //if the button reach the left corner
          bright=14;                                           //set minimum bright
          buttonCen=40;                                        //set minimum button center          
        }           
      }
      lcd.bright(bright);                                      //set new brightness value to SMART GPU          
    }
  } 
}

/**************************************************/
/**************************************************/
//google maps application
void googleMaps(){
  char mapsOnSDCard[10][9]={"map0","map1","map2","map3","map4","map5","map6","map7","map8","map9"}; //array containing the names of the different called maps  
  char maps=0,nothing=1;

  while(1){   //Loop forever in the slide show!
    if(nothing!=0){                              //do something
      drawWindowBattery(mapsOnSDCard[maps]);     //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
      lcd.imageBMPSD(5,25,"barmap");                //draw zoom bar
    }
    
    while(lcd.touchScreen(&point)==SG_INVALID && lcd.touchIcon(&icon)==SG_INVALID); //wait for a touch to do something
    if(lcd.touchIcon(&icon)==SG_VALID){                //if the received touch was on any icon we exit go to main menu 
      break;  
    } 
    
    if(point.x<25){                     //touch on bar
      if(point.y<120){                  //touch on upper side of zoom bar
        maps++;
        if(maps>10){
          maps=10;
        }
      }else{                                  //touch on lower side of zoom bar
        maps--;
        if(maps<1){
          maps=1;  
        }          
      }
       nothing=1;                             //prepare to do new image loading
    }else{                                    //touch on inactive area
       nothing=0;                             //do nothing and get another touch  
    }
  }
}  
 
/**************************************************/
/**************************************************/
//paint application   
void paint(){
  unsigned char penSize=1;
  unsigned int colPaint=SG_BLACK;
  char pen[4]={'x','0','1',0x00};                     //Array that show the current penSize
       
  //Load paint design
  drawWindowBattery("paint");                         //load paint image
  lcd.setTextColour(SG_GREEN);
  lcd.setTextSize(SG_FONT0);
  lcd.setTextBackFill(SG_FILLED);  
  lcd.string(7,54,48,65,"Erase",0);    //draw Erase word
  lcd.string(77,54,110,65,pen,0);      //draw penSize 
  
   while(1){   //Start the Paint application
     while(lcd.touchScreen(&point)==SG_INVALID && lcd.touchIcon(&icon)==SG_INVALID); //wait for a touch to do something
     if(lcd.touchIcon(&icon)==SG_VALID){                //if the received touch was on any icon we exit go to main menu 
       break;  
     }     
   
     if(point.y<67){                                   //the touch was on the menu
       if(point.x<45){                                 //touch on erase circle
         lcd.drawRectangle(0,67,319,239,SG_WHITE,SG_FILL);      //Draw a white rectangle on drawing area
       }else if(point.x<75){                           //touch to select the eraser
         colPaint=SG_WHITE;
         lcd.drawCircle(25,34,14,colPaint,SG_FILL);    //draw WHITE colour circle on top left corner           
       }else if(point.x<108){                          //touch to change pen Size 
         delay(300);                                   //delay to avoid fast penSize changing                   
         penSize=penSize*2;                            //double the penSize
         if(penSize==16){                              //maximum pen size = 8, if we reach 16 we set to 1.
           penSize=1;
         }          
         pen[1]=(penSize/10)+0x30;                     //get the tens of penSize and convert them to ascii
         pen[2]=(penSize%10)+0x30;                     //get the ones of penSize and convert them to ascii
         lcd.string(77,54,110,65,pen,0);//draw penSize 
       }else if(point.x<312 & point.y>20 & point.y<59){                     //touch on the colours bar                  
         lcd.getImageFromMemory(point.x,point.y,point.x,point.y,pixelArray);  //assign new colour based on touch coordinates and memory read, this function return a 24 bit pixel array, 
         colPaint=RGB888ToRGB565(pixelArray);
         lcd.drawCircle(25,34,14,colPaint,SG_FILL);                                              //draw new selected colour on top left corner           
       }                
    }else{                                            //Touch on drawing area
       if((point.y-penSize)<67){                      // If the touch was very close to the menu, we compensate the radius
         point.y=point.y+penSize;
       }
       lcd.drawCircle(point.x,point.y,penSize,colPaint,SG_FILL);                    //Draw
    }
  }   
}

//End of applications, the next function is for pixel format conversion
/**************************************************/
/**************************************************/
//Funcion to convert a 3 byte array to an int RGB565
unsigned int RGB888ToRGB565(char pixBuffer[]){   //get an array of 3 bytes( red, green, blue), and convert them to RGB565 returned in an int
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

/**************************************************/
/**************************************************/
//draws initial screen image, upper bar and battery icon, adds a delay to avoid unwanted touchs
void drawWindowBattery(char image[]){	
    lcd.imageBMPSD(0,0,image);                    //draw image
    lcd.imageBMPSD(0,0,"winHead");                //draw image             
    delay(350);                                //A little delay to avoid fast image changing   
}

/**************************************************/
/**************************************************/
//Initial setup
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
 
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
  unsigned char ic;
  
  lcd.baudChange(SG_BAUD6);           //set high baud for advanced applications
  
  lcd.SDFopenDir("Windows");       //Open the Windows folder that contains the images of the Application
  
  while(1){
    //load Desktop
    lcd.imageBMPSD(0,0,"WinDesk");  
    ic=0;
    
    while(ic==0){                                                    //loop until we get a click on one application      
      do{             
        while(lcd.touchScreen(&point)==SG_INVALID);                            //Wait for touch      
      }while(point.x>20 | point.y<220);                  //Wait for touch on Start Menu
      //pop up start menu
      lcd.imageBMPSD(0,8,"WinMenu");
      delay(350);
      while(lcd.touchScreen(&point)==SG_INVALID);                              //Wait for touch
      if(point.x<70 && point.y> 8 && point.y< 230){ //If touch on menu
        ic=((point.y-8)/27)+1;                                 //divide (222pixels/8)=27 and add 1, to get the icon number
      }                                                              //else go back
      lcd.imageBMPSD(0,0,"MenClose");                                   //close menu     
      delay(150);      
    }
   
    //begin application based on icon number  
    switch(ic){                 //now that we know a touch was made on a specified icon:
      case 1:                   //case 1 (clock)
        clocks();
      break;                    //end of case 1
      
      case 2:                   //case 2 (notes) 
        notes();
      break;                    //end of case 2
      
      case 3:                   //case 3 (calculator)
        calculator();  
      break;                    //end of case 3
      
      case 4:                   //case 4 (pong) 
        pong();
      break;                    //end of case 4 

      case 5:                   //case 5 (slide show) 
        slideShow();
      break;                    //end case 5 

      case 6:                   //case 6 (settings)
        settings();
      break;                    //end case 6

      case 7:                   //case 7 (paintPro)
        paint();             
      break;                    //end of case 7
      
      case 8:                   //case 8 (googleMaps)
        googleMaps();                 
      break;                    //end of case 8 
      
      default:                  //default for any other case
      break;                    //do nothing
    } 
  }  
}
