#include <SMARTGPU2.h>   

#define SCREEN_OPTIONS 0
#define SCREEN_PLAY 1

#define PENCIL_LABEL_LEFT 348
#define PENCIL_LABEL_TOP 0
#define PENCIL_LABEL_HEIGHT 102
#define PENCIL_LABEL_WIDTH 22
#define PENCIL_LEFT 377
#define PENCIL_TOP 0

#define PEN_LABEL_LEFT 348
#define PEN_LABEL_TOP 120
#define PEN_LABEL_HEIGHT 102
#define PEN_LABEL_WIDTH 22
#define PEN_LEFT 377
#define PEN_TOP 120

#define PENCIL_ERROR_TOP 275
#define PENCIL_ERROR_LEFT 340
#define PEN_ERROR_TOP 298
#define PEN_ERROR_LEFT 340

#define CELL_SELECTED_VALUE 0
#define CELL_SPACING 35
#define CELL_WIDTH 32
#define CHECK_WIDTH 18
#define CHECK_HEIGHT 18
#define CHECK_LABEL_SPACING 17
#define CHECK_OUTER_RADIUS 4
#define CHECK_INNER_RADIUS 2
#define CHECK_INSET 3

#define COMMAND_SAVE_LEFT 344
#define COMMAND_SAVE_TOP 25
#define COMMAND_SAVE_WIDTH 135
#define COMMAND_SAVE_HEIGHT 32

#define COMMAND_RESTORE_LEFT 344
#define COMMAND_RESTORE_TOP 65
#define COMMAND_RESTORE_WIDTH 135
#define COMMAND_RESTORE_HEIGHT 32

#define COMMAND_PLAY_LEFT 344
#define COMMAND_PLAY_TOP 105
#define COMMAND_PLAY_WIDTH 135
#define COMMAND_PLAY_HEIGHT 32

#define COMMAND_MENU_LEFT 377
#define COMMAND_MENU_TOP 280
#define COMMAND_MENU_WIDTH 102
#define COMMAND_MENU_HEIGHT 32

#define TAB_EASY 0
#define TAB_EASY_LEFT 0
#define TAB_EASY_TOP 0
#define TAB_EASY_WIDTH 90
#define TAB_EASY_HEIGHT 25

#define TAB_MEDIUM 1
#define TAB_MEDIUM_LEFT 90
#define TAB_MEDIUM_TOP 0
#define TAB_MEDIUM_WIDTH 90
#define TAB_MEDIUM_HEIGHT 25

#define TAB_HARD 2
#define TAB_HARD_LEFT 180
#define TAB_HARD_TOP 0
#define TAB_HARD_WIDTH 90
#define TAB_HARD_HEIGHT 25

#define TAB_LEFT 0
#define TAB_TOP 25
#define TAB_WIDTH 330
#define TAB_HEIGHT 294

#define COLOUR_DARKGREY 4
#define COLOUR_LIGHTGREY 12
#define COLOUR_DARKBLUE 0x10e6
#define COLOUR_LIGHTBLUE 0x01ec
#define COLOUR_GRID_LOWLIGHT 0x10e6// 0x31e6//1100
#define COLOUR_GRID_HIGHLIGHT 0x01ec//2700
#define COLOUR_GRID_SELECTED 0x01F3//2700
#define GRID_ROW_HEIGHT 30
  
#define GREY1 0x2104
#define GREY2 0x3186
#define GREY3 0x528A
#define GREY4 0x630C
#define GREY5 0x8410
#define GREY6 0xA514
#define GREY7 0xB596
#define GREY8 0xC618
#define GREY9 0xE71C

#define TAB_PAGE_TEXT_LEFT 290
#define TAB_PAGE_TEXT_TOP 298

#define TAB_PAGE_PREV_LEFT 264
#define TAB_PAGE_PREV_TOP 296
#define TAB_PAGE_PREV_WIDTH 18
#define TAB_PAGE_PREV_HEIGHT 18

#define TAB_PAGE_NEXT_LEFT 304
#define TAB_PAGE_NEXT_TOP 296
#define TAB_PAGE_NEXT_WIDTH 18
#define TAB_PAGE_NEXT_HEIGHT 18
#define TAB_ROWS_TOP 35

PROGMEM const int RECORD_LENGTH = 102;
PROGMEM const int RECORD_DESC_START = 0;
PROGMEM const int RECORD_DESC_LENGTH = 20;
PROGMEM const int RECORD_SOLUTION_START = 20;
PROGMEM const int RECORD_SOLUTION_LENGTH = 81;
PROGMEM const int TAB_ENTRIES_PER_PAGE = 8;

PROGMEM const int DIALOG_RESULT_OK = 0;
PROGMEM const int DIALOG_RESULT_CANCEL = 1;
PROGMEM const int DIALOG_BUTTONS_OKCANCEL = 0;
PROGMEM const int DIALOG_BUTTONS_OKONLY = 1;

PROGMEM const int DIALOG_LEFT = 100;
PROGMEM const int DIALOG_TOP = 70;
PROGMEM const int DIALOG_WIDTH = 280;
PROGMEM const int DIALOG_HEIGHT = 180;
PROGMEM const int DIALOG_BUTTON_TOP = 130;
PROGMEM const int DIALOG_BUTTON_WIDTH = 85;
PROGMEM const int DIALOG_BUTTON_HEIGHT = 35;
PROGMEM const int DIALOG_BUTTON_RADIUS = 5;
PROGMEM const int DIALOG_1BUTTONS_LEFT = 97;
PROGMEM const int DIALOG_2BUTTONS_BUTTON1_LEFT = 50;
PROGMEM const int DIALOG_2BUTTONS_BUTTON2_LEFT = 145;
PROGMEM const int DIALOG_MESSAGE_LEFT = 40;
PROGMEM const int DIALOG_MESSAGE_WIDTH = 200;
PROGMEM const int DIALOG_MESSAGE_TOP = 50;
PROGMEM const int DIALOG_BUTTON_CANCEL_LEFT = 248; 
PROGMEM const int DIALOG_BUTTON_CANCEL_TOP = 3; 
PROGMEM const int DIALOG_BUTTON_CANCEL_WIDTH = 23; 
PROGMEM const int DIALOG_BUTTON_CANCEL_HEIGHT = 16; 

                                         //12345678901234567890123456789012345678901234567890
//PROGMEM char DIALOG_MESSAGE_LOAD_GAME[] = "Quit current game and load the selected game ?";
//PROGMEM char DIALOG_TITLE_LOAD_GAME[] = "Load Game";
//PROGMEM char DIALOG_MESSAGE_RESTORE_GAME[] = "Quit current game and restore to previously saved version ?";
//PROGMEM char DIALOG_TITLE_RESTORE_GAME[] = "Restore Game";
//PROGMEM char DIALOG_MESSAGE_SAVE_GAME[] = "Game successfully saved.";
//PROGMEM char DIALOG_TITLE_SAVE_GAME[] = "Save Game";

FILERESULT res;            //create the variable that will store all SMARTGPU2 commands responses
 
SMARTGPU2 lcd;           

AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution
AXIS MAX_X_PORTRAIT, MAX_Y_PORTRAIT, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE;

char solution[9][9];
char board[9][9][10];
//char saveLoadData[81];
char selectedCellX = -1;
char selectedCellY = -1;
char selectedScreen = SCREEN_OPTIONS;
char selectedTab = TAB_EASY;
char selectedTab_Page = 0;
char selectedTab_Count = 0;
char selectedTab_Count_This_Page = 0;
char buf[2];
char buffer[RECORD_LENGTH]={0};
char* filename = "";           
boolean gameSaved0 = false;
boolean gameSaved1 = false;

RADIUS radius5 = 5;  

FILLGEOM solidFill=(FILLGEOM)1;
FILLGEOM hollowFill=(FILLGEOM)0;

boolean showPencilInError = true;
boolean showPenInError = true;

POINT point;

