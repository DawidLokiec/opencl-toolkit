#include "command_queue.h"
#include <stdexcept>
#include "error.h"
#include <iostream>

using namespace OpenClToolkit;

[[maybe_unused]] CommandQueue::CommandQueue(cl_context context, cl_device_id deviceId) {
	cl_int status = CL_SUCCESS;
	self_ = clCreateCommandQueue(context, deviceId, 0, &status);
	if (status) {
		// let it crash
		throw std::runtime_error("Failed to create command queue. " + toErrorDescription(status));
	}
}

CommandQueue::~CommandQueue() {
	const cl_int status = clReleaseCommandQueue(self_);
	if (status) {
		std::cerr << "Failed to release command queue. " + toErrorDescription(status) << std::endl;
	}
}

[[maybe_unused]] void CommandQueue::enqueueCommandCopyBytesFromHostMemoryIntoDeviceMemory(
		void *sourceHostMemory,
		cl_mem destinationDeviceMemory,
		const size_t numBytesToCopy
) {
	const cl_int status = clEnqueueWriteBuffer(
			self_,
			destinationDeviceMemory,
			CL_TRUE,
			0,
			numBytesToCopy,
			sourceHostMemory,
			0,
			nullptr,
			nullptr
	);
	if (status) {
		// let it crash
		throw std::runtime_error(
				"Failed to copy data from host memory do device memory. " + toErrorDescription(status)
		);
	}
}

[[maybe_unused]] void CommandQueue::enqueueCommandCopyBytesFromDeviceMemoryIntoHostMemory(
		cl_mem sourceDeviceMemory,
		void *destinationHostMemory,
		const size_t numBytesToCopy
) {
	const cl_int status = clEnqueueReadBuffer(
			self_,
			sourceDeviceMemory,
			CL_TRUE,
			0,
			numBytesToCopy,
			destinationHostMemory,
			0,
			nullptr,
			nullptr
	);
	if (status) {
		// let it crash
		throw std::runtime_error(
				"Failed to copy data from device memory to host memory. " + toErrorDescription(status)
		);
	}
}

[[maybe_unused]] void CommandQueue::enqueueCommandExecuteProgramOnDevice(
		const Program &program,
		const size_t numThreads
) {
	const cl_int status = clEnqueueNDRangeKernel(
			self_,
			program.getKernel(),
			1,
			nullptr,
			&numThreads,
			// let the OpenCL implementation determine how to break the global work-items into appropriate work-group instances
			nullptr,
			0,
			nullptr,
			nullptr
	);
	if (status) {
		// let it crash
		throw std::runtime_error("Failed to executed the program: " + toErrorDescription(status));
	}
}

