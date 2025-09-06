#include "cube.h"
#include <cassert>
#include <iostream>
#include <algorithm>

Cube::Cube(const std::array<char, FACE::SIZE>& text)
{
    m_face_value[FACE::TOP]    = text[0];
    m_face_value[FACE::BOTTOM] = text[1];
    m_face_value[FACE::LEFT]   = text[2];
    m_face_value[FACE::RIGHT]  = text[3];
    m_face_value[FACE::FRONT]  = text[4];
    m_face_value[FACE::BACK]   = text[5];
}

const char& Cube::getSideText(FACE face) const
{
    assert(static_cast<size_t>(face) < m_face_value.size());
    return m_face_value.at(face);
}

void Cube::setTextToSide(FACE face, char text)
{
    assert(static_cast<size_t>(face) < m_face_value.size());

    const auto it = std::find(m_face_value.begin(), m_face_value.end(), text);

    assert(("Cube dosn't has this letter: ", it != m_face_value.end()));

    const size_t text_face = std::distance(m_face_value.begin(), it);

    auto const current = m_face_value.at(face);
    m_face_value[text_face] = current;
    m_face_value[face] = text;
}

void Cube::rotate(const char axis)
{
    if(axis == 'x')
    {
        std::array<char, FACE::SIZE> new_face_value = m_face_value;
        new_face_value[FACE::BACK] = m_face_value[FACE::TOP];
        new_face_value[FACE::BOTTOM] = m_face_value[FACE::BACK];
        new_face_value[FACE::FRONT] = m_face_value[FACE::BOTTOM];
        new_face_value[FACE::TOP] = m_face_value[FACE::FRONT];
        m_face_value = new_face_value;
    }
    else if(axis == 'y')
    {

    }
}