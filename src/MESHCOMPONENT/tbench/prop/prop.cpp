

#include <MESHCOMPONENT/GMaterialComponent.h>

class GPropertyFloat : public GProperty<float>
{
public:
	GPropertyFloat():GProperty<float>(){};
	float getProperty() { return 180.0f; }
};

using namespace std;
int main(void)
{
	GProperty<float> * p = new GPropertyFloat;
	p->setProperty(32.0f);
	cout << "Test program for GMaterialComponent\n";
	cout << "p: " << p->getProperty() << "\n";
	return 0;
}