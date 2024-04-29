
add_subdirectory(collections)
add_subdirectory(game)

set(SRC_FILES 
    ${COLLECTIONS_SRC}
    ${GAME_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/asteroids.cpp 

    PARENT_SCOPE
)