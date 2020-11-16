#define USE_TOUCHSCREEN 
//#define USE_JOYSTICK 
//#define USE_ACCELEROMETER 

//Screen resolution
#define MAX_X_LANDSCAPE 480
#define MAX_Y_LANDSCAPE 320
#define MAX_X_PORTRAIT  320
#define MAX_Y_PORTRAIT  480

#include <SMARTGPU2.h>   

#ifdef USE_ACCELEROMETER
#include <Wire.h>
#include <ADXL345.h>
#endif

#define MODE_10 10
#define MODE_16 16
#define MODE_20 20

int mode = MODE_16;
boolean showScoreboard = true;

#define BOARD_BLANK 0
#define BOARD_APPLE 1
#define BOARD_BOMB  2
#define BOARD_WALL  3
#define BOARD_SNAKE 4
#define MIN_APPLE_COLLECTION 25

#define r1 12
#define r2 11
#define r3 10
#define r4 9

#define c1 8
#define c2 7
#define c3 6
#define c4 5
#define joyPin1   0  
#define joyPin2   1
#define joyButton 2
  
#define DARK_RED 0xC800
#define GREY1 0x2104
#define GREY2 0x3186
#define GREY3 0x528A
#define GREY4 0x630C
#define GREY5 0x8410
#define GREY6 0xA514
#define GREY7 0xB596
#define GREY8 0xC618
#define GREY9 0xE71C

SMARTGPU2 lcd;          

boolean createBomb = false;
boolean gameOver = false;
boolean levelOver = false;


int level = 0;
int lastApplePosition = 0;
int lastAppleFlash = 0;

int CELL_WIDTH = mode;
int CELL_HEIGHT = mode;
int CELL_MAXIMUM_X = ((MAX_X_LANDSCAPE + 1) / CELL_WIDTH);
int CELL_MAXIMUM_Y = ((MAX_Y_LANDSCAPE + 1) / CELL_HEIGHT) - (showScoreboard ? (mode == MODE_10 ? 2 : 1) : 0);
int CELL_WIDTH_HALF = CELL_WIDTH / 2;
int CELL_HEIGHT_HALF = CELL_HEIGHT / 2;
int CELL_RADIUS = (CELL_HEIGHT / 2) - 1;

int MESSAGE_BOX_WIDTH = 286;
int MESSAGE_BOX_LEFT = ((MAX_X_LANDSCAPE + 1) - (MESSAGE_BOX_WIDTH - 16)) / 2;
int MESSAGE_BOX_HEIGHT = 185;
int MESSAGE_BOX_TOP = ((MAX_Y_LANDSCAPE + 1) - MESSAGE_BOX_HEIGHT) / 2;

int COUNTDOWN_LEVEL_LEFT = ((MAX_X_LANDSCAPE + 1) / 2) - 104; //118;  
int COUNTDOWN_LEVEL_WIDTH = 27;
int COUNTDOWN_MAIN_LEFT = ((MAX_X_LANDSCAPE + 1) / 2) - 77; //145;
int COUNTDOWN_MAIN_WIDTH = 180;
int COUNTDOWN_TOP = ((MAX_Y_LANDSCAPE + 1) / 2) - 70; //60;  
int COUNTDOWN_HEIGHT = 140;  
int COUNTDOWN_LABEL_X = ((MAX_Y_LANDSCAPE + 1) / 2) - 26;
int COUNTDOWN_LABEL_Y = ((MAX_X_LANDSCAPE + 1) / 2) - 98; //125;  
int COUNTDOWN_COUNTL_X = ((MAX_Y_LANDSCAPE + 1) / 2) + 26;  

byte screen[20][32] = {0};
int snake[50] = {0};

byte head = 0;
byte tail = 0;
byte length = 0;
byte maxLength = 50;
byte fruit = 0;
char buf[10];
int inputX = 0;        
int inputY = 0;  
int inputZ = 0;  

char momentumX = 1, momentumY = 0;

SG_FILLGEOM solidFill = (SG_FILLGEOM)1;
SG_FILLGEOM hollowFill = (SG_FILLGEOM)0;

#ifdef USE_TOUCHSCREEN
SG_POINT point;
int SCREEN_X_THIRD =  ((MAX_X_LANDSCAPE + 1) / 3);
int SCREEN_Y_THIRD =  ((MAX_Y_LANDSCAPE + 1) / 3);
#endif

#ifdef USE_ACCELEROMETER
SG_POINT point;
ADXL345 adxl;
#endif

void setup() {                
    
  lcd.init();  
  lcd.start(); 
  lcd.baudChange(SG_BAUD4); 
    
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);

  pinMode(c1, INPUT);
  pinMode(c2, INPUT);
  pinMode(c3, INPUT);
  pinMode(c4, INPUT);
  
  randomSeed(analogRead(3));

#ifdef USE_ACCELEROMETER

  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625μs per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);

#endif

}

void loop() {

  gameOver = false;
  levelOver = false;
  level = 0;
  
  
  while (!gameOver) {

    fruit = 0;
    for (int x = 0; x < (CELL_MAXIMUM_X / 4); x++) {
      
      for (int y = 0; y < CELL_MAXIMUM_Y; y++) {
        
        screen[x][y] = 0;
        
      }
      
    }
    
    snake[0] = getCoords(2, 2);
    snake[1] = getCoords(3, 2);
    snake[2] = getCoords(4, 2);
    snake[3] = getCoords(5, 2);
    snake[4] = getCoords(6, 2);
    
    tail = 0;
    head = 4;
    length = 5;
    momentumX = 1;
    momentumY = 0;
 
    populateScreen_Frame();
   
    lastApplePosition = createItem(BOARD_APPLE);
    
    for (int x = 0; x < (level + 1); x++) {
      createItem(BOARD_BOMB);
      createItem(BOARD_BOMB);
    }
    
    drawScreen();
    drawSnake();
    levelOver = false;
  
    drawCountDown();
    
    while (!gameOver && !levelOver) {
      
      if ((length + 1) >= MIN_APPLE_COLLECTION) {

        lastAppleFlash++;
        
        if (lastAppleFlash > 5) { lastAppleFlash = 0;}
        
        if (lastAppleFlash == 0) {
          
          drawItem(getCoordX(lastApplePosition), getCoordY(lastApplePosition), BOARD_BLANK);
          
        }
       
        if (lastAppleFlash == 3) {
          
          drawItem(getCoordX(lastApplePosition), getCoordY(lastApplePosition), BOARD_APPLE);
          
        }
        
      }
 

#ifdef USE_TOUCHSCREEN

      lcd.touchScreen(&point);
      inputY = (point.x > SCREEN_X_THIRD && point.x < SCREEN_X_THIRD * 2 ? (point.y < SCREEN_Y_THIRD ? -1 : (point.y > SCREEN_Y_THIRD * 2 ? 1 : 0)) : 0);
      inputX = (point.y > SCREEN_Y_THIRD && point.y < SCREEN_Y_THIRD * 2 ? (point.x < SCREEN_X_THIRD ? -1 : (point.x > SCREEN_X_THIRD * 2 ? 1 : 0)) : 0);

      if (momentumX != 1 && inputX < 0)              { momentumX = -1; momentumY = 0; }
      if (momentumX != -1 && inputX > 0)             { momentumX = 1; momentumY = 0; }
      if (momentumY != 1 && inputY < 0)              { momentumX = 0; momentumY = -1; }
      if (momentumY != -1 && inputY > 0)             { momentumX = 0; momentumY = 1; }

#endif 

#ifdef USE_JOYSTICK

      inputX = 1024-analogRead(joyPin1);  
      inputY = analogRead(joyPin2);  

      if (momentumX != 1 && inputX < 100)            { momentumX = -1; momentumY = 0; }
      if (momentumX != -1 && inputX > 900)           { momentumX = 1; momentumY = 0; }
      if (momentumY != 1 && inputY < 100)            { momentumX = 0; momentumY = -1; }
      if (momentumY != -1 && inputY > 900)           { momentumX = 0; momentumY = 1; }
      
#endif

#ifdef USE_ACCELEROMETER

      adxl.readAccel(&inputX, &inputY, &inputZ); 
      inputY = inputY * -1;
      
      if (momentumX != 1 && inputX < -50)            { momentumX = -1; momentumY = 0; }
      if (momentumX != -1 && inputX > +50)           { momentumX = 1; momentumY = 0; }
      if (momentumY != 1 && inputY < -50)            { momentumX = 0; momentumY = -1; }
      if (momentumY != -1 && inputY > +50)           { momentumX = 0; momentumY = 1; }
      
#endif


 
      byte oldX = getCoordX(snake[head]);
      byte oldY = getCoordY(snake[head]);
      
      switch (getBoardValue(oldX + momentumX, oldY + momentumY)) {
        
        case BOARD_BLANK:
        
          for (int z = 0; z < length; z++) {
            
            if (getCoordX(snake[z]) == oldX + momentumX && getCoordY(snake[z]) == oldY + momentumY) {
             
              gameOver = true;
              drawMessage(BOARD_SNAKE);
              break;
              
            }
            
          }
           
          if (!gameOver) {  
        
            moveSnake(getCoords(oldX + momentumX, oldY + momentumY));
            
          }
          
          break;        
      
        case BOARD_APPLE:
        
          if (length + 1 < MIN_APPLE_COLLECTION) {
              
            setBoardValue(oldX + momentumX, oldY + momentumY, BOARD_BLANK);
            moveSnakeAndGrow(getCoords(oldX + momentumX, oldY + momentumY));
            if (length < MIN_APPLE_COLLECTION) { lastApplePosition = createItem(BOARD_APPLE); };
            if (createBomb) { createItem(BOARD_BOMB); }
            createBomb = !createBomb;
            fruit++;
            if (showScoreboard) { drawScoreBoard(); }
            
          }
          else {
            
            levelOver = true;
            level++;
            drawMessage(BOARD_APPLE);
            
          }
          
          break; 
      
        case BOARD_BOMB:
          gameOver = true;
          drawMessage(BOARD_BOMB);
          break; 
      
        case BOARD_WALL:
          gameOver = true;
          drawMessage(BOARD_WALL);
          break; 
          
      }
      
      delay(150 - (fruit * 2));
      
    }
    
  }
  
}

