//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRLineString.h"

double OGRLineString::GetLength() {
    double length = 0.0;
    if (list.empty()) return length;
    for (int i = 0; i < list.size() - 1; i++){
        length += sqrt((list[i].getX() - list[i+1].getX()) * (list[i].getX() - list[i+1].getX()) + (list[i].getY() - list[i+1].getY()) * (list[i].getY() - list[i+1].getY()));
    }
    return length;
}

bool OGRLineString::Intersects(OGRLineString &b) {
    double x1, x2, y1, y2;
    double bx1, bx2, by1, by2;
    GetMBR(x1, y2, x2, y2);
    b.GetMBR(bx1, by1, bx2, by2);

    if ( ((x1 - bx1) * (x2 - bx2) > 0) && ((y1 - by1) * (y2 - by2) > 0) )
        // 此时外包多边形不相交
        return false;
    else{
        for (int i = 0; i < list.size() - 1; i++){
            for (int j = 0; j < b.list.size() - 1; j++){ // 两两线段查看是否相交
                OGRPoint P = list[i] - list[i+1];
                OGRPoint P1 = b.list[j] - list[i+1];
                OGRPoint P2 = b.list[j+1] - list[i+1];

                OGRPoint Q = b.list[j] - b.list[j+1];
                OGRPoint Q1 = list[i] - b.list[j+1];
                OGRPoint Q2 = list[i+1] - b.list[j+1];

                if (COMPARE((P^P1) * (P^P2), 0) == 1 && COMPARE((Q^Q1) * (Q^Q2), 0) == 1){
                    return true;
                }
            }
        }
    }
    return false;
}

void OGRLineString::Clone(OGRLineString &Sample) {
    list = Sample.list;
}

OGRLineString &OGRLineString::Clone() {
    OGRLineString *newl = new OGRLineString(list);
    return *newl;
}