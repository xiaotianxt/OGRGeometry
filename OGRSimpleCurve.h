//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRCurve.h"
#ifndef OGR_GEOMETRY_OGRSIMPLECURVE_H
#define OGR_GEOMETRY_OGRSIMPLECURVE_H


class OGRSimpleCurve : public OGRCurve{
public:
    const char * GetGeometryType() override { return "OGRSimpleCurve"; }
};


#endif //OGR_GEOMETRY_OGRSIMPLECURVE_H