int getBoardValue(byte x, byte y) {
  
  byte xMaj = x / 4;
  byte xMin = x % 4;
  
  int val = screen[xMaj][y];

  //1 2 4 8 16 32 64 128 
  
  switch (xMin) {
    
    case 0:
      val = val & 3;
      break;
      
    case 1:
      val = (val & 12) >> 2;
      break;
      
    case 2:
      val = (val & 48) >> 4;
      break;
      
    case 3:
      val = (val & 192) >> 6;
      break;
      
  }

  return val;
  
}


int setBoardValue(int x, int y, byte value) {
  
  byte mask = 0;
  byte xMaj = x / 4;
  byte xMin = x % 4;
  
  int val = screen[xMaj][y];
  
  switch (xMin) {
    
    case 0:
      mask = B11111100;
      val = (val & mask) | value;
      break;
      
    case 1:
      mask = B11110011;
      val = (val & mask) | (value << 2);
      break;
      
    case 2:
      mask = B11001111;
      val = (val & mask) | (value << 4);
      break;
      
    case 3:
      mask = B00111111;
      val = (val & mask) | (value << 6);
      break;
      
  }

  screen[xMaj][y] = val;
  
}

int getCoords(byte x, byte y) {
 
 return (y * CELL_MAXIMUM_X) + x;
 
}

int getCoordX(int value) {
 
 return value % CELL_MAXIMUM_X;
 
}

int getCoordY(int value) {
 
 return value / CELL_MAXIMUM_X;
 
}

void moveSnake(int coords) {
 
  int oldTail = snake[tail];
  
  head = tail;
  snake[head] = coords;
  tail++;  if (tail == length) { tail = 0; }
  
  lcd.drawRectangle(getCoordX(snake[head]) * CELL_WIDTH, getCoordY(snake[head]) * CELL_HEIGHT, (getCoordX(snake[head]) * CELL_WIDTH) + (CELL_WIDTH - 1), (getCoordY(snake[head]) * CELL_HEIGHT) + (CELL_HEIGHT - 1), SG_BLACK, solidFill);
  lcd.drawCircle((getCoordX(snake[head]) * CELL_WIDTH) + CELL_WIDTH_HALF - 1, (getCoordY(snake[head]) * CELL_HEIGHT) + CELL_HEIGHT_HALF - 1, CELL_RADIUS, SG_GREEN, solidFill);
  lcd.drawRectangle(getCoordX(oldTail) * CELL_WIDTH, getCoordY(oldTail) * CELL_HEIGHT, (getCoordX(oldTail) * CELL_WIDTH) + (CELL_WIDTH - 1), (getCoordY(oldTail) * CELL_HEIGHT) + (CELL_HEIGHT - 1), SG_BLACK, solidFill);
  
}

void moveSnakeAndGrow(int coords) {

  for (byte q=length; q > tail; q--) { 
    
    snake[q] = snake[q-1]; 
  
  } 

  length++;
  head = tail;  
  tail++;  
  snake[head] = coords; 

  lcd.drawRectangle(getCoordX(snake[head]) * CELL_WIDTH, getCoordY(snake[head]) * CELL_HEIGHT, (getCoordX(snake[head]) * CELL_WIDTH) + (CELL_WIDTH - 1), (getCoordY(snake[head]) * CELL_HEIGHT) + (CELL_HEIGHT - 1), SG_BLACK, solidFill);
  lcd.drawCircle((getCoordX(snake[head]) * CELL_WIDTH) + CELL_WIDTH_HALF - 1, (getCoordY(snake[head]) * CELL_HEIGHT) + CELL_HEIGHT_HALF - 1, CELL_RADIUS, SG_GREEN, solidFill);
  
}

