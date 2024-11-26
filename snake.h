#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QVector>
#include <QPixmap>

class SnakeGame : public QWidget {
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    void loadImages();
    void initGame();
    void locateApple();
    void move();
    void checkCollision();

    QPoint &NewFunction(int i);

    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

    QVector<QPoint> snake;
    QPoint apple;
    int score;
    Direction dir;
    bool gameOver;
    QTimer *timer;

    QPixmap appleImage;
    QPixmap dotImage;
    QPixmap headImage;
};

#endif // SNAKE_H
