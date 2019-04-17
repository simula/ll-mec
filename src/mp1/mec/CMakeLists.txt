cmake_minimum_required (VERSION 3.2)

project(mp1-mec-api)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pg -g3" )

link_directories(/usr/local/lib/)

aux_source_directory(model MODEL_SOURCES)
file(GLOB MEC_API_SOURCES
"api/DefaultApi.h"
"api/DefaultApi.cpp"
"impl/DefaultApiImpl.h"
"impl/DefaultApiImpl.cpp"
)


include_directories(model)
include_directories(api)
include_directories(impl)

set(MEC_API_SERVER_SOURCES
mp1-mec-api.cpp
    ${MODEL_SOURCES}
    ${MEC_API_SOURCES})

add_executable(${PROJECT_NAME}
${MEC_API_SERVER_SOURCES})

target_link_libraries(${PROJECT_NAME} pistache pthread)