void populateScreen_Frame() {
  
  
  for (int x=0; x < CELL_MAXIMUM_X; x++) {
    
    setBoardValue(x, 0, BOARD_WALL);    
    setBoardValue(x, CELL_MAXIMUM_Y - 1, BOARD_WALL);
    
  }
  
  for (int y=1; y < CELL_MAXIMUM_Y; y++) {
    
    setBoardValue(0, y, BOARD_WALL);    
    setBoardValue(CELL_MAXIMUM_X - 1, y, BOARD_WALL);
    
  }
  
  switch (level) {
    
    case 0:
      break;
    
    case 1:
       
      if (CELL_MAXIMUM_X == 48 && CELL_MAXIMUM_Y == 30) { // 480 x 320 @ 10 pixels with scoreboard
        
        setBoardValue(15, 16, BOARD_WALL); 
        setBoardValue(16, 16, BOARD_WALL); 
        setBoardValue(17, 16, BOARD_WALL); 
        setBoardValue(18, 16, BOARD_WALL); 
        setBoardValue(19, 16, BOARD_WALL); 
        setBoardValue(20, 16, BOARD_WALL); 
        setBoardValue(21, 16, BOARD_WALL); 
        setBoardValue(22, 16, BOARD_WALL); 
        setBoardValue(23, 16, BOARD_WALL); 
        setBoardValue(24, 16, BOARD_WALL); 
        setBoardValue(25, 16, BOARD_WALL); 
        setBoardValue(26, 16, BOARD_WALL); 
        setBoardValue(27, 16, BOARD_WALL); 
        setBoardValue(28, 16, BOARD_WALL); 
        setBoardValue(29, 16, BOARD_WALL); 
        setBoardValue(30, 16, BOARD_WALL); 
        setBoardValue(31, 16, BOARD_WALL); 
        setBoardValue(32, 16, BOARD_WALL); 
        
      }
       
      if (CELL_MAXIMUM_X == 30 && CELL_MAXIMUM_Y == 19) { // 480 x 320 @ 16 pixels with scoreboard
        
        setBoardValue(10, 10, BOARD_WALL); 
        setBoardValue(11, 10, BOARD_WALL); 
        setBoardValue(12, 10, BOARD_WALL); 
        setBoardValue(13, 10, BOARD_WALL); 
        setBoardValue(14, 10, BOARD_WALL); 
        setBoardValue(15, 10, BOARD_WALL); 
        setBoardValue(16, 10, BOARD_WALL); 
        setBoardValue(17, 10, BOARD_WALL); 
        setBoardValue(18, 10, BOARD_WALL); 
        setBoardValue(19, 10, BOARD_WALL); 
        setBoardValue(20, 10, BOARD_WALL); 
        
      }
       
      if (CELL_MAXIMUM_X == 24 && CELL_MAXIMUM_Y == 15) { // 480 x 320 @ 20 pixels with scoreboard
        
        setBoardValue(8, 8, BOARD_WALL); 
        setBoardValue(9, 8, BOARD_WALL); 
        setBoardValue(10, 8, BOARD_WALL); 
        setBoardValue(11, 8, BOARD_WALL); 
        setBoardValue(12, 8, BOARD_WALL); 
        setBoardValue(13, 8, BOARD_WALL); 
        setBoardValue(14, 8, BOARD_WALL); 
        setBoardValue(15, 8, BOARD_WALL); 
        
      }

      break;
    
    case 2:
       
      if (CELL_MAXIMUM_X == 48 && CELL_MAXIMUM_Y == 30) { // 480 x 360 @ 10 pixels
        
        setBoardValue(10, 10, BOARD_WALL); 
        setBoardValue(11, 10, BOARD_WALL); 
        setBoardValue(12, 10, BOARD_WALL); 
        setBoardValue(13, 10, BOARD_WALL); 
        setBoardValue(14, 10, BOARD_WALL); 
        setBoardValue(15, 10, BOARD_WALL); 
        setBoardValue(16, 10, BOARD_WALL); 
        setBoardValue(17, 10, BOARD_WALL); 
        setBoardValue(18, 10, BOARD_WALL); 
        setBoardValue(19, 10, BOARD_WALL); 
        setBoardValue(20, 10, BOARD_WALL); 
        setBoardValue(21, 10, BOARD_WALL); 
        setBoardValue(22, 10, BOARD_WALL); 
        setBoardValue(23, 10, BOARD_WALL); 
        setBoardValue(24, 10, BOARD_WALL); 
        setBoardValue(10, 11, BOARD_WALL); 
        setBoardValue(10, 12, BOARD_WALL); 
        setBoardValue(10, 13, BOARD_WALL); 
        setBoardValue(10, 14, BOARD_WALL); 
        setBoardValue(10, 15, BOARD_WALL); 
        setBoardValue(10, 16, BOARD_WALL); 
        setBoardValue(10, 17, BOARD_WALL); 
        setBoardValue(10, 18, BOARD_WALL); 
        setBoardValue(10, 19, BOARD_WALL); 
        setBoardValue(10, 20, BOARD_WALL); 
        setBoardValue(10, 21, BOARD_WALL); 
        setBoardValue(10, 22, BOARD_WALL); 

        setBoardValue(25, 22, BOARD_WALL); 
        setBoardValue(26, 22, BOARD_WALL); 
        setBoardValue(27, 22, BOARD_WALL); 
        setBoardValue(28, 22, BOARD_WALL); 
        setBoardValue(29, 22, BOARD_WALL); 
        setBoardValue(30, 22, BOARD_WALL); 
        setBoardValue(31, 22, BOARD_WALL); 
        setBoardValue(32, 22, BOARD_WALL); 
        setBoardValue(33, 22, BOARD_WALL); 
        setBoardValue(34, 22, BOARD_WALL); 
        setBoardValue(35, 22, BOARD_WALL); 
        setBoardValue(36, 22, BOARD_WALL); 
        setBoardValue(37, 22, BOARD_WALL); 
        setBoardValue(38, 22, BOARD_WALL); 
        setBoardValue(38, 21, BOARD_WALL); 
        setBoardValue(38, 20, BOARD_WALL); 
        setBoardValue(38, 19, BOARD_WALL); 
        setBoardValue(38, 18, BOARD_WALL); 
        setBoardValue(38, 17, BOARD_WALL); 
        setBoardValue(38, 16, BOARD_WALL); 
        setBoardValue(38, 15, BOARD_WALL); 
        setBoardValue(38, 14, BOARD_WALL); 
        setBoardValue(38, 13, BOARD_WALL); 
        setBoardValue(38, 12, BOARD_WALL); 
        setBoardValue(38, 11, BOARD_WALL); 
        setBoardValue(38, 10, BOARD_WALL); 

      }
       
      if (CELL_MAXIMUM_X == 30 && CELL_MAXIMUM_Y == 19) { // 480 x 360 @ 16 pixels
        
        setBoardValue(6, 5, BOARD_WALL); 
        setBoardValue(7, 5, BOARD_WALL); 
        setBoardValue(8, 5, BOARD_WALL); 
        setBoardValue(9, 5, BOARD_WALL); 
        setBoardValue(10, 5, BOARD_WALL); 
        setBoardValue(11, 5, BOARD_WALL); 
        setBoardValue(12, 5, BOARD_WALL); 
        setBoardValue(13, 5, BOARD_WALL); 
        setBoardValue(14, 5, BOARD_WALL); 
        setBoardValue(15, 5, BOARD_WALL); 
        setBoardValue(6, 6, BOARD_WALL); 
        setBoardValue(6, 7, BOARD_WALL); 
        setBoardValue(6, 8, BOARD_WALL); 
        setBoardValue(6, 9, BOARD_WALL); 
        setBoardValue(6, 10, BOARD_WALL); 
        setBoardValue(6, 11, BOARD_WALL); 
        setBoardValue(6, 12, BOARD_WALL); 
        setBoardValue(6, 13, BOARD_WALL); 
        setBoardValue(6, 14, BOARD_WALL); 

        setBoardValue(23, 5, BOARD_WALL); 
        setBoardValue(23, 6, BOARD_WALL); 
        setBoardValue(23, 7, BOARD_WALL); 
        setBoardValue(23, 8, BOARD_WALL); 
        setBoardValue(23, 9, BOARD_WALL); 
        setBoardValue(23, 10, BOARD_WALL); 
        setBoardValue(23, 11, BOARD_WALL); 
        setBoardValue(23, 12, BOARD_WALL); 
        setBoardValue(23, 13, BOARD_WALL); 
        setBoardValue(23, 14, BOARD_WALL); 
        setBoardValue(16, 14, BOARD_WALL); 
        setBoardValue(17, 14, BOARD_WALL); 
        setBoardValue(18, 14, BOARD_WALL); 
        setBoardValue(19, 14, BOARD_WALL); 
        setBoardValue(20, 14, BOARD_WALL); 
        setBoardValue(21, 14, BOARD_WALL); 
        setBoardValue(22, 14, BOARD_WALL); 
        
      }
       
      if (CELL_MAXIMUM_X == 24 && CELL_MAXIMUM_Y == 15) { // 480 x 360 @ 20 pixels
        
        setBoardValue(5, 5, BOARD_WALL); 
        setBoardValue(6, 5, BOARD_WALL); 
        setBoardValue(7, 5, BOARD_WALL); 
        setBoardValue(8, 5, BOARD_WALL); 
        setBoardValue(9, 5, BOARD_WALL); 
        setBoardValue(10, 5, BOARD_WALL); 
        setBoardValue(11, 5, BOARD_WALL); 
        setBoardValue(5, 6, BOARD_WALL); 
        setBoardValue(5, 7, BOARD_WALL); 
        setBoardValue(5, 8, BOARD_WALL); 
        setBoardValue(5, 9, BOARD_WALL); 
        setBoardValue(5, 10, BOARD_WALL); 

        setBoardValue(18, 10, BOARD_WALL); 
        setBoardValue(17, 10, BOARD_WALL); 
        setBoardValue(16, 10, BOARD_WALL); 
        setBoardValue(15, 10, BOARD_WALL); 
        setBoardValue(14, 10, BOARD_WALL); 
        setBoardValue(13, 10, BOARD_WALL); 
        setBoardValue(18, 9, BOARD_WALL); 
        setBoardValue(18, 8, BOARD_WALL); 
        setBoardValue(18, 7, BOARD_WALL); 
        setBoardValue(18, 6, BOARD_WALL); 
        setBoardValue(18, 5, BOARD_WALL); 
        
      }

      break;
        
    case 3:
       
      if (CELL_MAXIMUM_X == 48 && CELL_MAXIMUM_Y == 30) { // 480 x 360 @ 10 pixels
        
        setBoardValue(10, 10, BOARD_WALL); 
        setBoardValue(10, 11, BOARD_WALL); 
        setBoardValue(10, 12, BOARD_WALL); 
        setBoardValue(10, 13, BOARD_WALL); 
        setBoardValue(10, 14, BOARD_WALL); 
        setBoardValue(10, 15, BOARD_WALL); 
        setBoardValue(10, 16, BOARD_WALL); 
        setBoardValue(10, 17, BOARD_WALL); 
        setBoardValue(10, 18, BOARD_WALL); 
        setBoardValue(10, 19, BOARD_WALL); 
        setBoardValue(10, 20, BOARD_WALL); 
        setBoardValue(10, 21, BOARD_WALL); 
        setBoardValue(10, 22, BOARD_WALL); 

        setBoardValue(23, 10, BOARD_WALL); 
        setBoardValue(23, 11, BOARD_WALL); 
        setBoardValue(23, 12, BOARD_WALL); 
        setBoardValue(23, 13, BOARD_WALL); 
        setBoardValue(23, 14, BOARD_WALL); 
        setBoardValue(23, 15, BOARD_WALL); 
        setBoardValue(23, 16, BOARD_WALL); 
        setBoardValue(23, 17, BOARD_WALL); 
        setBoardValue(23, 18, BOARD_WALL); 
        setBoardValue(23, 19, BOARD_WALL); 
        setBoardValue(23, 20, BOARD_WALL); 
        setBoardValue(23, 21, BOARD_WALL); 
        setBoardValue(23, 22, BOARD_WALL); 

        setBoardValue(24, 10, BOARD_WALL); 
        setBoardValue(24, 11, BOARD_WALL); 
        setBoardValue(24, 12, BOARD_WALL); 
        setBoardValue(24, 13, BOARD_WALL); 
        setBoardValue(24, 14, BOARD_WALL); 
        setBoardValue(24, 15, BOARD_WALL); 
        setBoardValue(24, 16, BOARD_WALL); 
        setBoardValue(24, 17, BOARD_WALL); 
        setBoardValue(24, 18, BOARD_WALL); 
        setBoardValue(24, 19, BOARD_WALL); 
        setBoardValue(24, 20, BOARD_WALL); 
        setBoardValue(24, 21, BOARD_WALL); 
        setBoardValue(24, 22, BOARD_WALL); 

        setBoardValue(37, 22, BOARD_WALL); 
        setBoardValue(37, 21, BOARD_WALL); 
        setBoardValue(37, 20, BOARD_WALL); 
        setBoardValue(37, 19, BOARD_WALL); 
        setBoardValue(37, 18, BOARD_WALL); 
        setBoardValue(37, 17, BOARD_WALL); 
        setBoardValue(37, 16, BOARD_WALL); 
        setBoardValue(37, 15, BOARD_WALL); 
        setBoardValue(37, 14, BOARD_WALL); 
        setBoardValue(37, 13, BOARD_WALL); 
        setBoardValue(37, 12, BOARD_WALL); 
        setBoardValue(37, 11, BOARD_WALL); 
        setBoardValue(37, 10, BOARD_WALL); 

      }
       
      if (CELL_MAXIMUM_X == 30 && CELL_MAXIMUM_Y == 19) { // 480 x 360 @ 16 pixels
        
        setBoardValue(6, 5, BOARD_WALL); 
        setBoardValue(6, 6, BOARD_WALL); 
        setBoardValue(6, 7, BOARD_WALL); 
        setBoardValue(6, 8, BOARD_WALL); 
        setBoardValue(6, 9, BOARD_WALL); 
        setBoardValue(6, 10, BOARD_WALL); 
        setBoardValue(6, 11, BOARD_WALL); 
        setBoardValue(6, 12, BOARD_WALL); 
        setBoardValue(6, 13, BOARD_WALL); 
        setBoardValue(6, 14, BOARD_WALL); 
        
        setBoardValue(14, 5, BOARD_WALL); 
        setBoardValue(14, 6, BOARD_WALL); 
        setBoardValue(14, 7, BOARD_WALL); 
        setBoardValue(14, 8, BOARD_WALL); 
        setBoardValue(14, 9, BOARD_WALL); 
        setBoardValue(14, 10, BOARD_WALL); 
        setBoardValue(14, 11, BOARD_WALL); 
        setBoardValue(14, 12, BOARD_WALL); 
        setBoardValue(14, 13, BOARD_WALL); 
        setBoardValue(14, 14, BOARD_WALL); 
      
        setBoardValue(15, 5, BOARD_WALL); 
        setBoardValue(15, 6, BOARD_WALL); 
        setBoardValue(15, 7, BOARD_WALL); 
        setBoardValue(15, 8, BOARD_WALL); 
        setBoardValue(15, 9, BOARD_WALL); 
        setBoardValue(15, 10, BOARD_WALL); 
        setBoardValue(15, 11, BOARD_WALL); 
        setBoardValue(15, 12, BOARD_WALL); 
        setBoardValue(15, 13, BOARD_WALL); 
        setBoardValue(15, 14, BOARD_WALL); 

        setBoardValue(23, 5, BOARD_WALL); 
        setBoardValue(23, 6, BOARD_WALL); 
        setBoardValue(23, 7, BOARD_WALL); 
        setBoardValue(23, 8, BOARD_WALL); 
        setBoardValue(23, 9, BOARD_WALL); 
        setBoardValue(23, 10, BOARD_WALL); 
        setBoardValue(23, 11, BOARD_WALL); 
        setBoardValue(23, 12, BOARD_WALL); 
        setBoardValue(23, 13, BOARD_WALL); 
        setBoardValue(23, 14, BOARD_WALL); 
        
      }
       
      if (CELL_MAXIMUM_X == 24 && CELL_MAXIMUM_Y == 15) { // 480 x 360 @ 20 pixels
        
        setBoardValue(5, 5, BOARD_WALL); 
        setBoardValue(5, 6, BOARD_WALL); 
        setBoardValue(5, 7, BOARD_WALL); 
        setBoardValue(5, 8, BOARD_WALL); 
        setBoardValue(5, 9, BOARD_WALL); 
        setBoardValue(5, 10, BOARD_WALL); 

        setBoardValue(12, 10, BOARD_WALL); 
        setBoardValue(12, 9, BOARD_WALL); 
        setBoardValue(12, 8, BOARD_WALL); 
        setBoardValue(12, 7, BOARD_WALL); 
        setBoardValue(12, 6, BOARD_WALL); 
        setBoardValue(12, 5, BOARD_WALL); 

        setBoardValue(11, 10, BOARD_WALL); 
        setBoardValue(11, 9, BOARD_WALL); 
        setBoardValue(11, 8, BOARD_WALL); 
        setBoardValue(11, 7, BOARD_WALL); 
        setBoardValue(11, 6, BOARD_WALL); 
        setBoardValue(11, 5, BOARD_WALL); 

        setBoardValue(18, 10, BOARD_WALL); 
        setBoardValue(18, 9, BOARD_WALL); 
        setBoardValue(18, 8, BOARD_WALL); 
        setBoardValue(18, 7, BOARD_WALL); 
        setBoardValue(18, 6, BOARD_WALL); 
        setBoardValue(18, 5, BOARD_WALL); 
        
      }

      break;
        
    default:
       
      if (CELL_MAXIMUM_X == 48 && CELL_MAXIMUM_Y == 30) { // 480 x 360 @ 10 pixels
        
        setBoardValue(10, 10, BOARD_WALL); 
        setBoardValue(10, 11, BOARD_WALL); 
        setBoardValue(10, 12, BOARD_WALL); 
        setBoardValue(10, 13, BOARD_WALL); 
        setBoardValue(10, 14, BOARD_WALL); 
        setBoardValue(10, 15, BOARD_WALL); 
        setBoardValue(10, 16, BOARD_WALL); 
        setBoardValue(10, 17, BOARD_WALL); 
        setBoardValue(10, 18, BOARD_WALL); 
        setBoardValue(10, 19, BOARD_WALL); 
        setBoardValue(10, 20, BOARD_WALL); 
        setBoardValue(10, 21, BOARD_WALL); 
        setBoardValue(10, 22, BOARD_WALL); 

        setBoardValue(23, 10, BOARD_WALL); 
        setBoardValue(23, 11, BOARD_WALL); 
        setBoardValue(23, 12, BOARD_WALL); 
        setBoardValue(23, 13, BOARD_WALL); 
        setBoardValue(23, 14, BOARD_WALL); 
        setBoardValue(23, 15, BOARD_WALL); 
        setBoardValue(23, 16, BOARD_WALL); 
        setBoardValue(23, 17, BOARD_WALL); 
        setBoardValue(23, 18, BOARD_WALL); 
        setBoardValue(23, 19, BOARD_WALL); 
        setBoardValue(23, 20, BOARD_WALL); 
        setBoardValue(23, 21, BOARD_WALL); 
        setBoardValue(23, 22, BOARD_WALL); 

        setBoardValue(24, 10, BOARD_WALL); 
        setBoardValue(24, 11, BOARD_WALL); 
        setBoardValue(24, 12, BOARD_WALL); 
        setBoardValue(24, 13, BOARD_WALL); 
        setBoardValue(24, 14, BOARD_WALL); 
        setBoardValue(24, 15, BOARD_WALL); 
        setBoardValue(24, 16, BOARD_WALL); 
        setBoardValue(24, 17, BOARD_WALL); 
        setBoardValue(24, 18, BOARD_WALL); 
        setBoardValue(24, 19, BOARD_WALL); 
        setBoardValue(24, 20, BOARD_WALL); 
        setBoardValue(24, 21, BOARD_WALL); 
        setBoardValue(24, 22, BOARD_WALL); 

        setBoardValue(37, 22, BOARD_WALL); 
        setBoardValue(37, 21, BOARD_WALL); 
        setBoardValue(37, 20, BOARD_WALL); 
        setBoardValue(37, 19, BOARD_WALL); 
        setBoardValue(37, 18, BOARD_WALL); 
        setBoardValue(37, 17, BOARD_WALL); 
        setBoardValue(37, 16, BOARD_WALL); 
        setBoardValue(37, 15, BOARD_WALL); 
        setBoardValue(37, 14, BOARD_WALL); 
        setBoardValue(37, 13, BOARD_WALL); 
        setBoardValue(37, 12, BOARD_WALL); 
        setBoardValue(37, 11, BOARD_WALL); 
        setBoardValue(37, 10, BOARD_WALL); 

      }
       
      if (CELL_MAXIMUM_X == 30 && CELL_MAXIMUM_Y == 19) { // 480 x 360 @ 16 pixels
        
        setBoardValue(1, 7, BOARD_WALL); 
        setBoardValue(2, 7, BOARD_WALL); 
        setBoardValue(5, 7, BOARD_WALL); 
        setBoardValue(6, 7, BOARD_WALL); 
        setBoardValue(9, 7, BOARD_WALL); 
        setBoardValue(10, 7, BOARD_WALL); 
        setBoardValue(13, 7, BOARD_WALL); 
        setBoardValue(14, 7, BOARD_WALL); 
        setBoardValue(17, 7, BOARD_WALL); 
        setBoardValue(18, 7, BOARD_WALL); 
        setBoardValue(21, 7, BOARD_WALL); 
        setBoardValue(22, 7, BOARD_WALL); 
        setBoardValue(25, 7, BOARD_WALL); 
        setBoardValue(26, 7, BOARD_WALL); 
        setBoardValue(29, 7, BOARD_WALL); 
        
        setBoardValue(1, 8, BOARD_WALL); 
        setBoardValue(2, 8, BOARD_WALL); 
        setBoardValue(5, 8, BOARD_WALL); 
        setBoardValue(6, 8, BOARD_WALL); 
        setBoardValue(9, 8, BOARD_WALL); 
        setBoardValue(10, 8, BOARD_WALL); 
        setBoardValue(13, 8, BOARD_WALL); 
        setBoardValue(14, 8, BOARD_WALL); 
        setBoardValue(17, 8, BOARD_WALL); 
        setBoardValue(18, 8, BOARD_WALL); 
        setBoardValue(21, 8, BOARD_WALL); 
        setBoardValue(22, 8, BOARD_WALL); 
        setBoardValue(25, 8, BOARD_WALL); 
        setBoardValue(26, 8, BOARD_WALL); 
        setBoardValue(29, 8, BOARD_WALL); 
        
        setBoardValue(3, 11, BOARD_WALL); 
        setBoardValue(4, 11, BOARD_WALL); 
        setBoardValue(7, 11, BOARD_WALL); 
        setBoardValue(8, 11, BOARD_WALL); 
        setBoardValue(11, 11, BOARD_WALL); 
        setBoardValue(12, 11, BOARD_WALL); 
        setBoardValue(15, 11, BOARD_WALL); 
        setBoardValue(16, 11, BOARD_WALL); 
        setBoardValue(19, 11, BOARD_WALL); 
        setBoardValue(20, 11, BOARD_WALL); 
        setBoardValue(23, 11, BOARD_WALL); 
        setBoardValue(24, 11, BOARD_WALL); 
        setBoardValue(27, 11, BOARD_WALL); 
        setBoardValue(28, 11, BOARD_WALL); 
        
        setBoardValue(3, 12, BOARD_WALL); 
        setBoardValue(4, 12, BOARD_WALL); 
        setBoardValue(7, 12, BOARD_WALL); 
        setBoardValue(8, 12, BOARD_WALL); 
        setBoardValue(11, 12, BOARD_WALL); 
        setBoardValue(12, 12, BOARD_WALL); 
        setBoardValue(15, 12, BOARD_WALL); 
        setBoardValue(16, 12, BOARD_WALL); 
        setBoardValue(19, 12, BOARD_WALL); 
        setBoardValue(20, 12, BOARD_WALL); 
        setBoardValue(23, 12, BOARD_WALL); 
        setBoardValue(24, 12, BOARD_WALL); 
        setBoardValue(27, 12, BOARD_WALL); 
        setBoardValue(28, 12, BOARD_WALL); 
        
      }
       
      if (CELL_MAXIMUM_X == 24 && CELL_MAXIMUM_Y == 15) { // 480 x 360 @ 20 pixels
        
        setBoardValue(5, 5, BOARD_WALL); 
        setBoardValue(5, 6, BOARD_WALL); 
        setBoardValue(5, 7, BOARD_WALL); 
        setBoardValue(5, 8, BOARD_WALL); 
        setBoardValue(5, 9, BOARD_WALL); 
        setBoardValue(5, 10, BOARD_WALL); 

        setBoardValue(12, 10, BOARD_WALL); 
        setBoardValue(12, 9, BOARD_WALL); 
        setBoardValue(12, 8, BOARD_WALL); 
        setBoardValue(12, 7, BOARD_WALL); 
        setBoardValue(12, 6, BOARD_WALL); 
        setBoardValue(12, 5, BOARD_WALL); 

        setBoardValue(11, 10, BOARD_WALL); 
        setBoardValue(11, 9, BOARD_WALL); 
        setBoardValue(11, 8, BOARD_WALL); 
        setBoardValue(11, 7, BOARD_WALL); 
        setBoardValue(11, 6, BOARD_WALL); 
        setBoardValue(11, 5, BOARD_WALL); 

        setBoardValue(18, 10, BOARD_WALL); 
        setBoardValue(18, 9, BOARD_WALL); 
        setBoardValue(18, 8, BOARD_WALL); 
        setBoardValue(18, 7, BOARD_WALL); 
        setBoardValue(18, 6, BOARD_WALL); 
        setBoardValue(18, 5, BOARD_WALL); 
        
      }

      break;
      
  }
    
}

