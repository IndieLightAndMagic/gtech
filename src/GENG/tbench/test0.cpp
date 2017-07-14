#include <GENG/g.h>

using namespace GENG;
int main (){

	class GObx:public GOb{
		void update(){
			cout << "Updating object and making delay 10000 ms "<< typeid(this).name() << endl; 
			SDL_Delay(10000);
		}
	};

	GOb a;
	GObx b;
	GTh ta(NULL);
	GTh tb(NULL);
	
	ta.pushObject(&a);
	tb.pushObject(&b);
	SDL_Delay(30000);
	ta.killThread();
	tb.killThread();
	
	return 0;
}
