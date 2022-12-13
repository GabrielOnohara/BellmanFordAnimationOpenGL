
#include<dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

/* Globals */
int triangles_array = 3;
int  type_primitive = GL_TRIANGLES;
int type_polygon = GL_FILL;
/** Window width. */
int win_width  = 500;
/** Window height. */
int win_height = 500;

/** Program variable. */
int program;
/** Vertex array object. */
unsigned int VAO;
/** Vertex buffer object. */
unsigned int VBO;

/** Vertex shader. */
// const char *vertex_code = "\n"
// "#version 330 core\n"
// "layout (location = 0) in vec3 position;\n"
// "layout (location = 1) in vec3 color;\n"
// "\n"
// "out vec3 vColor \n"
// "void main()\n"
// "{\n"
// // "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//     "gl_Position = vec4(position, 1.0);\n"
//     "vColor = color;\n"
// "}\0";

// /** Fragment shader. */
// const char *fragment_code = "\n"
// "#version 330 core\n"
// "in vec3 vColor\n"
// "out vec4 FragColor;\n"
// "\n"
// "void main()\n"
// "{\n"
// "    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
// "}\0";


/** Rotation angle. */
float angle = 0.0f;
/** Rotation increment. */
float angle_inc = 1.0f;
/** Rotation mode. */
int mode = 1;
int step = 0;

float deslocamentoX = 0.0f;
float deslocamentoY = 0.0f;
float scale = 1.0f;

const char *vertex_code = "\n"
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"\n"
"out vec3 vColor;\n"
"\n"
"uniform mat4 transform;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = transform * vec4(position, 1.0);\n"
"    vColor = color;\n"
"}\0";

/** Fragment shader. */
const char *fragment_code = "\n"
"#version 330 core\n"
"\n"
"in vec3 vColor;\n"
"out vec4 FragColor;\n"
"uniform vec3 objectColor;\n"
"\n"
"void main()\n"
"{\n"
"    vec3 auxColor = vColor*objectColor;   \n"
"    FragColor = vec4(auxColor, 1.0f);\n"
"}\0";

#include <windows.h>

/* Functions. */
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void initData(void);
void initShaders(void);
void idle(void);
/** 
 * Drawing function.
 *
 * Draws a triangle.
 */



void display()
{
    	glClearColor(0.5, 0.6, 0.5, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT);

    	glUseProgram(program);
    	glBindVertexArray(VAO);

      	// Translation. 
        
        for (int i = 0; i < 7; i++)
        {
          for (int j = -6; j <= 0 ; j++)
          {unsigned int loc2 = glGetUniformLocation(program, "objectColor");
            if(step == 0){ 
                glUniform3f(loc2, 1.0, 1.0, 1.0);
            }else if(step == 1){
              if(i==0  && j==0){
                glUniform3f(loc2, 1.0, 1.0, 10.0);  
              }else if(i==6  && j== -6){
                glUniform3f(loc2, 1.0, 1.0, 10.0);  
              }else{
                glUniform3f(loc2, 1.0, 1.0, 1.0); 
              }
            }else if(step > 1){
              if(i< step && j< step){
                if(i==0  && j==0){
                glUniform3f(loc2, 1.0, 1.0, 10.0);  
              }else if(i==6  && j== -6){
                glUniform3f(loc2, 1.0, 1.0, 10.0);  
              }else{
                if(i == -j){
                  glUniform3f(loc2, 1.0, 10.0, 1.0); 
                }
                else{
                  glUniform3f(loc2, 1.0, 1.0, 1.0); 
                }
              }
              }
            }
            glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(deslocamentoX+i*0.2, deslocamentoY+j*0.2, 0.0f));
            // Rotation around z-axis.
            glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,0.0f,1.0f));
            // Scale.
            glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));

            glm::mat4 M = glm::mat4(1.0f);
            if (mode == 1)
            M = T*Rz*S;
            else if (mode == 2)
            M = Rz*T*S;

            // Retrieve location of tranform variable in shader.
            unsigned int loc = glGetUniformLocation(program, "transform");

            // Send matrix to shader.
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(M));

            // Draws the triangle.
            glDrawArrays(type_primitive, 0, 3*triangles_array);
           
          }
          
        }
      

       
      glutSwapBuffers();
    	
}

/**
 * Reshape function.
 *
 * Called when window is resized.
 *
 * @param width New window width.
 * @param height New window height.
 */
void reshape(int width, int height)
{
    win_width = width;
    win_height = height;
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}


