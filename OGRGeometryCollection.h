//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRGeometry.h"
#include "OGRPoint.h"
#include "OGRPolygon.h"
#include "OGRLineString.h"
#ifndef OGR_GEOMETRY_OGRGEOMETRYCOLLECTION_H
#define OGR_GEOMETRY_OGRGEOMETRYCOLLECTION_H


class OGRGeometryCollection : public OGRGeometry{
protected:
    std::vector<OGRGeometry *> list;
    double XMin, YMin, XMax, YMax; //
    std::vector<OGRGeometry *> GetList() { return list; }

public:
    OGRGeometryCollection() = default;
    OGRGeometryCollection(std::vector<OGRGeometry*> list){
        this->list = list;
    }
    ~OGRGeometryCollection() = default;
    const char * GetGeometryType() override { return "OGRGeometryCollection"; }

    virtual void AddGeometry(OGRGeometry &object);
    virtual void RemoveGeometry(int index);
    virtual OGRGeometry* GetGeometry(int index);
    virtual void UpdateGeometry(int index, OGRGeometry &object);
    virtual int GetNumGeometries();
    
    bool Equals(const OGRGeometry & Sample);
    
    void Clone(OGRGeometryCollection & Sample);
    OGRGeometryCollection& Clone() override;
    
    bool IsEmpty() override;

};


#endif //OGR_GEOMETRY_OGRGEOMETRYCOLLECTION_H
