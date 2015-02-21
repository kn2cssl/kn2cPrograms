#include "voronoi_diagram.h"

Voronoi_Diagram::Voronoi_Diagram()
{
}

QList<Vector2D> Voronoi_Diagram::calculate(QList<Vector2D> in_points)
{
    //consider some points
    std::vector<Point_2> points;
    for(int i=0;i<in_points.size();i++)
    {
        points.push_back(Point_2(in_points.at(i).x,in_points.at(i).y));
    }

    Delaunay_triangulation_2 dt2;
    //insert points into the triangulation
    dt2.insert(points.begin(),points.end());
    //construct a rectangle
    Iso_rectangle_2 bbox(-500,-500,500,500);
    Cropped_voronoi_from_delaunay vor(bbox);
    //extract the cropped Voronoi diagram
    dt2.draw_dual(vor);
    //print the cropped Voronoi diagram as segments
    for(int i=0;i<vor.m_cropped_vd.size();i++)
        std::cout << vor.m_cropped_vd[i]<<"\n";
    std::cout<<"-----------------\n";
    std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),
              std::ostream_iterator<Segment_2>(std::cout,"\n"));
}
