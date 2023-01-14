#include "device_manager.h"
#include <stdexcept>
#include <iostream>

using namespace OpenClToolkit;

[[maybe_unused]]DeviceManager &DeviceManager::getInstance() {
	static DeviceManager instance;
	return instance;
}

DeviceManager::DeviceManager() : numAvailablePlatforms_(0), defaultDevice_(nullptr) {
	cl_int status;
	// check the available platforms (e.g. Intel, Nvidia, AMD etc.) on the current host
	status = clGetPlatformIDs(0, nullptr, &numAvailablePlatforms_);
	if (status) {
		// let it crash
		throw std::runtime_error("Cannot get the number of available platforms");
	}

	platformIds_.resize(numAvailablePlatforms_);
	status = clGetPlatformIDs(numAvailablePlatforms_, &platformIds_[0], nullptr);
	if (status) {
		// let it crash
		throw std::runtime_error("Cannot get the list of platforms");
	}

	// check the available devices for each platform
	platformDevices_.resize(numAvailablePlatforms_);
	for (size_t i = 0; i < numAvailablePlatforms_; ++i) {
		cl_uint numDevices;
		clGetDeviceIDs(
				platformIds_[i],
				CL_DEVICE_TYPE_ALL,
				0,
				nullptr,
				&numDevices
		);
		platformDevices_[i].resize(numDevices);
		clGetDeviceIDs(
				platformIds_[i],
				CL_DEVICE_TYPE_ALL,
				numDevices,
				&platformDevices_[i][0],
				nullptr
		);
	}

	// check for default device
	status = CL_DEVICE_NOT_FOUND;
	for (size_t i = 0; i < platformDevices_.size() && (CL_DEVICE_NOT_FOUND == status); ++i) {
		cl_uint num_default_device = 0;
		status = clGetDeviceIDs(
				platformIds_[i],
				CL_DEVICE_TYPE_DEFAULT,
				0,
				nullptr,
				&num_default_device
		);
		if ((num_default_device > 0) && (CL_DEVICE_NOT_FOUND != status)) {
			clGetDeviceIDs(
					platformIds_[i],
					CL_DEVICE_TYPE_DEFAULT,
					1,
					&defaultDevice_,
					nullptr
			);
		}
	}

	// check the available GPUs
	for (size_t i = 0; i < platformIds_.size(); ++i) {
		cl_uint numGpus = 0;
		status = clGetDeviceIDs(
				platformIds_[i],
				CL_DEVICE_TYPE_GPU,
				0,
				nullptr,
				&numGpus
		);
		if (numGpus > 0 && (CL_DEVICE_NOT_FOUND != status)) {
			gpuIds_.resize(gpuIds_.size() + numGpus);
			clGetDeviceIDs(
					platformIds_[i],
					CL_DEVICE_TYPE_GPU,
					numGpus,
					&gpuIds_[i],
					nullptr
			);
		}
	}
}

[[maybe_unused]] bool DeviceManager::isDefaultDeviceAvailable() const {
	return !defaultDevice_;
}

[[maybe_unused]] cl_device_id DeviceManager::getDefaultOpenClDevice() const {
	return defaultDevice_;
}

[[maybe_unused]] bool DeviceManager::isOpenClCompatibleGpuAvailable() const {
	return !gpuIds_.empty();
}

[[maybe_unused]] std::vector<cl_device_id> DeviceManager::getOpenClCompatibleGpus() const {
	return gpuIds_;
}

std::string DeviceManager::deviceTypeToString(const cl_device_type type) {
	switch (type) {
		case CL_DEVICE_TYPE_CPU:
			return "CPU";
		case CL_DEVICE_TYPE_GPU:
			return "GPU";
		case CL_DEVICE_TYPE_ACCELERATOR:
			return "Accelerator";
		default:
			return "unknown";
	}
}

[[maybe_unused]] void DeviceManager::stdoutInfo() const {
	std::cout << "Number of platforms available: " << numAvailablePlatforms_ << std::endl;
	for (size_t i = 0; i < numAvailablePlatforms_; ++i) {
		// Get the platform name
		char platformName[256];
		const cl_int status = clGetPlatformInfo(
				platformIds_[i],
				CL_PLATFORM_NAME,
				sizeof(char) * 256,
				platformName,
				nullptr
		);
		if (status) {
			std::cerr << "Cannot get the name of the platform #" << (i + 1) << std::endl;
		} else {
			std::cout << "Platform #" << (i + 1) << " name: " << platformName << std::endl;
		}
		// Print the platform's devices
		std::cout << "  Available devices for this platform: " << platformDevices_[i].size() << std::endl;
		for (size_t j = 0; j < platformDevices_[i].size(); j++) {
			char deviceName[256];
			clGetDeviceInfo(platformDevices_[i][j], CL_DEVICE_NAME, sizeof(char) * 256, deviceName, nullptr);
			std::cout << "    Device type#" << (j + 1) << " name: " << deviceName << std::endl;
			cl_device_type deviceType;
			clGetDeviceInfo(platformDevices_[i][j], CL_DEVICE_TYPE, sizeof(char) * 256, &deviceType, nullptr);
			std::cout << "    Device type#" << (j + 1) << " type: " << deviceTypeToString(deviceType) << std::endl;
		}
	}
}
