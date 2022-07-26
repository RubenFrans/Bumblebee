#pragma once
#pragma comment(lib, "xinput.lib")
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <vector>
#include "Input/Commands/Command.h"
#include <memory>
#include "Input/Controllers/XboxController.h"
#include "Input/Commands/Command.h"
#include "Input/Controllers/ControllerButtons.h"
#include "Singleton.h"

namespace BTEngine {
	class Keyboard;
}

class InputManager : public BTEngine::Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();
	bool ProcessInput();

	void AddButtonMapping(ControllerButton btn, std::shared_ptr<Command> command, ButtonBehaviour behv);
	void AddButtonMapping(ControllerButton btn, std::shared_ptr<Command> command, ButtonBehaviour behv, int controllerId);

	void AddKeyboardMapping(KeyboardButton btn, std::shared_ptr<Command> command, ButtonBehaviour behv);

private:
	void CheckPressed();
	void CheckDownThisFrame() const;
	void CheckUpThisFrame() const;

	const int m_AmountOfControllers{ 4 };
	std::vector<XboxController*> m_Controllers{};
	BTEngine::Keyboard* m_pKeyboard;
};
