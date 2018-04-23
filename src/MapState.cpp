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

#include <EssexEngineAppGame/MapState.h>

EssexEngine::Apps::Game::MapState::MapState(WeakPointer<Context> _context, WeakPointer<Daemons::Json::IJsonDocument> _gameDocument, WeakPointer<Daemons::Json::IJsonDocument> _mapDocument)
:State(_context) {
    gameDocument = _gameDocument;
    mapDocument = _mapDocument;
}

EssexEngine::Apps::Game::MapState::~MapState()
{
    delete map;
}

void EssexEngine::Apps::Game::MapState::Setup() {
    //setup map.
    map = new Libs::IsoMap::Map(context, gameDocument, mapDocument);
}

void EssexEngine::Apps::Game::MapState::Logic() {
    //set x / y position
    map->SetScreenX(map->GetCharacter()->GetX());
    map->SetScreenY(map->GetCharacter()->GetY());
    
    //Listen to Actions.
    if (context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Space)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::Attack, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Left) && context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Up)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveNorthWest, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Right) && context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Up)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveNorthEast, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Left) && context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Down)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveSouthWest, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Right) && context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Down)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveSouthEast, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Left)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveWest, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Right)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveEast, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Up)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveNorth, 0));
    } else if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Down)) {
        map->GetCharacter()->QueueAction(new Libs::IsoMap::MapCharacterAction(Libs::IsoMap::MoveSouth, 0));
    } else {
        map->GetCharacter()->SetAnimation(Libs::IsoMap::Stance);
    }
    
    if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Plus)) {
        map->ZoomIn();
    }
    if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Minus)) {
        map->ZoomOut();
    }
    if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Esc)) {
        this->completed = true;
    }
    
    if(context->GetDaemon<Daemons::Input::InputDaemon>()->IsKeyPressed(Daemons::Input::KeyboardButton::Tilde)) {
        //showDebugConsole = !showDebugConsole;
    }
    
    //Update Map;
    map->Update();
}

void EssexEngine::Apps::Game::MapState::Render() {
    map->Render(context->GetDaemon<Daemons::Gfx::GfxDaemon>()->GetPrimaryRenderContext());
    context->GetDaemon<Daemons::Gfx::GfxDaemon>()->RenderString(context->GetDaemon<Daemons::Gfx::GfxDaemon>()->GetPrimaryRenderContext(), "test", 100, 100);
}

bool EssexEngine::Apps::Game::MapState::PauseUnder() {
    return true;
}
