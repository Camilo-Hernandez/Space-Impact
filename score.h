#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score(QGraphicsItem *parent = nullptr); // darle un padre por defecto de 0
    int getScore();
private:
    int score=0;
public slots:
    ~Score();
    void changeScore(int change);
};

#endif // SCORE_H
