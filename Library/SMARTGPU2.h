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
 ARDUINO SMARTGPU2 LIBRARY VERSION V7.0
 - Library supports any SmartGPU2 LCDXXXxXXX connected via SmartSHIELD board(for smartGPU2 4.3" and 7.0" smartSHIELD is always required)
 - Library supports the SmartGPU2 LCD320x240 2.4" mounted directly as shield by uncommenting the appropriate line below
 - Library supports the ARDUINO DUE board via SmartSHIELD by adding external jumpers to serial2 or serial3 port
 IMPORTANT : This library was created for the Arduino 1.8.9 Software IDE or newer
********************************************************/

#ifndef SMARTGPU2_h
#define SMARTGPU2_h

#include <inttypes.h>

/*******************USER MODIFABLE**********************/
//If using smartGPU2 2.4" LCD320x240 mounted directly as arduino shield, please uncomment the next:
//#define SMARTGPU2_24_DIRECT_SHIELD

//-SmartSHIELD uses default Arduino pin p4 for Reset, if another pin is soldered in the SmartSHIELD(pin 7, 8 or 13), please modify here:
//-SmartGPU2-Arduino RESET PIN definition 
#define SG_RESET 4       //Define for the RESET pin connected on the SmartSHIELD board(pin 7, 8 or 13) 

//-Arduino serial port configuration using smartSHIELD, modify to Serial2, Serial3 if needed
#define SG_SERIALPORT     (Serial)

//If DUE (SAM3X8E) is being used and SmartGPU2 is mounted as shield...
#if defined(__SAM3X8E__) //If arduino DUE is being used...
#ifdef  SMARTGPU2_24_DIRECT_SHIELD
#error "smartGPU2 LCD320x240 2.4 board can't be used directly mounted as shield on Arduino DUE, connect via SmartSHIELD or jumpers"
#endif
//Arduino DUE can't use Serial or Serial1 for communication(only for debug via terminal), this because a bad design of arduino engineers, so we must use redefine to Serial2 or Serial3
#define SG_SERIALPORT     (Serial2)  //re-define serial port Serial2 or Serial3 for arduino DUE
#endif
/****************END OF USER MODIFABLE******************/


/**************DON'T MODIFY UP FROM HERE****************/
//SmartGPU2-Arduino security RESET PIN re-definition and AREF pin re-configuration if using SmartGPU2 LCD320x240 2.4" directly as shield
#ifdef  SMARTGPU2_24_DIRECT_SHIELD  //define valid only for the SmartGPU2 LCD320x240 2.4" mounted directly as Arduino Shield
#define SG_RESET           13       //re-define SG_RESET pin as 13 as this is the pin that is connected to Reset 
#define SG_SERIALPORT     (Serial)  //re-define serial port
#endif

//General definitions
#define SG_OFF 0
#define SG_ON  1
#define SG_GND 0
#define SG_VCC 1
#define SG_SCROLLBUTTONSIZE 25

//basic colours definitions
#define SG_BLACK   0x0000
#define SG_WHITE   0xFFFF
#define SG_RED     0xF800
#define SG_GREEN   0x07E0
#define SG_BLUE    0x001F
#define SG_YELLOW  0xFFE0
#define SG_CYAN    0x07FF
#define SG_MAGENTA 0xF81F

//File access definitions
#define SG_BEGINNING    0
#define SG_ALLCONTENTS  0

//General typedefs
typedef unsigned int  SG_AXIS;
typedef unsigned int  SG_COLOUR;
typedef unsigned int  SG_RADIUS;
typedef unsigned int  SG_NUMBEROFBYTES;
typedef unsigned int  SG_ITEMNUMBER;
typedef unsigned int  SG_ADDRESS;
typedef unsigned long SG_POINTERPOSITION;
typedef char SG_FILENAME[];

/*******ENUMS*********/
typedef enum {
	SG_DISABLE, //0
	SG_ENABLE   //1
} SG_STATE; //to set Enable/Disable States

typedef enum {
	SG_DESELECTED, //0
	SG_SELECTED    //1
} SG_ACTIVE; //to set Selected/DeSelected Active objects

typedef enum {
	SG_DESELECTEDTRANS, //0 set an unselected top window with transparent center
	SG_SELECTEDTRANS,   //1 set a selected window with transparent center
	SG_SELECTEDGRAY,    //2 set a selected window with gray center
	SG_SELECTEDWHITE    //3 set a selected window with white center
} SG_WINDOWTYPE; //to set type of window to draw

