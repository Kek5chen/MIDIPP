#pragma once

#define WINMIDI_API __declspec(dllexport)

#define WIN_DEVICE_NAME_LEN 32

namespace mpp {
	namespace types {
		typedef struct device_info_s {
			short wManufacturerId;
			short wProductId;
			short bDriverVersionMajor;
			short bDriverVersionMinor;
			char  szName[WIN_DEVICE_NAME_LEN];
		} device_info_t;
	}
	namespace base {
		WINMIDI_API unsigned int get_device_amount();
		WINMIDI_API unsigned int get_device_info(types::device_info_t* device, unsigned int deviceId);
	}
}