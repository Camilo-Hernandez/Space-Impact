#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score(QGraphicsItem *parent=0); // darle un padre por defecto de 0
    int getScore();
private:
    int score;
public slots:
    void changeScore(int change);
};

#endif // SCORE_H
