#include "Perlin3D.h"
#include <iostream>

Perlin3D::Perlin3D(int seed , int NoChunk , double persistance)
    : _seed(seed) , _NoChunk(NoChunk) , _persistance(persistance), _pas(16)
{
    for (int i = 0 ; i < _octave ; i++) {
        for (int j = 0 ; j < _chunkSide ; j++) {
            for (int k = 0 ; k < _chunkSide ; k++) {
                for (int l = 0 ; l < _chunkSide ; l++)
                    _elementaryNoise[i][j][k][l] = 0;
            }
        }  
    }
    
    for (int i = 0 ; i < _chunkSide ; i++) {
        for (int j = 0 ; j < _chunkSide ; j++) {
            for (int  k = 0 ; k < _chunkSide ; k++)
                _chunk[i][j][k] = 0 ;
        }
    }
    init();
}

void Perlin3D::init()
{
    for (int i = 0 ; i < _octave ; i++) {
        noise3D(i , _pas);
        smoothNoise(i);
        // if (i ==3) {
        //     for(int k=0 ; k<16 ; k++) {
        //         for (int j = 0 ; j < 16 ; j++)
        //             std::cout<<_elementaryNoise[2][j][k][0]<<" ";
        //         std::cout<<std::endl;
        //     }
        // }
        _pas /= 2;
    }
    for (int j = 0 ; j < _chunkSide ; j++) {
        for(int k = 0 ; k < _chunkSide ; k++) {
            for (int l = 0 ; l < _chunkSide ; l++) {
                for (int m = 0 ; m < _octave ; m++) {
                    _chunk[j][k][l]+= _elementaryNoise[m][j][k][l] * pow(_persistance , m);
                }
            }
        }
    }
    // for(int i = 0 ; i< _chunkSide ; i++) {
    //     for (int j = 0  ; j < _chunkSide ; j++) {
    //         std::cout<<_chunk[j][0][i]<<" ";
    //     }
    //     std::cout<<std::endl;
    // }
}

int Perlin3D::seed(int chunk1 , int chunk2)
{
    int x=chunk1+chunk2+_seed;
    double y = sin(x)*sin(3*x)*cos(5*x)*sin(7*x)*sin(16*x)*2*pow(x,1/3)*10000;
    if(y < 0) {
        y *=-1;
    }
    return (int) y;
}

double Perlin3D::randUniform()
{
	return (double)rand() / RAND_MAX;
}

