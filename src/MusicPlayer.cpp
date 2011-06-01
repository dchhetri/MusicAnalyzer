/*
 * MusicPlayer.cpp
 *
 *  Created on: May 19, 2011
 *      Author: MacBoss
 */

#include "MusicPlayer.h"
#include "SDL_mixer.h"
#include <string>

namespace SDL_OpenGL
{
	//initialize static variable
	_MusicInfo MusicPlayer::_musicInfo = _MusicInfo();

	MusicPlayer::MusicPlayer(const int FREQUENCY,
							 const int FORMAT,
							 const int CHANNEL,
							 const int CHUNK_SIZE
							) : _channel(1)
	{
		_doLazyInitialization(FREQUENCY,FORMAT,CHANNEL,CHUNK_SIZE);
	}
	MusicPlayer& getObject(){
		static MusicPlayer mpObj;
		return mpObj;
	}
	//loads a music, returns false if not able to load
	bool MusicPlayer::loadMusic(const std::string& musicFileName){
		_music = Mix_LoadWAV(musicFileName.c_str());
		return _music != NULL;
	}
	//sets the current channel for the music to be played on
	void MusicPlayer::setChannelToPlayOn(const int channel){
		_channel = channel;
	}
	//returns the current set channel
	const int MusicPlayer::getCurrentChannel()const{
		return _channel;
	}
	//plays the current music
	void MusicPlayer::play()const{
		//check if its being played already
		//if not then play it
		if(!Mix_Playing(_channel)){
			Mix_PlayChannel(_channel,_music,0); //play music
		}
		//else check if it has been paused
		else if( Mix_Paused(_channel) ){
			 Mix_Resume(_channel);
		}
	}
	//pauses the current music being played
	void MusicPlayer::pause()const{
		Mix_Pause(_channel);
	}
	void MusicPlayer::restart()const{
		Mix_PlayChannel(_channel,_music,0);
	}
	void MusicPlayer::registerEffectCallback(	const Mix_EffectFunc_t& effectFunc,
												const Mix_EffectDone_t& finishedFunc){
		Mix_RegisterEffect(_channel,effectFunc,finishedFunc,NULL);
	}
	void MusicPlayer::unregisterEffectCallback()const{
		Mix_UnregisterAllEffects(_channel);
	}
	MusicPlayer::~MusicPlayer(){
		Mix_FreeChunk(_music);
	}
	//private helper function
	void MusicPlayer::_doLazyInitialization(const int FREQUENCY,
											const int FORMAT,
											const int CHANNEL,
											const int CHUNK_SIZE){
		//check for initialization
		if(!_musicInfo.isAlreadyInitialized){
			//initialize audio components
			Mix_OpenAudio(FREQUENCY,FORMAT,CHANNEL,CHUNK_SIZE);
			_musicInfo = _MusicInfo(FREQUENCY,FORMAT,CHANNEL,CHUNK_SIZE);
			_musicInfo.isAlreadyInitialized = true;
		}
		else{ //initialized already so check if same parameter
			if( _musicInfo.frequency == FREQUENCY && _musicInfo.format == FORMAT &&
				_musicInfo.channel == CHANNEL && _musicInfo.chunkSize == CHUNK_SIZE){
				/* same parameter so no need for initialization */
			}
			else{ //different initialization parameter
				Mix_CloseAudio(); //close audio component
				Mix_OpenAudio(FREQUENCY,FORMAT,CHANNEL,CHUNK_SIZE); //re-initialize audio components
				_musicInfo = _MusicInfo(FREQUENCY,FORMAT,CHANNEL,CHUNK_SIZE);
				_musicInfo.isAlreadyInitialized = true;
			}
		}
	}
}