void drawScreen() {
  
  lcd.setEraseBackColour(SG_BLACK);
  lcd.erase();
 
  for (byte y=0; y < CELL_MAXIMUM_Y; y++) {
  
    for (byte x=0; x < CELL_MAXIMUM_X; x++) {
      
      if (getBoardValue(x, y) > 0) { drawItem(x, y, getBoardValue(x, y)); }  // Don't draw blacks as we have just cleared the screen ..
    
    }
    
  }

 
  int x = 53;
  int y = (CELL_MAXIMUM_Y * CELL_HEIGHT) + 3;
  
  lcd.drawLine(x + 6, y, x + 9, y, GREY4);
  lcd.drawLine(x + 5, y + 1, x + 8, y + 1, GREY4);
  lcd.putPixel(x + 5, y + 2, GREY4);
  lcd.drawLine(x + 2, y + 1, x + 3, y + 1, GREY2);
  lcd.drawLine(x + 1, y + 2, x + 4, y + 2, GREY2);
  lcd.drawLine(x + 6, y + 2, x + 7, y + 2, GREY2);
  lcd.drawLine(x, y + 3, x + 8, y + 3, GREY2);
  lcd.drawLine(x, y + 4, x + 8, y + 4, GREY2);
  lcd.drawLine(x, y + 5, x + 8, y + 5, GREY2);
  lcd.drawLine(x, y + 6, x + 8, y + 6, GREY2);
  lcd.drawLine(x, y + 7, x + 8, y + 7, GREY2);
  lcd.drawLine(x + 1, y + 8, x + 7, y + 8, GREY2);
  lcd.drawLine(x + 2, y + 9, x + 3, y + 9, GREY2);
  lcd.drawLine(x + 5, y + 9, x + 6, y + 9, GREY2);
  
  if (showScoreboard) { drawScoreBoard(); }

}

