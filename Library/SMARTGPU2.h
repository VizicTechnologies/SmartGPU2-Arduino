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

#ifndef SMARTGPU2_h
#define SMARTGPU2_h

#include <inttypes.h>

/*******************USER MODIFABLE**********************/
//If using smartGPU2 2.4" LCD320x240 mounted directly as arduino shield, please uncomment the next:
//#define SMARTGPU2ASSHIELD

//If using Arduino DUE please uncomment the next line - Remember to re-wire smartGPU2 TX and RX pins to the defined Serial port of Arduino
//#define ARDUINO_DUE

//-SmartGPU2-Arduino RESET PIN definition 
//-SmartSHIELD uses default Arduino pin p4 for Reset, if another pin is soldered in the SmartSHIELD(pin 7, 8 or 13), please modify here:
#define RESET 4        //Define for the RESET pin connected on the SmartSHIELD board(pin 7, 8 or 13) 

//-Arduino serial port and AREF configuration using smartSHIELD
#ifdef ARDUINO_DUE                  //If arduino DUE is defined
#define SERIALPORT        (Serial3) //(Serial2,Serial3), connect the smartGPU2 TX and RX pins to the defined serial port of Arduino
#define ARDUINOREFERENCE   AR_DEFAULT
#else                               //Arduino UNO. MEGA or similar
#define SERIALPORT        (Serial)
#define ARDUINOREFERENCE  DEFAULT   //Define the AREF pin - Internal Analog reference as DEFAULT
#endif
/****************END OF USER MODIFABLE******************/



/**************DON'T MODIFY UP FROM HERE****************/
//SmartGPU2-Arduino security RESET PIN re-definition and AREF pin re-configuration if using SmartGPU2 LCD320x240 2.4" directly as shield
#ifdef SMARTGPU2ASSHIELD            //define valid only for the SmartGPU2 LCD320x240 2.4" mounted directly as Arduino Shield
#ifdef ARDUINO_DUE                  //If arduino DUE is defined
#error "smartGPU2 LCD320x240 2.4 board can't be used directly mounted as shield on Arduino DUE, connect via SmartSHIELD or jumpers"
#endif
#define RESET              13       //re-define RESET pin as 13 as this is the pin that is connected to Reset 
#define ARDUINOREFERENCE   EXTERNAL //re-define AREF pin reference as EXTERNAL in order to not interfere with 3.3V of smartGPU2
#endif

//General definitions
#define OFF 0
#define ON  1
#define GND 0
#define VCC 1
#define SCROLLBUTTONSIZE 25

//basic colours definitions
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F

//File access definitions
#define BEGINNING    0
#define ALLCONTENTS  0

//General typedefs
typedef unsigned int AXIS;
typedef unsigned int COLOUR;
typedef unsigned int RADIUS;
typedef unsigned int NUMBEROFBYTES;
typedef unsigned int ITEMNUMBER;
typedef unsigned int ADDRESS;
typedef unsigned long POINTERPOSITION;
typedef char FILENAME[];

typedef enum {
	DISABLE, //0
	ENABLE   //1
} STATE; //to set Enable/Disable States

typedef enum {
	DESELECTED, //0
	SELECTED    //1
} ACTIVE; //to set Selected/DeSelected Active objects

typedef enum {
	DESELECTEDTRANS, //0 set an unselected top window with transparent center
	SELECTEDTRANS,   //1 set a selected window with transparent center
	SELECTEDGRAY,    //2 set a selected window with gray center
	SELECTEDWHITE    //3 set a selected window with white center
} WINDOWTYPE; //to set type of window to draw

typedef struct {
	AXIS x; //X axis
	AXIS y; //Y axis
} POINT;    //to create a point with point.x and point.y variables

typedef enum {
	OK   = 'O',  //Command successfully executed
	FAIL = 'F'   //Command Fail
} SMARTGPUREPLY; //to get SmartGPU2 command responses

//Graphics functions definitions
typedef enum {
	UNFILL, //0
	FILL    //1
} FILLGEOM;  //to set fill or unfill colour geometry

