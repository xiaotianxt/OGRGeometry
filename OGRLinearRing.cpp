//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRLinearRing.h"

double OGRLinearRing::GetArea() {
    double area = 0;
    for(int i = 0, k = list.size() - 1; i < list.size(); k=i++){
        area += list[k].getX() * list[i].getY();
        area -= list[k].getY() * list[i].getX();
    }
    return area / 2;
}

double OGRLinearRing::GetLength() {
    double length = 0.0;
    if (list.empty()) return length;
    for (int i = 0; i < list.size() - 1; i++){
        length += sqrt((list[i].getX() - list[i+1].getX()) * (list[i].getX() - list[i+1].getX()) + (list[i].getY() - list[i+1].getY()) * (list[i].getY() - list[i+1].getY()));
    }
    length += sqrt((list.back().getX() - list[0].getX()) * (list.back().getX() - list[0].getX()) + (list.back().getY() - list[0].getY()) * (list.back().getY() - list[0].getY()));
    return length;
}

//判断点Q是否在P1和P2的线段上
bool OGRLinearRing::OnSegment(OGRPoint P1,OGRPoint P2,OGRPoint Q)
{
    //前一个判断点Q在P1P2直线上 后一个判断在P1P2范围上
    return COMPARE((P1-Q)^(P2-Q), 0)==0 && COMPARE((P1-Q)*(P2-Q), 0)<=0;
}

bool OGRLinearRing::Contains(const OGRPoint &object) {
    bool flag = false; //相当于计数
    OGRPoint P1,P2; //多边形一条边的两个顶点
    double x1, y1, x2, y2;
    GetMBR(x1, y1, x2, y2);
    for(int i = 0,j = list.size()-1 ;i < list.size(); j=i++) // 遍历每一个点
    {
        //polygon[]是给出多边形的顶点
        P1 = list[i];
        P2 = list[j];
        if(OnSegment(P1,P2,object)) return false; //点在多边形一条边上
        //前一个判断min(P1.y,P2.y)<P.y<=max(P1.y,P2.y)
        //后一个判断被测点 在 射线与边交点 的左边
        if( (COMPARE(0, P1.getY()-object.getY())>0 != COMPARE(0, P2.getY()-object.getY())>0) && COMPARE(object.getX() - (object.getY()-P1.getY())*(P1.getX()-P2.getX())/(P1.getY()-P2.getY())-P1.getX(), 0) < 0)
            flag = !flag;
    }
    return flag;
}

bool OGRLinearRing::Intersects(OGRLineString &object) {
    double x1, x2, y1, y2;
    double bx1, bx2, by1, by2;
    GetMBR(x1, y2, x2, y2);
    object.GetMBR(bx1, by1, bx2, by2);

    std::vector<OGRPoint> plist = object.GetList();

    for (int i = 0, k = list.size() - 1; i < list.size(); k=i++){
        for (int j = 0; j < plist.size() - 1; j++){ // 两两线段查看是否相交
            OGRPoint P(plist[j+1].getX() - plist[j].getX(), plist[j+1].getY() - plist[j].getY());
            OGRPoint P1(list[i].getX() - plist[j].getX(), list[i].getY() - plist[j].getY());
            OGRPoint P2(list[k].getX() - plist[j].getX(), list[k].getY() - plist[j].getY());

            OGRPoint Q(list[k].getX() - list[i].getX(), list[k].getY() - list[i].getY());
            OGRPoint Q1(plist[j+1].getX() - list[i].getX(), plist[j+1].getY() - list[i].getY());
            OGRPoint Q2(plist[j].getX() - list[i].getX(), plist[j].getY() - list[i].getY());

            if (COMPARE((P^P1) * (P^P2), 0) == 1 & COMPARE((Q^Q1)*(Q^Q2), 0) == 1)
                return true;
        }
    }
    return false;
}

bool OGRLinearRing::Intersects(OGRLinearRing &object) {
    double x1, x2, y1, y2;
    double bx1, bx2, by1, by2;
    GetMBR(x1, y2, x2, y2);
    object.GetMBR(bx1, by1, bx2, by2);

    std::vector<OGRPoint> plist = object.GetList();

    for (int i = 0, k = list.size() - 1; i < list.size(); k=i++){
        for (int j = 0, l = plist.size() - 1; j < plist.size(); l=j++){ // 两两线段查看是否相交
            OGRPoint P(plist[j].getX() - plist[l].getX(), plist[j].getY() - plist[l].getY());
            OGRPoint P1(list[i].getX() - plist[l].getX(), list[i].getY() - plist[l].getY());
            OGRPoint P2(list[k].getX() - plist[l].getX(), list[k].getY() - plist[l].getY());

            OGRPoint Q(list[k].getX() - list[i].getX(), list[k].getY() - list[i].getY());
            OGRPoint Q1(plist[j].getX() - list[i].getX(), plist[j+1].getY() - list[i].getY());
            OGRPoint Q2(plist[l].getX() - list[i].getX(), plist[l].getY() - list[i].getY());

            if (COMPARE((P^P1) * (P^P2), 0) == 1 & COMPARE((Q^Q1)*(Q^Q2), 0) == 1)
                return true;
        }
    }
    return false;
}

void OGRLinearRing::Clone(OGRLinearRing &Sample) {
    list = Sample.list;
}

OGRLinearRing &OGRLinearRing::Clone() {
    auto *newring = new OGRLinearRing(list);
    return *newring;
}

bool OGRLinearRing::On(const OGRPoint &object) {
    OGRPoint P1,P2; //多边形一条边的两个顶点
    double x1, y1, x2, y2;
    GetMBR(x1, y1, x2, y2);
    for(int i = 0,j = list.size()-1 ;i < list.size(); j=i++) // 遍历每一个点
    {
        //polygon[]是给出多边形的顶点
        P1 = list[i];
        P2 = list[j];
        if(OnSegment(P1,P2,object)) return true; //点在多边形一条边上
    }
    return false;
}
