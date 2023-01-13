#include "read_only_buffer.h"

using namespace OpenClToolkit;

ReadOnlyBuffer::ReadOnlyBuffer(cl_context context, const size_t size) : BaseBuffer(context, size, CL_MEM_READ_ONLY) {

}