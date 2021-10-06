//
// Created by Jacques Perrault on 10/6/21.
//
#include <iostream>
#include <clickup/clickup.h>

using namespace std;

int main() {
  clickup client = clickup();
  client.getToken();
  auto o = client.GetFolderlessList("54005663");
  cout << o << endl;
}