cmake_minimum_required(VERSION 3.23)
project(gol)

set(CMAKE_CXX_STANDARD 20)

add_executable(gol src/main.cpp
        src/commands/CliCommand.cpp src/commands/CliCommand.h
        src/commands/command_callbacks.cpp src/commands/command_callbacks.h
        src/game/game.cpp src/game/game.h
        src/gol/Rule.cpp src/gol/Rule.h
        src/gol/Cell.cpp src/gol/Cell.h
        src/gol/GOLArea.cpp src/gol/GOLArea.h
        src/commands/commands.cpp src/commands/commands.h
        src/game/globals.cpp src/game/globals.h
        src/game/callbacks.cpp src/game/callbacks.h src/ArgParser.cpp src/ArgParser.h)


set(ENGINE_DIR /media/alexium/Shared/engine/cws-rengines)

if(EMSCRIPTEN)
    target_compile_options(gol PUBLIC -sUSE_SDL=2 -sUSE_SDL_IMAGE=2)
    target_link_options(gol PUBLIC -sUSE_SDL=2 -sUSE_SDL_IMAGE=2)
    target_link_options(gol PUBLIC -sSDL2_IMAGE_FORMATS=["png"])
    message("Compiling to web!")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
    target_link_options(gol PRIVATE -sWASM -sALLOW_MEMORY_GROWTH -sASYNCIFY)
#    target_link_options(gol PRIVATE -sWEBSOCKET_SUBPROTOCOL='null')
    target_link_options(gol PRIVATE -sUSE_SDL=2)
    target_link_options(gol PRIVATE -fexceptions)
    target_compile_options(gol PRIVATE -fexceptions)

    #    target_link_options(gol PRIVATE -sWEBSOCKET_URL=ws://)
    #    target_link_options(gol PRIVATE -sWEBSOCKET_SUBPROTOCOL='text')
    target_link_options(gol PRIVATE --preload-file ../assets/)
    target_link_options(gol PRIVATE --shell-file "${ENGINE_DIR}/src/emscripten/shell_minimal.html")
#    target_link_options(gol PRIVATE -sEXPORTED_RUNTIME_METHODS=["ccall"])
    target_link_options(gol PRIVATE -sFORCE_FILESYSTEM=1)
#    target_link_options(gol PRIVATE -sEXPORTED_FUNCTIONS=_main)
    set_target_properties(gol PROPERTIES OUTPUT_NAME "index")

    target_link_libraries(gol
            debug "${ENGINE_DIR}/target/wasm32-unknown-emscripten/debug/libcws_rengines.a"
            optimized "${ENGINE_DIR}/target/wasm32-unknown-emscripten/release/libcws_rengines.a"
            #        "${ENGINE_DIR}/target/debug/libcws_rengines.a"
            )
    set_target_properties(gol
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
            )
else()
    INCLUDE(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    target_link_libraries(gol ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

    target_link_libraries(gol
            debug "${ENGINE_DIR}/target/debug/libcws_rengines.a"
            optimized "${ENGINE_DIR}/target/release/libcws_rengines.a"
            #        "${ENGINE_DIR}/target/debug/libcws_rengines.a"
            )

endif()


