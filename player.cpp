#include "player.h"
#include "enemybullet.h"
#include "menu.h"
#include "playerbullet.h"
#include "qgraphicsscene.h"
#include "qtimer.h"
#include <QKeyEvent>

extern Menu *menu;

Player::Player(QObject *parent)
    : QObject{parent}
{
    setPixmap(QPixmap(":/images/images/player.png"));
    setScale(0.35);

    // Timer para detectar colisiones con los enemigos
    collision_timer = new QTimer();
    connect(collision_timer, SIGNAL(timeout()), this, SLOT(collidesWithEnemies()));
    collision_timer->start(20);
}

Player::~Player(){
    qDebug() << "Jugador eliminado de memoria";
}

void Player::keyPressEvent(QKeyEvent *event)
// Función reservada de los QObject que detecta automáticamente las teclas presionadas
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
        PlayerBullet *playerbullet = new PlayerBullet(scene());
        playerbullet->setPos(x()+143,y()+42); // posición de la bala respecto de la esquina superior izquierda del Player
        scene()->addItem(playerbullet); // cada item tiene un puntero a la escena a la que será añadido

        // Recibir la señal de choque de la bala con una bala enemiga y enviar otra señal con el mismo valor
        // el Player está sirviendo de puente entre la bala y la clase Game para que pueda cambiar el Score
        connect(playerbullet, SIGNAL(setScore(int)), this, SLOT(sendChangedScore(int)));
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
        // enviar señal al slot de la clase
        // Game para actualizar los corazones de la ui
        emit healthChanged(newHealth);
        // destruir el jugador si su salud es 0
        if (health <= 0) this->~Player();
    }
}

void Player::collidesWithEnemies(){
    // Si Player colisiona con tipo Enemy o EnemyBullet, baja una vida al Player
    foreach(QGraphicsItem *item, collidingItems()){
        // dynamic_cast Tratar de hacer una transformación del item a EnemyBullet.
        // Si es exitosa, pasa el if.
        if(dynamic_cast<EnemyBullet*>(item)){
            emit scoreChanged(-5); // Disminuir el Score si le da una bala
            delete item; // eliminar la bala
            this->setHealth(getHealth()-1); // disminuir la salud
        }
    }
}

void Player::sendChangedScore(int scoreDiff)
{
    // envía el valor a sumar al Score actual, al
    emit scoreChanged(scoreDiff);
}

void Player::healthChanged()
{
    if (health < 3){
        this->setHealth(getHealth()+1); // aumentar la salud
    }
}
