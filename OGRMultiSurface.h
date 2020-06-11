//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRGeometryCollection.h"
#ifndef OGR_GEOMETRY_OGRMULTISURFACE_H
#define OGR_GEOMETRY_OGRMULTISURFACE_H


class OGRMultiSurface : public OGRGeometryCollection{
public:
    const char* GetGeometryType() override { return "OGRMultiSurface"; }
};


#endif //OGR_GEOMETRY_OGRMULTISURFACE_H
