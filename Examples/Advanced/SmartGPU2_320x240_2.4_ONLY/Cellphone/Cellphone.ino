/*********************************************************
 * VIZIC TECHNOLOGIES. COPYRIGHT 2020.
 * THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
 * VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
 * ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
 * LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
 * ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
 * ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
 * OR OTHER SIMILAR COSTS.
 *********************************************************/

/********************************************************
 * IMPORTANT : This Example is created for the Arduino 1.0 Software IDE
 ********************************************************/

#include <SMARTGPU2.h>      //include the SMARTGPU2 library!

SMARTGPU2 lcd;              //create our object called LCD

SG_AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution

//declare our general coodinates structs
SG_POINT point;
SG_ICON icon;

//Global variables
//Start time: hours = 2, minutes = 19, seconds = 33;
int clockTime= (2*(60*60)) + (19*60) + (33); //In seconds

char contactName[7][20]={
  "Adam Playford","Akash Krishnani","Alexis Barta","Alice Alcantara","Amanda Bannout","Andrea Jahanbozorg","Anna Kaltenbrunner"};

//Main applications, the next applications are called by the main loop menu
/**************************************************/
/**************************************************/
/**************************************************/
/**************************************************/
//clock application THIS METHOD IS 100% RECOMMENDED TO BE EXECUTED WITH TIMER INTERRUPTS, BUT DUE TO SKETCH SIMPLICITY WE CREATED THIS WITH DELAYS INSTEAD OF TIMERS
char clocks(unsigned char drawHands){
 SG_NUMBEROFBYTES nb;
  int xs,ys,xm,ym,xh,yh,i;
  int angleH,angleM,angleS;
  int halfx=208 ,halfy=50, radiusClk=25; //Clock related sizes  
  int handHour=16;                       //hand size
  int handMin=20;                        //hand size
  int handSec=23;                        //hand size 
  char tim[9]={
    0x30,0x30,':',0x30,0x30,':',0x30,0x30,0x00            };
  int hrs,secs,mins;

  lcd.setTextColour(SG_WHITE);
  lcd.setTextSize(SG_FONT1);
  lcd.setTextBackFill(SG_FILLED);    

  while(1){                              //we loop between clocks until a touch on something
    if(drawHands==1){   
      lcd.drawCircle(halfx,halfy,radiusClk,SG_WHITE,SG_FILL);
      lcd.drawCircle(halfx,halfy,radiusClk,SG_BLUE,SG_UNFILL);    
    }    
    while(1){
      //time update managing
      hrs  = ((clockTime+(millis()/1000))/(60*60));
      while(hrs >= 12){ hrs = hrs-12; }                     // correct if more than 12 hrs
      mins = (((clockTime+(millis()/1000))%(60*60))/60);
      secs = (((clockTime+(millis()/1000))%(60*60))%60);
           
      //Do some Math to get the second point of the clock hands. (first point is always the center of the clock)
      angleS=secs*6;                           //get the current seconds in angle form, a circle have 360 degrees divided by 60 seconds = 6, then we multiply the 6 by the current seconds to get current angle
      xs=(sin((angleS*3.14)/180)) * handSec;   //get X component of the second's hand
      ys=(cos((angleS*3.14)/180)) * handSec;   //get Y component of the second's hand
      angleM=mins*6;                           //get the current minutes in angle form, a circle have 360 degrees divided by 60 minutes = 6, then we multiply the 6 by the current minutes to get current angle
      xm=(sin((angleM*3.14)/180)) * handMin;   //get X component of the minutes's hand
      ym=(cos((angleM*3.14)/180)) * handMin;   //get Y component of the minutes's hand 
      angleH=hrs*30;                         //get the current hours in angle form, a circle have 360 degrees divided by 12 hours = 30, then we multiply the 30 by the current hours to get current angle
      xh=(sin((angleH*3.14)/180)) * handHour;  //get X component of the hours's hand
      yh=(cos((angleH*3.14)/180)) * handHour;  //get Y component of the hours's hand

      //Draw current time hands if drawHands=1
      if(drawHands==1){ 
        lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,SG_BLACK);  // Draw the minutes hand, first point is the center of the clock, and the second is the point obtained by doing math
        lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,SG_BLACK);  // Draw the hours hand, first point is the center of the clock, and the second is the point obtained by doing math
        lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,SG_RED);    // Draw the seconds hand, first point is the center of the clock, and the second is the point obtained by doing math      
      }      
      //Draw text time on top of screen 
      tim[0]=(hrs/10)+0x30;                                // convert hours to ascii format
      tim[1]=(hrs%10)+0x30;                                // convert hours to ascii format
      tim[3]=(mins/10)+0x30;                               // convert mins to ascii format 
      tim[4]=(mins%10)+0x30;                               // convert mins to ascii format 
      tim[6]=(secs/10)+0x30;                               // convert secs to ascii format 
      tim[7]=(secs%10)+0x30;                               // convert secs to ascii format       
      lcd.string(170,3,LCD_HEIGHT-1,30,tim,&nb);     

      for(i=0;i<100;i++){                                   // loop for about one second delay (we dont need to explain why we're waiting one second, right?)
        if(lcd.touchScreen(&point)){                        //if we receive a touch on screen
          return 0;                                         //Exit clock
        }
        delay(10);
      }
                    
      //Erase all hands    
      if(drawHands==1){       
        lcd.drawLine(halfx,halfy,halfx+xs,halfy-ys,SG_WHITE); // Erase Second's hand
        lcd.drawLine(halfx,halfy,halfx+xm,halfy-ym,SG_WHITE); // Erase Minute's hand
        lcd.drawLine(halfx,halfy,halfx+xh,halfy-yh,SG_WHITE); // Erase Hour's hand            
      }
    }
  }    
}

