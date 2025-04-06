#include "Cloud.hpp"

#include <iostream>
using std::cout;
using std::endl;

Cloud::Cloud(string message, string fname) : ASCIIPicture("./clouds/" + fname + ".cloud"), message(message)
{
}

Cloud::~Cloud() {}

void Cloud::print(unsigned int left, char fill, unsigned int width)
{
    for (unsigned int i = 0; i < width; i++)
        cout << fill;
    cout << endl;

    unsigned int messageLength = width / 3;

    for (unsigned int i = 0; i < 2; i++)
    {
        for (unsigned int j = 0; j < left; j++)
            cout << fill;
        for (unsigned int j = 0; j < 4; j++)
            cout << picture[i][j];
        for (unsigned int j = 0; j < messageLength ; j++)
            cout << picture[i][4];
        for (unsigned int j = 0; j < 4; j++)
            cout << picture[i][j + 5];
        for (unsigned int j = left + 8 + messageLength; j < width; j++)
            cout << fill;
        cout << endl;
    }
    
    for (unsigned int i = 0; i < message.size()/messageLength + 1; i++)
    {
        for (unsigned int j = 0; j < left; j++)
            cout << fill;
        for (unsigned int j = 0; j < 4; j++)
            cout << picture[2][j];
        unsigned int length = i < message.size()/messageLength ? messageLength : message.size() - i*messageLength;
        for (unsigned int j = 0; j < length ; j++)    
            cout << message[i*messageLength + j];
        for (unsigned int j = length; j < messageLength; j++)
            cout << ' ';
        for (unsigned int j = 0; j < 4; j++)
            cout << picture[2][j + 5];
        for (unsigned int j = left + 8 + messageLength; j < width; j++)
            cout << fill;
        cout << endl;
    }

    for (unsigned int i = 3; i < picture.size(); i++)
    {
        for (unsigned int j = 0; j < left; j++)
            cout << fill;
        for (unsigned int j = 0; j < 4; j++)
            cout << picture[i][j];
        for (unsigned int j = 0; j < messageLength ; j++)
            cout << picture[i][4];
        for (unsigned int j = 0; j < 4; j++)
            cout << picture[i][j + 5];
        for (unsigned int j = left + 8 + messageLength; j < width; j++)
            cout << fill;
        cout << endl;
    }
}
