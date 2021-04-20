
#include "Utils.h"

#include "CGLObject.h"

// Others inclusions
#include <iostream>
#include <string>
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
GLuint createVAO_VBO_EBO(const float vertices[], GLuint vsize, const GLuint indices[], GLuint isize);
GLuint createVAO_VBO(const float vertices[], GLuint size);


class Shoot : public CGLObject
{
    public :
    vec2 m_dir;
    int m_live = 0;
    bool destruct = false;

    Shoot(vector<float> vertices, vec2 dir) : CGLObject(vertices)
    {
        m_dir = -dir;
        m_scale = vec3(0.2, 0.2, 0.2);
    }

    void render(Shader& program) override
    {
        CGLObject::render(program);

        m_live++;
        m_pos = m_pos + vec3(m_dir.x, 0, m_dir.y) * 0.05f;
        m_rot += vec3(0.01, 0.02, 0.01);

        if(m_live > 1000)
            destruct = true;
    }
};


/**
 * Main function
 */
int main()
{
    srand(time(nullptr));

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
//    onWindowResize(window, WINDOW_WIDTH, WINDOW_HEIGHT); // Be sure the event is call at least one time during init

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

    vector<float> vec;
    for(size_t i = 0 ; i < (sizeof(vertices) / sizeof(float)) ; ++i)
        vec.push_back(vertices[i]);
    CGLObject* cglobj = new CGLObject(vec);

    Texture* tex1 = new Texture("assets/lol.jpg");
    Texture* tex2 = new Texture("assets/map.jpg");
    Texture* tex3 = new Texture("assets/out_of_order.png");
    cglobj->setTexture(tex1);
    cglobj->setScale(vec3(.5, .5, .5));

    vector<float> vect2;
    for(size_t i = 0 ; i < (sizeof(PLANE) / sizeof(float)) ; ++i)
        vect2.push_back(PLANE[i]);
    CGLObject* plane = new CGLObject(vect2);
    plane->setTexture(tex2);

    plane->setRotation(vec3(-M_PI / 2, 0, 0));
    plane->setPosition(vec3(0, -1, -2));
    plane->setScale(vec3(8, 8, 8));

    list<Shoot*> shoots;

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


        // plane position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        vec2 curpos(xpos, ypos);
        vec2 dir = normalize(vec2(g_width / 2, g_height / 2) - curpos);

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            plane->setPosition(vec3(plane->getPosition().x + dir.x * 0.01, plane->getPosition().y, plane->getPosition().z + dir.y * 0.01));

        // Shooting
        static bool press = false;
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && press == false)
        {
            press = true;
            Shoot* shoot = new Shoot(vec, dir);
            shoot->setTexture(tex3);
            shoots.push_back(shoot);
        }
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
            press = false;

        static float viewRot = 0;
        if(viewRot < M_PI / 2)
            viewRot += .003;

        mat4 view = mat4(1.0f);
        view = translate(view, vec3(0, 0.5 - (M_PI / 2 - viewRot) * 10, -6 - (M_PI / 2 - viewRot) * 30));
        view = rotate(view, viewRot, vec3(1, 0, 0));
        mat4 projection = perspective(radians(45.0f), (float) g_width / g_height, 0.1f, 100.0f);

        program.setUniform("uniView", view);
        program.setUniform("uniProjection", projection);

        cglobj->setRotation(vec3(cglobj->getRotation().x + .002, cglobj->getRotation().y + .004, cglobj->getRotation().z + .002));

        // Rendering
        cglobj->render(program);
        plane->render(program);

        for(Shoot* sh : shoots)
        {
            sh->render(program);
            if(sh->destruct)
            {
                shoots.remove(sh);
                delete sh;
            }
        }

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

GLuint createVAO_VBO_EBO(const float vertices[], GLuint vsize, const GLuint indices[], GLuint isize)
{
    // Create two buffers, an EBO and a VBO.
    GLuint buffers[2];
    glGenBuffers(2, buffers);

    // Create the VAO object and start storing actions.
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id); // start

    // Configure ebo as ebo and vbo as vbo.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);

    // Put data inside vbo and ebo.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);

    // Tell how to interpret data in the vbo.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0); // vertex coords
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float))); // tex coords
    glEnableVertexAttribArray(1);

    // Unbind the vao, storage is finished.
    glBindVertexArray(0);
    return vao_id;
}

GLuint createVAO_VBO(const float vertices[], GLuint size)
{
    // ===== vertices =====
    // Create a VBO and put the vertices inside it.
    GLuint vbo_id; // OpenGL ID of the buffer object
    glGenBuffers(1, &vbo_id); // Generate the ID of the buffer (1 time)

    // Create the VAO that will store the VBO and its attributes.
    // The VAO must be binded to save any call to :
    // - glVertexAttribPointer
    // - glEnableVertexAttribArray / glDisableVertexAttribArray
    // Like this, we can bind the VAO, configure the VBO correcly and unbind the VAO. Next it will
    // be possible to just bind the VAO to load the configuration directly, without the need of
    // reconfigure everything.
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id); // Generate the vao
    glBindVertexArray(vao_id); // From now, save all actions

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id); // Tell OpenGL that this is a vertex object buffer.
    // It's possible to pass nullptr as first argument to remove any buffer specification.
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Fill the buffer with vertices.
    /*
    fourth argument can be :
    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    This tells the gpu how datas will be used so it can put it in an adaptated memory. 
    */

    // Tell OpenGL how it shoulds interpret vertices
    // The first parameter is the vertex attribute index. Because in the vertex shader location = 0
    // is specified, 0 must be passed here. The second parameter is the number of values that composes
    // a vertex attribute. Here we have x, y and z so it is 3 values. Third parameter specifies the
    // type of each attribute, here we have 3 floats (because a vec? in GLSL consists of float values).
    // Next argument allows to normalize input datas between -1 and 1, it can be useful if inputs datas
    // are int or byte for example.
    // It is possible for OpenGL to determine the size of each vertex as we tell him there is 3 values
    // of type float by vertex (so 3 * 4 = 12 bytes / vertex). Now, if vertices are tighly packed (no space
    // between) it is possible to pass 0 as next parameter. If there is some space it is necessary to specify
    // the stride. Here the stride is 3 times the size of a float, so 0 can match too.
    // Last parameter is the pointer on the first data in the buffer. 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0); // Enable the vbo at index 0

    // Texture
    // Location = 1, 3 values for an attribute, no normalization, stride of a vertex if 6 times the size of a float,
    // the texture data starts 3*sizeof(float) after the beginning of the vertex, so after the vertex pos.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind the vao
    glBindVertexArray(0);
    return vao_id; // Return the vao id.
}