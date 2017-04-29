#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

char heart = 'H';
char diamond = 'D';
char club = 'C';
char spade = 'S';
int cash = 500;

struct node{
    char *result;
    int wager, score, dscore, bank;
    struct node *next;
};
struct node *head = NULL;
struct node *current = NULL;
int wins = 0;
int losses = 0;

struct bTreeNode{
	int wager;
	struct bTreeNode* left;
	struct bTreeNode* right;
};


struct bTreeNode* sortedListToBST(struct node **head_reff, int n);
struct bTreeNode* newNode(int wager);

//count number of nodes in linked list and return value to create BST
struct bTreeNode* sortBST(struct node *head){
	
	int n = countNodes(head);
	return sortedListToBST(&head, n);
}

//construct BST and return root
struct bTreeNode* sortedListToBST(struct node **head_reff, int n){
	if (n<= 0){
		return NULL;
	}
	//create left side of tree recursively
	struct bTreeNode *left= sortedListToBST(head_reff, n/2);
	
	//allocate memory for root and connect left subtree.
	struct bTreeNode *root = newNode((*head_reff)->wager);
	root->left = left;
	
	//iterate throught list.
	*head_reff = (*head_reff)->next
	;
	//create right side of tree recursively
	root->right = sortedListToBST(head_reff, n-n/2-1);
	
	return root;
}

//iterate through list and count nodes
int countNodes(struct node *head){
	int count = 0;
	struct node *temp = head;
	
	while(temp){
		temp = temp->next;
		count++;
	}
	return count;
}

//create new node for BST
struct bTreeNode* newNode(int wager){
	struct bTreeNode* btnode = (struct bTreeNode*)malloc(sizeof(struct bTreeNode));
	btnode->wager = wager;
	btnode->left = NULL;
	btnode->right = NULL;
	
	return btnode;
};

//print a preorder traversal of BST
void printBST(struct bTreeNode* btnode){
	if(btnode == NULL){
		//printf("\nThe tree is empty\n");
		return;
	}
	printf("\nwager: %d\n", btnode->wager);
	printBST(btnode->left);
	printBST(btnode->right);
}

void insertToList(char r, int wager, int score, int dscore){
    struct node *link = (struct node*)malloc(sizeof(struct node));
    link->result = r;
    link->wager = wager;
    link->bank = cash;
    link->score = score;
    link->dscore = dscore;
    link->next = head;
    head=link;
};

void printList(){
    struct node *ptr = head;
    while(ptr != NULL){
        printf("outcome: %c\tWager: %d\t Bank Balance: %d\tPlayer Score: %d\tDealer Score: %d\n",ptr->result, ptr->wager, ptr->bank, ptr->score, ptr->dscore);
        ptr=ptr->next;
    }

};

int dealer(int dealerScore){
	int randCard = 0;

	if (dealerScore<17){
		srand((unsigned) time(NULL) + 1);
    	randCard=rand()%13+1;
	}

	//if card is Jack, Queen, King or Ace it will be set to 10
	if(randCard > 10){
		randCard = 10;
	}
	//Ace value condition check.
	else if(randCard == 13){
		if (dealerScore>11){
			randCard = 1;
		}
		else{
			randCard = 11;
		}
	}


	dealerScore = dealerScore + randCard;
	return dealerScore;
};


