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
// On inialise aussi la dll ainsi que l'interface usb avec les commandes 
// Enfin on finira aussi par mettre les diff�rents valeurs qu'il nous faut pour piloter les lumieres dans leurs attributs ainsi que le time pour l'envoie de trame
// 
//-------------------------------------------------------------------------------------------
PilotageLumiere::PilotageLumiere(int adressValue, int red, int green, int blue, int white, int timer)
{
	this->adressLight = adressValue;
	this->redValue = red;
	this->greenValue = green;
	this->blueValue = blue;
	this->whiteValue = white;
	this->timer = timer;
	DasUsbCommand = nullptr;
	interface_open = 0;

	//Chargement de la DLL
	g_dasusbdll = LoadLibraryA("C:\\Users\\Quentin Pollet\\source\\repos\\QtDMX\\DasHard2006.dll");

	//Verification du chargement
	if (g_dasusbdll)
	{
		DasUsbCommand = (DASHARDCOMMAND)::GetProcAddress((HMODULE)g_dasusbdll, "DasUsbCommand");

		//Initialisation de la DLL
		interface_open = DasUsbCommand(DHC_INIT, 0, NULL);

		//On ouvre la liaison avec l'interface USB -1 si on ne trouve pas le port USB
		//retourn DHC-OK = 1 si USB connecter
		interface_open = DasUsbCommand(DHC_OPEN, 0, 0);
	}

	// Parametre : Commande DHC_DMXOUT, Taille Block 512 , Trame dmxbloc Pointeur
	// dmxBlock[512] est declarer en global dans le .h mais il faut creer la trame
	for (int i = 0; i < DMX_MAXCHANNEL; i++)
		dmxBlock[i] = 0;

}

//---------------------------------------------------------------------------------------------
//* Destructeur de la classe PilotageLumiere qui permet de d�truire l'objet PilotageLumiere et fermer l'interface usb des commandes ainsi que la DLL
//-------------------------------------------------------------------------------------------
PilotageLumiere::~PilotageLumiere()
{
	//Fermeture du DMX � l'arret du programme
	if (interface_open > 0) {
		DasUsbCommand(DHC_CLOSE, 0, 0);
		DasUsbCommand(DHC_EXIT, 0, NULL);
	}
	if (g_dasusbdll != NULL)
		FreeLibrary(g_dasusbdll);
}


int PilotageLumiere::isInterfaceOpen()
{
	return interface_open;
}

void PilotageLumiere::setAdressValue(int newValue)
{
	this->adressLight = newValue;
}

void PilotageLumiere::setRedValue(int newValue)
{
	this->redValue = newValue;
}

void PilotageLumiere::setGreenValue(int newValue)
{
	this->greenValue = newValue;
}

void PilotageLumiere::setBlueValue(int newValue)
{
	this->blueValue = newValue;
}

void PilotageLumiere::setWhiteValue(int newValue)
{
	this->whiteValue = newValue;
}

int PilotageLumiere::getTimer()
{
	return timer;
}

//---------------------------------------------------------------------------------------------
//* Envoie de la trame DMX (avec le positionnnement des couleurs gr�ce au canal DMX, l'adresse de la lumi�re en question ainsi que la trame et les valeurs des couleurs de celle-ci
// ensuite une fois que l'on aura construit la trame il nous faudra l'envoyer en commande usb avec DasUsbCommand
//-------------------------------------------------------------------------------------------
void PilotageLumiere::sendTrame()
{
	// ALORS ON VA CONSTRUIRE LA TRAME  AVEC LES COULEURS ETC PAR RAPPORT AU MODE DMX AINSI QUA L ADRESSE DE LA LUMIERE
	dmxBlock[adressLight - 1] = redValue;
	dmxBlock[adressLight] = greenValue;
	dmxBlock[adressLight + 1] = blueValue;
	dmxBlock[adressLight + 2] = whiteValue;

	DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
}