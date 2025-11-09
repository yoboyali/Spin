#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#define Height 43
#define Width 100
#define CubeSize 20
#define DistanceFromCam 120
#define K1 40
#define R 20
#define r 10
float x , y , z;
float A , B , C;
int Xp , Xy , Delta , Offset;
char buffer[Height * Width];
float zbuffer[Height * Width] , OoZ;
char BackGround = ' ';
float CalculateX(int i, int j, int k) {
  return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float CalculateY(int i, int j, int k) {
  return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
}

float CalculateZ(int i, int j, int k) {
  return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}
float Luminance(float theta , float phi){
  float sinTheta = sin(theta);
    float cosTheta = cos(theta);
    float sinPhi = sin(phi);
    float cosPhi = cos(phi);

    float Nx = cosPhi * cosTheta;
    float Ny = sinPhi * cosTheta;
    float Nz = sinTheta;

    float Lx = 0.0f, Ly = 1.0f, Lz = -1.0f;

    float Lmag = sqrtf(Lx * Lx + Ly * Ly + Lz * Lz);
    Lx /= Lmag; Ly /= Lmag; Lz /= Lmag;

    float L = Nx * Lx + Ny * Ly + Nz * Lz;

    return fmax(0.0f, L);
}
void CalculateCube(float i , float j , float k , int Character){
  x = CalculateX(i,  j,  k);
  y = CalculateY(i, j,  k);
  z = CalculateZ(i, j, k) + DistanceFromCam;
  OoZ = 1 / z;
  Xp = (int)(Width/2 + K1 *OoZ * x *2 + Offset);
  Xy = (int)(Height/2 + K1 * OoZ * y);
  if(z < 0.001){return;}
  if(Xp < 0 || Xp >= Width || Xy < 0 || Xy >= Height){return;}
  Delta = Xp + Xy * Width;
  if(OoZ > zbuffer[Delta]){
    zbuffer[Delta] = OoZ;
    buffer[Delta] = Character;
  }

}
void CalculateCircle(float i , float j , float k , float L){
 x = CalculateX(i, j, k);
    y = CalculateY(i, j, k);
    z = CalculateZ(i, j, k) + DistanceFromCam;

    if (z <= 0.001) return;

    OoZ = 1 / z;
    Xp = (int)(Width / 2 + K1 * OoZ * x * 2 + Offset);
    Xy = (int)(Height / 2 + K1 * OoZ * y);

    if (Xp < 0 || Xp >= Width || Xy < 0 || Xy >= Height) return;

    Delta = Xp + Xy * Width;

    if (OoZ > zbuffer[Delta]) {
        zbuffer[Delta] = OoZ;

        int luminanceIndex = (int)(L * 11);
        luminanceIndex = fmax(0, fmin(11, luminanceIndex));
        const char *shades =".,-~:;=!*#$@";
        buffer[Delta] = shades[luminanceIndex];
    }
}

int main(){

  while(1){
    printf("\x1b[2J");
    memset(buffer , BackGround , Width * Height);
    memset(zbuffer, 0 ,sizeof(zbuffer));
    Offset =25;
  for(float i =- CubeSize ; i < CubeSize ; i+= 0.15){
    for(float j =- CubeSize ; j < CubeSize ; j+=0.15){
        CalculateCube( i , j , -CubeSize , '@');
        CalculateCube( i , j , CubeSize , '#');
        CalculateCube(i , -CubeSize , j , ';');
        CalculateCube(i , CubeSize , j , '~');
        CalculateCube(-CubeSize , i , j , '.');
        CalculateCube(CubeSize , i , j , ',');
    }
  }
   Offset = -25;
for (float theta = 0; theta < 2*  M_PI; theta += 0.07) {
  for (float phi = 0; phi <2 *  M_PI; phi += 0.02) {
    float i = (R + r * cos(theta)) * cos(phi);
    float j = (R + r * cos(theta)) * sin(phi);
    float k = r * sin(theta);
    float L = Luminance(theta , phi);
    CalculateCircle(i, j, k , L);
  }
}

  printf("\x1b[H");
  for(int i = 0 ; i < Width * Height ; i++){
    putchar(i % Width ? buffer[i] : 10);
  }
  A+= 0.05;
  B+= 0.05;
  C+= 0.05;
  usleep(10000);
}
 return 0;
}

