//
// Created by 小田小田 on 2020/6/8.
//
#ifndef OGR_GEOMETRY_OGRLINESTRING_H
#define OGR_GEOMETRY_OGRLINESTRING_H

#include <utility>

#include "OGRSimpleCurve.h"


class OGRLineString : public OGRSimpleCurve{
public:
    OGRLineString() = default;
    OGRLineString(std::vector<OGRPoint>list) { this->list = std::move(list);}

    const char * GetGeometryType() override { return "OGRLineString"; }

    double GetLength() override;

    virtual bool Intersects(OGRLineString &b);

    void Clone(OGRLineString &Sample);

    OGRLineString& Clone();
};

#endif //OGR_GEOMETRY_OGRLINESTRING_H
