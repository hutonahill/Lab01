#pragma once
#include <vector>

#include "Position.h"
#include "Piece.h"
#include "uiInteract.h"

#include "uiDraw.h" 

using namespace std;

class Piece;

class Board{
public:
	Board(Board* oldBoard);

	Board(ogstream& goutInput, const vector<Piece*>& startingBoard);

	Board();

	bool isWhite(Position location) const;

	bool isNotWhite(Position location) const;

	bool isBlack(Position location) const;

	bool isNotBlack(Position location) const;

	void drawBoard(const Interface& ui, const vector <Position>& possible);

	bool inCheck(const Position location, bool blackAttacking) const;

	ogstream* getGout();
	
	void set(const Position location, const Piece* newPiece) {
		
		set(location.getLocation(), newPiece);
	}

	void set(const int location, const Piece* newPiece) {

		//delete board[location];

		board[location] = const_cast<Piece*>(newPiece);
	}

	Board& operator=(const Board& other);

	const Piece& operator[](const Position& position) const;

	Piece& operator[](const Position& position);

	const Piece& operator[](const int& position) const;

	Piece& operator[](const int& position);

	operator const char* () const;

	

private:
	ogstream* gout;
	vector<Piece*> board;
};

