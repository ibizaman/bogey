#ifndef PERLIN3D_H
#define PERLIN3D_H

#include <cmath>
#include <ctime>
#include <cstdlib>

class Perlin3D
{
    
public:
    Perlin3D(int seed , int NoChunk , double persistance);
    void init();
    int seed(int chunk1 , int chunk2);
    double randUniform();
    void noise3D(int NoOctave , int pas);
    double cosInterpolation(double A , double B , double position);
    void smoothNoise(int NoOctave);
    double getChunk (int x , int y , int z);
    
private:
    
    int _seed;
    int _NoChunk;
    static const int _chunkSide = 16;
    double _chunk[_chunkSide][_chunkSide][_chunkSide];
    double _persistance;
    double _amplitude;
    int _pas;
    static const int _octave = 4;
    static const int _mapSize = 65536;
    double _elementaryNoise[_octave][_chunkSide][_chunkSide][_chunkSide];
    
          
};

#endif