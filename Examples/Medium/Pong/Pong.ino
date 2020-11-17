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
SG_AXIS MAX_X, MAX_Y;

// defines for balls - user modifable
#define radiusBall1 15     //ball1 size
#define colourBall1 SG_GREEN  //ball1 colour
#define radiusBall2 8      //ball2 size
#define colourBall2 SG_YELLOW //ball2 colour

SG_POINT point;

//variables used by move ball methods
int speedBall1=2; //ball1 moving speed - amount of pixels that ball move each time
int speedBall2=3; //ball2 moving speed - amount of pixels that ball move each time 
int dirx1=1;      //xball1 initial positive direction
int diry1=1;      //yball1 initial positive direction
int xBall1=300;   //x initial position of ball1
int yBall1;       //y position of ball1
int dirx2=-1;     //xball2 initial negative direction
int diry2=1;      //yball2 initial positive direction
int xBall2=30;    //x initial position of ball2
int yBall2;       //y position of ball2

//variables used by Pong method
char score[7]={0,0,' ','P','T','S',0x00}; //array to save score
char points;            
char gameOver;             //game over flag
char speedCounter;         //Counter that saves the speed 
char ball1Active;          //acrive ball flag
char ball2Active;          //active ball flag 
int barSize;               //size of bar in pixels 
int bar;                   //initial x position of the bar   
int barCenter;             //we need to know the center of the bar

/***************************************************/
//function that move or update the actual position of the ball1
void moveBall1(){
   lcd.drawCircle(xBall1,yBall1,radiusBall1,SG_BLACK,SG_UNFILL);    // Erase previous ball position
   xBall1+=(dirx1*speedBall1);                                      // Calculate new x coordinate for ball1 
   yBall1+=(diry1*speedBall1);                                      // Calculate new y coordinate for ball1  
   lcd.drawCircle(xBall1,yBall1,radiusBall1,colourBall1,SG_UNFILL); // Draw new ball position
   if(((xBall1+speedBall1+radiusBall1)>(LCD_WIDTH-2)) || ((xBall1-speedBall1-radiusBall1)<=1)){       // if ball reaches the left or right corner, we invert moving direction 
    dirx1= dirx1*(-1);
   }
   if(((yBall1+speedBall1+radiusBall1)>(LCD_HEIGHT-10)) || ((yBall1-speedBall1-radiusBall1)<=20)){      // if ball reaches the top or bottom corner, we invert moving direction 
    if((yBall1-speedBall1-radiusBall1)<=20){                        // Bounce on top, only invert moving direction
      diry1= diry1*(-1);                                            // We invert the moving direction by multiplying by -1
    }else{                                                          // Bounce on bottom, check if inside the bar       
      if(((xBall1+speedBall1+radiusBall1)>bar) && ((xBall1-speedBall1-radiusBall1)<(bar+barSize))){  //if bounce inside the bar
        diry1= diry1*(-1);                                          // We invert the moving direction by multiplying by -1
        points++;                                                   // Increase player current points
        speedCounter++;                                             // Increase the speed counter
        if(speedCounter>9){                                         // If we reach 10 counts we increase the ball1 bouncing speed
          speedBall1++;          
          speedCounter=0;                                           // Reset the counter
        }                           
      }else{                                                        // Bounce outside the bar
        ball1Active=0;                                              // Clear ball1 active flag
        lcd.drawCircle(xBall1,yBall1,radiusBall1,SG_BLACK,SG_UNFILL);// Delete this ball because bounce outside of the bar        
        if(ball1Active==0 & ball2Active==0){                        // if we have lost both balls     
          gameOver=1;                                               // Set game over flag
        }         
      }
    }
   } 
}

