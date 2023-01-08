#include "buffer_factories.h"
#include <string>
#include <stdexcept>

using namespace OpenClToolkit;

namespace {
	std::string getFailureDescription(const cl_int errorCode) {
		switch (errorCode) {
			case CL_INVALID_CONTEXT:
				return "CL_INVALID_CONTEXT: the passed contex is invalid";
			case CL_INVALID_VALUE:
				return "CL_INVALID_VALUE: the passed flag is invalid";
			case CL_INVALID_BUFFER_SIZE:
				return "CL_INVALID_BUFFER_SIZE: the passed size is outside the range 1 and CL_DEVICE_MAX_MEM_ALLOC_SIZE";
			case CL_INVALID_HOST_PTR:
				return "CL_INVALID_HOST_PTR: the passed pointer and the flag are not allowed together";
			case CL_OUT_OF_RESOURCES:
				return "CL_OUT_OF_RESOURCES: cannot allocate resources required by the OpenCL implementation on the device";
			case CL_OUT_OF_HOST_MEMORY:
				return "CL_OUT_OF_HOST_MEMORY: cannot allocate resources required by the OpenCL implementation on the host";
			default:
				return "unknown error code: " + std::to_string(errorCode);
		}
	}

	cl_mem createBuffer(cl_context context, const size_t size, const cl_mem_flags flags) {
		cl_int status;
		cl_mem buffer = clCreateBuffer(context, flags, size, nullptr, &status);
		if (status) {
			// let it crash
			throw std::runtime_error("Failed to create buffer: " + getFailureDescription(status));
		} else {
			return buffer;
		}
	}
}

[[maybe_unused]] cl_mem createReadOnlyBuffer(cl_context context, const size_t size) {
	return createBuffer(context, size, CL_MEM_READ_ONLY);
}

[[maybe_unused]] cl_mem createWriteOnlyBuffer(cl_context context, const size_t size) {
	return createBuffer(context, size, CL_MEM_WRITE_ONLY);
}