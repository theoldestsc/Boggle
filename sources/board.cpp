#include "board.h"
#include <ctime>
#include <array>
#include <cassert>
#include <iostream>

//Набор кубиков 6x6:

#define N_CUBE_EDGES 6
#define N_CUBES6x6 36

constexpr auto CUBES = std::to_array<std::array<char, N_CUBE_EDGES>>({
                                            {'A','A','A','F','R','S'},
                                            {'A','E','A','N','G','N'},
                                            {'A','A','S','E','C','M'},
                                            {'A','A','F','A','R','S'},
                                            {'A','G','N','E','E','E'},
                                            {'A','E','O','I','U','U'},
                                            {'A','B','B','J','O','O'},
                                            {'B','D','E','I','S','X'},
                                            {'D','D','O','N','T','U'},
                                            {'E','E','E','H','N','W'},
                                            {'E','E','H','I','T','T'},
                                            {'E','F','F','K','P','S'},
                                            {'E','I','I','L','S','T'},
                                            {'E','L','R','T','T','Y'},
                                            {'E','I','O','S','S','T'},
                                            {'F','S','U','I','P','R'},
                                            {'G','H','G','R','N','O'},
                                            {'H','H','L','R','D','O'},
                                            {'I','M','N','N','G','E'},
                                            {'I','F','G','R','E','V'},
                                            {'L','D','R','D','H','O'},
                                            {'N','O','N','N','E','E'},
                                            {'O','U','U','E','M','O'},
                                            {'R','T','T','T','L','Y'},
                                            {'S','A','C','O','R','T'},
                                            {'S','E','L','R','U','T'},
                                            {'U','T','O','I','E','S'},
                                            {'W','N','O','T','W','T'},
                                            {'A','E','I','T','M','O'},
                                            {'C','O','U','E','G','I'},
                                            {'D','N','D','H','I','S'},
                                            {'P','A','L','R','I','S'},
                                            {'R','U','N','D','D','S'},
                                            {'W','I','I','I','R','S'},
                                            {'Y','L','E','G','U','B'},
                                            {'Z','V','U','Q','U','N'}
                                        });



Board::Board() : m_map(CUBES[0].size(), std::vector<char>(CUBES[0].size(), ' '))
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
