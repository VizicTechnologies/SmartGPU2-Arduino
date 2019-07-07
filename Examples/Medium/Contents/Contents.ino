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
ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
OR OTHER SIMILAR COSTS.
*********************************************************/

/********************************************************
 IMPORTANT : This Example is created for the Arduino 1.0 Software IDE
********************************************************/

/********************************************************
 This simple sketch does the next:
 1.- list the dirs and files
 2.- print the number of dirs and files
 3.- print the names while they fit
********************************************************/

#include <SMARTGPU2.h>      //include the SMARTGPU2 library!

SMARTGPU2 lcd;              //create our object called lcd

AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution

FILERESULT res;             //create the variable that will store all SMARTGPU2 commands responses

unsigned int row=10;

//function that loops forever on error
void die(unsigned char response){ //if the response is different than OK, print and loop forever
  if(response!=F_OK){
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"Error on microSD... forever loop@",0);
    while(1);  
  }
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
void loop() { //main loop 
    char buffer[100]={0}; 
    unsigned int dirs=0, files=0, i=0;        
    
    //strings config
    lcd.setTextColour(GREEN);  
    lcd.setTextSize(FONT1);    
    
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"List dirs, files + print names demo!",0); row+=20;
    lcd.setTextSize(FONT0);        
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"List Dirs and Files...",0);             row+=15;
    res=lcd.SDFgetList(&dirs,&files);    //obtain dirs and files
    die(res);
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"Dirs:",0);
    lcd.printNumber(40,row,dirs); //print the obtained directories
    lcd.string(70,row,LCD_WIDTH-1,LCD_HEIGHT-1,"Files:",0);    
    lcd.printNumber(105,row,files); //print the obtained files    
    row+=15;

    //print dir names
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"Dir Names--------------------",0);             row+=12;
    for(i=0;i<dirs;i++){
      res=lcd.SDFgetDirName(i,buffer); //get Dir number i name in buffer
      die(res);
      lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,buffer,0); row+=12;      //print the name if fit
    }
    
    //print file names
    row+=10;
    lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,"File Names--------------------",0);             row+=12;
    for(i=0;i<files;i++){
      res=lcd.SDFgetFileName(i,buffer); //get Dir number i name in buffer
      die(res);
      lcd.string(10,row,LCD_WIDTH-1,LCD_HEIGHT-1,buffer,0); row+=12;      //print the name if fit
    }    
    
    while(1); //loop forever    
}
