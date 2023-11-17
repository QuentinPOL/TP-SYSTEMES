//*********************************************************************************************
//* Programme : QtDMX.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 17/11/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Faire l'impl�mentation des m�thodes / constructeur / constructeur de celle-ci
//* Programmes associ�s : QtDMX.h (fichier ent�te de la classe QtDMX)
//*********************************************************************************************

#include "QtDMX.h"

//---------------------------------------------------------------------------------------------
//* Constructeur de la classe QtDMX qui est l'ihm du programme -> cela regroupe le chargement de la DLL 
// L'initlisation de l'interface ainsi que le module pour envoyer des trames DMX gr�ce � des commandes
// Cr�ation de l'objet PilotageLumiere qui va permettre  de piloter le changement des couleurs des lumi�res
// initialisation des 512 blocks de la trame DMX et cr�ation du timer pour l'envoie de trame r�gulier (50 ms)
//-------------------------------------------------------------------------------------------
QtDMX::QtDMX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	//Chargement de la DLL
	g_dasusbdll = LoadLibraryA("C:\\Users\\Quentin Pollet\\source\\repos\\QtDMX\\DasHard2006.dll");

	//Verification du chargement
	if (g_dasusbdll)
		DasUsbCommand = (DASHARDCOMMAND)::GetProcAddress((HMODULE)g_dasusbdll, "DasUsbCommand");

	//Initialisation de la DLL
	interface_open = DasUsbCommand(DHC_INIT, 0, NULL);

	//On ouvre la liaison avec l'interface USB -1 si on ne trouve pas le port USB
	//retourn DHC-OK = 1 si USB connecter
	interface_open = DasUsbCommand(DHC_OPEN, 0, 0);

	//Envoi D'une Trame DMX
	piloteLum = new PilotageLumiere();

	// Parametre : Commande DHC_DMXOUT, Taille Block 512 , Trame dmxbloc Pointeur
	// dmxBlock[512] est declarer en global dans le .h mais il faut creer la trame
	for (int i = 0; i < DMX_MAXCHANNEL; i++)
		dmxBlock[i] = 0;

	// Connecter le signal timeout du timer au slot sendTrame
	QObject::connect(&timer, &QTimer::timeout, this, &QtDMX::sendTrame);
	timer.start(50); // on envoie toutes les 50 ms une trame
}

//---------------------------------------------------------------------------------------------
//* Destructeur de la classe de l'ihm QtDMX qui ferme la connexion ainsi que lib�re la librairie DLL
//---------------------------------------------------------------------------------------------

QtDMX::~QtDMX()
{
	//Fermeture du DMX � l'arret du programme
	if (interface_open > 0) {
		DasUsbCommand(DHC_CLOSE, 0, 0);
		DasUsbCommand(DHC_EXIT, 0, NULL);
	}
	if (g_dasusbdll != NULL)
		FreeLibrary(g_dasusbdll);
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de l'adresse de la lumi�re du slider dans le label
//* Param�tres :
//*  - int value : variable qui � la valeur du slider de l'adresse de la lumi�re
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderValueChanged(int value)
{
	ui.labelLampValue->setText(QString::number(value));
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur rouge du slider dans le label
//* Param�tres :
//*  - int value : variable qui � la valeur du slider de la couleur rouge
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorRedChanged(int value)
{
	ui.labelValueRed->setText(QString::number(value));
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur verte du slider dans le label
//* Param�tres :
//*  - int value : variable qui � la valeur du slider de la couleur verte
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorGreenChanged(int value)
{
	ui.labelValueGreen->setText(QString::number(value));
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur blueue du slider dans le label
//* Param�tres :
//*  - int value : variable qui � la valeur du slider de la couleur blueue
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorBlueChanged(int value)
{
	ui.labelValueBlue->setText(QString::number(value));
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur blanche du slider dans le label
//* Param�tres :
//*  - int value : variable qui � la valeur du slider de la couleur blanche
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorWhiteChanged(int value)
{
	ui.labelValueWhite->setText(QString::number(value));
}

//---------------------------------------------------------------------------------------------
//* Fonction qui envoie une trame si l'interface est ouverte et donc que la libraire DLL est charg�e
// Ainsi que r�cup�ration de la valeure du mode DMX / num�ro d'adresse de la lumi�re selectionn� et des couleurs s�lectionn�es
// Enfin on fait le changement de couleur de la lumi�re en question s�lectionner dans numAdressLum en appelant la m�thode setColor de la classe  piloteLum
// Mais on va v�rifier avant si la checkbox est coch� ou non  pour faire un d�filement automatique des couleurs et ensuite une fois qu'on � fait tout cela on envoie la trame DMX
//---------------------------------------------------------------------------------------------
void QtDMX::sendTrame()
{
	if (interface_open > 0)
	{
		// on va r�cup�rer la valeur mode DMX (spinBoxDMXModes)
		int numDMXMode = ui.spinBoxDMXModes->value();

		// on va r�cup�rer la valeur � de l'adresse de la lumi�re � laquelle nous sommes (horizontalSlider)
		int numAdressLum = ui.horizontalSlider->value();

		// ensuite on va mettre les diff�rentes informations � la lumi�re par rapport au mode DMX auquel nous sommes 
		// (verticalSliderColorRed, verticalSliderColorGreen, verticalSliderColorBlue, verticalSliderIntensity)
		// exemple si la lumiere est sur le canal 12, alors l'octet dmxBlock[12] contient
		// un ensemble de 8 bits representant les informations � envoyer � la lumiere : intensite couleur ect
		// Attention une lumiere peut avoir plusieur cannaux
		// exemple une led 3 couleurs aura 3 cannaux pour rouge vert bleu
		// donc la deuxieme lampe devra etre configure sur un canal 4

		int redValue = ui.verticalSliderColorRed->value(); // D�grad� rouge
		int greenValue = ui.verticalSliderColorGreen->value();  // D�grad� vert
		int blueValue = ui.verticalSliderColorBlue->value();   // D�grad� bleu
		int whiteValue = ui.verticalSliderIntensity->value();   // D�grad� blanc

		// Si on veut faire un d�filement de couleur automatique
		if (ui.checkBox->isChecked())
		{
			int time = QTime::currentTime().msecsSinceStartOfDay();  // Obtient le temps actuel en millisecondes
			redValue = (time / 10) % 256;    // D�grad� rouge
			greenValue = (time / 15) % 256;  // D�grad� vert
			blueValue = (time / 20) % 256;   // D�grad� bleu
			whiteValue = (time / 25) % 256;   // D�grad� bleu
		}

		piloteLum->setColor(redValue, greenValue, blueValue, whiteValue, numAdressLum, numDMXMode, dmxBlock);

		DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
	}
}