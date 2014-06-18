#include "StompBox.h"
#include "owlcontrol.h"
#include "ApplicationSettings.h"
#include "CodecController.h"
#include "PatchProcessor.h"
#include "PatchController.h"
#include "device.h"
#include <cstddef>
#include <string.h>

AudioBuffer::~AudioBuffer(){}

Patch::Patch(){
  processor = patches.getCurrentPatchProcessor();
}

Patch::~Patch(){}

void Patch::registerParameter(PatchParameterId pid, const char* name, const char* description){
  processor->registerParameter(pid, name, description);
}

double Patch::getSampleRate(){
  return codec.getSamplingRate();
}

int Patch::getBlockSize(){
  return AUDIO_BLOCK_SIZE;
 // return settings.audio_blocksize;
}

float Patch::getParameterValue(PatchParameterId pid){
  return processor->getParameterValue(pid);
}

AudioBuffer* Patch::createMemoryBuffer(int channels, int samples){
  return processor->createMemoryBuffer(channels, samples);
}

void pressButton(PatchButtonId bid){
  switch(bid){
  case BYPASS_BUTTON:
    break;
  case PUSHBUTTON:
    toggleLed();
    break;
  case GREEN_BUTTON:
    setLed(GREEN);
    break;
  case RED_BUTTON:
    setLed(RED);
    break;
  }
}

bool Patch::isButtonPressed(PatchButtonId bid){
  switch(bid){
  case BYPASS_BUTTON:
    return isStompSwitchPressed();
    break;
  case PUSHBUTTON:
    return isPushButtonPressed();
    break;
  case GREEN_BUTTON:
    return getLed() == GREEN;
    break;
  case RED_BUTTON:
    return getLed() == RED;
    break;
  }
  return false;
}
