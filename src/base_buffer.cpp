#include "base_buffer.h"
#include <stdexcept>
#include <iostream>

using namespace OpenClToolkit;

BaseBuffer::BaseBuffer(cl_context context, const size_t size, const cl_mem_flags flags) {
	cl_int status;
	self_ = clCreateBuffer(context, flags, size, nullptr, &status);
	if (status) {
		// let it crash
		throw std::runtime_error("Failed to create buffer: " + getFailureDescription(status));
	}
}

BaseBuffer::~BaseBuffer() {
	const cl_int status = clReleaseMemObject(self_);
	if (status) {
		std::cerr << "Failed to release the buffer: " + getFailureDescription(status) << std::endl;
	}
}

BaseBuffer::operator cl_mem() const {
	return self_;
}

std::string BaseBuffer::getFailureDescription(const cl_int errorCode) {
	switch (errorCode) {
		case CL_INVALID_CONTEXT:
			return "CL_INVALID_CONTEXT: the passed contex is invalid";
		case CL_INVALID_VALUE:
			return "CL_INVALID_VALUE: the passed flag is invalid";
		case CL_INVALID_BUFFER_SIZE:
			return "CL_INVALID_BUFFER_SIZE: the passed size is outside the range 1 and " +
				   std::to_string(CL_DEVICE_MAX_MEM_ALLOC_SIZE);
		case CL_INVALID_HOST_PTR:
			return "CL_INVALID_HOST_PTR: the passed pointer and the flag are not allowed together";
		case CL_OUT_OF_RESOURCES:
			return "CL_OUT_OF_RESOURCES: cannot allocate resources required by the OpenCL implementation on the device";
		case CL_OUT_OF_HOST_MEMORY:
			return "CL_OUT_OF_HOST_MEMORY: cannot allocate resources required by the OpenCL implementation on the host";
		case CL_INVALID_MEM_OBJECT: // -38
			return "CL_INVALID_MEM_OBJECT: the passed memory object is not valid";
		default:
			return "unknown error code: " + std::to_string(errorCode);
	}
}