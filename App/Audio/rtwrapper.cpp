#include "rtwrapper.h"
#include "RtAudio.h"

RtWrapper::RtWrapper(QObject *parent)
    : QObject(parent),
      m_rtAudio(new RtAudio())
{
    try {

    } catch (const RtError& error) {
        delete m_rtAudio;
        m_rtAudio = nullptr;
    }
}

RtWrapper::~RtWrapper()
{
    delete m_rtAudio;
    m_rtAudio = nullptr;
}
