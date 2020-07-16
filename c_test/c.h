#include "b.h"

#pragma once
class C : public B{
	int c;
	virtual void ha();
};
void C :: ha(){
	c = 10;
	return;
}
