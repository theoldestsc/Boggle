#include <QtTest>
#include "../src/loader.h"


class LoaderTest : public QObject
{
        Q_OBJECT
        /* [NOTE] Конструктор вызывается на каждый тест */
    private:
        Loader m_loader; 
    private slots:
        //void initTestCase();      // вызывается один раз перед всеми тестами
        //void cleanupTestCase();   // вызывается один раз после всех тестов
        //void init();              // вызывается перед каждым тестом
        //void cleanup();           // вызывается после каждого теста

        void initTestCase()
        {
            /* [NOTE] Один раз для всех тестов */
            m_loader.init();
        }

        void cleanupTestCase()
        {
            return;
            /* [NOTE] Один раз после всех тестов */
        }

        void testInitialization()
        {
            std::array<QPixmap, 3> textures;
            textures = m_loader.get_letter_textures('a');
            qDebug() << !textures.empty();

            textures = m_loader.get_letter_textures('/');
            qDebug() << !textures.empty();
            //TODO:QVERIFY тут
            //return res;
        }

    };

QTEST_MAIN(LoaderTest)
#include "loader_test.moc"