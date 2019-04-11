cmake_minimum_required (VERSION 3.2)

project(api-server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pg -g3" )

#include(ExternalProject)

#set(EXTERNAL_INSTALL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)

#ExternalProject_Add(PISTACHE
#    GIT_REPOSITORY https://github.com/oktal/pistache.git
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#)

#ExternalProject_Add(NLOHMANN
#    GIT_REPOSITORY https://github.com/nlohmann/json.git
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#
#)

#add_library(PISTACHE STATIC IMPORTED)
#set_target_properties(PISTACHE PROPERTIES IMPORTED_LOCATION /usr/local/lib/libpistache.a)
#set(PISTACHE_include_files /usr/local/include/pistache)

link_directories(/usr/local/lib/)

include_directories(/usr/local/include/pistache)
include_directories(/usr/local/include/nlohmann)

include_directories(model)
include_directories(api)
include_directories(impl)

file(GLOB SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${SRCS} )
#add_dependencies(${PROJECT_NAME} PISTACHE NLOHMANN)
target_link_libraries(${PROJECT_NAME} pistache pthread)
