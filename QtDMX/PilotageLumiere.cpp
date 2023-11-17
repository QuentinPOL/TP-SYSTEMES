//*********************************************************************************************
//* Programme : PilotageLumiere.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 17/11/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Faire l'impl�mentation des m�thodes / constructeur / constructeur de la classe PilotageLumiere
//* Programmes associ�s : PilotageLumiere.h (fichier ent�te de la classe PilotageLumiere)
//*********************************************************************************************

#include "PilotageLumiere.h"

//---------------------------------------------------------------------------------------------
//* Constructeur de la classe PilotageLumiere qui permet de cr�er l'objet PilotageLumiere
//-------------------------------------------------------------------------------------------
PilotageLumiere::PilotageLumiere()
{}

//---------------------------------------------------------------------------------------------
//* Destructeur de la classe PilotageLumiere qui permet de d�truire l'objet PilotageLumiere
//-------------------------------------------------------------------------------------------
PilotageLumiere::~PilotageLumiere()
{}

//---------------------------------------------------------------------------------------------
//* Fonction qui fait le changement de couleur de l'adresse de la lampe en question et qui le met directement dans la trame DMX par rapport au MODE DMX rentrer dans l'interface
//-------------------------------------------------------------------------------------------
void PilotageLumiere::setColor(int redValue, int greenValue, int blueValue, int whiteValue, int adresseLumiere, int dmxMode, unsigned char dmxBlock[])
{
	// ALORS ON VA CONSTRUIRE LA TRAME  AVEC LES COULEURS ETC PAR RAPPORT AU MODE DMX AINSI QUA L ADRESSE DE LA LUMIERE
	dmxBlock[adresseLumiere-1] = redValue;
	dmxBlock[adresseLumiere] = greenValue;
	dmxBlock[adresseLumiere + 1] = blueValue;
	dmxBlock[adresseLumiere + 2] = whiteValue;
}