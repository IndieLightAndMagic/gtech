#include "G.h"

/* This class is an utility class that generates ids for camsample.cpp for free :) */
class StaticIds{
	static unsigned long int ids=0;
	static bool done = false;
public:
	static unsigned long int GetId(){
		if (!done){
			done = true;
			srand (time(NULL));
			ids = rand();
		}
		return ++ids;
	}
};


void GOb::initId(){
	m_id = StaticIds::GetId();
}


