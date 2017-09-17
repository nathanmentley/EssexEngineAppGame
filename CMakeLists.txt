#files

file(GLOB EssexEngineAppGame_HEADERS
    "src/Apps/Game/*.h"
)
file(GLOB EssexEngineAppGame_SRC
    ${EssexEngineAppGame_HEADERS}
    "src/Apps/Game/*.cpp"
)

#setup headers

file(COPY ${EssexEngineAppGame_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineAppGame/")

#setup build

add_library(EssexEngineAppGame SHARED ${EssexEngineAppGame_SRC})
target_link_libraries(EssexEngineAppGame EssexEngineCore)
target_link_libraries(EssexEngineAppGame EssexEngineLibIsoMap)
target_link_libraries(EssexEngineAppGame EssexEngineInputDaemon)

#run

add_custom_target(runGame
    COMMAND EssexEngineBootloader --game
    DEPENDS EssexEngineBootloader
    WORKING_DIRECTORY ../filesystem
)