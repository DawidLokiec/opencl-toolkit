#ifndef OPENCL_TOOLKIT_ABSTRACT_BUFFER_H
#define OPENCL_TOOLKIT_ABSTRACT_BUFFER_H

#include "portable_opencl_include.h"
#include <string>

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
			BaseBuffer(cl_context context, size_t size, cl_mem_flags flags);

		public:
			virtual ~BaseBuffer();
			operator cl_mem() const; // NOLINT(google-explicit-constructor)

		private:
			static std::string getFailureDescription(cl_int errorCode);
	};
}

#endif //OPENCL_TOOLKIT_ABSTRACT_BUFFER_H
