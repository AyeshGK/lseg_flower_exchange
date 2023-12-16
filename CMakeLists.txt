cmake_minimum_required(VERSION 3.10)
project(lseg_flower_exchange)

# Add C++11 standard
set(CMAKE_CXX_STANDARD 11)

# Set the source files
set(SOURCE_FILES
    src/common/OrderBuffer.cpp
    src/DAO/Order.cpp
    src/Exchanger.cpp
    src/factory/FlowerBookFactory.cpp
    src/model/Book.cpp
    src/service/CSVReader.cpp
    src/service/CSVWriter.cpp
    src/service/NewMatchingEngine.cpp
    src/service/OldMatchingEngine.cpp
    src/main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
    include
)

# Add additional dependencies if needed
# target_link_libraries(${PROJECT_NAME} some_library)

# Set output directories for binaries and libraries
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