typedef enum {
	HORIZONTAL, //0
	VERTICAL    //1
} ORIENTATIONPARAMETER;//to set gradient colour fade orientation and objects: scrollBar and Slider orientations

typedef enum {
	LANDSCAPE_LEFT,     //0 left
	PORTRAIT_LOW,      //1 low
	LANDSCAPE_RIGHT,     //2 right
	PORTRAIT_TOP       //3 top
} LCDORIENTATIONS;  //to set LCD orientations

typedef enum {
	QUADRANT1 = 1, //1
	QUADRANT2,     //2
	QUADRANT3,     //3
	QUADRANT4      //4
} ARCQUADRANT;     //to set desired arc drawing quadrant

//fonts definitions
typedef enum {
	FONT0 = 0,
	FONT1,
	FONT2,
	FONT3,
	FONT4,
	FONT5,
	FONT6,
	FONT7,
	FONT8,
	FONT9,
	FONT10,
	FONT11,
	FONT12,
	FONT13
} FONTSIZE; //to set text font sizes

typedef enum {
	TRANS = 0,
	FILLED
} TEXTBACKGROUNDCOLOURFILLUNFILL; //to set text background colour to transparent or filled

//Video 
typedef struct {
	unsigned int width;  //X width
	unsigned int height; //Y height
	unsigned int framesPerSec; //video frames per second
	unsigned int totalFrames;  //video total frames in the file
} VIDDATA;    //to create a Video Data struct containing, size X, size Y, frames per second and totalframes info

//Touch definitions
typedef enum {
	INVALID,  //returned touch point is invalid
	VALID     //returned touch point is valid
} TOUCHREPLY; //to get SmartGPU2 touch responses

typedef enum {
	HOUSE    = 'H',
	MESSAGE  = 'M',
	BOOK     = 'B',
	PHONE    = 'P',
	SONG     = 'S',
	NONE     = 'N'
} ICON;  //to get the type of touched icon

//File access definitions
typedef enum {
	READONLY = 1, //1
	WRITEONLY,    //2
	READWRITE     //3
} OPENMODE;       //to set the file access open mode

//SMARTGPU2 Command Execution responses definitions
typedef enum {
	F_OK = 0,				/* (0) Succeeded */
	F_DISK_ERR,				/* (1) A hard error occurred in the low level disk I/O layer */
	F_INT_ERR,				/* (2) Assertion failed */
	F_NOT_READY,			/* (3) The physical drive cannot work */
	F_NO_FILE,				/* (4) Could not find the file */
	F_NO_PATH,				/* (5) Could not find the path */
	F_INVALID_NAME,			/* (6) The path name format is invalid */
	F_DENIED,				/* (7) Access denied due to prohibited access or directory full */
	F_EXIST,				/* (8) Access denied due to prohibited access */
	F_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
	F_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
	F_INVALID_DRIVE,		/* (11) The logical drive number is invalid */
	F_NOT_ENABLED,			/* (12) The volume has no work area */
	F_NO_FILESYSTEM,		/* (13) There is no valid FAT volume */
	F_MKFS_ABORTED,			/* (14) The f_mkfs() aborted due to any parameter error */
	F_TIMEOUT,				/* (15) Could not get a grant to access the volume within defined period */
	F_LOCKED,				/* (16) The operation is rejected according to the file sharing policy */
	F_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
	F_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > _FS_SHARE */
	F_INVALID_PARAMETER		/* (19) Given parameter is invalid */
} FILERESULT;               //Gets all FAT functions related responses

//SMARTGPU2 WorkSpaces definitions
typedef enum {
	WORKSPACE0 = 0, 
	WORKSPACE1,
	WORKSPACE2,
	WORKSPACE3 
} WORKSPACEBLOCK;  //to set the working workspace

//SMARTGPU2 EEPROM pages definitions, each page is 2048bytes (2Kb) in size
typedef enum {
	PAGE0 = 0, 
	PAGE1,
	PAGE2,
	PAGE3,
	PAGE4,
	PAGE5,
	PAGE6,
	PAGE7
} EEPROMPAGE;  //to set the EEPROM page

