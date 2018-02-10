#include "rtwrapper.h"
#include "RtAudio.h"

#include <QtDebug>

namespace {

int callback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void *data );

}

RtWrapper::RtWrapper(QObject *parent)
    : QObject(parent),
      m_rtAudio(nullptr)
{
}

RtWrapper::~RtWrapper()
{
    delete m_rtAudio;
    m_rtAudio = nullptr;
}

bool RtWrapper::start(RtWrapper::Mode mode)
{
    if (!m_rtAudio) {
        try {
            m_rtAudio = new RtAudio();
        } catch (const RtError& error) {
            qDebug() << error.getMessage();
            delete m_rtAudio;
            m_rtAudio = nullptr;
            return false;
        }
    }
}

void RtWrapper::stop()
{

}
