#include "winmessages.h"

#include <vector>

std::vector<midi_callback_t> midi_in_callbacks;
std::vector<midi_callback_t> midi_out_callbacks;

#define DATA_PRESSED 0x7F

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
#ifdef MIDILOG
	if (wMsg == MIM_OPEN)
		printf("Received In-Open Message\n");
	else if (wMsg == MIM_CLOSE)
		printf("Received In-Close Message\n");
	else
#endif		
	if (wMsg == MIM_DATA) {
		unsigned char firstData = dwParam1 >> 16 & 0xFF;
		unsigned char secondData = dwParam1 >> 8 & 0xFF;
		unsigned char status = dwParam1 & 0xFF;
		for(midi_callback_t callback : midi_in_callbacks) {
			callback(firstData, secondData, status);
		}
	}
#ifdef MIDILOG
	else if (wMsg == MIM_LONGDATA) {
		auto midihdr = (MIDIHDR*)dwParam1;
		if (midihdr->dwFlags & MHDR_DONE)
			printf("MHDR_DONE\n");
		if (midihdr->dwFlags & MHDR_INQUEUE)
			printf("MHDR_INQUEUE\n");
		if (midihdr->dwFlags & MHDR_ISSTRM)
			printf("MHDR_ISSTRM\n");
		if (midihdr->dwFlags & MHDR_PREPARED)
			printf("MHDR_PREPARED\n");
	} else
		printf("RECEIVED UNKNOWN IN MESSAGE WITH PARAMETERS: %08x %08x %08x %08x\n", wMsg, dwInstance, dwParam1, dwParam2);
#endif
}

void CALLBACK MidiOutProc(HMIDIOUT hmo, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
#ifdef MIDILOG
	if (wMsg == MOM_OPEN)
		printf("Received Out-Open Message\n");
	else if (wMsg == MOM_CLOSE)
		printf("Received Out-Close Message\n");
	else
		printf("RECEIVED UNKNOWN IN MESSAGE WITH PARAMETERS: %08x %08x %08x %08x\n", wMsg, dwInstance, dwParam1, dwParam2);
#endif
	
	for(midi_callback_t callback : midi_out_callbacks) {
		callback(wMsg, 0, 0);
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