void Perlin3D::noise3D(int NoOctave , int _pas)
{
    double value=-1;
    int chunk2 = -1;
    //north side
    chunk2= _NoChunk - _mapSize;
    if(chunk2 > 0) {
        srand(seed(_NoChunk , chunk2));
    }
    else {
        srand(seed(_NoChunk , _NoChunk));
    }
    for (int i = 0 ; i <= _chunkSide ; i += _pas) { //fait varier z
        for (int j = 0 ; j <= _chunkSide ; j += _pas) { //fait varier y
            value = randUniform();
            
            if(i == 0){
                if(j == 0) {
                    _elementaryNoise[NoOctave][0][j][i]= value;
                }
                else if(j == _chunkSide) {
                    _elementaryNoise[NoOctave][0][j-1][i]= value;
                }
                else {
                    _elementaryNoise[NoOctave][0][j][i]= value;
                    _elementaryNoise[NoOctave][0][j-1][i]= value;
                    
                }
            }
            else if(i == _chunkSide) {
                if(j == 0) {
                    _elementaryNoise[NoOctave][0][j][i-1]= value;
                }
                else if(j == _chunkSide) {
                    _elementaryNoise[NoOctave][0][j-1][i-1]= value;
                }
                else {
                    _elementaryNoise[NoOctave][0][j][i-1]= value;
                    _elementaryNoise[NoOctave][0][j-1][i-1]= value;
                }
            }
            else {
                if(j == 0) {
                    _elementaryNoise[NoOctave][0][j][i]= value;
                    _elementaryNoise[NoOctave][0][j][i-1]= value;
                }
                else if(j == _chunkSide) {
                    _elementaryNoise[NoOctave][0][j-1][i]= value;
                    _elementaryNoise[NoOctave][0][j-1][i-1]= value;
                }
                else {
                    _elementaryNoise[NoOctave][0][j][i]= value;
                    _elementaryNoise[NoOctave][0][j-1][i]= value;
                    _elementaryNoise[NoOctave][0][j][i-1]= value;
                    _elementaryNoise[NoOctave][0][j-1][i-1]= value;
                }
            }
        }
    }
    //south side
    chunk2 = _NoChunk + _mapSize;
    if(chunk2 < pow(_mapSize,2)) {
        srand(seed(_NoChunk , chunk2));
    }
    else {
        srand(seed(_NoChunk , _NoChunk));
    }

    for (int i = 0 ; i <= _chunkSide ; i += _pas) { //fait varier z
        for (int j = 0 ; j <= _chunkSide ; j += _pas) { // fait varier y
            value = randUniform();

            if(i == 0) {
                if(j == 0) {
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i] = value;
                }
                else if(j == _chunkSide) {
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i] = value;
                }
                else {
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i] = value;
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i] = value;
                }
            }
            else if(i == _chunkSide) {
                if(j == 0) {
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i-1] = value;
                }
                else if(j == _chunkSide) {
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i-1] = value;
                }
                else {
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i-1] = value;
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i-1] = value;
                }
            }
            else {
                if(j == 0) {
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i] = value;
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i-1] = value;
                }
                else if(j == _chunkSide) {
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i] = value;
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i-1] = value;
                }
                else {
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i] = value;
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i] = value;
                    _elementaryNoise[NoOctave][_chunkSide-1][j][i-1] = value;
                    _elementaryNoise[NoOctave][_chunkSide-1][j-1][i-1] = value;
                }
            }
        }
    }
    //west side
    chunk2 = _NoChunk - 1;
    if(chunk2 % _mapSize != 0) {
        srand(seed(_NoChunk , chunk2));
    }
    else {
        srand(seed(_NoChunk , _NoChunk));
    }
    for (int i = 0 ; i <= _chunkSide ; i += _pas) { //fait varier z
        for (int j = 0 ; j <= _chunkSide ; j += _pas) { // fait varier x
            value = randUniform();
            if(i==0) {
                if(j==0) {
                    _elementaryNoise[NoOctave][j][0][i] = value;
                }
                else if(j==_chunkSide) {
                    _elementaryNoise[NoOctave][j-1][0][i] = value;
                }
                else {
                    _elementaryNoise[NoOctave][j][0][i] = value;
                    _elementaryNoise[NoOctave][j-1][0][i] = value;
                }
            }
            else if(i==_chunkSide) {
                if(j==0) {
                    _elementaryNoise[NoOctave][j][0][i-1] = value;
                }
                else if(j==_chunkSide) {
                    _elementaryNoise[NoOctave][j-1][0][i-1] = value;
                }
                else {
                    _elementaryNoise[NoOctave][j][0][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][0][i-1] = value;
                }
            }
            else {
                if(j==0) {
                    _elementaryNoise[NoOctave][j][0][i] = value;
                    _elementaryNoise[NoOctave][j][0][i-1] = value;
                }
                else if(j==_chunkSide) {
                    _elementaryNoise[NoOctave][j-1][0][i] = value;
                    _elementaryNoise[NoOctave][j-1][0][i-1] = value;
                }
                else {
                    _elementaryNoise[NoOctave][j][0][i] = value;
                    _elementaryNoise[NoOctave][j-1][0][i] = value;
                    _elementaryNoise[NoOctave][j][0][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][0][i-1] = value;
                }
            }
        }
    }
    //east side
    chunk2 = _NoChunk + 1;
    if(chunk2 % (_mapSize+1) != 0) {
        srand(seed(_NoChunk , chunk2));
    }
    else {
        srand(seed(_NoChunk , _NoChunk));
    }
        
    for (int i = 0 ; i <= _chunkSide ; i += _pas) { //fait varier z
        for (int j = 0 ; j <= _chunkSide ; j += _pas) { // fait varier x
            value = randUniform();

            if(i==0) {
                if(j==0) {
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i] = value;
                }
                else if(j==_chunkSide) {
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i] = value;
                }
                else {
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i] = value;
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i] = value;
                }
            }
            else if(i==_chunkSide) {
                if(j==0) {
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i-1] = value;
                }
                else if(j==_chunkSide) {
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i-1] = value;
                }
                else {
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i-1] = value;
                }
            }
            else {
                if(j==0) {
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i] = value;
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i-1] = value;
                }
                else if(j==_chunkSide) {
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i] = value;
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i-1] = value;
                }
                else {
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i] = value;
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i] = value;
                    _elementaryNoise[NoOctave][j][_chunkSide-1][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][_chunkSide-1][i-1] = value;
                }
            }
        }
    }
    // center
    srand(seed(_NoChunk,_NoChunk));
    for (int i = 1 ; i < _chunkSide ; i += _pas) { //fait varier z
        for (int j = _pas ; j < _chunkSide ; j += _pas) { // fait varier x
            for (int k = _pas ; k < _chunkSide ; k += _pas) { //fait varier y
                value = randUniform();

                if(i == 0) {
                    _elementaryNoise[NoOctave][j][k][i] = value;
                    _elementaryNoise[NoOctave][j-1][k][i] = value;
                    _elementaryNoise[NoOctave][j][k-1][i] = value;
                    _elementaryNoise[NoOctave][j-1][k-1][i] = value;
                }
                else if(i == _chunkSide) {
                    _elementaryNoise[NoOctave][j][k][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][k][i-1] = value;
                    _elementaryNoise[NoOctave][j][k-1][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][k-1][i-1] = value;
                }
                else {
                    _elementaryNoise[NoOctave][j][k][i] = value;
                    _elementaryNoise[NoOctave][j-1][k][i] = value;
                    _elementaryNoise[NoOctave][j][k-1][i] = value;
                    _elementaryNoise[NoOctave][j-1][k-1][i] = value;
                    
                    _elementaryNoise[NoOctave][j][k][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][k][i-1] = value;
                    _elementaryNoise[NoOctave][j][k-1][i-1] = value;
                    _elementaryNoise[NoOctave][j-1][k-1][i-1] = value;
                }
            }
        }
    }
}