void setup() { 

  lcd.init();  
  lcd.start(); 
  lcd.baudChange(BAUD6);      

  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);

  MAX_X_PORTRAIT = LCD_HEIGHT-1;
  MAX_Y_PORTRAIT = LCD_WIDTH-1;
  MAX_X_LANDSCAPE= LCD_WIDTH-1;
  MAX_Y_LANDSCAPE= LCD_HEIGHT-1;

  gameSaved0 = isGameSaved(PAGE0);
  gameSaved1 = isGameSaved(PAGE1);
  
  if (!gameSaved1) {
    
    populateSolution(0, -3,-5,-8, 1,-2,-6, 9, 7, 4);
    populateSolution(1, -4, 6,-7,-3, 9, 8, 5, 2,-1);
    populateSolution(2, -9, 1, 2,-4, 7,-5,-6,-8,-3);
    populateSolution(3, -2,-9,-6,-7, 4, 3,-1,-5, 8);
    populateSolution(4,  1,-7, 5,-2,-8,-9, 4,-3, 6);
    populateSolution(5,  8,-4,-3, 5, 6,-1,-2,-9,-7);
    populateSolution(6,  5,-2,-1,-8, 3,-4, 7, 6,-9);
    populateSolution(7, -6, 3, 4, 9, 5,-7,-8, 1,-2);
    populateSolution(8,  7, 8, 9,-6, 1, 2,-3,-4,-5);

    initBoard();
  
  }
  else {
    
    restoreGame(PAGE1);
    selectedScreen = SCREEN_PLAY;
    
  }
  
  drawScreen();
  
}

void loop() {
  
  if (lcd.touchScreen(&point)) {

    if (selectedScreen == SCREEN_OPTIONS) {
      
      process_ScreenOptions();
   
    }
    else {
      
      process_ScreenPlay();
      
    }
   
  }
  
  delay(50);
 
}


void process_ScreenOptions() {

  char row = (point.x > 10 && point.x < 320 && ((point.y - 35) <= (TAB_ENTRIES_PER_PAGE * GRID_ROW_HEIGHT)) && (((point.y - 35) / GRID_ROW_HEIGHT) + 1) <= selectedTab_Count_This_Page ? (point.y - 35) / GRID_ROW_HEIGHT : -1);
  
  
  // If the pencil checkbox has been selected ..
  
  if (point.x >= PENCIL_ERROR_LEFT && point.x < PENCIL_ERROR_LEFT + CHECK_WIDTH && point.y >= PENCIL_ERROR_TOP && point.y < PENCIL_ERROR_TOP + CHECK_HEIGHT) {

    lcd.drawRoundRect(PENCIL_ERROR_LEFT + CHECK_INSET, PENCIL_ERROR_TOP + CHECK_INSET, PENCIL_ERROR_LEFT + CHECK_WIDTH - CHECK_INSET, PENCIL_ERROR_TOP + CHECK_HEIGHT - CHECK_INSET, CHECK_INNER_RADIUS, (showPencilInError ? BLACK : COLOUR_DARKBLUE), solidFill);  
    showPencilInError = !showPencilInError;

  }
  
  
  // If the pen checkbox has been selected ..
  
  if (point.x >= PEN_ERROR_LEFT && point.x < PEN_ERROR_LEFT + CHECK_WIDTH && point.y >= PEN_ERROR_TOP && point.y < PEN_ERROR_TOP + CHECK_HEIGHT) {

    lcd.drawRoundRect(PEN_ERROR_LEFT + CHECK_INSET, PEN_ERROR_TOP + CHECK_INSET, PEN_ERROR_LEFT + CHECK_WIDTH - CHECK_INSET, PEN_ERROR_TOP + CHECK_HEIGHT - CHECK_INSET, CHECK_INNER_RADIUS, (showPenInError ? BLACK : COLOUR_DARKBLUE), solidFill);  
    showPenInError = !showPenInError;

  }
  
  
  // Save the game ?
  
  if (point.x >= COMMAND_SAVE_LEFT && point.x < COMMAND_SAVE_LEFT + COMMAND_SAVE_WIDTH && point.y >= COMMAND_SAVE_TOP && point.y < COMMAND_SAVE_TOP + COMMAND_SAVE_HEIGHT) {
   
    saveGame(PAGE0);
    gameSaved0 = true;
    showDialog("Save Game", "Game successfully saved.", DIALOG_BUTTONS_OKONLY);
    drawScreen();    

  }
  
  
  // Restore the game ?
  
  if (point.x >= COMMAND_RESTORE_LEFT && point.x < COMMAND_RESTORE_LEFT + COMMAND_RESTORE_WIDTH && point.y >= COMMAND_RESTORE_TOP && point.y < COMMAND_RESTORE_TOP + COMMAND_RESTORE_HEIGHT && gameSaved0) {
    
    if (showDialog("Restore Game", "Quit current game and restore to previously saved version ?", DIALOG_BUTTONS_OKCANCEL) == DIALOG_RESULT_OK) {
    
      restoreGame(PAGE0);
      selectedCellX = -1;
      selectedCellY = -1;
      selectedScreen = SCREEN_PLAY;
      
    }

    drawScreen();    
    
  }

  
  // Play the game ?
  
  if (point.x >= COMMAND_PLAY_LEFT && point.x < COMMAND_PLAY_LEFT + COMMAND_PLAY_WIDTH && point.y >= COMMAND_PLAY_TOP && point.y < COMMAND_PLAY_TOP + COMMAND_PLAY_HEIGHT) {
    
    selectedScreen = SCREEN_PLAY;
    drawScreen();
    
  }

  
  // Change the tab ?
  
  if ((point.x >= TAB_EASY_LEFT && point.x < TAB_EASY_LEFT + TAB_EASY_WIDTH && point.y >= TAB_EASY_TOP && point.y < TAB_EASY_TOP + TAB_EASY_HEIGHT) && selectedTab != TAB_EASY) {
    
    selectedTab = TAB_EASY;
    selectedTab_Page = 0;
    drawTab();
    
  }
  
  if ((point.x >= TAB_MEDIUM_LEFT && point.x < TAB_MEDIUM_LEFT + TAB_MEDIUM_WIDTH && point.y >= TAB_MEDIUM_TOP && point.y < TAB_MEDIUM_TOP + TAB_MEDIUM_HEIGHT) && selectedTab != TAB_MEDIUM) {
    
    selectedTab = TAB_MEDIUM;
    selectedTab_Page = 0;
    drawTab();
    
  }
  
  if ((point.x >= TAB_HARD_LEFT && point.x < TAB_HARD_LEFT + TAB_HARD_WIDTH && point.y >= TAB_HARD_TOP && point.y < TAB_HARD_TOP + TAB_HARD_HEIGHT) && selectedTab != TAB_HARD) {
    
    selectedTab = TAB_HARD;
    selectedTab_Page = 0;
    drawTab();
    
  }
  
  
  // Page through results ?
  
  if ((point.x >= TAB_PAGE_PREV_LEFT && point.x < TAB_PAGE_PREV_LEFT + TAB_PAGE_PREV_WIDTH && point.y >= TAB_PAGE_PREV_TOP && point.y < TAB_PAGE_PREV_TOP + TAB_PAGE_PREV_HEIGHT) && selectedTab_Page > 0) {
    
    selectedTab_Page--;
    drawTab();
    
  }
  
  if ((point.x >= TAB_PAGE_NEXT_LEFT && point.x < TAB_PAGE_NEXT_LEFT + TAB_PAGE_NEXT_WIDTH && point.y >= TAB_PAGE_NEXT_TOP && point.y < TAB_PAGE_NEXT_TOP + TAB_PAGE_NEXT_HEIGHT) && selectedTab_Page < selectedTab_Count) {
    
    selectedTab_Page++;
    drawTab();
    
  }
 
 
  // Load selected game ?
  
  if (row >= 0) {
    
    if (showDialog("Load Game", "Quit current game and load the selected game?", DIALOG_BUTTONS_OKCANCEL) == DIALOG_RESULT_OK) {

      loadGame(row);
      selectedScreen = SCREEN_PLAY;
      selectedCellX = -1;
      selectedCellY = -1;
      
    }
    
    drawScreen();
    
  }
 
}

