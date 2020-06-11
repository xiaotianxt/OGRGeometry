//
// Created by 小田小田 on 2020/6/8.
//

#include "OGRGeometryCollection.h"




void OGRGeometryCollection::AddGeometry(OGRGeometry &object) {
    OGRGeometry *p = &object;
    if (p->GetGeometryType() == std::string("OGRPoint")){
        list.push_back((OGRPoint *)p);
    }
    else if (p->GetGeometryType() == std::string("OGRPolygon")){
        list.push_back((OGRPolygon *)p);
    }
    else if (p->GetGeometryType() == std::string("OGRLineString")){
        list.push_back((OGRLineString *)p);
    }
    else if (p->GetGeometryType() == std::string("OGRCurve")){
        list.push_back((OGRCurve *)p);
    }
}

void OGRGeometryCollection::RemoveGeometry(const int index) {
    if (index >= list.size()){std::cerr << "Wrong Index !" << std::endl;  return; }
    list.erase(list.begin() + index);
}

OGRGeometry *OGRGeometryCollection::GetGeometry(const int index) {
    return list[index];
}

void OGRGeometryCollection::UpdateGeometry(const int index, OGRGeometry &object) {
    list[index] = &object;
}

int OGRGeometryCollection::GetNumGeometries() {
    return list.size();
}

void OGRGeometryCollection::Clone(OGRGeometryCollection & Sample) {
    std::vector<OGRGeometry *> &samplelist = Sample.list;
    list.reserve(samplelist.size());
    for (auto i : samplelist) {
        if (i->GetGeometryType() == std::string("OGRPoint")) // multipoint
            list.push_back(&(((OGRPoint *)i)->Clone()));
        else if (i->GetGeometryType() == std::string("OGRPolygon"))
            list.push_back(&(((OGRPolygon *)i)->Clone()));
        else if (i->GetGeometryType() == std::string("OGRLineString"))
            list.push_back(&(((OGRLineString *)i)->Clone()));
        else if (i->GetGeometryType() == std::string("OGRLinearRing"))
            list.push_back(&(((OGRLinearRing *)i)->Clone()));
    }

}

bool OGRGeometryCollection::IsEmpty() {
    return list.empty();
}

bool OGRGeometryCollection::Equals(const OGRGeometry & Sample) {
    auto *p = dynamic_cast<const OGRGeometryCollection *>(&Sample);

    if (list.size() != (*p).list.size()) return false;
    std::vector<bool> map(list.size(), 0);
    for (int i = 0; i < list.size(); i++){ // 遍历每一个点

        for (int j = 0; j < (*p).list.size(); j++){
            if (map[j]) continue;
            if (list[i]->GetGeometryType() != std::string((*p).list[j]->GetGeometryType()))
                return false;
            else
            {

                if ((*p).list[j]->GetGeometryType() == std::string("OGRPoint"))
                {
                    auto *q = dynamic_cast<OGRPoint *>((*p).list[j]);
                    if(list[i]->Equals(*q) && map[j] ==0)
                    {map[j] = 1; goto a;}
                }
                else if ((*p).list[j]->GetGeometryType() == std::string("OGRPolygon"))
                {
                    auto *q = dynamic_cast<OGRPolygon *>((*p).list[j]);
                    if(list[i]->Equals(*q) && map[j] ==0)
                    {map[j] = 1; goto a;}
                }
                else if ((*p).list[j]->GetGeometryType() == std::string("OGRCurve"))
                {
                    auto *q = dynamic_cast<OGRCurve *>((*p).list[j]);
                    if(list[i]->Equals(*q) && map[j] ==0)
                    {map[j] = 1; goto a;}
                }
                else if ((*p).list[j]->GetGeometryType() == std::string("OGRLineString"))
                {
                    auto *q = dynamic_cast<OGRLineString *>((*p).list[j]);
                    if(list[i]->Equals(*q) && map[j] ==0)
                    {map[j] = 1; goto a;}
                }
                else if ((*p).list[j]->GetGeometryType() == std::string("OGRSurface"))
                {
                    auto *q = dynamic_cast<OGRSurface *>((*p).list[j]);
                    if(list[i]->Equals(*q) && map[j] ==0)
                    {map[j] = 1; goto a;}
                }
                else
                    assert(false);

            }
        }
        return false;
        a:
        NULL;
    }
    return true;
}

OGRGeometryCollection& OGRGeometryCollection::Clone() {

    std::vector<OGRGeometry*> newlist;
    newlist.reserve(list.size());
    for (int i = 0; i < list.size(); i++){
        newlist.push_back(&list[i]->Clone());
    }
    OGRGeometryCollection * newobject = new OGRGeometryCollection(newlist);

    return *newobject;
}
