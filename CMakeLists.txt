cmake_minimum_required(VERSION 2.8)

project(game)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-switch") 
endif ( CMAKE_COMPILER_IS_GNUCC )

include_directories(ext)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

set(FILE_TO_COPY
    config/resource.xml
    config/config.xml
    data/new_map.tmx
    data/map.tmx
    data/map.png
    data/mage_front_1.png
    data/mage_front_2.png
    data/mage_front_3.png
    data/mage_front_4.png
    data/mage_front_9.png
    data/mage_front_10.png
    data/mage_front_11.png
    data/d_mage_front_1.png
    data/d_mage_front_2.png
    data/d_mage_front_3.png
    data/d_mage_front_4.png
    data/d_mage_front_9.png
    data/d_mage_front_10.png
    data/d_mage_front_11.png
    data/Br_creep_left_1.png
    data/Br_creep_left_2.png
    data/Br_creep_left_3.png
    data/Br_creep_right_1.png
    data/Br_creep_right_2.png
    data/Br_creep_right_3.png
    data/D_creep_left_1.png
    data/D_creep_left_2.png
    data/D_creep_left_3.png
    data/D_creep_right_1.png
    data/D_creep_right_2.png
    data/D_creep_right_3.png
    data/change.png
    data/connect.png
    data/create.png
    data/empty.png
    data/exit.png
    data/join.png
    data/menu.png
    data/players.png
    data/dark.png
    data/bright.png
    data/go.png
    data/screen_panel.png
)


foreach( file ${FILE_TO_COPY} )
get_filename_component(filename ${file} NAME)
    set(source_file ${PROJECT_SOURCE_DIR}/${file})
    set(dest_file ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${filename})

    if(${source_file} IS_NEWER_THAN ${dest_file})
        configure_file(${source_file} ${dest_file} COPYONLY)
        message(" '${dest_file}' ... copied.")
    endif()
endforeach(file)

add_subdirectory(src)
