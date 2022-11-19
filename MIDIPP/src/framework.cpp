#include "winmessages.h"
#include "../include/winmidipp.h"

bool init = false;
MIDIHDR buffer;
char data[0x200];

unsigned int mpp::base::get_device_amount()
{
	return midiInGetNumDevs();
}

unsigned int mpp::base::get_device_info(device_info_t* device, const unsigned int deviceId)
{
	return midiInGetDevCapsA(deviceId, (LPMIDIINCAPSA)device, sizeof(device_info_t));
}

void mpp::base::add_in_callback(const midi_callback_t callback)
{
	messages::register_in_callback(callback);
}

void mpp::base::remove_in_callback(const midi_callback_t callback)
{
	messages::unregister_in_callback(callback);
}

void mpp::base::add_out_callback(const midi_callback_t callback)
{
	messages::register_out_callback(callback);
}

void mpp::base::remove_out_callback(const midi_callback_t callback)
{
	messages::unregister_out_callback(callback);
}

unsigned int mpp::base::open_midi_in(const unsigned int deviceId, midi_handle* deviceHandle)
{
	return midiInOpen((LPHMIDIIN)deviceHandle, deviceId, (DWORD_PTR) MidiInProc, 0, CALLBACK_FUNCTION);;
}

unsigned int mpp::base::open_midi_out(const unsigned int deviceId, midi_handle* deviceHandle)
{
	return midiOutOpen((LPHMIDIOUT)deviceHandle, deviceId, (DWORD_PTR) MidiOutProc, 0, CALLBACK_FUNCTION);
}

void mpp::base::close_midi_in(const midi_handle handle)
{
	midiInClose((HMIDIIN)handle);
}

void mpp::base::close_midi_out(const midi_handle handle)
{
	midiOutClose((HMIDIOUT)handle);
}

unsigned int mpp::start_recording(const midi_handle handle)
{
	unsigned int result;

	if (init)
		return 0;

	buffer.lpData = data;
	buffer.dwBufferLength = 0x200;
	buffer.dwFlags = 0;
	init = true;
	result = midiInPrepareHeader((HMIDIIN)handle, &buffer, sizeof(MIDIHDR));
	if (!result)
		result = midiInAddBuffer((HMIDIIN)handle, &buffer, sizeof(MIDIHDR));
	if (!result)
		result = midiInStart((HMIDIIN)handle);
	return result;
}

unsigned int mpp::stop_recording(const midi_handle handle)
{
	unsigned int result;

	if (!init)
		return 0;

	init = false;
	result = midiInStop((HMIDIIN)handle);
	if (!result)
		result = midiInReset((HMIDIIN)handle);
	if (!result)
		result = midiInUnprepareHeader((HMIDIIN)handle, &buffer, sizeof(MIDIHDR));
	return result;
}