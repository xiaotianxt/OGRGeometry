//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRMultiCurve.h"
#ifndef OGR_GEOMETRY_OGRMULTILINESTRING_H
#define OGR_GEOMETRY_OGRMULTILINESTRING_H


class OGRMultiLineString : public OGRMultiCurve{
public:
    const char * GetGeometryType() override { return "OGRMultiLineString";}
    double GetLength();
};


#endif //OGR_GEOMETRY_OGRMULTILINESTRING_H
