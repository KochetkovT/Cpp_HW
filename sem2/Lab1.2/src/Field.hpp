#ifndef FIELD_H
#define FIELD_H

#include <string>
using std::string;

#include "Cow.hpp"
#include "Cloud.hpp"
class Parser;

class Field {

    string message;
    Cow cow;
    Cloud cloud;
    string tongue;
    char fill;
    char sun; 

public:

    Field(Parser& parser);
    ~Field();

    void print();

};

#endif
