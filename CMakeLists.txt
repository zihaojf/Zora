cmake_minimum_required(VERSION 3.16)

project(Zora VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt5_DIR "D:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")
set(Qt5MultimediaWidgets_DIR **/Qt5.9.8/5.9.8/clang_64/lib/cmake/Qt5MultimediaWidgets)#包的位置

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt5 COMPONENTS Widgets Core Sql REQUIRED)
find_package(Qt5 COMPONENTS Multimedia REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        zora.cpp
        zora.h
        zora.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Zora
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Zora APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Zora SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Zora
            ${PROJECT_SOURCES}
            image.qrc
            music.h music.cpp music.ui
            account.h account.cpp account.ui
            schoolclass.h schoolclass.cpp schoolclass.ui
            work.h work.cpp work.ui
            password.h password.cpp password.ui
            life.h life.cpp life.ui
            account_addpage.h account_addpage.cpp account_addpage.ui
            account_yearchart.h account_yearchart.cpp account_yearchart.ui
            account_monthchart.h account_monthchart.cpp account_monthchart.ui
            passwordlogin.h passwordlogin.cpp passwordlogin.ui
            passwordaddpage.h passwordaddpage.cpp passwordaddpage.ui
            passwordsettings.h passwordsettings.cpp passwordsettings.ui
            worksetting.h worksetting.cpp worksetting.ui










        )
    endif()
endif()

target_link_libraries(Zora Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Zora Qt5::Widgets Qt5::Sql)
target_link_libraries(${PROJECT_NAME} Qt5::Multimedia)#链接到库

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Zora)
endif()
set_target_properties(Zora PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Zora
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Zora)
endif()












