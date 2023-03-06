#ifndef OPENCL_TOOLKIT_COMMAND_QUEUE_H
#define OPENCL_TOOLKIT_COMMAND_QUEUE_H

#include "portable_opencl_include.h"
#include "read_only_buffer.h"
#include "write_only_buffer.h"
#include "program.h"

/**
 * @brief Namespace of this toolkit.
 */
namespace OpenClToolkit {

	/**
	 * @brief Represents a Command Queue.
	 */
	class CommandQueue {

		private:
			/**
			 * The command queue.
			 */
			cl_command_queue self_;

		public:
			/**
			 * @brief The parametrized constructor.
			 * @param context a valid context.
			 * @param deviceId a valid device id.
			 */
			[[maybe_unused]] CommandQueue(const Context& context, cl_device_id deviceId);

			/**
			 *  @brief The destructor. Releases the current command queue.
			 */
			~CommandQueue();

			[[maybe_unused]] void enqueueCommandCopyBytesFromHostMemoryIntoDeviceMemory(
					void *sourceHostMemory,
					const ReadOnlyBuffer& destinationDeviceMemory,
					size_t numBytesToCopy
			);

			[[maybe_unused]] void enqueueCommandCopyBytesFromDeviceMemoryIntoHostMemory(
					const WriteOnlyBuffer& sourceDeviceMemory,
					void *destinationHostMemory,
					size_t numBytesToCopy
			);

			[[maybe_unused]] void enqueueCommandExecuteProgramOnDevice(const Program &program, size_t numThreads);
	};
}

#endif //OPENCL_TOOLKIT_COMMAND_QUEUE_H
