cmake_minimum_required(VERSION 3.16)

project(sfSnakePro)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(thirdparty/SFML)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(main ${SOURCES})
target_include_directories(main PUBLIC src thirdparty/SFML/include)
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-network sfml-graphics sfml-audio sfml-main)
set_property(TARGET main PROPERTY
  CXX_STANDARD          17
  CXX_STANDARD_REQUIRED ON)
