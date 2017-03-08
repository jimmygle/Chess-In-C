#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Piece {
	char name;
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

void printPiecePositions(struct Piece *whitePieces, struct Piece *blackPieces, struct ColumnMap *colMap) {
	printf("\n White   Black\n -----   -----\n");
	int i;
	char translatedColWhite;
	char translatedColBlack;
	for (i = 0; i < 16; i++) {
		char translatedColWhite = transColIntToChar(whitePieces[i].posCol, colMap);
		char translatedColBlack = transColIntToChar(blackPieces[i].posCol, colMap);
		printf(" %c  %c%d   %c  %c%d\n", whitePieces[i].name, translatedColWhite, whitePieces[i].posRow, blackPieces[i].name, translatedColBlack, blackPieces[i].posRow);
	}
}

struct Piece * findPiece(int row, int col, struct Piece *whitePieces, struct Piece *blackPieces) {
	struct Piece * foundPiece;

	int i;
	for (i = 0; i < 16; i++) {
		if (whitePieces[i].posRow == row && whitePieces[i].posCol == col) {
			return &whitePieces[i];
		} else if (blackPieces[i].posRow == row && blackPieces[i].posCol == col) {
			return &blackPieces[i];
		}
	}

	return NULL;
}

int main() 
{

	// Define player pieces and start position
	struct Piece whitePieces[16] = {
		{ 'R', 1, 1, 0, 0 }, { 'N', 1, 2, 0, 0 }, { 'B', 1, 3, 0, 0 }, { 'Q', 1, 4, 0, 0 },
		{ 'K', 1, 5, 0, 0 }, { 'B', 1, 6, 0, 0 }, { 'N', 1, 7, 0, 0 }, { 'R', 1, 8, 0, 0 },
		{ '-', 2, 1, 0, 0 }, { '-', 2, 2, 0, 0 }, { '-', 2, 3, 0, 0 }, { '-', 2, 4, 0, 0 },
		{ '-', 2, 5, 0, 0 }, { '-', 2, 6, 0, 0 }, { '-', 2, 7, 0, 0 }, { '-', 2, 8, 0, 0 }
	};
	struct Piece blackPieces[16] = {
		{ 'R', 8, 1, 0, 0 }, { 'N', 8, 2, 0, 0 }, { 'B', 8, 3, 0, 0 }, { 'Q', 8, 4, 0, 0 },
		{ 'K', 8, 5, 0, 0 }, { 'B', 8, 6, 0, 0 }, { 'N', 8, 7, 0, 0 }, { 'R', 8, 8, 0, 0 },
		{ '-', 7, 1, 0, 0 }, { '-', 7, 2, 0, 0 }, { '-', 7, 3, 0, 0 }, { '-', 7, 4, 0, 0 },
		{ '-', 7, 5, 0, 0 }, { '-', 7, 6, 0, 0 }, { '-', 7, 7, 0, 0 }, { '-', 7, 8, 0, 0 }
	};

	// Map column lettering (for Chess notation) to integer for mathematical grid usage
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
		skipAdvancingTurn = 0;

		// Determine player turn
		if (currentTurnPlayer == 'w') {
			printf("\nWhite's turn: ");
			nextTurnPlayer = 'b';
			activePieces = whitePieces;
		} else {
			printf("\nBlack's turn: ");
			nextTurnPlayer = 'w';
			activePieces = blackPieces;
		}

		// Get player input
		scanf("%s", playerInput);

		// Print board if 'board' text input
		if (strcmp(playerInput, "board") == 0) {
			printPiecePositions(whitePieces, blackPieces, colMap);
			continue;
		}

		// Move the piece
		// e2-e4 pawn e column, 2nd row move to e column, 4th row
		int i;
		for (i = 0; i < 16; i++) {
			// Convert char col to int
			int translatedColStart = transColCharToInt(playerInput[0], colMap);
			int playerInputRowStart = atoi(&playerInput[1]);
			int translatedColEnd = transColCharToInt(playerInput[3], colMap);
			int playerInputRowEnd = atoi(&playerInput[4]);

			// Check input is within bounds of board
			if (translatedColEnd > 8 || playerInputRowEnd > 8) {
				printf("Error: Out of board bounds.\n");
				skipAdvancingTurn = 1;
				break;
			}

			// Find piece
			if (activePieces[i].name == playerInput[2] && activePieces[i].posCol == translatedColStart && activePieces[i].posRow == playerInputRowStart) {
				// Check that piece can move according to its rules
				printf("\nDEBUG: %d %d %d\n", playerInputRowEnd, playerInputRowStart, activePieces[i].moveCount);
				if (playerInput[2] == '-') { // pawn
					// can move 2 if 0 moves
					if (activePieces[i].moveCount < 1 && abs(playerInputRowEnd - playerInputRowStart) > 2) {
						printf("Pawn in starting row can only move one or two row(s) ahead, or capture.\n");
						skipAdvancingTurn = 1;
						break;
					}

					// can move 1 if more than 1 moves
					if (activePieces[i].moveCount > 0 && abs(playerInputRowEnd - playerInputRowStart) > 1) {
						printf("Pawn can only move forward one space, or capture.\n");
						skipAdvancingTurn = 1;
						break;
					}

					// can only move forward
					if (currentTurnPlayer == 'w' && playerInputRowEnd <= playerInputRowStart) {
						printf("Pawn can only move forward.\n");
						skipAdvancingTurn = 1;
						break;
					}
					if (currentTurnPlayer == 'b' && playerInputRowEnd >= playerInputRowStart) {
						printf("Pawn can only move forward.\n");
						skipAdvancingTurn = 1;
						break;
					}

					// is there a piece at desired coordinates
					struct Piece * targetSpacePiece = findPiece(playerInputRowEnd, translatedColEnd, whitePieces, blackPieces);
					if (targetSpacePiece != NULL)
					{
						printf("%c", targetSpacePiece->name);
					}

				}

				// Check if piece collides with other piece

				// Move it
				activePieces[i].posCol = translatedColEnd;
				activePieces[i].posRow = playerInputRowEnd;
				activePieces[i].moveCount++;
				printPiecePositions(whitePieces, blackPieces, colMap);
				if (currentTurnPlayer == 'w') {
					printf("\nWhite moved: %c%c%c%c%c", playerInput[0], playerInput[1], playerInput[2], playerInput[3], playerInput[4]);
				} else {
					printf("\nBlack moved: %c%c%c%c%c", playerInput[0], playerInput[1], playerInput[2], playerInput[3], playerInput[4]);
				}
				continue;
			}
		}

		if (skipAdvancingTurn == 0) {
			currentTurnPlayer = nextTurnPlayer;
		}
	}

	return 0;
}
