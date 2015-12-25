/*
 * MainMenuScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "MainMenuScene.h"
#include "Cursor_png.h"
#include "ClassicBackgroundSprite_png.h"
#include "BasicButtonBig_png.h"
#include "BasicButtonBigHighlight_png.h"
#include "MinecraftLogo_png.h"
#include "../../utils/Debug.h"
#include "Hotbar_png.h"

// define all component names here!
#define MMS_BUTTON_SINGLEPLAYER "MMS_btnSingleplayer"
#define MMS_BUTTON_MULTIPLAYER "MMS_btnMultiplayer"
#define MMS_BUTTON_OPTION "MMS_btnOption"
#define MMS_BUTTON_EXIT "MMS_btnExit"
#define MMS_CLASSIC_BACKGROUND "MMS_ClassicBackground"
#define MMS_LOGO "MMS_Logo"
#define MMS_CURSOR "MMS_Cursor"


#define BUTTON_Y_DISTANCE 5


static void onButtonClicked(BasicButton* clickedButton) {
	if ( strcmp( clickedButton->getName(), MMS_BUTTON_SINGLEPLAYER ) == 0 )
	{
		Controller::getInstance().getBasicCommandHandler()->executeCommand( SwitchToInGameCommand::Name() );
	}
	// ..
}


MainMenuScene::MainMenuScene() {

}

MainMenuScene::~MainMenuScene() {

}

void MainMenuScene::load() {

	m_elements.push_back( new ClassicBackground( MMS_CLASSIC_BACKGROUND , m_TextureHandler->createTexture( ClassicBackgroundSprite_png )));
	Logo* logo = new Logo( MMS_LOGO , m_TextureHandler->createTexture( MinecraftLogo_png));
	logo->setY( 30 );
	m_elements.push_back( logo );

	createButtons();
	m_elements.push_back( new Cursor( MMS_CURSOR , m_TextureHandler->createTexture( Cursor_png )));
}

void MainMenuScene::draw() {
	GRRLIB_SetBackgroundColour(0x24, 0x5E, 0x23, 1);
	Basic2DScene::draw();
}

void MainMenuScene::update() {
	Basic2DScene::update();

	// todo kperdlich - just debug stuff, add debug preprocessor definition
	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );
	if ( pad->buttonsDown() & WPAD_BUTTON_LEFT)
	{
		Controller::getInstance().getBasicCommandHandler()->executeCommand( SwitchToIntroCommand::Name() );
	}
	else if ( pad->buttonsHeld() & WPAD_BUTTON_RIGHT )
	{
		Controller::getInstance().getBasicCommandHandler()->executeCommand( SwitchToInGameCommand::Name() );
	}
}

void MainMenuScene::createButtons()
{
	// todo kperdlich - create & use list component with buttons
	FontHandler* fontHandler = Controller::getInstance().getFontHandler();

	Texture* startButtonTexture = createTexture( BasicButtonBig_png );
	float xPos = (rmode->viWidth / 2) - (startButtonTexture->getWidth() / 2);
	float yPos = (rmode->viHeight / 2) - ( startButtonTexture->getHeight() / 2 );

	m_elements.push_back( new BasicButton( xPos, yPos, MMS_BUTTON_SINGLEPLAYER, startButtonTexture, createTexture( BasicButtonBigHighlight_png ), m_TextureHandler->createLabel( 0, 0, "Singleplayer", fontHandler->getNativFontByID( DEFAULT_MINECRAFT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE), &onButtonClicked ));

	yPos += startButtonTexture->getHeight() + BUTTON_Y_DISTANCE;
	m_elements.push_back( new BasicButton( xPos, yPos, MMS_BUTTON_MULTIPLAYER, createTexture( BasicButtonBig_png ), createTexture( BasicButtonBigHighlight_png ), m_TextureHandler->createLabel( 0, 0, "Multiplayer", fontHandler->getNativFontByID( DEFAULT_MINECRAFT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE), NULL ));

	yPos += startButtonTexture->getHeight() + BUTTON_Y_DISTANCE;
	m_elements.push_back( new BasicButton( xPos, yPos, MMS_BUTTON_OPTION, createTexture( BasicButtonBig_png ), createTexture( BasicButtonBigHighlight_png ), m_TextureHandler->createLabel( 0, 0, "Option", fontHandler->getNativFontByID( DEFAULT_MINECRAFT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE), NULL ));

	yPos += startButtonTexture->getHeight() + BUTTON_Y_DISTANCE;
	m_elements.push_back( new BasicButton( xPos, yPos, MMS_BUTTON_EXIT, createTexture( BasicButtonBig_png ), createTexture( BasicButtonBigHighlight_png ), m_TextureHandler->createLabel( 0, 0, "Exit", fontHandler->getNativFontByID( DEFAULT_MINECRAFT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE), NULL ));
}
