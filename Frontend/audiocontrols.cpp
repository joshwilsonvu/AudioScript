
#include "audiocontrols.h"

#include <QGroupBox>
#include <QToolButton>
#include <QGridLayout>

AudioControls::AudioControls(QWidget* parent, Qt::WindowFlags flags)
    : SideWidgetBase(parent, flags),
      m_play_b(new QToolButton(this)),
      m_pause_b(new QToolButton(this)),
      m_groupBox(new QGroupBox(tr("Audio Controls")))
{
    m_play_b->setText("Play");
    m_pause_b->setText("Pause");
    // Create layout with contents
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_play_b, 0, 0);
    layout->setColumnStretch(0, 1);
    layout->addWidget(m_pause_b, 0, 1);
    layout->setColumnStretch(1, 1);

    // Add to titled GroupBox
    m_groupBox->setLayout(layout);

    // Lay out GroupBox
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_groupBox);
}

AudioControls::~AudioControls()
{

}
