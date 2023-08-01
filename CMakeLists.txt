
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(zikzira VERSION 0.0.1 LANGUAGES C)


if(WIN32)

    add_custom_command(OUTPUT ./res/res.o
    COMMAND windres -F pe-x86-64 res/res.rc -o res/res.o
    # COMMAND windres -F pe-i386 res/res.rc -o res/res.o
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

endif()


file(GLOB executable_source_files
    "./*.c"
    "./gameplay_shared/*.c"
    "./gameplay/*.c"
)

set(executable_header_files
    ./
)


find_package(SDL2 REQUIRED)


if(WIN32)

    add_executable(${CMAKE_PROJECT_NAME} ${executable_source_files} ./res/res.o)

else()

    add_executable(${CMAKE_PROJECT_NAME} ${executable_source_files})

endif()


include_directories(${executable_header_files})


if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    target_link_libraries(${CMAKE_PROJECT_NAME} SDL2)

else()

    include_directories(${SDL2_INCLUDE_DIRS})

    target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})

endif()

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2_image)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2_mixer)


target_link_libraries(${CMAKE_PROJECT_NAME} m winmm)
