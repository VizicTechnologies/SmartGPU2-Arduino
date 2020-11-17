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

//KEYBOARD DEFINITIONS
#define LETTERSLOWER     0
#define LETTERSUPPER     1
#define NUMBERS          2
#define SPECCHAR         3
#define KEYBOARD_X_SIZE  LCD_WIDTH
#define KEYBOARD_Y_SIZE  KEYBOARD_X_SIZE/2
#define KEY_Y_TOP        LCD_HEIGHT-1 - KEYBOARD_Y_SIZE //at the bottom of screen
#define KEYXSIZE         KEYBOARD_X_SIZE/10 //10 - columns
#define KEYYSIZE         KEYBOARD_Y_SIZE/4  //4 - rows 

//keys definitions
#define SPACE    ' '
#define OK       0x01
#define DEL      0x02
#define TYPE     0x03
#define KEYCASE  0x04

//Keyboards type data, row1: 10 characters, row2: 9 characters, row3: 7 characters
const char lettL[]= {"qwertyuiopasdfghjklzxcvbnm"}; //10-9-7 lower case
const char lettU[]= {"QWERTYUIOPASDFGHJKLZXCVBNM"}; //10-9-7 upper case
const char num []= {"1234567890-/:;()&@\"_.,?!'*"};//10-9-7
const char spc []= {"[]{}#%^*+=:|~<>$-/\\_.,?!'*"};//10-9-7
const char* keyboards[4]={lettL, lettU, num, spc};
  
/*********************************************************/
void drawSingleKey(char key, char keyboardType, SG_ACTIVE state){ //draws the received key as "state"(SELECTED or DESELECTED)
  unsigned int i=0;
  char *data = (char*)keyboards[keyboardType];
  char letter[2]={key,0};
  
  //special case when key is ' '(space) or 0x01 "enter" or 0x02 "del" or 0x03 "type" or 0x04 "keycase"
  if(key == ' ' || key <= KEYCASE){
    switch(key){
      case ' ':  //space
        lcd.objButton(KEYXSIZE+(KEYXSIZE/2), KEY_Y_TOP+(KEYYSIZE*3), (7*KEYXSIZE+(KEYXSIZE/2))+KEYXSIZE-1, KEY_Y_TOP+(KEYYSIZE*4)-1, state, "space");
      break;
      case OK:   //OK
        lcd.objButton(8*KEYXSIZE+(KEYXSIZE/2), KEY_Y_TOP+(KEYYSIZE*3), KEYBOARD_X_SIZE-1, KEY_Y_TOP+(KEYYSIZE*4)-1, state, "OK");
      break;      
      case DEL:  //delete
        lcd.objButton(8*KEYXSIZE+(KEYXSIZE/2), KEY_Y_TOP+(KEYYSIZE*2), (8*KEYXSIZE+(KEYXSIZE/2))+KEYXSIZE-1, KEY_Y_TOP+(KEYYSIZE*3), state, "del");
      break;
      case TYPE: //keyboard type
        lcd.objButton(KEYXSIZE/2, KEY_Y_TOP+(KEYYSIZE*2), (KEYXSIZE/2)+KEYXSIZE-1, KEY_Y_TOP+(KEYYSIZE*3), state, "type");
      break;
      case KEYCASE: //letters upper/lower case
        lcd.objButton(0, KEY_Y_TOP+(KEYYSIZE*3), KEYXSIZE+(KEYXSIZE/2)-1, KEY_Y_TOP+(KEYYSIZE*4)-1, state, "case");      
      break;
      default: //0x00 none
      break;      
    }
    return;
  }
  //any other key case
  for(i=0;i<26;i++){ //search for the key in the received keyboardType data array
    if(key == data[i]) break;
  }
  if(i<10){
    lcd.objButton(i*KEYXSIZE, KEY_Y_TOP, (i*KEYXSIZE)+KEYXSIZE-1, KEY_Y_TOP+KEYYSIZE, state, letter);
  }else if(i<19){
    i-=10;
    lcd.objButton(i*KEYXSIZE+(KEYXSIZE/2), KEY_Y_TOP+KEYYSIZE, (i*KEYXSIZE+(KEYXSIZE/2))+KEYXSIZE-1, KEY_Y_TOP+(KEYYSIZE*2), state, letter);
  }else if(i<26){
    i-=18;
    lcd.objButton(i*KEYXSIZE+(KEYXSIZE/2), KEY_Y_TOP+(KEYYSIZE*2), (i*KEYXSIZE+(KEYXSIZE/2))+KEYXSIZE-1, KEY_Y_TOP+(KEYYSIZE*3), state, letter);
  }
}

/*********************************************************/
void drawAllKeyboard(char keyboardType){
  unsigned int i=0;
  char *data = (char*)keyboards[keyboardType];
  
  for(i=0;i<26;i++){ //go through all keyboard data
    drawSingleKey(*data++, keyboardType, SG_DESELECTED);
  }
  //draw special keys
  drawSingleKey(TYPE, keyboardType, SG_DESELECTED);
  drawSingleKey(DEL, keyboardType, SG_DESELECTED);  
  drawSingleKey(KEYCASE, keyboardType, SG_DESELECTED);    
  drawSingleKey(SPACE, keyboardType, SG_DESELECTED);
  drawSingleKey(OK, keyboardType, SG_DESELECTED);  
}

