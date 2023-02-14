#set(OE_QMAKE_PATH_EXTERNAL_HOST_BINS /usr/bin/qt5)

find_package(Qt5 COMPONENTS Core Network Concurrent Qml Quick QuickControls2 REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

set(SYSTEMD_UNIT_DIR "/lib/systemd/system/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# add the necessary include directories
include_directories(. ../gui )

# application source files
file(GLOB sources *.cpp *.c ${qm_files})

# application header files
file(GLOB headers *.h)

# build resources
qt5_add_resources(QT_RESOURCES ../gui/qml.qrc)

# create the executable file
add_executable(eLaundry_hmi ${sources} ${qm_files} ${QT_RESOURCES})

IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    target_link_libraries(eLaundry_hmi Qt5::Core Qt5::Widgets Qt5::Concurrent Qt5::Qml Qt5::Quick Qt5::QuickControls2  -lpthread)
ELSE ()
    target_link_libraries(eLaundry_hmi Qt5::Core Qt5::Concurrent Qt5::Qml Qt5::Quick Qt5::QuickControls2 -lcrypt -lrt -lpthread -lncurses)
ENDIF()

install(TARGETS eLaundry_hmi
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES ../service/eLaundry_hmi.service DESTINATION ${SYSTEMD_UNIT_DIR})


if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(eLaundry)
    qt_finalize_executable(eLaundry)
endif()

#INSTALL(DIRECTORY ../share/wallbox/gif DESTINATION share/wallbox)
#INSTALL(DIRECTORY ../share/wallbox/image DESTINATION share/wallbox)
#INSTALL(FILES ${qm_files} DESTINATION share/wallbox/lang)
#INSTALL(FILES ../service/copper_hmi.service DESTINATION ${SYSTEMD_UNIT_DIR})
#INSTALL(FILES ../hardware/cfg.json DESTINATION /home/root/.wallbox)
#INSTALL(FILES ../share/wallbox/image/black.png DESTINATION /home/root/.wallbox)
