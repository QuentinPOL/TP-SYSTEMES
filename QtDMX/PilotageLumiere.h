#pragma once

//*********************************************************************************************
//* Programme : PilotageLumiere.h                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 17/11/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Cr�er la classe PilotageLumiere et d�clarer les m�thodes / constructeur / desctructeur de celle-ci
//* Programmes associ�s : DashHard.h / Windows.h
//*********************************************************************************************

#include <iostream>
#include <vector>

#include <Windows.h>
#include "DashHard.h"

#define DMX_MAXCHANNEL 512

class PilotageLumiere
{
private:
	int adressLight;
	int redValue;
	int greenValue;
	int blueValue;
	int whiteValue;
	int timer;

	HINSTANCE g_dasusbdll;
	typedef int (*DASHARDCOMMAND)(int, int, unsigned char*);
	DASHARDCOMMAND DasUsbCommand;

	int interface_open;
	unsigned char dmxBlock[512];

public:
	PilotageLumiere(int adressValue, int red, int green, int blue, int white, int timer);
	~PilotageLumiere();

	//Getteur
	int getTimer();

	// Setteur
	void setAdressValue(int newValue);
	void setRedValue(int newValue);
	void setGreenValue(int newValue);
	void setBlueValue(int newValue);
	void setWhiteValue(int newValue);

	// BOOLEAN
	int isInterfaceOpen();

	// Envoie d'une trame
	void sendTrame();
};