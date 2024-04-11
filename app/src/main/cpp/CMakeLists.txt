# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.
set(PROJECT_NAME "rendererddream")

project(PROJECT_NAME)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(OPENGL_LIB GLESv2)
set(GL_dir "glInterface")
set(GLM "deps/glm-master/glm")

set(ASSET_DIR ${CMAKE_SOURCE_DIR}/../assets)
set(GAME_DIR ${CMAKE_SOURCE_DIR}/game)
set(deps_DIR ${CMAKE_SOURCE_DIR}/deps)

add_library(lib_png SHARED IMPORTED)

set_target_properties(lib_png PROPERTIES IMPORTED_LOCATION
        ${deps_DIR}/lib/${ANDROID_ABI}/libpng16.so)

add_library(rendererddream SHARED
        android/JNIWrapper.cpp
        glInterface/image.c
        glInterface/image.h
        android/androidLoader.c
        android/androidLoader.h
        ${CMAKE_SOURCE_DIR}/core/renderer.cpp
        ${CMAKE_SOURCE_DIR}/core/renderer.h
        ${CMAKE_SOURCE_DIR}/core/gCore.cpp
        ${CMAKE_SOURCE_DIR}/core/gCore.h
        ${CMAKE_SOURCE_DIR}/core/Entity.cpp
        ${CMAKE_SOURCE_DIR}/core/Entity.h
        ${CMAKE_SOURCE_DIR}/core/TileMap.cpp
        ${CMAKE_SOURCE_DIR}/core/TileMap.h
        ${CMAKE_SOURCE_DIR}/core/utils/TextureUtil.h
        ${CMAKE_SOURCE_DIR}/core/utils/TextureUtil.c
        ${CMAKE_SOURCE_DIR}/core/utils/entityHelper.h
        ${CMAKE_SOURCE_DIR}/core/utils/entityHelper.cpp
        ${CMAKE_SOURCE_DIR}/core/utils/Common.h
        ${CMAKE_SOURCE_DIR}/core/utils/Common.c
        ${CMAKE_SOURCE_DIR}/core/utils/Loader.h
        ${CMAKE_SOURCE_DIR}/core/utils/Loader.c
        ${CMAKE_SOURCE_DIR}/core/GDGEngine.h
        ${CMAKE_SOURCE_DIR}/core/utils/Anim.h
        ${CMAKE_SOURCE_DIR}/core/utils/Anim.cpp
        ${GL_dir}/textureLoader.c
        ${GL_dir}/textureLoader.h
        ${GL_dir}/glRend.c
        ${GL_dir}/glRend.h
        ${GL_dir}/shader.c
        ${GL_dir}/shader.h
        ${GAME_DIR}/gdgArcade.h
        ${GAME_DIR}/gdgArcade.cpp
        ${GAME_DIR}/EntityContainer.h
        ${GAME_DIR}/EntityContainer.cpp
        ${GAME_DIR}/CurrentMap.h
        ${GAME_DIR}/CurrentMap.cpp
        )


file(GLOB ${GLM}/*.hpp)

target_link_libraries(rendererddream
        ${OPENGL_LIB}
        android
        lib_png
        EGL
        log
        m
)

