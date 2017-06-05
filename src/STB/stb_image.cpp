#include "stb_image.h"





/* TEST_BENCH */
#ifdef TEST_BENCH
#include <iostream>
using namespace std;
int main (int argc, char ** argv){
	
	stbi_uc * p_imageData = 0x0;
	cout << "Argc: " << argc << endl;
	if (argc == 1 ){
		cout << "Usage: stbtest {image_file}" << endl;

	} else if (argc >= 2) { 

		int index;
		for (index = 1; index< argc; index++) {
			int x,y,channels;
			p_imageData = 0x0;
			p_imageData = stbi_load(argv[index],&x,&y,&channels,3);

			if (!p_imageData) {
				cout << "Problems trying to load: " << argv[index] << endl;
				continue;
			}
			cout << "Image " <<  argv[index] << " W x H : " << x << "x" <<  y << " Channels [" << channels << "]" << endl; 

			cout<< "Releasing image memory...." << endl;
			stbi_image_free(p_imageData);

		}
	}

	return 0;
}
#endif 
/* TEST_BENCH */