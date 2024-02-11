#pragma once
#include "Piece.h"
#include "Position.h"
#include "EmptySpace.h"

class Pawn : public Piece{
public:
    Pawn(bool isBlackInput, ogstream* gout) : Piece(isBlackInput, isBlackInput ? blackSymbol : whtieSymbol, gout) {}

    vector<tuple<Position, Board>> getPossibleMoves(const Position& currentPosition, const Board& board) const override;

    void drawPiece(int rawLocation) const override;

private:
    static char blackSymbol;
    static char whtieSymbol;
};

