#include "Rook.h"
#include "EmptySpace.h"

char Rook::blackSymbol = blackRook;
char Rook::whiteSymbol = whiteRook;

vector<tuple<Position, Board>> Rook::getPossibleMoves(const Position& currentPosition, const Board& board) const {
    int r;
    int c;
    int row = currentPosition.getRow();
    int col = currentPosition.getCol();

    bool amBlack = Piece::getIsBlack();

    vector<tuple<Position, Board>> possible;

    Position newLocation = Position();

    EmptySpace empty = EmptySpace();
    
    RC moves[4] ={
                {0,  1},
        {-1, 0},         {1, 0},
                {0, -1}
    };

    for (int i = 0; i < 4; i++){

        r = row + moves[i].row;
        c = col + moves[i].col;

        newLocation.setXY(r, c);
        while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
            board[newLocation] == ' ')
        {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

            r += moves[i].row;
            c += moves[i].col;
            newLocation.setXY(r, c);
        }
        if (amBlack && board.isNotBlack(newLocation)) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        if (!amBlack && board.isNotWhite(newLocation)) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }
    }

    return possible;
}

void Rook::drawPiece(int rawLocation) const {
    Piece::gout->drawRook(rawLocation, getIsBlack());
}