int gameStart(){
	//declare local variables
	int score = 0;
	int temp = 0;
	int choice;
	int wager = 0;
	int opponentScore = 0;

	printf("\n\nBank: %d\n\n", cash);
	score = generateSuit();
	opponentScore = dealer(opponentScore);
	printf("Player Card Value: %d\tDealers Card Value: %d\n", score, opponentScore);
	wager = bet(cash);

	//loop until either player chooses to exit or player loses
	while(score<=21){
		if(score<21){
			
			printf("\n\nDealers Score: %d\n\n", opponentScore);
			printf("\n\nChoose an option: \n1. Hit\n2.Stay\n");
			scanf("%d", &choice);

			//condition "hit", draws another card for player
			if(choice == 1){
				temp = generateSuit();
				score = score + temp;
				printf("\n\nPlayer Score: %d\t Dealer Score: %d\n", score, opponentScore);
			}


			//condition "stay", ends players drawing phase and the dealer tries to get a better hand then the player.
			else if (choice == 2){
				//while the dealer has less than 17 or less than the player it will draw.
				while(opponentScore < 17 || opponentScore <= score){
					opponentScore = dealer(opponentScore);

					//display dealers card values for the user to view
					printf("Dealers Score: %d\n", opponentScore);
				}
				//Condiiton "Dealer wins with a better score"
				if(opponentScore > score && opponentScore<=21){
					printf("The dealer beat you!");
					cash = cash - wager;

					losses++;
					insertToList('L', wager, score, opponentScore);
				}

				//Condition "Dealer Bust", dealer goes over 21 and player wins
				if(opponentScore>21){
					printf("\nCongratulations! The dealer busted! You Win!\n");
					cash = cash + wager;

					wins++;
					insertToList('W', wager, score, opponentScore);
				}
				break;
			}
		}

		else if (score == 21){
			printf("BLACK JACK!\n\n You won!\n\n");
			cash = cash + wager;

			wins++;
			insertToList('W', wager, score, opponentScore);
			break;
		}

}
	if(score > 21){
		printf("\n\n Bust...Sorry you lost.\n\n");
		cash = cash - wager;

		losses++;
		insertToList('L', wager, score, opponentScore);
	}

};

int bet(int cash){
	int wager;
	int credits = cash;

	printf("\n\nPlease enter bet: ");
	scanf("%d", &wager);

	while(wager>credits){
		printf("You do not have enough funds to proceed with that bet.\n Please enter bet: ");
		scanf("%d", &wager);
	}

	return wager;

};

//generate the suit of the card.
int generateSuit(){
	int randCard = 0;

	srand((unsigned) time(NULL));
	randCard = rand()%4+1;

	//Call function that creates the card corresponding to the correct suit.
	if(randCard==1)
     {
         heartCard();
         //l=k;
     }

     if(randCard==2)
     {
         diamondCard();
         //l=k;
     }

     if(randCard==3)
     {
         spadeCard();
         //l=k;
     }

     if(randCard==4)
     {
         clubCard();
         //l=k;
     }
     //return l;
};

//Create a heart card
int heartCard(){
	int randCard = 0;

	srand((unsigned) time(NULL));
	randCard = rand()%13+1;

	if(randCard<=9){
    //Heart Card
	    printf("-------\n");
	    printf("|%c    |\n", heart);
	    printf("|  %d  |\n", randCard);
	    printf("|    %c|\n", heart);
	    printf("-------\n");
    }


    //create Jack and set value of card to 10
    if (randCard == 10){
    	printf("-------\n");
	    printf("|%c    |\n", heart);
	    printf("|  J  |\n");
	    printf("|    %c|\n", heart);
	    printf("-------\n");
	}
	if (randCard == 11){
    	printf("-------\n");
	    printf("|%c    |\n", heart);
	    printf("|  Q  |\n");
	    printf("|    %c|\n", heart);
	    printf("-------\n");
	    randCard = 10;
	}
	if (randCard == 12){
    	printf("-------\n");
	    printf("|%c    |\n", heart);
	    printf("|  K  |\n");
	    printf("|    %c|\n", heart);
	    printf("-------\n");
	    randCard = 10;
	}
	if (randCard == 13){
    	printf("-------\n");
	    printf("|%c    |\n", heart);
	    printf("|  A  |\n");
	    printf("|    %c|\n", heart);
	    printf("-------\n");
	    randCard = 11;
	}

	return randCard;
};