typedef enum {
	SG_OK   = 'O',  //Command successfully executed
	SG_FAIL = 'F'   //Command Fail
} SG_REPLY;       //to get SmartGPU2 command responses

//Graphics functions definitions
typedef enum {
	SG_UNFILL, //0
	SG_FILL    //1
} SG_FILLGEOM;  //to set fill or unfill colour geometry

typedef enum {
	SG_HORIZONTAL, //0
	SG_VERTICAL    //1
} SG_ORIENTATIONPARAMETER;//to set gradient colour fade orientation and objects: scrollBar and Slider orientations

typedef enum {
	SG_LANDSCAPE_LEFT,     //0 left
	SG_PORTRAIT_LOW,      //1 low
	SG_LANDSCAPE_RIGHT,     //2 right
	SG_PORTRAIT_TOP       //3 top
} SG_LCDORIENTATION;  //to set LCD orientations

typedef enum {
	SG_QUADRANT1 = 1, //1
	SG_QUADRANT2,     //2
	SG_QUADRANT3,     //3
	SG_QUADRANT4      //4
} SG_ARCQUADRANT;     //to set desired arc drawing quadrant

//fonts definitions
typedef enum {
	SG_FONT0 = 0,
	SG_FONT1,
	SG_FONT2,
	SG_FONT3,
	SG_FONT4,
	SG_FONT5,
	SG_FONT6,
	SG_FONT7,
	SG_FONT8,
	SG_FONT9,
	SG_FONT10,
	SG_FONT11,
	SG_FONT12,
	SG_FONT13
} SG_FONTSIZE; //to set text font sizes

typedef enum {
	SG_TRANS = 0,
	SG_FILLED
} SG_TEXTBACKGROUND; //to set text background colour to transparent or filled

//Touch definitions
typedef enum {
	SG_INVALID,  //returned touch point is invalid
	SG_VALID     //returned touch point is valid
} SG_TOUCHREPLY; //to get SmartGPU2 touch responses

typedef enum {
	SG_HOUSE    = 'H',
	SG_MESSAGE  = 'M',
	SG_BOOK     = 'B',
	SG_PHONE    = 'P',
	SG_SONG     = 'S',
	SG_NONE     = 'N'
} SG_ICON;  //to get the type of touched icon

//File access definitions
typedef enum {
	SG_READONLY = 1, //1
	SG_WRITEONLY,    //2
	SG_READWRITE     //3
} SG_OPENMODE;       //to set the file access open mode

//SMARTGPU2 Command Execution responses definitions
typedef enum {
	SG_F_OK = 0,				/* (0) Succeeded */
	SG_F_DISK_ERR,				/* (1) A hard error occurred in the low level disk I/O layer */
	SG_F_INT_ERR,				/* (2) Assertion failed */
	SG_F_NOT_READY,			/* (3) The physical drive cannot work */
	SG_F_NO_FILE,				/* (4) Could not find the file */
	SG_F_NO_PATH,				/* (5) Could not find the path */
	SG_F_INVALID_NAME,			/* (6) The path name format is invalid */
	SG_F_DENIED,				/* (7) Access denied due to prohibited access or directory full */
	SG_F_EXIST,				/* (8) Access denied due to prohibited access */
	SG_F_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
	SG_F_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
	SG_F_INVALID_DRIVE,		/* (11) The logical drive number is invalid */
	SG_F_NOT_ENABLED,			/* (12) The volume has no work area */
	SG_F_NO_FILESYSTEM,		/* (13) There is no valid FAT volume */
	SG_F_MKFS_ABORTED,			/* (14) The f_mkfs() aborted due to any parameter error */
	SG_F_TIMEOUT,				/* (15) Could not get a grant to access the volume within defined period */
	SG_F_LOCKED,				/* (16) The operation is rejected according to the file sharing policy */
	SG_F_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
	SG_F_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > _FS_SHARE */
	SG_F_INVALID_PARAMETER		/* (19) Given parameter is invalid */
} SG_FILERESULT;               //Gets all FAT functions related responses

//SMARTGPU2 WorkSpaces definitions
typedef enum {
	SG_WORKSPACE0 = 0, 
	SG_WORKSPACE1,
	SG_WORKSPACE2,
	SG_WORKSPACE3 
} SG_WORKSPACEBLOCK;  //to set the working workspace

