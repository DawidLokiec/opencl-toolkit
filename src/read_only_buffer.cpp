#include "read_only_buffer.h"

using namespace OpenClToolkit;

[[maybe_unused]] ReadOnlyBuffer::ReadOnlyBuffer(const Context &context, const size_t size) :
		BaseBuffer(context, size, CL_MEM_READ_ONLY) {

}
