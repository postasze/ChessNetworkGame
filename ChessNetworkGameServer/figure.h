#ifndef FIGURE_H
#define FIGURE_H

#include "constants.h"

class Figure
{
public:
    Figure(PlayerColor figureColor, FigureType figureType, int x, int y);
    Figure();

    PlayerColor figureColor;
    FigureType figureType;
    int x, y;
};

#endif // FIGURE_H
