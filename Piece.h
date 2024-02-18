#pragma once
#include "Position.h"
#include "Board.h"
#include "uiDraw.h"

#include <vector>
#include <tuple>
#include <functional>

using namespace std;

class Board;

struct RC {
	int row;
	int col;
};

using DrawFunction = function<void(int position, bool isBlack)>;

class Piece
{

public:
	
	static const char blackPawn = 'P';
	static const char blackKnight = 'N';
	static const char blackBishop = 'B';
	static const char blackRook = 'R';
	static const char blackQueen = 'Q';
	static const char blackKing = 'K';

	static const char whitePawn = 'p';
	static const char whiteKnight = 'n';
	static const char whiteBishop = 'b';
	static const char whiteRook = 'r';
	static const char whiteQueen = 'q';
	static const char whiteKing = 'k';

	const char emptySpace = '5';

	virtual vector<tuple<Position, Board>> getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const = 0;
	
	virtual void drawPiece(int rawLocation) const = 0;

	Piece(bool isBlackInput, char symbolInput, ogstream* goutInput);
	Piece(bool isBlackInput, char symbolInput, ogstream* goutInput, bool IsEmptyInput) : 
		Piece(isBlackInput, symbolInput, goutInput) {
		isEmpty = IsEmptyInput;
	}
	Piece();
	Piece(Piece* oldPiece);

	bool getIsBlack() const;

	char getSymbol() const;

	bool getIsEmpty() const;

	bool operator==(const Piece& other) const {
		return symbol == other.symbol;
	}
	bool operator==(const char other) const {
		return symbol == other;
	}

	operator char() const {
		return symbol;
	}

	

protected:
	tuple<Position, Board> standardMove(const Position& location, const Position& newLocation, const Board& board) const;
	ogstream* gout;

private:
	bool isBlack;
	bool isEmpty;
	char symbol;
	

};

