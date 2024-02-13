#include "Board.h"
#include "uiInteract.h"
#include "EmptySpace.h"

#include <stdexcept>
#include <sstream>

Board::Board(Board* oldBoard){
    board = oldBoard->board;
    gout = oldBoard->gout;
}

Board::Board(ogstream& goutInput, const vector<Piece*>& startingBoard) {
    gout = &goutInput;
    board = startingBoard;
}

Board::Board() {
    board;
    gout = nullptr;
}

bool Board::isWhite(Position location) const {
    if ((*board[location.getLocation()]).getIsEmpty()) {
        return false;
    }
    
    return !isBlack(location);
}

bool Board::isNotWhite(Position location) const {
    if ((*board[location.getLocation()]).getIsEmpty()) {
        return true;
    }
    
    return !isWhite(location);
}

bool Board::isBlack(Position location) const {
    if ((*board[location.getLocation()]).getIsEmpty()) {
        return false;
    }
    return (*board[location.getLocation()]).getIsBlack();
}

bool Board::isNotBlack(Position location) const {
    if ((*board[location.getLocation()]).getIsEmpty()) {
        return true;
    }
    
    return !isBlack(location);
}

ogstream* Board::getGout() {
    return gout;
}

void Board::drawBoard(const Interface& ui, const vector <Position>& possible){
    
    // draw the checkerboard
    (*gout).drawBoard();

    // draw any selections
    (*gout).drawHover(ui.getHoverPosition());
    (*gout).drawSelected(ui.getSelectPosition());

    // Iterate through the vector using range-based for loop
    for (int value : possible) {
        (*gout).drawPossible(value);
    }

    // draw the pieces
    for (int i = 0; i < board.size(); i++){
        (*board[i]).drawPiece(i);
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {  // Check for self-assignment
        // Deallocate existing resources if needed

        // Call the copy constructor for deep copy
        Board temp(other);
        swap(*this, temp);  // Use the swap idiom for efficient assignment
    }
    return *this;
}

const Piece& Board::operator[](const Position& position) const {
    return *board[position.getLocation()];
}

Piece& Board::operator[](const Position& position) {
    return *board[position.getLocation()];
}

const Piece& Board::operator[](const int& positionInt) const {
    return *board[positionInt];
}

Piece& Board::operator[](const int& positionInt) {
    return *board[positionInt];
}

Board::operator const char* () const {
    // Create a string by concatenating the char representation of each Piece
    std::string result;
    for (const Piece* piece : board) {
        result += static_cast<char>(*piece);
    }

    // Allocate memory for the char array and copy the string content
    char* charArray = new char[result.length() + 1];
    std::strcpy(charArray, result.c_str());

    return charArray;
}