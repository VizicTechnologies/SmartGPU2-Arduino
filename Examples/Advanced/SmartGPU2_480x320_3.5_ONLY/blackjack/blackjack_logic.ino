
void initialDeal() {

  numberOfGamesPlayed++;  


/* Normal hand */

  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND, CARD_LARGE_TOP_DEALER, getCard(DEALER, FIRST_HAND), false, true);
  delay(500);  
  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND, CARD_LARGE_TOP_PLAYER, getCard(PLAYER, FIRST_HAND), false, true);
  delay(500);  
  getCard(DEALER, FIRST_HAND);
  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, CARD_BLUE_BACKGROUND, false, true);
  delay(500);  
  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + CARD_LARGE_SPACING, CARD_LARGE_TOP_PLAYER, getCard(PLAYER, FIRST_HAND), false, true);
  delay(500);  


/* Dealer blackjack 

  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND, CARD_LARGE_TOP_DEALER, getCard(DEALER, FIRST_HAND, 0), false, true);
  delay(500);  
  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND, CARD_LARGE_TOP_PLAYER, getCard(PLAYER, FIRST_HAND), false, true);
  delay(500);  
  getCard(DEALER, FIRST_HAND, 10);
  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, CARD_BLUE_BACKGROUND, false, true);
  delay(500);  
  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + CARD_LARGE_SPACING, CARD_LARGE_TOP_PLAYER, getCard(PLAYER, FIRST_HAND), false, true);
  delay(500);  

*/
  
  player_Split = ((player_FirstHand[0] % 13) == (player_FirstHand[1] % 13)) && (chkAllowSplit == SG_SELECTED);
  
  
  // Offer insurance ?
  
  if ((dealer[0] % 13) == 0 && purse >= 1) {

    buttonMode = SHOW_INSURANCE_BUTTONS;
    drawPlayerScores();
    drawButtons();

  }
  else {

    if ((dealer[0] % 13) == 0 && purse == 0) {
       
        peekOnTen();
       
    }
    else {
        
      if ((dealer[0] % 13) == 9 || (dealer[0] % 13) == 10 || (dealer[0] % 13) == 11 || (dealer[0] % 13) == 12) {
       
        peekOnTen();
        
      }
      else {
        
        buttonMode = SHOW_GAME_PLAY_BUTTONS;
        drawPlayerScores();
        drawButtons();
  
      }
      
    }
    
  }
  
 
}



void peekOnTen() {
      
  lcd.setTextColour(GREY3);
  lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, SG_BLACK, solidFill);
  delay(500);
  lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Dealer is peeking at his hand.", 0);
  delay(1000);

  if (calculateHand(DEALER, true) == 21) {

    drawCard(CARD_LARGE_LEFT_DEALER + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, dealer[1], false, true);   
    delay(500);
    lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, SG_BLACK, solidFill);

    if (calculateHand(PLAYER, FIRST_HAND, true) == 21) {
    
      lcd.setTextColour(GREY3);
      lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "You both have a blackjack, push!", 0);
  
      purse = purse + currentBetInit;
      numberOfGamesPush++;
  
      delay(500);  
      buttonMode = SHOW_END_OF_GAME_BUTTONS;
      drawButtons();

    }
    else {

      lcd.setTextColour(GREY3);
      lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Dealer has a Blackjack, your hand loses", 0);
      lcd.setTextColour(SG_RED);
      lcd.printNumber(STATUS_LEFT_FIRSTHAND + 254, STATUS_MIDDLE_TOP + 5, -currentBetInit);
  
      numberOfGamesLost++;
      highlightLoss(-currentBetInit);

      delay(500);  
      buttonMode = SHOW_END_OF_GAME_BUTTONS;
      drawButtons();
      
    }

  }
  else {

    drawCard(30, CARD_LARGE_TOP_DEALER, CARD_RED_BACKGROUND, false, true);
    lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, SG_BLACK, solidFill);
    lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Dealer does not have a blackjack.", 0);
    delay(2000);
  
    buttonMode = SHOW_GAME_PLAY_BUTTONS;
  
    drawPlayerScores();
    drawButtons();
    
  }
 
}

