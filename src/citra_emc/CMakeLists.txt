set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMakeModules)

add_library(citra_emc STATIC EXCLUDE_FROM_ALL
    # config.cpp
    # config.h
    # default_ini.h
    # emu_window/emu_window_sdl2.cpp
    # emu_window/emu_window_sdl2.h
    # citra_sdl.cpp
    # precompiled_headers.h
    # resource.h
    citra_emc.cpp
)

# if (ENABLE_SOFTWARE_RENDERER)
#     target_sources(citra_sdl PRIVATE
#         emu_window/emu_window_sdl2_sw.cpp
#         emu_window/emu_window_sdl2_sw.h
#     )
# endif()
# if (ENABLE_OPENGL)
#     target_sources(citra_sdl PRIVATE
#         emu_window/emu_window_sdl2_gl.cpp
#         emu_window/emu_window_sdl2_gl.h
#     )
# endif()
# if (ENABLE_VULKAN)
#     target_sources(citra_sdl PRIVATE
#         emu_window/emu_window_sdl2_vk.cpp
#         emu_window/emu_window_sdl2_vk.h
#     )
# endif()

create_target_directory_groups(citra_emc)

target_link_libraries(citra_emc PRIVATE citra_common citra_core input_common network)
target_link_libraries(citra_emc PRIVATE inih)

# target_link_libraries(citra_emc PRIVATE ${PLATFORM_LIBRARIES} Threads::Threads)

# if (ENABLE_OPENGL)
#     target_link_libraries(citra_sdl PRIVATE glad)
# endif()

# if (CITRA_USE_PRECOMPILED_HEADERS)
#     target_precompile_headers(citra_sdl PRIVATE precompiled_headers.h)
# endif()
