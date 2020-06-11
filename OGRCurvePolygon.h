//
// Created by 小田小田 on 2020/6/8.
//
#include <utility>

#include "OGRSurface.h"
#include "OGRLinearRing.h"
#ifndef OGR_GEOMETRY_OGRCURVEPOLYGON_H
#define OGR_GEOMETRY_OGRCURVEPOLYGON_H


class OGRCurvePolygon : public OGRSurface{
protected:
    std::vector<OGRLinearRing> list;
public:
    OGRCurvePolygon() = default;
    explicit OGRCurvePolygon(std::vector<OGRLinearRing> list) { this->list = std::move(list); }
    
    const char* GetGeometryType() override { return "OGRCurvePolygon"; }
    
    bool IsEmpty() override { return list.empty(); }
    
    void GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) override;
    virtual std::pair<OGRPoint, OGRPoint> GetMBR();
    
    OGRCurvePolygon &Clone() override;
    void Clone(OGRCurvePolygon &Sample);
    
    bool Equals( const OGRGeometry& object ) ;
    
    const std::vector<OGRLinearRing> &GetList();
};


#endif //OGR_GEOMETRY_OGRCURVEPOLYGON_H
