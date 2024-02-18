#include "Pawn.h"
#include "Position.h"
#include "EmptySpace.h"

char Pawn::blackSymbol = Piece::blackPawn;
char Pawn::whtieSymbol = Piece::whitePawn;


vector<tuple<Position, Board>> Pawn::getPossibleMoves(const Position& currentPosition, const Board& board, const bool isBlackMove) const {
    
    vector<tuple<Position, Board>> possible;
    int c;
    int r;
    const int row = currentPosition.getRow();
    const int col = currentPosition.getCol();

    Position newLocation;

    const Piece* empty = new EmptySpace();

    bool amBlack = Piece::getIsBlack();

    if (amBlack != isBlackMove) {
        return possible;
    }

    if (amBlack == false) {

        

        // move forward 2 blank spaces
        c = col;
        r = row - 2;
        newLocation = Position(r, c);
        if (row == 6 && board[newLocation.getLocation()].getIsEmpty() == true) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // move forward one blank spaces
        r = row - 1;
        newLocation = Position(r, c);
        if (r >= 0 && board[newLocation.getLocation()].getIsEmpty() == true) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack left
        c = col - 1;
        newLocation = Position(r, c);
        if (newLocation.isValid() && board[newLocation].getIsBlack() && !board[newLocation].getIsEmpty()) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack right
        c = col + 1;
        newLocation = Position(r, c);
        if (newLocation.isValid() && board[newLocation].getIsBlack() && !board[newLocation].getIsEmpty()) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // what about en-passant and pawn promotion
        if (row == 3) {

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(1, col - 1)
            if (col > 0 && board[currentPosition.getLocation() - 1].getSymbol() == blackSymbol) {
                newLocation = Position(2, col - 1);

                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);
                
                tempBoard.set(currentPosition.getLocation() - 1, empty);

                possible.emplace_back(make_tuple(get<0>(output), tempBoard));
            }

            if (col < 7 && board[currentPosition.getLocation() + 1] == blackSymbol) {

                newLocation = Position(2, col + 1);
                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard.set(currentPosition.getLocation() + 1, empty);
                
                possible.emplace_back(make_tuple(get<0>(output), tempBoard));
            }
        }
    }
        
    else if (amBlack == true) {

        // forward two blank spaces
        int currentLocationInt = currentPosition;
        c = col;
        r = row + 2;
        newLocation = Position(r, c);
        int tempLocation = newLocation;
        char targetPiece = board[tempLocation].getSymbol();
        if (row == 1 && board[tempLocation].getIsEmpty() == true) {
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // forward one blank space
        r = row + 1;
        newLocation = Position(r, c);
        if (r < 8 && board[newLocation].getIsEmpty()){
            possible.emplace_back(standardMove(currentPosition, newLocation, board));
        }

        // attack left
        c = col - 1;
        newLocation = Position(r, c);
        if (newLocation.isValid() && !board[newLocation].getIsBlack() && !board[newLocation].getIsEmpty())
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // attack right
        c = col + 1;
        newLocation = Position(r, c);
        if (newLocation.isValid() && !board[newLocation].getIsBlack() && !board[newLocation].getIsEmpty())
            possible.emplace_back(standardMove(currentPosition, newLocation, board));

        // what about en-passant and pawn promotion?

        if (row == 4) {

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(6, col - 1)
            if (col > 0 && board[currentPosition.getLocation() - 1] == whtieSymbol) {
                // Add the en passant move
                newLocation = Position(5, currentPosition.getCol() - 1);
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard.set(currentPosition.getLocation() - 1, empty);

                possible.emplace_back(make_tuple(get<0>(output), tempBoard));
            }

            // impliment this condition later after we impliment move history:
                // lastMove.from == convertToLocation(6, col + 1)
            if (col < 7 && board[currentPosition.getLocation() + 1] == blackSymbol) {
                newLocation = Position(5, currentPosition.getCol() + 1);
                // Add the en passant move
                tuple<Position, Board> output = standardMove(currentPosition, newLocation, board);

                Board tempBoard = get<1>(output);

                tempBoard.set(currentPosition.getLocation() + 1, empty);

                possible.emplace_back(make_tuple(get<0>(output), tempBoard));
            }
        }
    }
    else {
        throw invalid_argument("ERROR: unreachable state reached! Pawn is nether black nor white.");
    }

    return possible;
    
}

void Pawn::drawPiece(int rawLocation) const {
    bool isBlack = Piece::getIsBlack();
    Piece::gout->drawPawn(rawLocation, isBlack);
}
