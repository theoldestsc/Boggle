#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include "sources/block.h"
#include "sources/libgameitems/src/board.h"
#include "sources/libgameitems/src/cube.h"
#include <QWidget>


#include <QMouseEvent>

class QGraphicsScene;
class QGraphicsView;

class GameWindow : public QWidget
{
    public:
        GameWindow(QWidget *parent = nullptr);
    protected:
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
    private:
        Board board;
        QGraphicsScene *m_scene;
        QGraphicsView *m_view;
        
};

#endif