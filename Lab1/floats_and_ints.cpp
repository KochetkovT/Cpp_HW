#include <iostream>
#include <bitset>
#include <climits>
#include <cmath>

using namespace std;

void printFloat(bitset<32> f) {
    cout << f[31] << " ";
    for (int i = 30; i > 22; --i) {
        cout << f[i];
    }
    cout << " ";
    for (int i = 22; i != -1 ; --i) {
        cout << f[i];
    }
    cout << "\n";
}

int main(){
    //  часть с int и uint

    int num1 = 123, num2 = -123;
    unsigned int unum1 = 123;
    
    cout << num1 << " = \t" << bitset<sizeof(num1) * CHAR_BIT>(num1) << endl;
    cout << num2 << " = \t" << bitset<sizeof(num2) * CHAR_BIT>(num2) << endl;
    cout << unum1 << " = \t" << bitset<sizeof(unum1) * CHAR_BIT>(unum1) << endl;
    cout << "\n";

    num1 = INT_MAX;
    num2 = INT_MIN;
    unum1 = UINT_MAX;
    
    cout << num1 << " = \t" << bitset<sizeof(num1) * CHAR_BIT>(num1) << endl;
    cout << num2 << " = \t" << bitset<sizeof(num2) * CHAR_BIT>(num2) << endl;
    cout << unum1 << " = \t" << bitset<sizeof(unum1) * CHAR_BIT>(unum1) << endl;
    cout << "\n";

    unum1 = 0;
    unum1 -= 1;
    
    cout << unum1 << " = \t" << bitset<sizeof(unum1) * CHAR_BIT>(unum1) << endl;
    cout << "\n";

    unum1 = UINT_MAX;
    unum1 += 1;
    
    cout << unum1 << " = \t" << bitset<sizeof(unum1) * CHAR_BIT>(unum1) << endl;
    cout << "\n";

    num1 = num1 + 1;
    num2 = num2 - 1;
    
    cout << num1 << " = \t" << bitset<sizeof(num1) * CHAR_BIT>(num1) << endl;
    cout << num2 << " = \t" << bitset<sizeof(num2) * CHAR_BIT>(num2) << endl;
    cout << "\n";

//  часть с float

//111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
    float f = 1.f;



    union
    {
        float input;
        int output;
    } data;

    data.input = f;

    bitset<sizeof(float) * CHAR_BIT> bits(data.output);
    printFloat(bits);
    cout << "\n";

//22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222
    float k = 0;
    while((k+1) != k){
        ++k;
    }

    cout.precision(8);
    cout << powf(2,24) << "\n";
    cout << k << "\n";
    cout << "\n";

//3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
    float a = powf(2,24), b = 1, c = 1;
    cout << a + (b + c) << "\n";
    cout << (a + b) + c << "\n";
    cout << "\n";

//454545454545454545454545454545454545544545544554455454545454545454545454545454545454545544545544554455

    float sum = 0;
    unsigned int i = 1;

    while((sum + 1/float(i)) != sum){
        sum += 1/float(i);
        ++i;
    }

    cout << sum << " " << i << " " << 1/float (i) << "\n";

    sum = 0;

    for (unsigned int j = 10*i; j != 0; --j){
        sum += 1/float(j);
    }

    cout << sum  << "\n";
    cout << "\n";

//finalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinalfinal
    float final = 0.3f;
    if(final == 0.3f){
        cout << "Yep";
    }
    return 0;
}
