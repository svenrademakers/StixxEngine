#ifndef GAMECONTAINER_HPP
#define	GAMECONTAINER_HPP

class GameContainer
{
public:
	virtual ~GameContainer(){};
	virtual void WindowHints() const = 0;
};
#endif