//Files Time and Date
typedef struct {
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char day;
	unsigned char month;
	unsigned int  year;	
} TIME;    //to create a Time-Date info struct

//JPG images scale factor definitions
typedef enum {
	SCALE1_1 = 0,  // 1 to 1
	SCALE1_2,      // 1 to 2
	SCALE1_4,      // 1 to 4
	SCALE1_8       // 1 to 8
} JPGSCALEFACTOR; //to set the desired JPG image decompression scale factor

//Recommended(but not limited to) Arduino-SmartGPU Baud rate definitions
typedef enum{
	BAUD0 = 9600,
	BAUD1 = 19200,
	BAUD2 = 57600,
	BAUD3 = 115200,
	BAUD4 = 256000,
	BAUD5 = 500000,
	BAUD6 = 1000000,
	BAUD7 = 2000000
} BAUDRATE;


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
	
	void init();

	SMARTGPUREPLY reset();
	
	SMARTGPUREPLY start();  

/****************************************************************/
//Master Functions
/****************************************************************/	
	SMARTGPUREPLY erase();

	SMARTGPUREPLY sleep(STATE);
	
	SMARTGPUREPLY orientation(LCDORIENTATIONS);
	
	SMARTGPUREPLY bright(unsigned char);
	
	SMARTGPUREPLY baudChange(unsigned long);
		
	SMARTGPUREPLY setEraseBackColour(COLOUR);
	
	SMARTGPUREPLY getWidth(AXIS*);

    SMARTGPUREPLY getHeight(AXIS*);

/****************************************************************/
//Geometric Functions
/****************************************************************/		
	SMARTGPUREPLY putPixel(AXIS, AXIS, COLOUR);
	
	SMARTGPUREPLY drawLine(AXIS, AXIS, AXIS, AXIS, COLOUR);
	
	SMARTGPUREPLY drawRectangle(AXIS, AXIS, AXIS, AXIS, COLOUR, FILLGEOM);

	SMARTGPUREPLY drawRoundRect(AXIS, AXIS, AXIS, AXIS, RADIUS, COLOUR, FILLGEOM);
	
	SMARTGPUREPLY drawGradientRect(AXIS, AXIS, AXIS, AXIS, COLOUR, COLOUR, ORIENTATIONPARAMETER);
	
	SMARTGPUREPLY drawTriangle(AXIS, AXIS, AXIS, AXIS, AXIS, AXIS, COLOUR, FILLGEOM);
	
	SMARTGPUREPLY drawArc(AXIS, AXIS, RADIUS, RADIUS, ARCQUADRANT, COLOUR, FILLGEOM);
	
	SMARTGPUREPLY drawCircle(AXIS, AXIS, RADIUS, COLOUR, FILLGEOM);
	
	SMARTGPUREPLY drawEllipse(AXIS, AXIS, RADIUS, RADIUS, COLOUR, FILLGEOM);		
	
/****************************************************************/
//String Functions
/****************************************************************/		
	SMARTGPUREPLY putLetter(AXIS, AXIS, char, AXIS*);
	
	SMARTGPUREPLY printNumber(AXIS, AXIS, float);	

	//function only for the SmartGPU2 LCD480x272 4.3" and SmartGPU2 LCD800X480 7.0", function only available on those processors
	SMARTGPUREPLY printSpecialNumber(AXIS, AXIS, AXIS, AXIS, float, unsigned char, unsigned char);

	SMARTGPUREPLY string(AXIS, AXIS, AXIS, AXIS, char[], NUMBEROFBYTES*); //returns in NUMBEROFBYTES the successfully printed chars or letters
	
	SMARTGPUREPLY stringSD(AXIS, AXIS, AXIS, AXIS, NUMBEROFBYTES, NUMBEROFBYTES, FILENAME, NUMBEROFBYTES*); //returns in NUMBEROFBYTES the successfully printed chars or letters
	
	SMARTGPUREPLY setTextColour(COLOUR);
	
	SMARTGPUREPLY setTextBackColour(COLOUR);

	SMARTGPUREPLY setTextSize(FONTSIZE);

	SMARTGPUREPLY setTextBackFill(TEXTBACKGROUNDCOLOURFILLUNFILL);	
	
