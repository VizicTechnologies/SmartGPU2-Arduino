/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2014.
THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
ANY DEFENCE THEREOF), ANYg CLAIMS FOR INDEMNITY OR CONTRIBUTION,
OR OTHER SIMILAR COSTS.
*********************************************************/

/********************************************************
 IMPORTANT : This Example is created for the Arduino 1.0 Software IDE
********************************************************/

#include <SMARTGPU2.h>      //include the SMARTGPU2 library!

SMARTGPU2 lcd;              //create our object called LCD

AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution

//Calculator defines
#define OPERANDLENGHT  5    //A max of 5 digits per operand
#define DISPLAYCOLOUR 0xD6B6
//symbols in the calculator panel
const char panelSymbols[5][4]={{'E','I',0x2F,'*'},{'7','8','9','-'},{'4','5','6','+'},{'1','2','3','='},{'0','0','.','='}}; //0x2F eq /  

//declare our structures POINT and ICON
POINT point;
ICON icon;

//Main applications, the next applications are called by the main loop menu
/**************************************************/
/**************************************************/
/**************************************************/
/**************************************************/
//calc application
void calculator(){
  unsigned char col=0,row=0,i=0;
  char symbol=0,select=0,operationSymbol=0;
  char firstOperand[OPERANDLENGHT]={0};
  char secondOperand[OPERANDLENGHT]={0};
  double result=0;
          
  //load design
  lcd.imageBMPSD(0,0,"Calculator");                                            //draw image
  
  //strings config
  lcd.setTextColour(BLACK);
  lcd.setTextBackColour(DISPLAYCOLOUR);
  lcd.setTextBackFill(FILLED);  
  lcd.setTextSize(FONT3);  
  lcd.string(224,34,255,65,"0",0);                                             //draw zero
  lcd.setTextSize(FONT0);
    
  //Start application
  while(1){
    while(lcd.touchScreen(&point)==INVALID && lcd.touchIcon(&icon)==INVALID);  //wait for a touch to do something
    if(lcd.touchIcon(&icon)==VALID) break;                                     //if the received touch was on any icon we go to main menu(EXIT APP) 

    delay(300);
    
    //decode touch into symbol
    if(point.x>74 && point.x<249 && point.y>73 && point.y<215){                //if touch inside panel
      col = ((point.x-74)/((249-74)/4));                                       //decode touch by substracting the x coord of panel start and dividing value by (panel size / 4 cols);      
      row = ((point.y-73)/((215-73)/5));                                       //decode touch by substracting the y coord of panel start and dividing value by (panel size / 5 rows);
    }else continue;                                                            //touch outside panel : go to upper while(1)

    //A valid touch on panel was done, decode the touch...
    symbol= panelSymbols[row][col];                                            //get digit or symbol
    
    if(select == 0){                                                           //get first operand
      if((symbol >= '0') && (symbol <= '9')){                                  //if the received digit is a number
        if(strlen((const char*)firstOperand) < OPERANDLENGHT)                  //add symbol only if the firstOperand is less than OPERANDLENGHT digits
          firstOperand[strlen((const char*)firstOperand)] = symbol;            //add the symbol to the firstOperand buffer
        lcd.string(80,36,LCD_WIDTH-1,LCD_HEIGHT-1,firstOperand,0);
      }else{                                        //received digit is something different than a number
        if((symbol=='*') || (symbol==0x2F) || (symbol=='+') || (symbol=='-')){ //if the received digit is an operation symbol
          operationSymbol = symbol;                                            //store type of operation to perform
          select=1;                                                            //turn select 1
          lcd.putLetter(80+(8*OPERANDLENGHT),36,operationSymbol,0);
        }else if(symbol == '='){                                               //if equal to =
        //ignore                                                               //ignore if received digit is equal symbol, can't perform operation now
        }else{                                                                 //erase contents on any other symbol AC or +/- or .
          lcd.drawRectangle(75,34,248,58,DISPLAYCOLOUR,FILL);                  //erase display
          select = operationSymbol= 0;                                         //reset digit and operation
          for(i=0;i<OPERANDLENGHT;i++) firstOperand[i]=0;                      //clear firstOperand buffer
          for(i=0;i<OPERANDLENGHT;i++) secondOperand[i]=0;                     //clear secondOperand buffer
          lcd.setTextSize(FONT3);  
          lcd.string(224,34,255,65,"0",0);   //draw zero          
          lcd.setTextSize(FONT0);            
        }
      }
    }else{                                                                     //get second operand
      if((symbol >= '0') && (symbol <= '9')){                                  //if the received digit is a number
        if(strlen((const char*)secondOperand) < OPERANDLENGHT)                 //add symbol only if the secondOperand is less than OPERANDLENGHT digits
          secondOperand[strlen((const char*)secondOperand)] = symbol;          //add the symbol to the secondOperand buffer
        lcd.string(90+(8*OPERANDLENGHT),36,LCD_WIDTH-1,LCD_HEIGHT-1,secondOperand,0);
      }else{                                                                   //received digit is something different than a number
        if((symbol=='*') || (symbol==0x2F) || (symbol=='+') || (symbol=='-')){ //if the received digit is an operation symbol
        //ignore                                                               //ignore if received digit is again an operation type(already set)
        }else if(symbol == '='){                                               //if equal to = then perform operation
          switch(operationSymbol){
            case '+':
              result  = atof(firstOperand);
              result += atof(secondOperand);
            break;
            case '-':
              result  = atof(firstOperand);
              result -= atof(secondOperand);
            break;
            case '*':
              result  = atof(firstOperand);
              result *= atof(secondOperand);
            break;
            case 0x2F:                                                         //division
              result  = atof(firstOperand);
              result /= atof(secondOperand);
            break;            
            default:
            break;
          }
          lcd.drawRectangle(75,34,248,58,DISPLAYCOLOUR,FILL);                  //erase display          
          lcd.setTextSize(FONT3);
          lcd.putLetter(80,36,'=',0);          
          lcd.printNumber(95,34,(float)result);
          
          while(lcd.touchScreen(&point)==INVALID);                             //wait for touch to start again          
          lcd.drawRectangle(75,34,248,58,DISPLAYCOLOUR,FILL);                  //erase display
          lcd.string(224,34,255,65,"0",0);                                     //draw zero
          lcd.setTextSize(FONT0);          
          select = operationSymbol = 0;                                        //reset digit and operation
          for(i=0;i<OPERANDLENGHT;i++) firstOperand[i]=0;                      //clear firstOperand buffer
          for(i=0;i<OPERANDLENGHT;i++) secondOperand[i]=0;                     //clear secondOperand buffer
          lcd.setTextSize(FONT3);  
          lcd.string(224,34,255,65,"0",0);                                     //draw zero          
          lcd.setTextSize(FONT0);          
        }else{                                                                 //erase contents on any other symbol AC or +/- or .
          lcd.drawRectangle(75,34,248,58,DISPLAYCOLOUR,FILL);                  //erase display
          lcd.string(224,34,255,65,"0",0);                                     //draw zero
          lcd.setTextSize(FONT0);          
          select = operationSymbol = 0;                                        //reset digit and operation
          for(i=0;i<OPERANDLENGHT;i++) firstOperand[i]=0;                      //clear firstOperand buffer
          for(i=0;i<OPERANDLENGHT;i++) secondOperand[i]=0;                     //clear secondOperand buffer
          lcd.setTextSize(FONT3);  
          lcd.string(224,34,255,65,"0",0);                                     //draw zero          
          lcd.setTextSize(FONT0);  
        }        
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
}

/**************************************************/
/****************** MAIN LOOP *********************/
/**************************************************/
/**************************************************/
void loop() { //main loop
  unsigned char ic;
  
  lcd.baudChange(BAUD5);           //set high baud for advanced applications

  while(1){
    calculator();                  //run calc app
  }  
}
