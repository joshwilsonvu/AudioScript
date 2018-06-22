#ifndef AS_LOG_H
#define AS_LOG_H

#include <sstream>

// TODO: Create a true logging class, with a thread safe proxy,
// an internal buffer, and a way for the engine to extract its contents.

// This class shall replace std::cout for plugins, and all information
// streamed to this will be displayed in the AudioScript application.
// A proxy may be used.
// One stream chain (logger << x << y << z;) should be added atomically
// to the stream.
// The stream should be flushed to the display *at most* once per
// processed buffer, to reduce I/O to manageable levels, and not in the
// audio thread.

class QString;

namespace AS {

class Log {
public:
    class Proxy {
    public:
        Proxy(Proxy&& other);
        ~Proxy();

        template <typename T>
        Proxy& operator<<(const T& t);
        Proxy& operator<<(const QString s);

    private:
        friend class Log;
        Proxy(Log* parent);

        Log* parent;
        std::stringstream stream;
    };

    ~Log();

    // Returns a logging proxy that will write to the main
    // Log instance on destruction.
    Proxy log();

    // Trigger the flushing of data into the set sink
    void flush();

    // Set the function that will be called that is responsible
    // for draining the internal buffer with size() and read()
    template <typename Callback>
    void setSink(Callback&& callback);
    // Default to std::cout
    void setSink(std::ostream& out);

    // Returns the number of characters contained in the logger
    std::streamsize size();

    // Read std::min(count, size()) characters from the logger
    // into the given buffer, returning the number of characters read.
    // Discards characters if buffer is null.
    std::streamsize read(char* buffer, std::streamsize count
                         = std::numeric_limits<std::streamsize>::max());

    static Log& instance();

private:
    Log();
    void append(Proxy& proxy);

    std::mutex m_mutex;
    std::stringstream m_ss;
    std::function<void(Log&)> m_sink;
};

// free function users should use
// ex. AS::log() << "Parameter a = " << this->a << std::endl;
Log::Proxy log();

// template implementations
template <typename T>
Log::Proxy& Log::Proxy::operator<<(const T& t) {
    stream << t;
    return *this;
}

template<typename Callback>
void Log::setSink(Callback&& callback)
{
    m_sink = std::forward<Callback>(callback);
}



} // AS

#endif // AS_LOG_H
