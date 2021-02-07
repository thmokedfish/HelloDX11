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

    float InputManager::GetMouseX()
    {
        if (GetInstance()->mouseXorigin)
        {
            return *GetInstance()->mouseXorigin - GetInstance()->mouseX;
        }
        return 0;
    }
    float InputManager::GetMouseY()
    {
        if (GetInstance()->mouseXorigin)
        {
            return *GetInstance()->mouseYorigin - GetInstance()->mouseY;
        }
        return 0;
    }
    
	void InputManager::Init(_In_ Windows::UI::Core::CoreWindow^ window)
	{
        window->KeyDown +=
            ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputManager::OnKeyDown);

        window->KeyUp +=
            ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputManager::OnKeyUp);
        window->PointerMoved +=
            ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputManager::OnPointerMoved);
	}
    void InputManager::OnPointerMoved(
        _In_ Windows::UI::Core::CoreWindow^ sender,
        _In_ Windows::UI::Core::PointerEventArgs^ args)
    {
        mouseX = args->CurrentPoint->Position.X;
        mouseY = args->CurrentPoint->Position.Y;
        if (mouseXorigin == nullptr) { mouseXorigin=std::make_unique<float>( mouseX); }
        if (mouseYorigin == nullptr) { mouseYorigin = std::make_unique <float>(mouseY); }
        //mousePosition= DirectX::XMFLOAT2(args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y);
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