int diamondCard(){
	int randCard = 0;

	srand((unsigned) time(NULL));
	randCard = rand()%13+1;

	if(randCard<=9){
    //Diamaon Card
	    printf("-------\n");
	    printf("|%c    |\n", diamond);
	    printf("|  %d  |\n", randCard);
	    printf("|    %c|\n", diamond);
	    printf("-------\n");
    }

    if (randCard == 10){
    	printf("-------\n");
	    printf("|%c    |\n", diamond);
	    printf("|  J  |\n");
	    printf("|    %c|\n", diamond);
	    printf("-------\n");
	}
	if (randCard == 11){
    	printf("-------\n");
	    printf("|%c    |\n", diamond);
	    printf("|  Q  |\n");
	    printf("|    %c|\n", diamond);
	    printf("-------\n");
	    randCard = 10;
	}
	if (randCard == 12){
    	printf("-------\n");
	    printf("|%c    |\n", diamond);
	    printf("|  K  |\n");
	    printf("|    %c|\n", diamond);
	    printf("-------\n");
	    randCard = 10;
	}
	if (randCard == 13){
    	printf("-------\n");
	    printf("|%c    |\n", diamond);
	    printf("|  A  |\n");
	    printf("|    %c|\n", diamond);
	    printf("-------\n");
	    randCard = 11;
	}

	return randCard;
};


int spadeCard(){
	int randCard = 0;

	srand((unsigned) time(NULL));
	randCard = rand()%13+1;

	if(randCard<=9){
    //Heart Card
	    printf("-------\n");
	    printf("|%c    |\n", spade);
	    printf("|  %d  |\n", randCard);
	    printf("|    %c|\n", spade);
	    printf("-------\n");
    }

    if (randCard == 10){
    	printf("-------\n");
	    printf("|%c    |\n", spade);
	    printf("|  J  |\n");
	    printf("|    %c|\n", spade);
	    printf("-------\n");
	}
	if (randCard == 11){
    	printf("-------\n");
	    printf("|%c    |\n", spade);
	    printf("|  Q  |\n");
	    printf("|    %c|\n", spade);
	    printf("-------\n");
		randCard = 10;
	}
	if (randCard == 12){
    	printf("-------\n");
	    printf("|%c    |\n", spade);
	    printf("|  K  |\n");
	    printf("|    %c|\n", spade);
	    printf("-------\n");
		randCard = 10;
	}
	if (randCard == 13){
    	printf("-------\n");
	    printf("|%c    |\n", spade);
	    printf("|  A  |\n");
	    printf("|    %c|\n", spade);
	    printf("-------\n");
	    randCard = 11;
	}

	return randCard;
};


int clubCard(){
	int randCard = 0;

	srand((unsigned) time(NULL));
	randCard = rand()%13+1;

	if(randCard<=9){
    //Heart Card
	    printf("-------\n");
	    printf("|%c    |\n", club);
	    printf("|  %d  |\n", randCard);
	    printf("|    %c|\n", club);
	    printf("-------\n");
    }

    if (randCard == 10){
    	printf("-------\n");
	    printf("|%c    |\n", club);
	    printf("|  J  |\n");
	    printf("|    %c|\n", club);
	    printf("-------\n");
	}
	if (randCard == 11){
    	printf("-------\n");
	    printf("|%c    |\n", club);
	    printf("|  Q  |\n");
	    printf("|    %c|\n", club);
	    printf("-------\n");
	    randCard = 10;
	}
	if (randCard == 12){
    	printf("-------\n");
	    printf("|%c    |\n", club);
	    printf("|  K  |\n");
	    printf("|    %c|\n", club);
	    printf("-------\n");
	    randCard = 10;
	}
	if (randCard == 13){
    	printf("-------\n");
	    printf("|%c    |\n", club);
	    printf("|  A  |\n");
	    printf("|    %c|\n", club);
	    printf("-------\n");
	    randCard = 11;
	}

	return randCard;
};






