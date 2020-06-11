//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRMultiSurface.h"
#ifndef OGR_GEOMETRY_OGRMULTIPOLYGON_H
#define OGR_GEOMETRY_OGRMULTIPOLYGON_H


class OGRMultiPolygon : public OGRMultiSurface{
protected:
    std::vector<OGRPolygon> list;
public:
    const char * GetGeometryType() override { return "OGRMultiPolygon"; }
    
    void ImportFromWkt(const char * filepath);
    void ExportToWkt(const char * filepath);
    
    double GetArea();
    double GetPerimeter();

    bool Contains(OGRPoint &object);
    bool Contains(OGRLineString &object);
    bool Contains(OGRPolygon &object);

};


#endif //OGR_GEOMETRY_OGRMULTIPOLYGON_H
