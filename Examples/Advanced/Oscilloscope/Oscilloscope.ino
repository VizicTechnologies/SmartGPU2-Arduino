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
     DOES NOT WORK FOR DUE OR ANY OTHER THAN AVR PROCESSORS
 -------------MINIMUM INPUT VOLTAGE IS 0 VOLTS--------------------
--------------MAX INPUT VOLTAGE IS 3.3 VOLTS----------------------
********************************************************/

#include <SMARTGPU2.h>                     //include the SMARTGPU2 library!

SMARTGPU2 lcd;                             //create our object called LCD

SG_AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution

#define GRAY 0x528A                        //GRAY colour of the grid

//OSCILLOSCOPE DEFINES
#define PROBE_INPUT         A0             //select the input pin for the oscilloscope - A0 analog pin
#define MAX_INPUT_VOLTAGE   3.3            //maximum input voltage to the PROBE_INPUT pin

#define NUMBEROFVOLTSVALUES       6
#define NUMBEROFMILLISECVALUES    6
const float         voltsPerDivValues[NUMBEROFVOLTSVALUES]           = {0.1, 0.25, 0.5, 1.0, 1.5, 2.0};
const unsigned long millisecondsPerDivValues[NUMBEROFMILLISECVALUES] = {10, 50, 100, 250, 500, 1000};
unsigned char       voltsPerDivPointer=3, millisecondsPerDivPointer=3; //default start values 1voltPerDiv and 250mSecPerDiv

unsigned int sampleBuffer[450];                                //array to store ADC probe samples

//Display variables
SG_AXIS WIN_HORIZONTAL_START;
SG_AXIS WIN_VERTICAL_START;
SG_AXIS WIN_HORIZONTAL_END;
SG_AXIS WIN_VERTICAL_END;
SG_AXIS MAX_X;
SG_AXIS MAX_Y;
unsigned int MAX_SAMPLES;

/*********************************************************/
void initSampleBuffer(void){
  unsigned int i;
  for(i=0; i < MAX_SAMPLES; i++) sampleBuffer[i] = WIN_VERTICAL_END;
  sampleBuffer[0]= getScaledSample();  //get first sample
}

/*********************************************************/
void showIntro(void){
  int aux=5,xs,ys,i, time=30;
  SG_NUMBEROFBYTES nb;  

  lcd.setTextSize(SG_FONT4);
  lcd.string(2,2,MAX_X,MAX_Y,"SmartGPU 2 : Simple Oscilloscope", &nb);
  lcd.setTextSize(SG_FONT2);
  lcd.string(20,MAX_Y-35,MAX_X,MAX_Y,"Vizic Technologies 2020(c)", &nb);
  while(time--){
    //draw next circle
    xs=(sin(((aux*24)*3.14)/180)) * 40;
    ys=(cos(((aux*24)*3.14)/180)) * 40;
    lcd.drawCircle((LCD_WIDTH/2)+xs,(LCD_HEIGHT/2)-ys,2,SG_BLUE,SG_FILL); 
    //erase previous circle
    xs=(sin((((aux-5)*24)*3.14)/180)) * 40;
    ys=(cos((((aux-5)*24)*3.14)/180)) * 40;
    lcd.drawCircle((LCD_WIDTH/2)+xs,(LCD_HEIGHT/2)-ys,3,SG_BLACK,SG_FILL);    
    //increase vaiable aux
    if(aux++ > 13) aux=0;        
    delay(100);
  }
  lcd.erase();               //erase screen before exit 
}

/*********************************************************/
void wait_milliseconds_and_process_touch(void){ //wait the millisecondsPerDivValues[] parameter and process touch in the while
  SG_POINT point;
  SG_NUMBEROFBYTES nb;

  TCNT1=0;               //reset timer counter - timer counts one step every 4 microseconds 
  while(TCNT1 < ((millisecondsPerDivValues[millisecondsPerDivPointer]*(1000/4)) / ((MAX_SAMPLES)/5))){    //wait to reach scaled time
    if((lcd.touchScreen(&point)==SG_VALID) && (point.y > WIN_VERTICAL_END)){    //if a touch is received and if touch on volts per div or in mSec per div strings
      if(point.x < (LCD_WIDTH/2)){        //if touch on volts per div(left half of the screen)
        if(++voltsPerDivPointer >= NUMBEROFVOLTSVALUES) voltsPerDivPointer = 0;
      }else{                              //touch on mSec per div(right half of the screen)
        if(++millisecondsPerDivPointer >= NUMBEROFMILLISECVALUES) millisecondsPerDivPointer = 0;
      }
      lcd.drawRectangle(0,MAX_Y-20,MAX_X,MAX_Y,SG_GREEN,SG_FILL);  //erase previous strings
      lcd.string(20,MAX_Y-20,MAX_X,MAX_Y,"Volts/Div:",&nb);
      lcd.printNumber(110,MAX_Y-20,voltsPerDivValues[voltsPerDivPointer]);
      lcd.string(MAX_X-140,MAX_Y-20,MAX_X,MAX_Y,"mSec/Div:",&nb);
      lcd.printNumber(MAX_X-50,MAX_Y-20,millisecondsPerDivValues[millisecondsPerDivPointer]);   
      delay(250);
    }   
  }
}

