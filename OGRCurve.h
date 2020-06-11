//
// Created by 小田小田 on 2020/6/8.
//
#include <utility>

#include "OGRGeometry.h"
#include "OGRPoint.h"
#ifndef OGR_GEOMETRY_OGRCURVE_H
#define OGR_GEOMETRY_OGRCURVE_H


class OGRCurve : public OGRGeometry{
protected:
    std::vector<OGRPoint> list;
public:
    
    OGRCurve() = default;
    OGRCurve(std::vector<OGRPoint> newlist) : list(std::move(newlist)){ }
    OGRCurve(double x1, double x2, double y1, double y2);
    
    const char * GetGeometryType() override { return "OGRCurve"; }
    
    bool IsEmpty() override;

    void GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) override;
    virtual std::pair<OGRPoint, OGRPoint> GetMBR();

    void Clone(OGRCurve & Sample);
    OGRCurve &Clone();

    bool Equals(const OGRGeometry& object);
    
    std::string print();
    const std::vector<OGRPoint>& GetList();
};


#endif //OGR_GEOMETRY_OGRCURVE_H
