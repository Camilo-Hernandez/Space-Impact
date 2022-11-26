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
    QTimer *bullet_timer;

    int getDurability() const;
    void setDurability(int newDurability);

private:
    int durability=1;

public slots:
    void move();
    void collidesWithEnemyBullets();

signals:
    void setScore(int);
};

#endif // PLAYERBULLET_H
