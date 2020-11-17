
byte getCard(byte player, byte hand) {

  byte card = 0;
  
  while (true) {
    
    card = random(52);

    if (cards[card] == 0) {
      
      cards[card] = 1;
      break;
      
    }
    
  }
  
  
  if (player == DEALER) {
   
    dealer[dealer_CardCount] = card;
    dealer_CardCount++;
    
  }
  
  if (player == PLAYER && hand == FIRST_HAND) {
   
    player_FirstHand[player_FirstHand_CardCount] = card;
    player_FirstHand_CardCount++;
    
  }
  
  if (player == PLAYER && hand == SECOND_HAND) {
   
    player_SecondHand[player_SecondHand_CardCount] = card;
    player_SecondHand_CardCount++;
    
  }
  
  return card;
  
}


byte getCard(byte player, byte hand, byte cardNumber) {
  
  if (player == DEALER) {
   
    dealer[dealer_CardCount] = cardNumber;
    dealer_CardCount++;
    
  }
  
  if (player == PLAYER && hand == FIRST_HAND) {
   
    player_FirstHand[player_FirstHand_CardCount] = cardNumber;
    player_FirstHand_CardCount++;
    
  }
  
  if (player == PLAYER && hand == SECOND_HAND) {
   
    player_SecondHand[player_SecondHand_CardCount] = cardNumber;
    player_SecondHand_CardCount++;
    
  }
  
  return cardNumber;
  
}

boolean isBlackjack(byte player, byte hand) {
  
  if (player == DEALER && calculateHand(player, hand, true) == 21 && dealer_CardCount == 2) {
   
    return true;
    
  }
  
  if (player == PLAYER && hand == FIRST_HAND && calculateHand(player, hand, true) == 21 && player_FirstHand_CardCount == 2) {
   
    return true;
    
  }
  
  if (player == PLAYER && hand == SECOND_HAND && calculateHand(player, hand, true) == 21 && player_SecondHand_CardCount == 2) {
   
    return true;
    
  }
  
  return false;
  
}

int calculateHand(byte player, boolean bestHand) {

   return calculateHand(player, FIRST_HAND, bestHand);
   
}

int calculateHand(byte player, byte hand, boolean bestHand) {
  
  int result = 0;
  int aces = 0;
    
  if (player == DEALER) {
   
    for (int x=0; x< dealer_CardCount; x++) {
       
      switch (dealer[x] % 13) {
       
        case 0:   result = result + 1; aces++; break;
        case 9:   result = result + 10; break;
        case 10:  result = result + 10; break;
        case 11:  result = result + 10; break;
        case 12:  result = result + 10; break;
        default:  result = result + (dealer[x] % 13) + 1; break;
         
      }
        
    }
    
  }
  
  if (player == PLAYER && hand == FIRST_HAND) {
   
    for (int x=0; x< player_FirstHand_CardCount; x++) {
       
      switch (player_FirstHand[x] % 13) {
       
        case 0:   result = result + 1; aces++; break;
        case 9:   result = result + 10; break;
        case 10:  result = result + 10; break;
        case 11:  result = result + 10; break;
        case 12:  result = result + 10; break;
        default:  result = result + (player_FirstHand[x] % 13) + 1; break;
         
      }
    
    }
    
  }
  
  if (player == PLAYER && hand == SECOND_HAND) {
   
    for (int x=0; x< player_SecondHand_CardCount; x++) {
       
      switch (player_SecondHand[x] % 13) {
       
        case 0:   result = result + 1; aces++; break;
        case 9:   result = result + 10; break;
        case 10:  result = result + 10; break;
        case 11:  result = result + 10; break;
        case 12:  result = result + 10; break;
        default:  result = result + (player_SecondHand[x] % 13) + 1; break;
         
      }

    }
    
  }
  
  if (bestHand) {
    
    while (result < 12 && aces > 0) {
      
      result = result + 10;
      aces --;
      
    }
    
  }
  
  return result;
  
}
