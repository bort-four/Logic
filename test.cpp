// test.cpp

#include <iostream>
#include "atlpp.hpp"

using namespace std;
using namespace ATL;


int main(void)
{
	cout << "Helllo from test!\n";
	
	ATL_Model model;
	NamedConstant con(&model, "const1", "type1");
	
	cout << con.toString() << "\n";
	
	return 0;
}
