#include "write_only_buffer.h"

using namespace OpenClToolkit;

WriteOnlyBuffer::WriteOnlyBuffer(cl_context context, const size_t size) : BaseBuffer(context, size, CL_MEM_WRITE_ONLY) {

}