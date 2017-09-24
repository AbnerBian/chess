#ifndef STONE_H
#define STONE_H
#include<QString>

class stone
{
public:
    stone();

    enum TYPE {JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    int _row;
    int _col;
    int _id;
    bool _dead;
    bool _red;
    TYPE _type;
    void init(int id)
    {
        struct {
                int row, col;
                stone::TYPE type;
            } pos[16] = {
            {0, 0, stone::CHE},
            {0, 1, stone::MA},
            {0, 2, stone::XIANG},
            {0, 3, stone::SHI},
            {0, 4, stone::JIANG},
            {0, 5, stone::SHI},
            {0, 6, stone::XIANG},
            {0, 7, stone::MA},
            {0, 8, stone::CHE},

            {2, 1, stone::PAO},
            {2, 7, stone::PAO},
            {3, 0, stone::BING},
            {3, 2, stone::BING},
            {3, 4, stone::BING},
            {3, 6, stone::BING},
            {3, 8, stone::BING},
            };

        _id = id;
        _dead = false;
        _red = id<16;

        if(id < 16)
        {
            _row = pos[id].row;
            _col = pos[id].col;
            _type = pos[id].type;
        }
        else
        {
            _row = 9-pos[id-16].row;
            _col = 8-pos[id-16].col;
            _type = pos[id-16].type;
        }

    }

    QString getText(){
        switch(this->_type)
            {
                case CHE:
                    return "车";
                case MA:
                    return "马";
                case PAO:
                    return "炮";
                case BING:
                    return "兵";
                case JIANG:
                    return "将";
                case SHI:
                    return "士";
                case XIANG:
                    return "相";
            }
        return "错误";
    }


};



#endif // STONE_H
