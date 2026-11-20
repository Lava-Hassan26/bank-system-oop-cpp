#include <iostream>
#include "clsBankClient.h"
using namespace std;

int main()
{
    clsBankClient client = clsBankClient::Find("A100");
    client.Print();

    clsBankClient client2 = clsBankClient::Find("A101", "1234");
    client2.Print();

    return 0;
}