#pragma once
#include "../include/winmidipp.h"
#include <Windows.h>

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
void CALLBACK MidiOutProc(HMIDIOUT hmo, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

namespace mpp {
	namespace messages {
		void register_in_callback(midi_callback_t callback);
		void unregister_in_callback(midi_callback_t callback);
		void register_out_callback(midi_callback_t callback);
		void unregister_out_callback(midi_callback_t callback);
	}
}