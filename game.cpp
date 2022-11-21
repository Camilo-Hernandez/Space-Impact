#include "game.h"
#include "enemy.h"
#include "qgraphicsscene.h"
#include "qtimer.h"
#include "ui_game.h"

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
    //move the player to the bottom center of the view
    player->setPos(100, 150);
    // make the item focusable to be able to respond to events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the item to the scene
    scene->addItem(player);

    // --- agregar el score --- //
    score = new Score();
    scene -> addItem(score);
    score->setPos(900, 0);

    // --- actualizar los indicadores de salud --- //
    connect(player, SIGNAL(healthChanged(int)), this, SLOT(changeHealth(int)));

    // --- crear los enemigos periódicamente --- //
    enemies_timer = new QTimer();
    connect(enemies_timer, SIGNAL(timeout()), this, SLOT(spawnEnemies()));
    enemies_timer->start(1000);

}

void Game::spawnEnemies(){
    Enemy *enemy = new Enemy(this);
    scene->addItem(enemy);
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
    }
}

Game::~Game()
{
    delete ui;
}

QMovie *Game::getBg_gif() const
{
    return bg_gif;
}

void Game::setBg_gif(QMovie *newBg_gif)
{
    bg_gif = newBg_gif;
}
