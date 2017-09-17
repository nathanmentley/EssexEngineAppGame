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

EssexEngine::Apps::Game::MainMenuState::MainMenuState(WeakPointer<Context> _context)
:State(_context) {
}

EssexEngine::Apps::Game::MainMenuState::~MainMenuState() {}

void EssexEngine::Apps::Game::MainMenuState::Setup() {
    gameFile = context->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(GAME_FILE_LOCATION);
    
    gameDocument = context->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonDocument(gameFile);

    std::string mapName = context->GetDaemon<Daemons::Json::JsonDaemon>()->GetStringFromNode(gameDocument, "initialMap");
    
    mapFile = context->GetDaemon<Daemons::FileSystem::FileSystemDaemon>()->ReadFile(mapName);
    
    mapDocument = context->GetDaemon<Daemons::Json::JsonDaemon>()->GetJsonDocument(mapFile);
    
    context->GetStateStack()->Push(new MapState(context, gameDocument.GetWeakPointer(), mapDocument.GetWeakPointer()));
}

void EssexEngine::Apps::Game::MainMenuState::Logic() {
    completed = true;
}

void EssexEngine::Apps::Game::MainMenuState::Render() {
}

bool EssexEngine::Apps::Game::MainMenuState::PauseUnder() {
    return false;
}
