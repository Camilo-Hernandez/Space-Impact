#include "menu.h"

#include <QApplication>

Menu *menu;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu = new Menu();
    menu->show();
    return a.exec();
}
