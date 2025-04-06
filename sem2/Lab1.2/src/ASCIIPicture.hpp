#ifndef ASCIIPICTURE_H
#define ASCIIPICTURE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class ASCIIPicture {

protected:

    vector<string> picture;

public:

    ASCIIPicture(string fname);
    int getWidth();
    int getHeight();
    virtual void print(unsigned int left, char fill, unsigned int width) = 0;

};

#endif
