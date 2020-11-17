project (LL_MEC)
cmake_minimum_required(VERSION 2.8)


macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")
  else ()
    set (CMAKE_CXX_STANDARD 14)
  endif ()
endmacro(use_cxx11)

use_cxx11()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(LL_MEC_SRC "${PROJECT_SOURCE_DIR}/src")
set(LL_MEC_TARGET "${PROJECT_SOURCE_DIR}/targets")

#3 levels - DRIVER / CORE / APP / UTIL / DATA
set(APP_DIR "${LL_MEC_SRC}/app")
set(CORE_DIR "${LL_MEC_SRC}/core")
set(EVENT_DIR "${LL_MEC_SRC}/event")
set(DRIVER_DIR "${LL_MEC_SRC}/driver")
set(UTIL_DIR "${LL_MEC_SRC}/util")
set(DATA_DIR "${LL_MEC_SRC}/data")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#OF BASE DRIVER
set(FLUIDBASE_DIR "${DRIVER_DIR}/fluidbase")
set(FLUIDBASE_include_files
  "${FLUIDBASE_DIR}"
  "${FLUIDBASE_DIR}/fluid"
  "${FLUIDBASE_DIR}/fluid/base"
  )
set(FLUIDBASE_src_files
  ${FLUIDBASE_DIR}/fluid/base/EventLoop.cc
  ${FLUIDBASE_DIR}/fluid/base/BaseOFConnection.cc
  ${FLUIDBASE_DIR}/fluid/base/BaseOFServer.cc
  ${FLUIDBASE_DIR}/fluid/OFConnection.cc
  ${FLUIDBASE_DIR}/fluid/OFServerSettings.cc
  ${FLUIDBASE_DIR}/fluid/OFServer.cc
  ${FLUIDBASE_DIR}/fluid/TLS.cc
  )

add_library(FLUIDBASE ${FLUIDBASE_src_files})
target_link_libraries(FLUIDBASE
  event
  pthread
  ssl
  crypto
  event_openssl
  event_pthreads
  )

#OF MSG DRIVER
set(FLUIDMSG_DIR "${DRIVER_DIR}/fluidmsg")
set(FLUIDMSG_include_files
  ${FLUIDMSG_DIR}
  ${FLUIDMSG_DIR}/fluid
  ${FLUIDMSG_DIR}/fluid/ofcommon
  ${FLUIDMSG_DIR}/fluid/of10
  ${FLUIDMSG_DIR}/fluid/of13
  ${FLUIDMSG_DIR}/fluid/util
  )
set(FLUIDMSG_src_files
  ${FLUIDMSG_DIR}/fluid/util/ethaddr.cc
  ${FLUIDMSG_DIR}/fluid/util/ipaddr.cc
  ${FLUIDMSG_DIR}/fluid/ofcommon/msg.cc
  ${FLUIDMSG_DIR}/fluid/ofcommon/action.cc
  ${FLUIDMSG_DIR}/fluid/ofcommon/common.cc
  ${FLUIDMSG_DIR}/fluid/of10/of10action.cc
  ${FLUIDMSG_DIR}/fluid/of10/of10common.cc
  ${FLUIDMSG_DIR}/fluid/of10/of10match.cc
  ${FLUIDMSG_DIR}/fluid/of13/of13instruction.cc
  ${FLUIDMSG_DIR}/fluid/of13/of13action.cc
  ${FLUIDMSG_DIR}/fluid/of13/of13meter.cc
  ${FLUIDMSG_DIR}/fluid/of13/of13common.cc
  ${FLUIDMSG_DIR}/fluid/of13/of13match.cc
  ${FLUIDMSG_DIR}/fluid/of10msg.cc
  ${FLUIDMSG_DIR}/fluid/of13msg.cc
  )

add_library(FLUIDMSG ${FLUIDMSG_src_files})

#JSON driver
set(JSON_DIR "${DRIVER_DIR}/json")
set(JSON_include_files
  ${JSON_DIR}
  )

#CORE/EPS
set(EPS_DIR "${CORE_DIR}/eps")
set(EPS_src_files
  ${EPS_DIR}/controller.cc
  ${EPS_DIR}/of_interface.cc
  ${EPS_DIR}/conf.cc
  )
set(EPS_include_files
  ${EPS_DIR}
  ${APP_DIR}
  )

#Util
set(UTIL_src_files
  ${UTIL_DIR}/input_parser.cc
  )
set(UTIL_include_files
  ${UTIL_DIR}
  )
add_library(UTIL ${UTIL_src_files})

#Data
set(DATA_src_files
  ${DATA_DIR}/context_manager.cc
  )
set(DATA_include_files
  ${DATA_DIR}
  )
add_library(DATA ${DATA_src_files})

find_package(Event REQUIRED)
add_library(EPS ${EPS_src_files})
target_link_libraries(EPS FLUIDBASE FLUIDMSG)

