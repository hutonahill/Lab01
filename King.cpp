#include "King.h"
#include "EmptySpace.h"

char King::blackSymbol = blackKing;
char King::whiteSymbol = whiteKing;

vector<tuple<Position, Board>> King::getPossibleMoves(const Position& currentPosition, const Board& board) const {
    
    int r;
    int c;

    int row = currentPosition.getRow();
    int col = currentPosition.getCol();

    Position newLocation = Position();

    EmptySpace empty = EmptySpace();

    bool amBlack = Piece::getIsBlack();
    
    vector<tuple<Position, Board>> kingMoves;
    vector <tuple<int, char*>> possible;

    RC moves[8] =
    {
        {-1,  1}, {0,  1}, {1,  1},
        {-1,  0},          {1,  0},
        {-1, -1}, {0, -1}, {1, -1}
    };


    for each (RC space in moves) {
        r = row + space.row;
        c = col + space.col;
        newLocation.set(r, c);
        if (amBlack && board.isNotBlack(newLocation)) {
            kingMoves.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        if (!amBlack && board.isNotWhite(newLocation)) {
            kingMoves.emplace_back(standardMove(currentPosition, newLocation, board));
        }
    }

    // what about castling?
    // Black castling
    if (amBlack) {

        if (row == 0 && col == 4) {
            // We dont have access to move history yet, so for now we just check of there
            // is a rook in the right place.

            // note that we also need to check if thse locations are under attack once check
            // has been implimented.

            // Quean Side
            if (board[Position(row, 0)] == blackRook &&
                board[Position(row, 0)] == empty &&
                board[Position(row, 0)] == empty &&
                board[Position(row, 0)] == empty) {
                newLocation.set(row, 2);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[Position(row, 0)] = empty;
                tempBoard[Position(row, 3)] = board[Position(row, 0)];

                kingMoves.emplace_back(output);

            }

            // King Side
            if (board[Position(row, 7)] == blackRook &&
                board[Position(row, 6)] == empty &&
                board[Position(row, 5)] == empty) {
                newLocation.set(row, 6);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[Position(row, 7)] = empty;
                tempBoard[Position(row, 5)] = board[Position(row, 7)];

                kingMoves.emplace_back(output);
            }
        }
    }

    // White castling
    else {
        if (row == 7 && col == 4) {
            // We dont have access to move history yet, so for now we just check of there
            // is a rook in the right place.

            // note that we also need to check if thse locations are under attack once check
            // has been implimented.

            // Quean Side
            if (board[Position(row, 0)] == whiteRook &&
                board[Position(row, 1)] == empty &&
                board[Position(row, 2)] == empty &&
                board[Position(row, 3)] == empty) {
                newLocation.set(row, 2);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[Position(row, 0)] = empty;
                tempBoard[Position(row, 3)] = board[Position(row, 0)];

                kingMoves.emplace_back(output);

            }

            // King Side
            if (board[Position(row, 7)] == whiteRook &&
                board[Position(row, 6)] == empty &&
                board[Position(row, 5)] == empty) {
                newLocation.set(row, 6);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[Position(row, 7)] = empty;
                tempBoard[Position(row, 5)] = board[Position(row, 7)];
                kingMoves.emplace_back(output);
            }
        }
    }

    // what about check?

    // We are going to have to check to see if any of the kings moves put them in check eventualy, 
    // so ive put the kings moves in a seprate set and we combine them at the end of the if.
    return kingMoves;
}

void King::drawPiece(int rawLocation) const {
    Piece::gout->drawKing(rawLocation, getIsBlack());
}