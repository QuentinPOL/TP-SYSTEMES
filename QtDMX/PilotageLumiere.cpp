#include "PilotageLumiere.h"

PilotageLumiere::PilotageLumiere()
{}

PilotageLumiere::~PilotageLumiere()
{}

void PilotageLumiere::setColor(int redValue, int greenValue, int blueValue, int whiteValue, int adresseLumiere, int dmxMode, unsigned char dmxBlock[])
{
	// ALORS ON VA CONSTRUIRE LA TRAME  AVEC LES COULEURS ETC PAR RAPPORT AU MODE DMX AINSI QUA L ADRESSE DE LA LUMIERE
	dmxBlock[adresseLumiere-1] = redValue;
	dmxBlock[adresseLumiere] = greenValue;
	dmxBlock[adresseLumiere + 1] = blueValue;
	dmxBlock[adresseLumiere + 2] = whiteValue;
}