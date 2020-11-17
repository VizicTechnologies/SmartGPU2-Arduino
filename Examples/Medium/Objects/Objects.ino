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
    SG_POINT point;
    unsigned char progress=0;
    char sliderPosition=49, scrollPosition=4;
    
    lcd.baudChange(SG_BAUD6); //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!

//DRAW INITIAL STATE/VALUES OBJECTS
    //draw the object window
    lcd.objWindow(0,0,LCD_WIDTH-1,LCD_HEIGHT-1, SG_FONT1, SG_SELECTEDGRAY, "objects window");
    //draw the object slider
    lcd.objSlider(10, 80, 309, 115, sliderPosition, 100, SG_HORIZONTAL); //draw the slider  with 100 divisions and 49 as current position
    //draw the object scroll bar
    lcd.objScrollBar(10, 125, 309, 160, scrollPosition, 10, SG_HORIZONTAL, SG_DESELECTED); //draw the scroll bar with 10 divisions and 4 as current position
    //draw the object button1 and button2
    lcd.objButton(10, 170, 150, 220, SG_DESELECTED, "button 1");
    lcd.objButton(170, 170, 309, 220, SG_DESELECTED, "button 2");     
     
//LOOP FOREVER AND DRAW ONLY IF TOUCH ON OBJECT     
    while(1){
   
      //draw the object progress bar - this is the only object that doesn't wait for a touch, it just updates automatically each delay cycle
      lcd.objProgressBar(10, 40, 309, 70, progress++); //draw the progress bar with the "progress" variable value
      if(progress>100) progress = 0;   
 
      //ask for a touch
      if(lcd.touchScreen(&point)==SG_VALID){ //if a touch on screen is valid
        //IF SLIDER
        if(point.y>80 && point.y<115){ //if the touch on the slider
          sliderPosition = ((point.x*100)/(309-10)); //scale the value and set it to sliderPosition
          //draw the object slider with currently obtained scaled touch value
          lcd.objSlider(10, 80, 309, 115, sliderPosition, 100, SG_HORIZONTAL); //draw the slider  with 100 divisions and "sliderPosition" variable value                  
        }
        //IF SCROLLBAR        
        if(point.y>125 && point.y<160){ //if the touch on the scroll bar
          if(point.x>(309-SG_SCROLLBUTTONSIZE)){ //if touch is on the right > button
            scrollPosition++;          
            if(scrollPosition>9) scrollPosition=9;              
            //draw the object scroll bar as SELECTED
            lcd.objScrollBar(10, 125, 309, 160, scrollPosition, 10, SG_HORIZONTAL, SG_SELECTED); //draw the scroll bar with 10 divisions and "scrollPosition" variable value                      
          }else if(point.x<SG_SCROLLBUTTONSIZE){             //if touch is on the left < button
            scrollPosition--;  
            if(scrollPosition<0) scrollPosition=0;
            //draw the object scroll bar as SELECTED
            lcd.objScrollBar(10, 125, 309, 160, scrollPosition, 10, SG_HORIZONTAL, SG_SELECTED); //draw the scroll bar with 10 divisions and "scrollPosition" variable value    
          }
          delay(50);
          lcd.objScrollBar(10, 125, 309, 160, scrollPosition, 10, SG_HORIZONTAL, SG_DESELECTED); //draw the scroll bar with 10 divisions and "scrollPosition" variable value        
        }
        //IF BUTTON1        
        if(point.y>170 && point.y<220 && point.x<160){ //if the touch on button1
          //draw the object button1 as SG_SELECTED
          lcd.objButton(10, 170, 150, 220, SG_SELECTED, "button 1");
          delay(50);
          lcd.objButton(10, 170, 150, 220, SG_DESELECTED, "button 1");
        }
        //IF BUTTON2        
        if(point.y>170 && point.y<220 && point.x>160){ //if the touch on button2
          //draw the object button2 as SG_SELECTED
          lcd.objButton(170, 170, 309, 220, SG_SELECTED, "button 2");
          delay(50);
          lcd.objButton(170, 170, 309, 220, SG_DESELECTED, "button 2");
        }
      }
      //update objects each 100 milliseconds
      delay(100);      
   }
}
