#include "program.h"
#include <stdexcept>
#include <iostream>

using namespace OpenClToolkit;

[[maybe_unused]] Program::Program(
		const char *kernelSourceCode,
		const std::string &kernelName,
		cl_context context,
		cl_device_id device
) : kernelName_(kernelName), device_(device) {
	cl_int status;
	program_ = clCreateProgramWithSource(
			context,
			1,
			static_cast<const char **>(&kernelSourceCode),
			nullptr,
			&status
	);
	if (status) {
		// let it crash
		throw std::runtime_error(
				"Cannot create OpenCL-program: " + getProgramCreationFailureReason(status)
		);
	}

	status = clBuildProgram(
			program_,
			1,
			&device,
			nullptr,
			nullptr,
			nullptr
	);

	if (status) {
		std::cerr << "There were problems while building the kernel: " << std::endl;
		char buildLog[4096];
		clGetProgramBuildInfo(
				program_,
				device,
				CL_PROGRAM_BUILD_LOG,
				sizeof(char) * 4096,
				buildLog,
				nullptr
		);
		std::cerr << buildLog << std::endl;
		// let it crash
		throw std::runtime_error("Cannot build OpenCL-program: " + getProgramBuildFailureReason(status));
	}

	kernel_ = clCreateKernel(program_, kernelName.c_str(), &status);

	if (status) {
		// let it crash
		throw std::runtime_error("Cannot create kernel: " + getKernelCreationFailureReason(status));
	}
}

Program::~Program() {
	cl_int status = clReleaseKernel(kernel_);
	if (status) {
		std::string reason;
		switch (status) {
			case CL_INVALID_KERNEL:
				reason = "the kernel is invalid";
				break;
			case CL_OUT_OF_RESOURCES:
				reason = "allocate resources required by the OpenCL implementation on the 'device'";
				break;
			case CL_OUT_OF_HOST_MEMORY:
				reason = "allocate resources required by the OpenCL implementation on the 'host'";
				break;
			default:
				reason = "unknown error code: " + std::to_string(status);
				break;
		}
		std::cerr << "Failed to release the OpenCL-kernel: " + reason << std::endl;
	}
	status = clReleaseProgram(program_);
	if (status) {
		std::string reason;
		switch (status) {
			case CL_INVALID_PROGRAM:
				reason = "the program is invalid";
				break;
			case CL_OUT_OF_RESOURCES:
				reason = "allocate resources required by the OpenCL implementation on the 'device'";
				break;
			case CL_OUT_OF_HOST_MEMORY:
				reason = "allocate resources required by the OpenCL implementation on the 'host'";
				break;
			default:
				reason = "unknown error code: " + std::to_string(status);
				break;
		}
		std::cerr << "Failed to release the OpenCL-program: " + reason << std::endl;
	}
}

[[maybe_unused]] cl_kernel Program::getKernel() const {
	return kernel_;
}

[[maybe_unused]] void Program::setKernelArg(const cl_uint argIndex, const size_t argSize, const void *argValue) {
	cl_int status;
	status = clSetKernelArg(
			kernel_,
			argIndex,
			argSize,
			argValue
	);
	if (status) {
		std::string reason;
		switch (status) {
			case CL_INVALID_KERNEL:
				reason = "kernel is invalid";
				break;
			case CL_INVALID_ARG_INDEX:
				reason = "the argument index: " + std::to_string(argIndex) + " is invalid";
				break;
			case CL_INVALID_ARG_VALUE:
				reason = "the argument value may not be NULL for a parameter declared with the __local qualifier or vice-versa";
				break;
			case CL_INVALID_MEM_OBJECT:
				reason = "the argument is declared to be a memory object but the passed value is not a valid memory object";
				break;
			case CL_INVALID_SAMPLER:
				reason = "the argument is declared to be a of type sampler_t but the passed value is not a valid sampler object";
				break;
			case CL_INVALID_ARG_SIZE:
				reason = "the value '" + std::to_string(argSize) + "' for argument 'size'"
																   " does not match the size of the data type of the passed argument at index '"
						 + std::to_string(argIndex) + "'";
				break;
			default:
				reason = "unknown error code: " + std::to_string(status);
				break;
		}
		// let it crash
		throw std::runtime_error("Cannot set kernel argument: " + reason);
	}
}

