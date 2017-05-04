# CS3050---Final-Project

Blackjack Card Game by David Heritage & Megan Cochran

## What Project Does
This program functions as a way for the user to enjoy as many virtual Blackjack games as they desire, while also storing accurate statistics on how the games went. For those new to Blackjack, the project also has the option explains the rules to new players so that all can enjoy the game.

## User Input
The user inputted needed to play our Blackjack game has been kept simple to avoid player confusion and due to the nature of the card game. When not in a game, the user is given several options to choose from: 1) Start a New Game, 2) Read the rules of Blackjack, 3) See a history of the users wins and losses, 4) See a binary search tree of the wagers the user has made, or 5) Exit the program. In order to select an option, the user merely needs to type in the number of the option they want and press enter. If an invalid input is submitted, than an error message will appear, the options will be displayed again, and the program will allow the user to select again. For options 2-5, no further input is required from the user besides the inital choice. 

For option 1, once a game starts the user is requested to submit a wager. The user is to type a number (within the amount available in the bank) and press enter to decide their wage. Again, if an invalid option is submitted, an error message will be shown and the user will be allowed to select a wager again. After the wager has been submitted, the user is presented with another two options, 1) Hit or 2) Stay. Invalid input is treated the same as previous examples. Option 2 will end the game and take you back to the main screen, while always telling you the results of the game. Option 1 will do the same if you lose in that round. If you do not, then the two options will be displayed again. This continues until either the user wins or loses the game.

### Sample Inputs

Selecting to play a new game

![New Game Image](https://github.com/M3gster/CS3050-Final-Project/blob/master/Play%20New%20Game.PNG)

Selecting the hit option

![Hit Option Image](https://github.com/M3gster/CS3050-Final-Project/blob/master/Hit%20Option.PNG)

Selecting the stay option

![Stay Option Image](https://github.com/M3gster/CS3050-Final-Project/blob/master/Stay%20Option.PNG)

Selecting another option rather than to play a new game

![Other Option Image](https://github.com/M3gster/CS3050-Final-Project/blob/master/Other%20Option.PNG)

## How to Run
To run the program, all one must do is launch the file. Nothing else is required besides the user input as explained in the earlier section. 

## Testbed
Due to the way that the program is implemented no input testbed is required. The project is all input driven, as a result no sample input is possible. The user must simply input their choices from the options given as the game is played out. 
However, some input is invalid and the program handles it as shown in the images below.

![Wrong  Menu Input Image](https://github.com/M3gster/CS3050-Final-Project/blob/master/Wrong%20Menu%20Input.png)
![Wrong Bet Input Image](https://github.com/M3gster/CS3050-Final-Project/blob/master/Wrong%20Bet%20Input.png)
![Wrong Hit or Stay Input Image](https://github.com/M3gster/CS3050-Final-Project/blob/master/Wrong%20Hit%20or%20Stay%20Input.png)

## Pseudo Code for Core Components

Construct_BST(node * head)

    call Count_Nodes on *head
    return the result of List_to_BST(&head, result of Count_Nodes on *head)

List_to_BST(node * * head_reference, int n)

    if n is greater than or equal to 0
        return NULL
        
     bTreeNode * left = List_to_BST(head_reference, n/2)
     bTreeNode * root = newNode((* head_reference)->wager)
     assign left to root->left
     
     assign (*head_reference)->next to *head_reference
     
     root->right = List_to_BST(head_reference, n-n/2-1)
     
     return root

Count_Nodes(node * head)

    count = 0
    code * temp = head
    
    while temp is true
        assign temp to temp->next
        add 1 to count
        
    return count

NewBST_Node(int wager)

    allocate memory for bTreeNode * btnode
    assign wager to btnode->wager
    assign NULL to btnode's left and right nodes
    
    return btnode

Print_BST(struct bTreeNode * btnode)

    if btnode is NULL
        return
        
     display wager of the node
     print_BST(left child of btnode)
     print_BST(right child of btnode)

Insert_to_List(char r, int wager, int score, int dscore)
    
    allocate memory for node *link
    assign r to link->result 
    assign wager to link->wager
    assign bank to link->cash
    assign score to link->score 
    assign dscore to link->dscore
    assign head to link->next
    
    make head of the list, link

Print_List()

    node *pointer = head
    while pointer isn't NULL
        display the user's outcome, wager, bank balance, their score, and dealer's score of the game
        assign pointer to the next node
        
     games = total number of wins and losses and draws
     display the total number of wins, losses, draws, and total games

Dealer(int dealerScore)
    
    card = 0
    
    if dealerScore is less than 17
        card = random number from 1 to 13
        
    if card is greater than 10
        card = 10
        
    else if card equals 13
        if dealerScore is greater than 11
            card = 1
        else
            card = 11
            
      dealerScore = delearScore + card
      return dealerScore

Game_Start()

    score, temp, wager, opponentScore equal 0
    create variable choice
    
    display cash available in the bank
    score = generate_Suit()
    opponentScore = dealer(opponentScore)
    display the card values for the player and for the dealer
    wager = bet(cash)
    
    while score is less than or equal to 21
        if score is less than 21
            display options to hit or stay
            if selected hit
                temp = generate_suit()
                score equals score plus temp
                displau scores for player and dealer
             else if selected stay
                while dealer has less than 17 or less than the player
                    opponentScore = dealer(opponentScore)
                    display dealer and player scores
                    add 1 to draws
                    insertToList('D', wager, score, opponentScore)
                if dealer has a better score than the player
                    display that the dealer won
                    subtract wager from the player's remaining amount of cash
                    add 1 to losses
                    insertToList('L', wager, score, opponentScore)
                if dealer's score is over 21
                    display that the player was won
                    add wager to the player's remaining amount of money
                    add 1 to wins
                    insertToList('W', wager, score, opponentScore)
                break
                
         else if score equals 21
            display that the player scored a blackgack and they have won
            add wager to the player's remaining amount of money
            add 1 to wins
            insertToList('W', wager, score, opponentScore)
            break
         
         if score is greater than 21
            display that the user has lost
            subtract wager from the player's remaining amount of cash
            add 1 to losses
            insertToList('L', wager, score, opponentScore)

Bet(int c)

    create variable wager
    
    ask user for their wager
        wager = user input
        
    while wager is greater than c
        print error that user input is invalid, and ask them to submit again
        wager = user input
        
    return wager

Generate_Suit()

    num equals 0
    num = random number from 1-4
    
    if num equals 1
        suit is hearts
        call display_card
    if num equals 2
        suit is diamonds
        call display_card
    if num equals 3
        suit is spades
        call display_card
    if num equals 4
        suit is clubs
        call display_card

Display_Card()

    num equals 0
    num = random number from 1-13
    
    if num less than or equal to 9
      card has a value of num in the chosen suit
      print visual of card
    if num equals 10
      card is a jack in the chosen suit
      print visual of card
    if num equals 11
      card is a queen in the chosen suit
      print visual of card
    if num equals 12
      card is a king in the chosen suit
      print visual of card
    if num equals 13
      card is an ace in the chosen suit
      print visual of card
      
    return num
