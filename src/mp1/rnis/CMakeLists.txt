cmake_minimum_required (VERSION 3.2)

project(mp1-rnis-api)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pg -g3" )

link_directories(/usr/local/lib/)

aux_source_directory(model MODEL_SOURCES)
file(GLOB MP1_API_SOURCES
"api/DefaultApi.h"
"api/DefaultApi.cpp"
"impl/DefaultApiImpl.h"
"impl/DefaultApiImpl.cpp"
)

include_directories(model)
include_directories(api)
include_directories(impl)

set(MP1_API_SERVER_SOURCES
mp1-rnis-api.cpp
    ${MODEL_SOURCES}
    ${MP1_API_SOURCES})

add_executable(${PROJECT_NAME} ${MP1_API_SERVER_SOURCES} )
target_link_libraries(${PROJECT_NAME} pistache pthread)


#include_directories(/usr/local/include/pistache)
#include_directories(/usr/local/include/nlohmann)

#include_directories(model)
#include_directories(api)
#include_directories(impl)

#file(GLOB SRCS
#    ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/model/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
#)

#add_executable(${PROJECT_NAME} ${SRCS} )
#target_link_libraries(${PROJECT_NAME} pistache pthread)