[[maybe_unused]] void Program::setKernelArg(cl_uint argIndex, size_t argSize, cl_mem buffer) {
	setKernelArg(argIndex,argSize, &buffer);
}

size_t Program::getMaxWorkGroupSizeInBytes() const {
	size_t size = -1;
	cl_int status = clGetKernelWorkGroupInfo(
			kernel_,
			device_,
			CL_KERNEL_WORK_GROUP_SIZE,
			sizeof(size_t),
			&size,
			nullptr
	);
	if (status) {
		// let it crash
		throw std::runtime_error("Cannot retrieve max work group size of current kernel: " +
								 getKernelWorkGroupInfoQueryFailureReason(status)
		);
	} else {
		return size;
	}
}

cl_ulong Program::getDeviceGlobalMemorySizeInBytes() const {
	cl_ulong size = -1;
	cl_int status = clGetDeviceInfo(
			device_,
			CL_DEVICE_GLOBAL_MEM_SIZE,
			sizeof(cl_ulong),
			&size,
			nullptr
	);

	if (status) {
		// let it crash
		throw std::runtime_error("Cannot retrieve the global memory size of the current used device: " +
								 getDeviceInfoQueryFailureReason(status)
		);
	} else {
		return size;
	}
}

size_t Program::getDeviceMaxGlobalVariableSizeInBytes() const {
	size_t size = -1;
	cl_int status = clGetDeviceInfo(
			device_,
			CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE,
			sizeof(size_t),
			&size,
			nullptr
	);

	if (status) {
		// let it crash
		throw std::runtime_error(
				"Cannot retrieve the max supported global variable size of the current used device: " +
				getDeviceInfoQueryFailureReason(status)
		);
	} else {
		return size;
	}
}

size_t Program::getDeviceLocalMemorySizeInBytes() const {
	cl_ulong size = -1;
	cl_int status = clGetDeviceInfo(
			device_,
			CL_DEVICE_LOCAL_MEM_SIZE,
			sizeof(cl_ulong),
			&size,
			nullptr
	);


	if (status) {
		// let it crash
		throw std::runtime_error(
				"Cannot retrieve local memory size of the current used device: " +
				getDeviceInfoQueryFailureReason(status)
		);
	} else {
		return size;
	}
}

[[maybe_unused]] void Program::printDeviceMemoryInfo(const bool useStderr) const {
	std::string output =
			"Device memory info:\n"
			"  Global memory size [bytes]: " + std::to_string(getDeviceGlobalMemorySizeInBytes()) +
			"\n  Max supported global variable size [byes]: " + std::to_string(getDeviceMaxGlobalVariableSizeInBytes())
			+ "\n  Local memory size [bytes]: " + std::to_string(getDeviceLocalMemorySizeInBytes()) + "\n";
	if (useStderr) {
		std::cerr << output;
	} else {
		std::cout << output;
	}
}

[[maybe_unused]] void Program::execute(cl_command_queue commandQueue, const size_t numThreads) const {
	const cl_int status = clEnqueueNDRangeKernel(
			commandQueue,
			kernel_,
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
		std::string reason;
		switch (status) {
			case CL_INVALID_PROGRAM_EXECUTABLE:
				reason = "no successfully built program executable available for device associated with passed queue";
				break;
			case CL_INVALID_COMMAND_QUEUE:
				reason = "the passed command queue is not a valid host command-queue";
				break;
			case CL_INVALID_KERNEL:
				reason = "the used kernel is invalid";
				break;
			case CL_INVALID_CONTEXT:
				reason = "the context associated with the command queue and kernel art not the same";
				break;
			case CL_INVALID_KERNEL_ARGS:
				reason = "the kernels args are invalid (check the passed values and if pointers point to a named address space)";
				break;
			case CL_INVALID_WORK_DIMENSION:
				reason = "the specified work dimension is invalid (must be between 1 and CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS)";
				break;
			case CL_INVALID_GLOBAL_WORK_SIZE:
				reason = "the value for global work size is invalid must be between 1 and maximum value representable "
						 "by size t on the device on which the kernel-instance will be enqueued";
				break;
			case CL_INVALID_GLOBAL_OFFSET:
				reason = "the value specified in global_work_size + the corresponding values in global_work_offset for "
						 "any dimensions is greater than the maximum value representable by size t on the device on "
						 "which the kernel-instance will be enqueued.";
				break;
			case CL_INVALID_WORK_GROUP_SIZE:
				reason = "the specified work group size does not fit the allowed max size '" +
						 std::to_string(getMaxWorkGroupSizeInBytes()) + "' for the current kernel";
				break;
			case CL_INVALID_VALUE:
				reason = "the kernel name is NULL";
				break;
			case CL_OUT_OF_HOST_MEMORY:
				reason = "allocate resources required by the OpenCL implementation on the host";
				break;
			default:
				reason = "unknown error code: " + std::to_string(status);
				break;
		}
		// let it crash
		throw std::runtime_error("Failed to executed the kernel: " + reason);
	}
}

