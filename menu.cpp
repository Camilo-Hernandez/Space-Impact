#include "menu.h"
#include "controls.h"
#include "ui_menu.h"
#include <QFont>
#include <QFontDatabase>

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    // poner gif de fondo de pantalla
    setBg_gif(new QMovie(":/images/images/bg_menu.gif"));
    ui->lbl_bg->setMovie(getBg_gif());
    getBg_gif()->start();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::startGame()
{
    game = new Game();
    game->show();
}

void Menu::setBg_gif(QMovie *_bg_gif)
{
    bg_gif = _bg_gif;
}

QMovie *Menu::getBg_gif() const
{
    return bg_gif;
}

void Menu::on_btn_play_clicked()
{
    startGame();
}

void Menu::on_btn_controls_clicked()
{
    Controls *controls = new Controls();
    controls->show();
}


void Menu::on_btn_quit_clicked()
{
    close();
}

void Menu::showEndingMessage()
{
    this->endingMsgBox.setWindowTitle("Nivel terminado");
    this->endingMsgBox.setIcon(QMessageBox::Information);
    this->endingMsgBox.setStandardButtons(QMessageBox::Yes);
    this->endingMsgBox.addButton(QMessageBox::No);
    this->endingMsgBox.setDefaultButton(QMessageBox::Yes);
    this->endingMsgBox.setEscapeButton(QMessageBox::Escape);
    this->endingMsgBox.setText("Perdiste :(\n Puntaje final: "
                               + QString::number(game->getScore()) + "\n¿Volver a jugar?");
    if (QMessageBox::Yes == this->endingMsgBox.exec()){
        //qDebug() << "Yes";
        game = new Game();
        game->show();
    }
    else{
        //qDebug() << "No";
        QCoreApplication::quit();
    }
}