/*********************************************************/
unsigned int getScaledSample(void){                        //get a sample and return a value scaled into window vertical size
  float value;
  value = analogRead(PROBE_INPUT);                         //Take a sample from the PROBE
  value = value * MAX_INPUT_VOLTAGE;                       //scale to max input voltage
  value = value / 1023;                                    //divide by the max input value of ADC
  value = value * ((WIN_VERTICAL_END - WIN_VERTICAL_START) / 5); //multiply value by the grid division value in pixels
  value = value / voltsPerDivValues[voltsPerDivPointer];   //finally divide the value by the volts per division parameter
  if(value > (WIN_VERTICAL_END - WIN_VERTICAL_START)) return WIN_VERTICAL_START;
  return WIN_VERTICAL_END - value;                         //return window vertical end substracting the scaled value
}

/*********************************************************/
void drawGrid(){
 unsigned int i;
 for(i=WIN_HORIZONTAL_START; i<=WIN_HORIZONTAL_END; i+=(WIN_HORIZONTAL_END - WIN_HORIZONTAL_START)/5)
   lcd.drawLine(i,WIN_VERTICAL_START,i,WIN_VERTICAL_END,GRAY);
 for(i=WIN_VERTICAL_START; i<=WIN_VERTICAL_END; i+=(WIN_VERTICAL_END - WIN_VERTICAL_START)/5)
   lcd.drawLine(WIN_HORIZONTAL_START,i,WIN_HORIZONTAL_END,i,GRAY);
}

/*********************************************************/
void updateScreen(void){
  static int drawPointer= 0;
  sampleBuffer[drawPointer+1]= getScaledSample();                                              //store a scaled sample
  lcd.drawLine(drawPointer+WIN_HORIZONTAL_START, sampleBuffer[drawPointer], drawPointer+WIN_HORIZONTAL_START+1, sampleBuffer[drawPointer+1], SG_YELLOW);        //draw fresh sample
  drawPointer++;
  if((drawPointer+2) >= MAX_SAMPLES){
    drawGrid();                                                                              //re-draw Grid
    drawPointer = 0;  
  }
  lcd.drawLine(drawPointer+WIN_HORIZONTAL_START+1, sampleBuffer[drawPointer+1], drawPointer+WIN_HORIZONTAL_START+2, sampleBuffer[drawPointer+2], SG_BLACK);         //erase old sample
}

/*********************************************************/
void drawInterface(void){
  SG_NUMBEROFBYTES nb;

  lcd.drawGradientRect(0, 0, MAX_X, MAX_Y, SG_BLUE, SG_GREEN, SG_VERTICAL);                              //draw background
  lcd.drawRectangle(WIN_HORIZONTAL_START, WIN_VERTICAL_START, WIN_HORIZONTAL_END, WIN_VERTICAL_END, SG_BLACK, SG_FILL);   //draw plotting area
  drawGrid();
  lcd.setTextSize(SG_FONT1);
  lcd.string(2,2,MAX_X,30,"SmartGPU 2 - Simple Oscilloscope", &nb);
  lcd.setTextColour(SG_BLACK);
  lcd.drawRectangle(0,MAX_Y-20,MAX_X,MAX_Y,SG_GREEN,SG_FILL);
  lcd.string(20,MAX_Y-20,MAX_X,MAX_Y,"Volts/Div:",&nb);
  lcd.printNumber(110,MAX_Y-20,voltsPerDivValues[voltsPerDivPointer]);
  lcd.string(MAX_X-140,MAX_Y-20,MAX_X,MAX_Y,"mSec/Div:",&nb);
  lcd.printNumber(MAX_X-50,MAX_Y-20,millisecondsPerDivValues[millisecondsPerDivPointer]);     
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

  //Display defines
  MAX_X                = LCD_WIDTH-1;
  MAX_Y                = LCD_HEIGHT-1;
  WIN_HORIZONTAL_START = 10;            //start pixel for the horizontal window
  WIN_VERTICAL_START   = 25;            //start pixel for the vertical window
  WIN_HORIZONTAL_END   = LCD_WIDTH-WIN_HORIZONTAL_START;   //size in pixels of the vertical window
  WIN_VERTICAL_END     = LCD_HEIGHT-WIN_VERTICAL_START;  //size in pixels of the vertical window
  MAX_SAMPLES          = WIN_HORIZONTAL_END - WIN_HORIZONTAL_START;  //must be the substraction of those 2 numbers 

  //oscilloscope configurations
  //set analog reference as EXTERNAL to avoid damage to arduino boards when using smartGPU2 as shield!
  //analogReference(EXTERNAL); //which AREF is connected to 3.3V of SmartGPU2 board
  pinMode(PROBE_INPUT, INPUT);
  
  // Timer/Counter 1 initialization
  // Clock source: System Clock
  // Clock value: 250.000 kHz
  // Mode: Normal top=0xFFFF
  TCCR1A=0x00;
  TCCR1B=0x03;  //timer will increase count one step every 4 microseconds
   
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/
void loop() { //main loop draw random colour, size and fill Ellipses    
  lcd.baudChange(SG_BAUD6); //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!
  
  showIntro();              //a Small intro  
  initSampleBuffer();       //initialize the sample Buffer to lowest value possible
  drawInterface();          //draws all the oscilloscope body and interface

   
  while(1){//forever
    wait_milliseconds_and_process_touch();       
    updateScreen(); 
  }
}
