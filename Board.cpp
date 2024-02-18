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
        
        board = other.board;  
        gout = other.gout;
    }
    return *this;
}

const Piece& Board::operator[](const Position& position) const {
    int index = position.getLocation();
    if (index >= 0 && index < board.size()) {
        return *board[index];
    }
    else {
        string errorMsg = "index `" + to_string(index) + "` is out of range for the board array. ";

        throw out_of_range(errorMsg);
    }
}

Piece& Board::operator[](const Position& position) {
    int index = position.getLocation();
    if (index >= 0 && index < board.size()) {
        return *board[index];
    }
    else {
        string errorMsg = "index `" + to_string(index) + "` is out of range for the board array. ";

        throw out_of_range(errorMsg);
    }
}

const Piece& Board::operator[](const int& positionInt) const {
    if (positionInt >= 0 && positionInt < board.size()) {
        return *board[positionInt];
    }
    else {
        string errorMsg = "index `" + to_string(positionInt) + "` is out of range for the board array. ";

        throw out_of_range(errorMsg);
    }
}

Piece& Board::operator[](const int& positionInt) {
    if (positionInt >= 0 && positionInt < board.size()) {
        return *board[positionInt];
    }
    else {
        string errorMsg = "index `" + to_string(positionInt) + "` is out of range for the board array. ";

        throw out_of_range(errorMsg);
    }
}

Board::operator const char* () const {
    // Create a string by concatenating the char representation of each Piece
    std::string result;

    for (int i = 0; i < board.size(); i++){
        result += static_cast<char>(*board[i]);
    }

    // Allocate memory for the char array and copy the string content
    char* charArray = new char[result.length() + 1];
    std::strcpy(charArray, result.c_str());

    return charArray;
}


bool Board::inCheck(const Position location, bool blackAttacking) const {
    // Check if any opponent's piece can attack the king
    for (int i = 0; i < 64; ++i)
    {
        if ((blackAttacking && !board[i]->getIsBlack()) || (!blackAttacking && board[i]->getIsBlack())){
            vector<tuple<Position, Board>> possibleMoves = board[i]->getPossibleMoves(Position(i), const_cast<Board*>(this), blackAttacking);
            for each (tuple<Position, Board> move in possibleMoves){
                if (get<0>(move) == location) {
                    return true;
                }
            }
        }
    }
    return false; // King is not in check
}
// no need to check for checkmate as the game will be frozen if 
/*
bool isCheckmate(const char* board, bool isBlackTurn)
{
    // Check if the king is in check
    if (!isCheck(board, isBlackTurn))
        return false; // King is not in check, so not checkmate

    // Check if the king has any legal moves to escape check
    for (int i = 0; i < 64; ++i)
    {
        if ((isBlackTurn && board[i].getIsBlack()) || (!isBlackTurn && isWhite(board, i)))
        {
            set<int> possibleMoves = getPossibleMoves(board, i);
            for (int move : possibleMoves)
            {
                char tempBoard[64];
                memcpy(tempBoard, board, sizeof(char) * 64);
                tempBoard[move] = tempBoard[i];
                tempBoard[i] = ' ';
                if (!isCheck(tempBoard, isBlackTurn))
                    return false; // King has at least one legal move to escape check
            }
        }
    }
    return true; // King is in checkmate
}
*/
