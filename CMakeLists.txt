#files

file(GLOB EssexEngineGfxDaemon_HEADERS
    "src/Daemons/Gfx/*.h"
    "src/Daemons/Gfx/*/*.h"
)
file(GLOB EssexEngineGfxDaemon_SRC
    ${EssexEngineGfxDaemon_HEADERS}
    "src/Daemons/Gfx/*.cpp"
    "src/Daemons/Gfx/*/*.cpp"
)

#setup headers

file(COPY ${EssexEngineGfxDaemon_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineGfxDaemon/")

#setup build

add_library(EssexEngineGfxDaemon SHARED ${EssexEngineGfxDaemon_SRC})
target_link_libraries(EssexEngineGfxDaemon EssexEngineCore)