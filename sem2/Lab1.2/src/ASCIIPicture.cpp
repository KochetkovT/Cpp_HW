#include "ASCIIPicture.hpp"

#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::endl;

ASCIIPicture::ASCIIPicture(string fname)
{
    ifstream file(fname);
    if (!file.is_open())
    {
        cout << "Picture " << fname << " is nowhere to be found." << endl;
        exit(0);
    }
    char buffer[200];
    while (file.getline(buffer, 200, '\n'))
    {
        string tmp(buffer);
        if (tmp.size() > 190)
        {
            cout << "Picture " << fname << " is too big." << endl;
            file.close();
            exit(0);
        }
        if (tmp[0] == '#') continue;
        picture.push_back(tmp);
    }
}

int ASCIIPicture::getWidth()
{
    if (picture.size() == 0)
        return 0;
    unsigned int max = 0;
    for (auto s : picture)
        max = max > s.size() ? max : s.size();
    return max;
}

int ASCIIPicture::getHeight()
{
    return picture.size();
}
