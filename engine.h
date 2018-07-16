#ifndef AS_ENGINE_H
#define AS_ENGINE_H

#include "globals.h"
#include <memory>
#include <QObject>

/**
 * The AudioScript Engine class should expose its own API and be fully
 * self-contained, much like RtAudio. The API will enable all audio-related
 * functionality, such as spawning scripts, recording and playing audio,
 * converting to AudioScriptBuffers, and running the processing chain in a
 * separate, high-priority or realtime thread.
 *
 * Usage will most likely be building and linking to a library and including
 * the engine.h header file.
 */

namespace AS {

class Script;
class Buffer;

class PluginLibrary;
class Plugin;
class ProcessGraph;
class Processor;

class Engine : public QObject
{
    Q_OBJECT

public:
    Engine(QObject* parent = nullptr);
    ~Engine() override;


    void probeAudio();

    int numChannels() const;

public slots:
    void start();

    void stop();

    // loads the plugin at the specified file and returns its name, "" if failed
    QString load(QString file);

signals:
    void pluginLoaded(QString);

    void started();

    void stopped();

private:    


    void initializeAudio();

    std::unique_ptr<PluginLibrary> m_pluginLibrary;
    std::unique_ptr<ProcessGraph> m_processGraph;
    std::unique_ptr<Processor> m_processor;

};

} // AS

#endif // AS_ENGINE_H
