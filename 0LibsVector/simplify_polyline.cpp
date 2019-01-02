#include <QDebug>
#include <iostream>
#include <math.h>

#include "simplify_polyline.h"
#include "globals.h"

using namespace std;


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;
bool simplify_polyline_success = true; //Not ideal, need to use to keep simple

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dPointToLine
// Used in simplify_polyline below
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double dPointToLine(Point L1, Point L2, Point P)
{
    double dist = (L1.y-L2.y)*P.x + (L2.x-L1.x)*P.y + (L1.x*L2.y - L2.x*L1.y);
    double botdist = sqrt(pow((L2.x-L1.x),2) + pow((L2.y-L1.y),2));

    if(botdist == 0) //to avoid divide by zero
    {
        dist = 0;
    }
    else
    {
        dist = dist / botdist;
    }

    if(L1.x==L2.x && L1.y==L2.y)
        dist = sqrt(pow((L1.x-P.x),2) + pow((L1.y-P.y),2));

    return (dist > 0 ? dist:(-dist));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// simplify_polyline
// Used in Vector Processing
// Is a recursive function, using global boolean for error checking
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void simplify_polyline(Point *poly, int start, int end, double tolerance, int *marker)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start simplify_polyline";

    try {

        if(poly == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1000] poly is null.");
            simplify_polyline_success = false;
            return;
        }

        // Flag accounts if the function is called for the first time.. 0=>first time; 1=>otherwise
        if (end < start+1)
            return;

        int     maxIndex = start;   // index of vertex farthest from S
        double   maxDistance = 0;   // distance squared of farthest vertex

        for (int i = start+1; i < end; i++)
        {
            double dist = dPointToLine(poly[start], poly[end], poly[i]);
            if(dist > maxDistance)
            {
                maxDistance = dist;
                maxIndex = i;
            }
        }

        if(maxDistance > tolerance)
        {
            marker[maxIndex] = 1;
            simplify_polyline(poly, start, maxIndex, tolerance, marker);
            simplify_polyline(poly, maxIndex, end, tolerance, marker);
        }

        return;

    }
    catch (...)
    {
        qDebug() << "Error: simplify_polyline is returning w/o checking";
        simplify_polyline_success = false;
        return;
    }

}

