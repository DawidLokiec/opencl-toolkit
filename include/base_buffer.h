#ifndef OPENCL_TOOLKIT_ABSTRACT_BUFFER_H
#define OPENCL_TOOLKIT_ABSTRACT_BUFFER_H

#include "portable_opencl_include.h"
#include "context.h"
#include <string>

/**
 * @brief Namespace of this toolkit.
 */
namespace OpenClToolkit {

	/**
	 * @brief Represents base class for buffers.
	 */
	class BaseBuffer {
		private:
			/**
			 * The buffer.
			 */
			cl_mem self_;

		protected:
			BaseBuffer(const Context& context, size_t size, cl_mem_flags flags);

		public:
			virtual ~BaseBuffer();
			operator cl_mem() const; // NOLINT(google-explicit-constructor)

		private:
			static std::string getFailureDescription(cl_int errorCode);
	};
}

#endif //OPENCL_TOOLKIT_ABSTRACT_BUFFER_H
