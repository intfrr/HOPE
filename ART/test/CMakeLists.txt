find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

function (add_unit_test file_name)
  add_executable(${file_name} ${file_name}.cpp)
  target_link_libraries(${file_name} ART gtest)
  add_test(NAME ${file_name} 
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${file_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endfunction()

add_unit_test(test_art)

