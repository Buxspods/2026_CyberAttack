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
        AI/EnemyTypes.h
        AI/Enemy.h
        AI/Enemy.c
        AI.h)
target_include_directories(2026_CyberAttack PRIVATE ${raylib_include_DIRS})

target_link_libraries(2026_CyberAttack PRIVATE ${LIB1})
