set(BUILD_TARGET program)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES ${SOURCES}
    main.cpp
    maingui.h
    maingui.cpp
    opengl_widget.h
    opengl_widget.cpp)

add_executable(${BUILD_TARGET} ${SOURCES})
qt5_use_modules(${BUILD_TARGET} Widgets OpenGL)
target_link_libraries(${BUILD_TARGET} ${OPENGL_LIBRARIES})

# ------------------------------------------------------------------------------
# Enable degugging and profiling
# ------------------------------------------------------------------------------
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
  set_property(TARGET ${libname} APPEND PROPERTY LINK_FLAGS "/DEBUG /PROFILE")
endif()

# ------------------------------------------------------------------------------
# Copy Qt DLLs
# ------------------------------------------------------------------------------
set(QT_LIB_LIST Qt5Widgets
                Qt5Widgetsd
                Qt5Core
                Qt5Cored
                Qt5Gui
                Qt5Guid
                Qt5Xml
                Qt5Xmld
                Qt5OpenGL
                Qt5OpenGLd
                Qt5Test
                Qt5Testd
                icuin54
                icuuc54
                icudt54)

# ------------------------------------------------------------------------------
# Copy Qt5 DLLs
# ------------------------------------------------------------------------------
if (WIN32)
  foreach (QT_LIB ${QT_LIB_LIST})
    add_custom_command(TARGET ${BUILD_TARGET} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       ARGS ${CMAKE_PREFIX_PATH}/bin/${QT_LIB}.dll
                            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  endforeach()
endif(WIN32)
