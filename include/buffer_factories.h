#ifndef OPENCL_TOOLKIT_OPENCL_BUFFER_FACTORIES_H
#define OPENCL_TOOLKIT_OPENCL_BUFFER_FACTORIES_H

#include "portable_opencl_include.h"

namespace OpenClToolkit {

	/**
 	 * @brief Creates a <strong>read only</strong> OpenCL-Buffer.
 	 * @param context a valid OpenCL-context.
 	 * @param size the size of the buffer in bytes.
 	 * @return a <strong>read only</strong> OpenCL-Buffer.
 	 */
	[[maybe_unused]] cl_mem createReadOnlyBuffer(cl_context context, size_t size);

	/**
 	 * @brief Creates a <strong>write only</strong> OpenCL-Buffer.
 	 * @param context a valid OpenCL-context.
 	 * @param size the size of the buffer in bytes.
 	 * @return a <strong>write only</strong> OpenCL-Buffer.
 	 */
	[[maybe_unused]] cl_mem createWriteOnlyBuffer(cl_context context, size_t size);
}

#endif //OPENCL_TOOLKIT_OPENCL_BUFFER_FACTORIES_H