/**************************************************/
/**************************************************/
//notes application
void notes(){

  lcd.imageBMPSD(0,0,"noteP");                //load notes design
  delay(350);                                 //A little delay to avoid fast image changing

  while(1){          
    clocks(0);                                //run clock
    if(point.y<65){                           //Touch on upper Icons
      if(point.x<65){
        break;
      }
      else if(point.x>190){
        lcd.imageBMPSD(0,0,"noteP");            //load notes design       
      }          
    }
    else if(point.y<270){             //touch on notepad
      lcd.drawCircle(point.x,point.y,2,SG_BLACK,SG_FILL);          
    }
    else{                                   //touch on Main Icons
      if(point.x<60){
        keypad();
      }
      else if(point.x<120){
        logs(); 
      }
      else if(point.x<180){
        apps();
      }
      else{
        contacts();
      }  
      break;
    }                                
  }                                 
}

/**************************************************/
/**************************************************/
//maps application
void maps(){
  SG_NUMBEROFBYTES nb;
  char mapsOnSDCard[10][9]={
    "map0","map1","map2","map3","map4","map5","map6","map7","map8","map9"            }; //array containing the names of the different called maps  
  static char maps=0;

  lcd.orientation(SG_LANDSCAPE_LEFT);                 //change to landscape Left mode 
  lcd.setTextColour(SG_RED);
  lcd.setTextSize(SG_FONT2);
  lcd.setTextBackFill(SG_TRANS);    
  while(1){                                       //Loop forever in the slide show!
    lcd.imageBMPSD(0,0,mapsOnSDCard[maps]);       //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.string(70,215,319,239,"Tap center to Exit",&nb); //Show text
    lcd.imageBMPSD(5,25,"barmap");                //draw zoom bar    
    lcd.imageBMPSD(300,25,"barmap");              //draw zoom bar 
    delay(250);                                   //A little delay to avoid fast image changing    
    while(lcd.touchScreen(&point)==SG_INVALID);   //wait for a touch to do something
    //check if we go to the next image, or to the previous one
    if(point.x>100 & point.x<219){  //touch on center, EXIT
      break;    
    }
    else{                                     //touch on bars
      if(point.y<120){                   //touch on upper side of zoom bar
        maps++;
        if(maps>10){
          maps=10;
        }
      }
      else{                                   //touch on lower side of zoom bar
        maps--;
        if(maps<1){
          maps=1;  
        }          
      }       
    }
  }  
  lcd.orientation(SG_PORTRAIT_LOW);                  //change to portrait mode    
} 

