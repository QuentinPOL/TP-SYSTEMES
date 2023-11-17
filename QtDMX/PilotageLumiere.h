#pragma once

class PilotageLumiere
{
public:
	PilotageLumiere();
	~PilotageLumiere();

	// Changer de couleur
	void setColor(int redValue, int greenValue, int blueValue, int whiteValue, int adresseLumiere, int dmxMode, unsigned char dmxBlock[]);
};