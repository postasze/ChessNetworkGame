#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>

const int BOARD_WIDTH = 512;
const int BOARD_HEIGHT = 512;
const int NUMBER_OF_SQUARES = 8;
const int SQUARE_SIZE = 64;
const QColor BRIGHT_FIELD_COLOR(170, 210, 170, 255);
const QColor DARK_FIELD_COLOR(20, 160, 20, 255);
const QColor POSSIBLE_MOVE_FIELD_COLOR(255, 200, 100, 255);

enum class FigureType {
    Pawn, Knight, Bishop, Rook, Queen, King
};

enum PlayerColor {
    Black, White
};

#endif // CONSTANTS_H