void process_ScreenPlay() {
    
  char selectedX = -1, selectedY = -1, pencilX = -1, pencilY = -1, penX = -1, penY = -1;
  
  selectedX = (point.x < (9 * CELL_SPACING) ? point.x / CELL_SPACING : -1);
  selectedY = (point.y < (9 * CELL_SPACING) ? point.y / CELL_SPACING : -1);
  pencilX = (point.x >= PENCIL_LEFT && point.x < PENCIL_LEFT + (3 * CELL_SPACING) ? (point.x - PENCIL_LEFT) / CELL_SPACING : -1);
  pencilY = (point.y >= PENCIL_TOP && point.y < PENCIL_TOP + (3 * CELL_SPACING) ? (point.y - PENCIL_TOP) / CELL_SPACING : -1);
  penX = (point.x >= PEN_LEFT && point.x < PEN_LEFT + (3 * CELL_SPACING) ? (point.x - PEN_LEFT) / CELL_SPACING : -1);
  penY = (point.y >= PEN_TOP && point.y < PEN_TOP + (3 * CELL_SPACING) ? (point.y - PEN_TOP) / CELL_SPACING : -1);


  // Deselect previous main cell ..
  
  if (selectedCellX >= 0 && selectedCellY >= 0) {
  
    drawCell(selectedCellX, selectedCellY, false);
  
  }
  
  
  // Select new main cell ..
  
  if (selectedX >= 0 && selectedY >= 0 && solution[selectedX][selectedY] < 0) {
  
    selectedCellX = selectedX;
    selectedCellY = selectedY;
    drawCell(selectedX, selectedY, true);
    drawPencilBoard(selectedX, selectedY, true);
    drawPenBoard(selectedCellX, selectedCellY, true);
  
  }
  else {
  
    // A cell with a provided number has been selected ..
    
    if (selectedX > 0 && selectedY >= 0) {

      drawPencilBoard(selectedX, selectedY, false);
      drawPenBoard(selectedCellX, selectedCellY, false);
      selectedCellX = -1;
      selectedCellY = -1;
      
    }
  
  }
  
  
  // If a main cell has been selected and then a pencil cell selected, pencil in the new selection ..
  
  if (selectedCellX >= 0 && selectedCellY >= 0 && pencilX >= 0 && pencilY >= 0) {
  
    if (board[selectedCellX][selectedCellY][(pencilY*3)+pencilX+1] != (pencilY*3)+pencilX+1) {
  
      board[selectedCellX][selectedCellY][(pencilY*3)+pencilX+1] = (pencilY*3)+pencilX+1;
  
    }
    else {
  
      board[selectedCellX][selectedCellY][(pencilY*3)+pencilX+1] = 0;
  
    }
  
    drawCell(selectedCellX, selectedCellY, true);
    drawPencilBoard(selectedCellX, selectedCellY, true);
    drawPenBoard(selectedCellX, selectedCellY, true);
  
    refreshAffectedCells(selectedCellX, selectedCellY);
    saveGame(PAGE1);
    
  }
  
  
  // If a main cell has been selected and then a pen cell selected, pen in the new selection ..
  
  if (selectedCellX >= 0 && selectedCellY >= 0 && penX >= 0 && penY >= 0) {
  
    if (board[selectedCellX][selectedCellY][CELL_SELECTED_VALUE] != (penY * 3) + penX + 1) {
    
      board[selectedCellX][selectedCellY][CELL_SELECTED_VALUE] = (penY*3) + penX + 1;
    
    }
    else {
    
      board[selectedCellX][selectedCellY][CELL_SELECTED_VALUE] = 0;
    
    }
    
    drawCell(selectedCellX, selectedCellY, true);
    drawPencilBoard(selectedCellX, selectedCellY, true);
    drawPenBoard(selectedCellX, selectedCellY, true);
      
    refreshAffectedCells(selectedCellX, selectedCellY);
    saveGame(PAGE1);
  
    if (isComplete()) {
      
      showDialog("Complete", "Congratulations, you have completed this Sudoku.", DIALOG_BUTTONS_OKONLY);
      drawScreen();
      
    }

  }
    
  
  // Return to the menu ?
  
  if (point.x >= COMMAND_MENU_LEFT && point.x < COMMAND_MENU_LEFT + COMMAND_MENU_WIDTH && point.y >= COMMAND_MENU_TOP && point.y < COMMAND_MENU_TOP + COMMAND_MENU_HEIGHT) {
    
    selectedScreen = SCREEN_OPTIONS;
    selectedCellX = -1;
    selectedCellY = -1;
    drawScreen();
    
  }

}

