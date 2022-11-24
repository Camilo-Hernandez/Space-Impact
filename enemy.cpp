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
    setPixmap(QPixmap(":/images/images/basicEnemy.png"));
    setScale(0.35);

    // Conectar la señal timeout() activada por la barra espaciadora y el método move()
    // Se necesita un timer para producir eventos periódicos, como el movimiento
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(move()));
    enemyTimer->start(40); // milisegundos que tarda en efectuar la función move()
    connect(shootingTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    shootingTimer->start(1500);

    // Timer para detectar colisiones con los enemigos
    collision_timer = new QTimer();
    connect(collision_timer, SIGNAL(timeout()), this, SLOT(collidesWithEnemies()));
    collision_timer->start(20);
}

Enemy::~Enemy(){
    qDebug() << "Enemigo eliminado de memoria";
}

void Enemy::move(int velocity)
    // mover el enemigo a la izquierda
{
    setPos(x()-velocity, y());
    // eliminar el enemigo cuando desaparece de la escena y disminuir el puntaje
    if (pos().x() < 0){
        // remover el enemigo de memoria
        this->~Enemy();
        // Disminuir el Score en 3
        menu->game->score->changeScore(-3);
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
            this->~Enemy();
            menu->game->score->changeScore(+10);
        }

    }
}

void Enemy::collidesWithEnemies(){
    // Si Player colisiona con tipo Enemy o EnemyBullet, baja una vida al Player
    foreach(QGraphicsItem *item, collidingItems()){
        if(dynamic_cast<PlayerBullet*>(item)){ // hacer una transformación del item a EnemyBullet
            delete item;
            this->setHealth(getHealth()-1); // disminuir la salud
        }
    }
}

int Enemy::getHealth() const
{
    return health;
}