void playInsurance() {
      
  lcd.setTextColour(GREY3);
  lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, SG_BLACK, solidFill);
  delay(500);
  lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Dealer is peeking at his hand.", 0);
  delay(1000);

  if (insurance > 0) {
      
    if (calculateHand(DEALER, true) == 21) {
  
      delay(500);
      drawCard(CARD_LARGE_LEFT_DEALER + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, dealer[1], false, true);   
      delay(500);
  
      if (calculateHand(PLAYER, FIRST_HAND, true) == 21) {
      
        lcd.setTextColour(GREY3);
        lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, SG_BLACK, solidFill);
        lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "You both have Blackjack! Insurance pays", 0);
        lcd.setTextColour(SG_GREEN);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 260, STATUS_MIDDLE_TOP + 5, (insurance * 2));
  
        purse = purse + currentBetInit;
        highlightWin(2 * insurance, 3 * insurance);    
    
        numberOfGamesPush++;
//        highlightWin(currentBetInit, currentBetInit * 2);
    
        delay(500);  
        buttonMode = SHOW_END_OF_GAME_BUTTONS;
        drawButtons();
  
      }
      else {
  
        lcd.setTextColour(GREY3);
        lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, SG_BLACK, solidFill);
        lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Blackjack, insurance pays      hand loses", 0);
        lcd.setTextColour(SG_GREEN);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 172, STATUS_MIDDLE_TOP + 5, (insurance * 2));
        lcd.setTextColour(SG_RED);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 270, STATUS_MIDDLE_TOP + 5, -currentBetInit);

        purse = purse + (3 * insurance);
        if (2 * insurance < currentBetInit) {

          highlightLoss(-(currentBetInit - (2 * insurance)));

        }

        numberOfGamesLost++;

        delay(500);  
        buttonMode = SHOW_END_OF_GAME_BUTTONS;
        drawButtons();
        
      }
  
    }
    else {
  
      delay(500);
      drawCard(30, CARD_LARGE_TOP_DEALER, CARD_RED_BACKGROUND, false, true);
      delay(500);
  
      lcd.setTextColour(GREY3);
      lcd.drawRectangle(STATUS_LEFT_FIRSTHAND, STATUS_MIDDLE_TOP, MAX_X_PORTRAIT - 5, STATUS_MIDDLE_TOP + STATUS_HEIGHT, SG_BLACK, solidFill);
      lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "No blackjack, you lose insurance of ", 0);
      lcd.setTextColour(SG_RED);
      lcd.printNumber(STATUS_LEFT_FIRSTHAND + 225, STATUS_MIDDLE_TOP + 5, insurance);
      
      highlightLoss(-insurance);
//    delay(500);  

      buttonMode = SHOW_GAME_PLAY_BUTTONS;
    
      drawPlayerScores();
      drawButtons();
      
    }
    
  }
  else {

    if (calculateHand(DEALER, true) == 21) {
  
      delay(500);
      drawCard(CARD_LARGE_LEFT_DEALER + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, dealer[1], false, true);   
      delay(500);
  
      if (calculateHand(PLAYER, FIRST_HAND, true) == 21) {
      
        lcd.setTextColour(GREY3);
        lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "You both have a blackjack, push!", 0);
    
        purse = purse + currentBetInit;
        numberOfGamesPush++;
    
        delay(500);  
        buttonMode = SHOW_END_OF_GAME_BUTTONS;
        drawButtons();
  
      }
      else {
  
        lcd.setTextColour(GREY3);
        lcd.string(STATUS_LEFT_FIRSTHAND + 8, STATUS_MIDDLE_TOP + 5, MAX_X_PORTRAIT, MAX_Y_PORTRAIT, "Dealer has a Blackjack, your hand loses", 0);
        lcd.setTextColour(SG_RED);
        lcd.printNumber(STATUS_LEFT_FIRSTHAND + 254, STATUS_MIDDLE_TOP + 5, -currentBetInit);
    
        numberOfGamesLost++;
        highlightLoss(-currentBetInit);
  
        delay(500);  
        buttonMode = SHOW_END_OF_GAME_BUTTONS;
        drawButtons();
        
      }
  
    }
    else {
  
      delay(500);
      drawCard(30, CARD_LARGE_TOP_DEALER, CARD_RED_BACKGROUND, false, true);
      delay(500);
    
      buttonMode = SHOW_GAME_PLAY_BUTTONS;
    
      drawPlayerScores();
      drawButtons();
      
    }
    
  }
  
}


