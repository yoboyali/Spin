# 3D Spinning Ascii donut

Using ascii characters and rotational matrices we can achieve a 3D effect with any geometric shape we want!

# Demo
<img src="https://github.com/yoboyali/Spin/blob/main/imgs/Demo.gif" width=100% />

# Code Explanation

1️⃣ Rotation Matrices

The following functions implement a 3D rotation using Euler angles A, B, and C.

i, j, k represent the original 3D coordinates of a point.

A, B, C are rotation angles updated every frame.

The returned values are the rotated coordinates of that point.

These equations are the expanded form of a combined rotation matrix:

R=Rz(C)⋅Ry(B)⋅Rx(A)
R=R
z
	​

(C)⋅R
y
	​

(B)⋅R
x
	​

(A)

Instead of multiplying matrices explicitly, the trigonometric expansion is written directly for performance.

```python
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
```

2️⃣ Donut (Torus) Point Generation & Projection

The torus is generated parametrically using two angles,
One angle defines the small circle (tube radius)
The other rotates that circle around the larger circle (main radius).

After generating the 3D point:

We rotate it (using the functions above)

Apply perspective projection

Perform depth testing

Compute luminance

Write to character buffer
```python
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
```

# Running the program
this program can be executed using the cmake command<br>
from inside the cmake-build-debug directory run:

```python
cmake --build .
```

To clean the program from inside the same directory run:

```python
cmake --build . --target clean
```
This deletes the generated binary file while leaving your source code intact.

## Credits 

This project would not have been possible without the help of the following sources

```python
https://www.a1k0n.net/2011/07/20/donut-math.html
```
```python
https://youtu.be/p09i_hoFdd0?si=Y03TClF9sU5w_H3e
```
```python
https://youtu.be/0E0UBphVRhY?si=cgl2J_mdYdfsNbYq
```
