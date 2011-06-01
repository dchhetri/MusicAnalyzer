/*
 * MusicPlayer.h
 *
 *  Created on: May 19, 2011
 *      Author: MacBoss
 *      Description: 	Encapsulates SDL music functions into a more easier interface,
 *      				Note MusicPlayer is non-copyable and non-assignable
 */


#ifndef MUSICPLAYER_H_
#define MUSICPLAYER_H_


#include <string>
#include "SDL_mixer.h"

namespace SDL_OpenGL{

	//Used to keep track of current audio settings, determines if reinitialization is needed or not
	struct _MusicInfo{
		bool isAlreadyInitialized;
		int frequency, format, channel, chunkSize;
		_MusicInfo() : frequency(-1), format(-1), channel(-1), chunkSize(-1) {}
		_MusicInfo(const int freq, const int format, const int ch, const int chunkSz)
		: frequency(freq), format(format), channel(ch), chunkSize(chunkSz){}
	};

	class MusicPlayer{
	private:
		Mix_Chunk * _music;
		int _channel;
		static _MusicInfo _musicInfo;
	public:
		explicit MusicPlayer(const int FREQUENCY = MIX_DEFAULT_FREQUENCY, //output sample frequency
							 const int FORMAT = MIX_DEFAULT_FORMAT,	//output sample format
							 const int CHANNEL = 2,	//number of sounds channel in output 2 for stereo or 1 for mono
							 const int CHUNK_SIZE = 1024);//bytes used per sample chunk
		~MusicPlayer();
		//loads the given musicFile, returns false on failure else true on success
		//available music type  = WAVE, AIFF, RIFF, OGG, and VOC
		bool loadMusic(const std::string& musicFileName);
		//sets the current channel for the music to be played on
		void setChannelToPlayOn(const int channel);
		//returns the current channel used
		const int getCurrentChannel()const;
		//plays the music -- If paused resumes it else starts the music
		void play()const;
		//pauses the music being played on current channel
		void pause()const;
		//restarts the music from the beginning
		void restart()const;
		//registers the function to current music channel
		//thus when music gets played effectFunc gets called every sample
		//when music is finished, finishedFunc gets called
		void registerEffectCallback(const Mix_EffectFunc_t& effectFunc, const Mix_EffectDone_t& finishedFunc);
		//removes all callback from current channel
		void unregisterEffectCallback()const;

		MusicPlayer& getObject();
	private:
		void _doLazyInitialization(const int,const int,const int,const int);
		// make non-copyable
		MusicPlayer(const MusicPlayer&);
		MusicPlayer& operator=(const MusicPlayer&);
	};

}//end of namespace SDL_OpenGL

#endif /* MUSICPLAYER_H_ */
