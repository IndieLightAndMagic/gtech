
#include <map>
#include <string>
#include <iostream> 

#include <MESHCOMPONENT/GMaterialComponent.h>
using namespace std;


int main(void)
{
	//An integer property of size 10.
	GPropertyValue<int> pprop;
	pprop.setPropertyValue(105);

	//A list of properties
	std::map<std::string, IGPropertyValue*> properties;
	properties["Edad"] = &pprop;
    auto edad = properties["Edad"]->getPropertyValue<int>();

    cout << "Test program for GMaterialComponent" << std::dec << std::endl;
	cout << "Edad: " << edad << "\n";
	return 0;
}
