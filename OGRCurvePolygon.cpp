//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRCurvePolygon.h"

void OGRCurvePolygon::GetMBR(double &XMin, double &YMin, double &XMax, double &YMax) {
    double x1, y1, x2, y2;
    if (list.size() != 0) {
        list[0].GetMBR(x1, y1, x2, y2);
        XMin = x1, YMin = y1, XMax = x2, YMax = y2;
        for (int i = 1; i < list.size(); i++){
            list[i].GetMBR(x1, y1, x2, y2);
            if (x1 < XMin)
                XMin = x1;
            if (y1 < YMin)
                YMin = y1;
            if (x2 > XMax)
                XMax = x2;
            if (y2 > YMax)
                YMax = y2;
        }
    }
}

OGRCurvePolygon &OGRCurvePolygon::Clone() {
    std::vector<OGRLinearRing> newlist(list);
    auto *newCurPolygon =  new OGRCurvePolygon(newlist);
    return *newCurPolygon;
}

void OGRCurvePolygon::Clone(OGRCurvePolygon &Sample){
    list = Sample.list;
    return;
}

bool OGRCurvePolygon::Equals(const OGRGeometry &object) {
    auto *p = dynamic_cast<const OGRCurvePolygon *>(&object);

    std::vector<bool> map(list.size(), 0);
    if ((*p).list.size() == list.size()){
        for (int i = 0; i < list.size(); i++){

            for (int j = 0; j < (*p).list.size(); j++){
                if (list[i].Equals((*p).list[j]) && map[i] == 0){
                    map[i] = 1;
                    goto a;
                }
            }
            return false;
            a:
            NULL;
        }
    }
    else{
        return false;
    }
}

const std::vector<OGRLinearRing> &OGRCurvePolygon::GetList() {
    return list;
}

std::pair<OGRPoint, OGRPoint> OGRCurvePolygon::GetMBR() {
    double x1, y1, x2, y2;
    GetMBR(x1, y1, x2, y2);
    return std::pair<OGRPoint, OGRPoint>(OGRPoint(x1, y1), OGRPoint(x2, y2));
}
