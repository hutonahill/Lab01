/**********************************************************************
 * GL Demo
 * Just a simple program to demonstrate how to create an Open GL window, 
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for draw*
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include <tuple>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>

// the chess peices
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "EmptySpace.h"

using namespace std;

ogstream gout;

vector<Piece*> startingBoard = vector<Piece*>{
    new Rook(true, &gout), new Knight(true, &gout), new Bishop(true, &gout), new Queen(true, &gout), new King(true, &gout), new Bishop(true, &gout), new Knight(true, &gout), new Rook(true, &gout),
    new Pawn(true, &gout), new Pawn(true, &gout), new Pawn(true, &gout), new Pawn(true, &gout), new Pawn(true, &gout), new Pawn(true, &gout), new Pawn(true, &gout), new Pawn(true, &gout),
    new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(),
    new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(),
    new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(),
    new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(), new EmptySpace(),
    new Pawn(false, &gout), new Pawn(false, &gout), new Pawn(false, &gout), new Pawn(false, &gout), new Pawn(false, &gout), new Pawn(false, &gout), new Pawn(false, &gout), new Pawn(false, &gout),
    new Rook(false, &gout), new Knight(false, &gout), new Bishop(false, &gout), new Queen(false, &gout), new King(false, &gout), new Bishop(false, &gout), new Knight(false, &gout), new Rook(false, &gout)
};

Board myBoard = Board(gout, startingBoard);


bool checkPromotion(const Board board, Position position) {
    // Assuming position is a valid index (0 to 63) in the board array
    int row = position / 8;

    // Check if the pawn is in a promotion position
    if ((board[position] == 'P' && row == 0) || (board[position] == 'p' && row == 7)) {
        // Pawn is in a position for promotion
        return true;
    }

    // No promotion position
    return false;
}

string toLowerCase(const string& input) {
    string result;

    for (char c : input) {
        result += tolower(c);
    }

    return result;
}

string toUpperCase(const string& input) {
    string result;

    for (char c : input) {
        result += toupper(c);
    }

    return result;
}

template <typename T>
bool vectorContainsValue(const std::vector<T>& vec, const T& value) {
    auto it = std::find(vec.begin(), vec.end(), value);
    return it != vec.end();
}

std::string vectorToString(const std::vector<std::string>& vec) {
    if (vec.empty()) {
        return "";
    }

    std::string result = vec[0];

    for (size_t i = 1; i < vec.size(); ++i) {
        result += ", " + vec[i];
    }

    return result;
}

bool isCapitalLetter(char c) {
    return std::isupper(static_cast<unsigned char>(c)) != 0;
}


void print(const std::string& message) {
    cout << message << std::endl;
}

// Function to get input as a string
string input(const string& prompt) {
    string userInput;

    cout << prompt;
    getline(cin, userInput);

    return userInput;
}


/*********************************************
 * MOVE
 * Execute one movement. Return TRUE if successful
 *********************************************/
bool move(Board& board, Position& positionFrom, Position& positionTo) {
    // do not move if a move was not indicated
    if (positionFrom.getLocation() == -1 || positionTo.getLocation() == -1) {
        return false;
    }
    assert(positionFrom.getLocation() >= 0 && positionFrom.getLocation() < 64);
    assert(positionTo.getLocation() >= 0 && positionTo.getLocation() < 64);




    // find the set of possible moves from our current location
    vector <tuple<Position, Board>> possiblePrevious = board[positionFrom].getPossibleMoves(positionFrom, board);

    bool moveIsValid = false;

    Board newBoard;

    for each (tuple<Position, Board> move in possiblePrevious) {
        if (get<0>(move) == positionTo) {
            moveIsValid = true;
            newBoard = get<1>(move);
        }
    }

    // only move there is the suggested move is on the set of possible moves
    if (moveIsValid == true) {

        // there is alot of code we are not using here for handling using input.
        // I plan to re enable this once we i figure out how to get any input from the user. >:(

        board = newBoard;

        // cin doesent work to get input from the user, so has been disabled.
        if (checkPromotion(board, positionTo) == true && false) {
            bool validInput = false;

            vector<string> validInputs = vector<string>{
                "q", "n", "b", "r"
            };

            string validInputsString = vectorToString(validInputs);

            string userInput = "";

            while (validInput == false) {
                //userInput = toLowerCase(input("What would you like to promote your pawn to?"));

                userInput = "q";

                if (vectorContainsValue(validInputs, userInput) == false) {
                    print("InvalidInput. Please input one of the following:");
                    print(validInputsString);
                }
                else {
                    validInput == true;
                }
            }

            if (isCapitalLetter(board[positionTo]) == true) {
                userInput = toUpperCase(userInput);
            }

            assert(userInput.size() == 1);

            const char* cStrUserInput = userInput.c_str();

            bool isBlack = board[positionTo].getIsBlack();

            board[positionTo] = Queen(isBlack, board.getGout());

        }

        return true;
    }

    return false;

}



