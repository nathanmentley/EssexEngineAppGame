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

#include <EssexEngineCore/BaseApp.h>
#include <EssexEngineAppGame/MainMenuState.h>

#include <iostream>

namespace EssexEngine{
namespace Apps{
namespace Game{
    class GameApp: public Core::BaseApp
    {
        public:
            GameApp(WeakPointer<Context> context): BaseApp(context),
                windowDef(
                    UniquePointer<Daemons::Window::WindowDef>(
                        new Daemons::Window::WindowDef(
                            "Game Window",
                            100,
                            100,
                            context->GetDaemon<Daemons::Config::ConfigDaemon>()->GetScreenWidth(),
                            context->GetDaemon<Daemons::Config::ConfigDaemon>()->GetScreenHeight(),
                            [this]() {
                                while(!GetStateStack()->IsEmpty()) {
                                    GetStateStack()->Pop();
                                }
                            }
                        )
                    )
                ), canvasDef(
                    UniquePointer<Daemons::Window::CanvasDef>(
                        new Daemons::Window::CanvasDef(
                            0,
                            0,
                            context->GetDaemon<Daemons::Config::ConfigDaemon>()->GetScreenWidth(),
                            context->GetDaemon<Daemons::Config::ConfigDaemon>()->GetScreenHeight()
                        )
                    )
                ), mainWindow(
                    context->GetDaemon<Daemons::Window::WindowDaemon>()->CreateWindow(
                        windowDef.ToWeakPointer()
                    )
                ), mainRenderContext(
                    context->GetDaemon<Daemons::Window::WindowDaemon>()->AddCanvas(
                        mainWindow.ToWeakPointer(),
                        canvasDef.ToWeakPointer()
                    )
                ),
                initState(
                    UniquePointer<MainMenuState>(
                        new MainMenuState(
                            context,
                            WeakPointer<Core::IApp>(this),
                            mainRenderContext.ToWeakPointer()
                        )
                    )
                )
                {
                    context->GetDaemon<Core::Logging::LogDaemon>()->LogLine(
                        "Starting Starting App [%s] [%s]",
                        GetAppName().c_str(),
                        GetAppVersion().c_str()
                    );
                    
                    context->GetDaemon<Daemons::Sfx::SfxDaemon>()->SetupSfx();
                    context->GetDaemon<Daemons::Gfx::GfxDaemon>()->SetupGfx();
                    context->GetDaemon<Daemons::Gfx::GfxDaemon>()->SetupRenderContext(mainRenderContext.ToWeakPointer());
                    
                    GetStateStack()->Push(GetInitState());
                }
            ~GameApp() {}

            std::string GetAppName() { return "Game"; }
            std::string GetAppVersion() { return ESSEX_ENGINE_VERSION; }

            WeakPointer<Core::Models::IState> GetInitState() { return initState.ToWeakPointer().Cast<Core::Models::IState>(); };

            void Execute() {
                bool doLogic = false;
                bool doRedraw = false;

                context->GetDaemon<Daemons::System::SystemDaemon>()->StartTimer();
                
                while(!GetStateStack()->IsEmpty()) {
                    context->GetDaemon<Daemons::Window::WindowDaemon>()->RepaintWindows();

                    int milliseconds = context->GetDaemon<Daemons::System::SystemDaemon>()->GetElapsedTime();
                    if (milliseconds >= 16) {
                        doLogic = true;
                        doRedraw = true;
                        context->GetDaemon<Daemons::System::SystemDaemon>()->StartTimer();
                    } else {
                        doRedraw = true;
                        context->GetDaemon<Daemons::System::SystemDaemon>()->Sleep(1);
                    }
                    
                    if(doLogic) {
                        for(int i = GetStateStack()->GetLength() - 1; i >= 0; i--) {
                            GetStateStack()->GetRawData()[i]->Logic();
                            
                            if(GetStateStack()->GetRawData()[i]->PauseUnder()) {
                                break;
                            }
                        }
                        doLogic = false;
                    }
                    
                    if(doRedraw) {
                        context->GetDaemon<Daemons::Gfx::GfxDaemon>()->StartRender(mainRenderContext.ToWeakPointer());
                    
                        for(int i = GetStateStack()->GetLength() - 1; i >= 0; i--) {
                            GetStateStack()->GetRawData()[i]->Render();
                            
                            if(GetStateStack()->GetRawData()[i]->PauseUnder()) {
                                break;
                            }
                        }
                    
                        context->GetDaemon<Daemons::Gfx::GfxDaemon>()->FinishRender(mainRenderContext.ToWeakPointer());
                        context->GetDaemon<Daemons::Window::WindowDaemon>()->RepaintCanvas(mainRenderContext.ToWeakPointer());
                        
                        doRedraw = false;
                    }
                    
                    //check if state is complete.
                    if(GetStateStack()->TopStateComplete()) {
                        GetStateStack()->Pop();
                    }
                }
            }
        private:
            UniquePointer<Daemons::Window::WindowDef> windowDef;
            UniquePointer<Daemons::Window::CanvasDef> canvasDef;
            UniquePointer<Daemons::Window::IWindow> mainWindow;
            UniquePointer<Daemons::Window::IRenderContext> mainRenderContext;
            
            UniquePointer<MainMenuState> initState;
    };
}}};
