#include <SMARTGPU2.h>

SMARTGPU2 lcd; 

SG_AXIS LCD_WIDTH, LCD_HEIGHT; //Variables to handle the screen resolution
SG_AXIS MAX_X_PORTRAIT, MAX_Y_PORTRAIT, MAX_X_LANDSCAPE, MAX_Y_LANDSCAPE;

#define GREY1 0x2104
#define GREY2 0x3186
#define GREY3 0x528A
#define GREY4 0x630C
#define GREY5 0x8410
#define GREY6 0xA514
#define GREY7 0xB596
#define GREY8 0xC618
#define GREY9 0xE71C
#define GREYA 0xF79E
#define GREYB 0xFFDF
#define TABLE_GREEN 0x03E6

#define CARD_LARGE_WIDTH 98
#define CARD_LARGE_HEIGHT 135
#define CARD_LARGE_INSET 3
#define CARD_LARGE_SPACING 20

#define CARD_LARGE_TOP_PLAYER 260
#define CARD_LARGE_LEFT_PLAYER_FIRSTHAND 10
#define CARD_LARGE_ROTATED_Y_OFFSET 20
#define CARD_LARGE_LEFT_PLAYER_SECONDHAND 130
#define CARD_LARGE_TOP_DEALER 40
#define CARD_LARGE_LEFT_DEALER 10

#define CARD_SMALL_WIDTH 48
#define CARD_SMALL_HEIGHT 68
#define CARD_SMALL_INSET 2
#define CARD_SMALL_ROTATED_Y_OFFSET 10
#define CARD_SMALL_LEFT_PLAYER_FIRSTHAND 10
#define CARD_SMALL_LEFT_PLAYER_SECONDHAND 200
#define CARD_SMALL_TOP_PLAYER 260
#define CARD_SMALL_SPACING 10

#define CARD_BLUE_BACKGROUND 52
#define CARD_RED_BACKGROUND 53

#define STATUS_LOWER_TOP 459
#define STATUS_HEIGHT 20
#define STATUS_BANK_CAPTION_LEFT 5
#define STATUS_BANK_VALUE_LEFT 43
#define STATUS_INIT_BET_CAPTION_LEFT 81
#define STATUS_INIT_BET_VALUE_LEFT 128
#define STATUS_TOTAL_BET_CAPTION_LEFT 159
#define STATUS_TOTAL_BET_VALUE_LEFT 221
#define STATUS_WIN_CAPTION_LEFT 253
#define STATUS_WIN_VALUE_LEFT 286
#define STATUS_LEFT_FIRSTHAND 5      
#define STATUS_LEFT_SECONDHAND 125
#define STATUS_MIDDLE_TOP 210
#define STATUS_HANDS_PLAYED_CAPTION_LEFT 5
#define STATUS_HANDS_PLAYED_VALUE_LEFT 93
#define STATUS_HANDS_WON_CAPTION_LEFT 124
#define STATUS_HANDS_WON_VALUE_LEFT 154
#define STATUS_HANDS_LOST_CAPTION_LEFT 186
#define STATUS_HANDS_LOST_VALUE_LEFT 218
#define STATUS_HANDS_PUSH_CAPTION_LEFT 249
#define STATUS_HANDS_PUSH_VALUE_LEFT 286
#define STATUS_TEXT_OFFSET 3

#define BUTTONS_TOP 420
#define BUTTONS_HEIGHT 31

#define BUTTONS_HITME_LEFT 4
#define BUTTONS_HITME_TOP BUTTONS_TOP
#define BUTTONS_HITME_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_HITME_WIDTH 73

#define BUTTONS_STAND_LEFT 82
#define BUTTONS_STAND_TOP BUTTONS_TOP
#define BUTTONS_STAND_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_STAND_WIDTH 74

#define BUTTONS_DOUBLE_LEFT 161
#define BUTTONS_DOUBLE_TOP BUTTONS_TOP
#define BUTTONS_DOUBLE_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_DOUBLE_WIDTH 74

