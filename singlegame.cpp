#include "singlegame.h"
#include<QTimer>

 void SingleGame::click(int id, int row, int col)
{
    //如果是红旗 ，那就结束，红棋是让电脑走
    if(this->_beredturn)
        return;
    //如果是黑棋，那就尝试move
    board::click(id,row,col);
    //如果是红棋，电脑走
    if(!this->_beredturn)
    {
        /*
         * 启动0.1秒定时器，在0.1秒后电脑
         */
//         QTimer::singleShot(100,this,slot(computerMove()));

    }



}
