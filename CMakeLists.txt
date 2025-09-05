cmake_minimum_required(VERSION 3.16)
project(BoggleGame VERSION 1.0 LANGUAGES CXX)

# Новый стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Находим системный Qt 6.8+
# CMake автоматически ищет в /usr/lib/x86_64-linux-gnu/cmake/Qt6
find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets Test)

# Исходные файлы
set(SOURCES
    main.cpp
    sources/block.h
)

# Собираю как статическую библиотеку
#-----------------------------------------------------------
add_library(loader STATIC sources/libloader/src/loader.h
                          sources/libloader/src/loader.cpp)
target_link_libraries(loader PRIVATE Qt6::Core Qt6::Gui)
#-----------------------------------------------------------

# Собираю как статическую библиотеку
#-----------------------------------------------------------
add_library(gameitems STATIC sources/libgameitems/src/board.h
                             sources/libgameitems/src/board.cpp
                             sources/libgameitems/src/cube.h
                             sources/libgameitems/src/cube.cpp)
target_link_libraries(gameitems PRIVATE Qt6::Core Qt6::Gui)
#-----------------------------------------------------------

# Ресурсы
qt_add_resources(RESOURCES "resources.qrc")

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})

# Подключение Qt модулей
target_link_libraries(${PROJECT_NAME} PRIVATE
                      Qt6::Core
                      Qt6::Gui
                      Qt6::Widgets
                      loader
)


enable_testing()

add_executable(loader_test
               sources/libloader/tests/loader_test.cpp
               ${RESOURCES})

set_target_properties(loader_test PROPERTIES
                      AUTOMOC ON
                      AUTOUIC ON
                      AUTORCC ON)

target_include_directories(loader_test PRIVATE "${SOURCES_ROOT}")

target_link_libraries(loader_test
                      loader
                      Qt6::Widgets Qt6::Test
)


add_test(NAME LoaderTests COMMAND loader_test)


add_executable(board_test
               sources/libgameitems/tests/board_test.cpp
               ${RESOURCES})

set_target_properties(board_test PROPERTIES
                     AUTOMOC ON
                     AUTOUIC ON
                     AUTORCC ON)

target_link_libraries(board_test
                      gameitems
                      Qt6::Test)

add_test(NAME LetterMapTests COMMAND board_test)