void drawScoreBoard() {

  lcd.setTextColour(GREY2);
  lcd.setTextSize(SG_FONT0);
  lcd.string(0, (CELL_MAXIMUM_Y * CELL_HEIGHT) + 3, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Level ", 0);
  itoa(level + 1, buf, 10);
  lcd.setTextColour(GREY4);
  lcd.drawRectangle(39, (CELL_MAXIMUM_Y * CELL_HEIGHT) + 3, 50, MAX_Y_LANDSCAPE, SG_BLACK, solidFill);
  lcd.string(39, (CELL_MAXIMUM_Y * CELL_HEIGHT) + 3, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);

  itoa(fruit, buf, 10);
  int index = (fruit < 10 ? 1 : 2);
  buf[index] =' '; index++;
  buf[index] ='o'; index++;
  buf[index] ='f'; index++;
  buf[index] =' '; index++;
  buf[index] ='2'; index++;
  buf[index] ='5'; index++;
  lcd.drawRectangle(73, (CELL_MAXIMUM_Y * CELL_HEIGHT) + 3, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, SG_BLACK, solidFill);
  lcd.string(73, (CELL_MAXIMUM_Y * CELL_HEIGHT) + 3, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);
  
}


void drawSnake() {
  
  for (byte x=0; x < length; x++) {

      lcd.drawCircle((getCoordX(snake[x]) * CELL_WIDTH) + CELL_WIDTH_HALF - 1,  (getCoordY(snake[x]) * CELL_HEIGHT) + CELL_HEIGHT_HALF - 1, CELL_RADIUS, SG_GREEN, solidFill); 
    
  }
  
}

void drawCountDown() {

    
  // Draw label ..
    
  lcd.setTextColour(GREY5);    
  lcd.setTextSize(SG_FONT1);
  lcd.drawRectangle(COUNTDOWN_LEVEL_LEFT, COUNTDOWN_TOP, COUNTDOWN_LEVEL_LEFT + COUNTDOWN_LEVEL_WIDTH, COUNTDOWN_TOP + COUNTDOWN_HEIGHT, GREY1, solidFill);  
  lcd.orientation(SG_PORTRAIT_LOW);
  lcd.string(COUNTDOWN_LABEL_X, COUNTDOWN_LABEL_Y, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Level", 0);
  itoa((level + 1), buf, 10);
  lcd.string(COUNTDOWN_COUNTL_X, COUNTDOWN_LABEL_Y, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, buf, 0);
  lcd.orientation(SG_LANDSCAPE_LEFT);

  lcd.setTextColour(SG_WHITE);
  lcd.setTextSize(SG_FONT7);

  for (byte x=3; x>=1; x--) {
  
    lcd.drawRectangle(COUNTDOWN_MAIN_LEFT, COUNTDOWN_TOP, COUNTDOWN_MAIN_LEFT + COUNTDOWN_MAIN_WIDTH, COUNTDOWN_TOP + COUNTDOWN_HEIGHT, GREY3, SG_FILL);
    itoa(x, buf, 10);
    lcd.string(COUNTDOWN_MAIN_LEFT + 67, COUNTDOWN_TOP + 40, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);
   
    delay(500);
    
  }

  lcd.drawRectangle(COUNTDOWN_MAIN_LEFT, COUNTDOWN_TOP, COUNTDOWN_MAIN_LEFT + COUNTDOWN_MAIN_WIDTH, COUNTDOWN_TOP + COUNTDOWN_HEIGHT, GREY3, SG_FILL);
  lcd.string(COUNTDOWN_MAIN_LEFT + 25, COUNTDOWN_TOP + 40, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "GO !", 0);
  delay(500);
  
  drawScreen();
  drawSnake();
  
}

int createItem(int itemType) {
  
  byte headX = getCoordX(snake[head]);
  byte headY = getCoordY(snake[head]);
    
  byte x = 0, y = 0;
  
  while(true) {
  
    x = random(CELL_MAXIMUM_X);  
    y = random(CELL_MAXIMUM_Y);  
    
    if ((x >= headX -1 && x <= headX + 1 && y >= headY -1 && y <= headY + 1) || getBoardValue(x, y) != 0) {
     
       // try again! 
    }
    else {

      boolean ok = true;
      
      for (int i=0; i<length; i++) {
                    
        if (getCoordX(snake[i]) == x && getCoordY(snake[i]) == y) {

          ok = false;
          break;
          
        }
        
      }
      
      if (ok) { break; }
      
    }
    
  }
  
  setBoardValue(x, y, itemType); 
  drawItem(x, y, itemType);
  
  return getCoords(x, y);
  
}

void drawItem(byte cellX, byte cellY, byte itemType) {
 
  int x = cellX * CELL_WIDTH;
  int y = cellY * CELL_HEIGHT;
  
  switch (itemType) {
    
    case BOARD_BLANK:
      lcd.drawRectangle(x, y, x + CELL_WIDTH - 1, y + CELL_HEIGHT - 1, SG_BLACK, solidFill);
      break;
        
    case BOARD_APPLE:
    
      switch (mode) {
        
        case MODE_10:
        
          lcd.drawLine(x + 6, y, x + 9, y, SG_GREEN);
          lcd.drawLine(x + 5, y + 1, x + 8, y + 1, SG_GREEN);
          lcd.putPixel(x + 5, y + 2, SG_GREEN);
          lcd.drawLine(x + 2, y + 1, x + 3, y + 1, SG_RED);
          lcd.drawLine(x + 1, y + 2, x + 4, y + 2, SG_RED);
          lcd.drawLine(x + 6, y + 2, x + 7, y + 2, SG_RED);
          lcd.drawLine(x, y + 3, x + 8, y + 3, SG_RED);
          lcd.drawLine(x, y + 4, x + 8, y + 4, SG_RED);
          lcd.drawLine(x, y + 5, x + 8, y + 5, SG_RED);
          lcd.drawLine(x, y + 6, x + 8, y + 6, SG_RED);
          lcd.drawLine(x, y + 7, x + 8, y + 7, SG_RED);
          lcd.drawLine(x + 1, y + 8, x + 7, y + 8, SG_RED);
          lcd.drawLine(x + 2, y + 9, x + 3, y + 9, SG_RED);
          lcd.drawLine(x + 5, y + 9, x + 6, y + 9, SG_RED);
          break;
  
        case MODE_16:
        
          lcd.drawLine(x + 10, y, x + 13, y, SG_GREEN);       
          lcd.drawLine(x + 9, y + 1, x + 15, y + 1, SG_GREEN);       
          lcd.drawLine(x + 8, y + 2, x + 14, y + 2, SG_GREEN);       
          lcd.drawLine(x + 8, y + 3, x + 9, y + 3, SG_GREEN);       
          lcd.drawLine(x + 4, y + 1, x + 4, y + 1, SG_RED);
          lcd.drawLine(x + 2, y + 2, x + 7, y + 2, SG_RED);
          lcd.drawLine(x + 1, y + 3, x + 7, y + 3, SG_RED);
          lcd.drawLine(x + 10, y + 3, x + 13, y + 3, SG_RED);
          lcd.drawLine(x + 1, y + 4, x + 13, y + 4, SG_RED);
          lcd.drawLine(x, y + 5, x + 14, y + 5, SG_RED);
          lcd.drawLine(x, y + 6, x + 14, y + 6, SG_RED);
          lcd.drawLine(x, y + 7, x + 14, y + 7, SG_RED);
          lcd.drawLine(x, y + 8, x + 14, y + 8, SG_RED);
          lcd.drawLine(x, y + 9, x + 14, y + 9, SG_RED);
          lcd.drawLine(x, y + 10, x + 14, y + 10, SG_RED);
          lcd.drawLine(x, y + 11, x + 14, y + 11, SG_RED);
          lcd.drawLine(x, y + 12, x + 14, y + 12, SG_RED);
          lcd.drawLine(x + 1, y + 13, x + 13, y + 13, SG_RED);
          lcd.drawLine(x + 2, y + 14, x + 12, y + 14, SG_RED);
          lcd.drawLine(x + 4, y + 15, x + 6, y + 15, SG_RED);
          lcd.drawLine(x + 8, y + 15, x + 10, y + 15, SG_RED);
          break;
         
        case MODE_20:
        
          lcd.drawLine(x + 12, y, x + 16, y, SG_GREEN);       
          lcd.drawLine(x + 10, y + 1, x + 19, y + 1, SG_GREEN);       
          lcd.drawLine(x + 9, y + 2, x + 18, y + 2, SG_GREEN);       
          lcd.drawLine(x + 9, y + 3, x + 9, y + 3, SG_GREEN);       
          lcd.drawLine(x + 11, y + 3, x + 16, y + 3, SG_GREEN);       
          lcd.drawLine(x + 12, y + 4, x + 14, y + 4, SG_GREEN);       
          lcd.drawLine(x + 3, y + 3, x + 7, y + 3, SG_RED);
          lcd.drawLine(x + 10, y + 3, x + 10, y + 3, SG_RED);
          lcd.drawLine(x + 2, y + 4, x + 11, y + 4, SG_RED);
          lcd.drawLine(x + 15, y + 4, x + 16, y + 4, SG_RED);
          lcd.drawLine(x + 1, y + 5, x + 17, y + 5, SG_RED);
          lcd.drawLine(x, y + 6, x + 18, y + 6, SG_RED);
          lcd.drawLine(x, y + 7, x + 18, y + 7, SG_RED);
          lcd.drawLine(x, y + 8, x + 18, y + 8, SG_RED);
          lcd.drawLine(x, y + 9, x + 18, y + 9, SG_RED);
          lcd.drawLine(x, y + 10, x + 18, y + 10, SG_RED);
          lcd.drawLine(x, y + 11, x + 18, y + 11, SG_RED);
          lcd.drawLine(x, y + 12, x + 18, y + 12, SG_RED);
          lcd.drawLine(x, y + 13, x + 18, y + 13, SG_RED);
          lcd.drawLine(x, y + 14, x + 18, y + 14, SG_RED);
          lcd.drawLine(x + 1, y + 15, x + 17, y + 15, SG_RED);
          lcd.drawLine(x + 1, y + 16, x + 17, y + 16, SG_RED);
          lcd.drawLine(x + 2, y + 17, x + 16, y + 17, SG_RED);
          lcd.drawLine(x + 3, y + 18, x + 15, y + 18, SG_RED);
          lcd.drawLine(x + 4, y + 19, x + 8, y + 19, SG_RED);
          lcd.drawLine(x + 11, y + 19, x + 14, y + 19, SG_RED);
          break;
        
      }
      break; 
  
    case BOARD_BOMB:
       
      switch (mode) {
        
        case MODE_10:
 
          lcd.drawLine(x + 9, y, x + 7, y + 2, SG_RED);
          lcd.drawLine(x + 7, y, x + 7, y + 1, SG_YELLOW);
          lcd.drawLine(x + 8, y + 2, x + 9, y + 2, SG_YELLOW);
          lcd.drawRectangle(x + 2, y + 2, x + 5, y + 9, 0x528a, solidFill);
          lcd.drawRectangle(x, y + 4, x + 7, y + 7, 0x528a, solidFill);
          lcd.drawRectangle(x + 1, y + 3, x + 6, y + 8, 0x528a, solidFill);
          break;
          
        case MODE_16:
          lcd.drawLine(x + 13, y + 2, x + 15, y, SG_RED);
          lcd.drawLine(x + 12, y, x + 12, y + 1, SG_YELLOW);
          lcd.drawLine(x + 14, y + 3, x + 15, y + 3, SG_YELLOW);
          lcd.drawRectangle(x + 5, y + 2, x + 8, y + 15, 0x528a, solidFill);
          lcd.drawRectangle(x + 3, y + 3, x + 10, y + 14, 0x528a, solidFill);
          lcd.drawRectangle(x + 2, y + 4, x + 11, y + 13, 0x528a, solidFill);
          lcd.drawRectangle(x + 1, y + 5, x + 12, y + 12, 0x528a, solidFill);
          lcd.drawRectangle(x, y + 7, x + 13, y + 10, 0x528a, solidFill);
          lcd.drawRectangle(x + 12, y + 2, x + 12, y + 4, 0x8410, solidFill);
          lcd.drawRectangle(x + 11, y + 3, x + 13, y + 3, 0x8410, solidFill);
          break;
          
        case MODE_20:
          lcd.drawLine(x + 17, y + 2, x + 19, y, SG_RED);
          lcd.drawLine(x + 16, y, x + 16, y + 1, SG_YELLOW);
          lcd.drawLine(x + 18, y + 3, x + 19, y + 3, SG_YELLOW);
          lcd.drawRectangle(x + 5, y + 3, x + 11, y + 19, 0x528a, solidFill);
          lcd.drawRectangle(x + 3, y + 4, x + 13, y + 18, 0x528a, solidFill);
          lcd.drawRectangle(x + 2, y + 5, x + 14, y + 17, 0x528a, solidFill);
          lcd.drawRectangle(x + 1, y + 6, x + 15, y + 16, 0x528a, solidFill);
          lcd.drawRectangle(x, y + 8, x + 16, y + 14, 0x528a, solidFill);
          lcd.drawRectangle(x + 16, y + 2, x + 14, y + 4, 0x8410, solidFill);
          lcd.drawRectangle(x + 17, y + 3, x + 15, y + 5, 0x8410, solidFill);
          break;
          
      }
      
      break; 
  
    case BOARD_WALL:
           
      switch (mode) {
        
        case MODE_10:
 
          lcd.drawRectangle(x, y, x + 9, y + 9, DARK_RED, solidFill);
          lcd.drawLine(x, y + 4, x + 9, y + 4, GREY5);
          lcd.drawLine(x, y + 9, x + 9, y + 9, GREY5);
          lcd.drawLine(x + 2, y, x + 2, y + 4, GREY5);
          lcd.drawLine(x + 7, y + 4, x + 7, y + 9, GREY5);
          break; 
        
        case MODE_16:
 
          lcd.drawRectangle(x, y, x + 15, y + 15, DARK_RED, solidFill);
          lcd.drawLine(x, y + 7, x + 15, y + 7, GREY5);
          lcd.drawLine(x, y + 15, x + 15, y + 15, GREY5);
          lcd.drawLine(x + 4, y, x + 4, y + 7, GREY5);
          lcd.drawLine(x + 11, y + 7, x + 11, y + 15, GREY5);
          break; 
        
        case MODE_20:
 
          lcd.drawRectangle(x, y, x + 19, y + 19, DARK_RED, solidFill);
          lcd.drawLine(x, y + 9, x + 19, y + 9, GREY5);
          lcd.drawLine(x, y + 19, x + 19, y + 19, GREY5);
          lcd.drawLine(x + 5, y, x + 5, y + 9, GREY5);
          lcd.drawLine(x + 13, y + 9, x + 13, y + 19, GREY5);
          break; 
      
      }
      
      break;
      
  }
  
}


void drawMessage(byte icon) {
  
  byte index = 0;
  lcd.setTextSize(SG_FONT2);
  lcd.SDFopenDir("snake");
  SG_RADIUS radius6 = 6;
  SG_RADIUS radius5 = 5;
  
  lcd.drawRoundRect(MESSAGE_BOX_LEFT, MESSAGE_BOX_TOP, MESSAGE_BOX_LEFT + MESSAGE_BOX_WIDTH, MESSAGE_BOX_TOP + MESSAGE_BOX_HEIGHT, radius6, SG_WHITE, solidFill);
  lcd.drawRoundRect(MESSAGE_BOX_LEFT, MESSAGE_BOX_TOP, MESSAGE_BOX_LEFT + MESSAGE_BOX_WIDTH, MESSAGE_BOX_TOP + MESSAGE_BOX_HEIGHT, radius6, GREY6, hollowFill);
  lcd.drawRoundRect(MESSAGE_BOX_LEFT + 1, MESSAGE_BOX_TOP + 1, MESSAGE_BOX_LEFT + MESSAGE_BOX_WIDTH - 1, MESSAGE_BOX_TOP + MESSAGE_BOX_HEIGHT - 1, radius5, GREY5, hollowFill);
  
  switch (icon) {
    
    case BOARD_APPLE:
      lcd.imageJPGSD(MESSAGE_BOX_LEFT + 10, MESSAGE_BOX_TOP + 10, SG_SCALE1_1, "apple");
      lcd.setTextSize(SG_FONT3);
      lcd.setTextColour(DARK_RED);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 20, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "N", 0);
      lcd.string(MESSAGE_BOX_LEFT + 105, MESSAGE_BOX_TOP + 25, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "I", 0);
      lcd.string(MESSAGE_BOX_LEFT + 112, MESSAGE_BOX_TOP + 18, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "C", 0);
      lcd.string(MESSAGE_BOX_LEFT + 132, MESSAGE_BOX_TOP + 25, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "E", 0);
      lcd.string(MESSAGE_BOX_LEFT + 143, MESSAGE_BOX_TOP + 20, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, " ", 0);
      lcd.string(MESSAGE_BOX_LEFT + 158, MESSAGE_BOX_TOP + 20, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "W", 0);
      lcd.string(MESSAGE_BOX_LEFT + 178, MESSAGE_BOX_TOP + 23, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "O", 0);
      lcd.string(MESSAGE_BOX_LEFT + 198, MESSAGE_BOX_TOP + 18, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "R", 0);
      lcd.string(MESSAGE_BOX_LEFT + 216, MESSAGE_BOX_TOP + 26, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "K", 0);
      lcd.string(MESSAGE_BOX_LEFT + 233, MESSAGE_BOX_TOP + 22, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "!", 0);
      lcd.setTextSize(SG_FONT2);
      lcd.setTextColour(GREY3);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 59, MESSAGE_BOX_LEFT + MESSAGE_BOX_WIDTH - 10, MAX_Y_LANDSCAPE, "You have cleared this level .. the next level is going to be even harder!", 0);
      break;
    
    case BOARD_BOMB:
      lcd.imageJPGSD(MESSAGE_BOX_LEFT + 10, MESSAGE_BOX_TOP + 10, SG_SCALE1_1, "bomb");
      lcd.setTextSize(SG_FONT4);
      lcd.setTextColour(DARK_RED);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 16, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "B", 0);
      lcd.string(MESSAGE_BOX_LEFT + 104, MESSAGE_BOX_TOP + 20, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "O", 0);
      lcd.string(MESSAGE_BOX_LEFT + 127, MESSAGE_BOX_TOP + 14, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "O", 0);
      lcd.string(MESSAGE_BOX_LEFT + 151, MESSAGE_BOX_TOP + 21, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "M", 0);
      lcd.string(MESSAGE_BOX_LEFT + 176, MESSAGE_BOX_TOP + 16, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "!", 0);
      lcd.setTextSize(SG_FONT2);
      lcd.setTextColour(GREY3);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 55, MESSAGE_BOX_LEFT + MESSAGE_BOX_WIDTH - 10, MAX_Y_LANDSCAPE, "You stepped on a bomb .. game over. Try again to see if you can do better.", 0);
      lcd.imageJPGSD(MESSAGE_BOX_LEFT + 82, MESSAGE_BOX_TOP + 144, SG_SCALE1_2, "apple");
      itoa(fruit, buf, 10);
      
      index = (fruit < 10 ? 1 : 2);
      buf[index] =' '; index++;
      buf[index] ='e'; index++;
      buf[index] ='a'; index++;
      buf[index] ='t'; index++;
      buf[index] ='e'; index++;
      buf[index] ='n'; index++;
      buf[index] ='.'; index++;
      lcd.string(MESSAGE_BOX_LEFT + 118, MESSAGE_BOX_TOP + 151, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);

      break;
    
    case BOARD_WALL:
      lcd.imageJPGSD(MESSAGE_BOX_LEFT + 10, MESSAGE_BOX_TOP + 10, SG_SCALE1_1, "wall");
      lcd.setTextSize(SG_FONT4);
      lcd.setTextColour(DARK_RED);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 16, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "B", 0);
      lcd.string(MESSAGE_BOX_LEFT + 104, MESSAGE_BOX_TOP + 20, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "A", 0);
      lcd.string(MESSAGE_BOX_LEFT + 127, MESSAGE_BOX_TOP + 14, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "M", 0);
      lcd.string(MESSAGE_BOX_LEFT + 153, MESSAGE_BOX_TOP + 19, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "!", 0);
      lcd.setTextSize(SG_FONT2);
      lcd.setTextColour(GREY3);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 55, MESSAGE_BOX_LEFT + MESSAGE_BOX_WIDTH - 10, MAX_Y_LANDSCAPE, "You hit the wall .. game over. Try again to see if you can do better.", 0);
      lcd.imageJPGSD(MESSAGE_BOX_LEFT + 82, MESSAGE_BOX_TOP + 144, SG_SCALE1_2, "apple");
      itoa(fruit, buf, 10);
      
      index = (fruit < 10 ? 1 : 2);
      buf[index] =' '; index++;
      buf[index] ='e'; index++;
      buf[index] ='a'; index++;
      buf[index] ='t'; index++;
      buf[index] ='e'; index++;
      buf[index] ='n'; index++;
      buf[index] ='.'; index++;
      lcd.string(MESSAGE_BOX_LEFT + 118, MESSAGE_BOX_TOP + 151, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);

      break;
   
    case BOARD_SNAKE:
      lcd.imageJPGSD(MESSAGE_BOX_LEFT + 10, MESSAGE_BOX_TOP + 10, SG_SCALE1_1, "snake");
      lcd.setTextSize(SG_FONT4);
      lcd.setTextColour(DARK_RED);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 16, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "O", 0);
      lcd.string(MESSAGE_BOX_LEFT + 110, MESSAGE_BOX_TOP + 20, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "U", 0);
      lcd.string(MESSAGE_BOX_LEFT + 131, MESSAGE_BOX_TOP + 14, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "C", 0);
      lcd.string(MESSAGE_BOX_LEFT + 156, MESSAGE_BOX_TOP + 19, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "H", 0);
      lcd.string(MESSAGE_BOX_LEFT + 180, MESSAGE_BOX_TOP + 15, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "!", 0);
      lcd.setTextSize(SG_FONT2);
      lcd.setTextColour(GREY3);
      lcd.string(MESSAGE_BOX_LEFT + 85, MESSAGE_BOX_TOP + 55, MESSAGE_BOX_LEFT + MESSAGE_BOX_WIDTH - 10, MAX_Y_LANDSCAPE, "You bit yourself .. game over. Try again to see if you can do better.", 0);
      lcd.imageJPGSD(MESSAGE_BOX_LEFT + 82, MESSAGE_BOX_TOP + 144, SG_SCALE1_2, "apple");
      itoa(fruit, buf, 10);
      
      index = (fruit < 10 ? 1 : 2);
      buf[index] =' '; index++;
      buf[index] ='e'; index++;
      buf[index] ='a'; index++;
      buf[index] ='t'; index++;
      buf[index] ='e'; index++;
      buf[index] ='n'; index++;
      buf[index] ='.'; index++;
      lcd.string(MESSAGE_BOX_LEFT + 118, MESSAGE_BOX_TOP + 151, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);

      break;

  }      


#ifdef USE_TOUCHSCREEN
 
   while (!lcd.touchScreen(&point)) {

     delay(100);
     
   }
     
#endif 

#ifdef USE_JOYSTICK
  
  do {  
    
    while (analogRead(joyButton) > 0) {   
  
      delay(100); 
    
    }
  
    delay(100); 
      
  }
  while (analogRead(joyButton) > 0);
  
#endif

#ifdef USE_ACCELEROMETER

  /* Accelerometer ..
  while (true) {
    
    delay(100);
    
    byte interrupts = adxl.getInterruptSource();  
    
    if (adxl.triggered(interrupts, ADXL345_SINGLE_TAP)) {
      
      break; 
      
    }
    
  } */
  
  while (!lcd.touchScreen(&point)) {

    delay(100);
     
  }

 
#endif

}
