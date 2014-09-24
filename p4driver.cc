/*------------------------
  CS246 - Assignment 6
  "p4driver.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

//Associated Files:
//Card.h/cc,CardPile.h/cc,Deck.h/cc, hearts.pdf, HumanPlayer.h/cc,Player.h/cc,PRNG.h,RandomPlayer.h/cc, SmartPlayer.h/cc, Trick.h/cc

#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "Deck.h"
#include "Card.h"
#include "Trick.h"

using namespace std;

string arrDefaultName[4] = {"Alice","Bob","Carole","Ted"};//default names
int maxScore = 40;//Score required to end game, default is 40
bool dinit = false, pinit = false;//Shows if the deck and players are specified on command line

//defined in the bottom
void checkBound(bool oob,char option); //Checks the correct boundaries
void illegalType(char* ptype); //Check for type


int main(int argc,char *argv[]){

//=====Command Line Options Parsing=====

	char* tmp;//temp store argv
	Deck playingDeck = Deck();//deck of 52 cards after passing options
	Player * players[4];// the players in the game
	for(int i = 1;i < argc ; i++){
		tmp = argv[i++];
		
		//Flag -r for seed
		if(strcmp(tmp,"-r") == 0){ 
			checkBound(i >= argc,'r');
			playingDeck.setRandomSeed(atoi(argv[i]));
			
		//Flag -s for max score	
		}else if(strcmp(tmp,"-s") == 0){
			checkBound(i >= argc,'s');
			maxScore = atoi(argv[i]);
			if(maxScore <= 0){
				cerr << "Error, maxScore must be positive." << endl;
				exit(EXIT_FAILURE);
			}
			
		//Flag -d to use deck defined in provided file	
		}else if(strcmp(tmp,"-d") == 0){
			dinit = true;
			ifstream fin(argv[i]);//file stream to read cards
			fin >> playingDeck;
			fin.close();
			
		//Flag -p to have players with the given names and types
		}else if(strcmp(tmp,"-p") == 0){
			pinit = true;
			for(int j = 0;j < 4; j++){
				checkBound( i >= argc , 'p');
				string playerName(argv[i++]);

				checkBound( i >= argc , 'p');
				char* stype = argv[i++];
				if(strlen(stype) != 1) illegalType(stype); //Exit if command too long
				
				switch(stype[0]){
				case 'H': //Human Player
					players[j] = new HumanPlayer(playerName);
					break;
				case 'S': //Smart Player
					players[j] = new SmartPlayer(playerName);
					break;
					
				case 'R': //Random Player
					checkBound( i >= argc , 'p');
					players[j] = new RandomPlayer(playerName,atoi(argv[i]));
					i++;
					break;
				default:
					illegalType(stype); //Exit otherwise
					break;
				}

			} //for
		}else{
			i--;
		} //if
	}
	//use defaults if players are not provided
	if(!pinit){
		for(int i = 0; i < 4 ; i++){
			players[i] = new SmartPlayer(arrDefaultName[i]);
		}
	}//if
	
	//use default deck if a deck is not provided
	if(!dinit){
		playingDeck.generate();
	}
	
//cout << "Starting a new game of Hearts. The MaxPoints is "<< maxScore << "." << endl;


//=====Gameplay=====

	
	int lead; //Player to go first
	int pid; //Player ID
	int match = 0; //Current match
	int gameEnd = -1; //If game has ended. If ended, will equal pid of player that exceeded score.
	Card* tempCard; //temporary variable
	string pHand; //temporary variable to store string
	
	
	//Main loop - 1 iteration per match (hand)
	do { 
		
		match++; //Increase Match Count	
	
		if(match > 1){
			//Makes a new deck for each subsequent round
			playingDeck.clear();
			playingDeck.generate();
		}
		
		//Shuffles and Prints the deck
		playingDeck.shuffle();
		cout << "\n\nAt the beginning of hand " << match << ", here is the deck:" << endl;
		playingDeck.print();
		
		//Deal to players, each round the next player is dealt to first
		playingDeck.deal(players[(match-1)%4],players[match%4],players[(match+1)%4],players[(match+2)%4]);
		cout << "\n\nHere are the hands for each player at the start of hand number " << match << endl << endl;
		
		
		//Prints the cards of each player and checks who has the 2 of Clubs
		for(int i = 0; i < 4; i++){
			cout << players[i]->getName() << " has these cards:" << endl;
			pHand =	players[i]->printHand();
			if (pHand.find("2C") != string::npos) lead = i;
			cout << pHand << "\n" << endl;
		}//for
		
		
		// Round Loop - 1 iteration per Round
		for (int round = 0; round < 13; round++){
			cout << "\nNow starting round " << round + 1 << " of hand " << match << endl;
			//Let pid represent current player id
			Trick t; //A new trick for each round
			
			//If first round, must play 2 of clubs, otherwise can lead anything
			if (round == 0) tempCard = players[lead]->playCard(0,-2);
			else tempCard = players[lead]->playCard(0,-1);
			
			//The trump suit of the round and the current high card
			int trump = tempCard->getSuit();
			int highRank = t.addCard(tempCard, lead);
			

			pid = (lead+1)%4;
			
			//Each player takes their turn, the high card is updated accordingly
			do {
				highRank = t.addCard(players[pid]->playCard(highRank,trump), pid);	
				pid = (pid+1)%4;
			} while(pid != lead);
						
			//The winner of the round leads next time, and gets any Hearts from the trick
			lead = t.getWinner();
			players[lead]->addPoints(t.getValue());
			cout << "  " << players[lead]->getName() << " won the trick and added the following cards:" << endl;
			cout << "    " << t.getCards() << endl;
		} // End Round Loop
		
		cout << "\nAt the end of hand " << match << ", the score is:" << endl;
		
		//Check if any plyaer has exceeded the MaxPoints at the end of a Match
		for (int i = 0; i < 4; i++){
			cout << "    " << players[i]->getName() << "  " << players[i]->getScore() << endl;
			if (players[i]->getScore() > maxScore && gameEnd < 0) gameEnd = i;
		} //for
		
		
		
		//If the game has ended
		if (gameEnd > -1){
			int winner = 0;
			//Display Scores
			for (int i = 0; i < 4; i++){
				if (players[i]->getScore() < players[winner]->getScore()) winner = i;
			}
			cout << "\nThe game is over." << endl;
			
			//Declare Winners
			cout << players[gameEnd]->getName() << " has exceeded " << maxScore << " points." << endl;
			cout << "The winner is " << players[winner]->getName() << endl;

			//Deallocate memory for players and exit program
			for (int i = 0; i < 4; i++){
				delete players[i];
			}
			return 0;
		
		} //if
		
		//Loops back if the game has not ended

	}while (gameEnd < 0); // End Match Loop
	

	return 0; //Should never be executed
	
}

//invoke to check boundary of argv
void checkBound(bool oob,char option){
	if(oob){
		cerr << "Error, -"<< option <<" requires another argument.  Aborting." << endl;
		exit(EXIT_FAILURE);
	}
}
//exit failure if out of boundary

//invoke when encounter illegal type
void illegalType(char* ptype){
	cerr << "Illegal player kind: \"" << ptype << "\"" <<endl;
	exit(EXIT_FAILURE);
}
//exit and print err msg
