# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.31.1)

# Define the project name and version
project(hello
    VERSION 1.0.0
    DESCRIPTION "Just learning CMAKE"
    LANGUAGES C CXX
)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11) # Requires C11 standard

# Assume the default OS bitness is 32-bit
set(OSBitness 32)

# Check if the platform is 64-bit and update the variable accordingly
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OBBitness 64)
endif()

# Define the output directory structure for binaries
# Output paths depend on system name, bitness, and build type
set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs") # static libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}") # shared libaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}") # executabel files

# Specify the source files for the main executable
set(SOURCES main.c)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if(NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)

    if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif()
endif()

# List of subprojects to include in the build
set(SubProjects
    console
)

# Add the main executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Add compile options for the main target
# -O2: Optimization for speed
# -Wall: Enable all warnings
# -Werror: Treat warnings as errors
# -Wpedantic: Enforce strict C standard compliance
target_compile_options(${PROJECT_NAME} PRIVATE -O2 -Wall -Werror -Wpedantic)

# Loop through the subprojects and add them to the build
foreach(Project IN LISTS SubProjects)
    # Include the directory for the subproject
    include_directories(${Project})

    # If the subproject is not already added, add it as a subdirectory
    if(NOT TARGET ${Project})
        add_subdirectory(${Project})
    endif()

    # Link the subproject with the main executable
    target_link_libraries(${PROJECT_NAME} ${Project})
endforeach()

target_link_libraries(${PROJECT_NAME} raylib)

# include_directories(console)
# if(NOT TARGET console)
# add_subdirectory(console)
# endif()
# # add_library(console SHARED console.c)
# # add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries(${PROJECT_NAME} console raylib)