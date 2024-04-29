add_subdirectory(collections)
add_subdirectory(game)

set(SRC 
    ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/asteroids.cpp 
    PARENT_SCOPE
)