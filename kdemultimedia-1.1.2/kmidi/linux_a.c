/* 

    TiMidity -- Experimental MIDI to WAVE converter
    Copyright (C) 1995 Tuukka Toivonen <toivonen@clinet.fi>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    linux_audio.c

    Functions to play sound on the VoxWare audio driver (Linux or FreeBSD)

*/

#if defined(linux) || defined(__FreeBSD__)
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#ifdef linux
#include <sys/ioctl.h> /* new with 1.2.0? Didn't need this under 1.1.64 */
#include <linux/soundcard.h>
#endif

#ifdef __FreeBSD__
#include <stdio.h>
#include <machine/soundcard.h>
#endif

#include "config.h"
#include "output.h"
#include "controls.h"

extern void b_out(int fd, int *buf, int ocount);

static int open_output(void); /* 0=success, 1=warning, -1=fatal error */
static void close_output(void);
static void output_data(int32 *buf, int32 count);
static void flush_output(void);
static void purge_output(void);

/* export the playback mode */

#define dpm linux_play_mode

PlayMode dpm = {
  DEFAULT_RATE, PE_16BIT|PE_SIGNED,
  -1,
  {0}, /* default: get all the buffer fragments you can */
  "Linux dsp device", 'd',
  "/dev/dsp",
  open_output,
  close_output,
  output_data,
  flush_output,
  purge_output  
};


/*************************************************************************/
/* We currently only honor the PE_MONO bit, the sample rate, and the
   number of buffer fragments. We try 16-bit signed data first, and
   then 8-bit unsigned if it fails. If you have a sound device that
   can't handle either, let me know. */

static int open_output(void)
{
  int fd, tmp, i, warnings=0;
  
  /* Open the audio device */
  fd=open(dpm.name, O_RDWR | O_NDELAY);
  if (fd<0)
    {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "%s: %s",
	   dpm.name, sys_errlist[errno]);
      return -1;
    }

  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) & ~O_NDELAY);


  /* They can't mean these */
  dpm.encoding &= ~(PE_ULAW|PE_BYTESWAP);


  /* Set sample width to whichever the user wants. If it fails, try
     the other one. */

  i=tmp=(dpm.encoding & PE_16BIT) ? 16 : 8;
  if (ioctl(fd, SNDCTL_DSP_SAMPLESIZE, &tmp)<0 || tmp!=i)
    {
      /* Try the other one */
      i=tmp=(dpm.encoding & PE_16BIT) ? 8 : 16;
      if (ioctl(fd, SNDCTL_DSP_SAMPLESIZE, &tmp)<0 || tmp!=i)
	{
	  ctl->cmsg(CMSG_ERROR, VERB_NORMAL, 
		    "%s doesn't support 16- or 8-bit sample width", 
		    dpm.name);
	  close(fd);
	  return -1;
	}
      ctl->cmsg(CMSG_WARNING, VERB_VERBOSE,
		"Sample width adjusted to %d bits", tmp);
      dpm.encoding ^= PE_16BIT;
      warnings=1;
    }
  if (dpm.encoding & PE_16BIT)
    dpm.encoding |= PE_SIGNED;
  else
    dpm.encoding &= ~PE_SIGNED;


  /* Try stereo or mono, whichever the user wants. If it fails, try
     the other. */

  i=tmp=(dpm.encoding & PE_MONO) ? 0 : 1;
  if ((ioctl(fd, SNDCTL_DSP_STEREO, &tmp)<0) || tmp!=i)
    {
      i=tmp=(dpm.encoding & PE_MONO) ? 1 : 0;

      if ((ioctl(fd, SNDCTL_DSP_STEREO, &tmp)<0) || tmp!=i)
	{
	  ctl->cmsg(CMSG_ERROR, VERB_NORMAL, 
	       "%s doesn't support mono or stereo samples",
	       dpm.name);
	  close(fd);
	  return -1;
	}
      if (tmp==0) dpm.encoding |= PE_MONO;
      else dpm.encoding &= ~PE_MONO;
      ctl->cmsg(CMSG_WARNING, VERB_VERBOSE, "Sound adjusted to %sphonic", 
	   (tmp==0) ? "mono" : "stereo");
      warnings=1;
    }


  /* Set the sample rate */
  
  tmp=dpm.rate;
  if (ioctl(fd, SNDCTL_DSP_SPEED, &tmp)<0)
    {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, 
	   "%s doesn't support a %d Hz sample rate",
	   dpm.name, dpm.rate);
      close(fd);
      return -1;	  
    }
  if (tmp != dpm.rate)
    {
      ctl->cmsg(CMSG_WARNING, VERB_VERBOSE,
	   "Output rate adjusted to %d Hz (requested %d Hz)", tmp, dpm.rate);
      dpm.rate=tmp;
      warnings=1;
    }

  /* Older VoxWare drivers don't have buffer fragment capabilities */  