#define BUTTONS_SPLIT_LEFT 240
#define BUTTONS_SPLIT_TOP BUTTONS_TOP
#define BUTTONS_SPLIT_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_SPLIT_WIDTH 74

#define BUTTONS_1_LEFT 5
#define BUTTONS_1_TOP BUTTONS_TOP
#define BUTTONS_1_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_1_WIDTH 40

#define BUTTONS_5_LEFT 50
#define BUTTONS_5_TOP BUTTONS_TOP
#define BUTTONS_5_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_5_WIDTH 40

#define BUTTONS_10_LEFT 95
#define BUTTONS_10_TOP BUTTONS_TOP
#define BUTTONS_10_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_10_WIDTH 40

#define BUTTONS_25_LEFT 140
#define BUTTONS_25_TOP BUTTONS_TOP
#define BUTTONS_25_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_25_WIDTH 40

#define BUTTONS_CLEAR_LEFT 185
#define BUTTONS_CLEAR_TOP BUTTONS_TOP
#define BUTTONS_CLEAR_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_CLEAR_WIDTH 62

#define BUTTONS_PLAY_LEFT 252
#define BUTTONS_PLAY_TOP BUTTONS_TOP
#define BUTTONS_PLAY_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_PLAY_WIDTH 62

#define BUTTONS_CONTINUE_LEFT 212
#define BUTTONS_CONTINUE_TOP BUTTONS_TOP
#define BUTTONS_CONTINUE_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_CONTINUE_WIDTH 102

#define BUTTONS_QUIT_LEFT 103
#define BUTTONS_QUIT_TOP BUTTONS_TOP
#define BUTTONS_QUIT_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_QUIT_WIDTH 102

#define BUTTONS_PLAY_GAME_LEFT 217
#define BUTTONS_PLAY_GAME_TOP 442
#define BUTTONS_PLAY_GAME_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_PLAY_GAME_WIDTH 92

#define BUTTONS_OPTIONS_LEFT 120
#define BUTTONS_OPTIONS_TOP 442
#define BUTTONS_OPTIONS_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_OPTIONS_WIDTH 92

#define BUTTONS_END_SPLASH_LEFT 212
#define BUTTONS_END_SPLASH_TOP BUTTONS_TOP + 22
#define BUTTONS_END_SPLASH_HEIGHT BUTTONS_HEIGHT
#define BUTTONS_END_SPLASH_WIDTH 102

#define PLAYER 0
#define DEALER 1
#define FIRST_HAND 0
#define SECOND_HAND 1
#define DEALER_HAND 2

#define SHOW_BET_BUTTONS 0
#define SHOW_OPTIONS_BUTTONS 1
#define SHOW_INSURANCE_BUTTONS 2
#define SHOW_END_OF_GAME_BUTTONS 3
#define SHOW_OPTIONS_BUTTONS_DISABLED 4
#define SHOW_GAME_PLAY_BUTTONS 5
#define SHOW_GAME_PLAY_BUTTONS_DISABLED 6

#define CHK_SIZE 16
#define CHK_ALLOW_SPLIT_LEFT 40
#define CHK_ALLOW_SPLIT_TOP 360
#define CHK_ALLOW_SPLIT_CAPTION_LEFT 70
#define CHK_DOUBLE_ON_SPLIT_LEFT 40
#define CHK_DOUBLE_ON_SPLIT_TOP 380
#define CHK_DOUBLE_ON_SPLIT_CAPTION_LEFT 70
#define CHK_BLACKJACK_PAYS_322_LEFT 40
#define CHK_BLACKJACK_PAYS_322_TOP 400
#define CHK_BLACKJACK_PAYS_322_CAPTION_LEFT 70

#define URL_LEFT 77
#define URL_TOP 415 

SG_RADIUS radius5 = 5;  
SG_RADIUS radius2 = 2;  
SG_FILLGEOM solidFill=(SG_FILLGEOM)1;
SG_FILLGEOM hollowFill=(SG_FILLGEOM)0;
SG_ORIENTATIONPARAMETER horizontal=(SG_ORIENTATIONPARAMETER)0;

