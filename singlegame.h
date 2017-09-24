#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "board.h"

class SingleGame : public board
{
    Q_OBJECT
public:

     void click(int id, int row, int col);

public slots:
    // void computermove();
};

#endif // SINGLEGAME_H