/*********************************************************/
char getKeyTouch(char keyboardType){ //ask for a touch and if VALID inside the keyboard returns the touched key
  char *data = (char*)keyboards[keyboardType];
  SG_POINT p;
  
  if(lcd.touchScreen(&p) == SG_VALID){ //ask for touch, if VALID
    if(p.y > KEY_Y_TOP && p.y< (KEY_Y_TOP+KEYBOARD_Y_SIZE)){ //if touch inside keyboard
      p.y -= KEY_Y_TOP;                                      //substract
      p.y /= (KEYBOARD_Y_SIZE/4);                            //obtain row
      //switch with the obtained row
      p.x--;
      switch(p.y){
        case 0: //1st row
          p.x /= KEYXSIZE; //obtain column 
        break;          
        case 1: //2nd row
          p.x -= (KEYXSIZE/2);
          p.x /= KEYXSIZE; //obtain column
          p.x += 10;
        break;      
        case 2: //3rd row
          p.x -= (KEYXSIZE/2);
          p.x /= KEYXSIZE; //obtain column
          p.x += 18;
          if(p.x==18) return TYPE;          
          if(p.x==26) return DEL;
        break;
        default: //4rt row
          p.x -= (KEYXSIZE/2);
          p.x /= KEYXSIZE; //obtain column
          if(p.x==0) return KEYCASE;          
          if(p.x>=8) return OK;
          return ' ';
        break;
      }
      return *(data+p.x);
    }
  }
  return 0;
}



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
void loop() { //main loop draw random colour, size and fill Arcs
  unsigned int currentX=5, lastX=5, currentY=5;
  char key = 0, currentKeyboard = LETTERSLOWER;
  
  lcd.baudChange(SG_BAUD6); //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!

  lcd.drawGradientRect(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1, SG_MAGENTA, SG_BLACK, SG_VERTICAL); //draw a background
  
  lcd.drawRectangle(5, 5, LCD_WIDTH-1-5, KEY_Y_TOP-5, SG_WHITE, SG_FILL); //draw text background
  lcd.setTextColour(SG_BLACK);                                            //set text colour as black
  lcd.setTextSize(SG_FONT2);                                              //set text size FONT2
       
  drawAllKeyboard(currentKeyboard);                                       //draw all keyboard
  
   while(1){
     while((key = getKeyTouch(currentKeyboard)) == 0x00);               //loop until get a valid key
     //once obtained a valid key
     if(key!=OK && key!=DEL && key!=TYPE && key!=KEYCASE){              //only print if key is not special key
       lcd.putLetter(lastX, currentY, key, &currentX);                  //print key on lastX and save updated value in currentX
       if(currentX<=lastX){                                             //if currentX couldn't advance, means end of X row
         currentY += 20;                                                //jump 1 row in Y axis
         if(currentY >= (KEY_Y_TOP-5)){                                 //if we reach the start of the keyboard
           currentY=5;
           lcd.drawRectangle(5, 5, LCD_WIDTH-1-5, KEY_Y_TOP-5, SG_WHITE, SG_FILL); //draw text background
         }
         lastX=5;                                                       //reset lastX       
         lcd.putLetter(lastX, currentY, key, &currentX);                //print key on new lastX and currentY            
       }
       lastX=currentX;                                                  //get new value
     }else{
       switch(key){
        case TYPE:
          if(currentKeyboard == LETTERSLOWER || currentKeyboard == LETTERSUPPER) currentKeyboard = NUMBERS; //go to next type
          else if(currentKeyboard == NUMBERS) currentKeyboard = SPECCHAR;
          else if (currentKeyboard == SPECCHAR) currentKeyboard = LETTERSLOWER;
          drawAllKeyboard(currentKeyboard);                             //update all keyboard
        break; 
        case DEL:
          lcd.drawRectangle(5, 5, LCD_WIDTH-1-5, KEY_Y_TOP-5, SG_WHITE, SG_FILL); //draw text background
          lastX=5;                                                      //reset lastX           
          currentY=5;                                                   //reset currentY          
        break;
        case KEYCASE:
          if(currentKeyboard == LETTERSLOWER) currentKeyboard = LETTERSUPPER;
          else if(currentKeyboard == LETTERSUPPER) currentKeyboard = LETTERSLOWER;
          drawAllKeyboard(currentKeyboard);                            //update all keyboard          
        break; 
        default: //key == OK
          //go to main menu - exit keyboard - or any other required action
        break;
       }
     } 
     //draw the animated key
     drawSingleKey(key, currentKeyboard, SG_SELECTED);                     //draw the obtained key button as SELECTED
     delay(200);                                                           //wait 200ms with key as SELECTED
     drawSingleKey(key, currentKeyboard, SG_DESELECTED);                   //draw the obtained key button as DESELECTED     
   }
}
