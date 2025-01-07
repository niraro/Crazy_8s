/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#ifndef UI_H
#define UI_H

#include <string>

/**
 * This is a virtual class that is inherited and implemented by other UI 
 * classes.
*/
class UI {
 public:
    /**
     * @brief Default constructor of UI.
    */
    UI();

    /**
     * @brief Default destructor of UI.
    */
    virtual ~UI();

 private:
    std::string instructions;
};


#endif // UI_H
