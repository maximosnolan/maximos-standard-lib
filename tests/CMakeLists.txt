# CMakeLists.txt inside the tests directory

# Add the source files in the tests directory
file(GLOB TEST_SOURCES "*.cpp")

# Create a separate executable for each test source file
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)  # Extract the name without extension
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} maximosStdLib)
endforeach()
