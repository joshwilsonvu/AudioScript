#include "log.h"

#include <mutex>
#include <iostream>
#include <QString>

namespace AS {

// free function, alias for Log::instance().log()
Log::Proxy log()
{
    return Log::instance().log();
}

// Log implementation
Log::Log()
{
    setSink(std::cout);
}

Log::~Log()
{}

Log::Proxy Log::log()
{
    return Proxy(this);
}

void Log::setSink(std::ostream& out)
{
    m_sink = [&out] (Log& log) {
        out << log.m_ss.rdbuf();
    };
}

std::streamsize Log::read(char* buffer, std::streamsize count)
{
    count = std::min(count, size());
    if (buffer) {
        m_ss.read(buffer, count);
    } else {
        m_ss.ignore(count);
    }
    return count;
}

std::streamsize Log::size()
{
    m_ss.seekg(0, std::ios::end);
    auto size = m_ss.tellg();
    m_ss.seekg(0, std::ios::beg);
    return size;
}

Log& Log::instance()
{
    static Log gLog;
    return gLog;
}

void Log::append(Proxy& proxy)
{
    // efficiently copy the stream's contents into ss
    std::unique_lock<std::mutex> locker(m_mutex);
    m_ss << proxy.stream.rdbuf();
}

void Log::flush()
{
    // prevent m_ss from modification while flushing
    std::unique_lock<std::mutex> locker(m_mutex);
    try {
        // call the callback to read data from *this
        m_sink(*this);
    } catch (...) {}
    m_ss.str(std::string());
    m_ss.clear();
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
