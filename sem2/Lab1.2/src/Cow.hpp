#ifndef COW_H
#define COW_H

#include "ASCIIPicture.hpp"

class Cow : public ASCIIPicture {

    string tongue;

public:

    Cow(string tongue, string fname);
    ~Cow();

    void print(unsigned int left, char fill, unsigned int width);

};

#endif
