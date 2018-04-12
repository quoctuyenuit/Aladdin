#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__
#include<dsound.h>
#include<Windows.h>
#include<map>
#include"Application.h"
#include"Global.h"
//============================================================
//BackGround
//============================================================
#define SOUND_BACKGOUND "Resources//Sound//BackGround.wav"
#define SOUND_BACKGROUND_BOSS "Resources//Sound//BossTune.wav"
#define SOUND_BACKGROUND_MENU "Resources//Sound//AWholeNewWorld.wav"
#define SOUND_LEVELCOMPLETE "Resources//Sound//LevelComplete.wav"
#define SOUND_BOXBELL "Resources//Sound//Boxing Bell.wav"
#define SOUND_GENIEFUMES "Resources//Sound//Genie_Fumes.wav"
#define SOUND_ROCK_BOUNCE "Resources//Sound//Rock_Bounce.wav"
//============================================================
//Map
//============================================================
#define SOUND_STICK "Resources//Sound//Flagpole.wav"
#define SOUND_FIRE_FROM_COAL "Resources//Sound//Fire_From_Coal.wav"
//============================================================
//Action
//============================================================
#define SOUND_HIGH_SWORD "Resources//Sound//High_Sword.wav"
#define SOUND_LOW_SWORD "Resources//Sound//Low_Sword.wav"
#define SOUND_SWORD_CHING "Resources//Sound//Sword_Ching.wav"
#define SOUND_OBJECT_THROW "Resources//Sound//Object_Throw.wav"
#define SOUND_OUTA_APPLE "Resources//Sound//Outta_Apples.wav"
#define SOUND_REACH_APPLE "Resources//Sound//Apple_Splat.wav"
#define SOUND_CLAY_POT "Resources//Sound//Clay_Pot.wav"
#define SOUND_CLOUD_POOF "Resources//Sound//Cloud_Poof.wav"
#define SOUND_POP "Resources//Sound//Balloon Pop.wav"
#define SOUND_STAR "Resources//Sound//Scarab Pickup.wav"
#define SOUND_GUN "Resources//Sound//Start Gun.wav"
#define SOUND_ILAGO "Resources//Sound//Iago Squawk.wav"
#define SOUND_ABU_WAVING "Resources//Sound//Abu Waving.wav"
#define SOUND_PEDDLERSHOP "Resources//Sound//Peddler Shop.wav"
#define SOUND_CASHREGISTER "Resources//Sound//Cash Register.wav"
#define SOUND_CASHFAILED "Resources//Sound//Eeeh.wav"

//============================================================
//Select
//============================================================
#define SOUND_MENU_CHANGE "Resources//Sound//Menu_Change.wav"
#define SOUND_MENU_SELECT "Resources//Sound//Menu_Select.wav"
//============================================================
//Speak
//============================================================
#define SOUND_ALADDIN_HURT "Resources//Sound//Aladdin_Hurt.wav"
#define SOUND_ALADDIN_OOF "Resources//Sound//Aladdin_Oof.wav"
#define SOUND_ALADDIN_PUSH "Resources//Sound//Aladdin_Push.wav"
#define SOUND_COMEON "Resources//Sound//Guard_Beckon.wav"
#define SOUND_GUARD_HIT1 "Resources//Sound//Guard_Hit_1.wav"
#define SOUND_GUARD_HIT2 "Resources//Sound//Guard_Hit_2.wav"
#define SOUND_GUARD_PAINTS "Resources//Sound//Guard_Pants.wav"
#define SOUND_JAFAR_LAUGH "Resources//Sound//Jafar_Laugh.wav"
#define SOUND_JAFAR_SNAKE "Resources//Sound//Jafar_Snake.wav"
#define SOUND_JAFAR_TRACTOR "Resources//Sound//Jafar_Tractor.wav"
#define SOUND_OOOH "Resources//Sound//Oooh.wav"
#define SOUND_CAMEL "Resources//Sound//Camel_Spit.wav"
#define SOUND_GENIE_FUMES "Resources//Sound//Genie_Fumes.wav"
#define SOUND_WOW "Resources//Sound//Wow.wav"
#define SOUND_YEAH "Resources//Sound//Yeah.wav"
//============================================================
//Item
//============================================================
#define SOUND_TAKE_GEM "Resources//Sound//Gem_Collect.wav"
#define SOUND_TAKE_APPLE "Resources//Sound//Apple_Slice.wav"
#define SOUND_TAKE_HEART "Resources//Sound//Extra_Health.wav"
#define SOUND_TAKE_JAR "Resources//Sound//Continue_Point.wav"

class Sound
{
public:
	struct WaveHeader
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
private:
	static Sound*				__instance;
	std::map<std::string, IDirectSoundBuffer8*> _listSoundBuffer;
	bool						_isMute;
	IDirectSoundBuffer*			_primaryBuffer;
	IDirectSound8*				_soundDevice;
	float						_volumne;
public:
	~Sound();
	static Sound*				Instance();
	float						getVolumne();
	void						setVolume(float percentage, std::string name = "");
	void						playBackGround(std::string name,  float volumne = -1, bool isLoop = true);
	void						play(std::string name, bool isLoop = false, int times = 1, float volumne = -1);
	void						stop(std::string name = "");
	void						mute();
	void						unMute();
	bool						isMute();
private:
	Sound();
	void						init();
	void						loadSound(char* path);

};

#endif __SOUND_H__