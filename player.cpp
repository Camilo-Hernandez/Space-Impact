#include "player.h"
#include "enemy.h"
#include "enemybullet.h"
#include "playerbullet.h"
#include "qgraphicsscene.h"
#include <QKeyEvent>

Player::Player(QObject *parent)
    : QObject{parent}
{
    setPixmap(QPixmap(":/images/images/player.png"));
    setScale(0.35);

    // Timer para detectar colisiones con los enemigos
    QTimer *collision_timer = new QTimer();
    connect(collision_timer, SIGNAL(timeout()), this, SLOT(collidesWithEnemies()));
    collision_timer->start(30);
}

Player::~Player(){
    qDebug() << "Jugador eliminado de memoria";
}

void Player::keyPressEvent(QKeyEvent *event)
{
    // Mover la nave con las flechas dentro de los límites de la escena
    if (event->key() == Qt::Key_Left && pos().x() > 0){
        setPos(x()-10, y());
    }
    else if (event->key() == Qt::Key_Right && pos().x() + 100 < 1000){
        setPos(x()+10, y());
    }
    else if (event->key() == Qt::Key_Up && pos().y() > 0){
            setPos(x(),y()-10);
    }
    else if (event->key() == Qt::Key_Down && pos().y() < 550){
        setPos(x(),y()+10);
    }
    else if (event->key() == Qt::Key_Space){
        // Crear una bala
        PlayerBullet *playerbullet = new PlayerBullet();
        playerbullet->setPos(x()+143,y()+42); // posición de la bala respecto de la esquina superior izquierda del Player
        scene()->addItem(playerbullet); // cada item tiene un puntero a la escena a la que será añadido
    }
}

int Player::getHealth() const
{
    return health;
}

void Player::setHealth(int newHealth)
{
    if (health != newHealth) {
        health = newHealth;
        emit healthChanged(newHealth);
        qDebug() << "Senal emitida";
    }
}

void Player::collidesWithEnemies(){
    // Si Player colisiona con tipo Enemy o EnemyBullet, baja una vida al Player
    foreach(QGraphicsItem *item, collidingItems()){
        if(dynamic_cast<Enemy*>(item) || dynamic_cast<EnemyBullet*>(item)){ // hacer una transformación a Enemy o EnemyBullet
            delete item; // eliminar enemigo

            // actualizar los indicadores de salud
            this->setHealth(getHealth()-1);
            //qDebug() << "Player colisiona con enemigo";
            qDebug() << this->getHealth();

            // destruir el jugador si la vida llega a cero
            if (getHealth() == 0) this->~Player();
        }
    }
}
