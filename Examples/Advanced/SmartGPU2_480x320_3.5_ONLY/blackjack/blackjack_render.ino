

void drawButtons() {
  
  lcd.setTextSize(FONT1);
  lcd.drawRectangle(0, BUTTONS_TOP, MAX_X_PORTRAIT, BUTTONS_TOP + BUTTONS_HEIGHT, TABLE_GREEN, solidFill);

  if (buttonMode == SHOW_GAME_PLAY_BUTTONS) {
    
    lcd.setTextColour(handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_HITME_LEFT, BUTTONS_HITME_TOP, BUTTONS_HITME_LEFT + BUTTONS_HITME_WIDTH, BUTTONS_HITME_TOP + BUTTONS_HITME_HEIGHT, radius5, (handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_HITME_LEFT + 12, BUTTONS_HITME_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Hit Me", 0);

    lcd.setTextColour(handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_STAND_LEFT, BUTTONS_STAND_TOP, BUTTONS_STAND_LEFT + BUTTONS_STAND_WIDTH, BUTTONS_STAND_TOP + BUTTONS_STAND_HEIGHT, radius5, (handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_STAND_LEFT + 12, BUTTONS_STAND_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);

    if (chkDoubleOnSplit == SELECTED) {
  
      lcd.setTextColour(currentBetInit <= purse && ((player_FirstHand_CardCount == 2 && handInPlay == FIRST_HAND) || (player_SecondHand_CardCount == 2 && handInPlay == SECOND_HAND)) ? WHITE : GREY5);
      lcd.drawRoundRect(BUTTONS_DOUBLE_LEFT, BUTTONS_DOUBLE_TOP, BUTTONS_DOUBLE_LEFT + BUTTONS_DOUBLE_WIDTH, BUTTONS_DOUBLE_TOP + BUTTONS_DOUBLE_HEIGHT, radius5, (currentBetInit <= purse && ((player_FirstHand_CardCount == 2 && handInPlay == FIRST_HAND) || (player_SecondHand_CardCount == 2 && handInPlay == SECOND_HAND)) ? WHITE : GREY5), hollowFill);
      lcd.string(BUTTONS_DOUBLE_LEFT + 11, BUTTONS_DOUBLE_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Double", 0);

    }
    else {
  
      lcd.setTextColour(currentBetInit <= purse && player_FirstHand_CardCount == 2 && handInPlay == FIRST_HAND ? WHITE : GREY5);
      lcd.drawRoundRect(BUTTONS_DOUBLE_LEFT, BUTTONS_DOUBLE_TOP, BUTTONS_DOUBLE_LEFT + BUTTONS_DOUBLE_WIDTH, BUTTONS_DOUBLE_TOP + BUTTONS_DOUBLE_HEIGHT, radius5, (currentBetInit <= purse && player_FirstHand_CardCount == 2 && handInPlay == FIRST_HAND ? WHITE : GREY5), hollowFill);
      lcd.string(BUTTONS_DOUBLE_LEFT + 11, BUTTONS_DOUBLE_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Double", 0);

    }
    
    lcd.setTextColour(currentBetInit <= purse && player_Split && handInPlay != DEALER_HAND && (chkAllowSplit == SELECTED) ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_SPLIT_LEFT, BUTTONS_SPLIT_TOP, BUTTONS_SPLIT_LEFT + BUTTONS_SPLIT_WIDTH, BUTTONS_SPLIT_TOP + BUTTONS_SPLIT_HEIGHT, radius5, (currentBetInit <= purse && player_Split && handInPlay != DEALER_HAND && (chkAllowSplit == SELECTED) ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_SPLIT_LEFT + 18, BUTTONS_SPLIT_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Split", 0);
  
  }

  if (buttonMode == SHOW_GAME_PLAY_BUTTONS_DISABLED) {
    
    lcd.setTextColour(GREY5);
    lcd.drawRoundRect(BUTTONS_HITME_LEFT, BUTTONS_HITME_TOP, BUTTONS_HITME_LEFT + BUTTONS_HITME_WIDTH, BUTTONS_HITME_TOP + BUTTONS_HITME_HEIGHT, radius5, GREY5, hollowFill);
    lcd.drawRoundRect(BUTTONS_STAND_LEFT, BUTTONS_STAND_TOP, BUTTONS_STAND_LEFT + BUTTONS_STAND_WIDTH, BUTTONS_STAND_TOP + BUTTONS_STAND_HEIGHT, radius5, GREY5, hollowFill);
    lcd.drawRoundRect(BUTTONS_DOUBLE_LEFT, BUTTONS_DOUBLE_TOP, BUTTONS_DOUBLE_LEFT + BUTTONS_DOUBLE_WIDTH, BUTTONS_DOUBLE_TOP + BUTTONS_DOUBLE_HEIGHT, radius5, GREY5, hollowFill);
    lcd.drawRoundRect(BUTTONS_SPLIT_LEFT, BUTTONS_SPLIT_TOP, BUTTONS_SPLIT_LEFT + BUTTONS_SPLIT_WIDTH, BUTTONS_SPLIT_TOP + BUTTONS_SPLIT_HEIGHT, radius5, GREY5, hollowFill);
    lcd.string(BUTTONS_HITME_LEFT + 12, BUTTONS_HITME_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Hit Me", 0);
    lcd.string(BUTTONS_STAND_LEFT + 12, BUTTONS_STAND_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
    lcd.string(BUTTONS_DOUBLE_LEFT + 11, BUTTONS_DOUBLE_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Double", 0);
    lcd.string(BUTTONS_SPLIT_LEFT + 18, BUTTONS_SPLIT_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Split", 0);
  
  }

  if (buttonMode == SHOW_BET_BUTTONS) {
  
    lcd.setTextColour(currentBetInit <= 199 && purse >= 1 && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_1_LEFT, BUTTONS_1_TOP, BUTTONS_1_LEFT + BUTTONS_1_WIDTH, BUTTONS_1_TOP + BUTTONS_1_HEIGHT, radius5, (currentBetInit <= 199 && purse >= 1 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_1_LEFT + 14, BUTTONS_1_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$1", 0);

    lcd.setTextColour(currentBetInit <= 195 && purse >= 5 && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_5_LEFT, BUTTONS_5_TOP, BUTTONS_5_LEFT + BUTTONS_5_WIDTH, BUTTONS_5_TOP + BUTTONS_5_HEIGHT, radius5, (currentBetInit <= 195 && purse >= 5 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_5_LEFT + 10, BUTTONS_5_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$5", 0);

    lcd.setTextColour(currentBetInit <= 190 && purse >= 10 && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_10_LEFT, BUTTONS_10_TOP, BUTTONS_10_LEFT + BUTTONS_10_WIDTH, BUTTONS_10_TOP + BUTTONS_10_HEIGHT, radius5, (currentBetInit <= 190 && purse >= 10 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_10_LEFT + 8, BUTTONS_10_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$10", 0);

    lcd.setTextColour(currentBetInit <= 175 && purse >= 25 && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_25_LEFT, BUTTONS_25_TOP, BUTTONS_25_LEFT + BUTTONS_25_WIDTH, BUTTONS_25_TOP + BUTTONS_25_HEIGHT, radius5, (currentBetInit <= 175 && purse >= 25 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_25_LEFT + 6, BUTTONS_25_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$25", 0);

    lcd.setTextColour(currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_CLEAR_LEFT, BUTTONS_CLEAR_TOP, BUTTONS_CLEAR_LEFT + BUTTONS_CLEAR_WIDTH, BUTTONS_CLEAR_TOP + BUTTONS_CLEAR_HEIGHT, radius5, (currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_CLEAR_LEFT + 10, BUTTONS_CLEAR_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Clear", 0);

    lcd.setTextColour(currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_PLAY_LEFT, BUTTONS_PLAY_TOP, BUTTONS_PLAY_LEFT + BUTTONS_PLAY_WIDTH, BUTTONS_PLAY_TOP + BUTTONS_PLAY_HEIGHT, radius5, (currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_PLAY_LEFT + 14, BUTTONS_PLAY_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Play", 0);
  
  }
  
  if (buttonMode == SHOW_INSURANCE_BUTTONS) {
  
    lcd.setTextColour(purse >= 1 && (insurance + 1) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_1_LEFT, BUTTONS_1_TOP, BUTTONS_1_LEFT + BUTTONS_1_WIDTH, BUTTONS_1_TOP + BUTTONS_1_HEIGHT, radius5, (purse >= 1 && (insurance + 1) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_1_LEFT + 14, BUTTONS_1_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$1", 0);

    lcd.setTextColour(purse >= 5 && (insurance + 5) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_5_LEFT, BUTTONS_5_TOP, BUTTONS_5_LEFT + BUTTONS_5_WIDTH, BUTTONS_5_TOP + BUTTONS_5_HEIGHT, radius5, (purse >= 5 && (insurance + 5) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_5_LEFT + 10, BUTTONS_5_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$5", 0);

    lcd.setTextColour(purse >= 10 && (insurance + 10) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_10_LEFT, BUTTONS_10_TOP, BUTTONS_10_LEFT + BUTTONS_10_WIDTH, BUTTONS_10_TOP + BUTTONS_10_HEIGHT, radius5, (purse >= 10 && (insurance + 10) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_10_LEFT + 8, BUTTONS_10_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$10", 0);

    lcd.setTextColour(purse >= 25 && (insurance + 25) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_25_LEFT, BUTTONS_25_TOP, BUTTONS_25_LEFT + BUTTONS_25_WIDTH, BUTTONS_25_TOP + BUTTONS_25_HEIGHT, radius5, (purse >= 25 && (insurance + 25) <= (currentBetInit / 2) && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_25_LEFT + 6, BUTTONS_25_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "$25", 0);

    lcd.setTextColour(currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5);
    lcd.drawRoundRect(BUTTONS_CLEAR_LEFT, BUTTONS_CLEAR_TOP, BUTTONS_CLEAR_LEFT + BUTTONS_CLEAR_WIDTH, BUTTONS_CLEAR_TOP + BUTTONS_CLEAR_HEIGHT, radius5, (currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
    lcd.string(BUTTONS_CLEAR_LEFT + 10, BUTTONS_CLEAR_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Clear", 0);

    if (insurance > 0) {

      lcd.setTextColour(currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5);
      lcd.drawRoundRect(BUTTONS_PLAY_LEFT, BUTTONS_PLAY_TOP, BUTTONS_PLAY_LEFT + BUTTONS_PLAY_WIDTH, BUTTONS_PLAY_TOP + BUTTONS_PLAY_HEIGHT, radius5, (currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
      lcd.string(BUTTONS_PLAY_LEFT + 14, BUTTONS_PLAY_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Play", 0);
    
    }
    else {

      lcd.setTextColour(currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5);
      lcd.drawRoundRect(BUTTONS_PLAY_LEFT, BUTTONS_PLAY_TOP, BUTTONS_PLAY_LEFT + BUTTONS_PLAY_WIDTH, BUTTONS_PLAY_TOP + BUTTONS_PLAY_HEIGHT, radius5, (currentBetInit > 0 && handInPlay != DEALER_HAND ? WHITE : GREY5), hollowFill);
      lcd.string(BUTTONS_PLAY_LEFT + 14, BUTTONS_PLAY_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Skip", 0);
      
    }
    
  }
   
  if (buttonMode == SHOW_END_OF_GAME_BUTTONS) {

    lcd.setTextColour(WHITE);
    lcd.drawRoundRect(BUTTONS_QUIT_LEFT, BUTTONS_QUIT_TOP, BUTTONS_QUIT_LEFT + BUTTONS_QUIT_WIDTH, BUTTONS_QUIT_TOP + BUTTONS_QUIT_HEIGHT, radius5, WHITE, hollowFill);
    lcd.string(BUTTONS_QUIT_LEFT + 36, BUTTONS_QUIT_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Quit", 0);
    lcd.drawRoundRect(BUTTONS_CONTINUE_LEFT, BUTTONS_CONTINUE_TOP, BUTTONS_CONTINUE_LEFT + BUTTONS_CONTINUE_WIDTH, BUTTONS_CONTINUE_TOP + BUTTONS_CONTINUE_HEIGHT, radius5, WHITE, hollowFill);
    lcd.string(BUTTONS_CONTINUE_LEFT + 16, BUTTONS_CONTINUE_TOP + 9, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Continue", 0);
    
  }
  
  lcd.setTextSize(FONT0);

  lcd.drawRectangle(0, 0, MAX_X_PORTRAIT, STATUS_HEIGHT, BLACK, solidFill);
  lcd.drawRectangle(0, STATUS_LOWER_TOP, MAX_X_PORTRAIT, STATUS_LOWER_TOP + STATUS_HEIGHT, BLACK, solidFill);

  lcd.setTextColour(GREY3);
  lcd.string(STATUS_HANDS_PLAYED_CAPTION_LEFT, STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Hands Played", 0);
  lcd.string(STATUS_HANDS_WON_CAPTION_LEFT, STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Won", 0);
  lcd.string(STATUS_HANDS_LOST_CAPTION_LEFT, STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Lost", 0);
  lcd.string(STATUS_HANDS_PUSH_CAPTION_LEFT, STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Push", 0);


  lcd.setTextColour(GREY3);
  lcd.string(STATUS_BANK_CAPTION_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bank", 0);
  lcd.string(STATUS_INIT_BET_CAPTION_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Init Bet", 0);
  lcd.string(STATUS_TOTAL_BET_CAPTION_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Total Bet", 0);
  if (currentWin >= 0) { lcd.string(STATUS_WIN_CAPTION_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Win", 0); }
  if (currentWin < 0)  { lcd.string(STATUS_WIN_CAPTION_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Lose", 0); }
  
  lcd.setTextColour(GREY6);
  
  lcd.printNumber(STATUS_HANDS_PLAYED_VALUE_LEFT, STATUS_TEXT_OFFSET, numberOfGamesPlayed);
  lcd.printNumber(STATUS_HANDS_WON_VALUE_LEFT, STATUS_TEXT_OFFSET, numberOfGamesWon);
  lcd.printNumber(STATUS_HANDS_LOST_VALUE_LEFT, STATUS_TEXT_OFFSET, numberOfGamesLost);
  lcd.printNumber(STATUS_HANDS_PUSH_VALUE_LEFT, STATUS_TEXT_OFFSET, numberOfGamesPush);

  lcd.setTextColour(GREY6);
  lcd.printNumber(STATUS_BANK_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, purse);
  lcd.printNumber(STATUS_INIT_BET_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, currentBetInit);
  lcd.printNumber(STATUS_TOTAL_BET_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, currentBetTotal);
  
  if (currentWin > 0) { lcd.setTextColour(GREEN); }
  if (currentWin < 0) { lcd.setTextColour(RED); }
  lcd.printNumber(STATUS_WIN_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, currentWin);


}

void drawPlayerScores() {

  if (buttonMode == SHOW_INSURANCE_BUTTONS) {

    lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
    lcd.setTextColour(YELLOW);
    lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Insurance ?", 0);
    lcd.setTextColour(GREY6);
    lcd.printNumber(STATUS_LEFT_FIRSTHAND + 88, STATUS_MIDDLE_TOP + 5, insurance);
    
  }
  else {
      
    lcd.setTextSize(FONT0);
    lcd.drawRectangle(0, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT, STATUS_MIDDLE_TOP + STATUS_HEIGHT, TABLE_GREEN, solidFill);
  
    if (handInPlay == FIRST_HAND) {
  
      if (player_FirstHand_Double) {
  
        lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, STATUS_LEFT_FIRSTHAND + 185, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
        lcd.drawRectangle(STATUS_LEFT_FIRSTHAND + 185 + 5, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
        lcd.setTextColour(GREY3);
        lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
        lcd.setTextColour(GREY6);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 33, STATUS_MIDDLE_TOP + 5, player_FirstHand_Bet);
  
         if (calculateHand(PLAYER, FIRST_HAND, false) > 21) {
           
          lcd.setTextColour(RED);
          lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bust !", 0);
          
         }
         else {
           
          if (player_FirstHand_Stand) {
  
            lcd.setTextColour(GREY3);
            lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
            lcd.setTextColour(GREY6);
            lcd.printNumber(STATUS_LEFT_FIRSTHAND + 106, STATUS_MIDDLE_TOP + 5, calculateHand(PLAYER, FIRST_HAND, true));
          
          }
          
        }
      
      }
      else {
  
        if (player_SecondHand_CardCount == 0) {
          
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, STATUS_LEFT_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING) + CARD_LARGE_WIDTH - 10, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING) + CARD_LARGE_WIDTH - 5, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
          
        }
        else {
  
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, STATUS_LEFT_FIRSTHAND + 185, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND + 185 + 5, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
   
        }
        
        lcd.setTextColour(GREY3);
        lcd.string(CARD_SMALL_LEFT_PLAYER_FIRSTHAND + 3, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
        lcd.setTextColour(GREY6);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 33, STATUS_MIDDLE_TOP + 5, player_FirstHand_Bet);
  
        if (player_SecondHand_CardCount > 0) {
          
          lcd.setTextColour(GREY3);
          lcd.string(STATUS_LEFT_FIRSTHAND + 185 + 12, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
          lcd.setTextColour(GREY6);
          lcd.printNumber(STATUS_LEFT_FIRSTHAND + 185 + 37, STATUS_MIDDLE_TOP + 5, player_SecondHand_Bet);
          
        }
  
        if (calculateHand(PLAYER, FIRST_HAND, false) > 21) {
           
          lcd.setTextColour(RED);
          lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bust !", 0);
          
        }
        else {
           
          if (player_FirstHand_Stand) {
  
            lcd.setTextColour(GREY3);
            lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
            lcd.setTextColour(GREY6);
            lcd.printNumber(STATUS_LEFT_FIRSTHAND + 106, STATUS_MIDDLE_TOP + 5, calculateHand(PLAYER, FIRST_HAND, true));
          
          }
          
        }
        
      }
      
    }
      
    if (handInPlay == SECOND_HAND) {
  
      lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, STATUS_LEFT_SECONDHAND - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
      lcd.drawRectangle(STATUS_LEFT_SECONDHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
      lcd.setTextColour(GREY3);
      lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
      lcd.string(STATUS_LEFT_SECONDHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
      lcd.setTextColour(GREY6);
      lcd.printNumber(STATUS_LEFT_FIRSTHAND + 33, STATUS_MIDDLE_TOP + 5, player_FirstHand_Bet);
      lcd.printNumber(STATUS_LEFT_SECONDHAND + 33, STATUS_MIDDLE_TOP + 5, player_SecondHand_Bet);
  
      if (player_FirstHand_Bust) {
  
        lcd.setTextColour(RED);
        lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bust !", 0);
      
      }
      else {
  
        lcd.setTextColour(GREY3);
        lcd.string(STATUS_LEFT_FIRSTHAND + 58, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
        lcd.setTextColour(GREY6);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 96, STATUS_MIDDLE_TOP + 5, calculateHand(PLAYER, FIRST_HAND, true));
      
      }
    
    }
      
    if (handInPlay == DEALER_HAND) {
  
      if (player_SecondHand_CardCount == 0) {
  
        if (player_FirstHand_Double) {
        
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, STATUS_LEFT_FIRSTHAND + 185, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND + 185 + 5, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
          lcd.setTextColour(GREY3);
          lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
          lcd.setTextColour(GREY6);
          lcd.printNumber(STATUS_LEFT_FIRSTHAND + 33, STATUS_MIDDLE_TOP + 5, player_FirstHand_Bet);
  
          if (player_FirstHand_Bust) {
  
            lcd.setTextColour(RED);
            lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bust !", 0);
      
          }
          else {
  
            lcd.setTextColour(GREY3);
            lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
            lcd.setTextColour(GREY6);
            lcd.printNumber(STATUS_LEFT_FIRSTHAND + 106, STATUS_MIDDLE_TOP + 5, calculateHand(PLAYER, FIRST_HAND, true));
      
          }
          
        }
        else {
        
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, STATUS_LEFT_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING) + CARD_LARGE_WIDTH - 10, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
          lcd.drawRectangle(STATUS_LEFT_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING) + CARD_LARGE_WIDTH - 5, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
          lcd.setTextColour(GREY3);
          lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
          lcd.setTextColour(GREY6);
          lcd.printNumber(STATUS_LEFT_FIRSTHAND + 33, STATUS_MIDDLE_TOP + 5, player_FirstHand_Bet);
  
          if (player_FirstHand_Bust) {
  
            lcd.setTextColour(RED);
            lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bust !", 0);
      
          }
          else {
  
            lcd.setTextColour(GREY3);
            lcd.string(STATUS_LEFT_FIRSTHAND + 68, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
            lcd.setTextColour(GREY6);
            lcd.printNumber(STATUS_LEFT_FIRSTHAND + 106, STATUS_MIDDLE_TOP + 5, calculateHand(PLAYER, FIRST_HAND, true));
      
          }
          
        }
      
      }
  
      if (player_SecondHand_CardCount > 0) {
        
        lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, STATUS_LEFT_SECONDHAND - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
        lcd.drawRectangle(STATUS_LEFT_SECONDHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, BLACK, solidFill);
        lcd.setTextColour(GREY3);
        lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
        lcd.string(STATUS_LEFT_SECONDHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bet", 0);
        lcd.setTextColour(GREY6);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 33, STATUS_MIDDLE_TOP + 5, player_FirstHand_Bet);
        lcd.printNumber(STATUS_LEFT_SECONDHAND + 33, STATUS_MIDDLE_TOP + 5, player_FirstHand_Bet);
  
        if (player_FirstHand_Bust) {
  
          lcd.setTextColour(GREY6);
          lcd.string(STATUS_LEFT_FIRSTHAND + 58, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bust !", 0);
      
        }
        else {
  
          lcd.setTextColour(GREY3);
          lcd.string(STATUS_LEFT_FIRSTHAND + 58, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
          lcd.setTextColour(GREY6);
          lcd.printNumber(STATUS_LEFT_FIRSTHAND + 96, STATUS_MIDDLE_TOP + 5, calculateHand(PLAYER, FIRST_HAND, true));
      
        }
  
        if (player_SecondHand_Bust) {
  
          lcd.setTextColour(GREY6);
          lcd.string(STATUS_LEFT_SECONDHAND + 58, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Bust !", 0);
      
        }
        else {
  
          lcd.setTextColour(GREY3);
          lcd.string(STATUS_LEFT_SECONDHAND + 58, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Stand", 0);
          lcd.setTextColour(GREY6);
          lcd.printNumber(STATUS_LEFT_SECONDHAND + 96, STATUS_MIDDLE_TOP + 5, calculateHand(PLAYER, SECOND_HAND, true));
      
        }
      
      }
    
    }
    
  }

}

void showDealerCards() {

  delay(250);
  drawCard(CARD_LARGE_LEFT_DEALER + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, dealer[1], false, true);   
  delay(2000);
  drawCard(CARD_LARGE_LEFT_DEALER, CARD_LARGE_TOP_DEALER, 52, false, true);   
  drawCard(CARD_LARGE_LEFT_DEALER + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, 52, false, true);   

}

void highlightWin(int win, int purseInc) {
  
  byte oldButtonMode = buttonMode;
  buttonMode = SHOW_GAME_PLAY_BUTTONS_DISABLED; 
  drawButtons();
  
  currentWin = currentWin + win;
  purse = purse + purseInc;

  lcd.setTextColour(GREY6);
  lcd.drawRectangle(STATUS_BANK_VALUE_LEFT, STATUS_LOWER_TOP, STATUS_INIT_BET_CAPTION_LEFT - 1, MAX_Y_PORTRAIT, BLACK, solidFill);
  lcd.printNumber(STATUS_BANK_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, purse);

  lcd.setTextColour(GREY3);
  lcd.drawRectangle(STATUS_WIN_CAPTION_LEFT, STATUS_LOWER_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, BLACK, solidFill);
  lcd.string(STATUS_WIN_CAPTION_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Win", 0);

  for (int x=0; x< 3; x++) {
  
    lcd.setTextColour(GREEN);
    lcd.printNumber(STATUS_WIN_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, currentWin);
    delay(500);
    lcd.drawRectangle( STATUS_WIN_VALUE_LEFT, STATUS_LOWER_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, BLACK, solidFill);
    delay(500);

  }

  lcd.printNumber(STATUS_WIN_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, currentWin);
  buttonMode = oldButtonMode;
   
}

void highlightLoss(int loss) {

  byte oldButtonMode = buttonMode;
  buttonMode = SHOW_GAME_PLAY_BUTTONS_DISABLED; 
  drawButtons();

  currentWin = currentWin + loss;
  
  lcd.setTextColour(GREY3);
  lcd.drawRectangle(STATUS_WIN_CAPTION_LEFT, STATUS_LOWER_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, BLACK, solidFill);
  lcd.string(STATUS_WIN_CAPTION_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Lose", 0);

  for (int x=0; x< 3; x++) {
  
    lcd.setTextColour(RED);
    lcd.printNumber(STATUS_WIN_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, loss);
    delay(500);
    lcd.drawRectangle( STATUS_WIN_VALUE_LEFT, STATUS_LOWER_TOP, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, BLACK, solidFill);
    delay(500);

  }

  lcd.printNumber(STATUS_WIN_VALUE_LEFT, STATUS_LOWER_TOP + STATUS_TEXT_OFFSET, loss);
  buttonMode = oldButtonMode;

}


void drawFirstHand_Large() {

  for (int x=0; x< player_FirstHand_CardCount; x++) {
   
    if (x == player_FirstHand_CardCount - 1 && player_FirstHand_Double) {
  
      drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + (x * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, player_FirstHand[x], true, true);   
  
    }
    else {
  
      drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + (x * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, player_FirstHand[x], false, true);   
  
    }
    
  }
    
}

void drawFirstHand_Small() {

  for (int x=0; x< player_FirstHand_CardCount; x++) {
       
    if (x == player_FirstHand_CardCount - 1 && player_FirstHand_Double) {
      
      drawCard(CARD_SMALL_LEFT_PLAYER_FIRSTHAND + (x * CARD_SMALL_SPACING), CARD_SMALL_TOP_PLAYER, player_FirstHand[x], true, false);   
      
    }
    else {
      
      drawCard(CARD_SMALL_LEFT_PLAYER_FIRSTHAND + (x * CARD_SMALL_SPACING), CARD_SMALL_TOP_PLAYER, player_FirstHand[x], false, false);   
      
    }
        
  }
  
}


void drawSecondHand_Large() {

  for (int x=0; x< player_SecondHand_CardCount; x++) {
   
    if (x == player_FirstHand_CardCount - 1 && player_FirstHand_Double) {
  
      drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND + (x * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, player_SecondHand[x], true, true);   
  
    }
    else {
  
      drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND + (x * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, player_SecondHand[x], false, true);   
  
    }
    
  }
      
}


void drawSecondHand_Small() {
  
  for (int x=0; x< player_SecondHand_CardCount; x++) {
   
    if (x == player_FirstHand_CardCount - 1 && player_FirstHand_Double) {
  
      drawCard(CARD_SMALL_LEFT_PLAYER_SECONDHAND + (x * CARD_SMALL_SPACING), CARD_SMALL_TOP_PLAYER, player_SecondHand[x], true, false);   
  
    }
    else {
  
      drawCard(CARD_SMALL_LEFT_PLAYER_SECONDHAND + (x * CARD_SMALL_SPACING), CARD_SMALL_TOP_PLAYER, player_SecondHand[x], false, false);   
  
    }
    
  }
  
}


void drawCard(int xPos, int yPos, byte card, boolean rotated, boolean large) {
  
  if (large) {
    
    if (!rotated) {
      
      switch (card) {
        
        case 0:    drawCardLarge(xPos, yPos, "AS");   break;
        case 1:    drawCardLarge(xPos, yPos, "2S");   break;
        case 2:    drawCardLarge(xPos, yPos, "3S");   break;
        case 3:    drawCardLarge(xPos, yPos, "4S");   break;
        case 4:    drawCardLarge(xPos, yPos, "5S");   break;
        case 5:    drawCardLarge(xPos, yPos, "6S");   break;
        case 6:    drawCardLarge(xPos, yPos, "7S");   break;
        case 7:    drawCardLarge(xPos, yPos, "8S");   break;
        case 8:    drawCardLarge(xPos, yPos, "9S");   break;
        case 9:    drawCardLarge(xPos, yPos, "10S");  break;
        case 10:   drawCardLarge(xPos, yPos, "JS");   break;
        case 11:   drawCardLarge(xPos, yPos, "QS");   break;
        case 12:   drawCardLarge(xPos, yPos, "KS");   break;
  
        case 13:   drawCardLarge(xPos, yPos, "AC");   break;
        case 14:   drawCardLarge(xPos, yPos, "2C");   break;
        case 15:   drawCardLarge(xPos, yPos, "3C");   break;
        case 16:   drawCardLarge(xPos, yPos, "4C");   break;
        case 17:   drawCardLarge(xPos, yPos, "5C");   break;
        case 18:   drawCardLarge(xPos, yPos, "6C");   break;
        case 19:   drawCardLarge(xPos, yPos, "7C");   break;
        case 20:   drawCardLarge(xPos, yPos, "8C");   break;
        case 21:   drawCardLarge(xPos, yPos, "9C");   break;
        case 22:   drawCardLarge(xPos, yPos, "10C");  break;
        case 23:   drawCardLarge(xPos, yPos, "JC");   break;
        case 24:   drawCardLarge(xPos, yPos, "QC");   break;
        case 25:   drawCardLarge(xPos, yPos, "KC");   break;
        
        case 26:   drawCardLarge(xPos, yPos, "AD");   break;
        case 27:   drawCardLarge(xPos, yPos, "2D");   break;
        case 28:   drawCardLarge(xPos, yPos, "3D");   break;
        case 29:   drawCardLarge(xPos, yPos, "4D");   break;
        case 30:   drawCardLarge(xPos, yPos, "5D");   break;
        case 31:   drawCardLarge(xPos, yPos, "6D");   break;
        case 32:   drawCardLarge(xPos, yPos, "7D");   break;
        case 33:   drawCardLarge(xPos, yPos, "8D");   break;
        case 34:   drawCardLarge(xPos, yPos, "9D");   break;
        case 35:   drawCardLarge(xPos, yPos, "10D");  break;
        case 36:   drawCardLarge(xPos, yPos, "JD");   break;
        case 37:   drawCardLarge(xPos, yPos, "QD");   break;
        case 38:   drawCardLarge(xPos, yPos, "KD");   break;
        
        case 39:   drawCardLarge(xPos, yPos, "AH");   break;
        case 40:   drawCardLarge(xPos, yPos, "2H");   break;
        case 41:   drawCardLarge(xPos, yPos, "3H");   break;
        case 42:   drawCardLarge(xPos, yPos, "4H");   break;
        case 43:   drawCardLarge(xPos, yPos, "5H");   break;
        case 44:   drawCardLarge(xPos, yPos, "6H");   break;
        case 45:   drawCardLarge(xPos, yPos, "7H");   break;
        case 46:   drawCardLarge(xPos, yPos, "8H");   break;
        case 47:   drawCardLarge(xPos, yPos, "9H");   break;
        case 48:   drawCardLarge(xPos, yPos, "10H");  break;
        case 49:   drawCardLarge(xPos, yPos, "JH");   break;
        case 50:   drawCardLarge(xPos, yPos, "QH");   break;
        case 51:   drawCardLarge(xPos, yPos, "KH");   break;
  
        case 52:   drawCardLarge(xPos, yPos, "Blue_Back");   break;
        case 53:   drawCardLarge(xPos, yPos, "Red_Back");    break;
        
      }
  
    }
    else {
          
      switch (card) {
        
        case 0:    drawCardLarge_Rotated(xPos, yPos, "ASR");   break;
        case 1:    drawCardLarge_Rotated(xPos, yPos, "2SR");   break;
        case 2:    drawCardLarge_Rotated(xPos, yPos, "3SR");   break;
        case 3:    drawCardLarge_Rotated(xPos, yPos, "4SR");   break;
        case 4:    drawCardLarge_Rotated(xPos, yPos, "5SR");   break;
        case 5:    drawCardLarge_Rotated(xPos, yPos, "6SR");   break;
        case 6:    drawCardLarge_Rotated(xPos, yPos, "7SR");   break;
        case 7:    drawCardLarge_Rotated(xPos, yPos, "8SR");   break;
        case 8:    drawCardLarge_Rotated(xPos, yPos, "9SR");   break;
        case 9:    drawCardLarge_Rotated(xPos, yPos, "10SR");  break;
        case 10:   drawCardLarge_Rotated(xPos, yPos, "JSR");   break;
        case 11:   drawCardLarge_Rotated(xPos, yPos, "QSR");   break;
        case 12:   drawCardLarge_Rotated(xPos, yPos, "KSR");   break;
  
        case 13:   drawCardLarge_Rotated(xPos, yPos, "ACR");   break;
        case 14:   drawCardLarge_Rotated(xPos, yPos, "2CR");   break;
        case 15:   drawCardLarge_Rotated(xPos, yPos, "3CR");   break;
        case 16:   drawCardLarge_Rotated(xPos, yPos, "4CR");   break;
        case 17:   drawCardLarge_Rotated(xPos, yPos, "5CR");   break;
        case 18:   drawCardLarge_Rotated(xPos, yPos, "6CR");   break;
        case 19:   drawCardLarge_Rotated(xPos, yPos, "7CR");   break;
        case 20:   drawCardLarge_Rotated(xPos, yPos, "8CR");   break;
        case 21:   drawCardLarge_Rotated(xPos, yPos, "9CR");   break;
        case 22:   drawCardLarge_Rotated(xPos, yPos, "10CR");  break;
        case 23:   drawCardLarge_Rotated(xPos, yPos, "JCR");   break;
        case 24:   drawCardLarge_Rotated(xPos, yPos, "QCR");   break;
        case 25:   drawCardLarge_Rotated(xPos, yPos, "KCR");   break;
        
        case 26:   drawCardLarge_Rotated(xPos, yPos, "ADR");   break;
        case 27:   drawCardLarge_Rotated(xPos, yPos, "2DR");   break;
        case 28:   drawCardLarge_Rotated(xPos, yPos, "3DR");   break;
        case 29:   drawCardLarge_Rotated(xPos, yPos, "4DR");   break;
        case 30:   drawCardLarge_Rotated(xPos, yPos, "5DR");   break;
        case 31:   drawCardLarge_Rotated(xPos, yPos, "6DR");   break;
        case 32:   drawCardLarge_Rotated(xPos, yPos, "7DR");   break;
        case 33:   drawCardLarge_Rotated(xPos, yPos, "8DR");   break;
        case 34:   drawCardLarge_Rotated(xPos, yPos, "9DR");   break;
        case 35:   drawCardLarge_Rotated(xPos, yPos, "10DR");  break;
        case 36:   drawCardLarge_Rotated(xPos, yPos, "JDR");   break;
        case 37:   drawCardLarge_Rotated(xPos, yPos, "QDR");   break;
        case 38:   drawCardLarge_Rotated(xPos, yPos, "KDR");   break;
        
        case 39:   drawCardLarge_Rotated(xPos, yPos, "AHR");   break;
        case 40:   drawCardLarge_Rotated(xPos, yPos, "2HR");   break;
        case 41:   drawCardLarge_Rotated(xPos, yPos, "3HR");   break;
        case 42:   drawCardLarge_Rotated(xPos, yPos, "4HR");   break;
        case 43:   drawCardLarge_Rotated(xPos, yPos, "5HR");   break;
        case 44:   drawCardLarge_Rotated(xPos, yPos, "6HR");   break;
        case 45:   drawCardLarge_Rotated(xPos, yPos, "7HR");   break;
        case 46:   drawCardLarge_Rotated(xPos, yPos, "8HR");   break;
        case 47:   drawCardLarge_Rotated(xPos, yPos, "9HR");   break;
        case 48:   drawCardLarge_Rotated(xPos, yPos, "10HR");  break;
        case 49:   drawCardLarge_Rotated(xPos, yPos, "JHR");   break;
        case 50:   drawCardLarge_Rotated(xPos, yPos, "QHR");   break;
        case 51:   drawCardLarge_Rotated(xPos, yPos, "KHR");   break;
  
        case 52:   drawCardLarge_Rotated(xPos, yPos, "Blue_BackR");   break;
        case 53:   drawCardLarge_Rotated(xPos, yPos, "Red_BackR");    break;
  
      }
      
    }
    
  }
  
  if (!large) {
       
    if (!rotated) {
 
      switch (card) {
      
        case 0:    drawCardSmall(xPos, yPos, "AS");   break;
        case 1:    drawCardSmall(xPos, yPos, "2S");   break;
        case 2:    drawCardSmall(xPos, yPos, "3S");   break;
        case 3:    drawCardSmall(xPos, yPos, "4S");   break;
        case 4:    drawCardSmall(xPos, yPos, "5S");   break;
        case 5:    drawCardSmall(xPos, yPos, "6S");   break;
        case 6:    drawCardSmall(xPos, yPos, "7S");   break;
        case 7:    drawCardSmall(xPos, yPos, "8S");   break;
        case 8:    drawCardSmall(xPos, yPos, "9S");   break;
        case 9:    drawCardSmall(xPos, yPos, "10S");  break;
        case 10:   drawCardSmall(xPos, yPos, "JS");   break;
        case 11:   drawCardSmall(xPos, yPos, "QS");   break;
        case 12:   drawCardSmall(xPos, yPos, "KS");   break;

        case 13:   drawCardSmall(xPos, yPos, "AC");   break;
        case 14:   drawCardSmall(xPos, yPos, "2C");   break;
        case 15:   drawCardSmall(xPos, yPos, "3C");   break;
        case 16:   drawCardSmall(xPos, yPos, "4C");   break;
        case 17:   drawCardSmall(xPos, yPos, "5C");   break;
        case 18:   drawCardSmall(xPos, yPos, "6C");   break;
        case 19:   drawCardSmall(xPos, yPos, "7C");   break;
        case 20:   drawCardSmall(xPos, yPos, "8C");   break;
        case 21:   drawCardSmall(xPos, yPos, "9C");   break;
        case 22:   drawCardSmall(xPos, yPos, "10C");  break;
        case 23:   drawCardSmall(xPos, yPos, "JC");   break;
        case 24:   drawCardSmall(xPos, yPos, "QC");   break;
        case 25:   drawCardSmall(xPos, yPos, "KC");   break;
      
        case 26:   drawCardSmall(xPos, yPos, "AD");   break;
        case 27:   drawCardSmall(xPos, yPos, "2D");   break;
        case 28:   drawCardSmall(xPos, yPos, "3D");   break;
        case 29:   drawCardSmall(xPos, yPos, "4D");   break;
        case 30:   drawCardSmall(xPos, yPos, "5D");   break;
        case 31:   drawCardSmall(xPos, yPos, "6D");   break;
        case 32:   drawCardSmall(xPos, yPos, "7D");   break;
        case 33:   drawCardSmall(xPos, yPos, "8D");   break;
        case 34:   drawCardSmall(xPos, yPos, "9D");   break;
        case 35:   drawCardSmall(xPos, yPos, "10D");  break;
        case 36:   drawCardSmall(xPos, yPos, "JD");   break;
        case 37:   drawCardSmall(xPos, yPos, "QD");   break;
        case 38:   drawCardSmall(xPos, yPos, "KD");   break;
      
        case 39:   drawCardSmall(xPos, yPos, "AH");   break;
        case 40:   drawCardSmall(xPos, yPos, "2H");   break;
        case 41:   drawCardSmall(xPos, yPos, "3H");   break;
        case 42:   drawCardSmall(xPos, yPos, "4H");   break;
        case 43:   drawCardSmall(xPos, yPos, "5H");   break;
        case 44:   drawCardSmall(xPos, yPos, "6H");   break;
        case 45:   drawCardSmall(xPos, yPos, "7H");   break;
        case 46:   drawCardSmall(xPos, yPos, "8H");   break;
        case 47:   drawCardSmall(xPos, yPos, "9H");   break;
        case 48:   drawCardSmall(xPos, yPos, "10H");  break;
        case 49:   drawCardSmall(xPos, yPos, "JH");   break;
        case 50:   drawCardSmall(xPos, yPos, "QH");   break;
        case 51:   drawCardSmall(xPos, yPos, "KH");   break;
    
        case 52:   drawCardSmall(xPos, yPos, "Blue_Back");   break;
        case 53:   drawCardSmall(xPos, yPos, "Red_Back");    break;
  
      }
      
    }
    else {
        
      switch (card) {
      
        case 0:    drawCardSmall_Rotated(xPos, yPos, "ASR");   break;
        case 1:    drawCardSmall_Rotated(xPos, yPos, "2SR");   break;
        case 2:    drawCardSmall_Rotated(xPos, yPos, "3SR");   break;
        case 3:    drawCardSmall_Rotated(xPos, yPos, "4SR");   break;
        case 4:    drawCardSmall_Rotated(xPos, yPos, "5SR");   break;
        case 5:    drawCardSmall_Rotated(xPos, yPos, "6SR");   break;
        case 6:    drawCardSmall_Rotated(xPos, yPos, "7SR");   break;
        case 7:    drawCardSmall_Rotated(xPos, yPos, "8SR");   break;
        case 8:    drawCardSmall_Rotated(xPos, yPos, "9SR");   break;
        case 9:    drawCardSmall_Rotated(xPos, yPos, "10SR");  break;
        case 10:   drawCardSmall_Rotated(xPos, yPos, "JSR");   break;
        case 11:   drawCardSmall_Rotated(xPos, yPos, "QSR");   break;
        case 12:   drawCardSmall_Rotated(xPos, yPos, "KSR");   break;

        case 13:   drawCardSmall_Rotated(xPos, yPos, "ACR");   break;
        case 14:   drawCardSmall_Rotated(xPos, yPos, "2CR");   break;
        case 15:   drawCardSmall_Rotated(xPos, yPos, "3CR");   break;
        case 16:   drawCardSmall_Rotated(xPos, yPos, "4CR");   break;
        case 17:   drawCardSmall_Rotated(xPos, yPos, "5CR");   break;
        case 18:   drawCardSmall_Rotated(xPos, yPos, "6CR");   break;
        case 19:   drawCardSmall_Rotated(xPos, yPos, "7CR");   break;
        case 20:   drawCardSmall_Rotated(xPos, yPos, "8CR");   break;
        case 21:   drawCardSmall_Rotated(xPos, yPos, "9CR");   break;
        case 22:   drawCardSmall_Rotated(xPos, yPos, "10CR");  break;
        case 23:   drawCardSmall_Rotated(xPos, yPos, "JCR");   break;
        case 24:   drawCardSmall_Rotated(xPos, yPos, "QCR");   break;
        case 25:   drawCardSmall_Rotated(xPos, yPos, "KCR");   break;
      
        case 26:   drawCardSmall_Rotated(xPos, yPos, "ADR");   break;
        case 27:   drawCardSmall_Rotated(xPos, yPos, "2DR");   break;
        case 28:   drawCardSmall_Rotated(xPos, yPos, "3DR");   break;
        case 29:   drawCardSmall_Rotated(xPos, yPos, "4DR");   break;
        case 30:   drawCardSmall_Rotated(xPos, yPos, "5DR");   break;
        case 31:   drawCardSmall_Rotated(xPos, yPos, "6DR");   break;
        case 32:   drawCardSmall_Rotated(xPos, yPos, "7DR");   break;
        case 33:   drawCardSmall_Rotated(xPos, yPos, "8DR");   break;
        case 34:   drawCardSmall_Rotated(xPos, yPos, "9DR");   break;
        case 35:   drawCardSmall_Rotated(xPos, yPos, "10DR");  break;
        case 36:   drawCardSmall_Rotated(xPos, yPos, "JDR");   break;
        case 37:   drawCardSmall_Rotated(xPos, yPos, "QDR");   break;
        case 38:   drawCardSmall_Rotated(xPos, yPos, "KDR");   break;
      
        case 39:   drawCardSmall_Rotated(xPos, yPos, "AHR");   break;
        case 40:   drawCardSmall_Rotated(xPos, yPos, "2HR");   break;
        case 41:   drawCardSmall_Rotated(xPos, yPos, "3HR");   break;
        case 42:   drawCardSmall_Rotated(xPos, yPos, "4HR");   break;
        case 43:   drawCardSmall_Rotated(xPos, yPos, "5HR");   break;
        case 44:   drawCardSmall_Rotated(xPos, yPos, "6HR");   break;
        case 45:   drawCardSmall_Rotated(xPos, yPos, "7HR");   break;
        case 46:   drawCardSmall_Rotated(xPos, yPos, "8HR");   break;
        case 47:   drawCardSmall_Rotated(xPos, yPos, "9HR");   break;
        case 48:   drawCardSmall_Rotated(xPos, yPos, "10HR");  break;
        case 49:   drawCardSmall_Rotated(xPos, yPos, "JHR");   break;
        case 50:   drawCardSmall_Rotated(xPos, yPos, "QHR");   break;
        case 51:   drawCardSmall_Rotated(xPos, yPos, "KHR");   break;
    
        case 52:   drawCardSmall_Rotated(xPos, yPos, "Blue_BackR");   break;
        case 53:   drawCardSmall_Rotated(xPos, yPos, "Red_BackR");    break;
   
      }
      
    }

  }
  
}

void drawCardLarge(int xPos, int yPos, char card[2]) {
      
  lcd.drawRoundRect(xPos, yPos, xPos + CARD_LARGE_WIDTH, yPos + CARD_LARGE_HEIGHT, radius5, WHITE, solidFill);
  lcd.drawRoundRect(xPos, yPos, xPos + CARD_LARGE_WIDTH, yPos + CARD_LARGE_HEIGHT, radius5, BLACK, hollowFill);
  lcd.imageJPGSD(xPos + CARD_LARGE_INSET, yPos + CARD_LARGE_INSET, SCALE1_1, card);

}

void drawCardLarge_Rotated(int xPos, int yPos, char card[2]) {
      
  lcd.drawRoundRect(xPos, yPos + CARD_LARGE_ROTATED_Y_OFFSET, xPos + CARD_LARGE_HEIGHT, yPos + CARD_LARGE_ROTATED_Y_OFFSET + CARD_LARGE_WIDTH, radius5, WHITE, solidFill);
  lcd.drawRoundRect(xPos, yPos + CARD_LARGE_ROTATED_Y_OFFSET, xPos + CARD_LARGE_HEIGHT, yPos + CARD_LARGE_ROTATED_Y_OFFSET + CARD_LARGE_WIDTH, radius5, BLACK, hollowFill);
  lcd.imageJPGSD(xPos + CARD_LARGE_INSET, yPos + CARD_LARGE_ROTATED_Y_OFFSET + CARD_LARGE_INSET, SCALE1_1, card);

}

void drawCardSmall(int xPos, int yPos, char card[2]) {
      
  lcd.drawRoundRect(xPos, yPos, xPos + CARD_SMALL_WIDTH, yPos + CARD_SMALL_HEIGHT, radius5, WHITE, solidFill);
  lcd.drawRoundRect(xPos, yPos, xPos + CARD_SMALL_WIDTH, yPos + CARD_SMALL_HEIGHT, radius5, BLACK, hollowFill);
  lcd.imageJPGSD(xPos + CARD_SMALL_INSET, yPos + CARD_SMALL_INSET, SCALE1_2, card);
  
}

void drawCardSmall_Rotated(int xPos, int yPos, char card[2]) {
      
  lcd.drawRoundRect(xPos, yPos + CARD_SMALL_ROTATED_Y_OFFSET, xPos + CARD_SMALL_HEIGHT, yPos + CARD_SMALL_ROTATED_Y_OFFSET + CARD_SMALL_WIDTH, radius5, WHITE, solidFill);
  lcd.drawRoundRect(xPos, yPos + CARD_SMALL_ROTATED_Y_OFFSET, xPos + CARD_SMALL_HEIGHT, yPos + CARD_SMALL_ROTATED_Y_OFFSET + CARD_SMALL_WIDTH, radius5, BLACK, hollowFill);
  lcd.imageJPGSD(xPos + CARD_SMALL_INSET, yPos + CARD_SMALL_ROTATED_Y_OFFSET + CARD_SMALL_INSET, SCALE1_2, card);

}
