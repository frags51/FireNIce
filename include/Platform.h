

#ifndef FIRENICE_PLATFORM_H
    #define FIRENICE_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "VisibleGameObject.h"
#include "Animation.h"
/*!
 * @class Platform
 * @brief This class stores any objects that are not "players" for now.
 * New classes for each object can be added later.
 * Objects are differentiated by their "texture filename"
 */
class Platform : public VisibleGameObject {
public:
    /*!
     * @brief Constructor
     * @param fName The texture filename.
     * @param size The size vector.
     * @param position The position vector.
     */
    Platform(const std::string &fName , sf::Vector2f size, sf::Vector2f position);
    /*!
     * @brief The destructor.
     */
    ~Platform();

    /*!
     * @brief Draw this object on the window.
     * @param window The window to draw this object on.
     */
    void Draw(sf::RenderWindow& window);
    /*!
     * Check collision of this object with other objects. Currently does nothing.
     * @param other The object to check collision with.
     * @param e "Elasticity"
     * @return true if collided, false if not.
     */
    bool checkCollision(VisibleGameObject* other, float e);
    /*!
     * @brief Update this object according to the new event recorded.
     * @param elapsedTime Time since last update.
     * @param _event The event that triggered this update.
     * @param _object A container containing other objects that might influence this object's position etc.
     */
    void Update(float elapsedTime,sf::Event& _event,std::map<std::string, VisibleGameObject*>& _object);
    Animation animation;


private:
    const float vBarrierMoveDist;


};


#endif //FIRENICE_PLATFORM_H
