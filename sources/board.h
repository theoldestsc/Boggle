
#include <vector>

//TODO: На боковых можно менять буквы
class Board
{

    public:
    //TODO: Устанавливать другой текст
        Board();
        void generate_map();

        /* Getters */
        const std::vector<std::vector<char>>& get_map() const;
        void set_cell_value(size_t row, size_t column, const char& ch);

    private:
        std::vector<std::vector<char>> m_map;

};

