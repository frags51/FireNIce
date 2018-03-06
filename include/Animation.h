#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>
class Animation{

public:

    Animation();
    ~Animation();
    /**
     * @brief Takes the row from the compound texture.
     * @param row
     * @param deltaTime
     * @param faceRight
     *      Row is taken as input from the source image and sets animation by running through the row.
     *      DeltaTime counts for the animation switch time.
     *      FaceRight is used for checking the direction of movement of player for loading texture.
     */
    void update(int row,float deltaTime,bool faceRight);
    /**
     * @brief Creates the animation
     * @param texture
     * @param imageCount
     * @param switchTime
     *      Takes the imagecount , switchtime and texture as parameters and updates the correspponding private
     *      member variables.
     */
    void create(sf::Texture* texture,sf::Vector2u imageCount,float switchTime);

public:
    /**
     * @brief Accounts for cropping 1 image out of the entire compound image.
     */
    sf::IntRect uvRect;

private:
    /**
     * @brief Vector which gives a count of the total images in compund image file.
     */
    sf::Vector2u imageCount;
    /**
     * @brief The image point at which the animation row is running at the moment.
     */
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

};

#endif