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

#include <EssexEngineCore/BaseMessage.h>
#include <EssexEngineCore/IMessageResponse.h>
#include <EssexEngineCore/WeakPointer.h>

#include <EssexEngineWindowDaemon/IRenderContext.h>

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
    namespace Messages {
        enum MessageType {
            SetupGfx = 1,
            SetupRenderContext = 2,
            StartRender = 3,
            FinishRender = 4,
            RenderEntity = 5,
            RenderModel = 6,
            RenderString = 7
        };
    }

    class GfxDaemonMessageResponse: public Core::Models::IMessageResponse
    {

    };

    class GfxDaemonMessage: public Core::Models::BaseMessage<GfxDaemonMessageResponse>
    {
        public:
            GfxDaemonMessage(
                Messages::MessageType _type,
                WeakPointer<Window::IRenderContext> _target,
                WeakPointer<void> _data = WeakPointer<void>(),
                Nullable<std::string> _message = Nullable<std::string>(),
                Nullable<int> _x = Nullable<int>(),
                Nullable<int> _y = Nullable<int>()
            ):
            Core::Models::BaseMessage<GfxDaemonMessageResponse>() {
                type = _type;
                target = _target;
                data = _data;

                message = _message;
                x = _x;
                y = _y;
            }

            int GetType() {
                return type;
            }
            
            WeakPointer<Window::IRenderContext> GetTarget() {
                return target;
            }

            WeakPointer<void> GetData() {
                return data;
            }

            Nullable<std::string> GetMessage() {
                return message;
            }

            Nullable<int> GetX() {
                return x;
            }

            Nullable<int> GetY() {
                return y;
            }
        private:
            Messages::MessageType type;
            WeakPointer<Window::IRenderContext> target;
            WeakPointer<void> data;
            Nullable<std::string> message;
            Nullable<int> x;
            Nullable<int> y;
    };
}}};