/**************************************************/
/**************************************************/
//settings application, brightness adjust
void settings(){
  static int bright=169;                                       //Maximum bright is set by default
  static int buttonCen=197;                                    //button center, static variables to avoid losing the parameters even if we go to main menu

  lcd.imageBMPSD(0,0,"Settings");                                 //Load image from SD card, image is 320x240(full screen) so we load it from top left corner X:0,Y:0   
  delay(350);                                //A little delay to avoid fast image changing
  //Start application
  while(1){                                 
    lcd.drawRectangle((bright)+33,103,201,105,SG_WHITE,SG_FILL);  //draw the white bar   
    lcd.drawRectangle(33,103,(bright)+33,105,0x4C7C,SG_FILL);     //draw brightness bar
    lcd.imageBMPSD(buttonCen,96,"button");                        //Load the button icon    
    clocks(0);                                                    //run clock   
    if(point.y<270){                                              //Touch on bar
      lcd.imageBMPSD(buttonCen,96,"clrBar");                      //clear the button icon  
      //check where to move left or right
      if(point.x>buttonCen){                                   //if we need to move the bar to the right        
        bright+=10;                                            //increase the brightness
        buttonCen+=10;                                         //increase the center of the button
        if(bright>169){                                        //if the button reach the right corner
          bright=169;                                          //set maximum bright
          buttonCen=197;                                       //set maximum button center          
        }              
      }
      else{                                                    //move the bar to the left                                          
        bright-=10;                                            //decrease the brightness
        buttonCen-=10;                                         //decrease the center of the button
        if(bright<1){                                          //if the button reach the left corner
          bright=1;                                            //set minimum bright
          buttonCen=28;                                        //set minimum button center          
        }           
      }
      lcd.bright(bright+20);                                   //set new brightness value to SMART GPU        
    }
    else{                                                      //touch on Main Icons
      if(point.x<60){
        keypad();
      }
      else if(point.x<120){
        logs();
      }
      else if(point.x<180){
        apps();
      }
      else{
        contacts();
      }
      break;      
    }
  } 
}

/**************************************************/
/**************************************************/
//calendar application
void calendar(){
  lcd.imageBMPSD(0,0,"Calendar");                //load contacts
  delay(350);                                //A little delay to avoid fast image changing
  //Start application
  while(1){                                  
    clocks(0);                                 //run clock        
    if(point.y>270){                    //touch on main icons
      if(point.x<60){
        keypad();
      }
      else if(point.x<120){
        logs();
      }
      else if(point.x<180){
        apps();
      }
      else{
        contacts();
      }
      break;      
    }    
  }     
}

/**************************************************/
/**************************************************/
//photos application
void photos(){
  SG_NUMBEROFBYTES nb;
  char imagesOnSDCard[8][9]={
    "Sea","Lake","Rainbow","Beach","House","House","Bridge","Trees"            }; //array containing the names of the different called images
  static char pic=0;

  lcd.setTextColour(SG_RED);
  lcd.setTextSize(SG_FONT2);
  lcd.setTextBackFill(SG_TRANS);  

  lcd.orientation(SG_LANDSCAPE_LEFT);              //change to landscape Left mode  
  while(1){  
    lcd.imageBMPSD(0,0,imagesOnSDCard[pic]);   //Load image from SD card, all images are 320x240(full screen) so we load them from top left corner X:0,Y:0
    lcd.imageBMPSD(3,219,"prev");              //Load the prev icon        
    lcd.imageBMPSD(300,219,"next");            //Load the next icon
    lcd.string(70,215,319,239,"Tap center to Exit",&nb); //Show text
    delay(350);                                //A little delay to avoid fast image changing    
    while(lcd.touchScreen(&point)==SG_INVALID);//wait for a touch to do something    
    //check if we go to the next image, or to the previous one
    if(point.x>219){                           //if the received touch was on the right corner of the screen we advance the image, else we decrease and go to previous image
      pic++;                                   //decrease image selector
      if(pic>7){                               //if we reach the position of the last image, we restart to image 0
        pic=0;                 
      }        
    }
    else if(point.x<100){
      pic--;    
      if(pic<0){                            //if we reach the position of the first image, we move to image 7
        pic=7;  
      }    
    }
    else{                                  //touch on center, EXIT      
      break;
    }   
  }
  lcd.orientation(SG_PORTRAIT_LOW);               //change to portrait mode  
} 

