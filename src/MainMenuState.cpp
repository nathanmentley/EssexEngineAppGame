/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineAppGame/MainMenuState.h>

using EssexEngine::Core::IApp;
using EssexEngine::Core::Models::IState;

using EssexEngine::Daemons::FileSystem::IFileBuffer;
using EssexEngine::Daemons::Window::IRenderContext;

using EssexEngine::Daemons::FileSystem::FileSystemDaemon;
using EssexEngine::Daemons::Json::JsonDaemon;

using EssexEngine::Apps::Game::MainMenuState;
using EssexEngine::Apps::Game::MapState;

MainMenuState::MainMenuState(
    WeakPointer<Context> _context,
    WeakPointer<IApp> _app,
    WeakPointer<IRenderContext> _renderContext
): State(_context, _app),
mapState(
    UniquePointer<MapState>()
) {
    renderContext = _renderContext;
}

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
            app,
            gameDocument.ToWeakPointer(),
            mapDocument.ToWeakPointer(),
            renderContext
        )
    );
    app->GetStateStack()->Push(mapState.ToWeakPointer().Cast<IState>());
}

void MainMenuState::Logic() {
    completed = true;
}

void MainMenuState::Render() {
}

bool MainMenuState::PauseUnder() {
    return false;
}
