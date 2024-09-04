# Triangle Intersection

| Github workflow | [![Build and Test](https://github.com/PrusC/triangle_intersection/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/PrusC/triangle_intersection/actions) |
| --------------- |----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

A pair or triangles is given as list of their vertices coordinates in three-dimensional space. 
Implemented algorithms checks whether triangles are intersecting or not.
____

# Project structure

![project_structure_graph](/images/project_structure_graph.png)

The project consists of three static libraries 'ti-geometry', 'ti-algorithms' and 'ti-io' and also
one executable 'ti-checker'. The libraries are covered by unit tests 'test-geometry', 
'test-algorithms' and 'test-io'.

### ti-geometry 

Contains base geometrical primitives need for solving triangle intersection problem and common 
operations with these primitive.

* `Point3D` - Represent a cartesian point in 3D.\
* `Vector3D` - Represents a mathematical vector in 3D. \
For `Vector3D` objects the following operation are defined:

```C++
Vector3D operator+(const Vector3D& leftV, const Vector3D& rightV);
Vector3D operator-(const Vector3D& leftV, const Vector3D& rightV);
Vector3D operator-(const Point3D& lastP, const Point3D& firstP);
Vector3D operator*(const Vector3D& vector, double number);
Vector3D operator*(double number, const Vector3D& vector);
Vector3D operator+(const Vector3D& vector, const Point3D& point);
Vector3D operator+(const Point3D& point, const Vector3D& vector);
Vector3D operator-(const Vector3D& vector, const Point3D& point);
Vector3D operator-(const Point3D& point, const Vector3D& vector);

double Scalar(const Vector3D& leftV, const Vector3D& rightV);
Vector3D Cross(const Vector3D& leftV, const Vector3D& rightV);
```
* `Segment3D` - Represents a segment object in 3D set by a couple of `Point3D`
* `Triangle3D` - Represent a triangle object in 3D set by three `p0`, `p1`, `p2` Points3D


### ti-algorithms

Contains all operations for checking intersection between two triangles. Its public api
consist of the following functions:
```C++
bool IsIntersect(const Point3D& point1, const Point3D& point2);
bool IsIntersect(const Point3D& point, const Segment3D& segment);
bool IsIntersect(const Segment3D& segment1, const Segment3D& segment2);
bool IsIntersect(const Segment3D& segment, const Triangle3D& triangle);
bool IsIntersect(const Triangle3D& triangle1, const Triangle3D& triangle2);
```
Actually for usage only the last function `bool IsIntersect(const Triangle3D& triangle1, const Triangle3D& triangle2)` 
is needed. All other functions are called inside it. But I decided to make all of them public to be able to write unit 
tests for them.

### ti-io

Contains operators `<<` and `>>` for `Point3D` and `Triangle3D` for working with `std::ostream` and `std::istream`.

### ti-checker

Simple console application which has only the name of the text file as input. The text file containing coordinates of 
triangle vertices and expected results. Empty lines and lines starting with ‘#’ must be ignored. The output (to `std::cout`)
will be the number of executed and failed tests. \
The samples of input files with expected output are shown below: 

| input1.txt                                                                 | input2.txt                                                                                                                           | input3.txt                                                                                                                                                           | 
|----------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| #this is a comment <br> 0 0 0 1 0 0 0 1 0 <br> 0 0 0 1 0 0 0 1 0 <br> true | #this is a comment <br> 0 0 0 1 0 0 0 1 0 <br> 0 0 0 1 0 0 0 1 0  <br> true <br>0 0 0 10 0 0 0 10 0 <br> 1 1 0 1 1 0 1 1 0 <br> true | 1 0 1 2 0 1 1 1 1 <br> 0 0 0 1 0 0 0 1 0 <br> false <br> 0 0 0 1 0 0 0 1 0 <br> 0 0 -1 1 0 1 0 1 1 <br> true <br> 0 0 0 0 0 5 5 5 5 <br> 5 0 0 5 0 5 0 5 5 <br> true |
| **Expected output:** <br> Tests done 1/ failed 0                           | **Expected output:** <br> line 4: expected false, got true <br> Tests done 2; failed 1                                               | **Expected output:** <br> Tests done 3/0 failed                                                                                                                      |

To run the application: \
`ti-checker input_file_name.txt[relative or absolute]`

____
# Installation

The project is built using [Cmake](https://cmake.org)(version 3.23 or newer).\
CMakeLists.txt has two options:
* `BUILD_UNITTESTS` - options allows you to build unit-test. For building unit-tests [GoogleTest](https://github.com/google/googletest.git) is required.
By default this option is `ON`.
* `BUILD_EXECUTABLE` - options allows you to build console application. If you want use only libraries and you
don't need to build executable you can set it `OFF`. By default this option is `ON`.

To build the project and run unit tests you can use the following commands:
* On Linux:
```
git clone https://github.com/PrusC/triangle_intersection.git
cd to/path/triangle_intersection
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE="Release" \
         -DCMAKE_INSTALL_PREFIX="to/path/install" \
         -DBUILD_UNITTESTS=ON \
         -DBUILD_EXECUTABLE=ON
cmake --build . --config Release --target install 
ctest .
```
* On Windows (with Visual Studio):
```
git clone https://github.com/PrusC/triangle_intersection.git
cd to/path/triangle_intersection
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX="to/path/install" -DBUILD_UNITTESTS=ON -DBUILD_EXECUTABLE=ON
cmake --build . --config Release --target install
cmake.exe --build . --target RUN_TESTS --config Release
```
After installing the 'to/path/install' folder should contain four folders:
* 'include' - contains all header files
* 'lib' - contains 'ti-geometry', 'ti-algorithms' and 'ti-io' static build files
* 'bin' - contains 'ti-checker' application'
* 'tests' - contains unit tests
* 'examples' - contains several samples of input files for 'ti-checker'
