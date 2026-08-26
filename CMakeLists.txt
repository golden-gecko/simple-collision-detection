cmake_minimum_required(VERSION 4.2)

# Includes
include(FetchContent)

# Project
project(simple-collision-detection)

# Sources
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Target
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/system
)

# Gecko
if(NOT DEFINED Gecko_DIR)
    set(Gecko_DIR "" CACHE PATH "")
endif()

find_package(Gecko REQUIRED)
target_link_libraries(${PROJECT_NAME} Gecko::Gecko)

# JsonCpp
set(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(JSONCPP_WITH_POST_BUILD_UNITTESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(jsoncpp GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git GIT_TAG 1.9.8)
FetchContent_MakeAvailable(jsoncpp)
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)

# Ogre
if(NOT DEFINED OGRE_DIR)
    set(OGRE_DIR "" CACHE PATH "")
endif()

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
target_link_libraries(${PROJECT_NAME} OgreBites)