/****************************************************************/
//Image Functions
/****************************************************************/		
	SMARTGPUREPLY drawIcon(AXIS, AXIS, AXIS, AXIS, const int[]);
	
	SMARTGPUREPLY imageBMPSD(AXIS, AXIS, FILENAME);
	
	SMARTGPUREPLY imageJPGSD(AXIS, AXIS, JPGSCALEFACTOR, FILENAME);	

	SMARTGPUREPLY getImageFromMemory(AXIS, AXIS, AXIS, AXIS, char[]); //Read the internal memory of the SMARTGPU2, This command returns 24bit pixels (3 bytes)

	SMARTGPUREPLY screenshot();
	
/****************************************************************/
//Video Functions
/****************************************************************/			
	SMARTGPUREPLY allocateVideoSD(FILENAME, VIDDATA*);

	SMARTGPUREPLY freeVideoSD();
	
	SMARTGPUREPLY setFrameVideoSD(unsigned int);
	
	SMARTGPUREPLY playVideoSD(AXIS, AXIS, unsigned int);	
	
/****************************************************************/
//Audio Functions
/****************************************************************/		
	SMARTGPUREPLY initDACAudio(STATE);

	SMARTGPUREPLY audioBoost(STATE);

	SMARTGPUREPLY getWAVPlayState(STATE*);

	SMARTGPUREPLY playWAVFile(FILENAME, unsigned int*); //returns in unsigned int* the file duration in seconds

	SMARTGPUREPLY pauseWAVFile();

	SMARTGPUREPLY stopWAVFile();

	SMARTGPUREPLY advanceWAVFile(unsigned int); //advance file to the parameter(means seconds)

	SMARTGPUREPLY setVolumeWAV(unsigned char);	
	
/****************************************************************/
//Real Time Clock Functions
/****************************************************************/			
	SMARTGPUREPLY setupRTC(STATE*);
	
	SMARTGPUREPLY getRTCTimeDate(TIME*);
	
	SMARTGPUREPLY setRTCTimeDate(TIME*);

/****************************************************************/
//Objects Functions - Refer to "smartGPU2 Command Set" to learn about minimum width and height objects size.
/****************************************************************/			
	SMARTGPUREPLY objButton(AXIS, AXIS, AXIS, AXIS, ACTIVE, char[]);

	SMARTGPUREPLY objSwitch(AXIS, AXIS, unsigned int, ACTIVE);
	
	SMARTGPUREPLY objCheckbox(AXIS, AXIS, unsigned int, ACTIVE);

	SMARTGPUREPLY objProgressBar(AXIS, AXIS, AXIS, AXIS, unsigned char);

	SMARTGPUREPLY objSlider(AXIS, AXIS, AXIS, AXIS, unsigned char, unsigned char, ORIENTATIONPARAMETER);

	SMARTGPUREPLY objScrollBar(AXIS, AXIS, AXIS, AXIS, unsigned char, unsigned char, ORIENTATIONPARAMETER, ACTIVE);

	SMARTGPUREPLY objWindow(AXIS, AXIS, AXIS, AXIS, FONTSIZE, WINDOWTYPE, char[]);

/****************************************************************/
//EEPROM-FLASH Functions - Refer to "smartGPU2 Command Set" to learn about READ-WRITE procedure, and page SIZE.
/****************************************************************/			
	SMARTGPUREPLY initClearEEPROMBuff();

	SMARTGPUREPLY readEEPROMBuff(char[], ADDRESS, NUMBEROFBYTES, NUMBEROFBYTES*);

	SMARTGPUREPLY writeEEPROMBuff(char[], ADDRESS, NUMBEROFBYTES, NUMBEROFBYTES*);

	SMARTGPUREPLY saveBuffToEEPROMPage(EEPROMPAGE);

	SMARTGPUREPLY fillBuffFromEEPROMPage(EEPROMPAGE);

	SMARTGPUREPLY compBuffToEEPROMPage(EEPROMPAGE, unsigned char*);
	
	SMARTGPUREPLY eraseEEPROMPage(EEPROMPAGE);
	
