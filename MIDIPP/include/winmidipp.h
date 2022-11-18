#pragma once

#define WINMIDI_API __declspec(dllexport)

#define DEVICE_NAME_LEN 32
#define MIDI_IN_HANDLE HMIDIIN

namespace mpp {
	typedef struct device_info_s {
		short manufacturerId;
		short productId;
		short driverVersionMajor;
		short driverVersionMinor;
		char  name[DEVICE_NAME_LEN];
	} device_info_t;
	namespace base {
		WINMIDI_API unsigned int get_device_amount();
		WINMIDI_API unsigned int get_device_info(device_info_t* device, unsigned int deviceId);
	}
}