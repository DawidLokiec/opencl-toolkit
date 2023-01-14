#include "write_only_buffer.h"

using namespace OpenClToolkit;

[[maybe_unused]] WriteOnlyBuffer::WriteOnlyBuffer(const Context &context, const size_t size) :
		BaseBuffer(context, size, CL_MEM_WRITE_ONLY) {

}
