#ifndef OPENCL_TOOLKIT_PORTABLE_OPENCL_INCLUDE_H
#define OPENCL_TOOLKIT_PORTABLE_OPENCL_INCLUDE_H

/**
 * This wrapper just ensures the inclusion of the properly header file under the macOS.
 */
#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#endif //OPENCL_TOOLKIT_PORTABLE_OPENCL_INCLUDE_H
