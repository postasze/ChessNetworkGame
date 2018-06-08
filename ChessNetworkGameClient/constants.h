#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>

const int BOARD_WIDTH = 512;
const int BOARD_HEIGHT = 512;
const int NUMBER_OF_SQUARES = 8;
const int SQUARE_SIZE = 64;
const int BUFFER_SIZE = 1024;
const QColor BRIGHT_FIELD_COLOR(170, 210, 170, 255);
const QColor DARK_FIELD_COLOR(20, 160, 20, 255);
const QColor POSSIBLE_MOVE_FIELD_COLOR(255, 200, 100, 255);

enum class FigureType {
    Pawn, Knight, Bishop, LeftRook, RightRook, Queen, King
};

enum PlayerColor {
    Black, White, None
};


inline std::ostream &operator<<(std::ostream &os, const FigureType &fig) {

    os << static_cast<std::underlying_type<FigureType>::type> (fig);

    return os;
}

inline std::ostream &operator<<(std::ostream &os, const PlayerColor &color) {

    os << static_cast<std::underlying_type<PlayerColor>::type> (color);

    return os;
}

#endif // CONSTANTS_H
