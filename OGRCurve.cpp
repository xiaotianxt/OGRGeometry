//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRCurve.h"

bool OGRCurve::IsEmpty() {
    return list.empty();
}

void OGRCurve::GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) {
    XMin = list[0].getX();
    XMax = list[0].getX();
    YMin = list[0].getY();
    YMax = list[0].getY();
    for (auto i : list){
        if (i.getX() < XMin)
            XMin = i.getX();
        if (i.getX() > XMax)
            XMax = i.getX();
        if (i.getY() < YMin)
            YMin = i.getY();
        if (i.getY() > YMax)
            YMax = i.getY();
    }
}

std::pair<OGRPoint, OGRPoint> OGRCurve::GetMBR() {
    double x1, y1, x2, y2;
    GetMBR(x1, y1, x2, y2);
    return std::pair<OGRPoint, OGRPoint>(OGRPoint(x1, y1), OGRPoint(x2, y2));
}

void OGRCurve::Clone(OGRCurve & Sample) {
    list = Sample.list;
}

bool OGRCurve::Equals(const OGRGeometry &object) {
    const OGRCurve *p = dynamic_cast<const OGRCurve*>(&object);

    if (this->list.size() != (*p).list.size())
        return false;
    else{
        for( int i = 0; i < list.size(); i++){
            if (!list[i].Equals((*p).list[i])){
                return false;
            }
        }
    }
    return true;
}

OGRCurve::OGRCurve(double x1, double x2, double y1, double y2) {
    list.push_back(OGRPoint(x1, y1));
    list.push_back(OGRPoint(x2, y2));
}

std::string OGRCurve::print() {
    std::string result = "(";
    result += std::to_string(list[0].getX()) + " " + std::to_string(list[0].getY());
    for (int i = 1; i < list.size(); i++)
    {
        result += ", " + std::to_string(list[i].getX()) + " " + std::to_string(list[i].getY());
    }
    result += ")";
    return result;
}

const std::vector<OGRPoint> &OGRCurve::GetList() {
    return list;
}

OGRCurve &OGRCurve::Clone() {
    auto *newCurve = new OGRCurve(list);
    return *newCurve;
}