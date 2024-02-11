#include "Bishop.h"
#include "EmptySpace.h"


char Bishop::blackSymbol = blackBishop;
char Bishop::whiteSymbol = whiteBishop;

vector<tuple<Position, Board>> Bishop::getPossibleMoves(const Position& currentPosition, const Board& board) const {
    int r;
    int c;

    int row = currentPosition.getRow();
    int col = currentPosition.getCol();

    Position newLocation = Position();

    EmptySpace empty = EmptySpace();

    bool amBlack = Piece::getIsBlack();
    
    vector<tuple<Position, Board>> possible;
    
    RC moves[4] =
    {
        {-1,  1}, {1,  1},
        {-1, -1}, {1, -1}
    };
    for (int i = 0; i < 4; i++) {

        r = row + moves[i].row;
        c = col + moves[i].col;
        newLocation.setXY(r, c);
        while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
            board[newLocation] == ' ') {

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

void Bishop::drawPiece(int rawLocation) const {
    Piece::gout->drawBishop(rawLocation, getIsBlack());
}