#include<iostream>

using namespace std;

/*
class OGRGeometry;

class OGRPoint;

class OGRPolygon;

class OGRMultiPoint;

class OGRMultiPolygon;
*/
#include "OGRPoint.h"
#include "OGRPolygon.h"
#include "OGRMultiPoint.h"
#include "OGRMultiPolygon.h"
#include "OGRMultiLineString.h"
#include "OGRLinearRing.h"

// You should include your header file here
using namespace std;
namespace testing {
    enum OGRName {
        OGRPoint = 0,
        OGRMultiPoint = 1,
        OGRPolygon = 2,
        OGRMultiPolygon = 3
    };
}


class TestGeometry {
private:


    string OGRName2String(testing::OGRName ogrName) {
        string s = "";
        switch (testing::OGRName(ogrName)) {
            case testing::OGRPoint:
                s = "OGRPoint";
                break;
            case testing::OGRPolygon:
                s = "OGRPolygon";
                break;
            case testing::OGRMultiPoint:
                s = "OGRMultiPoint";
                break;
            case testing::OGRMultiPolygon:
                s = "OGRMultiPolygon";
                break;
            default:
                break;
        }
        return s;
    }

public:

    void Test_Geometry_ImportFromWkt(string path, OGRGeometry *geometry) {
        if (path.empty() || !geometry)
            return;

        try {
            geometry->ImportFromWkt(path.c_str());
        }
        catch (exception &e) {
            cout << "Exception: " << e.what() << endl;
        }
    }

    void Test_Geometry_ExportToWkt(string path, OGRGeometry *geometry) {

        if (path.empty() || !geometry)
            return;

        try {
            geometry->ExportToWkt(path.c_str());
        }
        catch (exception &e) {
            cout << "Exception: " << e.what() << endl;
        }

    }

    void Test_Geometry(string filepath, string filename_import_template, string filename_export_template) {
        OGRGeometry *geometry;
        for (int i = 0; i < 4; i++) { // 临时修改用于查看不同情况
            switch (testing::OGRName(i)) {
                case testing::OGRPoint:
                    geometry = new OGRPoint();
                    break;
                case testing::OGRPolygon:
                    geometry = new OGRPolygon();
                    break;
                case testing::OGRMultiPoint:
                    geometry = new OGRMultiPoint();
                    break;
                case testing::OGRMultiPolygon:
                    geometry = new OGRMultiPolygon();
                    break;
                default:
                    break;
            }

            Test_Geometry_ImportFromWkt(filepath + OGRName2String(testing::OGRName(i)) + filename_import_template,
                                        geometry);
            Test_Geometry_ExportToWkt(filepath + OGRName2String(testing::OGRName(i)) + filename_export_template,
                                      geometry);
        }
    }
};


int main() {
    auto point = OGRPoint();
    auto b = OGRPoint(2.0, -2.5);
    point.ImportFromWkt("wkt/OGRPoint_import.txt");
    point.ExportToWkt("wkt/OGRPoint_export.txt");
    cout << point.GetGeometryType() << endl;
    auto c = OGRPoint();
    cout << c.IsEmpty() << endl;
    c.Clone(b) ;
    assert(b.Equals(c));
    cout << point.GetID() << endl;
    cout << b.GetID() << endl;
    cout << c.GetID() << endl;
    cout << c.IsEmpty() << endl;

    auto d = OGRLineString();
    cout << d.IsEmpty() << endl;
    cout << d.GetID() << endl;
    cout << d.GetGeometryType() << endl;
    cout << d.GetLength() << endl;
    auto e = OGRLineString();
    d.Clone(e);
    assert(d.Equals(e));

    cout << e.GetID() << endl;

    auto g = OGRLinearRing();
    assert(g.IsEmpty());
    cout << g.GetID() << " " << endl;
    cout << g.GetGeometryType() << endl;
    cout << g.GetLength() << endl;
    auto h = OGRLinearRing();
    h.Clone(g);

    assert(h.Equals(g));
    cout << h.GetID() << " " << endl;
    cout << h.GetLength() << endl;

    auto container = OGRGeometryCollection();
    container.AddGeometry(b);
    container.AddGeometry(d);
    container.AddGeometry(g);
    cout << container.GetID() << " " << endl;
    cout << container.GetGeometryType() << endl;
    auto container2 = OGRGeometryCollection();
    container2.Clone(container);
    assert(container2.Equals(container));

    auto multi_point = OGRMultiPoint();
    multi_point.ImportFromWkt("wkt/OGRMultiPoint_import.txt");
    multi_point.ExportToWkt("wkt/OGRMultiPoint_export.txt");
    cout << multi_point.GetID() << " " << endl;
    cout << multi_point.GetGeometryType() << endl;
    auto i = OGRMultiPoint();
    i.Clone(multi_point);
    assert(i.Equals(multi_point));
    i.AddGeometry(point);
    assert(!multi_point.Equals(i));
    i.RemoveGeometry(2); // index按照0 ... n-1来算的
    assert(i.Equals(multi_point));
    cout << i.GetNumGeometries() << endl;

    auto multi_line_str = OGRMultiLineString();
    multi_line_str.AddGeometry(d);
    multi_line_str.AddGeometry(e);
    cout << multi_line_str.GetID() << endl;
    cout << multi_line_str.GetGeometryType() << endl;
    cout << multi_line_str.GetLength() << endl;
    OGRMultiLineString j;
    j.Clone(multi_line_str);
    cout<<j.Equals(multi_line_str)<<endl;
    assert(j.Equals(multi_line_str));
    assert(multi_line_str.Equals(j));
    cout << j.GetLength() << endl;

    auto polygon = OGRPolygon();
    polygon.ImportFromWkt("wkt/OGRPolygon_import.txt");
    polygon.ExportToWkt("wkt/OGRPolygon_export.txt");
    cout << polygon.GetID() << " " << endl;
    cout << polygon.GetGeometryType() << endl;
    cout << polygon.GetPerimeter() << endl;
    cout << polygon.GetArea() << endl;
    cout << polygon.Contains(point) << endl;
    auto p = OGRPoint(3, 3);
    cout << polygon.Contains(p) << endl;
    p = OGRPoint(5, 5);
    cout << polygon.Contains(p) << endl;
    cout << endl;

    return 0;
}
