#ifndef CLOUD_H
#define CLOUD_H

#include "ASCIIPicture.hpp"

class Cloud : public ASCIIPicture {

    string message;

public:

    Cloud(string message, string fname);
    ~Cloud();

    void print(unsigned int left, char fill, unsigned int width);

};

#endif
