#include "Pawn.h"
#include "Position.h"
#include "EmptySpace.h"

char Pawn::blackSymbol = 'P';
char Pawn::whtieSymbol = tolower(Pawn::blackSymbol);


vector<tuple<Position, Board>> Pawn::getPossibleMoves(const Position& currentPosition, const Board& board) const {
    
    vector<tuple<Position, Board>> possible;
    int c;
    int r;
    Position newLocation;

    static EmptySpace empty = EmptySpace();

    if (Piece::getIsBlack() == false) {

        // move forward 2 blank spaces
        c = currentPosition.getCol();
        r = currentPosition.getRow() - 2;
        newLocation.setXY(r, c);
        if (currentPosition.getRow() == 6 && board[newLocation.getLocation()] == empty) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // move forward one blank spaces
        r = currentPosition.getRow() - 1;
        newLocation.setXY(r, c);
        if (r >= 0 && board[newLocation.getLocation()] == empty) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack left
        c = currentPosition.getCol() - 1;
        newLocation.setXY(r, c);
        if (board.isWhite(newLocation)) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack right
        c = currentPosition.getCol() + 1;
        newLocation.setXY(r, c);
        if (board.isWhite(newLocation)) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // what about en-passant and pawn promotion

        // Pawn Promotion covered in move()
        if (currentPosition.getRow() == 3) {

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(1, col - 1)
            if (currentPosition.getCol() > 0 && board[currentPosition.getLocation() - 1].getSymbol() == blackSymbol) {
                newLocation.setXY(2, currentPosition.getCol() - 1);

                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() - 1] = empty;

                possible.emplace_back(output);
            }

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(1, col + 1)
            if (currentPosition.getCol() < 7 && board[currentPosition.getLocation() + 1] == blackSymbol) {

                newLocation.setXY(2, currentPosition.getCol() + 1);
                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() + 1] = empty;

                possible.emplace_back(output);
            }
        }
    }
        
    else if (Piece::getIsBlack() == true) {

        // forward two blank spaces
        c = currentPosition.getCol();
        r = currentPosition.getRow() + 2;
        newLocation.setXY(r, c);
        if (currentPosition.getRow() == 1 && board[newLocation] == ' ')
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // forward one blank space
        r = currentPosition.getRow() + 1;
        newLocation.setXY(r, c);
        if (r < 8 && board[newLocation] == ' ')
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // attack left
        c = currentPosition.getCol() - 1;
        newLocation.setXY(r, c);
        if (board.isBlack(newLocation))
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // attack right
        c = currentPosition.getCol() + 1;
        newLocation.setXY(r, c);
        if (board.isBlack(newLocation))
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // what about en-passant and pawn promotion?

        if (Piece::getIsBlack() == 4) {

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(6, col - 1)
            if (currentPosition.getCol() > 0 && board[currentPosition.getLocation() - 1] == whtieSymbol) {
                // Add the en passant move
                newLocation.setXY(5, currentPosition.getCol() - 1);
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() - 1] = empty;

                possible.emplace_back(output);
            }

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(6, col + 1)
            if (currentPosition.getCol() < 7 && board[currentPosition.getLocation() + 1] == blackSymbol) {
                newLocation.setXY(5, currentPosition.getCol() + 1);
                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() + 1] = empty;

                possible.emplace_back(output);
            }
        }

    }

    return possible;
    
}


