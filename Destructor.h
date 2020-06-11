//
// Created by 小田小田 on 2020/6/9.
//
#include "util_variable.h"
#include "OGRGeometry.h"
#ifndef OGR_GEOMETRY_DESTRUCTOR_H
#define OGR_GEOMETRY_DESTRUCTOR_H


class Destructor {
public:
    std::vector<OGRGeometry*> data;
    ~Destructor() { for (auto i : data) delete i;}
};


#endif //OGR_GEOMETRY_DESTRUCTOR_H
