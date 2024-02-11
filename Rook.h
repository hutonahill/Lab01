#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(bool isBlackInput, ogstream* gout) : Piece(isBlackInput, isBlackInput ? blackSymbol : whiteSymbol, gout) {}

	vector<tuple<Position, Board>> getPossibleMoves(const Position& currentPosition, const Board& board) const override;

	void drawPiece(int rawLocation) const override;

private:
	static char blackSymbol;
	static char whiteSymbol;
};

