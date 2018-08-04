#include <iostream>

int main(){

    int a,b;
    std::cin>>a>>b;
    std::cout<<((a%2==0 || b%2==1)?"yes":"no")<<std::endl;
}