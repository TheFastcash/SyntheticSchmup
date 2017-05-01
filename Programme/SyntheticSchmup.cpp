
#include "SyntheticSchmup.h"

SyntheticSchmup SyntheticSchmup::m_instance = SyntheticSchmup();

void SyntheticSchmup::Initialize(int p_width, int p_height, double p_fov)
{
    windowWidth = p_width;
    windowHeight = p_height;
    windowRatio = (double)windowHeight / (double)windowWidth;
    windowFov = p_fov;

    // **************************** //
    // **** Load all resources **** //
    // **************************** //

    // **** Fonts **** //
    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "FONT ERROR" << std::endl;
    }

    // **** Sounds **** //
    soundMap["shot"] = Sound();
    if (!soundMap.at("shot").Load("resources/sound/shot.wav"))
        std::cout << "Failed loading resources/sound/shot.wav" << std::endl;
    soundMap["music"] = Sound();
    if (!soundMap.at("music").Load("resources/sound/music.wav"))
        std::cout << "Failed loading resources/sound/music.wav" << std::endl;

    // **** Textures **** //
    textureMap["background"] = sf::Texture();
    if (!textureMap["background"].loadFromFile("resources/menuBackground.jpg"))
    {
        std::cout << "Cannot load \"resources/menuBackground.jpg\"" << std::endl;
    }
    textureMap["ship"] = sf::Texture();
    if (!textureMap["ship"].loadFromFile("resources/ship.png"))
    {
        std::cout << "Cannot load \"resources/ship.png\"" << std::endl;
    }
}

Vector2d SyntheticSchmup::GetXYLimits(double depth)
{
    double x = tan(windowFov / 2 * M_PI / 180) * -depth;    // Calculate the maximum X axis value see-able on the windows
    double y = x * windowRatio;                             // Idem for Y axis
                                                            // These 2 values are oppositable as 0 is the center of the screen
    return Vector2d(x, y);
}

SyntheticSchmup * SyntheticSchmup::Get()
{
    return &m_instance;
};

void SyntheticSchmup::ExitWithMessage(int p_error, std::string p_message)
{
    std::cout << p_message << std::endl;
    exit(p_error);
}
