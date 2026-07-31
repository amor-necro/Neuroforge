add_executable(smoke_test smoke_test.cpp)

target_link_libraries(smoke_test PRIVATE Neuroforge::neuroforge)

neuroforge_enable_warnings(smoke_test)

add_test(NAME smoke_test COMMAND smoke_test)

add_executable(matrix_test matrix_test.cpp)

target_link_libraries(matrix_test PRIVATE Neuroforge::neuroforge)

neuroforge_enable_warnings(matrix_test)

add_test(NAME matrix_test COMMAND matrix_test)
