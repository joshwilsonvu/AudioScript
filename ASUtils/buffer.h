#ifndef BUFFER_H
#define BUFFER_H

#include "globals.h"
#include <QSharedDataPointer>

#include "bufferdata_p.h"

namespace AS {

class ASUTILS_EXPORT Buffer
{
public:

    Buffer(BufferSize size);
    Buffer(const Buffer& other);
    Buffer(Buffer&& other);
    const Buffer& operator=(const Buffer& other);
    const Buffer& operator=(Buffer&& other);

    void swap(Buffer& other);

    void reset();
    void fill(sample_t value);

    sample_t* begin();
    const sample_t* begin() const;
    sample_t* end();
    const sample_t* end() const;

    BufferSize size() const;

private:
    // Implicit sharing
    QSharedDataPointer<BufferData> d;
};

}

#endif // BUFFER_H
