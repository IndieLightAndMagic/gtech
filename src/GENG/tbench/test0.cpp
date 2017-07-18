#include <GENG/g.h>

using namespace GENG;
int main (){

	class GObx:public GOb{
		ui32 m_mscounter;

		void update(ui32 ui32msdelta){
			m_mscounter += ui32msdelta;	
			if (m_mscounter >= p_ui32top){
				cout << "Updating object and making delay "<< p_ui32top<<" ms "<< typeid(this).name() << endl; 
				m_mscounter = 0;
			}  
		}

	public:
		GObx():m_mscounter(0), p_ui32top(1000){}
		ui32 p_ui32top;
	};

	GObx a;
	GObx b;
	a.p_ui32top = 1000;
	b.p_ui32top = 5000;
	GTh ta(NULL);
	GTh tb(NULL);
	
	ta.pushObject(&a);
	tb.pushObject(&b);
	SDL_Delay(30000);
	ta.killThread();
	tb.killThread();
	
	return 0;
}
