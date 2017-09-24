#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "board.h"

class SingleGame : public board
{
    Q_OBJECT
public:

    void click(int id, int row, int col);
};

#endif // SINGLEGAME_H