void hitMe() {

  player_Split = false;

  if (handInPlay == FIRST_HAND) {
      
    drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, handInPlay), false, true);
    drawPlayerScores();
    
    if (calculateHand(PLAYER, FIRST_HAND, false) > 21) {
      
      bust(PLAYER, FIRST_HAND);
    
    }
    
  }
  else {

    drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND + (player_SecondHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, handInPlay), false, true);
    drawPlayerScores();
    
    if (calculateHand(PLAYER, SECOND_HAND, false) > 21) {
      
      bust(PLAYER, SECOND_HAND);
    
    }
  
  }
  
  drawButtons();
  
}

void bust(byte player, byte hand) {
  
  lcd.setTextColour(GREY5);
  lcd.setTextSize(SG_FONT1);
  numberOfGamesLost++;  
  
  if (player == PLAYER && hand == FIRST_HAND) {

    player_FirstHand_Bust = true;
    drawPlayerScores();
    
    highlightLoss(-player_FirstHand_Bet);
    playNextHand();
  
  }
  
  if (player == PLAYER && hand == SECOND_HAND) {
 
    player_SecondHand_Bust = true;
    drawPlayerScores();
    
    highlightLoss(-player_SecondHand_Bet);
    playNextHand();
    
  }
  
}

void doubleUp() {

  player_Split = false;

  if (handInPlay == FIRST_HAND) {
 
    player_FirstHand_Double = true;
    drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, handInPlay), true, true);
    purse = purse - currentBetInit;
    currentBetTotal = currentBetTotal + currentBetInit;
    player_FirstHand_Bet = player_FirstHand_Bet + currentBetInit;
    drawPlayerScores();
    
    delay(500);
    
    if (calculateHand(PLAYER, FIRST_HAND, false) > 21) {
      
      bust(PLAYER, FIRST_HAND);
    
    }
    else {
 
      playNextHand();
   
    }   
    
  }
  else {
  
    player_SecondHand_Double = true;
    drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND + (player_SecondHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, handInPlay), true, true);
  
    purse = purse - currentBetInit;
    currentBetTotal = currentBetTotal + currentBetInit;
    player_SecondHand_Bet = player_SecondHand_Bet + currentBetInit;
    drawPlayerScores();

    delay(500);
    
    if (calculateHand(PLAYER, SECOND_HAND, false) > 21) {
      
      bust(PLAYER, SECOND_HAND);
    
    }
    else {
 
      playDealerHand();
   
    }   
    
  }
    
}

void split() {

  player_Split = false;
  numberOfGamesPlayed++;  
 
  lcd.drawRectangle(10, CARD_LARGE_TOP_PLAYER, MAX_X_PORTRAIT, CARD_LARGE_TOP_PLAYER + CARD_LARGE_HEIGHT, TABLE_GREEN, solidFill);
  drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND, CARD_LARGE_TOP_PLAYER, player_FirstHand[0], false, true);
  player_FirstHand_CardCount--;
  player_SecondHand[0] = player_FirstHand[1];
  player_SecondHand_CardCount++;
  
  player_SecondHand_Bet = currentBetInit;
  purse = purse - currentBetInit;
  currentBetTotal = currentBetTotal + currentBetInit;


  // If splitting two aces, player can only take one card per hand ..
  
  if (player_FirstHand[0] % 13 == 0) {

    
    // Play the first hand ..
    
    drawPlayerScores();
    lcd.drawRectangle(10, CARD_LARGE_TOP_PLAYER, MAX_X_PORTRAIT, CARD_LARGE_TOP_PLAYER + CARD_LARGE_HEIGHT, TABLE_GREEN, solidFill);
    drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND, CARD_LARGE_TOP_PLAYER, player_FirstHand[0], false, true);   
    drawCard(CARD_SMALL_LEFT_PLAYER_SECONDHAND, CARD_SMALL_TOP_PLAYER, player_SecondHand[0], false, false);   
    delay(500);  
    drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, FIRST_HAND), false, true);
    delay(1000);  

    drawPlayerScores();
    lcd.drawRectangle(10, CARD_LARGE_TOP_PLAYER, MAX_X_PORTRAIT, CARD_LARGE_TOP_PLAYER + CARD_LARGE_HEIGHT, TABLE_GREEN, solidFill);
    drawFirstHand_Small();          
    drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND, CARD_LARGE_TOP_PLAYER, player_SecondHand[0], false, true);   
    delay(500);  
    drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND + (player_SecondHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, SECOND_HAND), false, true);
   
    playDealerHand();
    
  }
  else {

    drawButtons();
    drawPlayerScores();
    drawCard(CARD_SMALL_LEFT_PLAYER_SECONDHAND, CARD_SMALL_TOP_PLAYER, player_SecondHand[0], false, false);
    delay(500);  
    drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + (player_FirstHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, FIRST_HAND), false, true);
    drawButtons();
  
  } 
  
}


