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
    int getHealth() const;
    void setHealth(int newHealth);
    QTimer *collision_timer;

private:
    int health=2;

public slots:
    void move(int velocity=8);
    void shoot();
    void collidesWithEnemies();
};

#endif // ENEMY_H
