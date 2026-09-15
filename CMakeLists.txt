cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Pomodoro-Widget" VERSION 1.0.0 LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)
pkg_check_modules(LAYER_SHELL REQUIRED IMPORTED_TARGET gtk-layer-shell-0)

set( SOURCES
    src/main.cpp
    src/Notifier.cpp
    src/PomodoroTimer.cpp
    src/WidgetWindow.cpp
)

set( HEADERS
    include/Notifier.h
    include/PomodoroTimer.h
    include/WidgetWindow.h
)

add_executable("Pomodoro-Widget" ${SOURCES} ${HEADERS})
include_directories(include)
target_link_libraries(Pomodoro-Widget PRIVATE
    PkgConfig::GTK3
    PkgConfig::LAYER_SHELL
)
