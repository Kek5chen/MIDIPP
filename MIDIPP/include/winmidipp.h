#pragma once

#define WINMIDI_API __declspec(dllexport)

#define DEVICE_NAME_LEN 32
#define MIDI_IN_HANDLE int
#define NOVCOLOR(r,g) (((g) & 0x3) << 4 | ((r) & 0x3) | 0b100)

#ifdef _DEBUG
#define MIDILOG
#endif

union midi_message {
	char data[4];
	int message;
};

typedef void (*midi_callback_t)(unsigned char firstData, unsigned char secondData, unsigned char status);

namespace mpp {
	typedef struct device_info_s {
		short manufacturerId;
		short productId;
		short driverVersionMajor;
		short driverVersionMinor;
		char  name[DEVICE_NAME_LEN];
	} device_info_t;
	typedef MIDI_IN_HANDLE midi_handle;
	namespace base {
		WINMIDI_API unsigned int get_device_amount();
		WINMIDI_API unsigned int get_device_info(device_info_t* device, unsigned int deviceId);
		WINMIDI_API void         add_in_callback(midi_callback_t callback);
		WINMIDI_API void         remove_in_callback(midi_callback_t callback);
		WINMIDI_API void         add_out_callback(midi_callback_t callback);
		WINMIDI_API void         remove_out_callback(midi_callback_t callback);
		WINMIDI_API unsigned int open_midi_in(unsigned int deviceId, midi_handle* deviceHandle);
		WINMIDI_API unsigned int open_midi_out(unsigned int deviceId, midi_handle* deviceHandle);
		WINMIDI_API unsigned int send_midi(midi_handle handle, unsigned char status, unsigned char firstData, unsigned char secondData);
		WINMIDI_API void         close_midi_in(midi_handle handle);
		WINMIDI_API void         close_midi_out(midi_handle handle);
	}
	namespace novation {
		WINMIDI_API unsigned int set_led(midi_handle handle, unsigned char ledX, unsigned char ledY, unsigned char color);
		WINMIDI_API unsigned int reset(midi_handle handle);
	}
	WINMIDI_API unsigned int start_recording(midi_handle handle);
	WINMIDI_API unsigned int stop_recording(midi_handle handle);
}