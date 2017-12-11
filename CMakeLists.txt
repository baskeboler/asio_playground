cmake_minimum_required(VERSION 3.5)
project(asio_playground)

set(CMAKE_CXX_STANDARD 14)
set(BOOSTROOT "/usr/local")
#set(CMAKE_EXE_LINKER_FLAGS   -lpthread)
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
include_directories(/usr/local/include)
find_package(Boost 1.65.0 COMPONENTS filesystem exception system date_time iostreams container context timer type_erasure)
set(SOURCE_FILES main.cpp session.cpp session.h server.cpp server.h request_handler.cpp request_handler.h direct_response_handler.cpp direct_response_handler.h file_serve_handler.cpp file_serve_handler.h)
include_directories(${Boost_INCLUDE_DIRS} /home/victor/software/boost_1_65_1/libs/beast/include)


add_executable(asio_playground ${SOURCE_FILES})
target_link_libraries(asio_playground ${Boost_LIBRARIES})