/***************************************************/
//function that move or update the actual position of the ball2
void moveBall2(){
   lcd.drawCircle(xBall2,yBall2,radiusBall2,SG_BLACK,SG_FILL);       // Erase previous ball position
   xBall2+=(dirx2*speedBall2);                                       // Calculate new x coordinate for ball2 
   yBall2+=(diry2*speedBall2);                                       // Calculate new y coordinate for ball2
   lcd.drawCircle(xBall2,yBall2,radiusBall2,colourBall2,SG_FILL);    // Draw new ball position
   if(((xBall2+speedBall2+radiusBall2)>(LCD_WIDTH-2)) || ((xBall2-speedBall2-radiusBall2)<=1)){       // if ball reaches the left or right corner, we invert moving direction 
    dirx2= dirx2*(-1);
   }
   if(((yBall2+speedBall2+radiusBall2)>(LCD_HEIGHT-10)) || ((yBall2-speedBall2-radiusBall2)<=20)){      // if ball reaches the top or bottom corner, we invert moving direction 
    if((yBall2-speedBall2-radiusBall2)<=20){                          // Bounce on top, only invert moving direction
      diry2= diry2*(-1);        
    }else{                                                            // Bounce on bottom, check if inside the bar       
      if(((xBall2+speedBall2+radiusBall2)>bar) && ((xBall2-speedBall2-radiusBall2)<(bar+barSize))){  //if bounce inside the bar
        diry2= diry2*(-1);                                            // We invert the moving direction by multiplying by -1
        points++;                                                     // Increase player current points
        speedCounter++;                                               // Increase the speed counter
        if(speedCounter>9){                                           // If we reach 10 counts we increase the ball1 bouncing speed
          speedBall2++;                
          speedCounter=0;                                             // Reset the counter
        }                            
      }else{                                                         // Bounce outside the bar
        ball2Active=0;                                               // Clear ball1 active flag
        lcd.drawCircle(xBall2,yBall2,radiusBall2,SG_BLACK,SG_FILL);  // Delete this ball because bounce outside of the bar        
        if(ball1Active==0 & ball2Active==0){                         // if we have lost both balls     
          gameOver=1;                                                // Set game over flag
        }         
      }
    }
   } 
}

