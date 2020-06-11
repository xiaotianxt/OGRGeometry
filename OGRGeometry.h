//
// Created by 小田小田 on 2020/6/8.
//
#include "util_variable.h"

#ifndef OGR_GEOMETRY_OGRGEOMETRY_H
#define OGR_GEOMETRY_OGRGEOMETRY_H

// Abstract class for all OGR class
class OGRGeometry {
protected:
    int id; // 要素id
public:
    OGRGeometry(){
        id = GET_ID(); // 获得自己的ID
    }
    virtual ~OGRGeometry() = default;
    virtual const char * GetGeometryType()  { return "OGRGeometry"; }
    virtual bool IsEmpty();
    virtual void GetMBR(double &XMin, double &YMin, double &XMax, double &YMax);

    virtual void Clone(OGRGeometry & Sample) ;
    virtual OGRGeometry& Clone();
    
    virtual bool Equals(const OGRGeometry& object);
    
    int GetID() const { return id; }
    
    virtual void ImportFromWkt(const char * filepath);
    virtual void ExportToWkt(const char * filepath);
    
    virtual double GetLength() { std::cerr<< "Not using correctly !" << std::endl; return 0.0;}

    bool operator==(const OGRGeometry &b) const { return id == b.id; }
};


#endif //OGR_GEOMETRY_OGRGEOMETRY_H
