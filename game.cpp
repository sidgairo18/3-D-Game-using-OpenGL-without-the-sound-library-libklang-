#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

float xa=1280;
float ya=720;
float za=720;
int view = 0;
int lives=8;
int score=0;

int oldx=0;
int oldy=0;

float mult=1;

//level 1
/*
int map[10][10] = { 
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
int mov[10][10] = { 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
int map2[10][10] = { 
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
};
*/
//level 2

int map[10][10] = { 
    {1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 1, 1, 1, 0, 2, 0, 1, 1, 1},
};


//check for moving blocks
int mov[10][10] = { 
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
};

//map for collectable
int map2[10][10] = { 
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
};






int block_size=10;
int block_height=15;

//players variables

int finish=0;
float dotproductx,dotproductz,crossproductx,crossproductz;
float mod1,mod2;
float scroll=1;


struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint MatrixID;
} Matrices;

GLuint programID;

/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void quit(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


/* Generate VAO, VBOs and return VAO handle */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode=GL_FILL)
{
    struct VAO* vao = new struct VAO;
    vao->PrimitiveMode = primitive_mode;
    vao->NumVertices = numVertices;
    vao->FillMode = fill_mode;

    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers (1, &(vao->VertexBuffer)); // VBO - vertices
    glGenBuffers (1, &(vao->ColorBuffer));  // VBO - colors

    glBindVertexArray (vao->VertexArrayID); // Bind the VAO 
    glBindBuffer (GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
            0,                  // attribute 0. Vertices
            3,                  // size (x,y,z)
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );

    glBindBuffer (GL_ARRAY_BUFFER, vao->ColorBuffer); // Bind the VBO colors 
    glBufferData (GL_ARRAY_BUFFER, 3*numVertices*sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);  // Copy the vertex colors
    glVertexAttribPointer(
            1,                  // attribute 1. Color
            3,                  // size (r,g,b)
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );

    return vao;
}

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode=GL_FILL)
{
    GLfloat* color_buffer_data = new GLfloat [3*numVertices];
    for (int i=0; i<numVertices; i++) {
        color_buffer_data [3*i] = red;
        color_buffer_data [3*i + 1] = green;
        color_buffer_data [3*i + 2] = blue;
    }

    return create3DObject(primitive_mode, numVertices, vertex_buffer_data, color_buffer_data, fill_mode);
}

