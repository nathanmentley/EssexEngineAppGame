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

#include <EssexEngineAppGame/MapState.h>

using EssexEngine::UniquePointer;

using EssexEngine::Core::IApp;

using EssexEngine::Daemons::Json::IJsonDocument;
using EssexEngine::Daemons::Input::KeyboardButton::InputKeys;
using EssexEngine::Daemons::Gfx::IFont;
using EssexEngine::Daemons::Window::IRenderContext;

using EssexEngine::Daemons::Input::InputDaemon;
using EssexEngine::Daemons::FileSystem::FileSystemDaemon;
using EssexEngine::Daemons::Sfx::SfxDaemon;
using EssexEngine::Daemons::Gfx::GfxDaemon;

using EssexEngine::Libs::IsoMap::Map;
using EssexEngine::Libs::IsoMap::MapCharacterActionTypes;
using EssexEngine::Libs::IsoMap::CharacterAnimations;

using EssexEngine::Apps::Game::MapState;

MapState::MapState(
    WeakPointer<Context> _context,
    WeakPointer<IApp> _app,
    WeakPointer<IJsonDocument> _gameDocument,
    WeakPointer<IJsonDocument> _mapDocument,
    WeakPointer<IRenderContext> _renderContext
):State(_context, _app),
map(
    UniquePointer<Map>(
        new Map(
            _context,
            _renderContext,
            _gameDocument,
            _mapDocument
        )
    )
),
font(
    UniquePointer<IFont>()
) {
    font.Replace(
        context->GetDaemon<GfxDaemon>()->GetFont(
            _renderContext,
            context->GetDaemon<FileSystemDaemon>()->ReadFile("content/root/Fonts/Roboto-Thin.ttf"),
            48
        )        
    );
    
    renderContext = _renderContext;
    counter = 0;
}

MapState::~MapState(){}

void MapState::Setup() {}

void MapState::Logic() {
    //set x / y position
    map->SetScreenX(map->GetCharacter()->GetX());
    map->SetScreenY(map->GetCharacter()->GetY());

    context->GetDaemon<SfxDaemon>()->SetAudioListenerLocation(
        map->GetCharacter()->GetX(),
        map->GetCharacter()->GetY(),
        0
    );
    
    //Listen to Actions.
    if (context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Space)) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::Attack);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Left) &&
        context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Up)
    ) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveNorthWest);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Right) &&
        context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Up)
    ) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveNorthEast);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Left) &&
        context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Down)
    ) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveSouthWest);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Right) &&
        context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Down)
    ) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveSouthEast);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Left)) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveWest);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Right)) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveEast);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Up)) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveNorth);
    } else if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Down)) {
        map->GetCharacter()->QueueAction(MapCharacterActionTypes::MoveSouth);
    } else {
        map->GetCharacter()->SetAnimation(CharacterAnimations::Stance);
    }
    
    if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Plus)) {
        map->ZoomIn();
    }
    if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Minus)) {
        map->ZoomOut();
    }
    if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Esc)) {
        this->completed = true;
    }
    
    if(context->GetDaemon<InputDaemon>()->IsKeyPressed(renderContext, InputKeys::Tilde)) {
        //showDebugConsole = !showDebugConsole;
    }
    
    //Update Map;
    map->Update();
}

void MapState::Render() {
    counter++;
    map->Render();

    char buffer[255];
    sprintf(buffer, "%d", counter);

    context->GetDaemon<GfxDaemon>()->RenderString(
        renderContext,
        font.ToWeakPointer(),
        buffer,
        10,
        10
    );
}

bool MapState::PauseUnder() {
    return true;
}
