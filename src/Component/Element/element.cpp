#include "element.h"

Element::Element() {}

Element::Element(std::string label, unsigned int tag) :
    EmptyObject (label, tag) {}

Element::~Element() {}
