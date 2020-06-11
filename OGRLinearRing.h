//
// Created by 小田小田 on 2020/6/8.
//
#include <utility>

#ifndef OGR_GEOMETRY_OGRLINEARRING_H
#define OGR_GEOMETRY_OGRLINEARRING_H
#include "OGRLineString.h"

class OGRLinearRing : public OGRLineString{
private:
    bool OnSegment(OGRPoint P1, OGRPoint P2, OGRPoint Q);
// 注意ring和linestring的区别是list第一个元素和最后一个元素相连相同
public:
    const char * GetGeometryType() override { return "OGRLinearRing"; }
    OGRLinearRing() = default;
    OGRLinearRing(std::vector<OGRPoint> newlist){list = std::move(newlist); }
    
    double GetArea();
    double GetLength() override;
    
    bool Contains(const OGRPoint &object);
    bool On(const OGRPoint &object); // 用于判断点是否在Ring边上
    
    bool Intersects(OGRLinearRing &object);
    bool Intersects(OGRLineString &object) override;

    void Clone(OGRLinearRing &Sample);
    OGRLinearRing& Clone();

};


#endif //OGR_GEOMETRY_OGRLINEARRING_H
