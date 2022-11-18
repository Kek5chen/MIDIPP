#include "winmessages.h"

#include <vector>

std::vector<midi_callback_t> midi_in_callbacks;
std::vector<midi_callback_t> midi_out_callbacks;

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	if (wMsg == MIM_OPEN)
		printf("Reveiced In-Open Message\n");
	else if (wMsg == MIM_CLOSE)
		printf("Reveiced In-Close Message\n");
	else
		printf("RECEIVED UNKNWON IN MESSAGE WITH PARAMETERS: %d %d %d %d\n", wMsg, dwInstance, dwParam1, dwParam2);
	midiInStart(hMidiIn);
	midiInReset(hMidiIn);
	for(midi_callback_t callback : midi_in_callbacks) {
		callback();
	}
}

void CALLBACK MidiOutProc(HMIDIOUT hmo, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	if (wMsg == MOM_OPEN)
		printf("Reveiced Out-Open Message\n");
	else if (wMsg == MOM_CLOSE)
		printf("Reveiced Out-Close Message\n");
	else
		printf("RECEIVED OUT MESSAGE WITH PARAMETERS: %d %d %d %d\n", wMsg, dwInstance, dwParam1, dwParam2);
	for(midi_callback_t callback : midi_out_callbacks) {
		callback();
	}
}

void mpp::messages::register_in_callback(midi_callback_t callback)
{
	midi_in_callbacks.push_back(callback);
}

void mpp::messages::unregister_in_callback(midi_callback_t callback)
{
	midi_in_callbacks.erase(std::remove(midi_in_callbacks.begin(), midi_in_callbacks.end(), callback), midi_in_callbacks.end());
}

void mpp::messages::register_out_callback(midi_callback_t callback)
{
	midi_out_callbacks.push_back(callback);
}

void mpp::messages::unregister_out_callback(midi_callback_t callback)
{
	midi_out_callbacks.erase(std::remove(midi_out_callbacks.begin(), midi_out_callbacks.end(), callback), midi_out_callbacks.end());
}