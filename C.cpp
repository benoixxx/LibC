////////////////////////////////////////////////////////////////////////////////
//   File      : C.cpp
//   Contents  :
//
// Author(s) : FGR
// $LastChangedBy$
// $LastChangedDate$
// $Revision$
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licenses/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

#include <libB/B.h>

void C()
{
	cout << "Hello from C & calling B()" << endl;
	B();
}