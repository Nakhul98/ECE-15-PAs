#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EZPointer.h>		// This is a library we created to provide a gentle introduction to pointers


// Our constants
#define NO_MOVE_YET             0       // There was no move; this is used for the value of 'last_move' 
                                        // when there is no prior move (i.e.,this is the first move)
#define PUT_NO_COIN     	1       // The move is "do not put in a coin"
#define PUT_COIN        	2       // The move is "put in a coin"

#define	POINTS_C_NC		-1      // My net gain when I put in a coin (C) and the opponent does 
                                        // not put in a coin (NC)
#define	POINTS_C_C		2       // My net gain when I put in a coin (C) and the opponent also 
                                        // puts in a coin (C)
#define	POINTS_NC_NC		0       // My net gain when I do not put in a coin (NC) and the opponent
                                        // also does not put in a coin (NC)
#define	POINTS_NC_C		3       // My net gain when I do not put in a coin (NC) and the opponent 
                                        // does put in a coin (C)

#define SUCCESS         	1       // The task was executed successfully
#define FAILURE         	0       // The task was not executed successfully

#define ALWAYS_COOPERATE	0	// Strategy "always cooperate"
#define ALWAYS_CHEAT		1	// Strategy "always cheat"
#define GRUDGER			2	// Strategy "grudger"
#define MY_STRATEGY		3	// Custom strategy
        
#define COMPETITION		1	// The style of competition to be played as part of the tournament. 
                                        // You can use this to optimize your own strategy.


// Strategy "always cooperate" -- always put in a coin (i.e., cooperates on every turn)
// inputs:  my_last_move: this player's move on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
//          opponent_last_move: other player's move  on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
// returns: this player's move (PUT_NO_COIN or PUT_COIN)
int always_cooperate(int my_last_move, int opponent_last_move) {

    // This is the first round, there were no prior moves
    // Put in a coin
    if (my_last_move == NO_MOVE_YET)
	return PUT_COIN;

    // We make a decision based on what we played before and what 
    // our opponent played before
    else {
	if (my_last_move == opponent_last_move)
            return PUT_COIN;
        else
            return PUT_COIN;
    }
}


// Strategy "always cheat" -- never put in a coin (i.e., cheats every turn)
// inputs:  my_last_move: this player's move on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
//          opponent_last_move: other player's move on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
// returns: this player's move (PUT_NO_COIN or PUT_COIN)
int always_cheat(int my_last_move, int opponent_last_move) {

  // TODO: Implement this strategy
  return PUT_NO_COIN;
}


// Strategy "grudger" -- starts with cooperating and keeps on cooperating until the opponent cheats; 
//                       then always cheats
// inputs:  my_last_move: this player's move on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
//          opponent_last_move: other player's move on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
// returns: this player's move (PUT_NO_COIN or PUT_COIN)
int grudger(int my_last_move, int opponent_last_move) {

  // TODO: Implement this strategy
  static int last_time = PUT_COIN;
  if (my_last_move == NO_MOVE_YET) {
    return PUT_COIN;
  }

  else {
    if (opponent_last_move == PUT_NO_COIN) {
      last_time = PUT_NO_COIN;
    }  
  }
  
  opponent_last_move = last_time;
  return opponent_last_move;
}


// My own custom strategy to try to win the game
// inputs:  my_last_move: this player's move on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
//          opponent_last_move: other player's move on the last turn (NO_MOVE_YET, PUT_NO_COIN or PUT_COIN)
// returns: this player's move (PUT_NO_COIN or PUT_COIN)
int my_strategy(int my_last_move, int opponent_last_move) {

  // TODO: Implement your own strategy

  // in game theory, winning strategy is to play tit for tat
  // since mistakes happen, we will call a static variable that resets every

  static int insurance = 0; // this allows us to reset if opponent is playing same strategy as us - reset after 4 rounds in case of mistake
  int my_move;
  static grudge_weeder;

  // must trust in very beginning

  if(my_last_move == NO_MOVE_YET) {
    my_move = PUT_COIN;
  }
  else {
    if((insurance == 5) && (opponent_last_move == PUT_NO_COIN)) {
      grudge_weeder = 1;  // makes it so that if grudger, then never forgiven
    }
    if((insurance == 4) && !grudge_weeder) {
      my_move = PUT_COIN;
      insurance++;
    }
    else {
      my_move = opponent_last_move;
      insurance++;
    }
  }

  return my_move;
}


