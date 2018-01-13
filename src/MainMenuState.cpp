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

#include <EssexEngineCore/imgui.h>

#include <stdio.h>

EssexEngine::Apps::Game::MainMenuState::MainMenuState(WeakPointer<Context> _context)
:State(_context) {
}

EssexEngine::Apps::Game::MainMenuState::~MainMenuState() {}

void EssexEngine::Apps::Game::MainMenuState::Setup() {
    CachedPointer<std::string, Daemons::FileSystem::IFileBuffer> gameFile = context->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(GAME_FILE_LOCATION);
    
    context->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonDocument(
        gameFile.ToWeakPointer()
    ).swap(gameDocument);

    std::string mapName = context->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(
        gameDocument.ToWeakPointer(),
        "initialMap"
    );
    
    CachedPointer<std::string, Daemons::FileSystem::IFileBuffer> mapFile = context->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(mapName);
    
    context->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonDocument(
        mapFile.ToWeakPointer()
    ).swap(mapDocument);
    
    context->GetStateStack()->Push(
        new MapState(
            context,
            gameDocument.ToWeakPointer(),
            mapDocument.ToWeakPointer()
        )
    );
}

void EssexEngine::Apps::Game::MainMenuState::Logic() {
    completed = true;
}

void EssexEngine::Apps::Game::MainMenuState::Render() {
}

bool EssexEngine::Apps::Game::MainMenuState::PauseUnder() {
    return false;
}