/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface *pUI, void * p)
{
    vector <tuple<Position, Board>> possible;

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 

    Position oldPosition(pUI->getPreviousPosition());
    Position targetPosition(pUI->getSelectPosition());

    if (targetPosition.isValid() == true) {
        // move 
        bool success = move(myBoard, oldPosition, targetPosition);

        if (success) {
            pUI->clearSelectPosition();
        }

        else {
            possible = myBoard[targetPosition].getPossibleMoves(targetPosition, myBoard);
        }
    }

    // if we clicked on a blank spot, then it is not selected
    if (targetPosition != -1 && myBoard[targetPosition] == EmptySpace()) {
        pUI->clearSelectPosition();
    }

    

    vector<Position> possibleLocations = vector<Position>();

   for each (tuple<Position, Board> move in possible)
   {
       possibleLocations.emplace_back(get<0>(move));
   }

   // draw the board
   myBoard.drawBoard(*pUI, possibleLocations);

}

/********************************************************
 * PARSE
 * Determine the nature of the move based on the input.
 * This is the only function understanding Smith notation
 *******************************************************/
void parse(const string& textMove, Position& positionFrom, Position& positionTo)
{
   string::const_iterator it = textMove.cbegin();

   // get the source
   int col = *it - 'a';
   it++;
   int row = *it - '1';
   it++;
   positionFrom.setXY(row, col);

   // get the destination
   col = *it - 'a';
   it++;
   row = *it - '1';
   it++;
   positionTo.setXY(row, col);

   // capture and promotion information
   char capture = ' ';
   char piecePromotion = ' ';
   bool castleK = false;
   bool castleQ = false;
   bool enpassant = false;
   for (; it != textMove.end(); ++it)
   {
      switch (*it)
      {
      case 'p':   // capture a pawn
      case 'n':   // capture a knight
      case 'b':   // capture a bishop
      case 'r':   // capture a rook
      case 'q':   // capture a queen
      case 'k':   // !! you can't capture a king you silly!
         capture = tolower(*it);
         break;

      case 'c':  // short castling or king's castle
         castleK = true;
         break;
      case 'C':  // long castling or queen's castle
         castleQ = true;
         break;
      case 'E':  // En-passant
         enpassant = true;
         break;

      case 'N':  // Promote to knight
      case 'B':  // Promote to Bishop
      case 'R':  // Promote to Rook
      case 'Q':  // Promote to Queen
         piecePromotion = *it;
         break;

      }
   }

   // error checking
   if (positionFrom < 0 || positionFrom >= 64 ||
       positionTo   < 0 || positionTo   >= 64)
      positionFrom = positionTo = -1;
}

/********************************************************
 * READ FILE
 * Read a file where moves are encoded in Smith notation
 *******************************************************/
void readFile(const char* fileName, Board& board)
{
   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return;

   // read the file, one move at a time
   string textMove;
   bool valid = true;
   while (valid && fin >> textMove)
   {
      Position positionFrom;
      Position positionTo;
      parse(textMove, positionFrom, positionTo);

      valid = move(board, positionFrom, positionTo);
   }

   // close and done
   fin.close();
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
// pretty sparse my leg! this make __no__ since. 
// Heck, you have somehow disabled the terminal and now i cant print debug lines! >:(


#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   Interface ui("Chess");

   

   // Initialize the game class
   // note this is upside down: 0 row is at the bottom


   char rawboard[64];

   for (int i = 0; i < 64; i++)
   {
       rawboard[i] = myBoard[i];
   }
   
#ifdef _WIN32
 //  int    argc;
 //  LPWSTR * argv = CommandLineToArgvW(GetCommandLineW(), &argc);
 //  string filename = argv[1];
   if (__argc == 2)
      readFile(__argv[1], myBoard);
#else // !_WIN32
   if (argc == 2)
      readFile(argv[1], board);
#endif // !_WIN32

   // set everything into action
   ui.run(callBack, rawboard);             

   return 0;
}


