#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include "loader.h"

bool Loader::init()
{
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

    auto check_files_exist = [](const QStringList& paths) -> bool
    {
        for (int i = 0; i < paths.size(); ++i)
        {
            if (!QFile::exists(paths[i]))
            {
                qCritical() << "Error: Missing texture for letter"
                           << QChar('a' + i) << "at path:" << paths[i];
                return false;
            }
        }
        return true;
    };

    if (!check_files_exist(tops)) return false;
    if (!check_files_exist(lefts)) return false;
    if (!check_files_exist(rights)) return false;

    //TODO:side_idx должен быть наверное все-таки нашим enum Face
    auto load_textures = [&](const QStringList& paths,
                             size_t side_idx) -> bool 
    {
        for (int i = 0; i < paths.size(); ++i)
        {
            QPixmap pixmap(paths[i]);
            if (pixmap.isNull())
            {
                qCritical() << "Error: Failed to load texture:" << paths[i];
                return false;
            }
            m_letters_pixmaps[QChar('a' + i)][side_idx] = pixmap;
        }
        return true;
    };

    if (!load_textures(tops, 0)) return false;
    if (!load_textures(lefts, 1)) return false;
    if (!load_textures(rights, 2)) return false;


    for (const QString &path : colors)
    {
        QPixmap pixmap(path);
        //TODO: Check it
        if (!pixmap.isNull())
        {
            QString key = QFileInfo(path).baseName().replace("_mask", "");
            m_colors.insert(key, pixmap);
        }
        else
            return false;
    }

    return true;
}

const std::array<QPixmap, 3>& Loader::get_letter_textures(QChar key) const
{
    auto it = m_letters_pixmaps.constFind(key);
    if (it == m_letters_pixmaps.cend())
        throw std::out_of_range("Key not found in m_letters_pixmaps");
    return it.value();
}