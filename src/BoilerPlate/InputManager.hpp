#pragma once
#pragma once

#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include "Entity.hpp"
#include "Vector2.hpp"
#include <vector>


class InputManager
{
public:

	InputManager();

	void SetW(bool);
	void SetA(bool);
	void SetS(bool);
	void SetD(bool);
	void SetQ(bool);
	void SetE(bool);
	void SetF(bool);
	void SetR(bool);
	void SetZ(bool);
	void SetSpace(bool);

	bool GetW();
	bool GetA();
	bool GetS();
	bool GetD();
	bool GetQ();
	bool GetE();
	bool GetF();
	bool GetR();
	bool GetZ();
	bool GetSpace();


private:

	bool W_KEY;
	bool A_KEY;
	bool S_KEY;
	bool D_KEY;
	bool Q_KEY;
	bool E_KEY;
	bool F_KEY;
	bool R_KEY;
	bool Z_KEY;
	bool SPACE_KEY;

	

};

#endif