/* Render the VBOs handled by VAO */
void draw3DObject (struct VAO* vao)
{
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray (vao->VertexArrayID);

    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

/**************************
 * Customizable functions *
 **************************/

float triangle_rot_dir = 1;
float rectangle_rot_dir = 1;
bool triangle_rot_status = true;
bool rectangle_rot_status = true;

//player struct
typedef struct player{
    VAO *pl;
    float x,y,z;
    int b,h,l;
    float a,v;
}player;

player p;

//blocks struct


typedef struct blocks{
    VAO *bl;
    int x,y,z,flag,rev;
    float b,h,l;
    float c1,c2,c3;
    float add;
}blocks;

blocks bs[301];

float g=0.09;
float xangle=0,height=0,zangle=0;
float angle1=45;
float angle2=45;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_C:
                rectangle_rot_status = !rectangle_rot_status;
                break;
            case GLFW_KEY_P:
                triangle_rot_status = !triangle_rot_status;
                break;
            case GLFW_KEY_V:
                view = (view + 1)%6;
                break;
            case GLFW_KEY_UP:
                if(view==4 || view ==3)
                    p.x += mult*block_size*dotproductx/mod1,p.z += mult*block_size*dotproductz/mod1;
                else
                    p.x -=mult*block_size;

                break;
            case GLFW_KEY_DOWN:
                if(view==4 || view ==3)
                    p.x += -1*block_size*dotproductx/mod1*mult,p.z += -1*block_size*dotproductz/mod1*mult;
                else
                    p.x +=block_size*mult;
                break;
            case GLFW_KEY_LEFT:
                if(view==4 || view==3)
                    p.x += -1*block_size*crossproductx/mod2*mult,p.z += -1*block_size*crossproductz/mod2*mult;
                else
                    p.z +=block_size*mult;
                break;
            case GLFW_KEY_RIGHT:
                if(view==4 || view==3)
                    p.x += block_size*crossproductx/mod2*mult,p.z += block_size*crossproductz/mod2*mult;
                else
                    p.z -=block_size*mult;
                break;
            case GLFW_KEY_SPACE:
                p.v = 2;
                break;
            case GLFW_KEY_F:
                mult +=0.1;
                break;
            case GLFW_KEY_S:
                mult -= 0.1;
                break;
            default:
                break;
        }
    }
    else if (action == GLFW_REPEAT){

        switch(key){

            case GLFW_KEY_UP:
                if(view==4 || view==3)
                    p.x += block_size*dotproductx/mod1*mult,p.z += block_size*dotproductz/mod1*mult;
                else
                    p.x -=block_size*mult ;
                break;
            case GLFW_KEY_DOWN:
                if(view==4 || view==3)
                    p.x += -1*block_size*dotproductx/mod1*mult,p.z += -1*block_size*dotproductz/mod1*mult;
                else
                    p.x +=block_size*mult;
                break;
            case GLFW_KEY_LEFT:
                if(view==4 || view ==3)
                    p.x += -1*block_size*crossproductx/mod2*mult,p.z += -1*block_size*crossproductz/mod2*mult;
                else
                    p.z +=block_size*mult;
                break;
            case GLFW_KEY_RIGHT:
                if(view==4 || view==3)
                    p.x += block_size*crossproductx/mod2*mult,p.z += block_size*crossproductz/mod2*mult;
                else
                    p.z -=block_size*mult;
                break;

            case GLFW_KEY_D:
                xangle++;
                zangle++;
                angle1++;
                break;

            case GLFW_KEY_A:
                xangle--;
                zangle--;
                angle1--;
                break;
            case GLFW_KEY_W:
                height--;
                break;
            case GLFW_KEY_S:
                height++;
                break;
            default:
                break;
        }

    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            default:
                break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
    switch (key) {
        case 'Q':
        case 'q':
            quit(window);
            break;
        default:
            break;
    }
}

/* Executed when a mouse button is pressed/released */
bool mouse_drag = false;
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{

    switch(button){
        case GLFW_MOUSE_BUTTON_LEFT:
            if( action == GLFW_PRESS )
            {
                mouse_drag = true;
            }
            if (action == GLFW_RELEASE) 
            {
                mouse_drag = false;
            }
            break;
        default:
            break;
    }
}

void cursorPos(GLFWwindow *window, double x_position,double y_position)
{


    if( mouse_drag )
    {
        angle1+=(x_position-oldx);
        angle2+=(y_position-oldy);
    }
    oldx=x_position;
    oldy=y_position;

}

void mouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0) 
    { 
        scroll+=0.5;
    }
    else 
    {
        scroll-=0.5;
    }
}


