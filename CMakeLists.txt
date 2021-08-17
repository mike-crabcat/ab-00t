cmake_minimum_required (VERSION 3.12)

include(FetchContent)

FetchContent_Declare(
  kaitai_struct_cpp_stl_runtime
  GIT_REPOSITORY    https://github.com/kaitai-io/kaitai_struct_cpp_stl_runtime
  GIT_TAG           master
)

FetchContent_MakeAvailable(kaitai_struct_cpp_stl_runtime)



# LibBlocksmith
#
project(tester)

# Include all local header files
include_directories(
  .
  ${kaitai_struct_cpp_stl_runtime_SOURCE_DIR}
)

add_library(vulcan_tri_reader vulcan_00t.cpp fastlz.cpp VulcanTriReader.cpp export.cpp)
set_property(TARGET vulcan_tri_reader PROPERTY CXX_STANDARD 17)
set_property(TARGET vulcan_tri_reader PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(vulcan_tri_reader kaitai_struct_cpp_stl_runtime)

add_executable(tester tester.c)
target_link_libraries(tester vulcan_tri_reader)
set_target_properties(tester PROPERTIES LINKER_LANGUAGE C)
