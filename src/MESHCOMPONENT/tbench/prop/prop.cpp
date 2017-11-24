

#include <MESHCOMPONENT/GMaterialComponent.h>

using namespace std;


int main(void)
{
	//A 10 Bytes in Size Property.
	std::unique_ptr<IGPropertyValue> pprop = std::make_unique<GPropertyValue<int>>();

	cout << "Test program for GMaterialComponent\n";
	return 0;
}