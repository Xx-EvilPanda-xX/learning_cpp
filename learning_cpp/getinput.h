#ifndef GETINPUT_H
#define GETINPUT_H

namespace input
{
	int getIntInput(const char* message);

	float getFloatInput(const char* message);

	bool getBoolInput(const char* message);

	char* getStringInput(const char* message);
}

#endif
