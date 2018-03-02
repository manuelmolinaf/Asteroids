#include "InputManager.hpp"

InputManager::InputManager()
{
	W_KEY = false;
	A_KEY = false;
	S_KEY = false;
	D_KEY = false;
	Q_KEY = false;
	E_KEY = false;
	F_KEY = false;
	R_KEY = false;
	Z_KEY = false;
	G_KEY = false;
	ENTER_KEY = false;
	SPACE_KEY = false;
}

void InputManager::SetW(bool value)
{
	W_KEY = value;
}

void InputManager::SetA(bool value)
{
	A_KEY = value;
}

void InputManager::SetS(bool value)
{
	S_KEY = value;
}

void InputManager::SetD(bool value)
{
	D_KEY = value;
}

void InputManager::SetQ(bool value)
{
	Q_KEY = value;
}

void InputManager::SetE(bool value)
{
	E_KEY = value;
}

void InputManager::SetF(bool value)
{
	F_KEY = value;
}

void InputManager::SetR(bool value)
{
	R_KEY = value;
}

void InputManager::SetZ(bool value)
{
	Z_KEY = value;
}

void InputManager::SetG(bool value)
{
	G_KEY = value;
}

void InputManager::SetENTER(bool value)
{
	ENTER_KEY = value;
}

void InputManager::SetSPACE(bool value)
{
	SPACE_KEY = value;
}





bool InputManager::W_IsPressed()
{
	return W_KEY;
}

bool InputManager::A_IsPressed()
{
	return A_KEY;
}

bool InputManager::S_IsPressed()
{
	return S_KEY;
}

bool InputManager::D_IsPressed()
{
	return D_KEY;
}

bool InputManager::Q_IsPressed()
{
	return Q_KEY;
}

bool InputManager::E_IsPressed()
{
	return E_KEY;
}

bool InputManager::F_IsPressed()
{
	return F_KEY;
}

bool InputManager::R_IsPressed()
{
	return R_KEY;
}

bool InputManager::Z_IsPressed()
{
	return Z_KEY;
}

bool InputManager::G_IsPressed()
{
	return G_KEY;
}

bool InputManager::ENTER_IsPrerssed()
{
	return ENTER_KEY;
}

bool InputManager::SPACE_IsPressed()
{
	return SPACE_KEY;
}




