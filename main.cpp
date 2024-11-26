#include <QApplication>
#include "snake.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SnakeGame game;
    // устанавливаем цвет фона
    //game.setStyleSheet("background-color:black;");
    game.show();
    return a.exec();
}