//SMARTGPU2 EEPROM pages definitions, each page is 2048bytes (2Kb) in size
typedef enum {
	SG_PAGE0 = 0, 
	SG_PAGE1,
	SG_PAGE2,
	SG_PAGE3,
	SG_PAGE4,
	SG_PAGE5,
	SG_PAGE6,
	SG_PAGE7
} SG_EEPROMPAGE;  //to set the EEPROM page

//JPG images scale factor definitions
typedef enum {
	SG_SCALE1_1 = 0,  // 1 to 1
	SG_SCALE1_2,      // 1 to 2
	SG_SCALE1_4,      // 1 to 4
	SG_SCALE1_8       // 1 to 8
} SG_JPGSCALEFACTOR; //to set the desired JPG image decompression scale factor

//Recommended(but not limited to) Arduino-SmartGPU Baud rate definitions
typedef enum{
	SG_BAUD0 = 9600,
	SG_BAUD1 = 19200,
	SG_BAUD2 = 57600,
	SG_BAUD3 = 115200,
	SG_BAUD4 = 256000,
	SG_BAUD5 = 500000,
	SG_BAUD6 = 1000000,
	SG_BAUD7 = 2000000
} SG_BAUDRATE;

/*******STRUCTS*********/
//Point
typedef struct {
	SG_AXIS x; //X axis
	SG_AXIS y; //Y axis
} SG_POINT;    //to create a point with point.x and point.y variables

//Video 
typedef struct {
	unsigned int width;  //X width
	unsigned int height; //Y height
	unsigned int framesPerSec; //video frames per second
	unsigned int totalFrames;  //video total frames in the file
} SG_VIDDATA;    //to create a Video Data struct containing, size X, size Y, frames per second and totalframes info

//Files Time and Date
typedef struct {
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char day;
	unsigned char month;
	unsigned int  year;	
} SG_TIME;    //to create a Time-Date info struct

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
class SMARTGPU2{
	
public:
/****************************************************************/
//Arduino Functions
/****************************************************************/
  SMARTGPU2();
	
	SG_REPLY init();

	SG_REPLY reset();
	
	SG_REPLY start();  

/****************************************************************/
//Master Functions
/****************************************************************/	
	SG_REPLY erase();

	SG_REPLY sleep(SG_STATE);
	
	SG_REPLY orientation(SG_LCDORIENTATION);
	
	SG_REPLY bright(unsigned char);
	
	SG_REPLY baudChange(unsigned long);
	
	SG_REPLY setEraseBackColour(SG_COLOUR);
	
	SG_REPLY getWidth(SG_AXIS*);

  SG_REPLY getHeight(SG_AXIS*);

/****************************************************************/
//Geometric Functions
/****************************************************************/		
	SG_REPLY putPixel(SG_AXIS, SG_AXIS, SG_COLOUR);
	
	SG_REPLY drawLine(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_COLOUR);
	
	SG_REPLY drawRectangle(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_COLOUR, SG_FILLGEOM);

	SG_REPLY drawRoundRect(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_RADIUS, SG_COLOUR, SG_FILLGEOM);
	
	SG_REPLY drawGradientRect(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_COLOUR, SG_COLOUR, SG_ORIENTATIONPARAMETER);
	
	SG_REPLY drawTriangle(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_COLOUR, SG_FILLGEOM);
	
	SG_REPLY drawArc(SG_AXIS, SG_AXIS, SG_RADIUS, SG_RADIUS, SG_ARCQUADRANT, SG_COLOUR, SG_FILLGEOM);
	
	SG_REPLY drawCircle(SG_AXIS, SG_AXIS, SG_RADIUS, SG_COLOUR, SG_FILLGEOM);
	
	SG_REPLY drawEllipse(SG_AXIS, SG_AXIS, SG_RADIUS, SG_RADIUS, SG_COLOUR, SG_FILLGEOM);		
	
/****************************************************************/
//String Functions
/****************************************************************/		
	SG_REPLY putLetter(SG_AXIS, SG_AXIS, char, SG_AXIS*);
	
	SG_REPLY printNumber(SG_AXIS, SG_AXIS, float);	

	//function only for the SmartGPU2 LCD480x272 4.3" and SmartGPU2 LCD800X480 7.0", function only available on those processors
	SG_REPLY printSpecialNumber(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, float, unsigned char, unsigned char);

