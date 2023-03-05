#ifndef OPENCL_TOOLKIT_PROGRAM_H
#define OPENCL_TOOLKIT_PROGRAM_H

#include "portable_opencl_include.h"
#include <string>
#include "read_only_buffer.h"
#include "write_only_buffer.h"

/**
 * @brief Namespace of this toolkit.
 */
namespace OpenClToolkit {

	/**
	 * @brief Represents a program written in OpenCL that consists of one kernel.
	 */
	class Program {
		private:
			/**
			 * The program object.
			 */
			cl_program program_;

			/**
			 * The associated kernel of the current program.
			 */
			cl_kernel kernel_;

			/**
			 * The name of the function declared with the <code>__kernel</code> qualifier.
			 */
			std::string kernelName_;

			/**
			 * The target device of the current program.
			 */
			cl_device_id device_;

		public:
			/**
			 * @brief The parametrized constructor. Creates an OpenCL-program using the passed parameters.
			 * @param kernelSourceCode the kernel source code as a <strong>null-terminated C-style</strong> string.
			 * @param kernelName the name of the function declared with the <code>__kernel</code> qualifier inside the
			 *                   passed source code.
			 * @param context a valid OpenCL-context.
			 * @param device the target device of the current program.
			 */
			[[maybe_unused]] Program(
					const char *kernelSourceCode,
					const std::string &kernelName,
					const Context& context,
					cl_device_id device
			);

			/**
			 * @brief The destructor.
			 */
			~Program();

			/**
			 * @brief Returns the kernel of the current program.
			 * @return the kernel of the current
			 */
			[[maybe_unused]] [[nodiscard]] cl_kernel getKernel() const;

			/**
			 * @brief Sets the argument value for a specific argument of the current associated kernel.
			 * @param argIndex the argument index. 0 for the leftmost argument to n - 1.
			 * @param argSize  specifies the size of the argument value.
			 * @param argValue the pointer to data that should be used as the argument value for argument specified by arg_index.
			 */
			[[maybe_unused]] void setKernelArg(cl_uint argIndex, size_t argSize, const void *argValue);

			/**
			 * @brief Sets the argument value for a specific argument of the current associated kernel.
			 * @param argIndex the argument index. 0 for the leftmost argument to n - 1.
			 * @param argSize  specifies the size of the argument value.
			 * @param buffer the buffer that should be used as the argument value for argument specified by arg_index.
			 */
			[[maybe_unused]] void setKernelArg(cl_uint argIndex, size_t argSize, cl_mem buffer);

			/**
			 * @brief Returns the max work group size in bytes for the kernel of the current program.
			 * @return the max work group size in bytes for the kernel of the current program.
			 */
			[[nodiscard]] size_t getMaxWorkGroupSizeInBytes() const;

			/**
			 * @brief Returns the global memory size in bytes of the target device.
			 * @return the global memory size in bytes of the target device.
			 */
			[[nodiscard]] cl_ulong getDeviceGlobalMemorySizeInBytes() const;

			/**
			 * @brief Returns the max global variable size in bytes on the target device.
			 * @return the max global variable size in bytes on the target device.
			 */
			[[nodiscard]] size_t getDeviceMaxGlobalVariableSizeInBytes() const;

			/**
			 * @brief Returns the local memory size in bytes of the target device.
			 * @return the local memory size in bytes of the target device.
			 */
			[[nodiscard]] size_t getDeviceLocalMemorySizeInBytes() const;

			/**
			 * @brief Adds the current program to the passed command queue in order to be executed.
			 * @param commandQueue the command queue to take the current program and execute it.
			 * @param numThreads the number of threads used to execute the kernel of the current program.
			 */
			[[maybe_unused]] void execute(cl_command_queue commandQueue, size_t numThreads) const;

			/**
			 * @brief Prints to stdout the information about the memory of the current target device.
			 * @param useStderr an optional flag. If true, the info is printed to stderr, else to stdout.
			 */
			[[maybe_unused]] void printDeviceMemoryInfo(bool useStderr = false) const;

		private:
			/**
			 * @brief Converts the passed error code into a meaningful failure message why the kernel creation failed.
			 * @param errorCode the error code to be converted into a meaningful failure message.
			 * @return a meaningful failure message why the kernel creation failed.
			 */
			[[nodiscard]] std::string getKernelCreationFailureReason(cl_int errorCode) const;

			/**
			 * @brief Converts the passed error code into a meaningful failure message why the program creation failed.
			 * @param errorCode the error code to be converted into a meaningful failure message.
			 * @return a meaningful failure message why the program creation failed.
			 */
			static std::string getProgramCreationFailureReason(cl_int errorCode);

			/**
			 * @brief Converts the passed error code into a meaningful failure message why the program build failed.
			 * @param errorCode the error code to be converted into a meaningful failure message.
			 * @return a meaningful failure message why the program build failed.
			 */
			static std::string getProgramBuildFailureReason(cl_int errorCode);

			/**
			 * @brief Converts the passed error code into a meaningful failure message why the kernel work group info
			 * query failed.
			 * @param errorCode the error code to be converted into a meaningful failure message.
			 * @return a meaningful failure message why the kernel work group info query failed.
			 */
			static std::string getKernelWorkGroupInfoQueryFailureReason(cl_int errorCode);

			/**
			 * @brief Converts the passed error code into a meaningful failure message why the device info query failed.
			 * @param errorCode the error code to be converted into a meaningful failure message.
			 * @return a meaningful failure message why the device info query failed.
			 */
			static std::string getDeviceInfoQueryFailureReason(cl_int errorCode);
	};
}

#endif //OPENCL_TOOLKIT_PROGRAM_H
