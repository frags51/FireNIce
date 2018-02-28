cmake_minimum_required(VERSION 3.8)
project(FireNIce)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
set(SOURCE_FILES
        main.cpp
        include/GameState.h src/GameState.cpp
        include/Splash.h src/Splash.cpp
        include/MainMenu.h src/MainMenu.cpp
        src/Server.cpp include/Server.h
        src/Player.cpp include/Player.h 
        src/Animation.cpp include/Animation.h
        src/VisibleGameObject.cpp include/VisibleGameObject.h 
        src/Client.cpp include/Client.h include/ObjMan.h src/ObjMan.cpp src/Collision.cpp include/Collision.h src/Platform.cpp include/Platform.h)

add_executable(FireNIce ${SOURCE_FILES})

target_link_libraries(FireNIce
        sfml-window
        sfml-system
        sfml-graphics
        sfml-audio
        sfml-network
        pthread)