	SG_REPLY string(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, char[], SG_NUMBEROFBYTES*); //returns in SG_NUMBEROFBYTES the successfully printed chars or letters
	
	SG_REPLY stringSD(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_NUMBEROFBYTES, SG_NUMBEROFBYTES, SG_FILENAME, SG_NUMBEROFBYTES*); //returns in SG_NUMBEROFBYTES the successfully printed chars or letters
	
	SG_REPLY setTextColour(SG_COLOUR);
	
	SG_REPLY setTextBackColour(SG_COLOUR);

	SG_REPLY setTextSize(SG_FONTSIZE);

	SG_REPLY setTextBackFill(SG_TEXTBACKGROUND);	
	
/****************************************************************/
//Image Functions
/****************************************************************/		
	SG_REPLY drawIcon(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, const int[]);
	
	SG_REPLY imageBMPSD(SG_AXIS, SG_AXIS, SG_FILENAME);
	
	SG_REPLY imageJPGSD(SG_AXIS, SG_AXIS, SG_JPGSCALEFACTOR, SG_FILENAME);	

	SG_REPLY getImageFromMemory(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, char[]); //Read the internal memory of the SMARTGPU2, This command returns 24bit pixels (3 bytes)

	SG_REPLY screenshot();
	
/****************************************************************/
//Video Functions
/****************************************************************/			
	SG_REPLY allocateVideoSD(SG_FILENAME, SG_VIDDATA*);

	SG_REPLY freeVideoSD();
	
	SG_REPLY setFrameVideoSD(unsigned int);
	
	SG_REPLY playVideoSD(SG_AXIS, SG_AXIS, unsigned int);	
	
/****************************************************************/
//Audio Functions
/****************************************************************/		
	SG_REPLY initDACAudio(SG_STATE);

	SG_REPLY audioBoost(SG_STATE);

	SG_REPLY getWAVPlayState(SG_STATE*);

	SG_REPLY playWAVFile(SG_FILENAME, unsigned int*); //returns in unsigned int* the file duration in seconds

	SG_REPLY pauseWAVFile();

	SG_REPLY stopWAVFile();

	SG_REPLY advanceWAVFile(unsigned int); //advance file to the parameter(means seconds)

	SG_REPLY setVolumeWAV(unsigned char);	
	
/****************************************************************/
//Real Time Clock Functions
/****************************************************************/			
	SG_REPLY setupRTC(SG_STATE*);
	
	SG_REPLY getRTCTimeDate(SG_TIME*);
	
	SG_REPLY setRTCTimeDate(SG_TIME*);

/****************************************************************/
//Objects Functions - Refer to "smartGPU2 Command Set" to learn about minimum width and height objects size.
/****************************************************************/			
	SG_REPLY objButton(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_ACTIVE, char[]);

	SG_REPLY objSwitch(SG_AXIS, SG_AXIS, unsigned int, SG_ACTIVE);
	
	SG_REPLY objCheckbox(SG_AXIS, SG_AXIS, unsigned int, SG_ACTIVE);

	SG_REPLY objProgressBar(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, unsigned char);

	SG_REPLY objSlider(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, unsigned char, unsigned char, SG_ORIENTATIONPARAMETER);

	SG_REPLY objScrollBar(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, unsigned char, unsigned char, SG_ORIENTATIONPARAMETER, SG_ACTIVE);

	SG_REPLY objWindow(SG_AXIS, SG_AXIS, SG_AXIS, SG_AXIS, SG_FONTSIZE, SG_WINDOWTYPE, char[]);

/****************************************************************/
//EEPROM-FLASH Functions - Refer to "smartGPU2 Command Set" to learn about READ-WRITE procedure, and page SIZE.
/****************************************************************/			
	SG_REPLY initClearEEPROMBuff();

	SG_REPLY readEEPROMBuff(char[], SG_ADDRESS, SG_NUMBEROFBYTES, SG_NUMBEROFBYTES*);

	SG_REPLY writeEEPROMBuff(char[], SG_ADDRESS, SG_NUMBEROFBYTES, SG_NUMBEROFBYTES*);

	SG_REPLY saveBuffToEEPROMPage(SG_EEPROMPAGE);

	SG_REPLY fillBuffFromEEPROMPage(SG_EEPROMPAGE);