double Perlin3D::cosInterpolation(double A , double B , double position) // A et B sont la valeur dans la case, positionc [0,1] = position relative
{
    double inter = (1 - cos(position * 3.1415927)) * .5;
    return (1. - inter) * A + inter * B;
}

void Perlin3D::smoothNoise(int NoOctave)
{
    double A,B;
    double position;
    //x interpolation
    
    for (int i = 0 ; i < _chunkSide ; i += _pas) { //fait varier z
        for (int j = 0 ; j < _chunkSide ; j += _pas) { //fait varier y
            for (int k = 0 ; k < _chunkSide ; k += _pas) { // fait varier x
                A = _elementaryNoise[NoOctave][k][j][i];
                B = _elementaryNoise[NoOctave][k+_pas-1][j][i];
                for (int l = 0 ; l < _pas ; l++) { // interpole entre chaque point
                    position = (0.5+l) / _pas;
                    if (i == 0) {
                        if(j == 0) {
                            _elementaryNoise[NoOctave][k+l][j][i] = cosInterpolation(A , B , position);
                        }
                        else if (j == _chunkSide) {
                            _elementaryNoise[NoOctave][k+l][j-1][i] = cosInterpolation(A , B , position);
                        }
                        else {
                            _elementaryNoise[NoOctave][k+l][j][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][k+l][j-1][i] = cosInterpolation(A , B , position);
                        }
                    }
                    else if (i == _chunkSide){
                        if (j == 0){
                            _elementaryNoise[NoOctave][k+l][j][i-1] = cosInterpolation(A , B , position);
                        }
                        else if (j == _chunkSide) {
                            _elementaryNoise[NoOctave][k+l][j-1][i-1] = cosInterpolation(A , B , position);
                        }
                        else {
                            _elementaryNoise[NoOctave][k+l][j][i-1] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][k+l][j-1][i-1] = cosInterpolation(A , B , position);
                        }
                    }
                    else {
                        if (j == 0) {
                            _elementaryNoise[NoOctave][k+l][j][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][k+l][j][i-1] = cosInterpolation(A , B , position);
                        }
                        else if (j == _chunkSide) {
                            _elementaryNoise[NoOctave][k+l][j-1][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][k+l][j-1][i-1] = cosInterpolation(A , B , position);
                        }
                        else {
                            _elementaryNoise[NoOctave][k+l][j][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][k+l][j-1][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][k+l][j][i-1] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][k+l][j-1][i-1] = cosInterpolation(A , B , position);
                        }
                    }
                }
            }
        }
    }
    //y interpolation
    
    for (int i = 0 ; i < _chunkSide ; i += _pas) { // fait varier z
        for (int j = 0 ; j < _chunkSide ; j ++) { //fait varier x
            for (int k = 0 ; k < _chunkSide ; k += _pas) { // fait varier y
                A = _elementaryNoise[NoOctave][j][k][i];
                B = _elementaryNoise[NoOctave][j][k+_pas-1][i];
                for (int l = 0 ; l < _pas ; l++) { //interpole entre chaque point
                    position = (0.5+l) / _pas;
                    if (i == 0) {
                        if (j == 0) {
                            _elementaryNoise[NoOctave][j][k+l][i] = cosInterpolation(A , B , position);
                        }
                        else if (j == _chunkSide) {
                            _elementaryNoise[NoOctave][j-1][k+l][i] = cosInterpolation(A , B , position);
                        }
                        else {
                            _elementaryNoise[NoOctave][j][k+l][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][j-1][k+l][i] = cosInterpolation(A , B , position);
                        }
                    }
                    else if (i == _chunkSide) {
                        if (j == 0) {
                            _elementaryNoise[NoOctave][j][k+l][i-1] = cosInterpolation(A , B , position);
                        }
                        else if (j == _chunkSide) {
                            _elementaryNoise[NoOctave][j-1][k+l][i-1] = cosInterpolation(A , B , position);
                        }
                        else {
                            _elementaryNoise[NoOctave][j][k+l][i-1] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][j-1][k+l][i-1] = cosInterpolation(A , B , position);
                        }
                    }
                    else {
                        if (j == 0) {
                            _elementaryNoise[NoOctave][j][k+l][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][j][k+l][i-1] = cosInterpolation(A , B , position);
                        }
                        else if (j == _chunkSide) {
                            _elementaryNoise[NoOctave][j-1][k+l][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][j-1][k+l][i-1] = cosInterpolation(A , B , position);
                        }
                        else {
                            _elementaryNoise[NoOctave][j][k+l][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][j-1][k+l][i] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][j][k+l][i-1] = cosInterpolation(A , B , position);
                            _elementaryNoise[NoOctave][j-1][k+l][i-1] = cosInterpolation(A , B , position);
                        }
                    }
                }  
            }
        }
    }
    //z interpolation
    
    for (int i = 0 ; i < _chunkSide ; i++) { //fait varier x
        for (int j = 0 ; j < _chunkSide ; j++) { //fait varier y
            for (int k = 0 ; k < _chunkSide ; k += _pas) { //fait varier z
                A = _elementaryNoise[NoOctave][i][j][k];
                B = _elementaryNoise[NoOctave][i][j][k+_pas-1];
                for (int l = 0 ; l <_pas ; l++) { //interpole entre chaque point
                    position = (0.5+l) / _pas;
                    _elementaryNoise[NoOctave][i][j][k+l] = cosInterpolation(A , B , position);
                }
            }
        }
    }
}

double Perlin3D::getChunk(int x , int y , int z)
{
    return _chunk [x][y][z];
}