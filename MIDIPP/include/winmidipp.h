#pragma once

#define WINMIDI_API __declspec(dllexport)

#define DEVICE_NAME_LEN 32
#define MIDI_IN_HANDLE void*

typedef void (*midi_callback_t)(unsigned char firstData, unsigned char secondData, unsigned char status);

namespace mpp {
	typedef struct device_info_s {
		short manufacturerId;
		short productId;
		short driverVersionMajor;
		short driverVersionMinor;
		char  name[DEVICE_NAME_LEN];
	} device_info_t;
	typedef MIDI_IN_HANDLE handle;
	namespace base {
		WINMIDI_API unsigned int get_device_amount();
		WINMIDI_API unsigned int get_device_info(device_info_t* device, unsigned int deviceId);
		WINMIDI_API void         add_in_callback(midi_callback_t callback);
		WINMIDI_API void         remove_in_callback(midi_callback_t callback);
		WINMIDI_API void         add_out_callback(midi_callback_t callback);
		WINMIDI_API void         remove_out_callback(midi_callback_t callback);
		WINMIDI_API unsigned int open_midi_in(unsigned int deviceId, handle* deviceHandle);
		WINMIDI_API unsigned int open_midi_out(unsigned int deviceId, handle* deviceHandle);
		WINMIDI_API void         close_midi_in(handle handle);
		WINMIDI_API void         close_midi_out(handle handle);
	}
	WINMIDI_API unsigned int start_recording(handle handle);
	WINMIDI_API unsigned int stop_recording(handle handle);
}