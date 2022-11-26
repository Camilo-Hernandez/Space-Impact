#include "game.h"
#include "enemy.h"
#include "enemyboss.h"
#include "heart.h"
#include "qgraphicsscene.h"
#include "qtimer.h"
#include "ui_game.h"
#include "menu.h"

extern Menu *menu;

Game::Game(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::Game)
{
    // --- configurar la ventana --- //
    ui->setupUi(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH, HEIGHT);

    // --- poner gif de fondo en el QLabel de la ui --- //
    /* para poner un gif como fondo de pantalla
     * es necesario poner un graphicsView en la ui transparente
     * encima del QLabel donde se pone el gif
     * El graphicsView es donde se pondrá la escena
     */
    setBg_gif(new QMovie(":/images/images/bg_game.gif"));
    ui->lbl_bg->setMovie(getBg_gif());
    getBg_gif()->start();

    // --- crear la escena donde añadir el jugador y los enemigos sobre el graphicsView de la ui --- //
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0, WIDTH-10, HEIGHT-10);
    ui->graphicsView->setMaximumSize(WIDTH, HEIGHT);
    ui->graphicsView->setScene(scene);

    // --- crear el jugador --- //
    player = new Player(this);
    // mover el jugador a la posición (100, 150)
    player->setPos(100, 150);
    // hacer el jugador enfocable para que se pueda mover
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // añadir el jugador a la escena
    scene->addItem(player);

    // --- actualizar los indicadores de salud --- //
    connect(player, SIGNAL(healthChanged(int)), this, SLOT(changeHealth(int)));

    // --- actualizar el puntaje --- //
    connect(player, SIGNAL(scoreChanged(int)), this, SLOT(setScore(int)));

    // --- crear los enemigos periódicamente --- //
    enemies_timer = new QTimer();
    connect(enemies_timer, SIGNAL(timeout()), this, SLOT(spawnEnemies()));
    enemies_timer->start(1500);

    // --- crear los corazones periódicamente --- //
    heartsTimer = new QTimer();
    connect(heartsTimer, SIGNAL(timeout()), this, SLOT(spawnHearts()));
    heartsTimer->start(5000);

    // --- crear el Jefe Final --- //
    QTimer::singleShot(30000, this, SLOT(activateBoss()));
}

void Game::spawnEnemies(){
    Enemy *enemy = new Enemy(this);
    scene->addItem(enemy);
    enemy->setImage(QPixmap(":/images/images/basicEnemy.png"));
    connect(enemy, SIGNAL(changeScore(int)), this, SLOT(setScore(int)));
}

void Game::spawnHearts()
{
    Heart *heart = new Heart(this);
    scene->addItem(heart);
    connect(heart, SIGNAL(increaseHealth()), player, SLOT(healthChanged()));
}

void Game::changeHealth(int newHealth)
// Establecer la visibilidad de los corazones según la salud
{
    if (newHealth == 3){
        ui->lbl_heart3->setVisible(true);
    }
    else if (newHealth == 2){
        ui->lbl_heart2->setVisible(true);
        ui->lbl_heart3->setVisible(false);
    }
    else if (newHealth == 1){
        ui->lbl_heart2->setVisible(false);
    }
    else if (newHealth == 0){
        ui->lbl_heart1->setVisible(false);
        // al quedarse sin vida, muestra el mensaje de finalización
        //emit finishLevel();
        this->~Game();
        menu->showEndingMessage();
    }
}

int Game::getScore() const
{
    return score;
}

void Game::setScore(int scoreDiff)
{
    score += scoreDiff;
    ui->lbl_score->setText(QString::number(score));
}

void Game::activateBoss()
{
    enemies_timer->stop();
    heartsTimer->stop();
    EnemyBoss *enemyBoss = new EnemyBoss();
    scene->addItem(enemyBoss);
    connect(enemyBoss, SIGNAL(changeScore(int)), this, SLOT(setScore(int)));
}

Game::~Game()
{
    delete ui;
    qDebug() << "Game eliminado de memoria";
}

QMovie *Game::getBg_gif() const
{
    return bg_gif;
}

void Game::setBg_gif(QMovie *newBg_gif)
{
    bg_gif = newBg_gif;
}
