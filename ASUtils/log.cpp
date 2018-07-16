#include "log.h"

#include <iostream>
#include <QString>

namespace AS {

// free function, alias for Log::instance().log()
Log::Proxy log()
{
    return Log::instance()->log();
}

// Log implementation
Log::Log()
{}

Log::~Log()
{}

Log::Proxy Log::log()
{
    return Proxy(this);
}

Log* Log::instance()
{
    static Log gLog;
    return &gLog;
}

void Log::append(Proxy& proxy)
{
    auto stream = std::move(proxy.stream);

    // determine size of string buffer
    stream.seekg(0, std::ios::end);
    auto size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    // create QByteArray buffer
    auto buffer = QByteArray(size, '\0');

    if (size) {
        // fill the QByteArray
        stream.read(buffer.data(), size);

        // emit the signal
        auto str = QString::fromLocal8Bit(buffer);
        emit logged(std::move(str));
    }
}

// Log::Proxy implementation
Log::Proxy::Proxy(Log* parent)
    : parent(parent)
{}

Log::Proxy::Proxy(Log::Proxy&& other)
    : parent(other.parent),
      stream(std::move(other.stream))
{
    other.parent = nullptr;
}

Log::Proxy::~Proxy()
{
    if (parent) {
        // safely append contents to parent log
        parent->append(*this);
    }
}

Log::Proxy& Log::Proxy::operator<<(const QString s)
{
    stream << s.toLocal8Bit().constData();
    return *this;
}

} // AS
