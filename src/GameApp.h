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
#pragma once

#include <EssexEngineCore/BaseApp.h>

namespace EssexEngine{
namespace Apps{
namespace Game{
    class GameApp: public Core::BaseApp
    {
        public:
            GameApp(Core::Models::IState* _initState): BaseApp(_initState) { }
            ~GameApp() {}
            std::string GetAppName() { return "Game"; }
            std::string GetAppVersion() { return ESSEX_ENGINE_VERSION; }
    };
}}};
