/*
 * GameContainerMac.hpp
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#ifndef GAMECONTAINERMAC_H_
#define GAMECONTAINERMAC_H_

#include "GameContainer.h"

class GameContainerMac
	: public GameContainer
{
public:
	GameContainerMac() = default;
	void WindowHints() const override;
};



#endif /* GAMECONTAINERMAC_H_ */
