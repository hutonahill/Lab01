#pragma once
#include "Piece.h"
#include "Position.h"
#include "Board.h"
#include "EmptySpace.h"



Piece::Piece(bool isBlackInput, char symbolInput, ogstream* goutInput) {
	isBlack = isBlackInput;
	symbol = symbolInput;
    isEmpty = false;
    gout = goutInput;
}

Piece::Piece(Piece* oldPiece) {
    isBlack = oldPiece->isBlack;
    symbol = oldPiece->symbol;
    isEmpty = oldPiece->isEmpty;
    gout = oldPiece->gout;
}

Piece::Piece() {
    isBlack = false;
    symbol = emptySpace;
    isEmpty = true;
}

bool Piece::getIsBlack() const {
	return isBlack;
}

bool Piece::getIsEmpty() const {
    return isEmpty;
}

char Piece::getSymbol() const {
	return symbol;
}

tuple<Position, Board> Piece::standardMove(const Position& location, 
    const Position& newLocation, const Board& boardInput) const{


    Board tempBoard(boardInput);

    const Piece* empty = new EmptySpace();
    
    tempBoard.set(location, empty);

    // set the location the piece moves to as the piece.
    tempBoard.set(newLocation, const_cast<Piece*>(&boardInput[location]) );

    // construct the output and return it.
    return make_tuple(newLocation, tempBoard);
}