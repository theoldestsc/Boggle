#include <QtTest>
#include "../src/board.h"
#include "../src/cube.h"
#include <iostream>
//TODO: Записать весь процесс создания

//TODO: Переместить в test_helpers
//std::ostream& operator<<(std::ostream&, const Board&);

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<Cube>>& map)
{
    for(size_t row = 0; row < map.size(); ++row)
    {
        for(size_t column = 0; column < map.at(row).size(); ++column)
            os << map.at(row).at(column).getSideText(FACE::TOP) << " ";
        os << std::endl;
    }

    return os;
}


class BoardTest : public QObject
{
        Q_OBJECT
        /* [NOTE] Конструктор вызывается на каждый тест */
    //private:
    private slots:
        void initTestCase()
        {
            /* [NOTE] Один раз для всех тестов */
        }

        //void cleanupTestCase()
        //{
        //    return;
        //    /* [NOTE] Один раз после всех тестов */
        //}

        void mapGenerationTest()
        {
            auto board = Board();

            board.generate_map();

            const auto& map = board.get_map();

            for(size_t row = 0; row < map.size(); ++row)
            {
                const auto row_size = map.at(row).size();
                QVERIFY2(map.size() == row_size, "Map isn't quad");
            }

            //board.set_cell_value(0, 0, 'A');

            std::cout << map << std::endl;
            std::cout << std::endl;
            //QVERIFY(map.at(0).at(0) == 'A');
            //std::cout << map << std::endl;
            auto cube = Cube({'A', 'B', 'C', 'D', 'E', 'F'});
            //ПО икс верный поворот, оставить как тест
            //cube.rotate('x');
            //ASSERTION check exception index out of range
            //cube.setTextToSide(FACE::TOP, '+');
            cube.setTextToSide(FACE::TOP, 'D');
        
            std::cout << " TOP: " << cube.getSideText(FACE::TOP)
                      << " BOTTOM: " << cube.getSideText(FACE::BOTTOM)
                      << " LEFT: " << cube.getSideText(FACE::LEFT)
                      << " RIGHT: " << cube.getSideText(FACE::RIGHT)
                      << " FRONT: " << cube.getSideText(FACE::FRONT)
                      << " BACK: " << cube.getSideText(FACE::BACK) << std::endl;

        }
    };

QTEST_MAIN(BoardTest)
#include "board_test.moc"