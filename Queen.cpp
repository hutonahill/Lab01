#include "Queen.h"
#include "EmptySpace.h"

char Queen::blackSymbol = blackQueen;
char Queen::whiteSymbol = whiteQueen;

vector<tuple<Position, Board>> Queen::getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const {
    int r;
    int c;

    const int row = currentPosition.getRow();
    const int col = currentPosition.getCol();

    Position newLocation = Position();

    const Piece* empty = new EmptySpace();

    const bool amBlack = Piece::getIsBlack();

    vector<tuple<Position, Board>> possible;

    if (amBlack != isBlackMove) {
        return possible;
    }
    
    RC moves[8] =
    {
        {-1,  1}, {0,  1}, {1,  1},
        {-1,  0},          {1,  0},
        {-1, -1}, {0, -1}, {1, -1}
    };
    for each (RC space in moves)
    {
        r = row + space.row;
        c = col + space.col;
        newLocation = Position(r, c);

        // loop though every space in the current direction
        while (newLocation.isValid() &&
            // you hit a peice
            board[newLocation].getIsEmpty()) {



            possible.emplace_back(standardMove(currentPosition, newLocation, board));

            // ideratate the dierection 
            r += space.row;
            c += space.col;
            newLocation = Position(r, c);
        }

        // if the above loop stoped due to hitting a enemy peice
        if (newLocation.isValid()) {
            // add its location to the list.
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

void Queen::drawPiece(int rawLocation) const {
    Piece::gout->drawQueen(rawLocation, getIsBlack());
}