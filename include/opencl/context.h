#ifndef OPENCL_TOOLKIT_CONTEXT_H
#define OPENCL_TOOLKIT_CONTEXT_H

#include <string>

#include "portable_opencl_include.h"

/**
 * @brief Namespace of this toolkit.
 */
namespace OpenClToolkit {

	class Context {

		private:
			/**
			 * The context.
			 */
			cl_context self_;

		public:
			[[maybe_unused]] explicit Context(cl_device_id device);
			~Context();
			operator cl_context() const; // NOLINT(google-explicit-constructor)

		private:
			static std::string getFailureDescription(cl_int errorCode);
	};
}

#endif //OPENCL_TOOLKIT_CONTEXT_H
