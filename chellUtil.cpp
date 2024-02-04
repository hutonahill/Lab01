#include "chellUtil.h"



using namespace std;

bool checkPromotion(const char* board, int position) {
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


/***********************************************
* Row Column
* Simple row/column pair
************************************************/
struct RC {
    int row;
    int col;
};

/*********************************************
 * MOVE
 * Execute one movement. Return TRUE if successful
 *********************************************/
bool chessUtil::move(char* board, int positionFrom, int positionTo) {
    // do not move if a move was not indicated
    if (positionFrom == -1 || positionTo == -1) {
        return false;
    }
    assert(positionFrom >= 0 && positionFrom < 64);
    assert(positionTo >= 0 && positionTo < 64);




    // find the set of possible moves from our current location
    set <tuple<int, char*>> possiblePrevious = getPossibleMoves(board, positionFrom);

    bool moveIsValid = false;

    char* newBoard;

    for each (tuple<int, char*> move in possiblePrevious) {
        if (get<0>(move) == positionTo) {
            moveIsValid = true;
            newBoard = strdup(std::get<1>(move));
        }
    }

    // only move there is the suggested move is on the set of possible moves
    if (moveIsValid == true) {



        strcpy(board, newBoard);
        free(newBoard);

        if (checkPromotion(board, positionTo) == true) {
            bool validInput = false;

            vector<string> validInputs = vector<string>{
                "q", "n", "b", "r"
            };

            string validInputsString = vectorToString(validInputs);

            string userInput = "";

            while (validInput == false) {
                userInput = toLowerCase(input("What would you like to promote your pawn to?"));

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

            board[positionTo] = cStrUserInput[0];

        }

        return true;
    }

    return false;

}


tuple<int, char*> chessUtil::standardMove(int location, int newLocation, const char* board) {
    char* tempBoard = new char[strlen(board) + 1];

    tuple<int, char*>output;

    strcpy(tempBoard, board);



    tempBoard[location] = emptySpace;
    tempBoard[newLocation] = board[location];

    output = make_tuple(newLocation, tempBoard);

    return output;
}

int convertToLocation(int row, int column) {
    return row * 8 + column;
}

/*********************************************************
 * GET POSSIBLE MOVES
 * Determine all the possible moves for a given chess piece
 *********************************************************/
set <tuple<int, char*>> chessUtil::getPossibleMoves(const char* board, int location)
{
    set <tuple<int, char*>> possible;

    int newLocation;
    tuple<int, char*> output;




    // return the empty set if there simply are no possible moves
    if (location < 0 || location >= 64 || board[location] == ' ') {
        return possible;
    }


    int row = location / 8;  // current location row
    int col = location % 8;  // current location column
    int r;                   // the row we are checking
    int c;                   // the column we are checking
    bool amBlack = isBlack(board, row, col);

    //
    // PAWN
    //

    if (board[location] == whitePawn)
    {
        // move forward 2 blank spaces
        c = col;
        r = row - 2;
        newLocation = convertToLocation(r, c);
        if (row == 6 && board[newLocation] == ' ') {
            possible.insert(standardMove(location, newLocation, board));
        }

        // move forward one blank spaces
        r = row - 1;
        newLocation = convertToLocation(r, c);
        if (r >= 0 && board[newLocation] == ' ') {
            possible.insert(standardMove(location, newLocation, board));
        }

        // attack left
        c = col - 1;
        newLocation = convertToLocation(r, c);
        if (isWhite(board, r, c)) {
            possible.insert(standardMove(location, newLocation, board));
        }

        // attack right
        c = col + 1;
        newLocation = convertToLocation(r, c);
        if (isWhite(board, r, c)) {
            possible.insert(standardMove(location, newLocation, board));
        }

        // what about en-passant and pawn promotion
    }
    if (board[location] == blackPawn)
    {
        // forward two blank spaces
        c = col;
        r = row + 2;
        newLocation = convertToLocation(r, c);
        if (row == 1 && board[r * 8 + c] == ' ')
            possible.insert(standardMove(location, newLocation, board));

        // forward one blank space
        r = row + 1;
        newLocation = convertToLocation(r, c);
        if (r < 8 && board[r * 8 + c] == ' ')
            possible.insert(standardMove(location, newLocation, board));

        // attack left
        c = col - 1;
        newLocation = convertToLocation(r, c);
        if (isBlack(board, r, c))
            possible.insert(standardMove(location, newLocation, board));

        // attack right
        c = col + 1;
        newLocation = convertToLocation(r, c);
        if (isBlack(board, r, c))
            possible.insert(standardMove(location, newLocation, board));

        // what about en-passant and pawn promotion?
        // 
        // We need to access move history to do en-passant

        // we need a GUI to do pawn promotion
    }

    //
    // KNIGHT
    //
    if (board[location] == whiteKnight || board[location] == blackKnight) {
        RC moves[8] =
        {
                {-1,  2}, { 1,  2},
        {-2,  1},                    { 2,  1},
        {-2, -1},                    { 2, -1},
                {-1, -2}, { 1, -2}
        };


        for each (RC space in moves) {

            r = row + space.row;
            c = col + space.col;
            newLocation = convertToLocation(r, c);

            if (amBlack && isNotBlack(board, r, c))
                possible.insert(standardMove(location, newLocation, board));

            if (!amBlack && isNotWhite(board, r, c))
                possible.insert(standardMove(location, newLocation, board));
        }
    }

    //
    // KING
    //
    if (board[location] == whiteKing || board[location] == blackKing) {

        set <tuple<int, char*>> kingMoves;

        RC moves[8] =
        {
            {-1,  1}, {0,  1}, {1,  1},
            {-1,  0},          {1,  0},
            {-1, -1}, {0, -1}, {1, -1}
        };


        for each (RC space in moves) {
            r = row + space.row;
            c = col + space.col;
            newLocation = convertToLocation(r, c);
            if (amBlack && isNotBlack(board, r, c)) {
                kingMoves.insert(standardMove(location, newLocation, board));
            }

            if (!amBlack && isNotWhite(board, r, c)) {
                kingMoves.insert(standardMove(location, newLocation, board));
            }
        }
        // what about castling?

        // what about check?

        // We are going to have to check to see if any of the kings moves put them in check eventualy, 
        // so ive put the kings moves in a seprate set and we combine them at the end of the if.
        possible.insert(kingMoves.begin(), kingMoves.end());

    }

    //
    // QUEEN
    //
    if (board[location] == whiteQueen || board[location] == blackQueen)
    {
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
            newLocation = convertToLocation(r, c);

            // loop though every space in the current direction
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                // you hit a peice
                board[newLocation] == ' ') {



                possible.insert(standardMove(location, newLocation, board));

                // ideratate the dierection 
                r += space.row;
                c += space.col;
                newLocation = convertToLocation(r, c);
            }

            // if the above loop stoped due to hitting a enemy peice
            // add its location to the list.
            if (amBlack && isNotBlack(board, r, c)) {
                possible.insert(standardMove(location, newLocation, board));
            }
            if (!amBlack && isNotWhite(board, r, c)) {
                possible.insert(standardMove(location, newLocation, board));
            }

        }
    }

    //
    // ROOK
    //
    if (board[location] == whiteRook || board[location] == blackRook)
    {
        RC moves[4] =
        {
                    {0,  1},
            {-1, 0},         {1, 0},
                    {0, -1}
        };
        for (int i = 0; i < 4; i++)
        {
            r = row + moves[i].row;
            c = col + moves[i].col;
            newLocation = convertToLocation(r, c);
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[newLocation] == ' ')
            {
                possible.insert(standardMove(location, newLocation, board));

                r += moves[i].row;
                c += moves[i].col;
                newLocation = convertToLocation(r, c);
            }
            if (amBlack && isNotBlack(board, r, c)) {
                possible.insert(standardMove(location, newLocation, board));
            }

            if (!amBlack && isNotWhite(board, r, c)) {
                possible.insert(standardMove(location, newLocation, board));
            }
        }
    }

    //
    // BISHOP
    //
    if (board[location] == whiteBishop || board[location] == blackBishop)
    {
        RC moves[4] =
        {
            {-1,  1}, {1,  1},
            {-1, -1}, {1, -1}
        };
        for (int i = 0; i < 4; i++) {

            r = row + moves[i].row;
            c = col + moves[i].col;
            newLocation = convertToLocation(r, c);
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[newLocation] == ' ') {

                possible.insert(standardMove(location, newLocation, board));
                r += moves[i].row;
                c += moves[i].col;
                newLocation = convertToLocation(r, c);
            }

            if (amBlack && isNotBlack(board, r, c)) {
                possible.insert(standardMove(location, newLocation, board));
            }
            if (!amBlack && isNotWhite(board, r, c)) {
                possible.insert(standardMove(location, newLocation, board));
            }
        }
    }

    return possible;
}




/****************************************************
 * IS NOT WHITE
 * Is the current location valid and the piece is either
 * black (uppercase) or space
 ***************************************************/
inline bool chessUtil::isNotWhite(const char* board, int row, int col)
{
    // not white if we are off the board or if we are looking at a space
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return piece == ' ' || (piece >= 'A' && piece <= 'Z');
}

/****************************************************
 * IS  WHITE
 * Is the current location valid and the piece is white
 ***************************************************/
inline bool chessUtil::isWhite(const char* board, int row, int col)
{
    // not white if we are off the board or if we are looking at a space
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return (piece >= 'a' && piece <= 'z');
}

/****************************************************
 * IS NOT BLACK
 * Is the current location valid and the piece is either
 * white (lowercase) or space
 ***************************************************/
inline bool chessUtil::isNotBlack(const char* board, int row, int col)
{
    // not white if we are off the board or if we are looking at a space
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return piece == ' ' || (piece >= 'a' && piece <= 'z');
}


/****************************************************
 * IS  BLACK
 * Is the current location valid and the piece is black
 ***************************************************/
inline bool chessUtil::isBlack(const char* board, int row, int col)
{
    // not white if we are off the board or if we are looking at a space
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return (piece >= 'A' && piece <= 'Z');
}
