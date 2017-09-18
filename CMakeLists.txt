#files

file(GLOB EssexEngineGfxDaemon_HEADERS
    "src/Daemons/GfxDaemon/*.h"
    "src/Daemons/GfxDaemon/*/*.h"
)
file(GLOB EssexEngineGfxDaemon_SRC
    ${EssexEngineGfxDaemon_HEADERS}
    "src/Daemons/GfxDaemon/*.cpp"
    "src/Daemons/GfxDaemon/*/*.cpp"
)

#setup headers

file(COPY ${EssexEngineGfxDaemon_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineGfxDaemon/")

#setup build

add_library(EssexEngineGfxDaemon SHARED ${EssexEngineGfxDaemon_SRC})
target_link_libraries(EssexEngineGfxDaemon EssexEngineCore)