void playNextHand() {

  player_Split = false;
  
  if (handInPlay == FIRST_HAND) {

    player_FirstHand_Stand = true;
    
    if (player_SecondHand_CardCount > 0) {
      
      playSecondHand();
      
    }
    else {

      if (!player_FirstHand_Bust) {

        playDealerHand();
        
      }
      else {
       
        showDealerCards();
        buttonMode = SHOW_END_OF_GAME_BUTTONS;
        drawButtons(); 
        
      }
      
    }
    
  }
  else {

    if (!player_FirstHand_Bust || !player_SecondHand_Bust) {

      player_SecondHand_Stand = true;
      playDealerHand();
        
    }
    else {
       
      showDealerCards();
      buttonMode = SHOW_END_OF_GAME_BUTTONS;
      drawButtons(); 
        
    }
    
  }
  
}



void playSecondHand() {

  handInPlay = SECOND_HAND;
  drawPlayerScores();
  lcd.drawRectangle(10, CARD_LARGE_TOP_PLAYER, MAX_X_PORTRAIT, CARD_LARGE_TOP_PLAYER + CARD_LARGE_HEIGHT, TABLE_GREEN, solidFill);

  drawFirstHand_Small();
        
  drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND, CARD_LARGE_TOP_PLAYER, player_SecondHand[0], false, true);   
  delay(500);  
  drawCard(CARD_LARGE_LEFT_PLAYER_SECONDHAND + (player_SecondHand_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_PLAYER, getCard(PLAYER, SECOND_HAND), false, true);
  
}

