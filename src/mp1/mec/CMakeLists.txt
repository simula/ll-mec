cmake_minimum_required (VERSION 3.2)

project(main_api_server)

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
main-api-server.cpp
    ${MODEL_SOURCES}
    ${MEC_API_SOURCES})

add_executable(mec_api_server
${MEC_API_SERVER_SOURCES})

target_link_libraries(mec_api_server pistache pthread)
