#include <iostream>
#include "../Headers/KCsts.h"


int main() {
map<int,pair<string,string>> names;
    names[1]={"Youssef","Zaki"};
    cout<<names.find(1)->second.first;

}