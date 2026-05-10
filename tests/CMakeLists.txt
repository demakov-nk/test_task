find_package(GTest REQUIRED)

add_executable(test_list test_list.cpp)
target_link_libraries(test_list PRIVATE List GTest::GTest GTest::Main)
add_test(NAME ListTests COMMAND test_list)
