set(SRC ${SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/common.h

    ${CMAKE_CURRENT_SOURCE_DIR}/game_asset.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game_asset.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/game_font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game_font.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/game_texture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game_texture.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/game_renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game_renderer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/game_menu.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game_menu.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/game_object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game_object.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/player.h
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/game_state_vars.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game_state_vars.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/game.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
    PARENT_SCOPE
)