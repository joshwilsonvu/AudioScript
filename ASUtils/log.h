#ifndef AS_LOG_H
#define AS_LOG_H

#include <sstream>
#include <QObject>

// Users perform logging by calling AS::log() and then using the
// streaming operators, like so:
//     AS::log() << "Value of parameter g:" << g;
// Spaces are inserted between items automatically, and the chain is
// ended with a newline character.
// One stream chain (AS::log() << x << y << z;) is added atomically
// to the stream--that is, there will be no interleaving between two
// concurrent chains.
// When the stream is flushed to the display, it is not in the
// audio thread.

namespace AS {

class Log : public QObject {

    Q_OBJECT

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

    static Log* instance();

signals:
    void logged(QString);

private:
    Log();
    void append(Proxy& proxy); // add more text on Proxy destruction
};


// ex. AS::log() << "Parameter a = " << this->a << std::endl;
Log::Proxy log();

// template implementations
template <typename T>
Log::Proxy& Log::Proxy::operator<<(const T& t) {
    stream << t;
    return *this;
}

} // AS

#endif // AS_LOG_H
