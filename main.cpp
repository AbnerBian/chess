#include "board.h"
#include <QApplication>
#include "singlegame.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //SingleGame w;
    board w;
    w.show();

    return a.exec();
}
