#pragma once
#include "Piece.h"
class EmptySpace : public Piece{
public:
	EmptySpace() : Piece(false, Piece::emptySpace, &ogstream(), true){}

	vector<tuple<Position, Board>> getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const override {
		vector<tuple<Position, Board>> empty;
		return empty;
	}

	void drawPiece(int rawLocation) const override {
		int hello = 1;
	}

};

