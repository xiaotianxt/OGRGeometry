//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRGeometry.h"
#include "OGRPoint.h"
#ifndef OGR_GEOMETRY_OGRSURFACE_H
#define OGR_GEOMETRY_OGRSURFACE_H


class OGRSurface : public OGRGeometry{
public:
    const char * GetGeometryType() override { return "OGRSurface";}
};


#endif //OGR_GEOMETRY_OGRSURFACE_H