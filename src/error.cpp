#include "error.h"

std::string OpenClToolkit::toErrorDescription(const cl_int errorCode) {
	switch (errorCode) {
		case CL_INVALID_EVENT_WAIT_LIST: // -57
			return "CL_INVALID_EVENT_WAIT_LIST: event_wait_list is NULL and num_events_in_wait_list greater than 0 or "
				   "event_wait_list is not NULL and num_events_in_wait_list is 0 or "
				   "event objects in event_wait_list are not valid events.";
		case CL_INVALID_GLOBAL_OFFSET: // -56
			return "CL_INVALID_GLOBAL_OFFSET";
		case CL_INVALID_WORK_ITEM_SIZE: // -55
			return "CL_INVALID_WORK_ITEM_SIZE";
		case CL_INVALID_WORK_GROUP_SIZE: // -54
			return "CL_INVALID_WORK_GROUP_SIZE: The specified work group size does not fit the allowed max size";
		case CL_INVALID_WORK_DIMENSION: // -53
			return "CL_INVALID_WORK_DIMENSION: The work_dim is not a valid value (i.e. a value between 1 and 3)";
		case CL_INVALID_KERNEL_ARGS: // -52
			return "CL_INVALID_KERNEL_ARGS: The kernel argument values have not been specified";
		case CL_INVALID_KERNEL: // -48
			return "CL_INVALID_KERNEL: Kernel is not a valid kernel object";
		case CL_INVALID_PROGRAM_EXECUTABLE: // -45
			return "CL_INVALID_PROGRAM_EXECUTABLE: "
				   "No successfully built program executable available for device associated with command_queue";
		case CL_INVALID_MEM_OBJECT: // -38
			return "CL_INVALID_MEM_OBJECT: The passed buffer is not a valid buffer object.";
		case CL_INVALID_COMMAND_QUEUE: // -36
			return "CL_INVALID_COMMAND_QUEUE: The passed command queue is invalid.";
		case CL_INVALID_QUEUE_PROPERTIES: // -35
			return "CL_INVALID_QUEUE_PROPERTIES: The specified values in properties are not supported by the device.";
		case CL_INVALID_CONTEXT: // -34
			return "CL_INVALID_CONTEXT: An invalid context was passed.";
		case CL_INVALID_DEVICE: // -33
			return "CL_INVALID_DEVICE: The device is not valid or is not associated with the context";
		case CL_INVALID_VALUE: // -30
			return "CL_INVALID_VALUE: The specified values in properties are not valid.";
		case CL_OUT_OF_HOST_MEMORY: // -6
			return "CL_OUT_OF_HOST_MEMORY: Failed to allocate resources required by the OpenCL implementation on the host.";
		case CL_OUT_OF_RESOURCES: // -5
			return "CL_OUT_OF_RESOURCES: Failed to allocate resources required by the OpenCL implementation on the device.";
		case CL_MEM_OBJECT_ALLOCATION_FAILURE: // -4
			return "CL_MEM_OBJECT_ALLOCATION_FAILURE: Failed to allocate memory for data store associated with buffer.";
		case CL_SUCCESS: // 0
			return "CL_SUCCESS: No errors.";
		default:
			return "Unknown error code: " + std::to_string(errorCode);
	}
}