#include "King.h"
#include "EmptySpace.h"

char King::blackSymbol = blackKing;
char King::whiteSymbol = whiteKing;

vector<tuple<Position, Board>> King::getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const {
    
    int r;
    int c;

    const int row = currentPosition.getRow();
    const int col = currentPosition.getCol();

    Position newLocation = Position();

    const Piece* empty = new EmptySpace();

    const bool amBlack = Piece::getIsBlack();
    
    vector<tuple<Position, Board>> kingMoves;
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


    for each (RC space in moves) {
        r = row + space.row;
        c = col + space.col;
        newLocation = Position(r, c);
        //bool MoveInCheck = board.inCheck(newLocation, !amBlack);
        if (newLocation.isValid() //&& !MoveInCheck
            ){
            
            if (amBlack != board[newLocation].getIsBlack() || 
                board[newLocation].getIsEmpty()) {
                kingMoves.emplace_back(standardMove(currentPosition, newLocation, board));
            }
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
            Position pos1 = Position(row, 0);
            Position pos2 = Position(row, 1);
            Position pos3 = Position(row, 2);
            Position pos4 = Position(row, 3);

            if (board[pos1] == blackRook &&
                //!board.inCheck(pos1, !amBlack) &&
                board[pos2].getIsEmpty() &&
                //!board.inCheck(pos2, !amBlack) &&
                board[pos3].getIsEmpty() &&
                //!board.inCheck(pos3, !amBlack) &&
                board[pos4].getIsEmpty() //&&
                //!board.inCheck(pos4, !amBlack)
                ) {
                newLocation = Position(row, 2);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

   
                tempBoard.set(pos1, empty);
                tempBoard.set(pos4, &board[pos1] );

                kingMoves.emplace_back(make_tuple(get<0>(output), tempBoard));

            }

            // King Side
            pos1 = Position(row, 7);
            pos2 = Position(row, 6);
            pos3 = Position(row, 5);
            if (board[pos1] == blackRook &&
                //!board.inCheck(pos1, !amBlack) &&
                board[pos2].getIsEmpty() &&
                //!board.inCheck(pos2, !amBlack) &&
                board[pos3].getIsEmpty() //&&
                //!board.inCheck(pos3, !amBlack)
                ) {
                newLocation = Position(row, 6);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);
                tempBoard.set(pos1, empty);
                tempBoard.set(pos3, &board[pos1] );

                kingMoves.emplace_back(make_tuple(get<0>(output), tempBoard));
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
            Position pos1 = Position(row, 0);
            Position pos2 = Position(row, 1);
            Position pos3 = Position(row, 2);
            Position pos4 = Position(row, 3);

            if (board[pos1] == whiteRook &&
                //!board.inCheck(pos1, !amBlack) &&
                board[pos2].getIsEmpty() &&
                //!board.inCheck(pos2, !amBlack) &&
                board[pos3].getIsEmpty() &&
                //!board.inCheck(pos3, !amBlack) &&
                board[pos4].getIsEmpty() //&&
                //!board.inCheck(pos4, !amBlack)
                ) {

                newLocation = Position(row, 2);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard.set(pos1, empty);
                tempBoard.set(pos4, &board[pos1]);

                kingMoves.emplace_back(make_tuple(get<0>(output), tempBoard));

            }

            // King Side
            pos1 = Position(row, 7);
            pos2 = Position(row, 6);
            pos3 = Position(row, 5);
            if (board[pos1] == whiteRook &&
                //!board.inCheck(pos1, !amBlack) &&
                board[pos2].getIsEmpty() &&
                //!board.inCheck(pos2, !amBlack) &&
                board[pos3].getIsEmpty() //&&
                //!board.inCheck(pos3, !amBlack)
                ) {
                newLocation = Position(row, 6);

                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);
                
                tempBoard.set(pos1, empty);
                tempBoard.set(pos3, &board[pos1]);
                kingMoves.emplace_back(make_tuple(get<0>(output), tempBoard));
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