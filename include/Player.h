#ifndef PLAYER_DEF
#define PLAYER_DEF
#include "VisibleGameObject.h"
#include "Animation.h"
/**
 * @class Player Class
 * @brief Updates and checks Collision of FireBoy/WaterGirl with various objects.
 *
 *      The player inherits from the VisibleGameObject class and takes control of the
 *      Fireboy and Watergirl's updates.
 */
class Player : public VisibleGameObject{
public:

    /**
     * @brief Constructor for player.
     * @param fName File name for loading the texture.
     * @param _u Key for jumping the player
     * @param _l Key for going left.
     * @param _r Key for going right
     *
     *      The constructor initialises the members like maximum vecloity attainable by player, max
     *      jump height and other parameters.
     *
     *      Sets the animation of the player as well.
     */
    Player(const std::string &fName, sf::Keyboard::Key _u, sf::Keyboard::Key _l, sf::Keyboard::Key _r);
    ~Player();

    /**
     * @brief Takes an event as input and updates the player according to it.
     * @param elapsedTime
     * @param _event
     * @param _object
     *     Checks for any events that are trigerred for the player , like going up or going left or right.
     *
     *     It checks for collisions also for every player with any object .
     *
     *     Animates the object by giving a Texture to it by the corresponding state of game.
     */
    void Update(float elapsedTime,sf::Event& _event,std::map<std::string, VisibleGameObject*>& _object);

    /**
     * @brief Takes an object and checks for collision of player with it.
     * @param other
     * @param e
     * @return True if collision occured false otherwise.
     *      e value checks the elasticity of collosion. If e = 0.0 then it pushes the player back and other object
     *      stays put. If e = 1 then object moves easily with a push.
     */
    bool checkCollision(VisibleGameObject* other, float e);
    /**
     * @brief Animation object which takes care of animation of object.
     */
    Animation animation;



private:
    /**
     * @brief Distance moved by barrier upon activation by a switch.
     */
    const float vBarrierMoveDist;
    /**
     * @brief Key for upward movement
     */
    sf::Keyboard::Key u;
    /**
     * @brief Key for left movement
     */
    sf::Keyboard::Key l;
    /**
     * @brief Key for right movement
     */
    sf::Keyboard::Key r;
    /**
     * @brief Checks if up key is pressed
     */
    bool isUpPressed;
    /**
     * @brief Checks if left key is pressed
     */
    bool isLPressed;
    /**
     * @brief Checks if right key is pressed
     */
    bool isRPressed;
    //! \brief is It falling down after ataining max distance it can jump? Not if it is actually jumping
    bool isJumping;
    //! \brief The distance it jumped before falling down.
    float dJump;
    //! \brief Velocity for Jump.
    float _upVel;
    //! \brief Velocity to move left/right.
    float _xVal;
    //! \brief Downward Velocity
    float _velocity;
    //! \brief Max velocity
    float _maxVelocity;
};
#endif // PLAYER_H