/**************************************************/
/**************************************************/
//keypad application
void keypad(){
  unsigned int auxNum=0,numPosition=5,numRow=70;

  lcd.imageBMPSD(0,0,"keypad");              //load keypad
  delay(250);                                //A little delay to avoid fast image changing

  //Start application
  while(1){                               
    clocks(0);                             //run clock        
    if(point.y>140){                //touch on keypad
      if(point.y<187){              //first row       
        if(point.x<60){
          auxNum='1'; 
        }
        else if(point.x<123){
          auxNum='2';
        }
        else if(point.x<185){
          auxNum='3';
        }
        else{
          auxNum=0x00;
        }
      }
      else if(point.y<231){        //second row
        if(point.x<60){
          auxNum='4'; 
        }
        else if(point.x<123){
          auxNum='5';
        }
        else if(point.x<185){
          auxNum='6';
        }
        else{
          call("Unknown Number");
          break;
        }              
      }
      else if(point.y<275){        //third row
        if(point.x<60){
          auxNum='7'; 
        }
        else if(point.x<123){
          auxNum='8';
        }
        else if(point.x<185){
          auxNum='9';
        }
        else{
          call("Unknown Number");
          break;
        }                    
      }
      else{                              //fourth row
        if(point.x<60){
          auxNum='*'; 
        }
        else if(point.x<123){
          auxNum='0';
        }
        else if(point.x<185){
          auxNum='#';
        }
        else{
          auxNum=0x00;
        } 
      }           
      if(auxNum==0){
        lcd.drawRectangle(0,70,239,140,SG_BLACK,SG_FILL);          //erase numbers
        numPosition=5;                                             //reset columns
        numRow=70;                                                 //reset Rows        
      }
      else{ 
        lcd.setTextColour(SG_WHITE);
        lcd.setTextSize(SG_FONT3);
        lcd.setTextBackFill(SG_FILLED);         
        lcd.putLetter(numPosition,numRow,auxNum,&numPosition); //write numbers
        if(numPosition>209){                                       //if we reach column end
          numRow+=32;                                              //jump to next row
          numPosition=5;                                           //reset numPosition(columns)
          if(numRow>102){                                          //if we reach end of rows
            numRow=70;                                             //reset Rows
            lcd.drawRectangle(0,70,239,140,SG_BLACK,SG_FILL);      //erase numbers
          }
        }      
      }
      delay(200);      
    }
    else if(point.y<70){                                    //touch on main icons
      if(point.x>180){
        contacts();
      }
      else if(point.x>120){
        apps();
      }
      else if(point.x>60){
        logs();
      }
      break;                                                       //Exit to main menu      
    }           
  }     
}

/**************************************************/
/**************************************************/
//Call application
char call(char *contact){
  SG_NUMBEROFBYTES nb;
  unsigned char i;

  lcd.imageBMPSD(0,0,"Call");                              //load call window 
  delay(250);                                //A little delay to avoid fast image changing  
  lcd.setTextColour(SG_GREEN);
  lcd.setTextSize(SG_FONT0);
  lcd.setTextBackFill(SG_TRANS);    
  lcd.string(48,190,192,225,contact,&nb); //show contact
  while(1){
    /*If a real GSM GPRS module is connected, here goes the comamnd tha executes the call to
     *  the "contact" number
     */
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,170,5,SG_YELLOW,SG_FILL);
      if(lcd.touchScreen(&point)){               //if we receive a touch on screen
        if(point.y>280) return 0;                //Break and return
      }    
      delay(300);      
    }
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,170,5,SG_BLACK,SG_FILL);
      if(lcd.touchScreen(&point)){              //if we receive a touch on screen
        if(point.y>280) return 0;               //Break and return
      }    
      delay(300);      
    }       
  }
}

