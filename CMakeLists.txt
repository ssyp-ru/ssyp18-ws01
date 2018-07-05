cmake_minimum_required(VERSION 2.8)

project(game)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-switch") 
endif ( CMAKE_COMPILER_IS_GNUCC )


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

set(FILE_TO_COPY
    map.tmx
)

foreach( file ${FILE_TO_COPY} )
    configure_file(data/${file} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${file} COPYONLY)
endforeach(file)

add_subdirectory(src)
