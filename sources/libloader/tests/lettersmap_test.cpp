#include <QtTest>
#include "../../lettersmap.h"


class MapTest : public QObject
{
        Q_OBJECT
        /* [NOTE] Конструктор вызывается на каждый тест */
    //private:
    private slots:
        void initTestCase()
        {
            /* [NOTE] Один раз для всех тестов */
            //LettersMap m_map;
            //m_map->get();
        }

        void cleanupTestCase()
        {
            return;
            /* [NOTE] Один раз после всех тестов */
        }

        void testInitialization()
        {
        }

    };

QTEST_MAIN(MapTest)
#include "lettersmap_test.moc"