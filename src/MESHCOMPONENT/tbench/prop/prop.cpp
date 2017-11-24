

#include <MESHCOMPONENT/GMaterialComponent.h>

using namespace std;

class GPropertyValueInt : public GPropertyValue
{
public:
	GPropertyValueInt(std::size_t sz = sizeof(int), int * iptr = nullptr):
	GPropertyValue(sz,reinterpret_cast<Ptr>(iptr))
	{
		std::cout << "Derived::\n";
	}
	~GPropertyValueInt(){std::cout << "Derived::\n";};

	void setPropertyValue(const int *propertyValueAddress)
	{
		Ptr ptr = reinterpret_cast<Ptr>(propertyValueAddress);
		GPropertyValue::setPropertyValue(ptr,sizeof(int));
	}
	void setPropertyValue(const int &propertyValue)
	{
		setPropertyValue(&propertyValue);
	}
	int getPropertyValue()
	{
		int *iptr = reinterpret_cast<int*>(getPtr());
		return iptr[0];
	}
};
int main(void)
{
	//A 10 Bytes in Size Property.
	std::unique_ptr<GPropertyValue> pprop = std::make_unique<GPropertyValueInt>();

	cout << "Test program for GMaterialComponent\n";
	return 0;
}