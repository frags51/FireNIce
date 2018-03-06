#ifndef GAME_OBJECT
#define GAME_OBJECT
#include <iostream>
#include <SFML/Graphics.hpp>

/*!
 * @class VisibleGameObject
 * @brief This class is used to define an object that is to be drawn on the  screen.
 *
 * All the Game's Drawable objects must inherit from this class.
 * Currently, most of the type of object checking is done from the object's texture filename.
 */
class VisibleGameObject{
public:
    /*!
     * @brief The Constructor.
     *
     * Initializes the variabls isLoaded and _stateOfObj.
     */
    VisibleGameObject();
    ~VisibleGameObject();

    /*!
     * @brief Load the texture corresponding to the filename.
     * @param filename The location of this object's texture file.
     * @param x The x size (width) of the this object
     * @param y The y size (height) of this object
     */
    virtual void Load(std::string filename,float x,float y);
    /*!
     * @brief Draw this object on the window
     * @param window The window to draw this object on.
     */
    virtual void Draw(sf::RenderWindow & window);

    /*!
     * @brief Set's this object's position, relative to the origin.
     * @param x X-Coodinate of the position.
     * @param y Y-Coodinate of the position.
     */
    virtual void SetPosition(float x, float y);

    /*!
     * @brief Updates the objects position and texture of the object.
     * @param elapsedTime The time elapsed since last update (sort of simulates frame rate)
     * @param event The event that occured.
     * @param _object A map of all other objects to be drawn.
     *
     * Checks the _object map to update this object according to the position of other objects in game.
     * An example is checking for collisions.
     */
    virtual void Update(float elapsedTime,sf::Event& event,std::map<std::string, VisibleGameObject*>& _object);

    /*!
     * @brief Get the position of this object.
     * @return A float vector representing this object's position.
     */
    virtual sf::Vector2f GetPosition() const;
    /*!
     * @brief Check the value of _isLoaded
     * @return true if the texture file has been loaded properly, false otherwise
     */
    virtual bool IsLoaded() const;
    /*!
     * @brief The size vector of the object, divided by 2.
     * @return A vector: (size.x/2, size.y/2)
     */
    virtual sf::Vector2f GetHalfSize() { return _player.getSize()/2.0f;}
    /*!
     * Moves the player by the corresponding offsets.
     * @param dx The displacement in X direction.
     * @param dy The displacement in Y direction.
     */
    virtual void move(float dx,float dy){ _player.move(dx,dy); }
    /*!
     * @brief A rectangle shape that is drawable and holds the objects information.
     */
    sf::RectangleShape _player;
    /*!
     * @brief Get the file-name of the texture for this object.
     * @return A string containing the filepath (relative to the source directory)
     */
    virtual std::string getFileName() const;
    /*!
     * @brief A variable storing the texture's filepath.
     */
    std::string _filename;

    /*!
     * @enum VisibleGameObject::stateOfObj
     * @brief The various states the GameObject can be in.
     *
     * DEF: The default state.
     * VBSPRESSED_F: A switch has been pressed by FireBoy
     * VBSPRESSED_W: A switch has been pressed by WaterGirl
     * VBMOVED: A barrier has been moved due to the corresponding switch being pressed.
     * GEMCONSUMED: This "gem" has been consumed.
     */
    enum stateOfObj {DEF, VBSPRESSED_F=2, VBSPRESSED_W=4, VBSPRESSED_B=6,VBMOVED=16, GEMCONSUMED=32};
    /*!
     * @brief Stores the state of this object.
     */
    stateOfObj _stateOfObj;
protected:
    /*!
     * @brief Stores the player's texture.
     */
    sf::Texture playerTexture;
    /*!
     * @brief Stores whether the texture file was loaded properly.
     */
    bool _isLoaded;

};
#endif
