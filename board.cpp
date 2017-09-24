#include "board.h"
#include "ui_board.h"
#include<QPainter>
#include<QMouseEvent>
board::board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::board)
{
    ui->setupUi(this);
   this->resize(QSize(500,500));
    for (int i=0;i<32;i++){
        _s[i].init(i);
    }
    _selectid=-1;
    _beredturn=false;    //黑子先行

}


board::~board()
{
    delete ui;
}

void board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int d=40;
    _r=d/2;    //棋子的半径
    //画10横线
    for(int i=1;i<=10;++i)
    {

        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }
    //画9竖线
    for(int i=1;i<=9;++i){

        if(i==1 ||i==9)
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else
        {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }

    }
    //九宫格
    painter.drawLine(QPoint(4*d,1*d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,1*d),QPoint(4*d,3*d));
    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));

    //绘制棋子
    for(int i=0;i<32;++i)
    {
        drawStone(painter,i);

    }



}
QPoint board::center(int id){

    return center(_s[id]._row,_s[id]._col);
}

QPoint board::center(int row,int col)
{
    QPoint ret;
    ret.rx()  =(col+1)*_r*2;
    ret.ry()=(row+1)*_r*2;
    return ret;


}
void board::drawStone(QPainter& painter,int id)
{
    if(_s[id]._dead)
    {
        return;
    }
    QPoint c=center(id);
    QRect rect=QRect(c.rx()-_r,c.ry()-_r,_r*2,_r*2);
    if(id==_selectid){
        painter.setBrush(QBrush(Qt::gray));
    }
    else{
    painter.setBrush(QBrush(Qt::yellow));
    }
    painter.setPen(Qt::black);
    painter.drawEllipse(c,_r,_r);
    if(_s[id]._red)
        painter.setPen(Qt::red);
    painter.setFont(QFont("system",_r,700));
    //painter.drawText(_s[id].getText(),);
    painter.drawText(rect, Qt::AlignCenter, _s[id].getText());
}

bool board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row=0;row<=9;row++)
    {
        for(col=0;col<=8;col++)
        {
            QPoint c=center(row,col);
            int dx=c.x()-pt.x();
            int dy=c.y()-pt.y();
            int dist=dx*dx+dy*dy;
            if(dist<_r*_r)
                return true;
        }
    }
    return false;
}
bool board::canmove1(int moveid, int row, int col, int killid)
{
    //jiang
    /*
     * 首先目标的位置在九宫格内
     * 移动的步长是一个格子
     */
    if(_s[moveid]._red)
    {
        if(row>2)
        {
            return false;

        }
    }
    else
        {
            if(row<7)
            return false;
        }
    if(col<3) return false;
    if(col>5) return false;
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);//12,21,22,10,1
    if(d==1||d==10)
    {
        return true;
    }
        return false;

}
bool board::canmove2(int moveid, int row, int col, int killid)
{
    //shi
    if(_s[moveid]._red)
    {
        if(row>2)
            return false;
    }
    else
    {
        if(row<7)
            return false;
    }
    if(col<3)return false;
    if(col>5)return false;
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);//12,21,22,10,1
    if(d==11)
        return true;

    return false;

}
bool board::canmove3(int moveid, int row, int col, int killid)
{
    //xiang
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    if(d!=22)return false;
    int rEye=(row+_s[moveid]._row)/2;
    int cEye=(col+_s[moveid]._col)/2;
    if(getStoneId(rEye,cEye)!=-1)
    {
        return false;
    }
    if(_s[moveid]._red)
    {
        if(row>4)
            return false;
    }
    else
    {
        if(row<5)
            return false;
    }


    return true;
}
bool board::canmove4(int moveid, int row, int col, int killid)
{
    //che
    int ret=getStoneCountAtLine(_s[moveid]._row,_s[moveid]._col,row,col);
    if(ret==0)
        return true;
    return false;



}
bool board::canmove5(int moveid, int row, int col, int killid)
{
    //ma
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    if(d!=12&&d!=21)
        return false;
    if(d==12)
    {
        if(getStoneId(_s[moveid]._row,(_s[moveid]._col+col)/2)!=-1)
            return false;
    }
    else
    {

        if(getStoneId((_s[moveid]._row+row)/2,_s[moveid]._col)!=-1)
            return false;
    }



    return true;
}
bool board::canmove6(int moveid, int row, int col, int killid)
{
    //pao
    int ret=getStoneCountAtLine(_s[moveid]._row,_s[moveid]._col,row,col);
    //吃敌法门
    if(killid!=-1)
    {
        if(ret==1)
            return true;
    }
    else
    {
        if(ret==0)
            return true;

    }


    return false;
}
bool board::canmove7(int moveid, int row, int col, int killid)
{
    //bing
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    if(d!=10&&d!=1)
        return false;
    if(_s[moveid]._red)
    {
        if(_s[moveid]._row>row)
            return false;
        if(_s[moveid]._row<5)
        {
            if(_s[moveid]._col!=col)
            {
                return false;
            }
        }
    }
    else
    {
        if(_s[moveid]._row<row)
            return false;
        if(_s[moveid]._row>4)
        {
            if(_s[moveid]._col!=col){
                return false;
            }
        }
    }

    return true;
}

