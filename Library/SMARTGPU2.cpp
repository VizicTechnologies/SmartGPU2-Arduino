/*********************************************************
VIZIC TECHNOLOGIES. COPYRIGHT 2019.
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
 ARDUINO SMARTGPU2 LIBRARY VERSION V6.0
 - Library supports any SmartGPU2 LCDXXXxXXX connected via SmartSHIELD board(for smartGPU2 4.3" and 7.0" smartSHIELD is always required)
 - Library supports the SmartGPU2 LCD320x240 2.4" mounted directly as shield by uncommenting the appropriate line below
 - Library supports the ARDUINO DUE board via SmartSHIELD by adding external jumpers to serial2 or serial3 port
 IMPORTANT : This library was created for the Arduino 1.8.9 Software IDE or newer
********************************************************/

#include <Arduino.h> 

#include "SMARTGPU2.h"

/****************************************************************/
//Communication Functions(PLATFORM DEPENDENT) - MODIFY TO FIT YOUR PLATFORM IF DIFFERENT THAN ARDUINO
/****************************************************************/
//Sends a single character through the serial port(USART)
void putcharTX(char data){
	SERIALPORT.write(data);
}

//Returns a single character obtained from the serial port(USART)
char getcharRX(){
	while(SERIALPORT.available() == 0);
	return SERIALPORT.read();
}

//Changes/Sets a new Baudrate to the Host processor
void setBaud(unsigned long newBaud){
	SERIALPORT.begin(newBaud);
}

//Performs a Hardware Reset on smartGPU2 RESET pin
void resetSmartGPU(){            //Reset the SMARTGPU2 board
	digitalWrite(RESET, LOW);    //Set the pin to GND to reset 
	delay(500);
	digitalWrite(RESET, HIGH);   //Set the pin to 5v to end reset
	delay(500);	
}

//Arduino Exclusive function - Configures the Hardware
void SMARTGPU2::init(){          //configure the arduino board for SMARTGPU2 board support
	analogReference(ARDUINOREFERENCE); //Set AREF pin Analog Reference (avoids damage to arduino boards if SG2 is mounted as arduino shield)
	setBaud(9600);                     //Default Arduino-SmartGPU2 communication Baudrate is 9600
	pinMode(RESET, OUTPUT);            //Configure pin as output
	digitalWrite(RESET, HIGH);         //Set the pin to 5v to exit reset	
}
 
 
/****************************************************************/
/****************************************************************/ 
/****************************************************************/
//SmartGPU2 Arduino Functions - DO NOT MODIFY DOWN FROM HERE
/****************************************************************/
/****************************************************************/
/****************************************************************/
SMARTGPU2::SMARTGPU2(){
	init();
}

SMARTGPUREPLY SMARTGPU2::reset(){       //Physically Reset the SMARTGPU2 board
  resetSmartGPU();
  return OK;
}

SMARTGPUREPLY SMARTGPU2::start(){       //Init the SMARTGPU2
  delay(500); 
  putcharTX('U');  
  delay(500);
  if(getcharRX() == OK){
	//SMALL WORKAROUND TO GET/OBTAIN THE LCD SCREEN SIZE IN PIXELS AS SMARTGPU2 DOES NOT SUPPORT THE GETWIDTH OR GETHEIGTH FUNCTIONS:
	//Obtain height and width by trying to draw pixels outside the screen resolution
	if(       putPixel(800-1, 480-1, BLACK) == OK ){ wid= 800; hei = 480; //SmartGPU2 7.0" 800x480
	}else if( putPixel(480-1, 320-1, BLACK) == OK ){ wid= 480; hei = 320; //SmartGPU2 3.5" 480x320
	}else if( putPixel(480-1, 272-1, BLACK) == OK ){ wid= 480; hei = 272; //SmartGPU2 4.3" 480x272
	}else if( putPixel(320-1, 240-1, BLACK) == OK ){ wid= 320; hei = 240; //SmartGPU2 2.4" 320x240
	}else if( putPixel(160-1, 128-1, BLACK) == OK ){ wid= 160; hei = 128; //SmartGPU2 1.8" 160x128
	}else{ return FAIL;
	}
	return OK;
  }else{
	return FAIL;
  }
}

