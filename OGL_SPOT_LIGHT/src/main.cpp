#include <includes.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window);

int main()
{

    // glfw: init and config
    // --------------------
    init();
    
    // Get a window
    // ------------
    
    Window window = setupWindow(SCR_WIDTH, SCR_HEIGHT);        
    
    // Get the drawing data inside
    // ---------------------------
    RenderDataManager::getInstance().setup();
    
    // Start drawing
    // -------------
    Draw draw(window, 0.2f, 0.2f, 0.2f);
    
    draw.mainLoop();
        
    return 0;
}
