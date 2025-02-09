#include "Game.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gOptionButton[BUTTON_TOTAL];
SDL_Rect gExitOptionButton[BUTTON_TOTAL];
SDL_Rect gHardModeButton[BUTTON_TOTAL];
SDL_Rect gEasyModeButton[BUTTON_TOTAL];
SDL_Rect gSoundButton[BUTTON_TOTAL];
SDL_Rect gMusicButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gChooseSonicButton[BUTTON_TOTAL];
SDL_Rect gChooseShadowButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gFlyingEnemyClips[FLYING_ENEMY_FRAMES];
SDL_Rect gGroundEnemyClips[GROUND_ENEMY_FRAMES];

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gOptionTexture;
LTexture gBackgroundTexture;
LTexture gCharacterTexture;
LTexture gSonicTexture;
LTexture gSonicTextureHasShield;
LTexture gShadowTexture;
LTexture gShadowTextureHasShield;
LTexture gGroundTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gOptionButtonTexture;
LTexture gExitOptionButtonTexture;
LTexture gHardModeButtonTexture;
LTexture gEasyModeButtonTexture;
LTexture gSoundButtonTexture;
LTexture gMusicButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gChooseSonicButtonTexture;
LTexture gChooseShadowButtonTexture;
LTexture gChooseCharacterBackGroundTexture;
LTexture gLoseTexture;
LTexture g0live;
LTexture g1live;
LTexture g2live;
LTexture g3live;
LTexture gText1Texture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button OptionButton(OPTION_BUTTON_POSX, OPTION_BUTTON_POSY);
Button ExitOptionButton(EXIT_OPTION_BUTTON_POSX, EXIT_OPTION_BUTTON_POSY);
Button HardModeButton(HARD_MODE_BUTTON_POSX, HARD_MODE_BUTTON_POSY);
Button EasyModeButton(EASY_MODE_BUTTON_POSX, EASY_MODE_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button ChooseSonicButton(CHOOSE_SONIC_BUTTON_POSX, CHOOSE_SONIC_BUTTON_POSY);
Button ChooseShawdownButton(CHOOSE_SHADOW_BUTTON_POSX, CHOOSE_SHADOW_BUTTON_POSY);
Button SoundButton(SOUND_BUTTON_POSX, SOUND_BUTTON_POSY);
Button MusicButton(MUSIC_BUTTON_POSX, MUSIC_BUTTON_POSY);

void Game :: gameLoop()
{
    if(!Init())printf("Failed to initialize!\n");
	else std::cout << "Succeeded to initialize" << std::endl;
	
	if (!LoadMedia())printf("Failed to load media!\n");
	else std::cout << "Succeeded to load media" << std::endl;

	Mix_PlayMusic(gMusic, IS_REPEATITIVE);
	
	while(!Quit_Menu || Play)
	{
		if(MusicButton.currentSprite == BUTTON_MOUSE_OVER)Mix_ResumeMusic();
		else Mix_PauseMusic();
		while (!Quit_Menu)
		{
			SDL_Event e_mouse;
			while (SDL_PollEvent(&e_mouse) != 0)
			{
				if (e_mouse.type == SDL_QUIT)
				{
					Quit_Menu = true;
					Play = false;
				}

				HandlePlayButton(&e_mouse, gChooseSonicButton, gChooseShadowButton, PlayButton,
									ChooseSonicButton, ChooseShawdownButton, gChooseSonicButtonTexture,
									gChooseShadowButtonTexture, gChooseCharacterBackGroundTexture,
									gCharacterTexture, gSonicTexture, gShadowTexture,
									gRenderer, Quit_Menu, Play, gClick);
					
				HandleHelpButton(&e_mouse, gBackButton,
									HelpButton, BackButton, 
									gInstructionTexture, gBackButtonTexture,
									gRenderer, Quit_Menu, gClick);

				HandleOptionButton(&e_mouse, gExitOptionButton, gHardModeButton,
									gEasyModeButton,OptionButton, HardModeButton,
									EasyModeButton, ExitOptionButton,
									gOptionTexture,gHardModeButtonTexture,
									gEasyModeButtonTexture, gExitOptionButtonTexture, 
									gRenderer, Quit_Menu, gameMode, gClick);

				HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

				HandleSoundButton(&e_mouse, gSoundButton, SoundButton, gClick, gJump, gLose);

				HandleMusicButton(&e_mouse, gMusicButton, MusicButton);

			}

			gMenuTexture.Render(0, 0, gRenderer);
			
			SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
			PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

			SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
			HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

			SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
			ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

			SDL_Rect* currentClip_Option = &gOptionButton[OptionButton.currentSprite];
			OptionButton.Render(currentClip_Option, gRenderer, gOptionButtonTexture);

			SDL_Rect* currentClip_Sound = &gSoundButton[SoundButton.currentSprite];
			SoundButton.Render(currentClip_Sound, gRenderer, gSoundButtonTexture);

			SDL_Rect* currentClip_Music = &gMusicButton[MusicButton.currentSprite];
			MusicButton.Render(currentClip_Music, gRenderer, gMusicButtonTexture);

			SDL_RenderPresent(gRenderer); //present the rendered textures to the screen
		}
		
		while (Play)// handle play again
		{
			SDL_Event e;
			Character character;
			PowerUp shield;
			PowerUp live;
			Enemy enemy1(ON_GROUND_ENEMY);
			Enemy enemy2(ON_GROUND_ENEMY);
			Enemy enemy3(IN_AIR_ENEMY);
			srand(time(NULL));
			
			GenerateEnemy(enemy1, enemy2, enemy3, gFlyingEnemyClips, gGroundEnemyClips, gRenderer);
			
			SetGameMode(character.lives);
			while (!Die)
			{
				if (Game_State)
				{
					UpdateGameTimeAndScore(currentTime, acceleration, score);

					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							Die = true;
							Play = false;
						}

						if (e.type == SDL_KEYDOWN)
						{
							switch (e.key.keysym.sym)
							{
							case SDLK_ESCAPE:
								Die = true;
								Play = false;
								Quit_Menu = false;
								break;
							}
						}
						HandlePauseButton(&e, gRenderer, gContinueButton,
							PauseButton, ContinueButton,
							gContinueButtonTexture, Game_State, Die, Play, gClick);// Quit và play thêm để SDL_Quit khi đang dừng game

						character.HandleEvent(e, gJump);//change the status to jump
					}

					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);//Clear để render lại

					RenderScrollingBackground(OffsetSpeed_Bkgr, gBackgroundTexture, gRenderer);
					RenderScrollingGround(OffsetSpeed_Ground, acceleration, gGroundTexture, gRenderer);

					DrawPlayerScore(gText1Texture, gScoreTexture, textColor, gRenderer, gFont, score);
					DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);

					SDL_Rect* currentClip_Character = nullptr;
					currentClip_Character = &gCharacterClips[frame_Character / SLOW_FRAME_CHAR];
					character.Move();
					character.Render(currentClip_Character, gRenderer, gCharacterTexture);

					SDL_Rect* currentClip_GroundEnemy1 = &gGroundEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
					enemy1.Move(acceleration);
					enemy1.Render(gRenderer, currentClip_GroundEnemy1);

					SDL_Rect* currentClip_GroundEnemy2 = &gGroundEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
					enemy2.Move(acceleration);
					enemy2.Render(gRenderer, currentClip_GroundEnemy2);

					SDL_Rect* currentClip_FlyingEnemy = &gFlyingEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
					enemy3.Move(acceleration);
					enemy3.Render(gRenderer, currentClip_FlyingEnemy);

					SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
					PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);
					
					if(score % 200 == 0)
					{
						shield.isGenerated = true;
						GeneratePowerUp(shield, gRenderer, SHIELD);
					}
					if(score % 300 == 0)
					{
						live.isGenerated = true;
						GeneratePowerUp(live, gRenderer, LIVE);
					}

					if(shield.isGenerated)
					{
						shield.Move(acceleration, SHIELD);
						shield.Render(gRenderer);
					}
					if(live.isGenerated)
					{
						live.Move(acceleration, LIVE);
						live.Render(gRenderer);
					}

					if(shield.GetPosX() < 0)
					{
						shield.~PowerUp();
						shield.isGenerated = false;
					}
					if(live.GetPosX() < 0)
					{
						live.~PowerUp();
						live.isGenerated = false;
					}

					if (CheckPowerUpColission(character, currentClip_Character, shield))
					{

						shield.powerUpTimer = SDL_GetTicks();
						character.haveShield = true;
						shield.~PowerUp();
						if(gCharacterTexture.GetTexture() == gShadowTexture.GetTexture())gCharacterTexture = gShadowTextureHasShield;
						if(gCharacterTexture.GetTexture() == gSonicTexture.GetTexture())gCharacterTexture = gSonicTextureHasShield;
						std::cout << "Character has shield" << std::endl;
					}
					if(CheckPowerUpColission(character, currentClip_Character, live))
					{
						if(character.lives < 3)character.lives++;
						live.~PowerUp();
						live.isGenerated = false;
					}

					if(character.haveShield)
					{
						shield.currentTime = SDL_GetTicks();
						if (shield.currentTime - shield.powerUpTimer >= 5000) {
							if(gCharacterTexture.GetTexture() == gShadowTextureHasShield.GetTexture())gCharacterTexture = gShadowTexture;
							if(gCharacterTexture.GetTexture() == gSonicTextureHasShield.GetTexture())gCharacterTexture = gSonicTexture;
							std::cout << "Character lost shield" << std::endl;
							character.haveShield = false;
						}
					}
					
					if (!character.haveShield)
					{
						if (CheckEnemyColission(character,
						enemy1, enemy2, enemy3,
						currentClip_Character, currentClip_FlyingEnemy, 
						currentClip_GroundEnemy1, currentClip_GroundEnemy2))
						{
							Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
							character.ResetCharacter(Die);
							enemy1.resetEnemy();
							enemy2.resetEnemy();
							enemy3.resetEnemy();
						}
					}

					if(character.lives == 1)g1live.Render(LIVES_POSX, LIVES_POSY, gRenderer);
					else if(character.lives == 2)g2live.Render(LIVES_POSX, LIVES_POSY, gRenderer);
					else if(character.lives == 3)g3live.Render(LIVES_POSX, LIVES_POSY, gRenderer);
					else if(character.lives == 0)
					{
						g0live.Render(LIVES_POSX, LIVES_POSY, gRenderer);
						Mix_PauseMusic();
						UpdateHighScore("high_score.txt", score, highscore);
						Die = true;
					}

					SDL_RenderPresent(gRenderer);// Present tất cả những cái ở phía trên

					ControlCharFrame(frame_Character);
					ControlEnemyFrame(frame_Enemy);
				}
			}

			if(AskToPlayAgain(gLoseTexture, &e, gRenderer, Play, Quit_Menu))
			{

				ResetGame();
				character.ResetCharacter(Die);
				if(MusicButton.currentSprite == BUTTON_MOUSE_OVER)Mix_ResumeMusic();
			}else{
				ResetGame();
				enemy1.~Enemy();
				enemy2.~Enemy();
				enemy3.~Enemy();
				
			}
		}
	}
	Close();
	return;
}

