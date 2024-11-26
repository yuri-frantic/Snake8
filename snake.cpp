#include "snake.h"
#include <QTimerEvent>
#include <QMessageBox>

SnakeGame::SnakeGame(QWidget *parent) : QWidget(parent), score(0), dir(STOP), gameOver(false) {
    setFixedSize(400, 400);
    loadImages();
    initGame();
}

SnakeGame::~SnakeGame() {}

void SnakeGame::loadImages() {
    appleImage.load("apple.png");
    dotImage.load("dot.png");
    headImage.load("head.png");
}

void SnakeGame::initGame() {
    snake.clear();
    snake.append(QPoint(5, 5));
    snake.append(QPoint(5, 4));
    snake.append(QPoint(5, 3));
    snake.append(QPoint(5, 2));
    
    locateApple();

    dir = STOP;
    score = 0;
    gameOver = false;

    startTimer(100); // Запуск таймера с интервалом 100 мс
}

void SnakeGame::locateApple() {
    apple.setX(rand() % (width() / 10));
    apple.setY(rand() % (height() / 10));
    //QMessageBox::information(this, "Яблоко", QString("x: %1").arg(apple.rx())+"  "+ QString("y: %1").arg(apple.ry()));
}

void SnakeGame::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Отрисовка сегментов змеи
    for (int i = 0; i < snake.size(); ++i) {
        if (i == 0) {
            painter.drawPixmap(snake[i].x() * 10, snake[i].y() * 10, headImage);
            //QMessageBox::information(this, "Голова", QString("x: %1").arg(snake[i].x())+"  "+ QString("y: %1").arg(snake[i].y()));
            
        } else {
            painter.drawPixmap(snake[i].x() * 10, snake[i].y() * 10, dotImage);
            //QMessageBox::information(this, "Тело", QString("Тело: %1").arg(i)+QString("x: %1").arg(snake[i].x())+"  "+ QString("y: %1").arg(snake[i].y()));
        }
    }

    // Отрисовка яблока
    painter.drawPixmap(apple.x() * 10, apple.y() * 10, appleImage);

    // Отображение счета
    painter.drawText(10, 10, QString("Очки: %1").arg(score));

    // Если игра окончена
    if (gameOver == true) {
        painter.drawText(rect(), Qt::AlignCenter, "Игра окончена!");
        QMessageBox::information(this, "Игра окончена ", "Набранные очки: " + QString::number(score));
        initGame(); // Перезапуск игры после окончания
    }
}

void SnakeGame::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up && dir != DOWN) dir = UP;
    else if (event->key() == Qt::Key_Down && dir != UP) dir = DOWN;
    else if (event->key() == Qt::Key_Left && dir != RIGHT) dir = LEFT;
    else if (event->key() == Qt::Key_Right && dir != LEFT) dir = RIGHT;
}

void SnakeGame::move() {
    if (gameOver) return;

    // Сохранение позиции головы змеи
    QPoint prevSegment = snake.first();

    // Перемещение головы змеи
    switch (dir) {
        case LEFT: prevSegment.setX(prevSegment.x() - 1); break;
        case RIGHT: prevSegment.setX(prevSegment.x() + 1); break;
        case UP: prevSegment.setY(prevSegment.y() - 1); break;
        case DOWN: prevSegment.setY(prevSegment.y() + 1); break;
        default: break;
    }

    // Проверка на столкновение с яблоком
    if (prevSegment == apple)
    {
        score += 10;
        locateApple();
        snake.append(prevSegment); // Увеличиваем длину змеи
    }
    else
    {
        if (dir != STOP)
        {
            // Перемещение тела змеи

            for (int i = snake.size() - 1; i > 0; --i)
            {

                snake[i] = snake[i - 1];
                // QMessageBox::information(this, "Тело", QString("Тело: %1").arg(i)+QString("x: %1").arg(snake[i].x())+"  "+ QString("y: %1").arg(snake[i].y()));
            }

            snake[0] = prevSegment; // Обновляем позицию головы
            // QMessageBox::information(this, "Голова", QString("x: %1").arg(snake[0].x())+"  "+ QString("y: %1").arg(snake[0].y()));

            // Проверка на столкновение с стенами и телом змеи
            checkCollision();
        }
    }

    update(); // Перерисовка виджета
}

void SnakeGame::checkCollision() {
    
    // Проверка на столкновение со стенами
    if (snake[0].x() < 0 || snake[0].x() >= width() / 10 ||
        snake[0].y() < 0 || snake[0].y() >= height() / 10) {
        gameOver = true;
        
    }

    // Проверка на столкновение с самим собой
    for (int i = 1; i < snake.size(); ++i) {
        //QMessageBox::information(this, "Тело", QString("Тело: %1:  ").arg(i)+QString("x: %1").arg(snake[0].rx())+"  "+ QString("y: %1").arg(snake[0].ry()));
        if (snake[i] == snake[0]) {
            gameOver = true;
            //QMessageBox::information(this, "!!!!!!!!!", "checkCollision" + QString::number(score));
            break;
        }
    }
}

void SnakeGame::timerEvent(QTimerEvent *event) {
    move(); // Движение змеи в каждом тике таймера
}

