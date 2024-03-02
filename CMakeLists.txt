cmake_minimum_required(VERSION 3.5)

project(NahidaNotes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES NahidaNotes_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        nahidanotes.cpp
        nahidanotes.h
        nahidanotes.ui
        ${TS_FILES}
)

set(SOURCES_3RD_PARTY
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/linenumberarea.h
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/markdownhighlighter.cpp
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/markdownhighlighter.h
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/qmarkdowntextedit.cpp
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/qmarkdowntextedit.h
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/qownlanguagedata.cpp
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/qownlanguagedata.h
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/qplaintexteditsearchwidget.cpp
    ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit/qplaintexteditsearchwidget.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NahidaNotes
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${SOURCES_3RD_PARTY}
    )

    # includes dep
    target_include_directories(
        ${PROJECT_NAME} SYSTEM
        PUBLIC ${PROJECT_SOURCE_DIR}/3rdParty/qmarkdowntextedit)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NahidaNotes APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(NahidaNotes SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NahidaNotes
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(NahidaNotes PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.NahidaNotes)
endif()
set_target_properties(NahidaNotes PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS NahidaNotes
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NahidaNotes)
endif()
