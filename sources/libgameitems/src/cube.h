#ifndef CUBE_H
#define CUBE_H
#include "types.h"
#include <array>
#include <map>

//Mb relevant to make a enum class and overlad ++


class Cube
{
    public:
        Cube(const std::array<char, FACE::SIZE>& text);
        const char& getSideText(FACE face) const;
        void rotate(const char axis);

    private:
        std::array<char, FACE::SIZE> m_face_value;


};

#endif