/****************************************************************/
//Master Functions
/****************************************************************/
SMARTGPUREPLY SMARTGPU2::erase(){       //Erase the SMARTGPU2 screen
  putcharTX('M');             //Master function
  putcharTX('E'); 
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::sleep(STATE state){       //Send SMARTGPU2 to sleep mode
  putcharTX('M');             //Master function
  putcharTX('Z'); 
  putcharTX(state);
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::orientation(LCDORIENTATIONS side){       //Change display orientation
  putcharTX('M');             //Master function
  putcharTX('O'); 
  putcharTX(side);
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::bright(unsigned char val){       //Change display brightness
  putcharTX('M');             //Master function
  putcharTX('B'); 
  putcharTX(val);
  return (SMARTGPUREPLY)getcharRX();
}

// SMART GPU 2 DEFAULT/INITIAL BAUD RATE: 9600bps
SMARTGPUREPLY SMARTGPU2::baudChange(unsigned long baud){       //Change baud rate of arduino and SMARTGPU2 board
  unsigned char aux;

  putcharTX('M');             //Master function  
  putcharTX('X');
  putcharTX(baud>>24);
  putcharTX(baud>>16);
  putcharTX(baud>>8);
  putcharTX(baud);
  aux=getcharRX();
  if(aux=='O'){ //if command is successfull, change baudrate, if not just leave and return 'F'
	delay(150);
	setBaud(baud);
	delay(200);
	return (SMARTGPUREPLY)getcharRX();
  }else{
	return (SMARTGPUREPLY)aux;
  }
}

SMARTGPUREPLY SMARTGPU2::setEraseBackColour(COLOUR colour){       //Change the default screen background colour for erase function
  putcharTX('M');             //Master function
  putcharTX('C');             //Background Colour
  putcharTX(colour>>8);
  putcharTX(colour); 
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::getWidth(AXIS *w){
	*w = wid;
	return OK;
}

SMARTGPUREPLY SMARTGPU2::getHeight(AXIS *h){
	*h = hei;
	return OK;
}

/****************************************************************/
//Geometric Functions
/****************************************************************/
SMARTGPUREPLY SMARTGPU2::putPixel(AXIS x, AXIS y, COLOUR colour){       //Draw a pixel on the screen
  putcharTX('G');             //Geometric function 
  putcharTX('P'); 
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(colour>>8);
  putcharTX(colour);
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::drawLine(AXIS x1, AXIS y1, AXIS x2, AXIS y2, COLOUR colour){       //Draw a line on the screen
  putcharTX('G');             //Geometric function  
  putcharTX('L'); 
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);  
  putcharTX(colour>>8);
  putcharTX(colour);
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::drawRectangle(AXIS x1, AXIS y1, AXIS x2, AXIS y2, COLOUR colour, FILLGEOM fill){       //Draw a rectangle on the screen
  putcharTX('G');             //Geometric function 
  putcharTX('R');             //Rectangle   
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);  
  putcharTX(colour>>8);
  putcharTX(colour);
  putcharTX(fill);  
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::drawRoundRect(AXIS x1, AXIS y1, AXIS x2, AXIS y2, RADIUS radius, COLOUR colour, FILLGEOM fill){      //Draw a rounded rectangle on the screen
  putcharTX('G');             //Geometric function 
  putcharTX('O');             //Rounded Rectangle   
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);  
  putcharTX(radius>>8);
  putcharTX(radius);   
  putcharTX(colour>>8);
  putcharTX(colour);
  putcharTX(fill);  
  return (SMARTGPUREPLY)getcharRX();
}
	
SMARTGPUREPLY SMARTGPU2::drawGradientRect(AXIS x1, AXIS y1, AXIS x2, AXIS y2, COLOUR firstColour, COLOUR lastColour, ORIENTATIONPARAMETER direction){
  putcharTX('G');             //Geometric function 
  putcharTX('G');             //Gradient rectangle function
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);  
  putcharTX(firstColour>>8);
  putcharTX(firstColour);
  putcharTX(lastColour>>8);
  putcharTX(lastColour);  
  putcharTX(direction);  
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::drawTriangle(AXIS x1, AXIS y1, AXIS x2, AXIS y2, AXIS x3, AXIS y3, COLOUR colour, FILLGEOM fill){       //Draw a triangle on the screen
  putcharTX('G');             //Geometric function  
  putcharTX('T'); 
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);  
  putcharTX(x3>>8); 
  putcharTX(x3);
  putcharTX(y3>>8);
  putcharTX(y3);    
  putcharTX(colour>>8);
  putcharTX(colour);
  putcharTX(fill);  
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::drawArc(AXIS x, AXIS y, RADIUS radiusx, RADIUS radiusy, ARCQUADRANT quadrant, COLOUR colour, FILLGEOM fill){ //Draw an Arc on the screen
  putcharTX('G');             //Geometric function  
  putcharTX('A');             //Arc
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(radiusx>>8);
  putcharTX(radiusx);
  putcharTX(radiusy>>8);
  putcharTX(radiusy);  
  putcharTX(quadrant);
  putcharTX(colour>>8);
  putcharTX(colour);
  putcharTX(fill);  
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::drawCircle(AXIS x, AXIS y, RADIUS radius, COLOUR colour, FILLGEOM fill){       //Draw a circle on the screen
  putcharTX('G');             //Geometric function  
  putcharTX('C');             //Circle 
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(radius>>8);
  putcharTX(radius);
  putcharTX(colour>>8);
  putcharTX(colour);
  putcharTX(fill);  
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::drawEllipse(AXIS x, AXIS y, RADIUS radiusx, RADIUS radiusy, COLOUR colour, FILLGEOM fill){       //Draw an Ellipse on the screen
  putcharTX('G');             //Geometric function 
  putcharTX('E');             //Ellipse 
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(radiusx>>8);
  putcharTX(radiusx);
  putcharTX(radiusy>>8);
  putcharTX(radiusy);  
  putcharTX(colour>>8);
  putcharTX(colour);
  putcharTX(fill);  
  return (SMARTGPUREPLY)getcharRX();
}


/****************************************************************/
//String Functions
/****************************************************************/
SMARTGPUREPLY SMARTGPU2::putLetter(AXIS x, AXIS y, char letter, AXIS *xUpdated){  //Draw a letter on the screen on X,Y coords, returns updated value of X axis in xUpdated variable
  unsigned int xUp = 0;          //variable to store the updated position of X axis after command is called/char is printed
  
  putcharTX('S');             //String Function 
  putcharTX('L');             //Letter - a simple letter
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(letter); 

  ((unsigned char*)&xUp)[1]=getcharRX();
  ((unsigned char*)&xUp)[0]=getcharRX();  

  *xUpdated = xUp;
  return (SMARTGPUREPLY)getcharRX();  
}

SMARTGPUREPLY SMARTGPU2::printNumber(AXIS x, AXIS y, float number){ //Prints a float number on screen
  putcharTX('S');           //String Function 
  putcharTX('N');           //Number
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(((char *)&number)[3]);
  putcharTX(((char *)&number)[2]);
  putcharTX(((char *)&number)[1]);
  putcharTX(((char *)&number)[0]);    
  return (SMARTGPUREPLY)getcharRX();
}

//function only for the SmartGPU2 LCD480x272 4.3" and SmartGPU2 LCD800X480 7.0", function only available on those processors
SMARTGPUREPLY SMARTGPU2::printSpecialNumber(AXIS x1, AXIS y1, AXIS x2, AXIS y2, float number, unsigned char precision, unsigned char minNums){//Prints a float number on screen with special given parameters
  putcharTX('S');           //String Function 
  putcharTX('U');           //Special Number
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2); 
  putcharTX(((char *)&number)[3]);
  putcharTX(((char *)&number)[2]);
  putcharTX(((char *)&number)[1]);
  putcharTX(((char *)&number)[0]); 
  putcharTX(precision);              // Precision numbers after the decimal point, pass this parameter as 0 to remove decimal point
  putcharTX(minNums);                // Minimum numbers to be printed including sign(1) + integer part + decimal point(1) + decimal part, if size in numbers is less than this parameter, result will be left padded with zeros
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::string(AXIS x1, AXIS y1, AXIS x2, AXIS y2, char text[], NUMBEROFBYTES *SPB){    //Draw a string on the screen on defined Text Box coords, and stores the successfully printed bytes on SPB
  unsigned int counter=0, sp=0; 
  
  putcharTX('S');             //String Function 
  putcharTX('S');             //String 
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);   
  while(1){
	putcharTX(text[counter]);
    if(text[counter]==0x00){
      break;
	}	
	counter++;
  }  

  ((unsigned char*)&sp)[1]=getcharRX();
  ((unsigned char*)&sp)[0]=getcharRX();

  *SPB = sp;
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::stringSD(AXIS x1, AXIS y1, AXIS x2, AXIS y2, NUMBEROFBYTES BS, NUMBEROFBYTES BR, FILENAME name, NUMBEROFBYTES *SPB){       //Draw a String from a text file stored on the micro SD card
  unsigned int counter=0, sp=0;
  
  putcharTX('S');             //String function 
  putcharTX('F');             //text File from SD 
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);  
  putcharTX(BS>>8);
  putcharTX(BS);  
  putcharTX(BR>>8);
  putcharTX(BR);  
  while(1){
	putcharTX(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }

  ((unsigned char*)&sp)[1]=getcharRX();
  ((unsigned char*)&sp)[0]=getcharRX();

  *SPB = sp; 
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::setTextColour(COLOUR colour){        //Set the default text colour for letters and strings
  putcharTX('S');             //String Function 
  putcharTX('C');             //Config  
  putcharTX('T');             //Text
  putcharTX(colour>>8);
  putcharTX(colour); 
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::setTextBackColour(COLOUR colour){    //Set the default text background colour for letters and strings
  putcharTX('S');             //String Function 
  putcharTX('C');             //Config  
  putcharTX('B');             //Background
  putcharTX(colour>>8);
  putcharTX(colour); 
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::setTextSize(FONTSIZE size){           //Set the default text size for letters and strings
  putcharTX('S');             //String Function 
  putcharTX('C');             //Config  
  putcharTX('S');             //Size
  putcharTX(size); 
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::setTextBackFill(TEXTBACKGROUNDCOLOURFILLUNFILL fillState){  //Set the default text FILL or UNFILL background letters and strings
  putcharTX('S');             //String Function 
  putcharTX('C');             //Config  
  putcharTX('F');             //Fill
  putcharTX(fillState); 
  return (SMARTGPUREPLY)getcharRX();
}


/****************************************************************/
//Image Functions
/****************************************************************/
SMARTGPUREPLY SMARTGPU2::drawIcon(AXIS x1, AXIS y1, AXIS x2, AXIS y2, const int icon[]){            //Send and image or icon pixel by pixel to SMARTGPU2, 16bit(2 bytes) each pixel RGB565
  unsigned int i,j,k=0; 
  
  putcharTX('I');             //Image function 
  putcharTX('I');             //Icon image received pixel by pixel
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2);
  //Send icon buffer pixel by pixel
  for(j=0;j<=(y2-y1);j++){
	for(i=0;i<=(x2-x1);i++){
		putcharTX(icon[k]>>8); //16bit per pixel - Upper 8bits part
		putcharTX(icon[k++]);  //16bit per pixel - Lower 8bits part
	}
  }
  
  return (SMARTGPUREPLY)getcharRX();  
}

SMARTGPUREPLY SMARTGPU2::imageBMPSD(AXIS x, AXIS y, FILENAME name){        //Draw an Image stored on the micro SD card on the screen, at X,Y top right corner coordinates
  unsigned char counter=0;
  
  putcharTX('I');             //Image function 
  putcharTX('B');             //BMP from SD card
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  while(1){
	putcharTX(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  return (SMARTGPUREPLY)getcharRX();
}

SMARTGPUREPLY SMARTGPU2::imageJPGSD(AXIS x, AXIS y, JPGSCALEFACTOR scaleFactor, FILENAME name){        //Draw an Image stored on the micro SD card on the screen, at X,Y top right corner coordinates
  unsigned char counter=0;
  
  putcharTX('I');             //Image function 
  putcharTX('J');             //JPG from SD card
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(scaleFactor);
  while(1){
	putcharTX(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }
  return (SMARTGPUREPLY)getcharRX();
}

//Reads a defined x1,x1,x2,y2 box of the SmartGPU display, and returns it pixel by pixel in RGB 888 format, 1 byte per colour, 3 bytes per pixel
SMARTGPUREPLY SMARTGPU2::getImageFromMemory(AXIS x1, AXIS y1, AXIS x2, AXIS y2, char buffer[]){ //Read the internal memory of the SMARTGPU2, This command returns 24bit pixels (3 bytes)
  unsigned int i,j,k=0;
  
  putcharTX('I');             //Image function
  putcharTX('M');             //from SmartGPU internal Display Memory
  putcharTX(x1>>8); 
  putcharTX(x1);
  putcharTX(y1>>8);
  putcharTX(y1);
  putcharTX(x2>>8); 
  putcharTX(x2);
  putcharTX(y2>>8);
  putcharTX(y2); 
  //receive all the pixels
  for(j=0;j<=(y2-y1);j++){
	for(i=0;i<=(x2-x1);i++){
		buffer[k++]=getcharRX(); //Red
		buffer[k++]=getcharRX(); //Green		
		buffer[k++]=getcharRX(); //Blue
	}	
  }
  return (SMARTGPUREPLY)getcharRX();  
}

//takes a screenshot of SmartGPU2 display and stores it in the microSD card with consecutive names Screenshot000.bmp, Screenshot001.bmp, etc
SMARTGPUREPLY SMARTGPU2::screenshot(){ 
  putcharTX('I');             //Image function
  putcharTX('S');             //Screenshot
  return (SMARTGPUREPLY)getcharRX();    
}


/****************************************************************/
//Video Functions
/****************************************************************/
//Allocates a ".vid" video stored on the micro SD card with the given filename name
SMARTGPUREPLY SMARTGPU2::allocateVideoSD(FILENAME name, VIDDATA *videoData){ 
  unsigned int wid=0, hei=0, fra=0, tot=0;
  unsigned char counter=0;
  
  putcharTX('V');             //Video function   
  putcharTX('A');             //Allocate
  while(1){                   //Send Video Name
	putcharTX(name[counter]);
    if(name[counter]==0x00){
      break;
	}	
	counter++;
  }

  ((unsigned char *) &wid)[1]=getcharRX(); //get video width
  ((unsigned char *) &wid)[0]=getcharRX(); 
  ((unsigned char *) &hei)[1]=getcharRX(); //get video height
  ((unsigned char *) &hei)[0]=getcharRX();
  ((unsigned char *) &fra)[1]=getcharRX(); //get video frames per second
  ((unsigned char *) &fra)[0]=getcharRX();
  ((unsigned char *) &tot)[1]=getcharRX(); //get video total frames
  ((unsigned char *) &tot)[0]=getcharRX();
  videoData->width        = wid;
  videoData->height       = hei;
  videoData->framesPerSec = fra;
  videoData->totalFrames  = tot;
  return (SMARTGPUREPLY)getcharRX();
}

//deAllocates a ".vid" video previously allocated, must be called when no more calls to video will be done
SMARTGPUREPLY SMARTGPU2::freeVideoSD(){  
  putcharTX('V');             //Video function   
  putcharTX('D');             //DeAllocate
  return (SMARTGPUREPLY)getcharRX();
}

 //Sets a video start Frame position, this function can be used to FastForward video or Rewing, returns 'F' if invalid position
SMARTGPUREPLY SMARTGPU2::setFrameVideoSD(unsigned int startFrame){
  putcharTX('V');             //Video function   
  putcharTX('F');             //set Video Frame
  putcharTX(startFrame>>8);
  putcharTX(startFrame);
  return (SMARTGPUREPLY)getcharRX();
}

 //Plays a previously allocated ".vid" video stored on mSD card on X,Y top right corner coordinates, starting from current Video Frame and plays framesToPlay
SMARTGPUREPLY SMARTGPU2::playVideoSD(AXIS x, AXIS y, unsigned int framesToPlay){ //frames to play from current video Frame
  putcharTX('V');             //Video function   
  putcharTX('P');             //Play
  putcharTX(x>>8); 
  putcharTX(x);
  putcharTX(y>>8);
  putcharTX(y);
  putcharTX(framesToPlay>>8);
  putcharTX(framesToPlay);
  return (SMARTGPUREPLY)getcharRX();
}
	

/****************************************************************/
//Audio Functions
/****************************************************************/		
SMARTGPUREPLY SMARTGPU2::initDACAudio(STATE state){
  putcharTX('A');             //Audio Function
  putcharTX('I');             //Init - Deinit DACs
  putcharTX(state);           //Enable/Disable  
  return (SMARTGPUREPLY)getcharRX();      
}

SMARTGPUREPLY SMARTGPU2::audioBoost(STATE state){
  putcharTX('A');             //Audio Function
  putcharTX('B');             //Boost
  putcharTX(state);           //Enable/Disable
  return (SMARTGPUREPLY)getcharRX();    
}

SMARTGPUREPLY SMARTGPU2::getWAVPlayState(STATE* state){ //returns ENABLE or DISABLE if any file is playing
  putcharTX('A');             //Audio Function
  putcharTX('G');             //Get playing File status  
  *state = (STATE)getcharRX();        //Get state
  return (SMARTGPUREPLY)getcharRX();  
}

SMARTGPUREPLY SMARTGPU2::playWAVFile(FILENAME name, unsigned int* seconds){ //returns in "seconds" variable the song duration in seconds
  unsigned int secs=0;
  unsigned char counter=0;
  
  putcharTX('A');             //Audio Function
  putcharTX('P');             //Play WAV file
  while(1){                      //Send file name
  	putcharTX(name[counter]);
  	if(name[counter]==0x00){
  	break;
  	}	
  	counter++;
  }

  ((unsigned char *) &secs)[1]=getcharRX();  
  ((unsigned char *) &secs)[0]=getcharRX();     
  *seconds = secs;
  return (SMARTGPUREPLY)getcharRX();    
}

SMARTGPUREPLY SMARTGPU2::pauseWAVFile(){ //pauses a playing file, returns 'F' if no file is playing
  putcharTX('A');             //Audio Function
  putcharTX('W');             //Pause file
  return (SMARTGPUREPLY)getcharRX();   
}

SMARTGPUREPLY SMARTGPU2::stopWAVFile(){
  putcharTX('A');             //Audio Function
  putcharTX('S');             //Stop playing file
  return (SMARTGPUREPLY)getcharRX();   
}

SMARTGPUREPLY SMARTGPU2::advanceWAVFile(unsigned int seconds){ //advance to the file to the given seconds parameter  
  putcharTX('A');             //Audio Function
  putcharTX('A');             //Advance file  
  putcharTX(seconds>>8);
  putcharTX(seconds);  
  return (SMARTGPUREPLY)getcharRX();          //returns 'F' if no file is playing or if no seconds position exists, in this case file will stop playing
}

SMARTGPUREPLY SMARTGPU2::setVolumeWAV(unsigned char volume){
  putcharTX('A');             //Audio Function
  putcharTX('V');             //Volume
  putcharTX(volume);
  return (SMARTGPUREPLY)getcharRX();  
}


/****************************************************************/
//Real Time Clock Functions
/****************************************************************/			
SMARTGPUREPLY SMARTGPU2::setupRTC(STATE *state){
  putcharTX('R');              //RTC function - Real Time Clock
  putcharTX('S');              //Setup RTC
  *state = (STATE)getcharRX();  //Get state
  return (SMARTGPUREPLY)getcharRX();   
}
	
SMARTGPUREPLY SMARTGPU2::getRTCTimeDate(TIME *timeDate){
  unsigned int counter=0;
  
  putcharTX('R');              //RTC function - Real Time Clock
  putcharTX('P');              //Parameters
  putcharTX('G');              //Get
  timeDate->hour = getcharRX();	//hour
  timeDate->minute = getcharRX();	//min
  timeDate->second = getcharRX(); //sec
  timeDate->day = getcharRX();	//day
  timeDate->month = getcharRX();  //month
  ((unsigned char*)&counter)[1] = getcharRX();		 //year upper
  ((unsigned char*)&counter)[0] = getcharRX();		 //year lower
  timeDate->year = counter;		    //year 
  return (SMARTGPUREPLY)getcharRX();
}
	
SMARTGPUREPLY SMARTGPU2::setRTCTimeDate(TIME *timeDate){
  putcharTX('R');              //RTC function - Real Time Clock
  putcharTX('P');              //Parameters
  putcharTX('S');              //Set
  putcharTX(timeDate->hour);   //hour
  putcharTX(timeDate->minute); //min
  putcharTX(timeDate->second); //sec
  putcharTX(timeDate->day);	  //day
  putcharTX(timeDate->month);  //month
  putcharTX(timeDate->year>>8);//year upper
  putcharTX(timeDate->year);	  //year lower	
  return (SMARTGPUREPLY)getcharRX();
}
	
	
/****************************************************************/
//Objects Functions
/****************************************************************/			
SMARTGPUREPLY SMARTGPU2::objButton(AXIS x1, AXIS y1, AXIS x2, AXIS y2, ACTIVE activeState, char text[]){
  unsigned int counter=0;
  
  putcharTX('O');              //Object function
  putcharTX('B');              //Button
  putcharTX(x1>>8);
  putcharTX(x1);  
  putcharTX(y1>>8);
  putcharTX(y1);  
  putcharTX(x2>>8);
  putcharTX(x2);  
  putcharTX(y2>>8);
  putcharTX(y2);
  putcharTX(activeState);
  while(1){                      //Send button text
	putcharTX(text[counter]);
    if(text[counter]==0x00){
      break;
	}	
	counter++;
  }    
  return (SMARTGPUREPLY)getcharRX();  
}

SMARTGPUREPLY SMARTGPU2::objSwitch(AXIS x, AXIS y, unsigned int switchSize, ACTIVE activeState){
  putcharTX('O');              //Object function
  putcharTX('T');              //Switch
  putcharTX(x>>8);
  putcharTX(x);  
  putcharTX(y>>8);
  putcharTX(y);  
  putcharTX(switchSize>>8);
  putcharTX(switchSize);  
  putcharTX(activeState);
  return (SMARTGPUREPLY)getcharRX();
}
	
SMARTGPUREPLY SMARTGPU2::objCheckbox(AXIS x, AXIS y, unsigned int checkboxSize, ACTIVE activeState){
  putcharTX('O');              //Object function
  putcharTX('C');              //Checkbox
  putcharTX(x>>8);
  putcharTX(x);  
  putcharTX(y>>8);
  putcharTX(y);  
  putcharTX(checkboxSize>>8);
  putcharTX(checkboxSize);  
  putcharTX(activeState);
  return (SMARTGPUREPLY)getcharRX();    
}

SMARTGPUREPLY SMARTGPU2::objProgressBar(AXIS x1, AXIS y1, AXIS x2, AXIS y2, unsigned char progress){
  putcharTX('O');              //Object function
  putcharTX('P');              //Progress Bar
  putcharTX(x1>>8);
  putcharTX(x1);  
  putcharTX(y1>>8);
  putcharTX(y1);  
  putcharTX(x2>>8);
  putcharTX(x2);  
  putcharTX(y2>>8);
  putcharTX(y2);
  putcharTX(progress);
  return (SMARTGPUREPLY)getcharRX();    
}

SMARTGPUREPLY SMARTGPU2::objSlider(AXIS x1, AXIS y1, AXIS x2, AXIS y2, unsigned char position, unsigned char divisions, ORIENTATIONPARAMETER sliderOrientation){
  putcharTX('O');              //Object function
  putcharTX('L');              //Slider
  putcharTX(x1>>8);
  putcharTX(x1);  
  putcharTX(y1>>8);
  putcharTX(y1);  
  putcharTX(x2>>8);
  putcharTX(x2);  
  putcharTX(y2>>8);
  putcharTX(y2);
  putcharTX(position);
  putcharTX(divisions);
  putcharTX(sliderOrientation);
  return (SMARTGPUREPLY)getcharRX();    
}

SMARTGPUREPLY SMARTGPU2::objScrollBar(AXIS x1, AXIS y1, AXIS x2, AXIS y2, unsigned char position, unsigned char divisions, ORIENTATIONPARAMETER scrollBarOrientation, ACTIVE activeState){
  putcharTX('O');              //Object function
  putcharTX('S');              //Scroll bar
  putcharTX(x1>>8);
  putcharTX(x1);  
  putcharTX(y1>>8);
  putcharTX(y1);  
  putcharTX(x2>>8);
  putcharTX(x2);  
  putcharTX(y2>>8);
  putcharTX(y2);
  putcharTX(position);
  putcharTX(divisions);
  putcharTX(scrollBarOrientation);
  putcharTX(activeState);
  return (SMARTGPUREPLY)getcharRX();    
}

SMARTGPUREPLY SMARTGPU2::objWindow(AXIS x1, AXIS y1, AXIS x2, AXIS y2, FONTSIZE textSize, WINDOWTYPE winType, char text[]){
  unsigned int counter=0;
  
  putcharTX('O');              //Object function
  putcharTX('W');              //Window
  putcharTX(x1>>8);
  putcharTX(x1);  
  putcharTX(y1>>8);
  putcharTX(y1);  
  putcharTX(x2>>8);
  putcharTX(x2);  
  putcharTX(y2>>8);
  putcharTX(y2);
  putcharTX(textSize);  
  putcharTX(winType);
  while(1){                      //Send button text
	putcharTX(text[counter]);
    if(text[counter]==0x00){
      break;
	}	
	counter++;
  }
  return (SMARTGPUREPLY)getcharRX();    
}


/****************************************************************/
//EEPROM-FLASH Functions - Refer to "smartGPU2 Command Set" to learn about READ-WRITE procedure.
/****************************************************************/			
SMARTGPUREPLY SMARTGPU2::initClearEEPROMBuff(){
  putcharTX('E');              //EEPROM function
  putcharTX('I');              //Init/Clear EEPROM Buffer
  return (SMARTGPUREPLY)getcharRX(); 
}

SMARTGPUREPLY SMARTGPU2::readEEPROMBuff(char buffer[], ADDRESS EEPROMbufferAddress, NUMBEROFBYTES bytesToRead, NUMBEROFBYTES *SRB){
  unsigned int x=0, sr=0;
  
  putcharTX('E');              //EEPROM function
  putcharTX('R');              //Read N bytes from EEPROM buffer to received buffer[]
  putcharTX(EEPROMbufferAddress>>8); //address to start reading from EEPROM buffer
  putcharTX(EEPROMbufferAddress);  
  putcharTX(bytesToRead>>8);
  putcharTX(bytesToRead); 
  
  for(x=0; x<bytesToRead; x++){
	buffer[x]=getcharRX();
  }

  ((unsigned char*)&sr)[1]=getcharRX();
  ((unsigned char*)&sr)[0]=getcharRX();

  *SRB = sr;                   //store succesfully read bytes  
   return (SMARTGPUREPLY)getcharRX();  
}

SMARTGPUREPLY SMARTGPU2::writeEEPROMBuff(char buffer[], ADDRESS EEPROMbufferAddress, NUMBEROFBYTES bytesToWrite, NUMBEROFBYTES *SWB){
  unsigned int x=0, sw=0;
  
  putcharTX('E');              //EEPROM function
  putcharTX('W');              //Write N bytes to EEPROM buffer from received buffer[]
  putcharTX(EEPROMbufferAddress>>8); //address to start writting to EEPROM buffer
  putcharTX(EEPROMbufferAddress);  
  putcharTX(bytesToWrite>>8);
  putcharTX(bytesToWrite);    
  for(x=0; x<bytesToWrite; x++){
	putcharTX(buffer[x]);
  }  

  ((unsigned char*)&sw)[1]=getcharRX();
  ((unsigned char*)&sw)[0]=getcharRX();

  *SWB = sw;                   //store succesfully written bytes
   return (SMARTGPUREPLY)getcharRX();    
}

SMARTGPUREPLY SMARTGPU2::saveBuffToEEPROMPage(EEPROMPAGE page){
  putcharTX('E');              //EEPROM function
  putcharTX('S');              //Save EEPROM buffer contents to received EEPROM page#
  putcharTX(page);
  return (SMARTGPUREPLY)getcharRX(); 
}

SMARTGPUREPLY SMARTGPU2::fillBuffFromEEPROMPage(EEPROMPAGE page){
  putcharTX('E');              //EEPROM function
  putcharTX('F');              //Fill(copy) EEPROM buffer with received EEPROM page# contents
  putcharTX(page);
  return (SMARTGPUREPLY)getcharRX(); 
}

SMARTGPUREPLY SMARTGPU2::compBuffToEEPROMPage(EEPROMPAGE page, unsigned char *result){
  putcharTX('E');              //EEPROM function
  putcharTX('C');              //Compare EEPROM buffer contents with received EEPROM page#
  putcharTX(page);
  *result = getcharRX();
  return (SMARTGPUREPLY)getcharRX(); 
}	

SMARTGPUREPLY SMARTGPU2::eraseEEPROMPage(EEPROMPAGE page){
  putcharTX('E');              //EEPROM function
  putcharTX('E');              //Erase received EEPROM page#
  putcharTX(page);
  return (SMARTGPUREPLY)getcharRX(); 
}	

	
/****************************************************************/
//Touch Functions
//Those next Touch Functions return valid or invalid touch coordinates status(TOUCHREPLY) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/
TOUCHREPLY SMARTGPU2::touchScreen(POINT *point){ //Ask for a touch on the screen, if return==VALID, touch coords are valid and stored on xAxis and yAxis 
  unsigned int x=0,y=0;
  putcharTX('T');             //Touch Function
  putcharTX('S');             //Screen touch 
  ((unsigned char *) &x)[1]=getcharRX();
  ((unsigned char *) &x)[0]=getcharRX();
  ((unsigned char *) &y)[1]=getcharRX();
  ((unsigned char *) &y)[0]=getcharRX();
  if(getcharRX()=='O'){  //if touch coordinates are valid, assign values
    point->x=x;
    point->y=y;
	return (TOUCHREPLY)VALID;
  }
  return (TOUCHREPLY)INVALID;
}

//function only for the SmartGPU2 LCD320x240 2.4", as it is the only board with touch icons
TOUCHREPLY SMARTGPU2::touchIcon(ICON *icon){ //Ask for a touch on the icons of the screen, if return==VALID, icon first letter is stored on icon
  putcharTX('T');             //Touch Function
  putcharTX('I');             //Icons touch
  *icon = (ICON)getcharRX();
  if(getcharRX()=='O'){  //if touch coordinates are valid
	return (TOUCHREPLY)VALID;
  }
  return (TOUCHREPLY)INVALID;
}

/****************************************************************/
//SD FAT management Functions
//Those next SDF - SD Functions return file execution status(FILERESULT) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/
FILERESULT SMARTGPU2::SDFgetList(unsigned int *numOfDirs, unsigned int *numOfFiles){ //get number of dirs and files
  FILERESULT res;
  unsigned int dirs=0, files=0;
    
  putcharTX('F');           //File function - memory card file management
  putcharTX('L');           //List/count dirs and files
  
  ((unsigned char *) &dirs)[1]= getcharRX();       //Get Upper part
  ((unsigned char *) &dirs)[0]= getcharRX();       //Get Lower part
  ((unsigned char *) &files)[1]= getcharRX();      //Get Upper part
  ((unsigned char *) &files)[0]= getcharRX();      //Get Lower part  
  *numOfDirs=dirs;  
  *numOfFiles=files;
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFgetDirName(ITEMNUMBER itemNumber, FILENAME name){ //searches for the "itemNumber" on the SD current folder and updates the buffer with the Dir name ended with NULL character
  FILERESULT  res;
  unsigned int  i=0;

  putcharTX('F');           //File function - memory card file management
  putcharTX('G');           //Get name of given item file number
  putcharTX('D');           //Directory
  putcharTX(itemNumber>>8); //Send Upper part of itemNumber
  putcharTX(itemNumber);    //Send Lower part of itemNumber
  
  while(1){
	name[i]=getcharRX(); 
	if(name[i]==0x00){         //if we find NULL character, means end of name
		break;   
	}
	i++;
  }
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
 }

FILERESULT SMARTGPU2::SDFgetFileName(ITEMNUMBER itemNumber, FILENAME name){ //searches for the "itemNumber" on the SD current folder and updates the buffer with the File name ended with NULL character
  FILERESULT  res;
  unsigned int  i=0;

  putcharTX('F');           //File function - memory card file management
  putcharTX('G');           //Get name of given item file number
  putcharTX('F');           //File  
  putcharTX(itemNumber>>8); //Send Upper part of itemNumber
  putcharTX(itemNumber);    //Send Lower part of itemNumber

  while(1){
	name[i]=getcharRX(); 
	if(name[i]==0x00){         //if we find NULL character, means end of name
		break;   
	}
	i++;
  }
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
 }
 
FILERESULT SMARTGPU2::SDFgetDirPath(char path[]){ //obtains current dir path and stores on path[] buffer
  FILERESULT  res;
  unsigned int  i=0;
  putcharTX('F');           //File function - memory card file management
  putcharTX('H');           //Get current Dir Path
  
  while(1){
	path[i]=getcharRX(); 
	if(path[i]==0x00){         //if we find NULL character, means end of path
		break;   
	}
	i++;
  }
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFnewDir(FILENAME name){ //create a new Directory, fails if already exist
  FILERESULT res;
  unsigned int counter=0;  
 
  putcharTX('F');           //File function - memory card file management
  putcharTX('N');           //New
  putcharTX('D');           //Directory/Folder  
  while(1){
  	putcharTX(name[counter]);
  	if(name[counter]==0x00){
  	break;
  	}	
  	counter++;
  }

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFnewFile(FILENAME name){ //create a new File, fails if already exist
  FILERESULT res;
  unsigned int counter=0;  
 
  putcharTX('F');           //File function - memory card file management
  putcharTX('N');           //New
  putcharTX('F');           //File 
  while(1){
  	putcharTX(name[counter]);
  	if(name[counter]==0x00){
  	break;
  	}	
  	counter++;
  }

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFopenDir(FILENAME name){ //opens an existing Dir
  FILERESULT res;
  unsigned int counter=0;  
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('D');           //Open Dir
  while(1){
	putcharTX(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFopenFile(FILENAME name, OPENMODE mode, WORKSPACEBLOCK objectWorkspaceNo){ //opens an existing file in READONLY, WRITEONLY or READWRITE mode on the received object # workspace
  FILERESULT res;
  unsigned int counter=0;  
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('O');           //Open file
  putcharTX(objectWorkspaceNo); //object workspace number to allocate open file 0-4
  putcharTX(mode);          //Mode - READONLY,WRITEONLY,READWRITE
  while(1){
	putcharTX(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                    //Return SD file execution status  
}

FILERESULT SMARTGPU2::SDFcloseFile(WORKSPACEBLOCK objectWorkspaceNo){ //close and save file object # workspace
  FILERESULT res;

  putcharTX('F');           //File function - memory card file management
  putcharTX('C');           //Close File
  putcharTX(objectWorkspaceNo); //object workspace number to close 0-4  

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFsaveFile(WORKSPACEBLOCK objectWorkspaceNo){ //sync/save file object # workspace
  FILERESULT res;
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('S');           //Save/Sync file - Save changes on file
  putcharTX(objectWorkspaceNo); //object workspace number to save changes 0-4  

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFsetFilePointer(POINTERPOSITION pointerPosition, WORKSPACEBLOCK objectWorkspaceNo){ // set/move file pointer of file object # workspace
  FILERESULT res;
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('P');           //Pointer position
  putcharTX(objectWorkspaceNo); //object workspace number to move pointer 0-4  
  putcharTX('S');           //Set  
  putcharTX(pointerPosition>>24);
  putcharTX(pointerPosition>>16);
  putcharTX(pointerPosition>>8);
  putcharTX(pointerPosition);

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}	

FILERESULT SMARTGPU2::SDFgetFilePointer(POINTERPOSITION *pointerPosition, WORKSPACEBLOCK objectWorkspaceNo){ // get file pointer of file object # workspace
  FILERESULT res;
  unsigned long pos = 0;
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('P');           //Pointer position
  putcharTX(objectWorkspaceNo); //object workspace number to get pointer 0-4  
  putcharTX('G');           //Get
  
  ((unsigned char *) &pos)[3]=getcharRX();
  ((unsigned char *) &pos)[2]=getcharRX();
  ((unsigned char *) &pos)[1]=getcharRX();  
  ((unsigned char *) &pos)[0]=getcharRX();
  *pointerPosition =pos;
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}	

FILERESULT SMARTGPU2::SDFreadFile(char buffer[], NUMBEROFBYTES BTR, NUMBEROFBYTES *SRB, WORKSPACEBLOCK objectWorkspaceNo){ //Bytes to Read, Succesfully Read Bytes, file object # to read bytes from
  FILERESULT res;
  unsigned int x=0, sr=0;

  putcharTX('F');           //File function - memory card file management
  putcharTX('R');           //Read file
  putcharTX(objectWorkspaceNo); //object workspace number to read 0-4    
  putcharTX(BTR>>8);
  putcharTX(BTR);  

  for(x=0;x<BTR;x++){
	buffer[x]=getcharRX();
  }

  ((unsigned char*)&sr)[1]=getcharRX();
  ((unsigned char*)&sr)[0]=getcharRX();

  *SRB = sr;                   //store succesfully read bytes
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}	

FILERESULT SMARTGPU2::SDFwriteFile(char buffer[], NUMBEROFBYTES BTW, NUMBEROFBYTES *SWB,  WORKSPACEBLOCK objectWorkspaceNo){ //Bytes to Write, Succesfully Written Bytes, file object # to write bytes
  FILERESULT res;
  unsigned int x=0, sw=0;
 
  putcharTX('F');           //File function - memory card file management
  putcharTX('W');           //Write file
  putcharTX(objectWorkspaceNo); //object workspace number to write bytes 0-4    
  putcharTX(BTW>>8);
  putcharTX(BTW);    
  for(x=0;x<BTW;x++){
	putcharTX(buffer[x]);
  }

  ((unsigned char*)&sw)[1]=getcharRX();
  ((unsigned char*)&sw)[0]=getcharRX();

  *SWB = sw;                   //store succesfully written bytes   
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFtestFileError(WORKSPACEBLOCK objectWorkspaceNo){  //test for an error on file # workspace
  FILERESULT res;

  putcharTX('F');           //File function - memory card file management
  putcharTX('Q');           //Test 
  putcharTX(objectWorkspaceNo); //object workspace number to write bytes 0-4    
  putcharTX('R');           //Test Error  

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFtestFileEnd(WORKSPACEBLOCK objectWorkspaceNo){  //test for an error on file # workspace
  FILERESULT res;
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('Q');           //Test 
  putcharTX(objectWorkspaceNo); //object workspace number to write bytes 0-4    
  putcharTX('E');           //Test End of File

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SMARTGPU2::SDFtruncateFile(WORKSPACEBLOCK objectWorkspaceNo){  //truncates the file size to the current file read/write pointer of the file # workspace
  FILERESULT res;
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('V');           //Truncate
  putcharTX(objectWorkspaceNo); //object workspace number 0-4 to truncate on current pointerPosition

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SMARTGPU2::SDFeraseDirFile(FILENAME name){ //Erases an existing Dir or File
  FILERESULT res;
  unsigned int counter=0;  
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('E');           //Erase Dir File
  putcharTX('O');           //Unlock Erase Protection
  while(1){
	putcharTX(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFsetFileTimeDate(TIME *timeDate, FILENAME name){ //Set Time and Date to an existing File
  FILERESULT res;
  unsigned int counter=0;  
  
  putcharTX('F');              //File function - memory card file management
  putcharTX('T');              //Time/Date
  putcharTX('S');              //Set
  putcharTX(timeDate->hour);   //hour
  putcharTX(timeDate->minute); //min
  putcharTX(timeDate->second); //sec
  putcharTX(timeDate->day);	  //day
  putcharTX(timeDate->month);  //month
  putcharTX(timeDate->year>>8);//year upper
  putcharTX(timeDate->year);	  //year lower	
  while(1){
	putcharTX(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SMARTGPU2::SDFgetFileTimeDate(TIME *timeDate, FILENAME name){ //Get Time and Date to an existing File
  FILERESULT res;
  unsigned int counter=0;  
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('T');           //Time/Date
  putcharTX('G');           //Get
  while(1){
	putcharTX(name[counter]);
	if(name[counter]==0x00){
	  break;
	}	
	counter++;
  }	

  timeDate->hour = getcharRX();   //hour
  timeDate->minute = getcharRX(); //min
  timeDate->second = getcharRX(); //sec
  timeDate->day = getcharRX();    //day
  timeDate->month = getcharRX();  //month
  ((unsigned char*)&counter)[1] = getcharRX();		 //year upper
  ((unsigned char*)&counter)[0] = getcharRX();		 //year lower
  timeDate->year = counter;		    //year
  res = (FILERESULT)getcharRX();  //Get SD file execution status
  getcharRX();                    //Discard 'O' or 'F'
  return res;                     //Return SD file execution status
}

FILERESULT SMARTGPU2::SDFgetFileSize(FILENAME name, unsigned long *fileSize){ //Get Size of an existing File
  FILERESULT res;
  unsigned int counter=0;  
  unsigned long size=0;
  
	putcharTX('F');           //File function - memory card file management
	putcharTX('I');           //Info
	putcharTX('S');           //Size
	while(1){
		putcharTX(name[counter]);
		if(name[counter]==0x00){
		break;
		}	
		counter++;
	}	

  ((unsigned char *) &size)[3]=getcharRX();
  ((unsigned char *) &size)[2]=getcharRX();
  ((unsigned char *) &size)[1]=getcharRX();  
  ((unsigned char *) &size)[0]=getcharRX(); 
  *fileSize=size;
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SMARTGPU2::SDFrenameMoveDirFile(FILENAME oldName, FILENAME newName){ //renames or moves an existing Dir or File
  FILERESULT res;
  unsigned int counter=0;  
  
	putcharTX('F');           //File function - memory card file management
	putcharTX('M');           //Rename / Move
	while(1){
		putcharTX(oldName[counter]);
		if(oldName[counter]==0x00){
		break;
		}	
		counter++;
	}
	counter=0;
	while(1){
		putcharTX(newName[counter]);
		if(newName[counter]==0x00){
		break;
		}	
		counter++;
  }	

  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}

FILERESULT SMARTGPU2::SDFgetFreeTotalSpace(unsigned long *freeSpace,unsigned long *totalSpace){ //Get free and total space in bytes of the microSD card
  FILERESULT res;
  unsigned long fSpace=0, tSpace=0;
  
  putcharTX('F');           //File function - memory card file management
  putcharTX('F');           //Free/Total space

  ((unsigned char *) &fSpace)[3]=getcharRX();
  ((unsigned char *) &fSpace)[2]=getcharRX();
  ((unsigned char *) &fSpace)[1]=getcharRX();  
  ((unsigned char *) &fSpace)[0]=getcharRX(); 
  ((unsigned char *) &tSpace)[3]=getcharRX();
  ((unsigned char *) &tSpace)[2]=getcharRX();
  ((unsigned char *) &tSpace)[1]=getcharRX();  
  ((unsigned char *) &tSpace)[0]=getcharRX(); 
  *freeSpace=fSpace;
  *totalSpace=tSpace;  
  res = (FILERESULT)getcharRX(); //Get SD file execution status
  getcharRX();                   //Discard 'O' or 'F'
  return res;                      //Return SD file execution status 
}
