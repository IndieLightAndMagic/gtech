
#include <map>
#include <string>
#include <iostream> 

#include <MESHCOMPONENT/GMaterialComponent.h>
using namespace std;

typedef struct Color{
    float r,g,b;
}Color;

int main(void)
{
    Color c{1.0f,0.3f, 0.75f};
    
	//An integer property of size 10.
	GPropertyValue<int> pprop;
	pprop.setPropertyValue(105);

	GPropertyValue<float> pfprop;
	pfprop.setPropertyValue(3.5f+11.2f);

    GPropertyValue<Color> colorprop;
    colorprop.setPropertyValue(c);
    
	//A list of properties
	std::map<std::string, IGPropertyValue*> properties;
	properties["Edad"] = &pprop;
	properties["Estatura"] = &pfprop;
    properties["Cabello"] = &colorprop;
    
    auto edad = properties["Edad"]->getPropertyValue<int>();
    auto estatura = properties["Estatura"]->getPropertyValue<float>();
    auto cabello = properties["Cabello"]->getPropertyValue<Color>();
    
    cout << "Test program for GMaterialComponent\n";
	cout << "Edad: " << edad << "\n";
	cout << "Estatura: " << estatura << "\n";
    cout << "Color Cabello: " << cabello.r << "," << cabello.g << "," << cabello.b << "\n";
    
    return 0;
}