std::string Program::getKernelCreationFailureReason(const cl_int errorCode) const {
	switch (errorCode) {
		case CL_INVALID_PROGRAM:
			return "the associated program is invalid";
		case CL_INVALID_PROGRAM_EXECUTABLE:
			return "there is no successfully built executable for the program";
		case CL_INVALID_KERNEL_NAME:
			return "the kernel name '" + kernelName_ + "' could not be found in the provided source code";
		case CL_INVALID_KERNEL_DEFINITION:
			return "invalid kernel definition (check the number and types of the arguments for all devices are the same)";
		case CL_INVALID_VALUE:
			return "the kernel name is NULL";
		case CL_OUT_OF_HOST_MEMORY:
			return "allocate resources required by the OpenCL implementation on the host";
		default:
			return "unknown error code: " + std::to_string(errorCode);
	}
}

std::string Program::getProgramCreationFailureReason(const cl_int errorCode) {
	switch (errorCode) {
		case CL_INVALID_CONTEXT:
			return "the passed context is invalid";
		case CL_INVALID_VALUE:
			return "NULL was passed for the kernel source code";
		case CL_OUT_OF_HOST_MEMORY:
			return "allocate resources required by the OpenCL implementation on the host";
		default:
			return "unknown error code: " + std::to_string(errorCode);
	}
}

std::string Program::getProgramBuildFailureReason(const cl_int errorCode) {
	switch (errorCode) {
		case CL_INVALID_PROGRAM:
			return "the program is invalid";
		case CL_INVALID_VALUE:
			return "the passed device is NULL";
		case CL_INVALID_DEVICE:
			return "the passed device is not in the list of devices associated with program";
		case CL_INVALID_BINARY:
			return "the loaded program binary are invalid";
		case CL_INVALID_BUILD_OPTIONS:
			return "the specified build options are invalid";
		case CL_INVALID_OPERATION:
			return "there previous build has not completed";
		case CL_COMPILER_NOT_AVAILABLE:
			return "the compiler is not available";
		case CL_BUILD_PROGRAM_FAILURE:
			return "failure to build the program executable";
		case CL_OUT_OF_HOST_MEMORY:
			return "allocate resources required by the OpenCL implementation on the host";
		default:
			return "unknown error code: " + std::to_string(errorCode);
	}
}

std::string Program::getKernelWorkGroupInfoQueryFailureReason(const cl_int errorCode) {
	switch (errorCode) {
		case CL_INVALID_KERNEL:
			return "the passed kernel is invalid";
		case CL_INVALID_DEVICE:
			return "the passed device is not associated with the kernel";
		case CL_INVALID_VALUE:
			return "an invalid valid value was passed as an argument";
		case CL_OUT_OF_RESOURCES:
			return "cannot allocate resources required by the OpenCL implementation on the 'device'";
		case CL_OUT_OF_HOST_MEMORY:
			return "cannot allocate resources required by the OpenCL implementation on the 'host'";
		default:
			return "unknown error code: " + std::to_string(errorCode);
	}
}

std::string Program::getDeviceInfoQueryFailureReason(const cl_int errorCode) {
	switch (errorCode) {
		case CL_INVALID_DEVICE:
			return "the passed device is not associated with the kernel";
		case CL_INVALID_VALUE:
			return "an invalid valid value was passed as an argument";
		case CL_OUT_OF_RESOURCES:
			return "cannot allocate resources required by the OpenCL implementation on the 'device'";
		case CL_OUT_OF_HOST_MEMORY:
			return "cannot allocate resources required by the OpenCL implementation on the 'host'";
		default:
			return "unknown error code: " + std::to_string(errorCode);
	}
}