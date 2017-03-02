#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct Square {
// 	char color;
// 	int positionX;
// 	int positionY;
// }

// void drawGrid()
// {
// 	struct Square board[64];

// 	int rowCount = 8;
// 	int colCount = 8;
// 	int squareNum = 0;
// 	int row;
// 	int col;
// 	char color = 'b';

// 	for (row = 0; row < rowCount; row++) {
// 		for (col = 0; col < colCount; col++) {
// 			board[squareNum] = { *color, row+1, col+1 };
// 			squareNum++;
// 		}
// 	}	

// }

struct Piece {
	char name;
	int posRow;
	int posCol;
};

struct ColumnMap {
	int integer;
	char character;
};

char transColIntToChar(int posCol, struct ColumnMap *colMap) {
	int i;
	for (i=0; i < 8; i++) {
		if (colMap[i].integer == posCol) {
			return colMap[i].character;
		}
	}
}

int transColCharToInt(char posCol, struct ColumnMap *colMap) {
	int i;
	for (i=0; i < 8; i++) {
		if (colMap[i].character == posCol) {
			return colMap[i].integer;
		}
	}
}

// void printHelpMenu() {
// 	printf("\n Options:\n [n]ew game.\n [p]iece positions.\n [h]elp and options.\n [e]xit game.\n\n");
// }

void printPiecePositions(struct Piece *whitePieces, struct Piece *blackPieces, struct ColumnMap *colMap) {
	printf(" White   Black\n -----   -----\n");
	int i;
	char translatedColWhite;
	char translatedColBlack;
	for (i = 0; i < 16; i++) {
		char translatedColWhite = transColIntToChar(whitePieces[i].posCol, colMap);
		char translatedColBlack = transColIntToChar(blackPieces[i].posCol, colMap);
		printf(" %c  %c%d   %c  %c%d\n", whitePieces[i].name, translatedColWhite, whitePieces[i].posRow, blackPieces[i].name, translatedColBlack, blackPieces[i].posRow);
	}
}

// void startNewGame(char *currentTurnPlayer)
// {
// 	scanf("%c", currentTurnPlayer);
// 	printf("You selected: %c", *currentTurnPlayer);
// 	// Who's going first
// 	// printf("Who's going first? (`w` or `b`)?\n> ");
// 	// scanf("%c", currentTurnPlayer);
// }

