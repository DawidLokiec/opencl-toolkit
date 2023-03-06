#include <stdexcept>
#include <iostream>

#include "opencl/context.h"

using namespace OpenClToolkit;

[[maybe_unused]] Context::Context(cl_device_id device) {
	cl_int status;
	self_ = clCreateContext(
			nullptr,
			1,
			&device,
			nullptr,
			nullptr,
			&status
	);
	if (status) {
		// let it crash
		throw std::runtime_error("Failed to create context: " + getFailureDescription(status));
	}
}

Context::~Context() {
	const cl_int status = clReleaseContext(self_);
	if (status) {
		std::cerr << "Failed to release context: " + getFailureDescription(status) << std::endl;
	}
}

Context::operator cl_context() const {
	return self_;
}

std::string Context::getFailureDescription(cl_int errorCode) {
	switch (errorCode) {
		case CL_INVALID_CONTEXT: // -34
			return "CL_INVALID_CONTEXT: The context is invalid.";
		case CL_INVALID_DEVICE:    // -33
			return "CL_INVALID_DEVICE: Invalid devices were passed or are not associated with the specified platform.";
		case CL_INVALID_PLATFORM: // -32
			return "CL_INVALID_PLATFORM: Either properties is NULL and no platform could be selected or if platform "
				   "value specified in properties is not a valid platform";
		case CL_INVALID_VALUE: // -30
			return "CL_INVALID_VALUE: Either context property name in properties is not a supported property name; "
				   "devices is NULL; num_devices is equal to zero; or if pfn_notify is NULL but user_data is not NULL.";
		case CL_DEVICE_NOT_AVAILABLE: // -2
			return "CL_DEVICE_NOT_AVAILABLE: A device in devices is currently not available even though the device was "
				   "returned by clGetDeviceIDs.";
		case CL_OUT_OF_HOST_MEMORY: // -6
			return "There is a failure to allocate resources required by the OpenCL implementation on the host.";
		case CL_SUCCESS: // 0
			return "CL_SUCCESS: No errors occurred.";
		default:
			return "Unknown error code: " + std::to_string(errorCode) + ".";
	}
}
