#include <includes.h>

// settings
const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 480;

void processInput(GLFWwindow *window);

int main()
{

    // glfw: init and config
    // --------------------
    init();
    
    // Get a window
    // ------------
    
    Window window = setupWindow(SCR_WIDTH, SCR_HEIGHT);        
        
    // Start drawing
    // -------------
    Draw draw(window, 0.0f, 0.0f, 0.0f);
    // stbi_set_flip_vertically_on_load(true);
    draw.mainLoop();    
        
    return 0;
}
