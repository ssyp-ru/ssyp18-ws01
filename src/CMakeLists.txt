
set(EXECUTABLE  main.cpp
                map.cpp
                event.cpp
                gamelogic/gamelogic.cpp
                gameobject.cpp
                networkmanager.cpp
                player.cpp
                main_menu.cpp
                )

add_compile_options(-std=c++17)
add_compile_options(-g)
add_compile_options(-Wall)
add_compile_options(-Wpedantic)

include_directories($ENV{REAL_ENGINE_DIR}/include)
include_directories($ENV{REAL_ENGINE_DIR}/ext)
link_directories($ENV{REAL_ENGINE_DIR}/lib)

add_executable(real_game ${EXECUTABLE})
target_link_libraries(real_game real_engine)
