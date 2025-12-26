cmake_minimum_required(VERSION 4.2)

project(simple-collision-detection LANGUAGES CXX)

# Create target and add source files
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/system
)

# Find Gecko
find_package(Gecko REQUIRED)
target_link_libraries(${PROJECT_NAME} Gecko::Gecko)

# Find JsonCpp
find_package(jsoncpp REQUIRED)
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)

# Find Ogre
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
target_link_libraries(${PROJECT_NAME} OgreBites)