/**************************************************/
/**************************************************/
//Logs application
void logs(){
  lcd.imageBMPSD(0,0,"Logs");                    //load calls
  delay(400);                                //A little delay to avoid fast image changing
  //Start application
  while(1){                                  
    clocks(0);                                 //run clock        
    if(point.y>270){                    //touch on main icons
      if(point.x>180){
        contacts();
      }
      else if(point.x>120){
        apps();
      }
      else if(point.x<60){
        keypad();
      }
      break;      
    }    
  }     
}

/**************************************************/
/**************************************************/
//Apps
void apps(){

  lcd.imageBMPSD(0,0,"Apps");      //load Apps window 
  delay(350);                                //A little delay to avoid fast image changing  
  //Start application
  clocks(0);                     //run clock
  if(point.y<130){        //First Row        
    //obtain icon number
    if(point.x<79){       //if X coordinate is less than 79
      notes();      
    }
    else if(point.x<169){//if X coordinate is less than 169
      maps();
    }
    else{                      //if X coordinate is less than 239
      settings();      
    } 
  }
  else if(point.y<255){  //Second Row
    //obtain icon number
    if(point.x<79){       //if X coordinate is less than 79
      //clocks();                //IN WORK
    }
    else if(point.x<169){//if X coordinate is less than 169
      calendar();             
    }
    else{                      //if X coordinate is less than 239
      photos();      
    }             
  }
  else{                        //Third row Main Icons
    if(point.x<60){
      keypad();
    }
    else if(point.x<120){
      logs();
    }
    else if(point.x>180){
      contacts();
    }
  }
} 

/**************************************************/
/**************************************************/
//contacts application
void contacts(){
  unsigned char x;
  lcd.imageBMPSD(0,0,"Contacts");                //load contacts
  delay(350);                                //A little delay to avoid fast image changing
  //Start application
  while(1){                                 
    clocks(0);                                 //run clock        
    if(point.y>36 & point.y<270){ //touch on contacts
      x=(point.y-36)/34;                //get corresponding touch number contact
      call(contactName[x]);
      break;    
    }
    else if(point.y>270){              //touch on main icons
      if(point.x<60){
        keypad();
      }
      else if(point.x<120){
        logs();
      }
      else if(point.x<180){
        apps();      
      }
      break;      
    }    
  }     
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
}

/**************************************************/
/****************** MAIN LOOP *********************/
/**************************************************/
/**************************************************/
void loop() { //main loop
  unsigned char i,n; //icon variable

  lcd.baudChange(SG_BAUD6);          //For fast drawing we need a big baudRate. Note: if using Software Serial, use SG_BAUD2 or less!
  lcd.orientation(SG_PORTRAIT_LOW);  //change to portrait mode  

  lcd.SDFopenDir("Cellphone");       //Open the Cellphone folder that contains the images of the Application

  //Processing Intro
  lcd.imageBMPSD(0,20,"Intro");      //load main menu image  
  for(n=0;n<3;n++){
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,285,5,SG_YELLOW,SG_FILL);
      delay(200);      
    }
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,285,5,SG_BLACK,SG_FILL);
      delay(200);      
    }         
  }  

  //Main Menu
  while(1){                       //Forever loop
    lcd.orientation(SG_PORTRAIT_LOW);//change to portrait mode
    lcd.imageBMPSD(0,0,"Menu");   //load main menu image
    clocks(1);                     //Run clock app

    if(point.y>270){        //if Y coord is greater than 270       
      //obtain icon number and begin application based on touch icon number 
      if(point.x<60){       //if X coordinate is less than 60
        keypad();    
      }
      else if(point.x<120){//if X coordinate is less than 120
        logs();               
      }
      else if(point.x<180){//if X coordinate is less than 180
        apps();  
      }
      else{                      //then X coordinate is between 180-239
        contacts();        
      }    
    }
  }  
}
