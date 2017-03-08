#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Piece {
	char name;
	char team;
	int posRow;
	int posCol;
	int moveCount;
	int captured;
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

void printPiecePositions(struct Piece *pieces, struct ColumnMap *colMap) {
	printf("\n White   Black\n -----   -----\n");
	int i;
	char translatedColWhite;
	char translatedColBlack;
	for (i = 0; i < 16; i++) {
		char translatedColWhite = transColIntToChar(pieces[i].posCol, colMap);
		char translatedColBlack = transColIntToChar(pieces[i+16].posCol, colMap);
		printf(" %c  %c%d   %c  %c%d\n", pieces[i].name, translatedColWhite, pieces[i].posRow, pieces[i+16].name, translatedColBlack, pieces[i+16].posRow);
	}
}

struct Piece * findPiece(int row, int col, struct Piece * pieces, int piecesSize) {
	int i;
	for (i = 0; i < piecesSize; i++) {
		if (pieces[i].posRow == row && pieces[i].posCol == col) {
			return &pieces[i];
		}
	}

	return NULL;
}

void setActivePieces(char activeTeam, struct Piece * pieces, struct Piece * activePieces[16]) {
	int i;
	int start = 0;

	if (activeTeam == 'b') {
		start = 16;
	}

	for (i=0; i<16; i++) {
		activePieces[i] = &pieces[i + start];
	}
}

