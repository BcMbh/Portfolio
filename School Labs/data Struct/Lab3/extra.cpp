#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

stack<int>A;
int a=4,b=3, B[5];

/*
i.
[4] 
[3]
[2]
[1]
[0]12

ii.
[4] 
[3]
[2]
[1]
[0]

out[ut:12]

iii.
[4] 
[3]
[2]
[1]
[0]7

iv.
[4] 
[3]
[2]
[1]7
[0]-1


v.
[4] 
[3]
[2]
[1]
[0]7

a=-0.5

vi.
[4] 
[3]
[2]
[1]7
[0]10

a=-0.5

vii.
[4] 
[3]
[2]
[1]7
[0]3

a=-0.5
*/