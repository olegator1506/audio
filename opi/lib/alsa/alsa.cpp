/*
#include <alsa/asoundlib.h>
#include <iostream>
using namespace std;
// Globals are generally a bad idea in code.  We're using one here to keep it simple.
snd_pcm_t * _soundDevice;
unsigned int _actualRate;
bool alsaInit(const char *name, unsigned int rate)
{
  int err;
  snd_pcm_hw_params_t *hw_params;

  if( name == NULL )
  {
      // Try to open the default device
      err = snd_pcm_open( &_soundDevice, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, 0 );
  }
  else
  {
      // Open the device we were told to open.
      err = snd_pcm_open (&_soundDevice, name, SND_PCM_STREAM_PLAYBACK, 0);
  }

  // Check for error on open.
  if( err < 0 )
  {
      cout << "Init: cannot open audio device " << name << " (" << snd_strerror (err) << ")" << endl;
      return false;
  }
  else
  {
      cout << "Audio device opened successfully." << endl;
  }

  // Allocate the hardware parameter structure.
  if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0)
  {
      cout << "Init: cannot allocate hardware parameter structure (" << snd_strerror (err) << ")" << endl;
      return false;
  }

  if ((err = snd_pcm_hw_params_any (_soundDevice, hw_params)) < 0)
  {
      cout << "Init: cannot initialize hardware parameter structure (" << snd_strerror (err) << ")" << endl;
      return false;
  }

  // Enable resampling.
  unsigned int resample = 1;
  err = snd_pcm_hw_params_set_rate_resample(_soundDevice, hw_params, resample);
  if (err < 0)
  {
      cout << "Init: Resampling setup failed for playback: " << snd_strerror(err) << endl;
      return err;
  }

  // Set access to RW interleaved.
  if ((err = snd_pcm_hw_params_set_access (_soundDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
  {
      cout << "Init: cannot set access type (" << snd_strerror (err) << ")" << endl;
      return false;
  }

  if ((err = snd_pcm_hw_params_set_format (_soundDevice, hw_params, SND_PCM_FORMAT_S16_LE)) < 0)
  {
      cout << "Init: cannot set sample format (" << snd_strerror (err) << ")" << endl;
      return false;
  }

  // Set channels to stereo (2).
  if ((err = snd_pcm_hw_params_set_channels (_soundDevice, hw_params, 2)) < 0)
  {
      cout << "Init: cannot set channel count (" << snd_strerror (err) << ")" << endl;
      return false;
  }

  // Set sample rate.
  //unsigned int actualRate = 44100;
  _actualRate = rate;
  if ((err = snd_pcm_hw_params_set_rate_near (_soundDevice, hw_params, &_actualRate, 0)) < 0)
  {
      cout << "Init: cannot set sample rate to " << rate << ". (" << snd_strerror (err) << ")"  << endl;
      return false;
  }
  if( _actualRate != rate )
  {
      cout << "Init: sample rate does not match requested " << rate << ". (" << "44100 requested, " << _actualRate << " acquired)" << endl;
  }

  // Apply the hardware parameters that we've set.
  if ((err = snd_pcm_hw_params (_soundDevice, hw_params)) < 0)
  {
      cout << "Init: cannot set parameters (" << snd_strerror (err) << ")" << endl;
      return false;
  }
  else
  {
     cout << "Audio device parameters have been set successfully." << endl;
  }

  // Get the buffer size.
  snd_pcm_uframes_t bufferSize;
  snd_pcm_hw_params_get_buffer_size( hw_params, &bufferSize );
  // If we were going to do more with our sound device we would want to store
  // the buffer size so we know how much data we will need to fill it with.
  cout << "Init: Buffer size = " << bufferSize << " frames." << endl;

  // Display the bit size of samples.
  cout << "Init: Significant bits for linear samples = " << snd_pcm_hw_params_get_sbits(hw_params) << endl;

  // Free the hardware parameters now that we're done with them.
  snd_pcm_hw_params_free (hw_params);

  // Prepare interface for use.
  if ((err = snd_pcm_prepare (_soundDevice)) < 0)
  {
      cout << "Init: cannot prepare audio interface for use (" << snd_strerror (err) << ")" << endl;
      return false;
  }
  else
  {
      cout << "Audio device has been prepared for use." << endl;
  }

  return true;
}

bool alsaRelease()
{
  snd_pcm_close (_soundDevice);
  cout << "Audio device has been uninitialized." << endl;
  return true;
}

void alsaGenSound(int duration) {
unsigned char *data;
    int pcmreturn, cycles, l2, l1;
    short s1, s2;
    int frames;
    snd_pcm_uframes_t periodsize = 8192 * 4; 
    data = (unsigned char *)malloc(periodsize);

    frames = periodsize >> 2;
    cycles = duration * _actualRate / frames;
    for(l2 = 0; l2 < frames; l2++) {
        s1 = (l2 % 128) * 300 - 5000;  
        s2 = (l2 % 256) * 300 - 5000;  
//        printf("%d L: %d R:%d\n",l2,s1,s2);
        data[4*l2] = (unsigned char)s1;
        data[4*l2+1] = s1 >> 8;
        data[4*l2+2] = (unsigned char)s2;
        data[4*l2+3] = s2 >> 8;

    }
    for(l1 = 0;;l1++) {
      if((duration > 0)  && (l1 > cycles)) return;
      while ((pcmreturn = snd_pcm_writei(_soundDevice, data, frames)) < 0) {
        snd_pcm_prepare(_soundDevice);
        fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
      }
    }
}

void alsaPlay(unsigned char *data,int frames){
    snd_pcm_writei(_soundDevice, data, frames);
}

*/