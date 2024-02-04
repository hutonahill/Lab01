#pragma once

#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for draw*
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include <tuple>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;
static class chessUtil
{


public:
	static const char whitePawn = 'P';
	static const char whiteKnight = 'N';
	static const char whiteBishop = 'B';
	static const char whiteRook = 'R';
	static const char whiteQueen = 'Q';
	static const char whiteKing = 'K';

	static const char blackPawn = 'p';
	static const char blackKnight = 'n';
	static const char blackBishop = 'b';
	static const char blackRook = 'r';
	static const char blackQueen = 'q';
	static const char blackKing = 'k';

	const char emptySpace = ' ';

	chessUtil() {};

	bool move(char* board, int positionFrom, int positionTo);

	tuple<int, char*> standardMove(int location, int newLocation, const char* board);
	set <tuple<int, char*>> getPossibleMoves(const char* board, int location);

	inline bool isBlack(const char* board, int row, int col);
	inline bool isNotBlack(const char* board, int row, int col);
	inline bool isWhite(const char* board, int row, int col);
	inline bool isNotWhite(const char* board, int row, int col);



};

