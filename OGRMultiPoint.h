//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRGeometryCollection.h"
#include "OGRPoint.h"

#ifndef OGR_GEOMETRY_OGRMULTIPOINT_H
#define OGR_GEOMETRY_OGRMULTIPOINT_H


class OGRMultiPoint : public OGRGeometryCollection{
protected:

public:
    OGRMultiPoint() = default;

    const char * GetGeometryType() override { return "OGRMultiPoint"; }
    
    std::pair<OGRPoint, OGRPoint> GetMBR();
    void GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) override;

    void ImportFromWkt(const char * filepath) override;
    void ExportToWkt(const char * filepath) override;
};


#endif //OGR_GEOMETRY_OGRMULTIPOINT_H
