

#include <iostream>
#include <string>
#include <MESHCOMPONENT/GMeshComponent.h>

using namespace std;
int main (){

	cout << RES_DIR << endl;
	GAssimpLoaderComponent * loader = GAssimpLoaderComponent::openLoaderUsingResource(string(RES_DIR)+string("monkey.blend"));
	if (!loader)
	{
		cout << "Failed" << endl;
	}
	return 0;


}
