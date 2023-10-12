cmake_minimum_required(VERSION 3.25)

project(fx_native C)

include(bare)

if(NOT TARGET fx)
  add_subdirectory(vendor/libfx EXCLUDE_FROM_ALL)
endif()

add_bare_module(fx_native)

target_sources(
  fx_native
  PRIVATE
    binding.c
)

target_include_directories(
  fx_native
  PUBLIC
    $<TARGET_PROPERTY:fx,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(
  fx_native
  PUBLIC
    fx
)
