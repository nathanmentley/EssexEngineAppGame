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

#include <EssexEngineCore/Context.h>
#include <EssexEngineAppGame/GameApp.h>

using EssexEngine::Context;
using EssexEngine::WeakPointer;
using EssexEngine::Core::BaseApp;

using EssexEngine::Apps::Game::GameApp;

extern "C" {
    void app_init(WeakPointer<Context> context) {
        context->RegisterApp(new GameApp(context));
    }
}
