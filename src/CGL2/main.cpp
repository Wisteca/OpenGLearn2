
#include "Utils.h"
#include "Shader.h"

#include "WorldObject.h"

// Others inclusions
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;
using namespace glm;
using namespace cgl;

// Constants
/*const float RECTANGLE_1[] =
{
    //  vertex coord        texture coord
    0.25f,  0.5f, 0.0f,      1.0f, 1.0f,      // top right      
    0.25f, -0.5f, 0.0f,      1.0f, 0.0f,      // bottom right
    -0.25f, -0.5f, 0.0f,     0.0f, 0.0f,      // bottom left
    -0.25f,  0.5f, 0.0f,     0.0f, 1.0f,      // top left 
};

const GLuint INDICES[] =
{
    0, 1, 3,
    3, 1, 2
};*/

const float vertices[] = 
{ // this is a cube

//      vertex              tex      
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const float PLANE[] =
{
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
     1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,  1.0f, 1.0f,

    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
     1.0f,  1.0f, 0.0f,  1.0f, 1.0f
};

const unsigned int WINDOW_WIDTH = 1000;
const unsigned int WINDOW_HEIGHT = 800;

int g_width = WINDOW_WIDTH, g_height = WINDOW_HEIGHT;

// Prototypes
void onWindowResize(GLFWwindow* window, int newWidth, int newHeight);
void processInputs(GLFWwindow* window);
void quit(string mess);

/**
 * Main function
 */
int main()
{
    // Initialize the library
    if (!glfwInit())
        return -1;

    // Be sure that OpenGL 3.3 or higher is supported by the graphic card drivers
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Force using the core profile
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
  //  glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    // Create a window object
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "J'apprends wesh", nullptr, nullptr);
    if(window == nullptr)
        quit("Error while creating a window");
    glfwMakeContextCurrent(window); // This window and current (main) thread have the OpenGL context

    // Initialize GLAD 
    if(!gladLoadGLLoader((GLADloadproc) &glfwGetProcAddress))
        quit("Unable to load OpenGL OS specific functions");

    // Initialize events
    glfwSetFramebufferSizeCallback(window, &onWindowResize);
    onWindowResize(window, WINDOW_WIDTH, WINDOW_HEIGHT); // Be sure the event is call at least one time during init

    // windowed fullscreen
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window, nullptr, 0, 0, mode->width, mode->height, mode->refreshRate);

    // ====== OpenGL ======

    // Test max number of vertex attributes the gpu supports (just for fun).
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

    Shader program("shaders/vshader.vs", 
                    "shaders/fshader.fs");

    // Render loop
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST); // Enable z-buffer

    GLint frames = 0;
    unsigned long seconds = 0;
    while(!glfwWindowShouldClose(window))
    {
        // Call events, check keys
        glfwPollEvents();
        processInputs(window);

        // Rendering
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Tell OpenGL we'll be using this shader program to render.
        program.use();



        glfwSwapInterval(1);
        // Rendering finished, swap the buffers
        glfwSwapBuffers(window);

        // Calculate fps
        ++frames;
        if(seconds < (unsigned long) glfwGetTime())
        {
            seconds = glfwGetTime();

            // Only print if it has changed.
            static GLint lastFps = 0;
            if(abs((float) (lastFps - frames)) > 3)
                cout << frames << " fps" << endl;
            lastFps = frames;
            frames = 0;
        }
    }

    glfwTerminate();
    return 0;
}

void onWindowResize(GLFWwindow* window, int newWidth, int newHeight)
{
    // Tell OpenGL that the viewport take place inside the entire window
    glViewport(0, 0, newWidth, newHeight);
    g_width = newWidth;
    g_height = newHeight;
    cout << "new width is " << newWidth << ", new height is " << newHeight << "." << endl;
}

void processInputs(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); // Change close flag to true if esc key is pressed.
}

void quit(string mess)
{
    glfwTerminate();
    cout << mess << endl;
    getchar();
    exit(-1);
}
