#include <string>

namespace GTech{

    class Resourcer {
    public:

        virtual unsigned int Load(const std::string& resourceName)=0;
        virtual void UnLoad(const std::string& resourceName)=0;
    
    };

}

