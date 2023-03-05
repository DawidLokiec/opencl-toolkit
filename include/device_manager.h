#ifndef OPENCL_TOOLKIT_DEVICE_MANAGER_H
#define OPENCL_TOOLKIT_DEVICE_MANAGER_H

#include "portable_opencl_include.h"
#include "command_queue.h"
#include <vector>
#include <string>

/**
 * @brief Namespace of this library.
 */
namespace OpenClToolkit {

	/**
	 * @brief Represents a global manager to deal with OpenCL-compatible devices.
	 * @details The manager is implemented as singleton and can be used to create OpenCL-contexts,
	 * command queues and/or retrieve information about the available devices on the current system.
	 */
	class DeviceManager {
		private:
			/**
			 * The number of available platforms on the current system.
			 */
			cl_uint numAvailablePlatforms_;

			/**
			 * A list with the IDs of the available platform on the current system.
			 */
			std::vector<cl_platform_id> platformIds_;

			/**
			 * A list with the IDs of the available devices on the current system.
			 */
			std::vector<std::vector<cl_device_id>> platformDevices_;

			/**
			 * The ID of the default OpenCL-compatible device on the current system, else -1.
			 */
			cl_device_id defaultDevice_;

			/**
			 * The IDs of OpenCL-compatible GPUs on the current system, if any.
			 */
			std::vector<cl_device_id> gpuIds_;

			/**
			 * The default constructor. Creates a new instance of the current class.
			 */
			DeviceManager();

		public:
			/**
			 * @brief The copy constructor.
			 */
			DeviceManager(DeviceManager const &) = delete;

			/**
			 * @brief The assigment operator.
			 */
			void operator=(DeviceManager const &) = delete;

			/**
			 * @brief Returns the singleton instance of this class.
			 * @return the singleton instance of this class.
			 */
			[[maybe_unused]] static DeviceManager &getInstance();

			/**
			 * @brief Returns true if a default OpenCL-compatible device is available on the current system.
			 * @return true if a default OpenCL-compatible device is available on the current system.
			 */
			[[maybe_unused]] [[nodiscard]] bool isDefaultDeviceAvailable() const;

			/**
			 * @brief Returns the id of the default OpenCL-compatible device or -1 if not such device is available on
			 * the current system.
			 * @return the id of the default OpenCL-compatible device or -1 if not such device is available.
			 */
			[[maybe_unused]] [[nodiscard]] cl_device_id getDefaultOpenClDevice() const;

			/**
			 * @brief Returns true if a OpenCL-compatible GPU is available on the current system.
			 * @return true if a OpenCL-compatible GPU is available on the current system.
			 */
			[[maybe_unused]] [[nodiscard]] bool isOpenClCompatibleGpuAvailable() const;

			/**
			 * @brief Returns a list all OpenCL-compatible GPUs available on the current system.
			 * @return a list all OpenCL-compatible GPUs available on the current system.
			 */
			[[maybe_unused]] [[nodiscard]] std::vector<cl_device_id> getOpenClCompatibleGpus() const;

			/**
			 * @brief Converts the given device type as a magic number into a meaningful string.
			 * @param type the device type to be converted into a meaningful string.
			 * @return the given device type as a magic number into a meaningful string.
			 */
			[[nodiscard]] static std::string deviceTypeToString(cl_device_type type);

			/**
			 * @brief Constructs debug information about the available OpenCL-compatible devices on the current system.
			 * @return debug information about the available OpenCL-compatible devices on the current system.
			 */
			[[maybe_unused]] [[nodiscard]] std::string
			constructDebugInfoAboutAvailableOpenClDevicesOnCurrentSystem() const;
	};
}
#endif //OPENCL_TOOLKIT_DEVICE_MANAGER_H