int main() 
{

	// Define player pieces and start position
	struct Piece whitePieces[16] = {
		{ 'R', 1, 1 },		
		{ 'N', 1, 2 },
		{ 'B', 1, 3 },
		{ 'Q', 1, 4 },
		{ 'K', 1, 5 },
		{ 'B', 1, 6 },
		{ 'N', 1, 7 },
		{ 'R', 1, 8 },
		{ '-', 2, 1 },
		{ '-', 2, 2 },
		{ '-', 2, 3 },
		{ '-', 2, 4 },
		{ '-', 2, 5 },
		{ '-', 2, 6 },
		{ '-', 2, 7 },
		{ '-', 2, 8 }
	};
	struct Piece blackPieces[16] = {
		{ 'R', 8, 1 },		
		{ 'N', 8, 2 },
		{ 'B', 8, 3 },
		{ 'Q', 8, 4 },
		{ 'K', 8, 5 },
		{ 'B', 8, 6 },
		{ 'N', 8, 7 },
		{ 'R', 8, 8 },
		{ '-', 7, 1 },
		{ '-', 7, 2 },
		{ '-', 7, 3 },
		{ '-', 7, 4 },
		{ '-', 7, 5 },
		{ '-', 7, 6 },
		{ '-', 7, 7 },
		{ '-', 7, 7 }
	};

	struct ColumnMap colMap[8] = {
		{ 1, 'a' }, { 2, 'b' }, { 3, 'c' }, { 4, 'd' },
		{ 5, 'e' }, { 6, 'f' }, { 7, 'g' }, { 8, 'h' }
	};

	// Player turn
	char currentTurnPlayer = 'w';
	char nextTurnPlayer = 'b';
	struct Piece *activePieces;

	// Skip changing turns or not
	int skipAdvancingTurn = 0;

	// Print initial positions
	printPiecePositions(whitePieces, blackPieces, colMap);

	// Instantiate player input
	char playerInput[6];
	while (1) {

		// Determine player turn
		if (currentTurnPlayer == 'w') {
			printf("White's turn: ");
			nextTurnPlayer = 'b';
			activePieces = whitePieces;
		} else {
			printf("Black's turn: ");
			nextTurnPlayer = 'w';
			activePieces = blackPieces;
		}

		// Get player input
		scanf("%s", playerInput);

		// Print board if 'board' text input
		if (strcmp(playerInput, "board") == 0) {
			printPiecePositions(whitePieces, blackPieces, colMap);
			skipAdvancingTurn = 1;
		}

		// Move the piece
		// e2-e4 pawn e column, 2nd row move to e column, 4th row
		int i;
		for (i = 0; i < 16; i++) {
			// Convert char col to int
			int translatedColStart = transColCharToInt(playerInput[0], colMap);
			int playerInputRowStart = atoi(&playerInput[1]);
			int translatedColEnd = transColCharToInt(playerInput[3], colMap);

			// Find piece
			if (activePieces[i].name == playerInput[2] && activePieces[i].posCol == translatedColStart && activePieces[i].posRow == playerInputRowStart) {
				// Check that piece is of correct team

				// Check that piece wants to move within bounds of board

				// Check that piece can move according to its rules

				// Check if piece collides with other piece

				// Move it
				activePieces[i].posCol = translatedColEnd;
				activePieces[i].posRow = atoi(&playerInput[4]);
				printPiecePositions(whitePieces, blackPieces, colMap);
				continue;
			}
		}

		if (skipAdvancingTurn == 0) {
			currentTurnPlayer = nextTurnPlayer;
		}
	}

	// printf("\nWELCOME TO CHESS IN C\n");
	// printf("\nWhat would you like to do (`h` for options)?\n> ");
	// int firstRun = 1;
	// char input;
	// char currentTurnPlayer;
	// while (1) {
	// 	switch (input) {
	// 		case 'n':
	// 			startNewGame(&currentTurnPlayer);
	// 			// printf("It's %c's turn.\n", *currentTurnPlayer);
	// 			break;
	// 		case 'e':
	// 			printf("Bye, bye!\n\n");
	// 			return 0;
	// 		break;
	// 		case 'p':
	// 			printPiecePositions(whitePieces, blackPieces);
	// 			break;
	// 		case 'h':
	// 			printHelpMenu();
	// 			break;
	// 	}
	// 	scanf("%c", &input);			
	// 	printf("> ");

	// 	// printf("%c", input);
	// 	// printPiecePositions(whitePieces, blackPieces);
	// }

	// printf("White   Black\n-----   -----\n");
	// int i;
	// for (i = 0; i < 16; i++) {
	// 	printf("%c  %c%d   %c  %c%d\n", whitePieces[i].name, whitePieces[i].posCol, whitePieces[i].posRow, blackPieces[i].name, blackPieces[i].posCol, blackPieces[i].posRow);
	// }

	// // Get the piece to move
	// char inputPiece;
	// int inputPosX;
	// int inputPosY;
	// printf("----\nWhat piece would you like to move (eg p2,6)\n>");
	// scanf("%c%d,%d", &inputPiece, &inputPosX, &inputPosY);
	// printf("----\nYou entered: %c%d,%d\n", inputPiece, inputPosX, inputPosY);
	
	// // Locate the piece to move
	// struct Piece * selectedPiece;
	// int pieceFound = 0;
	// for (i = 0; i < 16; i++) {
	// 	if (whitePieces[i].positionX == inputPosX && whitePieces[i].positionY == inputPosY) {
	// 		selectedPiece = &whitePieces[i];
	// 		pieceFound = 1;
	// 		break;
	// 	}
	// }

	// if (pieceFound == 1) {	
	// 	printf("Found it: %c\n", selectedPiece->name);
	// } else {
	// 	printf("Didn't find it.\n");
	// }

	// // Move the piece
	// int newInputPosX;
	// int newInputPosY;
	// char confirm[1];
	// printf("Where would you like to move the %c at %d, %d? (eg 4,6)?\n>", inputPiece, inputPosX, inputPosY);
	// scanf("%d,%d", &newInputPosX, &newInputPosY);
	// //printf("Are you sure you want to move %c from %d, %d to %d, %d? (y/n)\n>", inputPiece, inputPosX, inputPosY, newInputPosX, newInputPosY);
	// //scanf("%c", &confirm);

	// //printf("Confirmed: %c", confirm);

	// //if (*confirm == 'y')
	// //{
	// 	// Move the piece
	// 	selectedPiece->positionX = newInputPosX;
	// 	selectedPiece->positionY = newInputPosY;
	// 	printf("New position for %c: %d, %d", inputPiece, selectedPiece->positionX, selectedPiece->positionY);
	// //}

	return 0;
}
