#pragma once
#include "Piece.h"
class EmptySpace : public Piece{
public:
	EmptySpace() : Piece(){}

	vector<tuple<Position, Board>> getPossibleMoves(const Position& currentPosition, const Board& board) const override {
		vector<tuple<Position, Board>> empty;
		return empty;
	}

	void drawPiece(int rawLocation) const override {}

};

