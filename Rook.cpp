#include "Rook.h"
#include "EmptySpace.h"

char Rook::blackSymbol = blackRook;
char Rook::whiteSymbol = whiteRook;

vector<tuple<Position, Board>> Rook::getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const {
    int r;
    int c;
    const int row = currentPosition.getRow();
    const int col = currentPosition.getCol();

    const bool amBlack = Piece::getIsBlack();

    vector<tuple<Position, Board>> possible;

    if (amBlack != isBlackMove) {
        return possible;
    }

    Position newLocation = Position();

    const Piece* empty = new EmptySpace();
    
    RC moves[4] ={
                {0,  1},
        {-1, 0},         {1, 0},
                {0, -1}
    };

    for (int i = 0; i < 4; i++){

        r = row + moves[i].row;
        c = col + moves[i].col;

        newLocation = Position(r, c);
        while (newLocation.isValid() &&
            board[newLocation].getIsEmpty())
        {
            if (newLocation.isValid()) {
                possible.emplace_back(standardMove(currentPosition, newLocation, board));
            }
            

            r += moves[i].row;
            c += moves[i].col;
            newLocation = Position(r, c);
        }
        if (newLocation.isValid()){
            if (amBlack && board.isNotBlack(newLocation)) {
                possible.emplace_back(standardMove(currentPosition, newLocation, board));
            }

            if (!amBlack && board.isNotWhite(newLocation)) {
                possible.emplace_back(standardMove(currentPosition, newLocation, board));
            }
        }
    }

    return possible;
}

void Rook::drawPiece(int rawLocation) const {
    Piece::gout->drawRook(rawLocation, getIsBlack());
}