#CORE
set(CORE_src_files
  ${CORE_DIR}/task.cc
  ${CORE_DIR}/rt_wrapper.cc
  )
set(CORE_include_files
  ${CORE_DIR}
  )
add_library(CORE ${CORE_src_files})
target_link_libraries(CORE EPS)

# We need boost signals2
find_package(Boost 1.54.0 REQUIRED COMPONENTS system)
add_library(EVENT ${EVENT_DIR}/subscription.cc)
target_link_libraries(EVENT EPS)
set(EVENT_include_files ${EVENT_DIR})

#APP
set(SGWC_DIR "${APP_DIR}/sgwc")
set(SWITCH_DIR "${APP_DIR}/switch_manager")
set(STATS_DIR "${APP_DIR}/stats")
set(UPLANE_DIR "${APP_DIR}/uplane")
#set(METER_DIR "${APP_DIR}/meter_manager")
set(APP_src_files
  ${SGWC_DIR}/sgwc.cc
  ${SWITCH_DIR}/switch_manager.cc
  ${STATS_DIR}/stats_manager.cc
  ${UPLANE_DIR}/ue_manager.cc
#  ${METER_DIR}/meter_manager.cc)
)
set(APP_include_files
  ${EPS_DIR}
  ${CORE_DIR}
  ${APP_DIR}
  ${SGWC_DIR}
  ${SWITCH_DIR}
  ${STATS_DIR}
  ${UPLANE_DIR}
#  ${METER_DIR}
  )
add_library(APP ${APP_src_files})
target_link_libraries(APP CORE EVENT)

#Pistache
add_library(PISTACHE STATIC IMPORTED)
set_target_properties(PISTACHE PROPERTIES IMPORTED_LOCATION /usr/local/lib/libpistache.a)
set(PISTACHE_include_files /usr/local/include/pistache)

#NORTH_API

set(NORTH_API_DIR "${LL_MEC_SRC}/north_api")
set(NORTH_API_src_files
  ${NORTH_API_DIR}/stats_rest_calls.cc
  ${NORTH_API_DIR}/ue_rest_calls.cc
  ${NORTH_API_DIR}/rest_manager.cc
  )
set(NORTH_API_include_files
  ${NORTH_API_DIR}
  )
add_library(NORTH_API ${NORTH_API_src_files})


#MP1_API
set(MP1_API_DIR "${LL_MEC_SRC}/mp1")
  
file(GLOB MP1_API_src_files
    ${MP1_API_DIR}/mp1-api-server.cpp
    ${MP1_API_DIR}/model/*.cpp
    ${MP1_API_DIR}/api/*.cpp
    ${MP1_API_DIR}/impl/*.cpp
    ${MP1_API_DIR}/rib/*.cpp
)
  
 
set(MP1_API_include_files
  ${MP1_API_DIR}/api
  ${MP1_API_DIR}/impl
  ${MP1_API_DIR}/model
  ${MP1_API_DIR}/rib
  ${MP1_API_DIR}
  )
add_library(MP1_API ${MP1_API_src_files})

#MP2_API
set(MP2_API_DIR "${LL_MEC_SRC}/mp2")
  
file(GLOB MP2_API_src_files
    ${MP2_API_DIR}/mp2-api-server.cpp
    ${MP2_API_DIR}/model/*.cpp
    ${MP2_API_DIR}/api/*.cpp
    ${MP2_API_DIR}/impl/*.cpp
)
  
 
set(MP2_API_include_files
  ${MP2_API_DIR}/api
  ${MP2_API_DIR}/impl
  ${MP2_API_DIR}/model
  ${MP2_API_DIR}
  )
add_library(MP2_API ${MP2_API_src_files})

# spdlog header files
set(SPDLOG_include_dir "${DRIVER_DIR}/spdlog")

#headers to be included
include_directories(
  ${FLUIDBASE_include_files}
  ${FLUIDMSG_include_files}
  ${JSON_include_files}
  ${EPS_include_files}
  ${EVENT_include_files}
  ${APP_include_files}
  ${UTIL_include_files}
  ${DATA_include_files}
  ${NORTH_API_include_files}
  ${MP1_API_include_files}
  ${MP2_API_include_files}
  ${PISTACHE_include_files}
  ${SPDLOG_include_dir}
  ${Event_INCLUDE_DIRS}
  )


#targets
# Uncomment ll-mecsim when needed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(LL_MEC ${LL_MEC_TARGET}/ll-mec)
#set(LL_MECSIM ${LL_MEC_TARGET}/ll-mecsim)
add_executable(ll-mec
  ${LL_MEC}/ll-mec.cc
  )
#add_executable(ll-mecsim
#  ${LL_MECSIM}/ll-mecsim.cc
#  )
#libraries to be linked
target_link_libraries(ll-mec
  CORE
  APP
  UTIL
  DATA
  NORTH_API
  MP1_API
  MP2_API
  PISTACHE
  curl
  )
#target_link_libraries(ll-mecsim FLUIDBASE FLUIDMSG)
