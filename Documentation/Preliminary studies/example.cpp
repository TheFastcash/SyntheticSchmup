#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace FooNS
{
    class Foo
    {
        private :
            int _number;

        public :
            Foo(int number = 1);
            int getNumber();
    };

    Foo::Foo(int number)
    {
        this->_number = number;
    }

    int Foo::getNumber()
    {
        /// Last update :      2016/07/03
        /// Last time tested : 2016/07/03
        /// Return the value of "_number"
        return this->_number;
    }
}

int main(int argc, char **argv)
{
    /// Last update :      2016/07/03
    /// Last time tested : 2016/07/03
    /// Show an example of code

    std::srand(std::time(0));
    for(int i = 0; i < 20; i++)
    {
        // Create a Foo with a random number
//        float random_variable = (float(std::rand()))*5.0f/float(RAND_MAX);
        float random_variable = ((float)(std::rand()))*20.0f/((float)(RAND_MAX));
//        std::cout << random_variable << std::endl;
        FooNS::Foo *foo = new FooNS::Foo(round(random_variable));

        // Depending on the Foo number, say something
        std::cout << std::setw(3) << foo->getNumber() << " : ";
        switch(foo->getNumber())
        {
            case 0 :
            {
                std::cout << "Can't be worst";
                break;
            }
            case 11 :
            {
                std::cout << "The twins !!";
                break;
            }
            case 20 :
            {
                std::cout << "Can't be better";
                break;
            }
            default :
            {
                std::cout << "Ok";
                break;
            }
        }
        std:: cout << std::endl;
        delete foo;
    }
    return 0;
}

