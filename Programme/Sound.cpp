#include "Sound.h"

Sound::Sound()
  : m_numSimultaneousPlay(0)
  , m_repeatIntervalTime(0)
{
}

bool Sound::Load(std::string p_file)
{
    bool out = m_soundBuffer.loadFromFile(p_file);
    if (out)
        m_sound.setBuffer(m_soundBuffer);
    return out;
}

void Sound::SetRepeatIntervalTime(unsigned int p_milliseconds)
{
    m_repeatIntervalTime = p_milliseconds;
}

void Sound::SetNumSimultaneousPlay(unsigned int p_num)
{
    m_numSimultaneousPlay = p_num;
}

void Sound::SetVolume(float p_volume)
{
    if (p_volume > 100.0)
        p_volume = 100.0;
    else if (p_volume < 0.0)
        p_volume = 0.0;
    m_sound.setVolume(p_volume);
}

void Sound::Play()
{
    if (m_sound.getStatus() != sf::Sound::Playing)
        m_sound.play();
}