#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "stone.h"
namespace Ui {
class board;
}

class board : public QWidget
{
    Q_OBJECT

public:
    explicit board(QWidget *parent = 0);
    stone _s[32];
    int _r;//棋子的半径
    int _selectid;
    int _beredturn;
    QPoint center(int row,int col);
    QPoint center(int id);
    bool getRowCol(QPoint pt,int& row,int& col);
    ~board();
    void drawStone(QPainter& painter, int id);//引用，不然后面传过去的就是复制
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool canmove(int moveid,int row,int col,int killid);
    bool canmove1(int moveid,int row,int col,int killid);
    bool canmove2(int moveid,int row,int col,int killid);
    bool canmove3(int moveid,int row,int col,int killid);
    bool canmove4(int moveid,int row,int col,int killid);
    bool canmove5(int moveid,int row,int col,int killid);
    bool canmove6(int moveid,int row,int col,int killid);
    bool canmove7(int moveid,int row,int col,int killid);
    int getStoneId(int row,int col);
    int getStoneCountAtLine(int row1,int col1,int row2,int col2);
    void click(QPoint pt);
    void click(int id,int row,int col);
    void trySelectStone(int id);
    void tryMoveStone(int id,int row,int col);
private:
    Ui::board *ui;
};

#endif // BOARD_H
