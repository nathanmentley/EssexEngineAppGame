ee_setup_project("EssexEngineAppGame" "src/Apps/Game/")

target_link_libraries(EssexEngineAppGame EssexEngineCore)
target_link_libraries(EssexEngineAppGame EssexEngineLibIsoMap)
target_link_libraries(EssexEngineAppGame EssexEngineInputDaemon)
target_link_libraries(EssexEngineAppGame EssexEngineSfxDaemon)

add_custom_target(runGame
    COMMAND EssexEngineBootloader --game
    DEPENDS EssexEngineBootloader
    WORKING_DIRECTORY ../filesystem
)
