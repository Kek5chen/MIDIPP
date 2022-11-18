#include "winmessages.h"
#include "../include/winmidipp.h"

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

unsigned int mpp::base::open_midi_in(const unsigned int deviceId, handle* deviceHandle)
{
	return midiInOpen((LPHMIDIIN)deviceHandle, deviceId, (DWORD_PTR) &MidiInProc, 0, CALLBACK_FUNCTION);
}

unsigned int mpp::base::open_midi_out(const unsigned int deviceId, handle* deviceHandle)
{
	return midiOutOpen((LPHMIDIOUT)deviceHandle, deviceId, (DWORD_PTR) &MidiOutProc, 0, CALLBACK_FUNCTION);
}

void mpp::base::close_midi_in(const handle handle)
{
	midiInClose((HMIDIIN)handle);
}

void mpp::base::close_midi_out(const handle handle)
{
	midiOutClose((HMIDIOUT)handle);
}