SG_POINT point;

int purse = 100;
int currentBetTotal = 0;
int currentBetInit = 0;
int currentWin = 0;
boolean showOptions = false;

SG_ACTIVE chkAllowSplit = SG_SELECTED;
SG_ACTIVE chkDoubleOnSplit = SG_SELECTED;
SG_ACTIVE chkBlackjackPays322 = SG_SELECTED;

byte buttonMode = SHOW_BET_BUTTONS;

byte cards[52]={0};
byte dealer[12]={0};
byte player_FirstHand[12]={0};
byte player_SecondHand[12]={0};

byte handInPlay = FIRST_HAND;
byte dealer_CardCount = 0;
boolean player_Split = false;
byte player_FirstHand_CardCount = 0;
byte player_SecondHand_CardCount = 0;
boolean player_FirstHand_Stand = false;
boolean player_SecondHand_Stand = false;
boolean player_FirstHand_Double = false;
boolean player_SecondHand_Double = false;
boolean player_FirstHand_Bust = false;
boolean player_SecondHand_Bust = false;
int player_FirstHand_Bet = 0;
int player_SecondHand_Bet = 0;

int numberOfGamesPlayed = 0;
int numberOfGamesWon = 0;
int numberOfGamesLost = 0;
int numberOfGamesPush = 0;
int insurance = 0;

boolean endOfHand = false;
/************************************************************************************************************************************************************************************************************************************/

void setup() { 
  
  lcd.init();  
  lcd.start(); 
  lcd.orientation(SG_PORTRAIT_LOW);
  lcd.baudChange(SG_BAUD6);      
  lcd.SDFopenDir("blackjack");

 // randomSeed(11);
  randomSeed(analogRead(3));
  
 
  //Obtain screen resolution
  lcd.getWidth(&LCD_WIDTH);
  lcd.getHeight(&LCD_HEIGHT);

  MAX_X_PORTRAIT = LCD_HEIGHT-1;
  MAX_Y_PORTRAIT = LCD_WIDTH-1;
  MAX_X_LANDSCAPE= LCD_WIDTH-1;
  MAX_Y_LANDSCAPE= LCD_HEIGHT-1;
}

