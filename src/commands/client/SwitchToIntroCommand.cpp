/*
 * SwitchToIntroCommand.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "SwitchToIntroCommand.h"

SwitchToIntroCommand::SwitchToIntroCommand() {
	// TODO Auto-generated constructor stub

}

SwitchToIntroCommand::~SwitchToIntroCommand() {
	// TODO Auto-generated destructor stub
}

void SwitchToIntroCommand::ExecuteCommand() {
	Controller::GetInstance().GetSceneHandler().LoadScene( INTRO_SCENE_ID );
}