/** 
 * Keyboard function.
 *
 * Called to treat pressed keys.
 *
 * @param key Pressed key.
 * @param x Mouse x coordinate when key pressed.
 * @param y Mouse y coordinate when key pressed.
 */
void keyboard(unsigned char key, int x, int y)
{
        switch (key)
        {
          case 27:
                  exit(0);
                  break;
          case 'q':
          case 'Q':
                  exit(0);
                  break;
          case 'h':
          case 'H':
                if(triangles_array == 3){
                  triangles_array = 2;
                }else if(triangles_array == 2){
                  triangles_array = 1;
                }else{
                  triangles_array = 3;
                }
                glutPostRedisplay();
                break;
          case 'v':
          case 'V':
                if(type_primitive == GL_TRIANGLES){
                  type_primitive = GL_POINTS;
                }else{
                  type_primitive = GL_TRIANGLES;
                }
                glutPostRedisplay();
                break;
          case 'f':
          case 'F':
                if(type_polygon == GL_FILL){
                  type_polygon = GL_LINE;                 
                }else{
                  type_polygon = GL_FILL;
                }
                glPolygonMode(GL_FRONT_AND_BACK, type_polygon);
                glutPostRedisplay();
                break;
          case '1':
            type_primitive = GL_POINTS;
            glutPostRedisplay();
            break;
          case '2':
            type_primitive = GL_LINES;
            glutPostRedisplay();
            break;
          case '3':
            type_primitive = GL_LINE_STRIP;
            glutPostRedisplay();
            break;
          case '4':
            type_primitive = GL_LINE_LOOP;
            glutPostRedisplay();
            break;
          case '5':
            type_primitive = GL_TRIANGLES;
            glutPostRedisplay();
            break;
          case '6':
            type_primitive = GL_TRIANGLE_STRIP;
            glutPostRedisplay();
            break;
          case '7':
            type_primitive = GL_TRIANGLE_FAN;
            glutPostRedisplay();
            break;
          case 'w':
          case 'W':
            deslocamentoY += 0.1f;
            glutPostRedisplay();
            break;
          case 's':
          case 'S':
            deslocamentoY -= 0.1f;
            glutPostRedisplay();
            break;
          case 'd':
          case 'D':
            deslocamentoX += 0.1f;
            glutPostRedisplay();
            break;
          case 'a':
          case 'A':
            deslocamentoX -= 0.1f;
            glutPostRedisplay();
            break;
          case 'p':
          case 'P':
            angle += angle_inc; 
            glutPostRedisplay();
            break;
          case 'n':
          case 'N':
            angle -= angle_inc;
            glutPostRedisplay();
            break;
          case 'i':
          case 'I':
            scale += 0.1f; 
            glutPostRedisplay();
            break;
          case 'o':
          case 'O':
            scale -= 0.1f; 
            glutPostRedisplay();
            break;
          case 'g':
          case 'G':
           
            step++;
    
            glutPostRedisplay();
            break;
        }
}

/**
 * Init vertex data.
 *
 * Defines the coordinates for vertices, creates the arrays for OpenGL.
 */

void initData()
{

    // Vertex array.
    float vertices[] = { 
    -0.9f, 0.9f, 0.0f, 1.0f, 0.1f, 0.1f,
    -0.9f, 0.8f, 0.0f,  1.0f, 0.1f, 0.1f,
    -0.8f, 0.8f, 0.0f, 1.0f, 0.1f, 0.1f,
    -0.9f, 0.9f, 0.0f, 1.0f, 0.1f, 0.1f,
    -0.8f, 0.9f, 0.0f, 1.0f, 0.1f, 0.1f,
    -0.8f, 0.8f, 0.0f,  1.0f, 0.1f, 0.1f,
     };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    
    // Desabilita VAO	
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}

/** Create program (shaders).
 * 
 * Compile shaders and create the program.
 */
void initShaders()
{
    // Request a program and shader slots from GPU
    program  = glCreateProgram();
    int vertex   = glCreateShader(GL_VERTEX_SHADER);
    int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Set shaders source
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compile shaders
    glCompileShader(vertex);
    glCompileShader(fragment);

    // Attach shader objects to the program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Link the program
    glLinkProgram(program);

    // Get rid of shaders (not needed anymore)
    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    // Set the program to be used.
    glUseProgram(program);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width,win_height);
	glutCreateWindow("Bellman Ford");
	glewExperimental = GL_TRUE; 
	glewInit();

	// Init vertex data for the triangle.
	initData();

	// Create shaders.
	initShaders();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}
