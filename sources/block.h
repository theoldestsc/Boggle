#include <QGraphicsItem>
#include <QPixmap>
#include <QPolygonF>
#include <array>
#include <cassert>

class Block : public QGraphicsItem
{
    public:
        enum STATE
        {
            TOGGLED,
            UNTOGGLED
        };

        //TODO: Он уже должен получать текстуры
        Block(const char* fname_block_base, const char* fname_color,
              const char* fname_ch_top, const char* fname_ch_left,
              const char* fname_ch_right,
              const char* fname_shading = "",
              const char* fname_texture_light = "",
              const char* selection_top = "",
              const char* selection_left = "",
              const char* selection_right = "") :
              Block(QString(fname_block_base), QString(fname_color),
                    QString(fname_ch_top), QString(fname_ch_left),
                    QString(fname_ch_right), QString(fname_shading),
                    QString(fname_texture_light),
                    QString(selection_top),
                    QString(selection_left),
                    QString(selection_right)){}

        Block(QString fname_block_base, QString fname_color,
              QString fname_ch_top, QString fname_ch_left,
              QString fname_ch_right, QString fname_shading = "",
              QString fname_texture_light = "",
              QString selection_top = "",
              QString selection_left = "",
              QString selection_right = "") :
              m_texture_block_base(fname_block_base),
              m_texture_block_color(fname_color),
              m_texture_ch_top(fname_ch_top),
              m_texture_ch_left(fname_ch_left),
              m_texture_ch_right(fname_ch_right),
              m_texture_shading(fname_shading),
              m_texture_light(fname_texture_light),
              m_selection_top(selection_top),
              m_selection_left(selection_left),
              m_selection_right(selection_right),
              m_is_pressed(false),
              m_shadow_force(0),
              m_face_states({UNTOGGLED, UNTOGGLED, UNTOGGLED}),
              m_block_checked_state(false)
        {
            assert(!m_texture_block_base.isNull());
        }


        void setName(QString name)
        {
            m_name = name;
        }

        void setPressed(bool is_pressed)
        {
            if (m_is_pressed != is_pressed)
            {
                m_is_pressed = is_pressed;
                update();
            }
        }
        QRectF boundingRect() const override
        {
            QRectF base_rect = m_texture_block_base.rect();
            return base_rect.united(m_texture_light.rect());
            //return base_rect;
        }

        QPainterPath shape() const override
        {
            QPainterPath path;
            QBitmap mask = m_texture_block_base.mask();
            QRegion region(mask);
            path.addRegion(region);
            return path;
        }

        enum FACE
        {
            UNKNOWN = -1,
            TOP,
            LEFT,
            RIGHT,
            SIZE
        };

        void toggle()
        {
            m_block_checked_state = !m_block_checked_state;
        }
        
        void set_face_selected(FACE face)
        {
            assert(face < m_face_states.size());
        
            m_face_states[face] = m_face_states[face] ? STATE::TOGGLED : STATE::UNTOGGLED;
        }

        void paint(QPainter* painter,
                  const QStyleOptionGraphicsItem* option,
                  QWidget* widget = nullptr) override
        {
            Q_UNUSED(option);
            Q_UNUSED(widget);

            painter->save();
            painter->setRenderHint(QPainter::SmoothPixmapTransform);

            if (m_is_pressed)
            {
                painter->translate(-5, 5);
            }

            painter->drawPixmap(0, 0, m_texture_block_base);
            painter->drawPixmap(0, 0, m_texture_ch_top);
            painter->drawPixmap(0, 0, m_texture_ch_left);
            painter->drawPixmap(0, 0, m_texture_ch_right);
            painter->drawPixmap(0, 0, m_texture_block_color);

            if(m_block_checked_state)
            {
                painter->drawPixmap(0,
                                    m_texture_block_base.height() - m_texture_light.height(),
                                    m_texture_light);
            }
            //if(m_face_states.at(FACE::TOP) == STATE::TOGGLED)
            //    painter->drawPixmap(0, 0, m_selection_top);
            //if(m_face_states.at(FACE::LEFT) == STATE::TOGGLED)
            //    painter->drawPixmap(0, 0, m_selection_left);
            //if(m_face_states.at(FACE::RIGHT) == STATE::TOGGLED)
            //    painter->drawPixmap(0, 0, m_selection_right);


            for(int i = 0; i < m_shadow_force; ++i)
                painter->drawPixmap(0, 0, m_texture_shading);

            painter->restore();
        }

        FACE get_face_at_point(const QPointF& point) const
        {
            QRectF rect = m_texture_block_base.rect();
            float width = rect.width();
            float height = rect.height();
            auto edge_size = static_cast<int>(m_texture_block_base.height() / (qSqrt(2.0) + 1.0));
            QPolygonF top_face_poly, right_face_poly, left_face_poly;
            //TODO: Проверить граничные координаты еще раз
            top_face_poly  << QPointF(width - edge_size, 0) << QPointF(width, 0)
                           << QPointF(width, edge_size) << QPointF(width - edge_size, edge_size);
            right_face_poly  << QPointF(width - edge_size, edge_size) << QPointF(width, edge_size)
                           << QPointF(edge_size, height) << QPointF(0, height);
            left_face_poly  << QPointF(0, height) << QPointF(0,height - edge_size)
                           << QPointF(width - edge_size, 0) << QPointF(width - edge_size, edge_size);

            if(top_face_poly.containsPoint(point, Qt::OddEvenFill))
                return TOP;
            else if(right_face_poly.containsPoint(point, Qt::OddEvenFill))
                return RIGHT;
            else if(left_face_poly.containsPoint(point, Qt::OddEvenFill))
                return LEFT;
            else
            {
                qDebug() <<  "UNKNOWN: " << point;
                return UNKNOWN;
            }
        }

    private:
        QMap<FACE, QChar> m_face_to_letter;
        std::array<STATE, FACE::SIZE> m_face_states;
        bool m_block_checked_state;

        QPixmap m_texture_block_base;
        QPixmap m_texture_block_color;
        QPixmap m_texture_ch_top, m_texture_ch_left, m_texture_ch_right;
        QPixmap m_texture_shading, m_texture_light,
                m_selection_top,
                m_selection_left,
                m_selection_right;

        unsigned int m_shadow_force;
        QString m_name;
        bool m_is_pressed;

};