int main() 
{
	// Define player pieces
	// struct Piece pieces[32] = {
	// 	// white
	// 	{ 'R', 'w', 1, 1, 0, 0 }, { 'N', 'w', 1, 2, 0, 0 }, { 'B', 'w', 1, 3, 0, 0 }, { 'Q', 'w', 1, 4, 0, 0 },
	// 	{ 'K', 'w', 1, 5, 0, 0 }, { 'B', 'w', 1, 6, 0, 0 }, { 'N', 'w', 1, 7, 0, 0 }, { 'R', 'w', 1, 8, 0, 0 },
	// 	{ '-', 'w', 2, 1, 0, 0 }, { '-', 'w', 2, 2, 0, 0 }, { '-', 'w', 2, 3, 0, 0 }, { '-', 'w', 2, 4, 0, 0 },
	// 	{ '-', 'w', 2, 5, 0, 0 }, { '-', 'w', 2, 6, 0, 0 }, { '-', 'w', 2, 7, 0, 0 }, { '-', 'w', 2, 8, 0, 0 },
	// 	// black
	// 	{ 'R', 'b', 8, 1, 0, 0 }, { 'N', 'b', 8, 2, 0, 0 }, { 'B', 'b', 8, 3, 0, 0 }, { 'Q', 'b', 8, 4, 0, 0 },
	// 	{ 'K', 'b', 8, 5, 0, 0 }, { 'B', 'b', 8, 6, 0, 0 }, { 'N', 'b', 8, 7, 0, 0 }, { 'R', 'b', 8, 8, 0, 0 },
	// 	{ '-', 'b', 7, 1, 0, 0 }, { '-', 'b', 7, 2, 0, 0 }, { '-', 'b', 7, 3, 0, 0 }, { '-', 'b', 7, 4, 0, 0 },
	// 	{ '-', 'b', 7, 5, 0, 0 }, { '-', 'b', 7, 6, 0, 0 }, { '-', 'b', 7, 7, 0, 0 }, { '-', 'b', 7, 8, 0, 0 }
	// };

	// DEBUGGING
	struct Piece pieces[32] = {
		// white
		{ 'R', 'w', 1, 1, 0, 0 }, { 'N', 'w', 1, 2, 0, 0 }, { 'B', 'w', 1, 3, 0, 0 }, { 'Q', 'w', 1, 4, 0, 0 },
		{ 'K', 'w', 1, 5, 0, 0 }, { 'B', 'w', 1, 6, 0, 0 }, { 'N', 'w', 1, 7, 0, 0 }, { 'R', 'w', 1, 8, 0, 0 },
		{ '-', 'w', 2, 1, 0, 0 }, { '-', 'w', 2, 2, 0, 0 }, { '-', 'w', 2, 3, 0, 0 }, { '-', 'w', 2, 4, 0, 0 },
		{ '-', 'w', 2, 5, 0, 0 }, { '-', 'w', 2, 6, 0, 0 }, { '-', 'w', 2, 7, 0, 0 }, { '-', 'w', 2, 8, 0, 0 },
		// black
		{ 'R', 'b', 8, 1, 0, 0 }, { 'N', 'b', 8, 2, 0, 0 }, { 'B', 'b', 8, 3, 0, 0 }, { 'Q', 'b', 8, 4, 0, 0 },
		{ 'K', 'b', 8, 5, 0, 0 }, { 'B', 'b', 8, 6, 0, 0 }, { 'N', 'b', 8, 7, 0, 0 }, { 'R', 'b', 8, 8, 0, 0 },
		{ '-', 'b', 7, 1, 0, 0 }, { '-', 'b', 7, 2, 0, 0 }, { '-', 'b', 7, 3, 0, 0 }, { '-', 'b', 7, 4, 0, 0 },
		{ '-', 'b', 3, 5, 0, 0 }, { '-', 'b', 7, 6, 0, 0 }, { '-', 'b', 7, 7, 0, 0 }, { '-', 'b', 7, 8, 0, 0 }
	};	

	// Map column lettering (for Chess notation) to integer for mathematical grid usage
	struct ColumnMap colMap[8] = {
		{ 1, 'a' }, { 2, 'b' }, { 3, 'c' }, { 4, 'd' }, { 5, 'e' }, { 6, 'f' }, { 7, 'g' }, { 8, 'h' }
	};

	// Player turn status and allocation
	char currentTurnPlayer = 'w';
	char nextTurnPlayer = 'b';
	struct Piece * activePieces[16];

	// Skip advancing player turn at end of master loop
	int skipAdvancingTurn = 0;

	// Print initial positions
	printPiecePositions(pieces, colMap);

	// Player input allocation
	char playerInput[6];

	// Start master loop
	while (1) {
		// Determine player turn and set active pieces
		if (currentTurnPlayer == 'w') {
			printf("\nWhite's turn: ");
			nextTurnPlayer = 'b';
			setActivePieces('w', pieces, activePieces);
		} else {
			printf("\nBlack's turn: ");
			nextTurnPlayer = 'w';
			setActivePieces('b', pieces, activePieces);
		}

		// Get player input
		scanf("%s", playerInput);

		// Print board if 'board' text input
		if (strcmp(playerInput, "board") == 0) {
			printPiecePositions(pieces, colMap);
			continue;
		}

		// Convert char col to int
		int translatedColStart = transColCharToInt(playerInput[0], colMap);
		int playerInputRowStart = atoi(&playerInput[1]);
		int translatedColEnd = transColCharToInt(playerInput[3], colMap);
		int playerInputRowEnd = atoi(&playerInput[4]);

		// Find the piece
		struct Piece * playerPiece = findPiece(playerInputRowStart, translatedColStart, *activePieces, 16);
		if (playerPiece == NULL) {
			printf("Invalid piece selected (%c%c%c).", playerInput[0], playerInput[1], playerInput[2]);
			continue;
		}

		// Check piece destination in bounds of board
		if (translatedColEnd > 8 || playerInputRowEnd > 8) {
			printf("Error: Out of board bounds.\n");
			continue;
		}

		// Allocate player piece destination
		struct Piece * playerPieceTarget;

		// Apply piece specific rules
		// pawn (-)
		if (playerPiece->name == '-') {
			// piece is in its starting position
			if (playerPiece->moveCount < 1) {
				// can't move more than 2 rows away
				if (abs(playerInputRowEnd - playerInputRowStart) > 2) {
					printf("Pawn in starting row can only move one or two row(s) ahead.\n");
					continue;
				}
				// can't move laterally more than 1
				if (abs(playerInputRowEnd - playerInputRowStart) > 1 && abs(translatedColEnd - translatedColStart) > 1) {
					printf("Pawn can not move laterally unless capturing.\n");
					continue;
				}
				// capturing up 1 row and left/right 1 column
				if (abs(playerInputRowEnd - playerInputRowStart) == 1 && abs(translatedColEnd - translatedColStart) == 1) {
					playerPieceTarget = findPiece(playerInputRowEnd, translatedColEnd, pieces, 32);
					if (playerPieceTarget == NULL) {
						printf("Can't move there. Pawn can only move laterally to capture.\n");
						continue;
					}
				}
			}

			// can move 1 if more than 1 moves
			if (playerPiece->moveCount > 0 && abs(playerInputRowEnd - playerInputRowStart) > 1) {
				printf("Pawn can only move forward one space, or capture.\n");
				continue;
			}

			// can only move forward
			if (currentTurnPlayer == 'w' && playerInputRowEnd <= playerInputRowStart) {
				printf("Pawn can only move forward.\n");
				continue;
			}
			if (currentTurnPlayer == 'b' && playerInputRowEnd >= playerInputRowStart) {
				printf("Pawn can only move forward.\n");
				continue;
			}
		}

		// Move the piece
		playerPiece->posRow = playerInputRowEnd;
		playerPiece->posCol = translatedColEnd;
		playerPiece->moveCount++;
		if (currentTurnPlayer == 'w') {
			printf("\nWhite moved: %c%c%c%c%c", playerInput[0], playerInput[1], playerInput[2], playerInput[3], playerInput[4]);
		} else {
			printf("\nBlack moved: %c%c%c%c%c", playerInput[0], playerInput[1], playerInput[2], playerInput[3], playerInput[4]);
		}
	}

	return 0;
}
