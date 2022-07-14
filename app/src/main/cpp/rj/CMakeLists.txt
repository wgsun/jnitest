
# 指定CMake的最低版本信息，不加入会收到警告
cmake_minimum_required(VERSION 3.10.2)

# 显示执行构建过程中详细的信息(比如为了得到更详细的出错信息)
set(CMAKE_VERBOSE_MAKEFILE on)

# so库的头文件路径 (PROJECT_SOURCE_DIR 即当前CMakeLists.txt所在目录)
# include_directories(${PROJECT_SOURCE_DIR}/src/main/cpp/rj)

# 添加库
add_library(
        # Specifies the target library
        RJDVA
        # Sets the library as a shared library
        SHARED
        # Sets the library as a imported library
        IMPORTED
)
set_target_properties(
        # Specifies the target library
        RJDVA
        # Specifies the parameter you want to define
        PROPERTIES IMPORTED_LOCATION
        # Provides the path to the library you want to import.
        # Must be Absolute Path, relative path is Not Support!
        ${PROJECT_SOURCE_DIR}/rj/${ANDROID_ABI}/libRJDVA.so
)

# 添加源文件
add_library(
        # Sets the name of the library.(编译后生成的so名字)
        native-rj
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        native-rj.cpp
)

find_library(
        # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries(
        # Specifies the target library.
        native-rj
        RJDVA
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )



