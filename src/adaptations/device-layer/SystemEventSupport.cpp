/*
 *
 *    Copyright (c) 2018 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Provides implementations of the Weave System Layer platform
 *          event functions that are suitable for use on all platforms.
 */

#include <Weave/DeviceLayer/internal/WeaveDeviceLayerInternal.h>
#include <Weave/DeviceLayer/PlatformManager.h>

namespace nl {
namespace Weave {
namespace System {
namespace Platform {
namespace Layer {

using namespace ::nl::Weave::DeviceLayer;

System::Error PostEvent(System::Layer & aLayer, void * aContext, System::Object & aTarget, System::EventType aType, uintptr_t aArgument)
{
    WeaveDeviceEvent event;
    event.Type = DeviceEventType::kWeaveSystemLayerEvent;
    event.WeaveSystemLayerEvent.Type = aType;
    event.WeaveSystemLayerEvent.Target = &aTarget;
    event.WeaveSystemLayerEvent.Argument = aArgument;

    PlatformMgr().PostEvent(&event);

    return WEAVE_SYSTEM_NO_ERROR;
}

System::Error DispatchEvents(Layer & aLayer, void * aContext)
{
    PlatformMgr().RunEventLoop();

    return WEAVE_SYSTEM_NO_ERROR;
}

System::Error DispatchEvent(System::Layer & aLayer, void * aContext, const WeaveDeviceEvent * aEvent)
{
    PlatformMgr().DispatchEvent(aEvent);

    return WEAVE_SYSTEM_NO_ERROR;
}

} // namespace Layer
} // namespace Platform
} // namespace System
} // namespace Weave
} // namespace nl
