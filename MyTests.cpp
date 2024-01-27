#include "MyTests.h"
#include<set>
#include"chess.cpp"


using namespace std;


void MyTests::testCastling()
{
    const char* board = ("rnbqkbnrpppppppp                                PPPPPPPPRNBQKBNR");
    int kingPosition = 4;

    set<int> possibleMoves = getPossibleMoves(board, kingPosition);

    assert(possibleMoves.find(2) != possibleMoves.end()); // King's side castling
    assert(possibleMoves.find(6) != possibleMoves.end()); // Queen's side castling
}

void MyTests::testPawnPromotion()
{
    const char* board = "rnbqkbnrpppppppp                                PPPPPPPPRNBQKBNR";
    int pawnPosition = 8;

    std::set<int> possibleMoves = getPossibleMoves(board, pawnPosition);

    if (!possibleMoves.empty())
    {
        assert(possibleMoves.find(0) != possibleMoves.end()); // Promote to rook
        assert(possibleMoves.find(1) != possibleMoves.end()); // Promote to knight
        assert(possibleMoves.find(2) != possibleMoves.end()); // Promote to bishop
        assert(possibleMoves.find(3) != possibleMoves.end()); // Promote to queen
    }
    else
    {
        // Check if there is a pawn in the last row of a different color
        char lastRowPawn = board[56]; // Assuming last row index is 56
        if (lastRowPawn != ' ' && ((pawnPosition < 16 && lastRowPawn >= 'a') || (pawnPosition >= 48 && lastRowPawn <= 'Z')))
        {
            std::cerr << "Error: Pawn in the last row not promoted!" << std::endl;
            return;
        }
    }
}

void MyTests::testEnPasent()
{
    const char* board = "rnbqkbnrpppp ppp           Pp                   PPP PPPPRNBQKBNR";
    int pawnPosition = 28;
    int capturePoint = 21;

    set<int> possibleMoves = getPossibleMoves(board, pawnPosition);

    assert(possibleMoves.find(capturePoint) != possibleMoves.end());
}