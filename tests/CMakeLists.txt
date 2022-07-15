find_package(Python REQUIRED)

# define tests
add_executable( test_swap 
  test_swap.c 
)

target_link_libraries(
  test_swap
  lib
)

#example of a unit test using C
add_test(
  NAME test_swap_index
  COMMAND $<TARGET_FILE:test_swap>
)

# example of a functional test using python
add_test(
  NAME test_example_file 
  COMMAND ${Python_EXECUTABLE} 
  ${CMAKE_CURRENT_SOURCE_DIR}/test_standard.py 
  $<TARGET_FILE:bin_packing> 
  ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
)