void drawScreen() {
  
  lcd.setEraseBackColour(BLACK);
  lcd.erase();
  
  if (selectedScreen == SCREEN_OPTIONS) {
  
       
    // Draw checkboxes ..
  
    lcd.setTextColour(WHITE);    
    lcd.setTextSize(FONT1);

    lcd.string(PENCIL_ERROR_LEFT + 2, PENCIL_ERROR_TOP - 22, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Show :", 0);
  
    lcd.drawRoundRect(PENCIL_ERROR_LEFT, PENCIL_ERROR_TOP, PENCIL_ERROR_LEFT + CHECK_WIDTH, PENCIL_ERROR_TOP + CHECK_HEIGHT, CHECK_OUTER_RADIUS, COLOUR_LIGHTBLUE, hollowFill);  
    lcd.drawRoundRect(PENCIL_ERROR_LEFT + CHECK_INSET, PENCIL_ERROR_TOP + CHECK_INSET, PENCIL_ERROR_LEFT + CHECK_WIDTH - CHECK_INSET, PENCIL_ERROR_TOP + CHECK_HEIGHT - CHECK_INSET, CHECK_INNER_RADIUS, (showPencilInError ? COLOUR_DARKBLUE : BLACK), solidFill);  
    lcd.string(PENCIL_ERROR_LEFT + CHECK_WIDTH + CHECK_LABEL_SPACING, PENCIL_ERROR_TOP + 2, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Pencil Errors", 0);
    
    lcd.drawRoundRect(PEN_ERROR_LEFT, PEN_ERROR_TOP, PEN_ERROR_LEFT + CHECK_WIDTH, PEN_ERROR_TOP + CHECK_HEIGHT, CHECK_OUTER_RADIUS, COLOUR_LIGHTBLUE, hollowFill);  
    lcd.drawRoundRect(PEN_ERROR_LEFT + CHECK_INSET, PEN_ERROR_TOP + CHECK_INSET, PEN_ERROR_LEFT + CHECK_WIDTH - CHECK_INSET, PEN_ERROR_TOP + CHECK_HEIGHT - CHECK_INSET, CHECK_INNER_RADIUS, (showPenInError ? COLOUR_DARKBLUE : BLACK), solidFill);  
    lcd.string(PEN_ERROR_LEFT + CHECK_WIDTH + CHECK_LABEL_SPACING, PEN_ERROR_TOP + 2, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Pen Errors", 0);
        
    lcd.setTextColour(WHITE);    
    lcd.setTextSize(FONT1);

    lcd.drawRoundRect(COMMAND_SAVE_LEFT, COMMAND_SAVE_TOP, COMMAND_SAVE_LEFT + COMMAND_SAVE_WIDTH, COMMAND_SAVE_TOP + COMMAND_SAVE_HEIGHT, radius5, COLOUR_DARKBLUE, solidFill);
    lcd.drawRoundRect(COMMAND_SAVE_LEFT, COMMAND_SAVE_TOP, COMMAND_SAVE_LEFT + COMMAND_SAVE_WIDTH, COMMAND_SAVE_TOP + COMMAND_SAVE_HEIGHT, radius5, COLOUR_LIGHTBLUE, hollowFill);
    lcd.string(COMMAND_SAVE_LEFT + 22, COMMAND_SAVE_TOP + 9, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Save Game", 0);

    lcd.drawRoundRect(COMMAND_RESTORE_LEFT, COMMAND_RESTORE_TOP, COMMAND_RESTORE_LEFT + COMMAND_RESTORE_WIDTH, COMMAND_RESTORE_TOP + COMMAND_RESTORE_HEIGHT, radius5, (gameSaved0 ? COLOUR_DARKBLUE : GREY1), solidFill);
    lcd.drawRoundRect(COMMAND_RESTORE_LEFT, COMMAND_RESTORE_TOP, COMMAND_RESTORE_LEFT + COMMAND_RESTORE_WIDTH, COMMAND_RESTORE_TOP + COMMAND_RESTORE_HEIGHT, radius5, (gameSaved0 ? COLOUR_LIGHTBLUE : GREY3), hollowFill);
    lcd.string(COMMAND_RESTORE_LEFT + 9, COMMAND_RESTORE_TOP + 9, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Restore Game", 0);

    lcd.drawRoundRect(COMMAND_PLAY_LEFT, COMMAND_PLAY_TOP, COMMAND_PLAY_LEFT + COMMAND_PLAY_WIDTH, COMMAND_PLAY_TOP + COMMAND_PLAY_HEIGHT, radius5, COLOUR_DARKBLUE, solidFill);
    lcd.drawRoundRect(COMMAND_PLAY_LEFT, COMMAND_PLAY_TOP, COMMAND_PLAY_LEFT + COMMAND_PLAY_WIDTH, COMMAND_PLAY_TOP + COMMAND_PLAY_HEIGHT, radius5, COLOUR_LIGHTBLUE, hollowFill);
    lcd.string(COMMAND_PLAY_LEFT + 47, COMMAND_PLAY_TOP + 9, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Play !", 0);

    drawTab();
    
  }
  else {
  
    drawMainBoard();
    drawPencilBoard(-1, -1, false);
    drawPenBoard(-1, -1, false);
         
    lcd.drawRoundRect(COMMAND_MENU_LEFT, COMMAND_MENU_TOP, COMMAND_MENU_LEFT + COMMAND_MENU_WIDTH, COMMAND_MENU_TOP + COMMAND_MENU_HEIGHT, radius5, COLOUR_DARKBLUE, solidFill);
    lcd.drawRoundRect(COMMAND_MENU_LEFT, COMMAND_MENU_TOP, COMMAND_MENU_LEFT + COMMAND_MENU_WIDTH, COMMAND_MENU_TOP + COMMAND_MENU_HEIGHT, radius5, COLOUR_LIGHTBLUE, hollowFill);
        
    lcd.setTextColour(WHITE);    
    lcd.setTextSize(FONT1);
    lcd.string(COMMAND_MENU_LEFT + 32, COMMAND_MENU_TOP + 9, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Menu", 0);

  }
  
}

void initBoard() {  // Copy any of the supplied or fixed values to the board array ..

  for (byte x=0; x<=8; x++) {   
   
    for (byte y=0; y<=8; y++) {   
      
      if (solution[x][y] > 0) {
     
        board[x][y][CELL_SELECTED_VALUE] = solution[x][y];
        
      }
      
    }
    
  }
  
}

void drawTab() {

  if (selectedTab == TAB_EASY) {
    
    lcd.drawRoundRect(TAB_MEDIUM_LEFT, TAB_MEDIUM_TOP, TAB_MEDIUM_LEFT + TAB_MEDIUM_WIDTH, TAB_MEDIUM_TOP + TAB_MEDIUM_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_MEDIUM_LEFT, TAB_MEDIUM_TOP, TAB_MEDIUM_LEFT + TAB_MEDIUM_WIDTH, TAB_MEDIUM_TOP + TAB_MEDIUM_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  
    lcd.drawRoundRect(TAB_HARD_LEFT, TAB_HARD_TOP, TAB_HARD_LEFT + TAB_HARD_WIDTH, TAB_HARD_TOP + TAB_HARD_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_HARD_LEFT, TAB_HARD_TOP, TAB_HARD_LEFT + TAB_HARD_WIDTH, TAB_HARD_TOP + TAB_HARD_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  
  
    lcd.drawRoundRect(TAB_EASY_LEFT, TAB_EASY_TOP, TAB_EASY_LEFT + TAB_EASY_WIDTH, TAB_EASY_TOP + TAB_EASY_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_EASY_LEFT, TAB_EASY_TOP, TAB_EASY_LEFT + TAB_EASY_WIDTH, TAB_EASY_TOP + TAB_EASY_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  
  
    lcd.drawRoundRect(TAB_LEFT, TAB_TOP, TAB_LEFT + TAB_WIDTH, TAB_TOP + TAB_HEIGHT, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_LEFT, TAB_TOP, TAB_LEFT + TAB_WIDTH, TAB_TOP + TAB_HEIGHT, radius5, COLOUR_LIGHTBLUE, hollowFill);  

    lcd.drawRectangle(1, 25, 90, 30, COLOUR_DARKBLUE, solidFill);  

  }
  
  if (selectedTab == TAB_MEDIUM) {
    
    lcd.drawRoundRect(TAB_EASY_LEFT, TAB_EASY_TOP, TAB_EASY_LEFT + TAB_EASY_WIDTH, TAB_EASY_TOP + TAB_EASY_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_EASY_LEFT, TAB_EASY_TOP, TAB_EASY_LEFT + TAB_EASY_WIDTH, TAB_EASY_TOP + TAB_EASY_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  
    lcd.drawRoundRect(TAB_HARD_LEFT, TAB_HARD_TOP, TAB_HARD_LEFT + TAB_HARD_WIDTH, TAB_HARD_TOP + TAB_HARD_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_HARD_LEFT, TAB_HARD_TOP, TAB_HARD_LEFT + TAB_HARD_WIDTH, TAB_HARD_TOP + TAB_HARD_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  
  
    lcd.drawRoundRect(TAB_MEDIUM_LEFT, TAB_MEDIUM_TOP, TAB_MEDIUM_LEFT + TAB_MEDIUM_WIDTH, TAB_MEDIUM_TOP + TAB_MEDIUM_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_MEDIUM_LEFT, TAB_MEDIUM_TOP, TAB_MEDIUM_LEFT + TAB_MEDIUM_WIDTH, TAB_MEDIUM_TOP + TAB_MEDIUM_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  
  
    lcd.drawRoundRect(TAB_LEFT, TAB_TOP, TAB_LEFT + TAB_WIDTH, TAB_TOP + TAB_HEIGHT, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_LEFT, TAB_TOP, TAB_LEFT + TAB_WIDTH, TAB_TOP + TAB_HEIGHT, radius5, COLOUR_LIGHTBLUE, hollowFill);  

    lcd.drawRectangle(90, 25, 180, 30, COLOUR_DARKBLUE, solidFill);  

  }
  
  if (selectedTab == TAB_HARD) {
    
    lcd.drawRoundRect(TAB_EASY_LEFT, TAB_EASY_TOP, TAB_EASY_LEFT + TAB_EASY_WIDTH, TAB_EASY_TOP + TAB_EASY_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_EASY_LEFT, TAB_EASY_TOP, TAB_EASY_LEFT + TAB_EASY_WIDTH, TAB_EASY_TOP + TAB_EASY_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  
    lcd.drawRoundRect(TAB_MEDIUM_LEFT, TAB_MEDIUM_TOP, TAB_MEDIUM_LEFT + TAB_MEDIUM_WIDTH, TAB_MEDIUM_TOP + TAB_MEDIUM_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_MEDIUM_LEFT, TAB_MEDIUM_TOP, TAB_MEDIUM_LEFT + TAB_MEDIUM_WIDTH, TAB_MEDIUM_TOP + TAB_MEDIUM_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  

    lcd.drawRoundRect(TAB_HARD_LEFT, TAB_HARD_TOP, TAB_HARD_LEFT + TAB_HARD_WIDTH, TAB_HARD_TOP + TAB_HARD_HEIGHT + 5, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_HARD_LEFT, TAB_HARD_TOP, TAB_HARD_LEFT + TAB_HARD_WIDTH, TAB_HARD_TOP + TAB_HARD_HEIGHT + 5, radius5, COLOUR_LIGHTBLUE, hollowFill);  

    lcd.drawRoundRect(TAB_LEFT, TAB_TOP, TAB_LEFT + TAB_WIDTH, TAB_TOP + TAB_HEIGHT, radius5, COLOUR_DARKBLUE, solidFill);  
    lcd.drawRoundRect(TAB_LEFT, TAB_TOP, TAB_LEFT + TAB_WIDTH, TAB_TOP + TAB_HEIGHT, radius5, COLOUR_LIGHTBLUE, hollowFill);  

    lcd.drawRectangle(180, 25, 270, 30, COLOUR_DARKBLUE, solidFill);  


  }

  lcd.setTextSize(FONT1);

  lcd.setTextColour(selectedTab == TAB_EASY ? WHITE : GREY5);    
  lcd.string(27, 6, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Easy", 0);
  lcd.setTextColour(selectedTab == TAB_MEDIUM ? WHITE : GREY5);    
  lcd.string(108, 6, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Medium", 0);
  lcd.setTextColour(selectedTab == TAB_HARD ? WHITE : GREY5);    
  lcd.string(204, 6, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Hard", 0);

 
  
  int entries = renderFilenames();
  
  
  // Render scrolling buttons ..
  
  lcd.setTextColour(GREY5);    
  selectedTab_Count = entries / TAB_ENTRIES_PER_PAGE + ((entries % TAB_ENTRIES_PER_PAGE) > 0 ? 1 : 0) - 1;
  selectedTab_Count_This_Page = (selectedTab_Count == selectedTab_Page ? ((entries % TAB_ENTRIES_PER_PAGE) > 0 ? entries % TAB_ENTRIES_PER_PAGE : TAB_ENTRIES_PER_PAGE) : TAB_ENTRIES_PER_PAGE);
  itoa((selectedTab_Page + 1), buf, 10);
  lcd.string(TAB_PAGE_TEXT_LEFT, TAB_PAGE_TEXT_TOP, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);


  lcd.drawRoundRect(TAB_PAGE_PREV_LEFT, TAB_PAGE_PREV_TOP, TAB_PAGE_PREV_LEFT + TAB_PAGE_PREV_WIDTH, TAB_PAGE_PREV_TOP + TAB_PAGE_PREV_HEIGHT, radius5, (selectedTab_Page > 0 ? COLOUR_DARKBLUE : GREY1), solidFill);  
  lcd.drawRoundRect(TAB_PAGE_PREV_LEFT, TAB_PAGE_PREV_TOP, TAB_PAGE_PREV_LEFT + TAB_PAGE_PREV_WIDTH, TAB_PAGE_PREV_TOP + TAB_PAGE_PREV_HEIGHT, radius5, (selectedTab_Page > 0 ? COLOUR_LIGHTBLUE : GREY2), hollowFill);  
  lcd.drawTriangle(TAB_PAGE_PREV_LEFT + 4, TAB_PAGE_PREV_TOP + 9, TAB_PAGE_PREV_LEFT + 12, TAB_PAGE_PREV_TOP + 3, TAB_PAGE_PREV_LEFT + 12, TAB_PAGE_PREV_TOP + 14, (selectedTab_Page > 0 ? COLOUR_LIGHTBLUE : GREY3), solidFill);

  lcd.drawRoundRect(TAB_PAGE_NEXT_LEFT, TAB_PAGE_NEXT_TOP, TAB_PAGE_NEXT_LEFT + TAB_PAGE_NEXT_WIDTH, TAB_PAGE_NEXT_TOP + TAB_PAGE_NEXT_HEIGHT, radius5, (selectedTab_Page < selectedTab_Count ? COLOUR_DARKBLUE : GREY1), solidFill);  
  lcd.drawRoundRect(TAB_PAGE_NEXT_LEFT, TAB_PAGE_NEXT_TOP, TAB_PAGE_NEXT_LEFT + TAB_PAGE_NEXT_WIDTH, TAB_PAGE_NEXT_TOP + TAB_PAGE_NEXT_HEIGHT, radius5, (selectedTab_Page < selectedTab_Count ? COLOUR_LIGHTBLUE : GREY2), hollowFill);  
  lcd.drawTriangle(TAB_PAGE_NEXT_LEFT + 13, TAB_PAGE_NEXT_TOP + 9, TAB_PAGE_NEXT_LEFT + 5, TAB_PAGE_NEXT_TOP + 3, TAB_PAGE_NEXT_LEFT + 5, TAB_PAGE_NEXT_TOP + 14, (selectedTab_Page < selectedTab_Count ? COLOUR_LIGHTBLUE : GREY2), solidFill);

}

void populateSolution(int row, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9) {
  
  solution[0][row]=v1;
  solution[1][row]=v2;
  solution[2][row]=v3;
  solution[3][row]=v4;
  solution[4][row]=v5;
  solution[5][row]=v6;
  solution[6][row]=v7;
  solution[7][row]=v8;
  solution[8][row]=v9;
  
}

void drawMainBoard() {  // draw the entire board ..
  
  for (byte x=0; x <= 8; x++){
    
    for (byte y=0; y <= 8; y++){
      
      drawCell(x,y, false);
    }
    
  }
  
}

void refreshAffectedCells(char selectedX, char selectedY) {  // refreshes those cells that may have been affected by a pen or pencil change ..

  // Refresh row ..
  
  for (byte x=0; x<=8; x++) {   

    if (x != selectedX) { drawCell(x, selectedY, false); }
    
  }


  // Refresh column ..
  
  for (byte y=0; y<=8; y++) {   

    if (y != selectedY) { drawCell(selectedX, y, false); }
    
  }
  
  
  // Refresh 3x3 grid ..

  char x1, x2, y1, y2;
  
  if (selectedX >= 0 && selectedX <= 2)   { x1 = 0; x2 = 2; }
  if (selectedX >= 3 && selectedX <= 5)   { x1 = 3; x2 = 5; }
  if (selectedX >= 6 && selectedX <= 8)   { x1 = 6; x2 = 8; }
  
  if (selectedY >= 0 && selectedY <= 2)   { y1 = 0; y2 = 2; }
  if (selectedY >= 3 && selectedY <= 5)   { y1 = 3; y2 = 5; }
  if (selectedY >= 6 && selectedY <= 8)   { y1 = 6; y2 = 8; }
          
  for (byte x=x1; x<=x2; x++) {   
        
    for (byte y=y1; y<=y2; y++) {   

      if (selectedX != x && selectedY != y) { drawCell(x, y, false); }
      
    }
  
  }
  
}

void drawCell(char x, char y, boolean highlight) {
  
  POINT p1, p2;
  COLOUR colour;

  p1.x = (x * CELL_SPACING);
  p1.y = (y * CELL_SPACING);
  p2.x = (x * CELL_SPACING) + CELL_WIDTH;
  p2.y = (y * CELL_SPACING) + CELL_WIDTH;
  
  if (highlight) {

    lcd.drawRoundRect(p1.x,p1.y,p2.x,p2.y,radius5,COLOUR_DARKBLUE,solidFill); //draw a round rectangle
    lcd.drawRoundRect(p1.x,p1.y,p2.x,p2.y,radius5,COLOUR_GRID_SELECTED,hollowFill); //draw a round rectangle
    
  }
  else {
  
    if (((x>2 && x<6) || (y>2 && y<6)) && !(x>2 && x<6 && y>2 && y<6)) {
      colour= COLOUR_GRID_HIGHLIGHT;
    }
    else {
      colour= COLOUR_GRID_LOWLIGHT;
    }
  
    lcd.drawRoundRect(p1.x,p1.y,p2.x,p2.y,radius5,colour,solidFill); //draw a round rectangle
    
  }
  
  if (solution[x][y] > 0) {
  
    lcd.setTextColour(WHITE);    
    lcd.setTextSize(FONT3);
    itoa(solution[x][y], buf, 10);
    lcd.string((x * CELL_SPACING) + 11, (y * CELL_SPACING) + 6, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);
    
  }
  else {
 
    if (board[x][y][CELL_SELECTED_VALUE] > 0) {

      lcd.setTextColour(YELLOW);    
      lcd.setTextSize(FONT3);

      if (showPenInError && penInError(x, y, board[x][y][CELL_SELECTED_VALUE])) {

        lcd.setTextColour(RED);    
        lcd.setTextSize(FONT3);

      }
      
      itoa(board[x][y][CELL_SELECTED_VALUE], buf, 10);
      lcd.string((x * CELL_SPACING) + 11, (y * CELL_SPACING) + 6, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);
    
    }
    else {

      lcd.setTextColour(YELLOW);    
      lcd.setTextSize(FONT0);

      for (byte x1=1; x1<=3; x1++) {

        for (byte y1=0; y1<=2; y1++) {
          
          if (board[x][y][(y1*3)+x1] > 0) {

            lcd.setTextColour(YELLOW);    
            lcd.setTextSize(FONT0);

            if (showPencilInError && pencilInError(x, y, (y1*3)+x1)) {
               
                lcd.setTextColour(RED);    
                lcd.setTextSize(FONT0);
              
            }
        
            itoa(board[x][y][(y1*3)+x1],buf, 10);
            lcd.string((x * CELL_SPACING) - 4 + (x1 * 9), (y * CELL_SPACING) + 1 + (y1 * 10), MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);
    
          }
          
        }
        
      }
    
    }
    
  }

}

void drawPencilBoard(char selectedX, char selectedY, boolean highlight) {
 
  for (byte x=0; x<=2; x++){
    
    for (byte y=0; y<=2; y++){

      lcd.drawRoundRect((x * CELL_SPACING) + PENCIL_LEFT, (y * CELL_SPACING) + PENCIL_TOP, (x * CELL_SPACING) + PENCIL_LEFT + CELL_WIDTH, (y * CELL_SPACING) + PENCIL_TOP + CELL_WIDTH, radius5, (highlight ? COLOUR_DARKBLUE : GREY1), solidFill); 
      lcd.drawRoundRect((x * CELL_SPACING) + PENCIL_LEFT, (y * CELL_SPACING) + PENCIL_TOP, (x * CELL_SPACING) + PENCIL_LEFT + CELL_WIDTH, (y * CELL_SPACING) + PENCIL_TOP + CELL_WIDTH, radius5, (highlight ? COLOUR_LIGHTBLUE : GREY3), hollowFill); 
           
    }
    
  }

  
  int i = 1;
  lcd.setTextSize(FONT0);
    
  for (byte y1=0; y1<=2; y1++) {
  
    for (byte x1=1; x1<=3; x1++) {
    
      if (highlight) {
        
        if (board[selectedX][selectedY][(y1 * 3) + x1] > 0) {
  
          lcd.setTextColour(YELLOW);    
  
          if (showPencilInError && pencilInError(selectedX, selectedY, (y1 * 3) + x1)) {
           
            lcd.setTextColour(RED);    
            
          }
        
        }
        else {
    
          lcd.setTextColour(WHITE);    
      
        }
        
      }
      else {
  
        lcd.setTextColour(GREY3);    
    
      }

      itoa(i, buf, 10);
      lcd.string(((x1 - 1) * CELL_SPACING) + PENCIL_LEFT - 4 + (x1 * 9), (y1 * CELL_SPACING) + PENCIL_TOP + 1 + (y1 * 10), MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);
      i++;

    }
    
  }
  
  
  // Draw label ..
    
  lcd.setTextColour(highlight ? WHITE : GREY3);    
  lcd.setTextSize(FONT0);
  lcd.drawRoundRect(PENCIL_LABEL_LEFT, PENCIL_LABEL_TOP, PENCIL_LABEL_LEFT + PENCIL_LABEL_WIDTH, PENCIL_LABEL_TOP + PENCIL_LABEL_HEIGHT, CHECK_OUTER_RADIUS, (highlight ? COLOUR_DARKBLUE : GREY1), solidFill);  
  lcd.orientation(PORTRAIT_LOW);
  lcd.string(255, PENCIL_LABEL_LEFT + 6, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Pencil", 0);
  lcd.orientation(LANDSCAPE_LEFT);
  
}

boolean pencilInError(char selectedX, char selectedY, char pencil) {
        
  for (byte x=0; x<=8; x++) {   
 
    if (board[x][selectedY][CELL_SELECTED_VALUE] == pencil || solution[x][selectedY] == pencil) {
 
      return true;
      
    }
    
  }
  
  for (byte y=0; y<=8; y++) {   
 
    if (board[selectedX][y][CELL_SELECTED_VALUE] == pencil || solution[selectedX][y] == pencil) {
 
      return true;
      
    }
    
  } 
  
  int x1, x2, y1, y2;
  
  if (selectedX >= 0 && selectedX <= 2)   { x1 = 0; x2 = 2; }
  if (selectedX >= 3 && selectedX <= 5)   { x1 = 3; x2 = 5; }
  if (selectedX >= 6 && selectedX <= 8)   { x1 = 6; x2 = 8; }
  
  if (selectedY >= 0 && selectedY <= 2)   { y1 = 0; y2 = 2; }
  if (selectedY >= 3 && selectedY <= 5)   { y1 = 3; y2 = 5; }
  if (selectedY >= 6 && selectedY <= 8)   { y1 = 6; y2 = 8; }
          
  for (byte x=x1; x<=x2; x++) {   
        
    for (byte y=y1; y<=y2; y++) {   

      if (selectedX != x && selectedY != y && (board[x][y][CELL_SELECTED_VALUE] == pencil || solution[x][y] == pencil)) {
 
        return true;
  
      }
      
    }
  
  }
  
  return false;
  
}

void drawPenBoard(char selectedX, char selectedY, boolean highlight) {

  for (byte x=0; x<=2; x++){
    
    for (byte y=0; y<=2; y++){

      lcd.drawRoundRect((x * CELL_SPACING) + PEN_LEFT, (y * CELL_SPACING) + PEN_TOP, (x * CELL_SPACING) + PEN_LEFT + CELL_WIDTH, (y * CELL_SPACING) + PEN_TOP + CELL_WIDTH, radius5, (highlight ? COLOUR_DARKBLUE : GREY1), solidFill); 
      lcd.drawRoundRect((x * CELL_SPACING) + PEN_LEFT, (y * CELL_SPACING) + PEN_TOP, (x * CELL_SPACING) + PEN_LEFT + CELL_WIDTH, (y * CELL_SPACING) + PEN_TOP + CELL_WIDTH, radius5, (highlight ? COLOUR_LIGHTBLUE : GREY3), hollowFill); 
                
    }
    
  }

  lcd.setTextSize(FONT3);
  
  for (byte y=0; y<=2; y++) {
  
    for (byte x=1; x<=3; x++) {
    
      if (highlight) {

        if (board[selectedX][selectedY][CELL_SELECTED_VALUE] == (y * 3) + x) {
  
          lcd.setTextColour(YELLOW);    
  
          if (showPenInError && penInError(selectedX, selectedY, (y * 3) + x)) {
            
            lcd.setTextColour(RED);    
      
          }
          
        }
        else {
  
          lcd.setTextColour(WHITE);    
      
        } 
        
      }
      else {
  
          lcd.setTextColour(GREY3);    
        
      }

      itoa((y*3)+x, buf, 10);
      lcd.string(((x - 1) * CELL_SPACING) + 11 + PEN_LEFT, (y * CELL_SPACING) + 6 + PEN_TOP, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buf, 0);

    }

  }

  
  // Draw label ..
    
  lcd.setTextColour(highlight ? WHITE : GREY3);    
  lcd.setTextSize(FONT0);
  lcd.drawRoundRect(PEN_LABEL_LEFT, PEN_LABEL_TOP, PEN_LABEL_LEFT + PEN_LABEL_WIDTH, PEN_LABEL_TOP + PEN_LABEL_HEIGHT, CHECK_OUTER_RADIUS, (highlight ? COLOUR_DARKBLUE : GREY1), solidFill);  
  lcd.orientation(PORTRAIT_LOW);
  lcd.string(PEN_LABEL_TOP + 18, PEN_LABEL_LEFT + 6, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Pen", 0);
  lcd.orientation(LANDSCAPE_LEFT);
  
}


boolean penInError(char selectedX, char selectedY, char pen) {
        
  for (byte x=0; x<=8; x++) {   
 
    if (x != selectedX && board[x][selectedY][CELL_SELECTED_VALUE] == pen || solution[x][selectedY] == pen) {
 
      return true;
      
    }
    
  }
  
  for (byte y=0; y<=8; y++) {   
 
    if (y != selectedY && board[selectedX][y][CELL_SELECTED_VALUE] == pen || solution[selectedX][y] == pen) {
 
      return true;
      
    }
    
  } 
  
  int x1, x2, y1, y2;
  
  if (selectedX >= 0 && selectedX <= 2)   { x1 = 0; x2 = 2; }
  if (selectedX >= 3 && selectedX <= 5)   { x1 = 3; x2 = 5; }
  if (selectedX >= 6 && selectedX <= 8)   { x1 = 6; x2 = 8; }
  
  if (selectedY >= 0 && selectedY <= 2)   { y1 = 0; y2 = 2; }
  if (selectedY >= 3 && selectedY <= 5)   { y1 = 3; y2 = 5; }
  if (selectedY >= 6 && selectedY <= 8)   { y1 = 6; y2 = 8; }
  
          
  for (byte x=x1; x<=x2; x++) {   
        
    for (byte y=y1; y<=y2; y++) {   

      if (selectedX != x && selectedY != y && (board[x][y][CELL_SELECTED_VALUE] == pen || solution[x][y] == pen)) {
 
        return true;
  
      }
      
    }
  
  }
  
  return false;
  
}

boolean isComplete() {

  
  // Check columns ..
  
  for (byte x=0; x<=8; x++) {   
   
    int total = 0;
    
    for (byte y=0; y<=8; y++) {   
   
      total = total + board[x][y][CELL_SELECTED_VALUE];
    
    }
    
    if (total != 45) {

      return false;
      
    }
    
  }
  

  // Check rows ..
  
  for (byte y=0; y<=8; y++) {   
   
    int total = 0;
  
    for (byte x=0; x<=8; x++) {   
   
      total = total + board[x][y][CELL_SELECTED_VALUE];
    
    }
    
    if (total != 45) {
      
      return false;
      
    }
    
  }



  // Check 3x3 grids ..
  
  for (byte x=0; x<=8; x=x+3) {   

    for (byte y=0; y<=8; y=y+3) {   

      int total = 0;

      for (byte x1=x; x1<=x+2; x1++) {   
  
        for (byte y1=y; y1<=y+2; y1++) {   
          
          total = total + board[x1][y1][CELL_SELECTED_VALUE];
          
        } 
        
      } 
    
      if (total != 45) { return false; }
      
    } 
    
  } 
     
  return true;    
  
}

void drawCompleteMessage() {
  
  lcd.setTextSize(FONT3);
  lcd.string(164, 164, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Complete !", 0);

}

void saveGame(EEPROMPAGE page) {

  lcd.initClearEEPROMBuff();


  // Write out SUDOKU at start of buffer to identify our data ..
  
  lcd.writeEEPROMBuff("SUDOKU", 0, 6, 0);
  

  //  Save solution first ..
  //
  for (byte x=0; x<=8; x=x+1) {   

    for (byte y=0; y<=8; y=y+1) {   

       buffer[(y * 9) + x] = solution[x][y] + 80;
       
    }
    
  }

  lcd.writeEEPROMBuff(buffer, 6, 81, 0);

  
  //  Save board next ..
  //
  for (byte z=0; z<=9; z=z+1) { // Z

    for (byte x=0; x<=8; x=x+1) {   

      for (byte y=0; y<=8; y=y+1) {   
  
       buffer[(y * 9) + x] = board[x][y][z] + 80;
       
      }
     
    }

    lcd.writeEEPROMBuff(buffer, ((z + 1) * 87), 81, 0);
  
  }
  
  lcd.eraseEEPROMPage(page);
  lcd.saveBuffToEEPROMPage(page);    
  
}


void restoreGame(EEPROMPAGE page) {

  lcd.initClearEEPROMBuff();
  lcd.fillBuffFromEEPROMPage(page);
  
  // Check to see if the saved data starts with SUDOKU ..

  lcd.readEEPROMBuff(buffer, 0, 6, 0);

  if (buffer[0] == 'S' && buffer[1] == 'U' && buffer[2] == 'D' && buffer[3] == 'O' && buffer[4] == 'K' && buffer[5] == 'U') { 

     
    // Populate the solution with the first 81 chars ..
    
    lcd.readEEPROMBuff(buffer, 6, 87, 0);
  
    for (byte x=0; x<=8; x=x+1) {   
  
      for (byte y=0; y<=8; y=y+1) {   
  
         solution[x][y] = buffer[(y * 9) + x] - 80;
         
      }
      
    }
    
    
    // Populate the board with the remaining 810 chars ..
  
    for (byte z=0; z<=9; z=z+1) {   
  
      lcd.readEEPROMBuff(buffer, ((z + 1) * 87), 81, 0);
    
      for (byte x=0; x<=8; x=x+1) {   
    
        for (byte y=0; y<=8; y=y+1) {   
    
          board[x][y][z] = buffer[(y * 9) + x] - 80;
         
        }
       
      }
    
    }
    
    initBoard();
  
  }
  
}


boolean isGameSaved(EEPROMPAGE page) {

  lcd.initClearEEPROMBuff();
  lcd.fillBuffFromEEPROMPage(page);

  
  // Check to see if the saved data starts with SUDOKU ..

  lcd.readEEPROMBuff(buffer, 0, 6, 0);

  if (buffer[0] == 'S' && buffer[1] == 'U' && buffer[2] == 'D' && buffer[3] == 'O' && buffer[4] == 'K' && buffer[5] == 'U') { 
  
    return true;
    
  }
  else {
    
    return false;
    
  }
  
}

void die(FILERESULT response){ //if the response is different than OK, print and loop forever

  if(response!=F_OK){
    lcd.string(10,20,MAX_X_LANDSCAPE,MAX_Y_LANDSCAPE,"Error... forever loop @",0);
    while(1); 
  }
  
}

int renderFilenames() {

  char* filename = "";             

  int row = TAB_ROWS_TOP;
  boolean highlight = false; 
  boolean cont = true;
  
  lcd.setTextSize(FONT1);
  lcd.setTextColour(WHITE);    
 
  unsigned int bytesRead=0, i=0;       
 
  if (selectedTab == TAB_EASY)     { filename = "sudoku_Easy.txt     "; }
  if (selectedTab == TAB_MEDIUM)   { filename = "sudoku_Medium.txt   "; }
  if (selectedTab == TAB_HARD)     { filename = "sudoku_Hard.txt     "; }
 
  res = lcd.SDFopenFile(filename, READONLY, WORKSPACE0); 

  if (res!=F_OK){
 
    res=lcd.SDFnewFile(filename);                                                die(res);
    res=lcd.SDFopenFile(filename, WRITEONLY, WORKSPACE0);                        die(res);
 
  }
 
  do {
 
    memset(buffer, 0, sizeof(buffer));
    res = lcd.SDFreadFile(buffer, RECORD_DESC_LENGTH, &bytesRead, WORKSPACE0);        die(res);    
 
    if (bytesRead == RECORD_DESC_LENGTH) {
 
      if (i >= (selectedTab_Page * TAB_ENTRIES_PER_PAGE) && i < ((selectedTab_Page + 1) * TAB_ENTRIES_PER_PAGE)) {


        if (highlight)   { lcd.drawRectangle(10, row, 320, row + GRID_ROW_HEIGHT, 0x01ec, solidFill); }
        highlight = !highlight;

        lcd.string(20, row + 8, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, buffer, 0);
        row+=GRID_ROW_HEIGHT;       
      
      }

      
      // Read and discard remainder of record ..
      
      res = lcd.SDFreadFile(buffer, RECORD_SOLUTION_LENGTH + 2, &bytesRead, WORKSPACE0);        die(res);       // Be careful about text files with CR / LF ! will need to have RECORD_SOLUTION_LENGTH + 1
     
      i++;
 
    }
    else {
     
      cont = false;
      
    }
 
  }
  while (cont);
 
  lcd.SDFcloseFile(WORKSPACE0);   

  return i;
 
}
 
void loadGame(int fileIndex) {
  
  char* filename = "";             
  boolean cont = true;
  
  lcd.setTextSize(FONT1);
  lcd.setTextColour(WHITE);    
 
  unsigned int bytesRead=0, i=0;       
 
  if (selectedTab == TAB_EASY)     { filename = "sudoku_Easy.txt     "; }
  if (selectedTab == TAB_MEDIUM)   { filename = "sudoku_Medium.txt   "; }
  if (selectedTab == TAB_HARD)     { filename = "sudoku_Hard.txt     "; }
 
  res = lcd.SDFopenFile(filename, READONLY, WORKSPACE0); 
 
  do {
 
    memset(buffer, 0, sizeof(buffer));
    res = lcd.SDFreadFile(buffer, RECORD_DESC_LENGTH, &bytesRead, WORKSPACE0);        die(res);    
 
    if (bytesRead == RECORD_DESC_LENGTH) {
      
      res = lcd.SDFreadFile(buffer, RECORD_SOLUTION_LENGTH + 2, &bytesRead, WORKSPACE0);        die(res);       // Be careful about text files with CR / LF ! will need to have RECORD_SOLUTION_LENGTH + 1
 
      if ((selectedTab_Page * TAB_ENTRIES_PER_PAGE) + fileIndex == i) {

        
        // Load the board ..
        
        for (byte x=0; x<=8; x=x+1) {   
      
          for (byte y=0; y<=8; y=y+1) {   
      
             solution[x][y] = buffer[(y * 9) + x] - 80;
             
          }
          
        }      
        
        
        // Clear the board of user mark up ..
      
        for (byte z=0; z<=9; z=z+1) {   
        
          for (byte x=0; x<=8; x=x+1) {   
        
            for (byte y=0; y<=8; y=y+1) {   
        
              board[x][y][z] = 0;
             
            }
           
          }
        
        }
     
        initBoard();
        break;
      
      }
     
      i++;
 
    }
    else {
     
      cont = false;
      
    }
 
  }
  while (cont);
  
  lcd.SDFcloseFile(WORKSPACE0);   
  saveGame(PAGE1);

}

int showDialog(char caption[], char message[], int buttons) {

  int dialogResult = -1; 
 
  lcd.setTextColour(BLACK);    
  lcd.setTextSize(FONT1);
  lcd.objWindow(DIALOG_LEFT, DIALOG_TOP, DIALOG_LEFT + DIALOG_WIDTH, DIALOG_TOP + DIALOG_HEIGHT, FONT2, SELECTEDGRAY, caption);
  lcd.string(DIALOG_LEFT + DIALOG_MESSAGE_LEFT, DIALOG_TOP + DIALOG_MESSAGE_TOP, DIALOG_LEFT + DIALOG_MESSAGE_LEFT + DIALOG_MESSAGE_WIDTH, MAX_Y_LANDSCAPE, message, 0);
  
  if (buttons == DIALOG_BUTTONS_OKCANCEL) {
    
    lcd.drawRoundRect(DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON1_LEFT, DIALOG_TOP + DIALOG_BUTTON_TOP, DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON1_LEFT + DIALOG_BUTTON_WIDTH, DIALOG_TOP + DIALOG_BUTTON_TOP + DIALOG_BUTTON_HEIGHT, DIALOG_BUTTON_RADIUS, COLOUR_DARKBLUE, hollowFill);  
    lcd.drawRoundRect(DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON2_LEFT, DIALOG_TOP + DIALOG_BUTTON_TOP, DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON2_LEFT + DIALOG_BUTTON_WIDTH, DIALOG_TOP + DIALOG_BUTTON_TOP + DIALOG_BUTTON_HEIGHT, DIALOG_BUTTON_RADIUS, COLOUR_DARKBLUE, hollowFill);  
    lcd.string(DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON1_LEFT + 34, DIALOG_TOP + DIALOG_BUTTON_TOP + 11, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "OK", 0);
    lcd.string(DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON2_LEFT + 18, DIALOG_TOP + DIALOG_BUTTON_TOP + 11, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "Cancel", 0);
    
  }
  
  if (buttons == DIALOG_BUTTONS_OKONLY) {
    
    lcd.drawRoundRect(DIALOG_LEFT + DIALOG_1BUTTONS_LEFT, DIALOG_TOP + DIALOG_BUTTON_TOP, DIALOG_LEFT + DIALOG_1BUTTONS_LEFT + DIALOG_BUTTON_WIDTH, DIALOG_TOP + DIALOG_BUTTON_TOP + DIALOG_BUTTON_HEIGHT, DIALOG_BUTTON_RADIUS, COLOUR_DARKBLUE, hollowFill);  
    lcd.string(DIALOG_LEFT + DIALOG_1BUTTONS_LEFT + 34, DIALOG_TOP + DIALOG_BUTTON_TOP + 11, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE, "OK", 0);
    
  }

  
  while (dialogResult == -1) { 
    
    if (lcd.touchScreen(&point)) {

      if (buttons == DIALOG_BUTTONS_OKCANCEL) {    

        
        // OK pressed ?
        
        if (point.x >= DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON1_LEFT && point.x <= DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON1_LEFT + DIALOG_BUTTON_WIDTH && point.y >= DIALOG_TOP + DIALOG_BUTTON_TOP && point.y <= DIALOG_TOP + DIALOG_BUTTON_TOP + DIALOG_BUTTON_HEIGHT) {
    
          dialogResult = DIALOG_RESULT_OK;
          break;
    
        }      
        
        
        // Cancel pressed ?
        
        if (point.x >= DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON2_LEFT && point.x <= DIALOG_LEFT + DIALOG_2BUTTONS_BUTTON2_LEFT + DIALOG_BUTTON_WIDTH && point.y >= DIALOG_TOP + DIALOG_BUTTON_TOP && point.y <= DIALOG_TOP + DIALOG_BUTTON_TOP + DIALOG_BUTTON_HEIGHT) {
    
          dialogResult = DIALOG_RESULT_CANCEL;
          break;
    
        }      
        
        
        // Close button pressed ?
        
        if (point.x >= DIALOG_LEFT + DIALOG_BUTTON_CANCEL_LEFT && point.x <= DIALOG_LEFT + DIALOG_BUTTON_CANCEL_LEFT + DIALOG_BUTTON_CANCEL_WIDTH && point.y >= DIALOG_TOP + DIALOG_BUTTON_CANCEL_TOP && point.y <= DIALOG_TOP + DIALOG_BUTTON_CANCEL_TOP + DIALOG_BUTTON_CANCEL_HEIGHT) {
    
          dialogResult = DIALOG_RESULT_CANCEL;
          break;
    
        }      
  
      }
  
      if (buttons == DIALOG_BUTTONS_OKONLY) {    

        
        // OK pressed ?
        
        if (point.x >= DIALOG_LEFT + DIALOG_1BUTTONS_LEFT && point.x <= DIALOG_LEFT + DIALOG_1BUTTONS_LEFT + DIALOG_BUTTON_WIDTH && point.y >= DIALOG_TOP + DIALOG_BUTTON_TOP && point.y <= DIALOG_TOP + DIALOG_BUTTON_TOP + DIALOG_BUTTON_HEIGHT) {
    
          dialogResult = DIALOG_RESULT_OK;
          break;
    
        }      
      
      
        // Close button pressed ?
        
        if (point.x >= DIALOG_LEFT + DIALOG_BUTTON_CANCEL_LEFT && point.x <= DIALOG_LEFT + DIALOG_BUTTON_CANCEL_LEFT + DIALOG_BUTTON_CANCEL_WIDTH && point.y >= DIALOG_TOP + DIALOG_BUTTON_CANCEL_TOP && point.y <= DIALOG_TOP + DIALOG_BUTTON_CANCEL_TOP + DIALOG_BUTTON_CANCEL_HEIGHT) {
    
          dialogResult = DIALOG_RESULT_OK;
          break;
    
        }      
  
      }    

    }
    
    delay(50);
    
  }
  
  point.x = -1;
  point.y = -1; 
  return dialogResult;
  
}
