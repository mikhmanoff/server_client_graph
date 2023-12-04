cmake_minimum_required(VERSION 3.5)

project(server_graph VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найдите Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        server.cpp
        server.h
)

# Проверка версии Qt и создание цели
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(server_graph
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(server_graph SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(server_graph
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Линковка с библиотеками Qt
target_link_libraries(server_graph PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# Настройка свойств приложения
set_target_properties(server_graph PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка приложения
install(TARGETS server_graph
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Завершение сборки приложения (только для Qt 6)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(server_graph)
endif()