/***************************************************/
/***************************************************/
//The game methodology
void pong(){
  SG_NUMBEROFBYTES nb;
  unsigned char i;
  char score[7]={0,0,' ','P','T','S',0x00};
  char buffer[4]="00 ";
  
  //reset all parameters
  gameOver=0;            //reset flag
  points=0;              //reset points
  speedCounter=0;        //reset speed
  ball1Active=1;         //acrive ball flag
  ball2Active=1;         //active ball flag 
  yBall1=25+radiusBall1; //y initial position of ball1 
  yBall2=25+radiusBall2; //y initial position of ball2
  
  lcd.drawRectangle(0,20,MAX_X,MAX_Y,SG_MAGENTA,SG_UNFILL);                //draw corners
  lcd.drawLine(bar,MAX_Y-8,bar+barSize,MAX_Y-8,SG_WHITE);                  //draw Bar 
  
  while(gameOver==0){                                                      //while game over flag is zero                          
    buffer[0]=(points/10)+0x30, buffer[1]=(points%10)+0x30;                //fill buffer that counts
    lcd.setTextColour(SG_RED);
    lcd.setTextSize(SG_FONT1);
    lcd.setTextBackFill(SG_FILLED);      
    lcd.string(2,2,30,35,buffer,&nb);                                      //display current points
      for(i=0;i<10;i++){                                                   //check 30 times if the player touches the screen
        if(lcd.touchScreen(&point)){                                       //if we receive a touch then we move the bar to touched side
          lcd.drawLine(bar,MAX_Y-8,bar+barSize,MAX_Y-8,SG_BLACK);          //erase previous Bar    
          if(point.x>barCenter){                                           //if we need to move the bar to the right           
            bar+=8;                                                        //move the bar to the right  8 pixels
            if((bar+barSize)>(LCD_WIDTH-2)){                               //if the bar reach the right corner
              bar=(LCD_WIDTH-2)-barSize;      
            }              
            barCenter=bar+(barSize/2);                                     //set new center position of the bar
          }else{                                                           //move the bar to the left                                   
            bar-=8;                                                        //move the bar to the left 8 pixels 
            if(bar<1){                                                     //if the bar reach the left corner
              bar=1;  
            }              
            barCenter=bar+(barSize/2);                                     //set new center position of the bar
          }
          lcd.drawLine(bar,MAX_Y-8,bar+barSize,MAX_Y-8,SG_WHITE);          //draw the new bar at the new position
        }else{
          delay(1); 
        }
      }
      //we update the balls
      if(ball1Active){                                                   //if we haven't lost the ball1
        moveBall1(); 
      }
      if(ball2Active){                                                   //if we haven't lost the ball2
        moveBall2();      
      }
  }
  //game over - proceed to show final score
  lcd.setTextColour(SG_RED);
  lcd.setTextSize(SG_FONT4);
  lcd.setTextBackFill(SG_TRANS);    
  lcd.string((LCD_WIDTH/5),(LCD_HEIGHT/4),MAX_X,MAX_Y,"Game Over",&nb);
  score[0]=(points/10)+0x30;                                            //convert points to ascii format and store them on the score buffer
  score[1]=(points%10)+0x30;                                            //convert points to ascii format and store them on the score buffer
  lcd.setTextColour(SG_YELLOW);
  lcd.setTextSize(SG_FONT4);
  lcd.string((LCD_WIDTH/3),(LCD_HEIGHT/2),MAX_X,MAX_Y,score,&nb);
  lcd.setTextColour(SG_GREEN);
  lcd.setTextSize(SG_FONT2);  
  lcd.string((LCD_WIDTH/4),(LCD_HEIGHT/3)*2,MAX_X,MAX_Y,"Touch to Exit",&nb);          
  delay(1000);
  while(lcd.touchScreen(&point)==0);                                    //wait for a touch to exit
  lcd.erase();                                                          //erase the screen and exit function
}

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
  
  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);

  MAX_X = LCD_WIDTH-1;
  MAX_Y = LCD_HEIGHT-1;

  barSize = LCD_WIDTH/5; //size of bar in pixels 
  bar = LCD_WIDTH/2;     //initial x position of the bar   
  barCenter = (barSize/2)+bar; //we need to know the center of the bar 
}

void loop() { //main loop
  SG_NUMBEROFBYTES nb;

  lcd.baudChange(SG_BAUD6);   //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!

  while(1){                   // Loop forever
    //Draw a cover
    lcd.drawTriangle(20,20,70,40,40,80,SG_YELLOW,SG_FILL);
    lcd.drawCircle(50,MAX_Y-50,28,SG_CYAN,SG_FILL);
    lcd.drawRectangle(MAX_X-70,30,MAX_X-20,80,SG_MAGENTA,SG_FILL);
    lcd.drawTriangle(MAX_X-60,MAX_Y-10,MAX_X-80,MAX_Y-40,MAX_X-20,MAX_Y-70,SG_RED,SG_FILL);
    lcd.setTextColour(SG_WHITE);
    lcd.setTextSize(SG_FONT5);    
    lcd.setTextBackFill(SG_TRANS); 
    lcd.string(LCD_WIDTH/3,LCD_HEIGHT/3,MAX_X,MAX_Y,"PONG",&nb);
    lcd.setTextColour(SG_GREEN);
    lcd.setTextSize(SG_FONT2);        
    lcd.string(LCD_WIDTH/8,LCD_HEIGHT/2,MAX_X,MAX_Y,"Touch screen to begin",&nb);
    delay(1000);
    while(lcd.touchScreen(&point)==SG_INVALID); //wait for a touch to begin
    lcd.erase();
    //start the game
    pong();                   // Play until game over
  }
}
