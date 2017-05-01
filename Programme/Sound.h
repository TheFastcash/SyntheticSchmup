#include <string>

#include <SFML/Audio.hpp>

class Sound
{
public:
    Sound();
    bool Load(std::string file);
    void SetRepeatIntervalTime(unsigned int milliseconds);
    void SetNumSimultaneousPlay(unsigned int num);
    void SetVolume(float volume);
    void Play();

private:
    unsigned int m_repeatIntervalTime;
    unsigned int m_numSimultaneousPlay;
    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;
};