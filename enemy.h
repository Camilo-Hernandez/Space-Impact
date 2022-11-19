#ifndef ENEMY_H
#define ENEMY_H

#include "qtimer.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = nullptr, int posy = rand() % 500, QTimer *enemyTimer = new QTimer(), QTimer *shootingTimer = new QTimer());
    ~Enemy();

public slots:
    void move(int velocity=8);
    void shoot();
};

#endif // ENEMY_H
