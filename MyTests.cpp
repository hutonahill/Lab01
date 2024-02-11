#include "MyTests.h"
#include <set>
#include <iostream>
#include <cassert>
#include "chellUtil.h"
#include <tuple>


using namespace std;

chessUtil chessutil2 = chessUtil();

MyTests::MyTests() {
    testCastling();
    testEnPasent();

    // testPawnPromotion
}

bool containsValue(const set<int>& mySet, const int& value) {
    return mySet.find(value) != mySet.end();
}


void MyTests::testCastling()
{
    char board1[64] = {
       chessutil2.blackRook, ' ', ' ', ' ', chessutil2.blackKing, chessutil2.blackBishop, chessutil2.blackKnight, chessutil2.blackRook,
       chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn,
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };

    char board2[64] = {
       chessutil2.blackRook, chessutil2.blackKnight, chessutil2.blackBishop, chessutil2.blackQueen, chessutil2.blackKing, ' ', ' ', chessutil2.blackRook,
       chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn, chessutil2.blackPawn,
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };
    int kingPosition = 4;

    set<tuple<int, char*>> possibleMoves = chessutil2.getPossibleMoves(board2, kingPosition);

    set<int> oldPossibleMoves = set<int>();

    for each (tuple<int, char*> move in possibleMoves) {
        oldPossibleMoves.insert(get<0>(move));

    }

    assert(containsValue(oldPossibleMoves, 5) == true); // King's side castling

    possibleMoves = chessutil2.getPossibleMoves(board1, kingPosition);

    oldPossibleMoves = set<int>();

    for each (tuple<int, char*> move in possibleMoves) {
        oldPossibleMoves.insert(get<0>(move));

    }

    assert(containsValue(oldPossibleMoves, 2) == true); // Queen's side castling
}

// have no method to get input form user. this is not possible
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

    set<int> oldPossibleMoves = set<int>();

    for each (tuple<int, char*> move in possibleMoves) {
        oldPossibleMoves.insert(get<0>(move));

    }

    

    assert(containsValue(oldPossibleMoves, 20) == true);
}