	SG_REPLY compBuffToEEPROMPage(SG_EEPROMPAGE, unsigned char*);
	
	SG_REPLY eraseEEPROMPage(SG_EEPROMPAGE);
	
/****************************************************************/
//Touch Functions
//Those next Touch Functions return valid or invalid touch coordinates status(TOUCHREPLY) instead of ACK 'O' or NAK 'F'(SG_REPLY)
/****************************************************************/	
	SG_TOUCHREPLY touchScreen(SG_POINT*);
    //function only for the SmartGPU2 LCD320x240 2.4" as it is the only board with touch icons
	SG_TOUCHREPLY touchIcon(SG_ICON*);

	
/****************************************************************/
//SD FAT management Functions
//Those next SDF - SD Functions return file execution status(SG_FILERESULT) instead of ACK 'O' or NAK 'F'(SG_REPLY)
/****************************************************************/
	SG_FILERESULT SDFgetList(unsigned int*, unsigned int*); //get number of dirs and files

	SG_FILERESULT SDFgetDirName(SG_ITEMNUMBER, SG_FILENAME); //searches for the "itemNumber" on the SD current folder and updates the buffer with the Dir name ended with NULL character

	SG_FILERESULT SDFgetFileName(SG_ITEMNUMBER, SG_FILENAME); //searches for the "itemNumber" on the SD current folder and updates the buffer with the File name ended with NULL character

	SG_FILERESULT SDFgetDirPath(char[]); //obtains current dir path and stores on path[] buffer

	SG_FILERESULT SDFnewDir(SG_FILENAME); //create a new Directory, fails if already exist

	SG_FILERESULT SDFnewFile(SG_FILENAME); //create a new File, fails if already exist
	
	SG_FILERESULT SDFopenDir(SG_FILENAME); //opens an existing Dir

	SG_FILERESULT SDFopenFile(SG_FILENAME, SG_OPENMODE, SG_WORKSPACEBLOCK); //opens an existing file in READONLY, WRITEONLY or READWRITE mode on the received object # workspace

	SG_FILERESULT SDFcloseFile(SG_WORKSPACEBLOCK); //close and save file object # workspace
 
	SG_FILERESULT SDFsaveFile(SG_WORKSPACEBLOCK); //sync/save file object # workspace

	SG_FILERESULT SDFsetFilePointer(SG_POINTERPOSITION, SG_WORKSPACEBLOCK); // set/move file pointer of file object # workspace

	SG_FILERESULT SDFgetFilePointer(SG_POINTERPOSITION*, SG_WORKSPACEBLOCK); // get file pointer of file object # workspace

	SG_FILERESULT SDFreadFile(char[], SG_NUMBEROFBYTES, SG_NUMBEROFBYTES*, SG_WORKSPACEBLOCK); //Bytes to Read, Succesfully Read Bytes, file object # to read bytes from

	SG_FILERESULT SDFwriteFile(char[], SG_NUMBEROFBYTES, SG_NUMBEROFBYTES*,  SG_WORKSPACEBLOCK); //Bytes to Write, Succesfully Written Bytes, file object # to write bytes

	SG_FILERESULT SDFtestFileError(SG_WORKSPACEBLOCK);  //test for an error on file # workspace

	SG_FILERESULT SDFtestFileEnd(SG_WORKSPACEBLOCK);  //test for an error on file # workspace

	SG_FILERESULT SDFtruncateFile(SG_WORKSPACEBLOCK);  //truncates the file size to the current file read/write pointer of the file # workspace

	SG_FILERESULT SDFeraseDirFile(SG_FILENAME); //Erases an existing Dir or File

	SG_FILERESULT SDFsetFileTimeDate(SG_TIME*, SG_FILENAME); //Set Time and Date to an existing File

	SG_FILERESULT SDFgetFileTimeDate(SG_TIME*, SG_FILENAME); //Get Time and Date to an existing File

	SG_FILERESULT SDFgetFileSize(SG_FILENAME, unsigned long *); //Get Size of an existing File

	SG_FILERESULT SDFrenameMoveDirFile(SG_FILENAME, SG_FILENAME); //renames or moves an existing Dir or File

	SG_FILERESULT SDFgetFreeTotalSpace(unsigned long *,unsigned long *); //Get free and total space in bytes of the microSD card

private:

	SG_AXIS wid;
	SG_AXIS hei;
	
};

#endif
