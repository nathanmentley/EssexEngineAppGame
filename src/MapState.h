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

#include <EssexEngineCore/State.h>

#include <EssexEngineLibIsoMap/Map.h>

#include <EssexEngineAppGame/Daemons.h>

namespace EssexEngine{
namespace Apps{
namespace Game{
    class MapState:public Core::Models::State
    {
        public:
            MapState(
                WeakPointer<Context> _context,
                WeakPointer<Core::IApp> _app,
                WeakPointer<Daemons::Json::IJsonDocument> _gameDocument,
                WeakPointer<Daemons::Json::IJsonDocument> _mapDocument,
                WeakPointer<Daemons::Window::IRenderContext> _renderContext
            );
            ~MapState();
            
            //override
            void Setup();
            void Logic();
            void Render();
            bool PauseUnder();
        private:
            UniquePointer<Libs::IsoMap::Map> map;
            UniquePointer<Daemons::Gfx::IFont> font;
            WeakPointer<Daemons::Window::IRenderContext> renderContext;

            int counter;
    };
}}};