//Reset when player want to play again
void Game :: ResetGame()
{

	Die = false;
	Game_State = true;
    currentTime = 0;
    score = 0;
    acceleration = 0;
    frame_Character = 0;
    frame_Enemy = 0;

    OffsetSpeed_Ground = BASE_OFFSET_SPEED;
	OffsetSpeed_Bkgr = BASE_OFFSET_SPEED;
}

void Game :: SetGameMode(int &lives)
{
	if(gameMode == HARD_MODE)
	{
		acceleration = 3;
		lives = 1;
	}
	else
	{
		acceleration = 0;
		lives = 3;
	}
}

bool Game::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game :: LoadMedia()
{
	bool success = true;

	gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load background music", MIX_ERROR);
		success = false;
	}

	gClick = Mix_LoadWAV("sound/mouse_click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}

	gJump = Mix_LoadWAV("sound/jump_sound.wav");
	if (gJump == nullptr)
	{
		LogError("Failed to load jumping sound", MIX_ERROR);
		success = false;
	}

	gLose = Mix_LoadWAV("sound/lose_sound.wav");
	if (gLose == nullptr)
	{
		LogError("Failed to load lose sound", MIX_ERROR);
		success = false;
	}

	else
	{
		gFont = TTF_OpenFont("font/G4 2004.ttf", 28);
		if (gFont == NULL)
		{
			LogError("Failed to load font", MIX_ERROR);
			std::cout << std::endl;
			success = false;
		}
		else
		{
			if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text1 texture" << std::endl;
				success = false;
			}

			if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text2 texture" << std::endl;
				success = false;
			}
			
			if (!gMenuTexture.LoadFromFile("imgs/background/menu.png", gRenderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}

			if (!gInstructionTexture.LoadFromFile("imgs/background/instruction.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!gOptionTexture.LoadFromFile("imgs/background/option.png", gRenderer))
			{
				std::cout << "Failed to load option image" << std::endl;
				success = false;
			}

			if (!g0live.LoadFromFile("imgs/other/0lives.png", gRenderer))
			{
				std::cout << "Failed to load 1lives image" << std::endl;
				success = false;
			}

			if (!g1live.LoadFromFile("imgs/other/1lives.png", gRenderer))
			{
				std::cout << "Failed to load 1lives image" << std::endl;
				success = false;
			}

			if (!g2live.LoadFromFile("imgs/other/2lives.png", gRenderer))
			{
				std::cout << "Failed to load 2lives image" << std::endl;
				success = false;
			}

			if (!g3live.LoadFromFile("imgs/other/3lives.png", gRenderer))
			{
				std::cout << "Failed to load 3lives image" << std::endl;
				success = false;
			}


			if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", gRenderer))
			{
				std::cout << "Failed to load play_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)// một mảng chứa từng frame trong clip playButton
				{
					gPlayButton[i].x = PLAY_BUTON_WIDTH * i; // vị trị frame trong play_button.png
					gPlayButton[i].y = 0;
					gPlayButton[i].w = PLAY_BUTON_WIDTH;
					gPlayButton[i].h = PLAY_BUTON_HEIGHT;
				}
			}

			if (!gHelpButtonTexture.LoadFromFile("imgs/button/big_button/help_button.png", gRenderer))
			{
				std::cout << "Failed to load help_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHelpButton[i].x = HELP_BUTTON_WIDTH * i;
					gHelpButton[i].y = 0;
					gHelpButton[i].w = HELP_BUTTON_WIDTH;
					gHelpButton[i].h = HELP_BUTTON_HEIGHT;
				}
			}

			if (!gBackButtonTexture.LoadFromFile("imgs/button/big_button/back_button.png", gRenderer))
			{
				std::cout << "Failed to load back_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i].x = BACK_BUTTON_WIDTH * i;
					gBackButton[i].y = 0;
					gBackButton[i].w = BACK_BUTTON_WIDTH;
					gBackButton[i].h = BACK_BUTTON_HEIGHT;
				}
			}

			if (!gExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", gRenderer))
			{
				std::cout << "Failed to load exit_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitButton[i].x = EXIT_BUTTON_WIDTH * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = EXIT_BUTTON_WIDTH;
					gExitButton[i].h = EXIT_BUTTON_HEIGHT;
				}
			}

			if (!gOptionButtonTexture.LoadFromFile("imgs/button/big_button/option_button.png", gRenderer))
			{
				std::cout << "Failed to load option button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gOptionButton[i].x = OPTION_BUTTON_WIDTH * i;
					gOptionButton[i].y = 0;
					gOptionButton[i].w = OPTION_BUTTON_WIDTH;
					gOptionButton[i].h = OPTION_BUTTON_HEIGHT;
				}
			}

			if (!gHardModeButtonTexture.LoadFromFile("imgs/button/big_button/hard_button.png", gRenderer))
			{
				std::cout << "Failed to load hard button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHardModeButton[i].x = HARD_MODE_BUTTON_WIDTH * i;
					gHardModeButton[i].y = 0;
					gHardModeButton[i].w = HARD_MODE_BUTTON_WIDTH;
					gHardModeButton[i].h = HARD_MODE_BUTTON_HEIGHT;
				}
			}

			if (!gEasyModeButtonTexture.LoadFromFile("imgs/button/big_button/easy_button.png", gRenderer))
			{
				std::cout << "Failed to load Easy button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gEasyModeButton[i].x = EASY_MODE_BUTTON_WIDTH * i;
					gEasyModeButton[i].y = 0;
					gEasyModeButton[i].w = EASY_MODE_BUTTON_WIDTH;
					gEasyModeButton[i].h = EASY_MODE_BUTTON_HEIGHT;
				}
			}


			if (!gExitOptionButtonTexture.LoadFromFile("imgs/button/big_button/exit_option_button.png", gRenderer))
			{
				std::cout << "Failed to load exit option button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitOptionButton[i].x = EXIT_OPTION_BUTTON_WIDTH * i;
					gExitOptionButton[i].y = 0;
					gExitOptionButton[i].w = EXIT_OPTION_BUTTON_WIDTH;
					gExitOptionButton[i].h = EXIT_OPTION_BUTTON_WIDTH;
				}
			}

			if (!gSoundButtonTexture.LoadFromFile("imgs/button/small_button/sound_button.png", gRenderer))
			{
				std::cout << "Failed to load sound button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gSoundButton[i].x = SOUND_BUTTON_WIDTH * i;
					gSoundButton[i].y = 0;
					gSoundButton[i].w = SOUND_BUTTON_WIDTH;
					gSoundButton[i].h = SOUND_BUTTON_HEIGHT;
				}
			}

			if (!gMusicButtonTexture.LoadFromFile("imgs/button/small_button/music_button.png", gRenderer))
			{
				std::cout << "Failed to load music button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gMusicButton[i].x = MUSIC_BUTTON_WIDTH * i;
					gMusicButton[i].y = 0;
					gMusicButton[i].w = MUSIC_BUTTON_WIDTH;
					gMusicButton[i].h = MUSIC_BUTTON_HEIGHT;
				}
			}

			if (!gPauseButtonTexture.LoadFromFile("imgs/button/small_button/pause_button.png", gRenderer))
			{
				std::cout << "Failed to load pause_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPauseButton[i].x = PAUSE_AND_CONTINUE_BUTTON_WIDTH * i;
					gPauseButton[i].y = 0;
					gPauseButton[i].w = PAUSE_AND_CONTINUE_BUTTON_WIDTH;
					gPauseButton[i].h = PAUSE_AND_CONTINUE_BUTTON_HEIGHT;
				}
			}

			if (!gContinueButtonTexture.LoadFromFile("imgs/button/small_button/continue_button.png", gRenderer))
			{
				std::cout << "Failed to load continue_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gContinueButton[i].x = PAUSE_AND_CONTINUE_BUTTON_WIDTH * i;
					gContinueButton[i].y = 0;
					gContinueButton[i].w = PAUSE_AND_CONTINUE_BUTTON_WIDTH;
					gContinueButton[i].h = PAUSE_AND_CONTINUE_BUTTON_HEIGHT;
				}
			}

			
			if (!gBackgroundTexture.LoadFromFile("imgs/background/layer.jpg", gRenderer))
			{
				std::cout << "Failed to load background image" << std::endl;
				success = false;
			}
			

			if (!gGroundTexture.LoadFromFile("imgs/background/ground.png", gRenderer))
			{
				std::cout << "Failed to load ground image" << std::endl;
				success = false;
			}

			if (!gSonicTexture.LoadFromFile("imgs/character/sonic.png", gRenderer))
			{
				std::cout << "Failed to load sonic_run image." << std::endl;
				success = false;
			}
			if (!gSonicTextureHasShield.LoadFromFile("imgs/character/sonicHasShield.png", gRenderer))
			{
				std::cout << "Failed to load sonic_run has shield image." << std::endl;
				success = false;
			}
			if (!gShadowTexture.LoadFromFile("imgs/character/shadow.png", gRenderer))
			{
				std::cout << "Failed to load shadow_run image." << std::endl;
				success = false;
			}
			if (!gShadowTextureHasShield.LoadFromFile("imgs/character/shadowHasShield.png", gRenderer))
			{
				std::cout << "Failed to load shadow_run has shield image." << std::endl;
				success = false;
			}
			else
			{
				gCharacterClips[0].x = CHARACTER_FRAME_WIDTH * 0;
				gCharacterClips[0].y = 0;
				gCharacterClips[0].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[0].h = CHARACTER_FRAME_HEIGHT;

				gCharacterClips[1].x = CHARACTER_FRAME_WIDTH * 1;
				gCharacterClips[1].y = 0;
				gCharacterClips[1].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[1].h = CHARACTER_FRAME_HEIGHT;

				gCharacterClips[2].x = CHARACTER_FRAME_WIDTH * 2;
				gCharacterClips[2].y = 0;
				gCharacterClips[2].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[2].h = CHARACTER_FRAME_HEIGHT;

				gCharacterClips[3].x = CHARACTER_FRAME_WIDTH * 3;
				gCharacterClips[3].y = 0;
				gCharacterClips[3].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[3].h = CHARACTER_FRAME_HEIGHT;
			}

			if (!gLoseTexture.LoadFromFile("imgs/background/lose.png", gRenderer))
			{
				std::cout << "Failed to load lose image." << std::endl;
				success = false;
			}
			
			if (!gChooseShadowButtonTexture.LoadFromFile("imgs/button/big_button/blackSonic.png", gRenderer))
			{
				std::cout << "Failed to load shadow button image." << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gChooseShadowButton[i].x = CHOOSE_CHARACTER_BUTTON_WIDTH * i;
					gChooseShadowButton[i].y = 0;
					gChooseShadowButton[i].w = CHOOSE_CHARACTER_BUTTON_WIDTH;
					gChooseShadowButton[i].h = CHOOSE_CHARACTER_BUTTON_HEIGHT;
				}
			}

			if (!gChooseSonicButtonTexture.LoadFromFile("imgs/button/big_button/blueSonic.png", gRenderer))
			{
				std::cout << "Failed to load sonic button image." << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gChooseSonicButton[i].x = CHOOSE_CHARACTER_BUTTON_WIDTH * i;
					gChooseSonicButton[i].y = 0;
					gChooseSonicButton[i].w = CHOOSE_CHARACTER_BUTTON_WIDTH;
					gChooseSonicButton[i].h = CHOOSE_CHARACTER_BUTTON_HEIGHT;
				}
			}

			if (!gChooseCharacterBackGroundTexture.LoadFromFile("imgs/background/characterSelectionBg.png", gRenderer))
			{
				std::cout << "Failed to load choose character background image" << std::endl;
				success = false;
			}
		}
	}
	return success;
}

void Game::Close()
{
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gOptionTexture.Free();
	gCharacterTexture.Free();
	gSonicTexture.Free();
	gSonicTextureHasShield.Free();
	gShadowTexture.Free();
	gShadowTextureHasShield.Free();
	gGroundTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gOptionButtonTexture.Free();
	gExitOptionButtonTexture.Free();
	gHardModeButtonTexture.Free();
	gEasyModeButtonTexture.Free();
	gSoundButtonTexture.Free();
	gMusicButtonTexture.Free();
	gExitButtonTexture.Free();
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	gLoseTexture.Free();
	gText1Texture.Free();
	gScoreTexture.Free();
	gText2Texture.Free();
	gHighScoreTexture.Free();
	g1live.Free();
	g2live.Free();
	g3live.Free();

	gChooseShadowButtonTexture.Free();
	gChooseSonicButtonTexture.Free();
	gChooseCharacterBackGroundTexture.Free();
	
	gBackgroundTexture.Free();
	

	Mix_FreeMusic(gMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	gMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	std::cout << "Free everything!" << std::endl;
}