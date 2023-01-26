#set(OE_QMAKE_PATH_EXTERNAL_HOST_BINS /usr/bin/qt5)

find_package(Qt6 COMPONENTS Core Network Concurrent Qml Quick QuickControls2 REQUIRED)

include_directories(${Qt6Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt6Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt6Quick_DEFINITIONS}})

set(SYSTEMD_UNIT_DIR "/lib/systemd/system/")
set(CMAKE_CXX_STANDARD 11)
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
qt6_add_resources(QT_RESOURCES ../gui/qml.qrc)

# create the executable file
add_executable(iLaundry_hmi ${sources} ${qm_files} ${QT_RESOURCES})

IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    target_link_libraries(iLaundry_hmi Qt6::Core Qt6::Widgets Qt6::Concurrent Qt6::Qml Qt6::Quick Qt6::QuickControls2  -lpthread)
ELSE ()
    target_link_libraries(iLaundry_hmi Qt6::Core Qt6::Concurrent Qt6::Qml Qt6::Quick Qt6::QuickControls2 -lcrypt -lrt -lpthread -lncurses)
ENDIF()

install(TARGETS iLaundry_hmi
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES ../service/iLaundry_hmi.service DESTINATION ${SYSTEMD_UNIT_DIR})


if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(iLaundry)
    qt_finalize_executable(iLaundry)
endif()

#INSTALL(DIRECTORY ../share/wallbox/gif DESTINATION share/wallbox)
#INSTALL(DIRECTORY ../share/wallbox/image DESTINATION share/wallbox)
#INSTALL(FILES ${qm_files} DESTINATION share/wallbox/lang)
#INSTALL(FILES ../service/copper_hmi.service DESTINATION ${SYSTEMD_UNIT_DIR})
#INSTALL(FILES ../hardware/cfg.json DESTINATION /home/root/.wallbox)
#INSTALL(FILES ../share/wallbox/image/black.png DESTINATION /home/root/.wallbox)
