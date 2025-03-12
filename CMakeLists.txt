cmake_minimum_required(VERSION 3.22)
project(diden_android_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Android ABI를 64bit로 강제 설정
set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)

# ✅ Android 설정 (빌드 아키텍처 지정)
    set(CMAKE_ANDROID_ARCH_ABI "arm64-v8a")
    set(CMAKE_ANDROID_NDK $ENV{ANDROID_NDK_HOME})
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_ANDROID_NDK}/build/cmake/android.toolchain.cmake")
    set(ANDROID_PLATFORM android-29)
    set(Protobuf_DIR "/home/khb/Desktop/utility_ws/grpc_and/install-android/lib/cmake/protobuf")
    set(gRPC_DIR "/home/khb/Desktop/utility_ws/grpc_and/install-android/lib/cmake/grpc")
list(APPEND CMAKE_PREFIX_PATH "${Protobuf_DIR}" "${gRPC_DIR}")
message(${CMAKE_PREFIX_PATH})
find_package(Threads)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets WebChannel)
find_package(Qt5 COMPONENTS Core Concurrent REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

set(ros2qtgui_HDRS
        diden_mainwindow.h
)

set(ros2qtgui_UIS
        diden_mainwindow.ui
)


qt5_wrap_cpp(ros2qtgui_MOCS ${ros2qtgui_HDRS})

qt5_wrap_ui(ros2qtgui_UIS_H ${ros2qtgui_UIS})
# ✅ Qt6 찾기
# find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent QtGrpc)

# ✅ Protobuf 및 gRPC 경로 설정 (필요없음)

# list(APPEND CMAKE_PREFIX_PATH "${Protobuf_DIR}" "${gRPC_DIR}")

# ✅ Proto 파일 경로 설정
set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_SRCS
    ${GEN_DIR}/camera.pb.cc
    ${GEN_DIR}/camera.grpc.pb.cc
)
set(PROTO_HDRS
    ${GEN_DIR}/camera.pb.h
    ${GEN_DIR}/camera.grpc.pb.h
)

include_directories(
    ${GEN_DIR}
)

file(GLOB SOURCES
    main.cpp
    diden_mainwindow.cpp
    # diden_camerastream.cpp
    # diden_camerastream.h
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCES}         ${ros2qtgui_SRCS}
        ${ros2qtgui_MOCS}
        ${ros2qtgui_UIS_H})
else()
    add_executable(${PROJECT_NAME} ${SOURCES}        ${ros2qtgui_SRCS}
        ${ros2qtgui_MOCS}
        ${ros2qtgui_UIS_H})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    # Qt6::Widgets
    # Qt6::Concurrent
    # Qt6::Grpc
    Qt5::Core
    Qt5::Quick
    Qt5::Widgets
    Qt5::WebChannel
    Qt5::Concurrent
    protobuf::libprotobuf
    gRPC::grpc++
    Threads::Threads
)

# ✅ 최종 메시지
message(STATUS "✅ CMake configuration complete!")
