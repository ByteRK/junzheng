cmake_minimum_required (VERSION 3.8)
project(junzheng)

set(CMAKE_CXX_STANDARD 11)

#find_package(CDROID REQUIRED)
include_directories(
   ./
   ./src/comm
   ./src/window
   ${CDROID_INCLUDE_DIRS}
   ${CDROID_DEPINCLUDES}
   ${CMAKE_BINARY_DIR}/include
   ${CMAKE_BINARY_DIR}/include/gui
   ${CMAKE_BINARY_DIR}/include/porting
   ${CMAKE_BINARY_DIR}/include/cairo
   ${CMAKE_BINARY_DIR}/include/epg
   ${CMAKE_BINARY_DIR}/include/freetype2
)
aux_source_directory(./ JZ_SRCS)
aux_source_directory(./src/comm JZ_SRCS)
aux_source_directory(./src/window JZ_SRCS)
add_definitions(--include cdtypes.h)
add_definitions(--include cdlog.h)
link_directories(${CMAKE_BINARY_DIR}/lib)
message("PROJECT_NAME=${PROJECT_NAME}")
add_executable(${PROJECT_NAME} ${JZ_SRCS})

CreatePAK(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pak ${PROJECT_SOURCE_DIR}/R.h)


target_link_libraries(${PROJECT_NAME} PRIVATE cdroid)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

