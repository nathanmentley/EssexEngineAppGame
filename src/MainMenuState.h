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
#pragma once

#include <string>

#include <EssexEngineCore/State.h>
#include <EssexEngineGfxDaemon/Entity.h>

#include <EssexEngineLibIsoMap/Map.h>

#include <EssexEngineAppGame/Daemons.h>
#include <EssexEngineAppGame/MapState.h>

namespace EssexEngine{
namespace Apps{
namespace Game{
    class MainMenuState:public MapState::State
    {
        public:
            MainMenuState(WeakPointer<Context> _context);
            ~MainMenuState();
            
            //override
            void Setup();
            void Logic();
            void Render();
            bool PauseUnder();
        private:
            UniquePointer<Daemons::Json::IJsonDocument> gameDocument;
            UniquePointer<Daemons::Json::IJsonDocument> mapDocument;

            UniquePointer<MapState> mapState;
    };
}}};
