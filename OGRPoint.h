//
// Created by 小田小田 on 2020/6/8.
//
#include "OGRGeometry.h"
#ifndef OGR_GEOMETRY_OGRPOINT_H
#define OGR_GEOMETRY_OGRPOINT_H


class OGRPoint : public OGRGeometry{
protected:
    double x;
    double y;
public:
    OGRPoint() {
        x = (std::numeric_limits<double>::max)();
        y = (std::numeric_limits<double>::max)(); // 此时为空类
    }
    OGRPoint(double x_, double y_) { x = x_; y = y_; }

    const char * GetGeometryType() override {
        return "OGRPoint";
    }

    bool IsEmpty() override;
    void GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) override; // 将多边形边界赋值给四个参数
    std::pair<OGRPoint, OGRPoint> GetMBR(); // 用std::pair实现返回外包矩形
    void Clone(OGRPoint & Sample); // 以Sample所谓样例
    OGRPoint &Clone() override;

    bool Equals(const OGRGeometry& object) override;
    void ImportFromWkt(const char * filepath) override;
    void ExportToWkt(const char * filepath) override;

    double getX() const;
    double getY() const;

    std::string print() const; // 用于构造点的输出格式

    OGRPoint operator-(const OGRPoint &objectb) const;
    double operator*(const OGRPoint &objectb) const; // 点乘
    double operator^(const OGRPoint &objectb) const; // 叉乘
    bool operator==(const OGRPoint &objectb) const; // 判断两个点相等
};


#endif //OGR_GEOMETRY_OGRPOINT_H
