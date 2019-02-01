/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

/**
 *creates a mosaic canvas given a source image and a test of tile images
 */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    // This will be our return value
    MosaicCanvas* result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
    // We construct a vector of points that represent LUV pixels, and a map from each tileImage's average color to itself
    vector<Point<3>> treePoints;
    map<Point<3>, unsigned> colorMap;
    for (unsigned i = 0; i < theTiles.size(); i++)
    {
        Point<3> convertedXYZ = convertToXYZ(theTiles[i].getAverageColor());
        treePoints.push_back(convertedXYZ);
        colorMap.insert(pair<Point<3>, unsigned>(convertedXYZ, i));
    }

    KDTree<3> tileTree(treePoints);

    for (int x = 0; x < result -> getRows(); x++)
    {
        for (int y = 0; y < result -> getColumns(); y++)
        {
            // Set the result mosaic canvas at (x, y) to the TileImage mapped at the key of the nearest neighbor of the source image at (x, y)
            result -> setTile(x, y, &theTiles[colorMap.at(tileTree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(x, y))))]);
        }
    }

    return result;
}

