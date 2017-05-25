
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
	std::string path;

    // **** Fonts **** //
	path = "resources/arial.ttf";
    if (!font.loadFromFile(path))
    {
        std::cout << "FONT ERROR" << std::endl;
    }

    // **** Effects **** //
	path = "resources/FromInternet/sounds/effects/magnum.ogg";
    soundMap["shot"] = Sound();
    if (!soundMap.at("shot").Load(path))
        std::cout << "Failed loading " << path << std::endl;

	// **** Musics **** //
	path = "resources/FromInternet/sounds/musics/music.wav";
    soundMap["music"] = Sound();
    if (!soundMap.at("music").Load(path))
		std::cout << "Failed loading " << path << std::endl;

    // **** Textures **** //
	path = "resources/FromInternet/visuals/backgrounds/IMG_8902.jpg";
    textureMap["background"] = sf::Texture();
    if (!textureMap["background"].loadFromFile(path))
    {
		std::cout << "Failed loading " << path << std::endl;
    }
	path = "resources/FromInternet/visuals/sprites/ship.png";
    textureMap["ship"] = sf::Texture();
    if (!textureMap["ship"].loadFromFile(path))
    {
		std::cout << "Failed loading " << path << std::endl;
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
