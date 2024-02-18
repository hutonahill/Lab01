#pragma once
#include "Piece.h"
class Knight : public Piece {
public:
	
	Knight(bool isBlackInput, ogstream* gout) : Piece(isBlackInput, isBlackInput ? blackSymbol : whiteSymbol, gout) {}

	vector<tuple<Position, Board>> getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const override;

	void drawPiece(int rawLocation) const override;

private:
	static char blackSymbol;
	static char whiteSymbol;
};

