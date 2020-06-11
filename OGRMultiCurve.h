//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRGeometryCollection.h"
#ifndef OGR_GEOMETRY_OGRMULTICURVE_H
#define OGR_GEOMETRY_OGRMULTICURVE_H


class OGRMultiCurve : public OGRGeometryCollection {
public:
    const char * GetGeometryType() override { return "OGRMultiCurve"; }
};

#endif //OGR_GEOMETRY_OGRMULTICURVE_H
