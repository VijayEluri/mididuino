#ifndef TEST_SUITE_H__
#define TEST_SUITE_H__

/* help out the IDE */
#ifndef TEST_SUITE
#define TEST_SUITE
#endif

#include "Platform.h"
#include <CppUnitLite2.h>
#include <TestResultStdErr.h>
#include <Test.h>

#include "test_helpers.h"

#include <ListPool.hh>

#include <Midi.h>
#include <VirtualMidi.h>

extern VirtualMidi Midi;
extern VirtualMidi Midi2;

#endif