int main(void){
	int choice;

	printf("Welcome to Black Jack!\n Choose an option below:\n 1. New Game\n 2. Rules of Black Jack\n 3. Show W/L\n 4. Create Binary Tree\n 5. Exit\n");
	scanf("%d", &choice);

	 if((choice<1) || (choice>5)) // If invalid choice entered
            {
                printf("\nIncorrect Choice. Please enter 1, 2, 3, 4 or 5\n");
                scanf("%d", &choice);
            }

	while(choice!=5){

		switch(choice) {
			case 1:
				printf("Shuffling deck\n");
				gameStart();
				break;
			case 2:
				printf("The Rules of Black jack are listed below\n\n\n\n");
				printf("RULES:\nBlackjack may be played with one to eight decks of 52-card decks.");
				//printf("Aces may be counted as 1 or 11 points, 2 to 9 according to pip value, and tens and face cards count as ten points.\nThe value of a hand is the sum of the point values of the individual cards. Except, a blackjack is the highest hand, consisting of an ace and any 10-point card, and it outranks all other 21-point hands.\nAfter the players have bet, the dealer will give two cards to each player and two cards to himself. One of the dealer cards is dealt face up. The facedown card is called the hole card.\nIf the dealer has an ace showing, he will offer a side bet called "insurance." This side wager pays 2 to 1 if the dealer's hole card is any 10-point card. Insurance wagers are optional and may not exceed half the original wager.\nIf the dealer has a ten or an ace showing (after offering insurance with an ace showing), then he will peek at his facedown card to see if he has a blackjack. If he does, then he will turn it over immediately.\nIf the dealer does have a blackjack, then all wagers (except insurance) will lose, unless the player also has a blackjack, which will result in a push. The dealer will resolve insurance wagers at this time.\nPlay begins with the player to the dealer's left. The following are the choices available to the player: \nStand: Player stands pat with his cards.\nHit: Player draws another card (and more if he wishes). If this card causes the player's total points to exceed 21 (known as "breaking" or "busting") then he loses.\nDouble: Player doubles his bet and gets one, and only one, more card.\nSplit: If the player has a pair, or any two 10-point cards, then he may double his bet and separate his cards into two individual hands. The dealer will automatically give each card a second card. Then, the player may hit, stand, or double normally. However, when splitting aces, each ace gets only one card. Sometimes doubling after splitting is not allowed. If the player gets a ten and ace after splitting, then it counts as 21 points, not a blackjack. Usually the player may keep re-splitting up to a total of four hands. Sometimes re-splitting aces is not allowed.\nSurrender: The player forfeits half his wager, keeping the other half, and does not play out his hand. This option is only available on the initial two cards, and depending on casino rules, sometimes it is not allowed at all.\nAfter each player has had his turn, the dealer will turn over his hole card. If the dealer has 16 or less, then he will draw another card. A special situation is when the dealer has an ace and any number of cards totaling six points (known as a "soft 17"). At some tables, the dealer will also hit a soft 17.\nIf the dealer goes over 21 points, then any player who didn't already bust will win.\nIf the dealer does not bust, then the higher point total between the player and dealer will win.\nWinning wagers pay even money, except a winning player blackjack usually pays 3 to 2. Some casinos have been short-paying blackjacks, which is a rule strongly in the casino's favor.\n");
				break;
			case 3:
			    printf("Printing Win/Loss History: \n");
                printList();
				break;
			case 4:
				printf("PreOrder Traversal Binary Tree: \n");
				struct node *ptr = head;
				struct bTreeNode *root = sortBST(head);
				printBST(root);
            case 5:
				break;
			default:
                   printf("\nInvalid Input");
		}
		printf("\n\nChoose an option below:\n 1. New Game\n 2. Rules of Black Jack\n 3. Show W/L\n 4. Create Binary Tree\n 5. Exit\n");
		scanf("%d", &choice);
	}
}