#ifdef SNDCTL_DSP_SETFRAGMENT
  /* Set buffer fragments (in extra_param[0]) */
  
  tmp=AUDIO_BUFFER_BITS;
  if (!(dpm.encoding & PE_MONO)) tmp++;
  if (dpm.encoding & PE_16BIT) tmp++;
  tmp |= (dpm.extra_param[0]<<16);
  i=tmp;
  if (ioctl(fd, SNDCTL_DSP_SETFRAGMENT, &tmp)<0)
    {
      ctl->cmsg(CMSG_WARNING, VERB_NORMAL, 
	   "%s doesn't support %d-byte buffer fragments", dpm.name, (1<<i));
      /* It should still work in some fashion. We should use a
	 secondary buffer anyway -- 64k isn't enough. */
      warnings=1;
    }
#else
  if (dpm.extra_param[0])
    {
      ctl->cmsg(CMSG_WARNING, VERB_NORMAL, 
		"%s doesn't support buffer fragments", dpm.name);
      warnings=1;
    }
#endif
/**
#ifdef ADAGIO
#ifndef NO_DEV_SEQUENCER
#ifdef SNDCTL_DSP_SETSYNCRO
  if (!no_dev_sequencer) ioctl(fd, SNDCTL_DSP_SETSYNCRO, 0);
#endif
#endif
#endif
**/
  dpm.fd=fd;
  
  return warnings;
}
#ifdef ADAGIO
int current_sample_count()
{
  count_info auinfo;

  if (ioctl(dpm.fd, SNDCTL_DSP_GETOPTR, &auinfo)<0) return -1;
  return auinfo.bytes;
}
#endif

static void output_data(int32 *buf, int32 count)
{
  int ocount;

  if (!(dpm.encoding & PE_MONO)) count*=2; /* Stereo samples */
  ocount = count;

  if (ocount) {
    if (dpm.encoding & PE_16BIT)
      {
        /* Convert data to signed 16-bit PCM */
        s32tos16(buf, count);
        ocount *= 2;
      }
    else
      {
        /* Convert to 8-bit unsigned and write out. */
        s32tou8(buf, count);
      }
  }

  b_out(dpm.fd, (int *)buf, ocount);
}

#if 0
static void output_data(int32 *buf, int32 count)
{
  if (!(dpm.encoding & PE_MONO)) count*=2; /* Stereo samples */
  
  if (dpm.encoding & PE_16BIT)
    {
      /* Convert data to signed 16-bit PCM */
      s32tos16(buf, count);
      
      /* Write the data out. Linux likes to give an EINTR if you suspend
	 a program while waiting on a write, so we may need to retry. */
      while ((-1==write(dpm.fd, buf, count * 2)) && errno==EINTR)
	;
    }
  else
    {
      /* Convert to 8-bit unsigned and write out. */
      s32tou8(buf, count);
      
      while ((-1==write(dpm.fd, buf, count)) && errno==EINTR)
	;
    }
}
#endif

static void close_output(void)
{
  close(dpm.fd);
}

static void flush_output(void)
{
  output_data(0, 0);
  ioctl(dpm.fd, SNDCTL_DSP_SYNC);
}

static void purge_output(void)
{
  ioctl(dpm.fd, SNDCTL_DSP_RESET);
}

#endif /* defined(linux) || defined(__FreeBSD__) */
