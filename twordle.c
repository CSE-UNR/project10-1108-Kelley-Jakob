// Project 10
// Jakob Kelley
// 5/1/26

#include <stdio.h>

#define FILE_NAME "mystery.txt"
#define MAX_GUESSES 6
#define WORDLENGTH 5

void wordcheck(char word[]);
void playerguess(char guess[], int turn);
int correctguess(char guess[]);
void lowercase(char lower[]);
void guesscheck(char guess[], char word[], char displayguess[], char hints[]);
void array(char displayguess[][WORDLENGTH + 1], char hints[][WORDLENGTH + 1], int count);
int lettercase(char displayguess[]);
int stringlength(char length[]);
void nulldelete(char buffer[]);

int main(){

	char word[WORDLENGTH + 1] = {0};
	char displayguess[MAX_GUESSES][WORDLENGTH + 1] = {{0}};
	char hints[MAX_GUESSES][WORDLENGTH + 1] = {{0}};
	char guess[20];

	int count = 0;
	int won = 0;

	wordcheck(word);

	while(count < MAX_GUESSES && !won){

	playerguess(guess, count + 1);

	if(correctguess(guess)){

	lowercase(guess);

	guesscheck(guess, word, displayguess[count], hints[count]);

	if(lettercase(displayguess[count])){
	won = 1;
	}

	count++;

	if(count == MAX_GUESSES || won){

	if(won && count == 1){
	printf("================================\n");
	printf("\t\t%s\n", displayguess[0]);
	printf("\tYou won in 1 guess!\n");
	printf("\t\tGOATED!\n");
	}
	else if(won){
	printf("================================\n");
	array(displayguess, hints, count);
	printf("You won in %d guesses!\n", count);
	}
	else{
	printf("FINAL GUESS : %s\n", guess);
	printf("================================\n");
	array(displayguess, hints, count);
	printf("You lost, better luck next time!\n");
	}

	}
	else{
	printf("================================\n");
	array(displayguess, hints, count);
	}

	}
	else{
	printf("Your guess must be 5 letters long.\n", WORDLENGTH);
	}
	}

	return 0;
}

void wordcheck(char word[]){//reads the word from the txt file, 5 letters only
	FILE *file = fopen(FILE_NAME, "r");
	if (file == NULL){
	printf("Could not open %s\n", FILE_NAME);
	}

	fgets(word, WORDLENGTH + 1, file);
	nulldelete(word);

	fclose(file);
}

void playerguess(char guess[], int turn){//asks for a word and saves it, sends it to nulldelete to remove newline
	printf("GUESS %d! Enter your guess: ", turn);
	fgets(guess, 20, stdin);
	nulldelete(guess);
}

int correctguess(char guess[]){//makes sure the guess is all letters and contains at least 5 letters
	int length = stringlength(guess);
	int index;

	if(length != WORDLENGTH){
	return 0;
	}

	for(index = 0; index < WORDLENGTH; index++){
	if(!(guess[index] >= 'a' && guess[index] <= 'z') && !(guess[index] >= 'A' && guess[index] <= 'Z')){
	return 0;
	}
	}

	return 1;
}

void lowercase(char lower[]){//helps to convert any letters to lowercase to be checked later, ie dOgGy fixed to doggy
	int index = 0;

	while(lower[index]){
	if(lower[index] >= 'A' && lower[index] <= 'Z'){
	lower[index] += 32;//ascii conversion for upper/lowercase
	}
	index++;
	}
}

void guesscheck(char guess[], char word[], char displayguess[], char hints[]){//used to check a word, gives hints such as uppercasing correct letters and adding the caret to valid letters
	int used[WORDLENGTH] = {0};
	int index, index2;

	for(index = 0; index < WORDLENGTH; index++){
	displayguess[index] = guess[index];
	hints[index] = ' ';
	}

	for(index = 0; index < WORDLENGTH; index++){
	if(guess[index] == word[index]){
	displayguess[index] = guess[index] - 32;//second ascii conversion for upper/lowercase
	used[index] = 1;
	}
	}

	for(index = 0; index < WORDLENGTH; index++){

	if(!(displayguess[index] >= 'A' && displayguess[index] <= 'Z')){

	for(index2 = 0; index2 < WORDLENGTH; index2++){
	if(!used[index2] && guess[index] == word[index2]){
	hints[index] = '^';
	used[index2] = 1;
	break;//loop i attempted to use kept breaking code, found this as a short solution?
	}
	}
	}
	}
}

void array(char displayguess[][WORDLENGTH + 1], char hints[][WORDLENGTH + 1], int count){//shows the user all the previous guesses, with hints
	int row, column;

	for(row = 0; row < count; row++){

	printf("%s\n", displayguess[row]);

	for(column = 0; column < WORDLENGTH; column++){
	printf("%c", hints[row][column]);
	}

	printf("\n");
	}
}

int lettercase(char displayguess[]){//checks for word uppercase and matches to txt file word
	int index;

	for(index = 0; index < WORDLENGTH; index++){
	if(displayguess[index] < 'A' || displayguess[index] > 'Z'){
	return 0;
	}
	}

	return 1;
}

int stringlength(char length[]){//used to count word characters up to newline
	int index = 0;

	while(length[index]){
	index++;
	}

	return index;
}

void nulldelete(char buffer[]){//removed the newline from the world so it can be stored properly
	int index = 0;

	while(buffer[index]){
	if(buffer[index] == '\n'){
	
	buffer[index] = '\0';
	return;
	}
	index++;
	}
}

