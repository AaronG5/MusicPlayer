cmake_minimum_required(VERSION 3.16)

project(MusicPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appMusicPlayer
    src/main.cpp
)

qt_add_qml_module(appMusicPlayer
    URI MusicPlayer
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        SOURCES src/player.h src/player.cpp
        RESOURCES LICENSE
        RESOURCES README.md
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMusicPlayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMusicPlayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMusicPlayer
    PRIVATE
        Qt6::Quick
        ${SDL2_LIBRARY}
)
target_link_libraries(appMusicPlayer PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appMusicPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


find_path(SDL2_INCLUDE_DIR SDL.h
    PATH_SUFFIXES SDL2
    HINTS /opt/homebrew/include
)

find_library(SDL2_LIBRARY SDL2
    HINTS /opt/homebrew/lib
)

if(NOT SDL2_INCLUDE_DIR OR NOT SDL2_LIBRARY)
        message(FATAL_ERROR "SDL2 not found!")
    endif()

    include_directories(${SDL2_INCLUDE_DIR})
