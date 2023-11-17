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
//* Programmes associ�s : Aucun
//*********************************************************************************************

class PilotageLumiere
{
public:
	PilotageLumiere();
	~PilotageLumiere();

	// Changer de couleur
	void setColor(int redValue, int greenValue, int blueValue, int whiteValue, int adresseLumiere, int dmxMode, unsigned char dmxBlock[]);
};