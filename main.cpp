#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsEllipseItem>

#include "sources/block.h"

/*TODO:
    Грани рисуются тольо для визуального представления,
    кубики можно будет типа поворачивать во двум осям.
    По двойному клику в направлении
    взависимости от положения мышки на верхней грани
    Знание на какой конкретно грани мышка нас интересует
    только из косметических целей создания
    эффекта нажатия от игрока
*/

class GameWindow : public QWidget
{
    public:
        GameWindow(QWidget *parent = nullptr) : QWidget(parent)
        {
            //TODO: каждый уровень в одной цветовой палитре
            QStringList colors = {
            ":/images/colors/blue_mask.png",
            ":/images/colors/cyan_mask.png",
            ":/images/colors/magneta_mask.png",
            ":/images/colors/purple_mask.png",
            ":/images/colors/yellow_mask.png",
            ":/images/colors/green_mask.png",
            ":/images/colors/orange_mask.png",
            ":/images/colors/red_mask.png"
            };

            // Топы (все буквы a..z)
            QStringList tops = {
                ":/images/letters/a_top.png",
                ":/images/letters/b_top.png",
                ":/images/letters/c_top.png",
                ":/images/letters/d_top.png",
                ":/images/letters/e_top.png",
                ":/images/letters/f_top.png",
                ":/images/letters/g_top.png",
                ":/images/letters/h_top.png",
                ":/images/letters/i_top.png",
                ":/images/letters/j_top.png",
                ":/images/letters/k_top.png",
                ":/images/letters/l_top.png",
                ":/images/letters/m_top.png",
                ":/images/letters/n_top.png",
                ":/images/letters/o_top.png",
                ":/images/letters/p_top.png",
                ":/images/letters/q_top.png",
                ":/images/letters/r_top.png",
                ":/images/letters/s_top.png",
                ":/images/letters/t_top.png",
                ":/images/letters/u_top.png",
                ":/images/letters/v_top.png",
                ":/images/letters/w_top.png",
                ":/images/letters/x_top.png",
                ":/images/letters/y_top.png",
                ":/images/letters/z_top.png"
            };
    
            // Левый бок (a..z)
            QStringList lefts = {
                ":/images/letters/a_left.png",
                ":/images/letters/b_left.png",
                ":/images/letters/c_left.png",
                ":/images/letters/d_left.png",
                ":/images/letters/e_left.png",
                ":/images/letters/f_left.png",
                ":/images/letters/g_left.png",
                ":/images/letters/h_left.png",
                ":/images/letters/i_left.png",
                ":/images/letters/j_left.png",
                ":/images/letters/k_left.png",
                ":/images/letters/l_left.png",
                ":/images/letters/m_left.png",
                ":/images/letters/n_left.png",
                ":/images/letters/o_left.png",
                ":/images/letters/p_left.png",
                ":/images/letters/q_left.png",
                ":/images/letters/r_left.png",
                ":/images/letters/s_left.png",
                ":/images/letters/t_left.png",
                ":/images/letters/u_left.png",
                ":/images/letters/v_left.png",
                ":/images/letters/w_left.png",
                ":/images/letters/x_left.png",
                ":/images/letters/y_left.png",
                ":/images/letters/z_left.png"
            };
            // Правый бок (a..z)
            QStringList rights = {
                ":/images/letters/a_right.png",
                ":/images/letters/b_right.png",
                ":/images/letters/c_right.png",
                ":/images/letters/d_right.png",
                ":/images/letters/e_right.png",
                ":/images/letters/f_right.png",
                ":/images/letters/g_right.png",
                ":/images/letters/h_right.png",
                ":/images/letters/i_right.png",
                ":/images/letters/j_right.png",
                ":/images/letters/k_right.png",
                ":/images/letters/l_right.png",
                ":/images/letters/m_right.png",
                ":/images/letters/n_right.png",
                ":/images/letters/o_right.png",
                ":/images/letters/p_right.png",
                ":/images/letters/q_right.png",
                ":/images/letters/r_right.png",
                ":/images/letters/s_right.png",
                ":/images/letters/t_right.png",
                ":/images/letters/u_right.png",
                ":/images/letters/v_right.png",
                ":/images/letters/w_right.png",
                ":/images/letters/x_right.png",
                ":/images/letters/y_right.png",
                ":/images/letters/z_right.png"
        };

            m_view = new QGraphicsView(m_scene);
            m_view->setRenderHint(QPainter::Antialiasing);
            m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

            int width = 1080;
            int height = 720;
            setFixedSize(width, height);

            // Создаем сцену фиксированного размера
            m_scene = new QGraphicsScene(this);
            //m_scene->setSceneRect(0, 0, 1080, 720); // сцена 1080x720

            m_scene->setSceneRect(- width / 2, - height / 2, width,  height);
            m_view = new QGraphicsView(m_scene);
            m_view->setRenderHint(QPainter::Antialiasing);

            // Отключаем полосы прокрутки
            m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

            // Подгоняем размер вида под сцену
            m_view->setFixedSize(width, height);

            QVBoxLayout *layout = new QVBoxLayout(this);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->addWidget(m_view);
            setLayout(layout);

            //1. Создаем изометрическую трансформацию
            QTransform cube_transform;
            cube_transform.scale(1, 0.5);
            cube_transform.rotate(-45);

            m_view->setTransform(cube_transform);
            m_view->centerOn(0, 0);

            int rows = 5;
            int cols = 5;

            int x_offset = 10;
            int y_offset = 10;

            //[NOTE]: 100 это ребро куба
            const int spacing_x = -100.0 - x_offset;
            const int spacing_y = 100.0 + y_offset;

            int grid_width = (cols - 1) * spacing_x;
            int grid_height = (rows - 1) * spacing_y;


            int start_x = - grid_width / 2;
            int start_y = - grid_height / 2;

            for (int row = 0; row < rows; ++row)
            {
                for (int col = 0; col < cols; ++col)
                {
                    int idx = row * cols + col;

                    Block* block = new Block(":/images/block_white.png",
                                             colors[idx % colors.size()],
                                             tops[idx % tops.size()],
                                             lefts[idx % lefts.size()],
                                             rights[idx % rights.size()],
                                             ":/images/colors/shading_mask.png",
                                             ":/images/colors/light_mask",
                                             ":/images/edges/top_chosen.png",
                                             ":/images/edges/left_chosen.png",
                                             ":/images/edges/right_chosen.png");

                    block->setName(QString("block_%1").arg(idx));
                    block->setZValue(row + 1);

                    m_scene->addItem(block);

                    qreal pos_x = start_x + col * spacing_x;
                    qreal pos_y = start_y + row * spacing_y;

                    //TODO: Константа ?
                    const int cube_width = 100.0;

                    //block->setPos((- cube_width - x_offset) * col,
                    //              (cube_width + y_offset) * row );

                    //TODO: Тоже пока захардкожено image.w() image.h()
                    //qDebug() << block->boundingRect();
                    block->setPos(pos_x - 249 /2, pos_y - 249 /2);
                    //qDebug() << pos_x << " " << pos_y;

                }
            }
        }
        

        
    protected:
        void mousePressEvent(QMouseEvent *event) override
        {
            if (event->button() == Qt::RightButton)
            {
                QPointF scenePos = m_view->mapToScene(event->pos());
                QPointF viewPos = event->pos();
                Block* block = new Block(":/images/block_white.png",
                                          ":/images/colors/green_mask.png",
                                          ":/images/letters/w_top.png",
                                          ":/images/letters/w_left.png",
                                          ":/images/letters/w_right.png",
                                          ":/images/shading_mask.png",
                                          ":/images/light_mask.png");


                scenePos -= QPointF(249 / 2, 249 / 2);
                block->setName(QString("block_%1").arg(m_scene->items().size()));
                block->setZValue(m_scene->items().size());
                
                block->setPos(scenePos);
                m_scene->addItem(block);
                
            }
            if (event->button() == Qt::LeftButton)
            {
                QPointF scene_pos = m_view->mapToScene(event->pos());
                QGraphicsItem* clicked_item = m_scene->itemAt(scene_pos, m_view->transform());

                Block* clicked_block = dynamic_cast<Block*>(clicked_item);
                if(clicked_block)
                {
                    QPointF block_pos = clicked_block->mapFromScene(scene_pos);

                    // Определяем грань
                    Block::FACE clicked_face = clicked_block->get_face_at_point(block_pos);
                    //clicked_block->set_face_selected(clicked_face);
                    //clicked_block->toggle();
                    clicked_block->setPressed(true);
                    //qDebug() << blockPos << " " << clickedFace;
                    /* for (QGraphicsItem* item : m_scene->items()) {
                        Block* block = dynamic_cast<Block*>(item);
                        if (block) {
                            block->toggleState(Block::UNTOGGLED);
                            block->setPressed(false); // Устанавливаем состояние "не нажато" для всех блоков
                        }
                    }

                    clickedBlock->toggleState(Block::TOGGLED);
                    clickedBlock->setPressed(true); */
                }
            }   
            QWidget::mousePressEvent(event);
        }

        void mouseReleaseEvent(QMouseEvent *event) override
        {
            if (event->button() == Qt::LeftButton)
            {
                QPointF scene_pos = m_view->mapToScene(event->pos());
                QGraphicsItem* clicked_item = m_scene->itemAt(scene_pos, m_view->transform());
                Block* clicked_block = dynamic_cast<Block*>(clicked_item);

                if(clicked_block)
                {
                    clicked_block->toggle();
                    clicked_block->setPressed(false);
                }
            }
            QWidget::mouseReleaseEvent(event);
        }

    private:
        QGraphicsScene *m_scene;
        QGraphicsView *m_view;
};



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameWindow window;
    window.show();
    return app.exec();
}
