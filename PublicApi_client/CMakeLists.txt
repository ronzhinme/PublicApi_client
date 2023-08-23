cmake_minimum_required(VERSION 3.16)

project(PublicApi_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/category)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/web_request)

qt_add_executable(appPublicApi_client
    main.cpp
)

qt_add_qml_module(appPublicApi_client
    URI PublicApi_client
    VERSION 1.0
    QML_FILES
        main.qml
        Navigator.qml
)

set_target_properties(appPublicApi_client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPublicApi_client
    PRIVATE Qt6::Quick
    category_model
    web_request
)

install(TARGETS appPublicApi_client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
