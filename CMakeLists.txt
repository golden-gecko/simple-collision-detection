cmake_minimum_required(VERSION 4.2)

project(simple-collision-detection)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} OgreBites)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS NO
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/system
)
