/*
 * Controller.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */


#include "Controller.h"
#include "utils/Debug.h"

#ifdef DEBUG
	static char* pLoadedTextureLogBuffer;
	static char* pResolutionLogBuffer;
#endif
Controller::Controller() {
	m_Running = false;
	m_sceneHandler = new SceneHandler();
	m_inputHandler = new InputHandler();
	m_fontHandler = new FontHandler();
	m_basicCommandHandler = new CBasicCommandHandler();

#ifdef DEBUG
	pLoadedTextureLogBuffer = new char[50];
	pResolutionLogBuffer = new char[30];
#endif
}

Controller::~Controller() {}



void Controller::Start()
{
	m_Running = true;

	Init();

	m_basicCommandHandler->ExecuteCommand( SwitchToIntroCommand::Name() );

	while( m_Running )
	{
		GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

		m_inputHandler->Update();
		m_sceneHandler->Update();
		m_sceneHandler->DrawScene();

#ifdef DEBUG
		printGameVersion(0, 25, m_fontHandler->GetNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE );
		printFps( 500, 25, m_fontHandler->GetNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_YELLOW );

		sprintf(pResolutionLogBuffer, "Resolution x: %d y: %d", rmode->viWidth, rmode->viHeight );
		Debug::GetInstance().Log(pResolutionLogBuffer);

		sprintf(pLoadedTextureLogBuffer, "Loaded Textures in scene: %d", m_sceneHandler->GetCurrentScene().GetTextureHandler().TextureCount());
		Debug::GetInstance().Log( pLoadedTextureLogBuffer );

		Debug::GetInstance().Print();
		Debug::GetInstance().Clear();
#endif

		GRRLIB_Render();
		calculateFrameRate();
	}

	delete m_basicCommandHandler;
	delete m_sceneHandler;
	delete m_inputHandler;
	delete m_fontHandler;

#ifdef DEBUG
	delete [] pResolutionLogBuffer;
	delete [] pLoadedTextureLogBuffer;
#endif

	GRRLIB_Exit();
}

void Controller::End() {
	m_Running = false;
}

void Controller::Init() {

	GRRLIB_Init();
	GRRLIB_Settings.antialias = true;

	m_fontHandler->Init();
	m_inputHandler->Init();
	m_sceneHandler->Init();
	m_basicCommandHandler->Init();
}

void Controller::SwitchToNextScene()
{
	m_sceneHandler->LoadNextScene();
}

SceneHandler& Controller::GetSceneHandler()
{
	return *m_sceneHandler;
}

InputHandler& Controller::GetInputHandler()
{
	return *m_inputHandler;
}

FontHandler& Controller::GetFontHandler()
{
	return *m_fontHandler;
}

CBasicCommandHandler& Controller::GetBasicCommandHandler()
{
	return *m_basicCommandHandler;
}
