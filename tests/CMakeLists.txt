
# define tests
add_executable(test_script test.c)

add_test(
  NAME test_script
  COMMAND $<TARGET_FILE:test_script> $<TARGET_FILE:stoneridge_hw>
)