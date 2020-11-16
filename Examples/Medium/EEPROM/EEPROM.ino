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

/********************************************************
 This simple sketch does the next:
 1.- init/Clear EEPROM buffer with 0xFF - EEPROM buffer size is 2048 (2k)
 2.- write data 10 times to EEPROM buffer "0123456789"
 3.- compare EEPROM buffer contents with EEPROM PAGE0, if equal go to step 7, if not continue to step 4
 4.- erase EEPROM PAGE0
 5.- save current EEPROM buffer contents(100 x "0123456789") to EEPROM PAGE0
 6.- compare again EEPROM buffer contents with EEPROM PAGE0
 7.- show results on display
 8.- end
 
- once executed the above, remove power from SmartGPU and run sketch again, EEPROM contents will remain as they are non-volatile data
********************************************************/

#include <SMARTGPU2.h>      //include the SMARTGPU2 library!

SMARTGPU2 lcd;              //create our object called lcd

SG_AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution

unsigned int row=10;

/********************************************/
/********************************************/
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU2 support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU2 support
  lcd.start(); //initialize the SMARTGPU2 processor
  
  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);
}

/********************************************/
/********************************************/
/********************************************/
/********************************************/
void loop() { //main loop 
    char data[]="0123456789";
    unsigned int i=0;        
    unsigned char result=0;
    
    lcd.baudChange(SG_BAUD4);
    
    //strings config
    lcd.setTextColour(SG_GREEN);  
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"EEPROM page open, read, write demo!",0);   row+=30;
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"Performing procedure...",0);               row+=30;

    //ONCE WE START USING EEPROM BUFFER WE CAN'T CALL OTHER SMARTGPU FUNCTIONS DIFFERENT THAN EEPROM 'E' FUNCTIONS, AS EEPROM BUFFER WILL BE DISCARDED IF SO
    //init/Clear EEPROM buffer with 0xFF values
    lcd.initClearEEPROMBuff();

    //write data array 10 times to EEPROM buffer
    for(i=0; i < 10; i++){ 
      lcd.writeEEPROMBuff(data, i*10, 10, 0);
    }
    
    //verify contents - EEPROM buffer contents vs EEPROM PAGE0
    lcd.compBuffToEEPROMPage(SG_PAGE0, &result);  //compare EEPROM buffer contents with EEPROM PAGE0
    
    if(result == 1){  //if contents are equal - means that data was already written and its equal
        lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"EEPROM PAGE0 Contents were already equal...END",0);
    }else{            //if contents are different - erase PAGE0 and write EEPROM buffer into PAGE0 - This procedure will be executed only the veryfirst time
      //erase EEPROM SG_PAGE0
      lcd.eraseEEPROMPage(SG_PAGE0);
      //save current EEPROM buffer contents(100 x "0123456789") to EEPROM SG_PAGE0
      lcd.saveBuffToEEPROMPage(SG_PAGE0);            
      //verify contents again - EEPROM buffer contents vs EEPROM SG_PAGE0
      lcd.compBuffToEEPROMPage(SG_PAGE0, &result);  //compare EEPROM buffer contents with EEPROM PAGE0          

      if(result == 1){ //if contents are equal
        lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"New EEPROM PAGE0 Contents are equal...END",0);
      }else{           //error
        lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"New EEPROM PAGE0 Contents differ...END",0);
      }        
    }
    //loop forever
    while(1);
}
