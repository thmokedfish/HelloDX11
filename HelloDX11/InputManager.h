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
		InputManager() {}
	public:
		static InputManager^ GetInstance()
		{
			static InputManager^ instance = ref new InputManager();
			return instance;
		}
		static bool GetKey(Windows::System::VirtualKey key);
		void Init(_In_ Windows::UI::Core::CoreWindow^ window);
		void OnKeyDown(_In_ Windows::UI::Core::CoreWindow^ sender,
			_In_ Windows::UI::Core::KeyEventArgs^ args);

		void OnKeyUp(
			_In_ Windows::UI::Core::CoreWindow^ sender,
			_In_ Windows::UI::Core::KeyEventArgs^ args
		);


	};
}