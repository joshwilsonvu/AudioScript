#ifndef ENGINE_H
#define ENGINE_H

#include "plugin.h"

#include <QObject>
#include <map>

class RtAudio;
class AudioScript;
class AudioScriptBuffer;

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine();

    // same interface as AudioScript but no actual inheritance
    AudioScriptBuffer process(AudioScriptBuffer input);

    int channelCount() const;

signals:
    void pluginFound(Plugin&);

public slots:
    // make the engine aware of a new plugin
    // creates Plugin, adds to m_plugins, makes available
    void findPlugins();

    // TODO for starting out, I am going to make this start in mono duplex
    // mode, without any other options. Once the minimum viable product
    // is working, more options can be added and the interface can be smoothed.
    bool start();

    void stop();

private:


    RtAudio* m_rtAudio;
    int m_numChannels;
    std::map<QString, Plugin> m_plugins;
    std::vector<AudioScript*> m_scripts;
};

#endif // ENGINE_H
