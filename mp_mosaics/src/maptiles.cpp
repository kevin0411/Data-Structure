/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if(theTiles.empty())return NULL;
    
    MosaicCanvas* ans = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    map<Point<3>, TileImage*> findTile;
    vector<Point<3>> kdNodes;
    for(int i=0;i<(int)theTiles.size();i++){
        LUVAPixel avg = theTiles[i].getAverageColor();
        Point<3> avgColor = convertToXYZ(avg);
        kdNodes.push_back(avgColor);
        findTile[avgColor] = &theTiles[i]; 
    }

    KDTree<3> k(kdNodes);

    for(int row=0; row<theSource.getRows(); row++){
        for(int col=0; col<theSource.getColumns(); col++){
            LUVAPixel region = theSource.getRegionColor(row, col);
            Point<3> avgRegion = convertToXYZ(region);
            Point<3> near = k.findNearestNeighbor(avgRegion);
            ans->setTile(row, col, findTile[near]);
        }
    }
    return ans;
}