void playDealerHand() {

  handInPlay = DEALER_HAND;
  drawPlayerScores();
  drawButtons();
  delay(500);
  drawCard(CARD_LARGE_LEFT_DEALER + CARD_LARGE_SPACING, CARD_LARGE_TOP_DEALER, dealer[1], false, true);   
  delay(500);

  while (calculateHand(DEALER, false) <= 16) {
    
    drawCard(CARD_LARGE_LEFT_PLAYER_FIRSTHAND + (dealer_CardCount * CARD_LARGE_SPACING), CARD_LARGE_TOP_DEALER, getCard(DEALER, FIRST_HAND), false, true);
    delay(500);  

  }

  
  // Are there two player hands ?
  
  if (player_SecondHand_CardCount > 0) {
        
    if (!player_FirstHand_Bust && !player_SecondHand_Bust) {
      
      lcd.drawRectangle(10, CARD_LARGE_TOP_PLAYER, MAX_X_PORTRAIT, CARD_LARGE_TOP_PLAYER + CARD_LARGE_HEIGHT, TABLE_GREEN, solidFill);
      drawFirstHand_Large();
      drawSecondHand_Small();

      delay(1000);
      
      if (calculateHand(PLAYER, FIRST_HAND, true) > calculateHand(DEALER, true) || calculateHand(DEALER, true) > 21) {

        if (isBlackjack(PLAYER, FIRST_HAND) && (chkBlackjackPays322 == SG_SELECTED)) {

          highlightWin(player_FirstHand_Bet * 3 / 2, player_FirstHand_Bet * 5 / 2);

        }
        else {        
        
          highlightWin(player_FirstHand_Bet, player_FirstHand_Bet * 2);
          
        }
        
      }
      else {
        
        highlightLoss(-player_FirstHand_Bet);
        
      }

      lcd.drawRectangle(10, CARD_LARGE_TOP_PLAYER, MAX_X_PORTRAIT, CARD_LARGE_TOP_PLAYER + CARD_LARGE_HEIGHT, TABLE_GREEN, solidFill);
      drawFirstHand_Small();
      drawSecondHand_Large();


      delay(1000);
    
      if (calculateHand(PLAYER, SECOND_HAND, true) > calculateHand(DEALER, true) || calculateHand(DEALER, true) > 21) {

        if (isBlackjack(PLAYER, SECOND_HAND) && (chkBlackjackPays322 == SG_SELECTED)) {

          highlightWin(player_SecondHand_Bet * 3 / 2, player_SecondHand_Bet * 5 / 2);

        }
        else {        
        
          highlightWin(player_SecondHand_Bet, player_SecondHand_Bet * 2);
          
        }
        
      }
      else {
        
        if (isBlackjack(PLAYER, SECOND_HAND)) {
          
          if (chkBlackjackPays322 == SG_SELECTED) {

            highlightWin(player_SecondHand_Bet * 3 / 2, player_SecondHand_Bet * 5 / 2);
            
          }
          else {

            highlightWin(player_SecondHand_Bet, player_SecondHand_Bet * 2);
            
          }

        }
        else {        
        
          highlightLoss(-player_SecondHand_Bet);
          
        }
        
      }
      
    }
    
    if (player_FirstHand_Bust && !player_SecondHand_Bust) {
      
      if (calculateHand(PLAYER, FIRST_HAND, true) > calculateHand(DEALER, true) || calculateHand(DEALER, true) > 21) {

        if (isBlackjack(PLAYER, FIRST_HAND) && (chkBlackjackPays322 == SG_SELECTED)) {

          highlightWin(player_FirstHand_Bet * 3 / 2, player_FirstHand_Bet * 5 / 2);

        }
        else {        
        
          highlightWin(player_FirstHand_Bet, player_FirstHand_Bet * 2);
          
        }        
        
      }
      else {
        
        if (isBlackjack(PLAYER, FIRST_HAND)) {
          
          if (chkBlackjackPays322 == SG_SELECTED) {

            highlightWin(player_FirstHand_Bet * 3 / 2, player_FirstHand_Bet * 5 / 2);
            
          }
          else {

            highlightWin(player_FirstHand_Bet, player_FirstHand_Bet * 2);
            
          }

        }
        else {        
        
          highlightLoss(-player_FirstHand_Bet);
          
        }
        
      }
      
    }
    
    if (!player_FirstHand_Bust && player_SecondHand_Bust) {
      
      if (calculateHand(PLAYER, SECOND_HAND, true) > calculateHand(DEALER, true) || calculateHand(DEALER, true) > 21) {
 
        if (isBlackjack(PLAYER, SECOND_HAND) && (chkBlackjackPays322 == SG_SELECTED)) {

          highlightWin(player_SecondHand_Bet * 3 / 2, player_SecondHand_Bet * 5 / 2);

        }
        else {        
        
          highlightWin(player_SecondHand_Bet, player_SecondHand_Bet * 2);
          
        }
        
      }
      else {
        
        if (isBlackjack(PLAYER, SECOND_HAND)) {
          
          if (chkBlackjackPays322 == SG_SELECTED) {

            highlightWin(player_SecondHand_Bet * 3 / 2, player_SecondHand_Bet * 5 / 2);
            
          }
          else {

            highlightWin(player_SecondHand_Bet, player_SecondHand_Bet * 2);
            
          }

        }
        else {        
        
          highlightLoss(-player_SecondHand_Bet);
          
        }
        
      }
      
    }
    
  }
  
  
  // Only one hand in play ..

  else {
       
    if (calculateHand(PLAYER, FIRST_HAND, true) > calculateHand(DEALER, true) || calculateHand(DEALER, true) > 21) {
 
      if (isBlackjack(PLAYER, FIRST_HAND) && (chkBlackjackPays322 == SG_SELECTED)) {

        highlightWin(player_FirstHand_Bet * 3 / 2, player_FirstHand_Bet * 5 / 2);

      }
      else {        
        
        highlightWin(player_FirstHand_Bet, player_FirstHand_Bet * 2);
          
      } 
        
    }
    else {
      
     if (isBlackjack(PLAYER, FIRST_HAND)) {
        
        if (chkBlackjackPays322 == SG_SELECTED) {

          highlightWin(player_FirstHand_Bet * 3 / 2, player_FirstHand_Bet * 5 / 2);
          
        }
        else {

          highlightWin(player_FirstHand_Bet, player_FirstHand_Bet * 2);
          
        }

      }
      else {        
      
        highlightLoss(-player_FirstHand_Bet);
        
      }
        
    }
      
  }
 
  buttonMode = SHOW_END_OF_GAME_BUTTONS;
  drawButtons();
 
} 
