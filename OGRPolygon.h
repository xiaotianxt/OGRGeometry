//
// Created by 小田小田 on 2020/6/8.
// 

#ifndef OGR_GEOMETRY_OGRPOLYGON_H
#define OGR_GEOMETRY_OGRPOLYGON_H
#include <utility>

#include "OGRCurvePolygon.h"

class OGRPolygon : public OGRCurvePolygon{
protected:

public:
    OGRPolygon() = default;
    OGRPolygon(std::vector<OGRLinearRing> list) { this->list = std::move(list); }

    const char * GetGeometryType() { return "OGRPolygon"; }
    
    void ImportFromWkt(const char * filepath);
    std::string print();
    void ExportToWkt(const char * filepath);

    double GetArea();
    double GetPerimeter();

    bool Contains(OGRPoint & object);
    bool Contains(OGRLineString & object);
    bool Contains(OGRPolygon & object);

    bool Intersects(OGRLineString &object);
    bool Intersects(OGRPolygon &object);

};


#endif //OGR_GEOMETRY_OGRPOLYGON_H
