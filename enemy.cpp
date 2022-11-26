#include "enemy.h"
#include "enemybullet.h"
#include "menu.h"
#include "playerbullet.h"
#include "qgraphicsscene.h"
#include "qtimer.h"

extern Menu *menu;

Enemy::Enemy(QObject *parent, int posy, QTimer *enemyTimer, QTimer *shootingTimer)
    : QObject{parent}
{
    // Crear el enemigo en una posición aleatoria en y() y 1100 en x()
    setPos(1100, posy);
    setScale(0.35);

    // Conectar la señal timeout() activada por la barra espaciadora y el método move()
    // Se necesita un timer para producir eventos periódicos, como el movimiento
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(move()));
    enemyTimer->start(40); // milisegundos que tarda en efectuar la función move()
    connect(shootingTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    shootingTimer->start(1200);

    // Timer para detectar colisiones con los enemigos
    collision_timer = new QTimer();
    connect(collision_timer, SIGNAL(timeout()), this, SLOT(collidesWithPlayerBullets()));
    collision_timer->start(20);
}

Enemy::~Enemy(){
//    qDebug() << "Enemigo eliminado de memoria";
}

void Enemy::move(int velocity)
    // mover el enemigo a la izquierda
{
    setPos(x()-velocity, y());
    // eliminar el enemigo cuando desaparece de la escena y disminuir el puntaje
    if (pos().x() < 0){
        // Disminuir el Score en 3
        emit changeScore(-3);
        // remover el enemigo de memoria
        this->~Enemy();
    }
}

void Enemy::shoot()
{
    // Crear una bala enemiga
    EnemyBullet *enemyBullet = new EnemyBullet();
    enemyBullet ->setPos(x()-50,y()+48); // posición de la bala respecto de la esquina superior izquierda del Enemy
    scene()->addItem(enemyBullet); // cada item tiene un puntero a la escena a la que será añadido
}

void Enemy::setHealth(int newHealth)
{
    if (health != newHealth) {
        health = newHealth;
        // destruir el enemigo si su salud es 0 y Aumentar el Score en 10
        if (health <= 0)        {
            emit changeScore(+10);
            this->~Enemy();
        }
    }
}

void Enemy::setImage(QPixmap image)
{
    setPixmap(image);
}

void Enemy::setImage(int numImage)
// Función sobrecargada
{
    QString image;
    if (numImage == 1){
        image = ":/images/images/basicEnemy.png";
    }
    else if (numImage == 2){
        image = ":/images/images/finalBoss.png";
    }
    setPixmap(QPixmap(image));
}

void Enemy::collidesWithPlayerBullets(){
    // Si Enemy colisiona con tipo PlayerBullet, baja la salud en 1
    foreach(QGraphicsItem *item, collidingItems()){
        if(dynamic_cast<PlayerBullet*>(item)){ // hacer una transformación del item a EnemyBullet
            delete item;
            this->setHealth(getHealth()-1); // disminuir la salud del enemigo
        }
    }
}

int Enemy::getHealth() const
{
    return health;
}
