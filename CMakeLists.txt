cmake_minimum_required(VERSION 3.0.0)
project(SUVILapse VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


include(CTest)
enable_testing()

add_executable(SUVILapse src/main.cpp src/argparse.cpp src/ProcessSUVI.cpp src/ProcessABI.cpp)

target_link_libraries(SUVILapse ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

