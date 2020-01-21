#include "Main.h"

/*
* All Class will by replaced with the templates must implement string toString() const();
* and at least one of the  constructors:
 *
* class(string)
* class (list<string>)
*
* => we handle with the problems as strings(get from the client) and
* send back the solution as string.
*/

int main(int argc,char* argv[]) {

    server_side::boot::Main m;
    m.main(argc,argv);

    return 0;
}