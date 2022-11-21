#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class EnemyBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EnemyBullet(QObject *parent = nullptr);
    ~EnemyBullet();
    QTimer *bullet_timer;

public slots:
    void move();
};

#endif // ENEMYBULLET_H
