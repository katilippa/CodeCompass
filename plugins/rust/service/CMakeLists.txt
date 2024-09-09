include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
  ${PROJECT_SOURCE_DIR}/util/include
  ${PROJECT_SOURCE_DIR}/webserver/include)

include_directories(SYSTEM
  ${THRIFT_LIBTHRIFT_INCLUDE_DIRS})

add_custom_command(
  OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/RustService.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/RustService.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
  COMMAND
    ${THRIFT_EXECUTABLE} --gen cpp
      -o ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/rust.thrift
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/rust.thrift
  COMMENT
    "Generating Thrift for rust.thrift")

add_library(rustthrift STATIC
  ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/RustService.cpp)

target_compile_options(rustthrift PUBLIC -fPIC)

add_library(rustservice SHARED
  src/rustservice.cpp
  src/plugin.cpp)

target_compile_options(rustservice PUBLIC -Wno-unknown-pragmas)

target_link_libraries(rustservice
  util
  ${THRIFT_LIBTHRIFT_LIBRARIES}
  ${ODB_LIBRARIES}
  rustthrift)

install(TARGETS rustservice DESTINATION ${INSTALL_SERVICE_DIR})
