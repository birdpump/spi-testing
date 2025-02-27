# Define library
add_library(TMC4671
        TMC4671.c
        TMC4671.h
        TMC4671_HW_Abstraction.h
)

target_link_libraries(TMC4671 pico_stdlib)

# Include directories
target_include_directories(TMC4671 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})