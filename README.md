# cl_math.h - Minimal C math utilities

- 2D and 3D vectors
	- Scale
	- Addition

- 4 by 4 square matrix
	- Initialization (null and identity)
	- Multiplication
	- Graphics: 2D orthographic projection
	- Graphics: transformations (translation, scale and rotation)

### Usage

To compile and use the lib (only needed once)

```c
#define CL_MATH_IMPLEMENTATION
#include "cl_math.h"

...

```

To simply use the library

```c
#include "cl_math.h"

...

```

If you do not want the "cl" prefix in front of the types names, define CL_MATH_NO_PREFIX

```c
#define CL_MATH_NO_PREFIX
#include "cl_math.h"

...

```
