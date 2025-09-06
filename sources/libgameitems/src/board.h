#ifndef BOARD_H
#define BOARD_H
#include "cube.h"
#include <vector>
//TODO: На боковых можно менять буквы
class Board
{

    public:
    //TODO: Устанавливать другой текст
        Board();
        void generate_map();

        /* Getters */
        const std::vector<std::vector<Cube>>& get_map() const;
        /* Setters */
        void set_cell_value(size_t row, size_t column, const Cube& cube);

    private:
        std::vector<std::vector<Cube>> m_map;

};
#endif