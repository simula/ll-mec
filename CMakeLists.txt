project (LL_MEC)
cmake_minimum_required(VERSION 3.0)


macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(LL_MEC_SRC "${PROJECT_SOURCE_DIR}/src")
set(LL_MEC_TARGET "${PROJECT_SOURCE_DIR}/targets")

#3 levels - DRIVER / CORE / APP
set(APP_DIR "${LL_MEC_SRC}/app")
set(CORE_DIR "${LL_MEC_SRC}/core")
set(DRIVER_DIR "${LL_MEC_SRC}/driver")

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
set (JSON_src_files
  ${JSON_DIR}/json11.cc
  )
set(JSON_include_files
  ${JSON_DIR}
  )
add_library(JSON ${JSON_src_files})

#CORE/EPS
set(EPS_DIR "${CORE_DIR}/eps")
set(EPS_src_files
  ${EPS_DIR}/controller.cc
  ${EPS_DIR}/of_interface.cc
  )
set(EPS_include_files
  ${EPS_DIR}
  ${APP_DIR}
  )

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


#APP

set(SGWC_DIR "${APP_DIR}/sgwc")
set(SWITCH_DIR "${APP_DIR}/basic_switch")
set(STATS_DIR "${APP_DIR}/stats")
set(APP_src_files
  ${SGWC_DIR}/sgwc.cc
  ${SWITCH_DIR}/basic_switch.cc
  ${STATS_DIR}/stats_manager.cc
  )
set(APP_include_files
  ${EPS_DIR}
  ${CORE_DIR}
  ${APP_DIR}
  ${SGWC_DIR}
  ${SWITCH_DIR}
  ${STATS_DIR}
  )
add_library(APP ${APP_src_files})
target_link_libraries(APP CORE)

#Pistache
add_library(PISTACHE STATIC IMPORTED)
set_target_properties(PISTACHE PROPERTIES IMPORTED_LOCATION /usr/local/lib/libpistache.a)
set(PISTACHE_include_files /usr/local/include/pistache)

#NORTH_API

set(NORTH_API_DIR "${LL_MEC_SRC}/north_api")
set(NORTH_API_src_files
  ${NORTH_API_DIR}/stats_rest_calls.cc
  ${NORTH_API_DIR}/rest_manager.cc
  )
set(NORTH_API_include_files
  ${NORTH_API_DIR}
  )
add_library(NORTH_API ${NORTH_API_src_files})

#headers to be included
include_directories(
  ${FLUIDBASE_include_files}
  ${FLUIDMSG_include_files}
  ${EPS_include_files}
  ${APP_include_files}
  ${NORTH_API_include_files}
  ${JSON_include_files}
  ${PISTACHE_include_files}
  ${Event_INCLUDE_DIRS}
  )


#targets
set(LL_MEC ${LL_MEC_TARGET}/ll-mec)
set(LL_MECSIM ${LL_MEC_TARGET}/ll-mecsim)
add_executable(ll-mec
  ${LL_MEC}/ll-mec.cc
  )
add_executable(ll-mecsim
  ${LL_MECSIM}/ll-mecsim.cc
  )
#libraries to be linked
target_link_libraries(ll-mec
  CORE
  APP
  NORTH_API
  PISTACHE
  )
target_link_libraries(ll-mecsim FLUIDBASE FLUIDMSG)
