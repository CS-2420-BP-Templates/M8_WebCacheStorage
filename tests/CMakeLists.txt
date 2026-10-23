# List of base names for source files to test
set(UNIT_TEST_LIST WebCache)

# Create list of test source files
foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST ${NAME}_test.cpp)
endforeach()

# Name of the test executable
set(TARGET_NAME WebCache_test)

# Library name must match the one in root CMake
set(LIB_NAME mylib)

# Catch2 definition
add_definitions(-DCATCH_CONFIG_NO_POSIX_SIGNALS)

# Create test executable
add_executable(${TARGET_NAME} ${UNIT_TEST_SOURCE_LIST})

# Link the library containing function definitions
target_link_libraries(${TARGET_NAME} PUBLIC ${LIB_NAME})

# Include headers
target_include_directories(${TARGET_NAME} PUBLIC ../)                # root headers
target_include_directories(${TARGET_NAME} PUBLIC ../externals/catch2/)
target_include_directories(${TARGET_NAME} PUBLIC ../externals/doctest/)

# Register the test with CTest
add_test(
        NAME project_test
        COMMAND $<TARGET_FILE:${TARGET_NAME}> --success
)
