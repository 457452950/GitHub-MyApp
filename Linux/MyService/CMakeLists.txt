cmake_minimum_required(VERSION 3.16)
project(MyService)

set(CMAKE_CXX_STANDARD 17)


find_package(Boost COMPONENTS thread)

if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()


include_directories($(Boost_include_dir))
include_directories(include)


add_executable(MyService src/main.cpp src/BaseServer.cpp src/BaseServer.h src/Config.cpp src/Config.h
        src/JsonFileReader.cpp src/JsonFileReader.h src/BaseConnection.cpp src/BaseConnection.h)


link_directories($(Boost_library_dir))
target_link_libraries(MyService ${Boost_LIBRARIES})

