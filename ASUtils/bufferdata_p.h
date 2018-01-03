#ifndef BUFFERDATA_P_H
#define BUFFERDATA_P_H

#include "globals.h"
#include <QSharedData>
#include <vector>

namespace AS {

class BufferData : public QSharedData {
public:
    BufferData(size_t size);
    BufferData(const BufferData& other);
    BufferData(BufferData&& other);
    const BufferData& operator=(const BufferData&) = delete;
    const BufferData& operator=(BufferData&&) = delete;
    ~BufferData();

    std::vector<sample_t> vec;
};

}

#endif // BUFFERDATA_P_H
