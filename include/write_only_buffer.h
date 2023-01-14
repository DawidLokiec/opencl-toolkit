#ifndef OPENCL_TOOLKIT_WRITE_ONLY_BUFFER_H
#define OPENCL_TOOLKIT_WRITE_ONLY_BUFFER_H

#include "base_buffer.h"

namespace OpenClToolkit {

	/**
 	 * @brief Represents a write-only buffer.
 	 */
	class WriteOnlyBuffer : public BaseBuffer {
		public:
			/**
			 * @brief The parametrized constructor. Creates an instance of this class by the passed parameters.
			 * @param context a valid OpenCL-context.
			 * @param size the size of the buffer in bytes.
			 */
			[[maybe_unused]] WriteOnlyBuffer(const Context& context, size_t size);
	};
}

#endif //OPENCL_TOOLKIT_WRITE_ONLY_BUFFER_H
