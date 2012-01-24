
#ifndef _included_radargrid_h
#define _included_radargrid_h

#include "lib/tosser/bounded_array.h"
#include "lib/math/fixed.h"

#define RADARGRID_WIDTH     360
#define RADARGRID_HEIGHT    200

struct RadarGridCell;


template< class T > class Vector2;

class RadarGrid
{
protected:
    unsigned char * m_radar;
    int             m_resolution;
    int             m_teamCount;
    
    void            GetIndices( Fixed _longitude, Fixed _latitude, int &_x, int &_y );
    void            GetIndices( Fixed _longitude, Fixed _latitude, Fixed _radius, int &_x, int &_y, int &_w, int &_h );

    void            GetIndicesRadar( int &_x, int &_y );

    void            GetWorldLocation( int _indexX, int _indexY, Fixed &_longitude, Fixed &_latitude ) const;

    void            ModifyCoverage( int _x, int _y, Fixed _radius, int _teamId, bool addCoverage );
    bool            IsInside( int x, int y, Fixed const & radiusSquared, Vector2<Fixed> const & centre ) const;

    void AddCoverage    ( int _x, int _y, Fixed _radius, int _teamId );
    void RemoveCoverage ( int _x, int _y, Fixed _radius, int _teamId );
public:
    RadarGrid();
    ~RadarGrid();

    void Initialise( int _resolution, int _numTeams );                              // Resolution should be 1 (normal), 2 (double) etc

    void AddCoverage    ( Fixed _longitude, Fixed _latitude, Fixed _radius, int _teamId );
    void RemoveCoverage ( Fixed _longitude, Fixed _latitude, Fixed _radius, int _teamId );
    
    void UpdateCoverage ( Fixed _oldLongitude, Fixed _oldLatitude, Fixed _oldRadius,
                          Fixed _newLongitude, Fixed _newLatitude, Fixed _newRadius, int _teamId );

    int  GetCoverage    ( Fixed _longitude, Fixed _latitude, int _teamId );
    void GetMultiCoverage( Fixed _longitude, Fixed _latitude, BoundedArray< int > & coveragePerTeam );

    void Render();                                                                  // Very slow
};



#endif