/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
    int fbwidth=width, fbheight=height;
    /* With Retina display on Mac OS X, GLFW's FramebufferSize
       is different from WindowSize */
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    GLfloat fov = 70.0f;

    // sets the viewport of openGL renderer
    glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

    // set the projection matrix as perspective
    /* glMatrixMode (GL_PROJECTION);
       glLoadIdentity ();
       gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
    // Store the projection matrix in a variable for future use
    //  Perspective projection for 3D views
    Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

    //Ortho projection for 2D views
    //Matrices.projection = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, 0.1f, 500.0f);
}

VAO *triangle, *rectangle,*xaxis,*yaxis,*zaxis,*cube;



// Creates the triangle object used in this sample code
void createTriangle ()
{
    /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

    /* Define vertex array as used in glBegin (GL_TRIANGLES) */
    static const GLfloat vertex_buffer_data [] = {
        0, 1,0, // vertex 0
        -1,-1,0, // vertex 1
        1,-1,0, // vertex 2
    };

    static const GLfloat color_buffer_data [] = {
        1,0,0, // color 0
        0,1,0, // color 1
        0,0,1, // color 2
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    triangle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
}
void createxaxis()
{
    /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

    /* Define vertex array as used in glBegin (GL_TRIANGLES) */
    GLfloat vertex_buffer_data [] = {
        640, 0,0, // vertex 0
        -640,0,0, // vertex 1
    };

    GLfloat color_buffer_data [] = {
        1,0,0, // color 0
        1,0,0, // color 1
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    xaxis= create3DObject(GL_LINES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
}
void createyaxis()
{
    /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

    /* Define vertex array as used in glBegin (GL_TRIANGLES) */
    GLfloat vertex_buffer_data [] = {
        0,360,0, // vertex 0
        0,-360,0, // vertex 1
    };

    GLfloat color_buffer_data [] = {
        0,1,0, // color 0
        0,1,0, // color 1
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    yaxis= create3DObject(GL_LINES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
}

//creating z axis
void createzaxis()
{
    /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

    /* Define vertex array as used in glBegin (GL_TRIANGLES) */
    GLfloat vertex_buffer_data [] = {
        0,0,360, // vertex 0
        0,0,-360, // vertex 1
    };

    GLfloat color_buffer_data [] = {
        0,0,1, // color 0
        0,0,1, // color 1
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    zaxis= create3DObject(GL_LINES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
}

// Creates the rectangle object used in this sample code
void createRectangle (float x, float y, float z)
{
    // GL3 accepts only Triangles. Quads are not supported
    static const GLfloat vertex_buffer_data [] = {
        -x,-y,z, // vertex 1
        x,-y,z, // vertex 2
        x, y,z, // vertex 3

        x, y,z, // vertex 3
        -x, y,z, // vertex 4
        -x,-y,z  // vertex 1
    };

    static const GLfloat color_buffer_data [] = {
        1,0,0, // color 1
        0,0,1, // color 2
        0,1,0, // color 3

        0,1,0, // color 3
        0.3,0.3,0.3, // color 4
        1,0,0  // color 1
    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void createcube (float b, float h, float l, float c1, float c2, float c3)
{
    // GL3 accepts only Triangles. Quads are not supported
    GLfloat vertex_buffer_data [] = {
        -b,-h,l, // vertex 1
        b,-h,l, // vertex 2
        b, h,l, // vertex 3

        b, h,l, // vertex 3
        -b, h,l, // vertex 4
        -b,-h,l,  // vertex 1*/

        -b,-h,-l, // vertex 1
        b,-h,-l, // vertex 2
        b, h,-l, // vertex 3

        b, h,-l, // vertex 3
        -b, h,-l, // vertex 4
        -b,-h,-l,  // vertex 1


        -b,h,-l, // vertex 1
        b,h,-l, // vertex 2
        b, h,l, // vertex 3

        b, h,l, // vertex 3
        -b, h,l, // vertex 4
        -b,h,-l,  // vertex 1

        -b,-h,-l, // vertex 1
        b,-h,-l, // vertex 2
        b, -h,l, // vertex 3

        b, -h,l, // vertex 3
        -b, -h,l, // vertex 4
        -b,-h,-l,  // vertex 1

        b,-h,-l, // vertex 1
        b,-h,l, // vertex 2
        b, h,l, // vertex 3

        b, h,l, // vertex 3
        b, h,-l, // vertex 4
        b,-h,-l,  // vertex 1

        -b,-h,-l, // vertex 1
        -b,-h,l, // vertex 2
        -b, h,l, // vertex 3

        -b, h,l, // vertex 3
        -b, h,-l, // vertex 4
        -b,-h,-l  // vertex 1
    };

    GLfloat color_buffer_data [] = {
        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    cube = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
}

//creating player
void createplayer (float x, float y, float z, float a, float c1, float c2, float c3)
{
    // GL3 accepts only Triangles. Quads are not supported
    GLfloat vertex_buffer_data [] = {
        -x,-y,a, // vertex 1
        x,-y,a, // vertex 2
        x, y,a, // vertex 3

        x, y,a, // vertex 3
        -x, y,a, // vertex 4
        -x,-y,a,  // vertex 1*/

        -x,-y,-a, // vertex 1
        x,-y,-a, // vertex 2
        x, y,-a, // vertex 3

        x, y,-a, // vertex 3
        -x, y,-a, // vertex 4
        -x,-y,-a,  // vertex 1


        -x,a,-z, // vertex 1
        x,a,-z, // vertex 2
        x, a,z, // vertex 3

        x, a,z, // vertex 3
        -x, a,z, // vertex 4
        -x,a,-z,  // vertex 1

        -x,-a,-z, // vertex 1
        x,-a,-z, // vertex 2
        x, -a,z, // vertex 3

        x, -a,z, // vertex 3
        -x, -a,z, // vertex 4
        -x,-a,-z,  // vertex 1

        a,-y,-z, // vertex 1
        a,-y,z, // vertex 2
        a, y,z, // vertex 3

        a, y,z, // vertex 3
        a, y,-z, // vertex 4
        a,-y,-z,  // vertex 1

        -a,-y,-z, // vertex 1
        -a,-y,z, // vertex 2
        -a, y,z, // vertex 3

        -a, y,z, // vertex 3
        -a, y,-z, // vertex 4
        -a,-y,-z  // vertex 1
    };

    GLfloat color_buffer_data [] = {
        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    p.pl = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
}

//colors base

float k1,k2,k3;

//creating blocks
void createblocks (float b, float h, float l, float c1, float c2, float c3,int index)
{
    // GL3 accepts only Triangles. Quads are not supported
    GLfloat vertex_buffer_data [] = {
        -b,-h,l, // vertex 1
        b,-h,l, // vertex 2
        b, h,l, // vertex 3

        b, h,l, // vertex 3
        -b, h,l, // vertex 4
        -b,-h,l,  // vertex 1*/

        -b,-h,-l, // vertex 1
        b,-h,-l, // vertex 2
        b, h,-l, // vertex 3

        b, h,-l, // vertex 3
        -b, h,-l, // vertex 4
        -b,-h,-l,  // vertex 1


        -b,h,-l, // vertex 1
        b,h,-l, // vertex 2
        b, h,l, // vertex 3

        b, h,l, // vertex 3
        -b, h,l, // vertex 4
        -b,h,-l,  // vertex 1

        -b,-h,-l, // vertex 1
        b,-h,-l, // vertex 2
        b,-h,l, // vertex 3

        b, -h,l, // vertex 3
        -b, -h,l, // vertex 4
        -b,-h,-l,  // vertex 1

        b,-h,-l, // vertex 1
        b,-h,l, // vertex 2
        b, h,l, // vertex 3

        b, h,l, // vertex 3
        b, h,-l, // vertex 4
        b,-h,-l,  // vertex 1

        -b,-h,-l, // vertex 1
        -b,-h,l, // vertex 2
        -b, h,l, // vertex 3

        -b, h,l, // vertex 3
        -b, h,-l, // vertex 4
        -b,-h,-l  // vertex 1
    };

    GLfloat color_buffer_data [] = {
        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3

        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3

        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3

        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        c1,c2,c3, // color 1
        c1,c2,c3, // color 2
        c1,c2,c3, // color 3

        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3

        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3

        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3

        k1,k2,k3, // color 1
        k1,k2,k3, // color 2
        k1,k2,k3, // color 3


    };

    // create3DObject creates and returns a handle to a VAO that can be used later
    bs[index].bl = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
}

float camera_rotation_angle = 90;
float rectangle_rotation = 0;
float triangle_rotation = 0;

void check_coll(){


    if(p.y<=-100){
        p.x=-9*block_size;
        p.z=9*block_size;
        lives--;
    }
    /*if(p.x>10*block_size || p.x<-10*block_size || p.z>10*block_size || p.z<-10*block_size)
      {p.x=-9*block_size;
      p.z=9*block_size;}*/



}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw ()
{
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    glm::vec3 Xaxis(1,0,0);
    glm::vec3 Zaxis(0,0,1);
    glm::vec3 Yaxis(0,1,0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    //  Don't change unless you are sure!!
    if( view == 0)
        Matrices.view = glm::lookAt(glm::vec3(180,200,180), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
    else if( view == 1)
        Matrices.view = glm::lookAt(glm::vec3(300,0.1,0.1), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
    else if( view == 2)
        Matrices.view = glm::lookAt(glm::vec3(0.1,400,0.1), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
    else if( view == 3)
        //Matrices.view = glm::lookAt(glm::vec3(-90+p.x,200,90+p.z), glm::vec3(0,p.y+10,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
        Matrices.view = glm::lookAt(glm::vec3(p.x-20*cos(xangle*M_PI/180.0f),p.y+height,p.z-20*sin(zangle*M_PI/180.0f)),glm::vec3(p.x,p.y,p.z), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
    else if( view == 4)
        Matrices.view = glm::lookAt(glm::vec3(p.x,p.y+10,p.z), glm::vec3(p.x+20*cos(xangle*M_PI/180.0f),p.y+height,p.z+20*sin(zangle*M_PI/180.0f)), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
    else if( view == 5)
        Matrices.view = glm::lookAt(glm::vec3(200*cos(angle1*M_PI/180.0f)*sin(angle2*M_PI/180.0f)/scroll,250/scroll,200*sin(angle1*M_PI/180.0f)*sin(angle2*M_PI/180.0f)/scroll), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane
    glm::vec3 camerapos(p.x,p.y+10,p.z);
    glm::vec3 cameralookat(p.x+20*cos(xangle*M_PI/180.0f),p.y+height,p.z+20*sin(zangle*M_PI/180.0f));
    glm::vec3 difference = cameralookat- camerapos;
    glm::vec3 perpend = glm::cross(difference,Yaxis);
    dotproductx = glm::dot(difference,Xaxis);
    dotproductz = glm::dot(difference,Zaxis);
    crossproductx = glm::dot(perpend,Xaxis);
    crossproductz = glm::dot(perpend,Zaxis);

    mod1 = sqrt(difference.x*difference.x+difference.z*difference.z);
    mod2 = sqrt(perpend.x*perpend.x+perpend.y*perpend.y+perpend.z*perpend.z);

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    //  Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    //  Don't change unless you are sure!!
    glm::mat4 MVP;	// MVP = Projection * View * Model

    // Load identity to model matrix
    Matrices.model = glm::mat4(1.0f);

    /* Render your scene */

    glm::mat4 translateTriangle = glm::translate (glm::vec3(-2.0f, 0.0f, 0.0f)); // glTranslatef
    glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
    glm::mat4 triangleTransform = translateTriangle * rotateTriangle;
    Matrices.model *= triangleTransform; 
    MVP = VP * Matrices.model; // MVP = p * V * M

    //  Don't change unless you are sure!!
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    //  draw3DObject(triangle);

    //drawing xaxis
    Matrices.model = glm::mat4(1.0f);

    /* Render your scene */

    glm::mat4 translatexaxis = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f)); // glTranslatef
    //glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
    glm::mat4 xaxisTransform = translatexaxis;
    Matrices.model *= xaxisTransform; 
    MVP = VP * Matrices.model; // MVP = p * V * M

    //  Don't change unless you are sure!!
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    draw3DObject(xaxis);

    //drawing yaxis
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateyaxis = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f)); // glTranslatef
    //glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
    glm::mat4 yaxisTransform = translateyaxis;
    Matrices.model *= yaxisTransform; 
    MVP = VP * Matrices.model; // MVP = p * V * M

    //  Don't change unless you are sure!!
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    draw3DObject(yaxis);
    //drawing zaxis
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translatezaxis = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f)); // glTranslatef
    //glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
    glm::mat4 zaxisTransform = translatezaxis;
    Matrices.model *= zaxisTransform; 
    MVP = VP * Matrices.model; // MVP = p * V * M

    //  Don't change unless you are sure!!
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    draw3DObject(zaxis);

    // Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
    // glPopMatrix ();
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateRectangle = glm::translate (glm::vec3(0, 0, 0));        // glTranslatef
    // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
    Matrices.model *= (translateRectangle);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    //draw3DObject(rectangle);

    //drawing blocks

    int k=0;
    int prev=p.y;

    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){

            if(map[i][j]!=0){
                if(mov[i][j]){
                    bs[k].add=bs[k].add+0.5f*bs[k].rev;
                    if(bs[k].add>30 || bs[k].add<-20)
                        bs[k].rev*=-1;
                }


                Matrices.model = glm::mat4(1.0f);
                glm::mat4 translateground = glm::translate (glm::vec3(bs[k].x, bs[k].y+bs[k].add, bs[k].z));        // glTranslatef
                // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
                Matrices.model *= (translateground);
                MVP = VP * Matrices.model;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                // draw3DObject draws the VAO given to it using current MVP matrix
                draw3DObject(bs[k].bl);
                bs[k].flag=1;

                if(p.x<=(bs[k].x+block_size) && p.x>=(bs[k].x-block_size) && p.z<=(bs[k].z+block_size) && p.z>=(bs[k].z-block_size)){
                    if(p.y<2*bs[k].h/*block_height*/+bs[k].add+p.h){
                        p.y=2*bs[k].h+bs[k].add+p.h;
                        p.v=0;
                        if(abs(prev-p.y)>=10){
                            p.x=-9*block_size;
                            p.z=9*block_size;
                            lives--;
                        }
                    }

                }

            }
            k++;
        }
    check_coll();
    //checking for finish position

    if(p.x<=(bs[99].x+block_size) && p.x>=(bs[99].x-block_size) && p.z<=(bs[99].z+block_size) && p.z>=(bs[99].z-block_size) && !finish){
        finish=1;
        score+=100;
    }

    if(finish==1)
        createblocks(bs[99].b,bs[99].h,bs[99].l,255.0f/255,255.0f/255,255.0f/255,99);


    //drawing water
    createcube (150,2,150,0,1,1);
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translatecube = glm::translate (glm::vec3(0, -2, 0));        // glTranslatef
    // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
    Matrices.model *= (translatecube);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // draw3DObject draws the VAO given to it using current MVP matrix
    draw3DObject(cube);

    //drawing player
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translateplayer = glm::translate (glm::vec3(p.x,p.y, p.z));        // glTranslatef
    // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
    Matrices.model *= (translateplayer);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    p.y+=p.v;
    p.v-=g;
    // cout<<p.v<<endl;

    // draw3DObject draws the VAO given to it using current MVP matrix
    if(lives>0)
        draw3DObject(p.pl);

    cout<<"Lives Left = "<<((lives-1)/2+1)<<" "<<" Score = "<<score<<" Speed "<<mult<<endl;

    //drawing collectables
    k=100;

    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){

            if(map2[i][j]!=0 && !bs[k].flag){

                Matrices.model = glm::mat4(1.0f);
                glm::mat4 translateground = glm::translate (glm::vec3(bs[k].x, bs[k].y+bs[k].add, bs[k].z));        // glTranslatef
                // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
                Matrices.model *= (translateground);
                MVP = VP * Matrices.model;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                // draw3DObject draws the VAO given to it using current MVP matrix
                draw3DObject(bs[k].bl);

                if(p.x<=(bs[k].x+bs[k].b) && p.x>=(bs[k].x-bs[k].b) && p.z<=(bs[k].z+bs[k].l) && p.z>=(bs[k].z-bs[k].l)){
                    bs[k].flag=1;
                    score+=10;
                }
            }
            k++;
        }


    // Increment angles
    float increments = 1;

    //camera_rotation_angle++; // Simulating camera rotation
    triangle_rotation = triangle_rotation + increments*triangle_rot_dir*triangle_rot_status;
    rectangle_rotation = rectangle_rotation + increments*rectangle_rot_dir*rectangle_rot_status;
}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height)
{
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
       is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks
    glfwSetCursorPosCallback(window, cursorPos);
    glfwSetScrollCallback(window,mouseScroll);

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    createTriangle (); // Generate the VAO, VBOs, vertices data & copy into the array buffer
    createRectangle (xa/100, ya/100, 20);
    createxaxis ();
    createyaxis ();
    createzaxis ();
    createcube (10,10,30,0,1,1);
    createplayer (p.b,p.h,p.l,p.a,255.0f/255,255.0f/255,0);
    int k=0;

    for(int i=-9;i<=9;i+=2)
        for(int j=9;j>=-9;j-=2){
            k++;

            bs[k-1].b=block_size;
            bs[k-1].l=block_size;
            bs[k-1].h=map[(i+9)/2][(9-j)/2]*block_height;
            if(k==100)
                createblocks(bs[k-1].b,bs[k-1].h,bs[k-1].l,0.0f/255,0.0f/255,0.0f/255,k-1);
            else if (k==1)
                createblocks(bs[k-1].b,bs[k-1].h,bs[k-1].l,255.0f/255,255.0f/255,255.0f/255,k-1);
            else
                createblocks(bs[k-1].b,bs[k-1].h,bs[k-1].l,165.0f/255,42.0f/255,42.0f/255,k-1);

            bs[k-1].x=block_size*i;
            bs[k-1].z=block_size*j;
            bs[k-1].y=bs[k-1].h;

            bs[k-1].c1=1.0f/255;
            bs[k-1].c2=1.0f/255;
            bs[k-1].c3=1.0f/255;

            bs[k-1].flag=0;
            bs[k-1].add=0;
            bs[k-1].rev=1;
        }
    k=100;
    for(int i=-9;i<=9;i+=2)
        for(int j=9;j>=-9;j-=2){

            bs[k].b=2;
            bs[k].l=2;
            bs[k].h=3;
            k1=255.0f/255;
            k2=255.0f/255;
            k3=224.0f/255;
            createblocks(bs[k].b,bs[k].h,bs[k].l,255.0f/255,99.0f/255,71.0f/255,k);
            bs[k].x=block_size*i;
            bs[k].z=block_size*j;
            bs[k].y=2*bs[k-100].h+bs[k].h;

            bs[k].c1=1.0f/255;
            bs[k].c2=1.0f/255;
            bs[k].c3=1.0f/255;

            bs[k].flag=0;
            bs[k].add=0;
            bs[k].rev=1;
            k++;

        }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (0.3f, 0.3f, 0.3f, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main (int argc, char** argv)
{
    int width = xa;
    int height = ya;
    /*k1=165.0f/255.0f;
      k2=42.0f/255.0f;
      k3=42.0f/255.0f;*/
    k1=0.0f/255.0f;
    k2=128.0f/255.0f;
    k3=0.0f/255.0f;

    p.b=5;
    p.h=5;
    p.l=5;
    p.a=2;
    p.x=-9*block_size;
    p.y=0;
    p.z=9*block_size;
    p.v=0;


    GLFWwindow* window = initGLFW(width, height);

    initGL (window, width, height);

    double last_update_time = glfwGetTime(), current_time;

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {

        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
