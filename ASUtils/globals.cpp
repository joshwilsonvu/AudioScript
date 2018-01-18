#include "globals.h"

size_t AS::to_size_t(AS::BufferSize size)
{
    switch(size) {
    case BufferSize::_32:
        return 32ul;
    case BufferSize::_64:
        return 64ul;
    case BufferSize::_128:
        return 128ul;
    case BufferSize::_256:
        return 256ul;
    case BufferSize::_512:
        return 512ul;
    case BufferSize::_1024:
        return 1024ul;
    }
}
