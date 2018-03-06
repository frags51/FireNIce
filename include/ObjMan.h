#ifndef FIRENICE_OBJMAN_H
#define FIRENICE_OBJMAN_H

#include "VisibleGameObject.h"
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
/*!
 * @class ObjMan
 * @brief A drawable object manager.
 *
 * Stores, manages and modifies all the drawable (VisibleGameObjects) objects.
 */
class ObjMan{
public:
    /*!
     * @brief The constructor
     *
     * Starts the clock.
     */
    ObjMan();
    /*!
     * @brief The destructor.
     *
     * Deletes all the member VisibleGameObject(s)
     */
    ~ObjMan();
    /*!
     * @brief Insert a new VisibleGameObject to this manager.
     * @param name The name by which this new object will be identified.
     * @param gameObject A pointer to this new VisibleGameObject
     */
    void add(std::string name, VisibleGameObject *gameObject);
    /*!
     * @brief Remove the object specified by name from the manager (does not free/delete).
     * @param name The name of the object to be removed.
     */
    void remove(std::string name);
    /*!
     * Remove, and delete(free) the object specified by name.
     * @param name The name of the object to be removed.
     */
    void removeAndDelete(std::string name);
    /*!
     * @brief Call's the update function for each VisibleGameObject in this manager.
     * @param _event The event to given for the update.
     * @param elapsedTime The time  elaopsed since the last update.
     */
    void updateAll(sf::Event& _event, float elapsedTime);
    /*!
     * @brief The number of objects in this manager.
     * @return The number of objects in this manager.
     */
    int getObjCount() const;
    /*!
     * @brief Get a VisbleGameObject
     * @param name The name of the object to get
     * @return A pointer to the corresponding VisibleGameObject
     */
    VisibleGameObject *get(std::string name) const;
    /*!
     * @brief Calls the Draw function on each VisibleGameObject.
     * @param renderWindow The window to draw the objects on.
     */
    void drawAll(sf::RenderWindow &renderWindow);
    /*!
     * @brief A clock keeping time since the last time update was called.
     */
    sf::Clock _clock;

    /*!
     * @brief A map storing all the VisibleGameObjects by name.
     */
    std::map<std::string, VisibleGameObject*> _gameObjects;

private:
    /*!
     * @brief A functor for deallocating the memory given to each VisibleGameObject. 
     */
    struct GameObjDealloc{
        void operator()(const std::pair<std::string, VisibleGameObject*> &a) const{
            delete a.second;
        }
    }; //functor ends
};

//class
#endif //FIRENICE_OBJMAN_H
