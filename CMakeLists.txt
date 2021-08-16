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
project(tester CXX)

# Include all local header files
include_directories(
  .
  ${kaitai_struct_cpp_stl_runtime_SOURCE_DIR}
)

# All source cpps for blocksmith
list(APPEND src
  main.cpp
  vulcan_00t.cpp
  fastlz.cpp
  VulcanTriReader.cpp)


add_executable(tester ${src})

set_property(TARGET tester PROPERTY CXX_STANDARD 17)
set_property(TARGET tester PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(tester kaitai_struct_cpp_stl_runtime)


