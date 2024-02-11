#include "Knight.h"


#include <cctype>

char Knight::blackSymbol = blackKnight;
char Knight::whiteSymbol = whiteKnight;

vector<tuple<Position, Board>> Knight::getPossibleMoves(const Position& currentPosition, const Board& board) const {
    
    Position newLocation;
    vector<tuple<Position, Board>> possible;

    RC moves[8] =
    {
            {-1,  2}, { 1,  2},
    {-2,  1},                    { 2,  1},
    {-2, -1},                    { 2, -1},
            {-1, -2}, { 1, -2}
    };


    for each (RC space in moves) {

        int r = currentPosition.getRow() + space.row;
        int c = currentPosition.getRow() + space.col;
        newLocation.setXY(r, c);

        if (Piece::getIsBlack() && board.isNotBlack(newLocation))
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        if (!Piece::getIsBlack() && board.isNotWhite(newLocation))
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }
    
}

void Knight::drawPiece(int rawLocation) const {
    Piece::gout->drawKnight(rawLocation, getIsBlack());
}