cmake_minimum_required(VERSION 4.2)
project(2026_CyberAttack C)

set(CMAKE_C_STANDARD 11)
include(FetchContent)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)
    FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB1 raylib)
find_package(${LIB1} QUIET)
if(NOT ${LIB1}_FOUND)
    include_dependency(${LIB1} http://github.com/raysan5/raylib.git 6.0)
endif ()
add_executable(2026_CyberAttack main.c
        mech/Player.h
        mech/Player.c
        mech/Projectile.h
        mech/Projectile.c
        mechanics.h
        AI/Enemy.h
        AI/Enemy.c
        AI.h
        GUI.h
        GUI/glavniMeni.h
        GUI/pauseMeni.h
        GUI/glavniMeni.c
        GUI/pauseMeni.c
        mech/GameState.h
        mech/GameState.c
        mech/Collisions.h
        mech/Collisions.c
        mech/EntityTypes.h
        mech/Entity.h
        GUI/assets.h
        GUI/highest-score.h
        GUI/stats.h
        GUI/stats.c
        GUI/highest-score.c
        GUI/planeGUI.c
        GUI/planeGUI.h
        DebugTools.h
        mech/Wave.h
        mech/Wave.c
        mech/Powerup.h
        mech/Powerup.c
        AI/EnemyActions.h
        AI/EnemyActions.c
        mech/EnemyWithTime.h
        mech/Level.h
        mech/Level.c
        GUI/endScreen.c
        GUI/endScreen.h
)
target_include_directories(2026_CyberAttack PRIVATE ${raylib_include_DIRS})

target_link_libraries(2026_CyberAttack PRIVATE ${LIB1})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/documents"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/documents")
