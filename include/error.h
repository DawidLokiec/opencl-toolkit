#ifndef OPENCL_TOOLKIT_ERROR_H
#define OPENCL_TOOLKIT_ERROR_H

#include <string>
#include "portable_opencl_include.h"

namespace OpenClToolkit {

	/**
	 * @brief Converts the passed error code into a description of the possible error cause.
	 * @param errorCode the error code to be converted into a meaningful error description.
	 * @return A description of the meaning of the error code passed.
	 */
	std::string toErrorDescription(cl_int errorCode);
}

#endif //OPENCL_TOOLKIT_ERROR_H
