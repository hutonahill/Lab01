#pragma once
#include <vector>

#include "Position.h"
#include "Piece.h"
#include "uiInteract.h"

#include "uiDraw.h" 

using namespace std;

class Board{
public:
	Board(Board* oldBoard);

	Board(ogstream* goutInput);

	Board();

	bool isWhite(Position location) const;

	bool isNotWhite(Position location) const;

	bool isBlack(Position location) const;

	bool isNotBlack(Position location) const;

	void drawBoard(const Interface& ui, const vector <Position>& possible);

	ogstream* getGout();

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

