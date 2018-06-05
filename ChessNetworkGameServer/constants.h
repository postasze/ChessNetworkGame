#ifndef CONSTANTS_H
#define CONSTANTS_H

const int BUFFER_SIZE = 1024;
const int NUMBER_OF_QUEUED_CLIENTS = 16;
const int NUMBER_OF_SQUARES = 8;

enum class FigureType {
    Pawn, Knight, Bishop, LeftRook, RightRook, Queen, King
};

enum PlayerColor {
    Black, White
};

#endif // CONSTANTS_H