/****************************************************************/
//Touch Functions
//Those next Touch Functions return valid or invalid touch coordinates status(TOUCHREPLY) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/	
	TOUCHREPLY touchScreen(POINT*);
    //function only for the SmartGPU2 LCD320x240 2.4" as it is the only board with touch icons
	TOUCHREPLY touchIcon(ICON*);

	
/****************************************************************/
//SD FAT management Functions
//Those next SDF - SD Functions return file execution status(FILERESULT) instead of ACK 'O' or NAK 'F'(SMARTGPUREPLY)
/****************************************************************/
	FILERESULT SDFgetList(unsigned int*, unsigned int*); //get number of dirs and files

	FILERESULT SDFgetDirName(ITEMNUMBER, FILENAME); //searches for the "itemNumber" on the SD current folder and updates the buffer with the Dir name ended with NULL character

	FILERESULT SDFgetFileName(ITEMNUMBER, FILENAME); //searches for the "itemNumber" on the SD current folder and updates the buffer with the File name ended with NULL character

	FILERESULT SDFgetDirPath(char[]); //obtains current dir path and stores on path[] buffer

	FILERESULT SDFnewDir(FILENAME); //create a new Directory, fails if already exist

	FILERESULT SDFnewFile(FILENAME); //create a new File, fails if already exist
	
	FILERESULT SDFopenDir(FILENAME); //opens an existing Dir

	FILERESULT SDFopenFile(FILENAME, OPENMODE, WORKSPACEBLOCK); //opens an existing file in READONLY, WRITEONLY or READWRITE mode on the received object # workspace

	FILERESULT SDFcloseFile(WORKSPACEBLOCK); //close and save file object # workspace
 
	FILERESULT SDFsaveFile(WORKSPACEBLOCK); //sync/save file object # workspace

	FILERESULT SDFsetFilePointer(POINTERPOSITION, WORKSPACEBLOCK); // set/move file pointer of file object # workspace

	FILERESULT SDFgetFilePointer(POINTERPOSITION*, WORKSPACEBLOCK); // get file pointer of file object # workspace

	FILERESULT SDFreadFile(char[], NUMBEROFBYTES, NUMBEROFBYTES*, WORKSPACEBLOCK); //Bytes to Read, Succesfully Read Bytes, file object # to read bytes from

	FILERESULT SDFwriteFile(char[], NUMBEROFBYTES,NUMBEROFBYTES*,  WORKSPACEBLOCK); //Bytes to Write, Succesfully Written Bytes, file object # to write bytes

	FILERESULT SDFtestFileError(WORKSPACEBLOCK);  //test for an error on file # workspace

	FILERESULT SDFtestFileEnd(WORKSPACEBLOCK);  //test for an error on file # workspace

	FILERESULT SDFtruncateFile(WORKSPACEBLOCK);  //truncates the file size to the current file read/write pointer of the file # workspace

	FILERESULT SDFeraseDirFile(FILENAME); //Erases an existing Dir or File

	FILERESULT SDFsetFileTimeDate(TIME*, FILENAME); //Set Time and Date to an existing File

	FILERESULT SDFgetFileTimeDate(TIME*, FILENAME); //Get Time and Date to an existing File

	FILERESULT SDFgetFileSize(FILENAME, unsigned long *); //Get Size of an existing File

	FILERESULT SDFrenameMoveDirFile(FILENAME, FILENAME); //renames or moves an existing Dir or File

	FILERESULT SDFgetFreeTotalSpace(unsigned long *,unsigned long *); //Get free and total space in bytes of the microSD card

private:

	AXIS wid;
	AXIS hei;
	
};

#endif
