


#include "g.h"



namespace GENG{ 


void GOb::update(){
	cout << "Updating object and making delay 1000 ms "<< typeid(this).name() << endl; 
	SDL_Delay(1000);
}




GTh::GTh(void * param):
m_pP(param),
bTAlive(false)
{
	cout <<"+"<<typeid(this).name()<<endl; 

}
GTh::~GTh(){
	cout <<"-"<<typeid(this).name()<<endl;
}

int threadHelper(void * pv){
	GTh * pt = (GTh*)pv;
	while (pt->isAlive())
		pt->run(); 
	return 0;
}
int GTh::run(){


	for (int i = 0; i<m_vO.size(); i++){
		m_vO[i]->update();
	}

	return 0;

}
void GTh::pushObject(GOb* pxO){


	for (int i = 0 ; i < m_vO.size() ; i++){
		if (m_vO[i] == pxO) return;
	}
	m_vO.push_back(pxO);
	
	if (!bTAlive){
		bTAlive = true;
		m_pxT = SDL_CreateThread(threadHelper,"GThThread",this);
		SDL_DetachThread(m_pxT);
	} 
}


};





