#pragma once

//*********************************************************************************************
//* Programme : PilotageLumiere.h                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 17/11/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Créer la classe PilotageLumiere et déclarer les méthodes / constructeur / desctructeur de celle-ci
//* Programmes associés : Aucun
//*********************************************************************************************

class PilotageLumiere
{
public:
	PilotageLumiere();
	~PilotageLumiere();

	// Changer de couleur
	void setColor(int redValue, int greenValue, int blueValue, int whiteValue, int adresseLumiere, int dmxMode, unsigned char dmxBlock[]);
};