#include "TestSuite.h"
#include "Midi.h"

class CB : public MidiCallback {
public:
  bool callbackCalled;
  CB() : callbackCalled(false) {
  };

  void callback(uint8_t *msg) {
    callbackCalled = true;
  }
};


struct MidiCallbackFixture {
  CB cb;

  MidiCallbackFixture() {
    Midi.init();
    Midi.initSerial();
    Midi.removeAllCallbacks();
  }
};


TEST_F (MidiCallbackFixture, TestNoteOn) {
  CHECK_EQUAL(false, cb.callbackCalled);

  static CB::callback_ptr_t p =
      (decltype(cb)::callback_ptr_t)
      &CB::callback;
  Midi.addOnNoteOnCallback(&cb, p);

  ADD_CALLBACK(Midi.addOnNoteOnCallback, cb, callback);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendNoteOn(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(true, cb.callbackCalled);

  cb.callbackCalled = false;
  Midi.sendNoteOn(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(true, cb.callbackCalled);

  cb.callbackCalled = false;
  Midi.sendNoteOff(MIDI_NOTE_A0);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendCC(0, 0);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendChannelPressure(100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendPitchBend(100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendPolyKeyPressure(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendProgramChange(100);
  CHECK_EQUAL(false, cb.callbackCalled);

  uint8_t foo[] = {1, 2, 3, 4};
  Midi.sendSysex(foo, 4);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendNoteOn(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(true, cb.callbackCalled);
}

TEST_F (MidiCallbackFixture, TestNoteOff) {
  CHECK_EQUAL(false, cb.callbackCalled);

  ADD_CALLBACK(Midi.addOnNoteOffCallback, cb, callback);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendNoteOn(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendNoteOff(MIDI_NOTE_A0);
  CHECK_EQUAL(true, cb.callbackCalled);

  cb.callbackCalled = false;
  Midi.sendNoteOn(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendCC(0, 0);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendChannelPressure(100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendPitchBend(100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendPolyKeyPressure(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendProgramChange(100);
  CHECK_EQUAL(false, cb.callbackCalled);

  uint8_t foo[] = {1, 2, 3, 4};
  Midi.sendSysex(foo, 4);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendNoteOn(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(false, cb.callbackCalled);

  Midi.sendNoteOff(MIDI_NOTE_A0);
  CHECK_EQUAL(true, cb.callbackCalled);
}

void setupMidiCallbacks();

bool noteOnCallbackCalled = false;
void onNoteOn(uint8_t *msg) {
  noteOnCallbackCalled = true;
}

TEST_F (MidiCallbackFixture, TestDefaultCallbacks) {
  setupMidiCallbacks();
  Midi.sendNoteOn(MIDI_NOTE_A0, 100);
  CHECK_EQUAL(true, noteOnCallbackCalled);
}


