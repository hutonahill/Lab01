#include "MyTests.h"
#include <set>
#include <iostream>
#include <cassert>
#include "chellUtil.h"
#include <tuple>


using namespace std;

chessUtil chessutil2 = chessUtil();


void MyTests::testCastling()
{
    const char* board = ("rnbqkbnrpppppppp                                PPPPPPPPRNBQKBNR");
    int kingPosition = 4;

    set<tuple<int, char*>> possibleMoves = chessutil2.getPossibleMoves(board, kingPosition);

    set<int> oldPossibleMoves = set<int>();

    for each (tuple<int, char*> move in possibleMoves) {
        oldPossibleMoves.insert(get<0>(move));
    }

    assert(oldPossibleMoves.find(2) != oldPossibleMoves.end()); // King's side castling
    assert(oldPossibleMoves.find(6) != oldPossibleMoves.end()); // Queen's side castling
}


void MyTests::testPawnPromotion()
{
    char board[64] = {
       chessutil2.blackRook, chessutil2.blackKnight, chessutil2.blackBishop, chessutil2.blackQueen, chessutil2.blackKing, chessutil2.blackBishop, chessutil2.blackKnight, chessutil2.blackRook,
       chessutil2.blackPawn, chessutil2.blackPawn, ' ', chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn,
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', chessutil2.blackPawn, ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };

    int pawnPosition = 52;
    int pawnMoveTo = 60;

    bool pass = chessutil2.move(board, pawnPosition, pawnMoveTo);

    if (pass == true){
        assert(board[pawnMoveTo] != ' ');

        bool isPeiceBlack = chessutil2.isBlack(board, pawnMoveTo / 8, pawnMoveTo % 8);

        assert(isPeiceBlack == true);
        assert(board[pawnMoveTo] != chessutil2.blackPawn);
        assert(board[pawnMoveTo] != chessutil2.blackKing);
    }
}

void MyTests::testEnPasent()
{
    const char* board = "rnbqkbnrpppp ppp           Pp                   PPP PPPPRNBQKBNR";
    int pawnPosition = 28;
    int capturePoint = 21;

    set<tuple<int, char*>> possibleMoves = chessutil2.getPossibleMoves(board, pawnPosition);

    auto isCapturePoint = [capturePoint](const tuple<int, char*>& move) {
        return get<0>(move) == capturePoint;
    };

    auto it = std::find_if(possibleMoves.begin(), possibleMoves.end(), isCapturePoint);

    assert(it != possibleMoves.end());
}