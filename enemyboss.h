#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "enemy.h"
#include <QObject>

class EnemyBoss : public Enemy
{
    Q_OBJECT
public:
    explicit EnemyBoss(QObject *parent = nullptr);
    ~EnemyBoss();
};

#endif // ENEMYBOSS_H
