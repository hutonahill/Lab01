#include "Pawn.h"
#include "Position.h"
#include "EmptySpace.h"

char Pawn::blackSymbol = 'P';
char Pawn::whtieSymbol = tolower(Pawn::blackSymbol);


vector<tuple<Position, Board>> Pawn::getPossibleMoves(const Position& currentPosition, const Board& board) const {
    
    vector<tuple<Position, Board>> possible;
    int c;
    int r;
    int row = currentPosition.getRow();
    int col = currentPosition.getCol();

    Position newLocation;

    static EmptySpace empty = EmptySpace();

    bool isBlack = Piece::getIsBlack();

    if (isBlack == false) {

        

        // move forward 2 blank spaces
        c = col;
        r = row - 2;
        newLocation.set(r, c);
        if (row == 6 && board[newLocation.getLocation()] == empty) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // move forward one blank spaces
        r = row - 1;
        newLocation.set(r, c);
        if (r >= 0 && board[newLocation.getLocation()] == empty) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack left
        c = col - 1;
        newLocation.set(r, c);
        if (board.isWhite(newLocation)) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack right
        c = col + 1;
        newLocation.set(r, c);
        if (board.isWhite(newLocation)) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // what about en-passant and pawn promotion

        // Pawn Promotion covered in move()
        if (row == 3) {

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(1, col - 1)
            if (col > 0 && board[currentPosition.getLocation() - 1].getSymbol() == blackSymbol) {
                newLocation.set(2, col - 1);

                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() - 1] = empty;

                possible.emplace_back(output);
            }

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(1, col + 1)
            if (col < 7 && board[currentPosition.getLocation() + 1] == blackSymbol) {

                newLocation.set(2, col + 1);
                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() + 1] = empty;

                possible.emplace_back(output);
            }
        }
    }
        
    else if (isBlack == true) {

        // forward two blank spaces
        c = col;
        r = row + 2;
        newLocation.set(c, r);
        int tempLocation = newLocation;
        char targetPiece = board[tempLocation];
        if (row == 1 && targetPiece == ' '){
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // forward one blank space
        r = row + 1;
        newLocation.set(r, c);
        if (r < 8 && board[newLocation] == ' '){
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack left
        c = col - 1;
        newLocation.set(r, c);
        if (board.isBlack(newLocation))
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // attack right
        c = col + 1;
        newLocation.set(r, c);
        if (board.isBlack(newLocation))
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // what about en-passant and pawn promotion?

        if (Piece::getIsBlack() == 4) {

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(6, col - 1)
            if (col > 0 && board[currentPosition.getLocation() - 1] == whtieSymbol) {
                // Add the en passant move
                newLocation.set(5, currentPosition.getCol() - 1);
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() - 1] = empty;

                possible.emplace_back(output);
            }

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(6, col + 1)
            if (col < 7 && board[currentPosition.getLocation() + 1] == blackSymbol) {
                newLocation.set(5, currentPosition.getCol() + 1);
                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard[currentPosition.getLocation() + 1] = empty;

                possible.emplace_back(output);
            }
        }
    }
    else {
        throw invalid_argument("ERROR: unreachable state reached! Pawn is nether black nor white.");
    }

    return possible;
    
}

void Pawn::drawPiece(int rawLocation) const {
    Piece::gout->drawPawn(rawLocation, getIsBlack());
}
