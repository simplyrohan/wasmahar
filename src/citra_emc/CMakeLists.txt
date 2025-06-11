set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMakeModules)

add_library(citra_emc STATIC EXCLUDE_FROM_ALL
    emu_window_sdl2.cpp
    emu_window_sdl2.h
    emu_window_sdl2_gl.cpp
    emu_window_sdl2_gl.h
    citra_emc.cpp
)

create_target_directory_groups(citra_emc)

target_link_libraries(citra_emc PRIVATE citra_common citra_core input_common network)
target_link_libraries(citra_emc PRIVATE inih)

# target_link_libraries(citra_emc PRIVATE ${PLATFORM_LIBRARIES} Threads::Threads)

target_link_libraries(citra_emc PRIVATE glad)

# if (CITRA_USE_PRECOMPILED_HEADERS)
#     target_precompile_headers(citra_sdl PRIVATE precompiled_headers.h)
# endif()