bool board::canmove(int moveid, int row, int col, int killid)
{
    if(killid!=-1)
    if(_s[moveid]._red==_s[killid]._red)//moveid和killid颜色相同
    {
        //换选择
        _selectid=killid;
        update();

        return false;

    }

    switch(_s[moveid]._type)
    {

        case stone::JIANG:
            return canmove1(moveid,row,col,killid);
            break;
        case stone::SHI:
            return canmove2(moveid,row,col,killid);
            break;
        case stone::XIANG:
            return canmove3(moveid,row,col,killid);
            break;
        case stone::CHE:
            return canmove4(moveid,row,col,killid);
            break;
        case stone::MA:
            return canmove5(moveid,row,col,killid);
            break;
        case stone::PAO:
            return canmove6(moveid,row,col,killid);
            break;
        case stone::BING:
            return canmove7(moveid,row,col,killid);
            break;

    }
    return true;




}
int board::getStoneId(int row, int col)
{
    for(int i=0;i<32;i++)
    {
        if(_s[i]._row==row&&_s[i]._col==col&&!_s[i]._dead)
        {
            return i;
        }

    }
    return -1;

}

int board::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret=0;
    if(row1!=row2&&col1!=col2)
        return -1;
    if(row1==row2&&col1==col2)
        return -1;
    if(row1==row2)
    {
        int min=col1<col2?col1:col2;
        int max=col1<col2?col2:col1;
        for(int col=min+1;col<max;++col)
        {
            if(getStoneId(row1,col)!=-1)
                ++ret;
        }

    }
    else
    {
        int min=row1<row2?row1:row2;
        int max=row1<row2?row2:row1;
        for(int row=min+1;row<max;++row)
        {
            if(getStoneId(row,col1)!=-1)
                ++ret;
        }
    }
    return ret;



}



/*void board::mouseReleaseEvent(QMouseEvent *event)
{

    QPoint pt=event->pos();
    //将pt转化成象棋的行列值
    //判断这个行列值上面有没有棋子
    int row,col;
    bool bRet=getRowCol(pt,row,col);
    if(bRet==false)//点到棋盘外
        return;
    int i;
    int clickid=-1;
    for(i=0;i<32;++i)//找到所对应的棋子
    {
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false)
        {
            break;
        }
    }
    if(i<32)
    {
        clickid=i;


    }
    if(_selectid==-1) //棋子未被选中，如果被选中，赋予新值
    {
        if(clickid!=-1)
        {
            if(_beredturn==_s[clickid]._red)
           {
                _selectid=clickid;
                update();
            }

        }
    }
    else{
        if(canmove(_selectid,row,col,clickid))
           { _s[_selectid]._row=row;     //棋子被选中，如果点新的位置，那么把新的位置给该棋子
            _s[_selectid]._col=col;
            if(clickid !=-1)
            {

                _s[clickid]._dead=1;  //若点击处存在棋子，那么把棋子删除

            }
            _selectid=-1;
            _beredturn=!_beredturn;
            update();

            }
        }





}

*/

void board::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
    {
        return;
    }
    click(event->pos());//获取点击的位置

}
void board::click(QPoint pt)
{
    int row,col;
    bool bClicked=getRowCol(pt,row,col);//获取对应的行列和点的位置
    if(!bClicked)return ;
    int id=getStoneId(row,col);//获取象棋的id
    click(id,row,col);
}

void board::click(int id,int row,int col){
    if(this->_selectid==-1)
    {
        trySelectStone(id);
    }
    else
    {
        tryMoveStone(id,row,col);
    }

}

void board::trySelectStone(int id)
{//选中棋子
    if(id==-1)
        return ;
    if(_beredturn==_s[id]._red)
    {
        _selectid=id;
        update();
    }
}
void board::tryMoveStone(int id, int row, int col)
{//移动棋子
    if(canmove(_selectid,row,col,id))
    {
        _s[_selectid]._row=row;
        _s[_selectid]._col=col;
        if(id!=-1)
        {
            _s[id]._dead=-1;
        }
        _selectid=-1;
        _beredturn=!_beredturn;
        update();
    }


}



