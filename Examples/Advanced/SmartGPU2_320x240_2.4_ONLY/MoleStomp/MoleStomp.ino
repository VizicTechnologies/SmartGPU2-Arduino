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

#define MOLEHOLE 3        //position of the array where mole hole image is contained
#define HITMOLE 4         //position of the array where hit mole image is contained
#define MISSMOLE 5        //position of the array where miss mole image is contained

//Create the Structs
SG_POINT point;
SG_ICON icon;

char moleType[6][9]={"MoleHap","MoleSee","MoleBad","MoleHole","MolePun","MoleMiss"}; //array containing the names of the different called images

/****************************************************/
//This function call the desired image in the position of the desired hole
void showMole(char mole, char hole){  
  switch(hole){
    case 1:
      lcd.imageBMPSD(38,70,moleType[mole]); // hole 1
    break;
    case 2:
      lcd.imageBMPSD(138,70,moleType[mole]); // hole 2
    break;  
    case 3:
      lcd.imageBMPSD(240,70,moleType[mole]); // hole 3
    break;    
    case 4:
      lcd.imageBMPSD(38,147,moleType[mole]); // hole 4
    break;  
    case 5:
      lcd.imageBMPSD(138,147,moleType[mole]); // hole 5
    break;
    case 6:
      lcd.imageBMPSD(240,147,moleType[mole]); // hole 6
    break;
    default:
    break;
  } 
}

/****************************************************/
//This function returns 1 if a touch has been made in a specified hole
char touchOnHole(char hole){
  char hit=0; 
  
  switch(hole){
    case 1:
      if(point.x>0 && point.x<111 && point.y>65 && point.y<146){   //check if the last touch was inside this area
        hit=1;    
      } 
    break;
    case 2:
      if(point.x>110 && point.x<211 && point.y>65 && point.y<146){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;  
    case 3:
      if(point.x>210 && point.x<320 && point.y>65 && point.y<146){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;    
    case 4:
      if(point.x>0 && point.x<111 && point.y>145 && point.y<240){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;  
    case 5:
      if(point.x>110 && point.x<211 && point.y>145 && point.y<240){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;
    case 6:
      if(point.x>210 && point.x<320 && point.y>145 && point.y<240){ //check if the last touch was inside this area
        hit=1;    
      } 
    break;
    default:
    break;
  }  
  return hit;  
}

void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
  
  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);
}

void loop() { //main loop
  SG_NUMBEROFBYTES nb;
  int x;
  char hitFlag=0;
  char hole, mole;
  char moleCounter=20,points=0;
  char pointsTotal[4]="00 ";       //array to store the points
  
  lcd.baudChange(SG_BAUD6);        //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!
  lcd.SDFopenDir("Mole Stomp");    //Open the Mole Stomp folder that contains the images of the Application  
  lcd.setTextBackColour(SG_BLUE);  //set the all text background to blue
  
 while(1){                         //loop forever the game
  lcd.setTextColour(SG_RED);
  lcd.setTextSize(SG_FONT5);
  lcd.setTextBackFill(SG_TRANS);  
  lcd.string(22,90,300,220,"GET READY!!!",&nb); //show ready string
  delay(1500);
  lcd.imageBMPSD(0,0,"MoleArea");     //show area   
  lcd.setTextColour(SG_WHITE);
  lcd.setTextSize(SG_FONT1);
  lcd.setTextBackFill(SG_FILLED);    
  lcd.string(35,27,50,50,"00",&nb); //draw the initial points
  delay(800);  
  
  //Start the game!
  while(moleCounter>0){            //loop the game while moleCounter reaches zero moles
    randomSeed(random(0,65535));   //set different seeds to obtain a good random number 
    mole=random(0,3);              //get a random mole 0-2
    hole=random(1,7);              //get a random hole 0-6
    showMole(mole,hole);           //show the random mole on the random hole
    for(x=0;x<3000;x++){            //wait some time for the player hit the mole(less time=more difficulty, more time=easy play)
      if(lcd.touchScreen(&point)){  //if we receive a touch on screen
        if(touchOnHole(hole)){     //if the touch is on the hole of the current mole
          hitFlag=1;               //turn on the hit mole flag
          break;                   //end the waiting time
        }
      }  
    }
    if(hitFlag==1){               //if the last mole was hit
      showMole(HITMOLE,hole);     //we show the hit mole
      points++;                   //increase hit mole counter or points
      hitFlag=0;                  //clear the hit flag
    }else{                        //if the last mole was missed
      showMole(MISSMOLE,hole);    //show the mole hiding
    }
    pointsTotal[0]=(points/10)+0x30;  //get the tens of the points and convert them to ascii
    pointsTotal[1]=(points%10)+0x30;  //get the ones of the points and convert them to ascii
    lcd.setTextColour(SG_WHITE);
    lcd.setTextSize(SG_FONT2);
    lcd.setTextBackFill(SG_FILLED);     
    lcd.string(33,27,100,100,pointsTotal,&nb); //draw the points    
    delay(350);
    showMole(MOLEHOLE,hole);          //show the bare hole
    moleCounter--;                    //decrease the mole counter
  }                                   //end of the game
  
  //Game over, display results
  lcd.setTextColour(SG_YELLOW);
  lcd.setTextSize(SG_FONT3);
  lcd.setTextBackFill(SG_TRANS);    
  lcd.string(80,50,300,220,"Whacked Moles:",&nb);   
  lcd.setTextColour(SG_BLUE);  
  lcd.string(153,75,300,220,pointsTotal,&nb); //draw the converted to ascii points array 
  lcd.setTextColour(SG_RED);  
  lcd.setTextSize(SG_FONT2);  
  lcd.string(50,150,319,239,"TOUCH TO RESTART",&nb);   
  delay(1000);
  
  //wait for a touch on screen to restart
  while(lcd.touchScreen(&point)==SG_INVALID);
  moleCounter=20;                   //reset the moleCounter
  points=0;                         //reset points
  lcd.erase();                      //erase screen and restart all
 } 
}
