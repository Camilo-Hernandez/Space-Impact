#include "playerbullet.h"
#include "enemybullet.h"
#include "game.h"
#include "menu.h"
#include <QTimer>

extern Menu *menu;

PlayerBullet::PlayerBullet(QObject *parent)
    : QObject{parent}
{
    setPixmap(QPixmap(":/images/images/playerBullet.png"));
    setScale(0.35);
    //qDebug() << "Bala creada";

    // Conectar la señal timeout() activada por la barra espaciadora y el método move()
    // Se necesita un timer para producir eventos periódicos, como el movimiento
    bullet_timer = new QTimer();
    connect(bullet_timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(bullet_timer, SIGNAL(timeout()), this, SLOT(collidesWithEnemyBullets()));
    bullet_timer->start(20); // milisegundos que tarda en efectuar la función move()
}

PlayerBullet::~PlayerBullet(){
    //qDebug() << "Bala eliminada de memoria";
}

void PlayerBullet::move()
{
    // mover la bala a la derecha
    setPos(x()+10, y());
    // eliminar la bala de la memoria si pasa la frontera derecha de la escena
    if (pos().x()>1100){
        this->~PlayerBullet();
    }
}

void PlayerBullet::collidesWithEnemyBullets(){
    foreach(QGraphicsItem *item, collidingItems()){
        // Aquí se evalúa la colisión entre balas
        if(dynamic_cast<EnemyBullet*>(item)){
            // Si colisiona con tipo EnemyBullet, baja la durabilidad del PlayerBullet en 1 y elimina el EnemyBullet
            // Pensado para balas con más durabilidad
            emit setScore(+5); // enviar la señal de aumentar el score en 5 antes de destruir la bala
            this->setDurability(getDurability()-1);
            delete item; // eliminar la bala enemiga
        }
    };
}

int PlayerBullet::getDurability() const
{
    return durability;
}

void PlayerBullet::setDurability(int newDurability)
{
    durability = newDurability;
    // destruir la bala si su vida llega a cero
    if (durability <= 0) this->~PlayerBullet();
}
