/*
 * BasicButton.cpp
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#include <math.h>
#include "BasicButton.h"
#include "../../handler/Controller.h"
#include "../../utils/Debug.h"
#include <grrlib.h>

BasicButton::BasicButton( float x, float y, const char* name, Texture* defaultTexture, Texture* highlightTexture, LabelTexture* label, OnClickCallback clickCallback  ) : m_label( label ), m_highlightTexture( highlightTexture ), m_clickCallback( clickCallback ), UITextureElement( x, y, 0, 0, name, defaultTexture )
{
	m_texture->setX( x );
	m_texture->setY( y );
	m_highlightTexture->setX( x );
	m_highlightTexture->setY( y );
	m_highlightTexture->setVisible(false);
	initLabel();
}

BasicButton::~BasicButton() {
}


void BasicButton::update() {
	// todo check click in cursor component or somewhere else
	if ( handleMoveOver() )
	{
		handleOnClick();
	}

}

bool BasicButton::handleMoveOver() {

	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );

	/*bool mouseOver = pad->getX() >= m_texture->getX() && pad->getX() <= (m_texture->getX() + m_texture->getWidth())
							&& pad->getY() >= m_texture->getY() && pad->getY() <= (m_texture->getY() + m_texture->getHeight());
	 */

	bool mouseOver = GRRLIB_PtInRect(m_texture->getX(), m_texture->getY(), m_texture->getWidth(), m_texture->getHeight(), pad->getX(), pad->getY() );
	if ( mouseOver )
	{
		char* clickedIn = new char[50];
		sprintf(clickedIn, "Mouse over" );
		Debug::getInstance().log( clickedIn );
	}

	m_texture->setVisible(!mouseOver);
	m_highlightTexture->setVisible(mouseOver);

	return mouseOver;
}

void BasicButton::handleOnClick() {

	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );

	if ( (pad->buttonsHeld() & WPAD_BUTTON_A) && m_clickCallback )
	{
		m_clickCallback(this);
	}
}

void BasicButton::setColor(u32 color)
{
	m_texture->setColor(color);
	m_highlightTexture->setColor(color);

}

u32 BasicButton::getColor(){
	return m_texture->getColor();
}

void BasicButton::initLabel()
{
	unsigned int newFontSize = m_texture->getHeight() - (2*BUTTON_LABEL_DISTANCE);
	m_label->setFontSize( newFontSize );
	m_label->setY( m_texture->getY() + BUTTON_LABEL_DISTANCE );

	unsigned int textWidthInPixel = GRRLIB_WidthTTF(m_label->getFont(), m_label->getText(), m_label->getFontSize());
	m_label->setX(m_texture->getX() + (( m_texture->getWidth() / 2) - (textWidthInPixel / 2)));
}


