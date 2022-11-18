#include <cstdio>

#include "Windows.h"
#include "../include/winmidipp.h"

unsigned int mpp::base::get_device_amount()
{
	return midiInGetNumDevs();
}

unsigned int mpp::base::get_device_info(device_info_t* device, unsigned int deviceId)
{
	return midiInGetDevCapsA(deviceId, (LPMIDIINCAPSA)device, sizeof(device_info_t));
}

int open_midi(unsigned int deviceId, mpp::handle* deviceHandle, )