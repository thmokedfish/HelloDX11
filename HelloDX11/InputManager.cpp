#include "pch.h"
#include"InputManager.h"
using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Windows::Devices::Input;
using namespace Windows::System;
namespace HelloDX11
{
    bool InputManager::GetKey(VirtualKey key){
        return GetInstance()->activeKey[key];
	}
	void InputManager::Init(_In_ Windows::UI::Core::CoreWindow^ window)
	{
        window->KeyDown +=
            ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputManager::OnKeyDown);

        window->KeyUp +=
            ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputManager::OnKeyUp);

	}

	void InputManager::OnKeyDown(_In_ Windows::UI::Core::CoreWindow^ sender,
		_In_ Windows::UI::Core::KeyEventArgs^ args)
	{
        activeKey[args->VirtualKey] = true;
        
        /*
        typedef void(*funcp)();
        int count = keyEvents[args->VirtualKey].size();
        for (int i = 0; i < count; ++i)
        {
           static_cast<funcp>(keyEvents[args->VirtualKey][i])();
        }
        */
	}
    void InputManager::OnKeyUp(
        _In_ Windows::UI::Core::CoreWindow^ sender,
        _In_ Windows::UI::Core::KeyEventArgs^ args
    )
    {

        activeKey[args->VirtualKey] = false;
        /*
        typedef void(*funcp)();
        int count = keyEvents[args->VirtualKey].size();
        for (int i = 0; i < count; ++i)
        {
            static_cast<funcp>(keyEvents[args->VirtualKey][i])();
        }
        */
    }



}
