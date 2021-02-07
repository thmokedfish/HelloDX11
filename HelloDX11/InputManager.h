#pragma once
#include "pch.h"
#include<Windows.h>
#include<unordered_map>
#include<vector>
namespace HelloDX11
{
	ref class InputManager
	{
	private:
		//typedef void(*funcp)();
		std::unordered_map<Windows::System::VirtualKey, std::vector<void*>> keyEvents;
		std::unordered_map<Windows::System::VirtualKey, bool> activeKey;
		InputManager():mouseXorigin(nullptr),mouseYorigin(nullptr) {}
		float mouseX; float mouseY;
		std::unique_ptr <float> mouseXorigin;
		std::unique_ptr <float> mouseYorigin;
	public:
		static InputManager^ GetInstance()
		{
			static InputManager^ instance = ref new InputManager();
			return instance;
		}
		static bool GetKey(Windows::System::VirtualKey key);
		static float GetMouseX();
		static float GetMouseY();
		void Init(_In_ Windows::UI::Core::CoreWindow^ window); 
		void OnPointerMoved(
			_In_ Windows::UI::Core::CoreWindow^ sender,
			_In_ Windows::UI::Core::PointerEventArgs^ args
		);

		void OnKeyDown(_In_ Windows::UI::Core::CoreWindow^ sender,
			_In_ Windows::UI::Core::KeyEventArgs^ args);

		void OnKeyUp(
			_In_ Windows::UI::Core::CoreWindow^ sender,
			_In_ Windows::UI::Core::KeyEventArgs^ args
		);
		

	};
}