// With a certain probably, change the move such that a coin is not put in even if the player meant to do so
// inputs:  move: the move the player wanted to make
//          mistake_prob: the probability (between 0.0 to 1.0) of making a mistake 
//                        (i.e., not putting in a coin when the player meant to do so)
// returns: the actual move the player makes
int mistake(int move, double mistake_prob) {
  
  
  // TODO: Implement this function

  if(move == PUT_COIN) {
    if((double) rand()/RAND_MAX <= mistake_prob) {
      move = PUT_NO_COIN;
    }
  }
  return move;
}


// Have two players compete against each other for a number of rounds and return the scores for each player
// inputs:  type1: strategy of player 1 (ALWAYS_COOPERATE, ALWAYS_CHEAT, GRUDGER or MY_STRATEGY)
//          type2: strategy of player 2 (ALWAYS_COOPERATE, ALWAYS_CHEAT, GRUDGER or MY_STRATEGY)
//          score1: pointer to the total score of player 1
//          score2: pointer to the total score of player 2
//          rounds: total number of rounds to be played
//          mistake_prob: the probability (between 0.0 to 1.0) of making a mistake 
//                        (i.e., not putting in a coin when the player meant to do so)
// returns: SUCCESS or FAILURE, depending on whether the competition was completed successfully or not 
int play_against_each_other(int type1, int type2, intPtr score1_address, intPtr score2_address, int rounds, double mistake_prob) {

    // TODO: Implement this function

  int i, temp1 = 0, temp2 = 0;

  score1_address = NO_MOVE_YET;
  score2_address = NO_MOVE_YET;


  for(i = 0; i < rounds; i++) {
  
  
    switch(type1) {  // determines move for player one                                                                            
    case (ALWAYS_COOPERATE) :
      temp1 = always_cooperate(score1_address, score2_address);
      if(temp1 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    case (ALWAYS_CHEAT) :
      temp1 = always_cheat(score1_address, score2_address);
      if(temp1 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    case (GRUDGER) :
      temp1 = grudger(score1_address, score2_address);
      if(temp1 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    case (MY_STRATEGY) :
      temp1 = my_strategy(score1_address, score2_address);
      if(temp1 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    }
    
    if(temp1 == PUT_COIN) {
      temp1 = 1;
    }
    
    
    switch(type2) {  // determines move for player 2                                                                              
    case (ALWAYS_COOPERATE) :
      temp2 = always_cooperate(score1_address, score2_address);
      if(temp2 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    case (ALWAYS_CHEAT) :
      temp2 = always_cheat(score1_address, score2_address);
      if(temp2 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    case (GRUDGER) :
      temp2 = grudger(score1_address, score2_address);
      if(temp2 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    case (MY_STRATEGY) :
      temp2 = my_strategy(score1_address, score2_address);
      if(temp2 == (PUT_COIN || PUT_NO_COIN)) {
        return FAILURE;
      }
      continue;
    }
    
    if(temp2 == PUT_COIN) {
      temp2 = 1;
    }
    
    
    if( temp1 && temp2) {  // both players are honest
      score1_address += POINTS_C_C;
      score2_address += POINTS_C_C;
    }
    

    if( (!temp1) && temp2) {// player 1 is not honest
      score1_address += POINTS_NC_C;
      score2_address += POINTS_C_NC;
    }   
    
    if( temp1 && (!temp2)) {// player 2 is not honest
      score1_address += POINTS_C_NC;
      score2_address += POINTS_NC_C;
    }  
    
    if( (!temp1) && (!temp2)) {// neither player is honest
      score1_address += POINTS_NC_NC;
      score2_address += POINTS_NC_NC;
    }  
  }
  return SUCCESS;
}


// Main program
// Call 'play_against_each_other' to run a competition and display the results
int main() {

    // Seed the random number generator
    srand(time(NULL));


    // TODO: Write your code here
    // ...


    
    return 0;
            
}
