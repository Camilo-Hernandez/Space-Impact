#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class PlayerBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit PlayerBullet(QObject *parent = nullptr);
    ~PlayerBullet();
public slots:
    void move();
    void collidesWithEnemies();
};

#endif // PLAYERBULLET_H
