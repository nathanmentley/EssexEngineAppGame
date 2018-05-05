/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineAppGame/MainMenuState.h>

using EssexEngine::Core::Models::IState;
using EssexEngine::Daemons::FileSystem::IFileBuffer;

using EssexEngine::Daemons::FileSystem::FileSystemDaemon;
using EssexEngine::Daemons::Json::JsonDaemon;

using EssexEngine::Apps::Game::MainMenuState;
using EssexEngine::Apps::Game::MapState;

MainMenuState::MainMenuState(WeakPointer<Context> _context): State(_context),
mapState(
    UniquePointer<MapState>()
) {}

MainMenuState::~MainMenuState() {}

void MainMenuState::Setup() {
    //load game config file
    CachedPointer<std::string, IFileBuffer> gameFile =
        context->GetDaemon<FileSystemDaemon>()->ReadFile(GAME_FILE_LOCATION);
    context->GetDaemon<JsonDaemon>()->GetJsonDocument(
        gameFile.ToWeakPointer()
    ).swap(gameDocument);

    //load initial map from game config
    std::string mapName = context->GetDaemon<JsonDaemon>()->GetStringFromNode(
        gameDocument.ToWeakPointer(),
        "initialMap"
    );
    CachedPointer<std::string, IFileBuffer> mapFile =
        context->GetDaemon<FileSystemDaemon>()->ReadFile(mapName);
    context->GetDaemon<JsonDaemon>()->GetJsonDocument(
        mapFile.ToWeakPointer()
    ).swap(mapDocument);
    
    //load MapState with the initial map.
    mapState.Replace(
        new MapState(
            context,
            gameDocument.ToWeakPointer(),
            mapDocument.ToWeakPointer()
        )
    );
    context->GetStateStack()->Push(mapState.ToWeakPointer().Cast<IState>());
}

void MainMenuState::Logic() {
    completed = true;
}

void MainMenuState::Render() {
}

bool MainMenuState::PauseUnder() {
    return false;
}