void loop() {
  
  int initDelay = 0;
  
  purse = 1000; 
  handInPlay = FIRST_HAND;
  dealer_CardCount = 0;
  player_Split = false;
  player_FirstHand_CardCount = 0;
  player_SecondHand_CardCount = 0;
  player_FirstHand_Stand = false;
  player_SecondHand_Stand = false;
  player_FirstHand_Double = false;
  player_SecondHand_Double = false;
  player_FirstHand_Bust = false;
  player_SecondHand_Bust = false;
  player_SecondHand_Bet = 0;
  insurance = 0;

  currentBetInit = 0;
  currentBetTotal = 0;
  player_FirstHand_Bet = 0;
  currentWin = 0;
 
  lcd.setTextSize(SG_FONT1);
  lcd.setTextColour(SG_WHITE);
  
  if (showOptions) {
    
    lcd.imageJPGSD(0, 0, SG_SCALE1_1, "splash2");
    lcd.objCheckbox(CHK_ALLOW_SPLIT_LEFT, CHK_ALLOW_SPLIT_TOP, CHK_SIZE, chkAllowSplit ); 
    lcd.string(CHK_ALLOW_SPLIT_CAPTION_LEFT, CHK_ALLOW_SPLIT_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Allow split?", 0);
    lcd.objCheckbox(CHK_DOUBLE_ON_SPLIT_LEFT, CHK_DOUBLE_ON_SPLIT_TOP, CHK_SIZE, chkDoubleOnSplit ); 
    lcd.string(CHK_DOUBLE_ON_SPLIT_CAPTION_LEFT, CHK_DOUBLE_ON_SPLIT_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Double on split?", 0);
    lcd.objCheckbox(CHK_BLACKJACK_PAYS_322_LEFT, CHK_BLACKJACK_PAYS_322_TOP, CHK_SIZE, chkBlackjackPays322 ); 
    lcd.string(CHK_BLACKJACK_PAYS_322_CAPTION_LEFT, CHK_BLACKJACK_PAYS_322_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Blackjack pays 3 to 2?", 0);
    
  }
  else {

    lcd.imageJPGSD(0, 0, SG_SCALE1_1, "splash");
    
  }

  lcd.drawRoundRect(BUTTONS_OPTIONS_LEFT, BUTTONS_OPTIONS_TOP, BUTTONS_OPTIONS_LEFT + BUTTONS_OPTIONS_WIDTH, BUTTONS_OPTIONS_TOP + BUTTONS_OPTIONS_HEIGHT, radius5, SG_WHITE, hollowFill);
  lcd.string(BUTTONS_OPTIONS_LEFT + 15, BUTTONS_OPTIONS_TOP + 8, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Options", 0);
  lcd.drawRoundRect(BUTTONS_PLAY_GAME_LEFT, BUTTONS_PLAY_GAME_TOP, BUTTONS_PLAY_GAME_LEFT + BUTTONS_PLAY_GAME_WIDTH, BUTTONS_PLAY_GAME_TOP + BUTTONS_PLAY_GAME_HEIGHT, radius5, SG_WHITE, hollowFill);
  lcd.string(BUTTONS_PLAY_GAME_LEFT + 24, BUTTONS_PLAY_GAME_TOP + 8, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Start", 0);

  while (true) {
    
    if (lcd.touchScreen(&point) == SG_VALID) {  
    
        if (point.x >= CHK_ALLOW_SPLIT_LEFT && point.x <= CHK_ALLOW_SPLIT_LEFT + CHK_SIZE && point.y >= CHK_ALLOW_SPLIT_TOP && point.y <= CHK_ALLOW_SPLIT_TOP + CHK_SIZE)                                                 { chkAllowSplit = (chkAllowSplit == SG_SELECTED ? SG_DESELECTED : SG_SELECTED); lcd.objCheckbox(CHK_ALLOW_SPLIT_LEFT, CHK_ALLOW_SPLIT_TOP, CHK_SIZE, chkAllowSplit ); }
        else if (point.x >= CHK_DOUBLE_ON_SPLIT_LEFT && point.x <= CHK_DOUBLE_ON_SPLIT_LEFT + CHK_SIZE && point.y >= CHK_DOUBLE_ON_SPLIT_TOP && point.y <= CHK_DOUBLE_ON_SPLIT_TOP + CHK_SIZE)                            { chkDoubleOnSplit = (chkDoubleOnSplit == SG_SELECTED ? SG_DESELECTED : SG_SELECTED); lcd.objCheckbox(CHK_DOUBLE_ON_SPLIT_LEFT, CHK_DOUBLE_ON_SPLIT_TOP, CHK_SIZE, chkDoubleOnSplit ); }
        else if (point.x >= CHK_BLACKJACK_PAYS_322_LEFT && point.x <= CHK_BLACKJACK_PAYS_322_LEFT + CHK_SIZE && point.y >= CHK_BLACKJACK_PAYS_322_TOP && point.y <= CHK_BLACKJACK_PAYS_322_TOP + CHK_SIZE)                { chkBlackjackPays322 = (chkBlackjackPays322 == SG_SELECTED ? SG_DESELECTED : SG_SELECTED); lcd.objCheckbox(CHK_BLACKJACK_PAYS_322_LEFT, CHK_BLACKJACK_PAYS_322_TOP, CHK_SIZE, chkBlackjackPays322 ); }
        else if (point.x >= BUTTONS_OPTIONS_LEFT && point.x <= BUTTONS_OPTIONS_LEFT + BUTTONS_OPTIONS_WIDTH && point.y >= BUTTONS_OPTIONS_TOP && point.y <= BUTTONS_OPTIONS_TOP + BUTTONS_OPTIONS_HEIGHT)                 { showOptions = !showOptions; break; }
        else if (point.x >= BUTTONS_PLAY_GAME_LEFT && point.x <= BUTTONS_PLAY_GAME_LEFT + BUTTONS_PLAY_GAME_WIDTH && point.y >= BUTTONS_PLAY_GAME_TOP && point.y <= BUTTONS_PLAY_GAME_TOP + BUTTONS_PLAY_GAME_HEIGHT)     { playGame_Loop(); break; }
  
    }      
      
    delay(100);
    
    if (!showOptions) {
        
      if (initDelay < 25) {
         
        initDelay++;
        
      }
      else {
        
        lcd.setTextSize(SG_FONT0);
        lcd.setTextColour(GREY7);
        lcd.string(URL_LEFT, URL_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "bloggingadeadhorse.com/blackjack.php", 0);
        
      }
      
    }

  }    

}

void playGame_Loop() {
  
  boolean endOfGame = false;
  
  while (!endOfGame) {
    
    endOfHand = false;
    buttonMode = SHOW_BET_BUTTONS;
    
    handInPlay = FIRST_HAND;
    dealer_CardCount = 0;
    player_Split = false;
    player_FirstHand_CardCount = 0;
    player_SecondHand_CardCount = 0;
    player_FirstHand_Stand = false;
    player_SecondHand_Stand = false;
    player_FirstHand_Double = false;
    player_SecondHand_Double = false;
    player_FirstHand_Bust = false;
    player_SecondHand_Bust = false;
    player_SecondHand_Bet = 0;
    insurance = 0;
  
    currentBetInit = 0;
    currentBetTotal = 0;
    player_FirstHand_Bet = 0;
    currentWin = 0;
  
   
    
    lcd.setEraseBackColour(SG_BLACK);
    lcd.erase();
    lcd.drawRectangle(0, STATUS_LOWER_TOP, MAX_X_PORTRAIT, STATUS_HEIGHT, TABLE_GREEN, solidFill);
  
    lcd.setTextSize(SG_FONT1);
    lcd.setTextColour(SG_BLACK);
  
    drawButtons();
  
    for (byte x=0; x<52; x++) {
      
      cards[x]=0;
      
    }
  
    for (byte x=0; x<12; x++) {
      
      dealer[x]=0;
      player_FirstHand[x]=0;
      player_SecondHand[x]=0;
      
    }
      
    while (!endOfHand) {
      
      if (lcd.touchScreen(&point) == SG_VALID) {         
        
        if (buttonMode == SHOW_BET_BUTTONS && currentBetInit <= 199 && purse >= 1 && point.x >= BUTTONS_1_LEFT && point.x <= BUTTONS_1_LEFT + BUTTONS_1_WIDTH && point.y >= BUTTONS_1_TOP && point.y <= BUTTONS_1_TOP + BUTTONS_1_HEIGHT)                                                    { currentBetInit = currentBetInit + 1; currentBetTotal = currentBetInit; player_FirstHand_Bet = currentBetInit; purse = purse - 1; drawButtons(); }
        else if (buttonMode == SHOW_BET_BUTTONS && currentBetInit <= 195 && purse >= 5 && point.x >= BUTTONS_5_LEFT && point.x <= BUTTONS_5_LEFT + BUTTONS_5_WIDTH && point.y >= BUTTONS_5_TOP && point.y <= BUTTONS_5_TOP + BUTTONS_5_HEIGHT)                                               { currentBetInit = currentBetInit + 5; currentBetTotal = currentBetInit; player_FirstHand_Bet = currentBetInit; purse = purse - 5; drawButtons(); }
        else if (buttonMode == SHOW_BET_BUTTONS && currentBetInit <= 190 && purse >= 10 && point.x >= BUTTONS_10_LEFT && point.x <= BUTTONS_10_LEFT + BUTTONS_10_WIDTH && point.y >= BUTTONS_10_TOP && point.y <= BUTTONS_10_TOP + BUTTONS_10_HEIGHT)                                        { currentBetInit = currentBetInit + 10; currentBetTotal = currentBetInit; player_FirstHand_Bet = currentBetInit; purse = purse - 10; drawButtons(); }
        else if (buttonMode == SHOW_BET_BUTTONS && currentBetInit <= 175 && purse >= 25 && point.x >= BUTTONS_25_LEFT && point.x <= BUTTONS_25_LEFT + BUTTONS_25_WIDTH && point.y >= BUTTONS_25_TOP && point.y <= BUTTONS_25_TOP + BUTTONS_25_HEIGHT)                                        { currentBetInit = currentBetInit + 25; currentBetTotal = currentBetInit; player_FirstHand_Bet = currentBetInit; purse = purse - 25; drawButtons(); }
  
        else if (buttonMode == SHOW_BET_BUTTONS && currentBetInit > 0 && handInPlay != DEALER_HAND && point.x >= BUTTONS_CLEAR_LEFT && point.x <= BUTTONS_CLEAR_LEFT + BUTTONS_CLEAR_WIDTH && point.y >= BUTTONS_CLEAR_TOP && point.y <= BUTTONS_CLEAR_TOP + BUTTONS_CLEAR_HEIGHT)           { purse = purse + currentBetInit; currentBetInit = 0; currentBetTotal = 0; player_FirstHand_Bet = 0; drawButtons(); }
        else if (buttonMode == SHOW_BET_BUTTONS && currentBetInit > 0 && handInPlay != DEALER_HAND && point.x >= BUTTONS_PLAY_LEFT && point.x <= BUTTONS_PLAY_LEFT + BUTTONS_PLAY_WIDTH && point.y >= BUTTONS_PLAY_TOP && point.y <= BUTTONS_PLAY_TOP + BUTTONS_PLAY_HEIGHT)                 { initialDeal(); }
  
  
  
        else if (buttonMode == SHOW_INSURANCE_BUTTONS && (insurance + 1) <= (currentBetInit / 2) && purse >= 1 && point.x >= BUTTONS_1_LEFT && point.x <= BUTTONS_1_LEFT + BUTTONS_1_WIDTH && point.y >= BUTTONS_1_TOP && point.y <= BUTTONS_1_TOP + BUTTONS_1_HEIGHT)                       { insurance = insurance + 1; currentBetTotal = currentBetTotal + 1; purse = purse - 1; drawPlayerScores(); drawButtons(); }
        else if (buttonMode == SHOW_INSURANCE_BUTTONS && (insurance + 5) <= (currentBetInit / 2) && purse >= 5 && point.x >= BUTTONS_5_LEFT && point.x <= BUTTONS_5_LEFT + BUTTONS_5_WIDTH && point.y >= BUTTONS_5_TOP && point.y <= BUTTONS_5_TOP + BUTTONS_5_HEIGHT)                       { insurance = insurance + 5; currentBetTotal = currentBetTotal + 5; purse = purse - 5; drawPlayerScores(); drawButtons(); }
        else if (buttonMode == SHOW_INSURANCE_BUTTONS && (insurance + 10) <= (currentBetInit / 2) && purse >= 10 && point.x >= BUTTONS_10_LEFT && point.x <= BUTTONS_10_LEFT + BUTTONS_10_WIDTH && point.y >= BUTTONS_10_TOP && point.y <= BUTTONS_10_TOP + BUTTONS_10_HEIGHT)               { insurance = insurance + 10; currentBetTotal = currentBetTotal + 10; purse = purse - 10; drawPlayerScores(); drawButtons(); }
        else if (buttonMode == SHOW_INSURANCE_BUTTONS && (insurance + 25) <= (currentBetInit / 2) && purse >= 25 && point.x >= BUTTONS_25_LEFT && point.x <= BUTTONS_25_LEFT + BUTTONS_25_WIDTH && point.y >= BUTTONS_25_TOP && point.y <= BUTTONS_25_TOP + BUTTONS_25_HEIGHT)               { insurance = insurance + 25; currentBetTotal = currentBetTotal + 25; purse = purse - 25; drawPlayerScores(); drawButtons(); }
  
        else if (buttonMode == SHOW_INSURANCE_BUTTONS && currentBetInit > 0 && handInPlay != DEALER_HAND && point.x >= BUTTONS_CLEAR_LEFT && point.x <= BUTTONS_CLEAR_LEFT + BUTTONS_CLEAR_WIDTH && point.y >= BUTTONS_CLEAR_TOP && point.y <= BUTTONS_CLEAR_TOP + BUTTONS_CLEAR_HEIGHT)     { purse = purse + insurance; currentBetTotal = currentBetTotal - insurance; insurance = 0; drawPlayerScores(); drawButtons(); }
        else if (buttonMode == SHOW_INSURANCE_BUTTONS && currentBetInit > 0 && handInPlay != DEALER_HAND && point.x >= BUTTONS_PLAY_LEFT && point.x <= BUTTONS_PLAY_LEFT + BUTTONS_PLAY_WIDTH && point.y >= BUTTONS_PLAY_TOP && point.y <= BUTTONS_PLAY_TOP + BUTTONS_PLAY_HEIGHT)           { drawPlayerScores(); playInsurance(); }
  
  
        else if (buttonMode == SHOW_GAME_PLAY_BUTTONS && point.x >= BUTTONS_HITME_LEFT && point.x <= BUTTONS_HITME_LEFT + BUTTONS_HITME_WIDTH && point.y >= BUTTONS_HITME_TOP && point.y <= BUTTONS_HITME_TOP + BUTTONS_HITME_HEIGHT)                                                        { hitMe(); }
        
        else if ((chkDoubleOnSplit == SG_SELECTED) && currentBetInit <= purse && ((player_FirstHand_CardCount == 2 && handInPlay == FIRST_HAND) || (player_SecondHand_CardCount == 2 && handInPlay == SECOND_HAND)) && buttonMode == SHOW_GAME_PLAY_BUTTONS && 
                  currentBetInit <= purse && point.x >= BUTTONS_DOUBLE_LEFT && point.x <= BUTTONS_DOUBLE_LEFT + BUTTONS_DOUBLE_WIDTH && point.y >= BUTTONS_DOUBLE_TOP && point.y <= BUTTONS_DOUBLE_TOP + BUTTONS_DOUBLE_HEIGHT)                                                              { doubleUp(); }
        else if ((chkDoubleOnSplit == SG_DESELECTED) && currentBetInit <= purse && player_FirstHand_CardCount == 2 && handInPlay == FIRST_HAND && buttonMode == SHOW_GAME_PLAY_BUTTONS && currentBetInit <= purse && point.x >= BUTTONS_DOUBLE_LEFT && 
                  point.x <= BUTTONS_DOUBLE_LEFT + BUTTONS_DOUBLE_WIDTH && point.y >= BUTTONS_DOUBLE_TOP && point.y <= BUTTONS_DOUBLE_TOP + BUTTONS_DOUBLE_HEIGHT)                                                                                                                           { doubleUp(); }
        else if (buttonMode == SHOW_GAME_PLAY_BUTTONS && point.x >= BUTTONS_STAND_LEFT && point.x <= BUTTONS_STAND_LEFT + BUTTONS_STAND_WIDTH && point.y >= BUTTONS_STAND_TOP && point.y <= BUTTONS_STAND_TOP + BUTTONS_STAND_HEIGHT)                                                        { playNextHand(); }
        else if (buttonMode == SHOW_GAME_PLAY_BUTTONS && currentBetInit <= purse && player_Split && point.x >= BUTTONS_SPLIT_LEFT && point.x <= BUTTONS_SPLIT_LEFT + BUTTONS_SPLIT_WIDTH && point.y >= BUTTONS_SPLIT_TOP && point.y <= BUTTONS_SPLIT_TOP + BUTTONS_SPLIT_HEIGHT)             { split(); }
        else if (buttonMode == SHOW_END_OF_GAME_BUTTONS && point.x >= BUTTONS_CONTINUE_LEFT && point.x <= BUTTONS_CONTINUE_LEFT + BUTTONS_CONTINUE_WIDTH && point.y >= BUTTONS_CONTINUE_TOP && point.y <= BUTTONS_CONTINUE_TOP + BUTTONS_CONTINUE_HEIGHT)                                    { endOfHand = true; }
        else if (buttonMode == SHOW_END_OF_GAME_BUTTONS && point.x >= BUTTONS_QUIT_LEFT && point.x <= BUTTONS_QUIT_LEFT + BUTTONS_QUIT_WIDTH && point.y >= BUTTONS_QUIT_TOP && point.y <= BUTTONS_QUIT_TOP + BUTTONS_QUIT_HEIGHT)                                                            { endOfHand = true; endOfGame = true; }

      }
    
    
      // Use has run out of money !
      
      if (purse == 0 && endOfHand) {

        lcd.imageJPGSD(0, 0, SG_SCALE1_1, "splash3");
        
        delay(3000);
        
        lcd.setTextSize(SG_FONT1);
        lcd.setTextColour(SG_WHITE);
        lcd.drawRoundRect(BUTTONS_END_SPLASH_LEFT, BUTTONS_END_SPLASH_TOP, BUTTONS_END_SPLASH_LEFT + BUTTONS_END_SPLASH_WIDTH, BUTTONS_END_SPLASH_TOP + BUTTONS_END_SPLASH_HEIGHT, radius5, SG_WHITE, hollowFill);
        lcd.string(BUTTONS_END_SPLASH_LEFT + 16, BUTTONS_END_SPLASH_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Continue", 0);

        while (true) {
      
          if (lcd.touchScreen(&point) == SG_VALID) {         

            if (point.x >= BUTTONS_END_SPLASH_LEFT && point.x <= BUTTONS_END_SPLASH_LEFT + BUTTONS_END_SPLASH_WIDTH && point.y >= BUTTONS_END_SPLASH_TOP && point.y <= BUTTONS_END_SPLASH_TOP + BUTTONS_END_SPLASH_HEIGHT) {
           
              endOfHand = true;
              endOfGame = true; 
              break;
              
            }
            
          }
          
        }
        
      }
    
    
      // Use has broken the bank !
      
      if (purse >= 10000 && endOfHand) {

        lcd.imageJPGSD(0, 0, SG_SCALE1_1, "splash4");
        
        delay(3000);
        
        lcd.setTextSize(SG_FONT1);
        lcd.setTextColour(SG_WHITE);
        lcd.drawRoundRect(BUTTONS_END_SPLASH_LEFT, BUTTONS_END_SPLASH_TOP, BUTTONS_END_SPLASH_LEFT + BUTTONS_END_SPLASH_WIDTH, BUTTONS_END_SPLASH_TOP + BUTTONS_END_SPLASH_HEIGHT, radius5, SG_WHITE, hollowFill);
        lcd.string(BUTTONS_END_SPLASH_LEFT + 16, BUTTONS_END_SPLASH_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Continue", 0);

        while (true) {
      
          if (lcd.touchScreen(&point) == SG_VALID) {         

            if (point.x >= BUTTONS_END_SPLASH_LEFT && point.x <= BUTTONS_END_SPLASH_LEFT + BUTTONS_END_SPLASH_WIDTH && point.y >= BUTTONS_END_SPLASH_TOP && point.y <= BUTTONS_END_SPLASH_TOP + BUTTONS_END_SPLASH_HEIGHT) {
           
              endOfHand = true;
              endOfGame = true; 
              break;
              
            }
            
          }
          
        }
        
      }
    
      delay(100);  
        
    }
    
  }
  
}
