cmake_minimum_required(VERSION 4.3)
project(WebCacheStorage)

set(CMAKE_CXX_STANDARD 20)




# IMPORTANT: Enable CTest support
enable_testing()

# Create the library
set(LIB_NAME mylib)

add_library(${LIB_NAME}
        HashTable.cpp   # Only the .cpp file
)
target_include_directories(${LIB_NAME} PUBLIC WebCacheStorage)

# Main program
add_executable(WebCacheStorage
        main.cpp
)

target_link_libraries(WebCacheStorage
        PUBLIC ${LIB_NAME}
)
add_subdirectory(tests)

