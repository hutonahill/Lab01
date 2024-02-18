#include "Knight.h"


#include <cctype>

char Knight::blackSymbol = blackKnight;
char Knight::whiteSymbol = whiteKnight;

vector<tuple<Position, Board>> Knight::getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const {

    Position newLocation;
    vector<tuple<Position, Board>> possible;
    const bool amBlack = Piece::getIsBlack();

    if (amBlack != isBlackMove) {
        return possible;
    }

    const int row = currentPosition.getRow();
    const int col = currentPosition.getCol();

    RC moves[8] =
    {
            {-1,  2}, { 1,  2},
    {-2,  1},                    { 2,  1},
    {-2, -1},                    { 2, -1},
            {-1, -2}, { 1, -2}
    };


    for (int index = 0; index < 8; index++) {
        RC space = moves[index];
        int r = row + space.row;
        int c = col + space.col;
        newLocation = Position(r, c);

        if (newLocation.isValid() == true) {
            if (amBlack != board[newLocation].getIsBlack() || board[newLocation].getIsEmpty()) {
                possible.emplace_back(standardMove(currentPosition, newLocation, board));
            }
        }

        
    }
    return possible;
}

void Knight::drawPiece(int rawLocation) const {
    Piece::gout->drawKnight(rawLocation, getIsBlack());
}