#ifndef LIBLOADER_LOADER_H
#define LIBLOADER_LOADER_H

#include <QPixmap>
#include <QMap>
#include <QString>
#include <array>



class Loader
{
    public:
        Loader() = default;
        bool init();
        const std::array<QPixmap, 3>& get_letter_textures(QChar key) const;
    private:
        QMap<QChar, std::array<QPixmap, 3>> m_letters_pixmaps;
        QMap<QString, QPixmap> m_colors;
};
#endif