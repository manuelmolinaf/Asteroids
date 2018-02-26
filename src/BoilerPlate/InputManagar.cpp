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

void InputManager::SetSpace(bool value)
{
	SPACE_KEY = value;
}




bool InputManager::GetW()
{
	return W_KEY;
}

bool InputManager::GetA()
{
	return A_KEY;
}

bool InputManager::GetS()
{
	return S_KEY;
}

bool InputManager::GetD()
{
	return D_KEY;
}

bool InputManager::GetQ()
{
	return Q_KEY;
}

bool InputManager::GetE()
{
	return E_KEY;
}

bool InputManager::GetF()
{
	return F_KEY;
}

bool InputManager::GetR()
{
	return R_KEY;
}

bool InputManager::GetZ()
{
	return Z_KEY;
}

bool InputManager::GetSpace()
{
	return SPACE_KEY;
}




