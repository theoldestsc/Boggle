#include "board.h"
#include <ctime>
#include <array>
#include <cassert>
#include <iostream>

//Набор кубиков 6x6:

#define N_CUBE_EDGES 6
#define N_ROW_SIZE 5

/*
TODO: Класс BoadrdGenerator.
А Board сам по себе должен принимать готовое поле
*/

/*
    TODO: m_map должен быть набором уже объектов класса CUBE,
    который можно повернуть и сменить у него current_top()
*/
constexpr auto CUBES = std::to_array<std::array<char, N_CUBE_EDGES>>({
                                            {'A', 'A', 'A', 'F', 'R', 'S'},
                                            {'A', 'A', 'E', 'E', 'E', 'E'},
                                            {'A', 'A', 'F', 'I', 'R', 'S'},
                                            {'A', 'D', 'E', 'N', 'N', 'N'},
                                            {'A', 'E', 'E', 'E', 'E', 'M'},

                                            {'A', 'E', 'E', 'G', 'M', 'U'},
                                            {'A', 'E', 'G', 'M', 'N', 'N'},
                                            {'A', 'F', 'I', 'R', 'S', 'Y'},
                                            {'B', 'J', 'K', 'Q', 'X', 'Z'},
                                            {'C', 'C', 'E', 'N', 'S', 'T'},

                                            {'C', 'E', 'I', 'I', 'L', 'T'},
                                            {'C', 'E', 'I', 'L', 'P', 'T'},
                                            {'C', 'E', 'I', 'P', 'S', 'T'},
                                            {'D', 'D', 'H', 'N', 'O', 'T'},
                                            {'D', 'H', 'H', 'L', 'O', 'R'},

                                            {'D', 'H', 'L', 'N', 'O', 'R'},
                                            {'D', 'H', 'L', 'N', 'O', 'R'},
                                            {'E', 'I', 'I', 'I', 'T', 'T'},
                                            {'E', 'M', 'O', 'T', 'T', 'T'},
                                            {'E', 'N', 'S', 'S', 'S', 'U'},

                                            {'F', 'I', 'P', 'R', 'S', 'Y'},
                                            {'G', 'O', 'R', 'R', 'V', 'W'},
                                            {'I', 'P', 'R', 'R', 'R', 'Y'},
                                            {'N', 'O', 'O', 'T', 'U', 'W'},
                                            {'O', 'O', 'O', 'T', 'T', 'U'}
                                        });



Board::Board() : m_map(N_ROW_SIZE, std::vector<char>(N_ROW_SIZE, ' '))
{

}

//TODO: Проверить какое будет исключение и будет ли если зайти за пределы массива
void Board::set_cell_value(size_t row,
                           size_t column,
                           const char& ch)
{
    assert(!m_map.empty());
    assert(row < m_map.size());
    assert(column < m_map.at(0).size());
    m_map[row][column] = ch;
}

//TODO: generate cubes from words
void Board::generate_map()
{
    // Инициализируем генератор текущим временем
    std::srand(std::time(0));

    for(size_t row = 0; row < m_map.size(); ++row)
    {
        for(size_t column = 0; column < m_map.at(row).size(); ++column)
        {
            // Генерируем случайный индекс
            auto& cube = CUBES[row + column];
            int random_index = std::rand() % 6;
            char random_element = cube[random_index];
            m_map[row][column] = random_element;
        }
    }

}


const std::vector<std::vector<char>>& Board::get_map() const
{
    return m_map;
}
