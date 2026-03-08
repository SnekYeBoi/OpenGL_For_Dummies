/* this is a basic setup on using opengl;
i will be using mingw builder and compiler for cpp, 
and using the automatic tasks.json to output the build commands.
for the tools im using to access the opengl library/api , these include :

-GLAD (a helper library that is an opengl-function loader/generator)
-glfw (a powerfull helper library for opengl and other graphics libraries)
      (it provides basic window support and a simple api for creating context and surfaces),
      (as well as an input & output system)
-imGui(a great tool for implementing user interface on the program so we can edit the engine on runtime)
-stb_image (a tool used for importing images)

i will be explaining the setup in a step-by-step method */


//--------(THE INCLUDES)---------// :- any include comment with a * means its not neccessairy for the setup

//the default includes
#include <iostream>
#include <cmath>
#include <algorithm>

//*imgui and the glfw and opengl3 implementations of imgui (hence the impl)
#include <imGui/imgui.h>
#include <imGui/imgui_impl_glfw.h>
#include <imGui/imgui_impl_opengl3.h>

//glad and glfw version 3
#include <glad/glad.h>
#include <glfw/glfw3.h>

//*stb image implementation 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//a resize function for glfw for the frame buffer size callback
void resize(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height); //a function for explaining the resolution that opengl can draw on (viewport)
}

int main(){

    /*OPEN_GL IS MOSTLY A FINITE STATE MACHINE , any change you make is represented in states , that means:
    in peusodo code, we can say:
    -changeplayer(status,happy)
    -changesettings(brightness,high)
    as well as binding too but well get to that later...*/

    //impl glfw and its context version and set profile to core
    glfwInit(); //a function to activate glfw (glad needs no activation niether is open_gl)


    //glfw needs to know its opengl version , versions are indicated by MAJOR and MINOR.
    //for example if we want version 2.1 , the MAJOR is 2 while the MINOR is 1,for now we'll use 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //opengl has many profiles depending on the enviorment, for this we want the big CORE profile
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //make a window and set it to current context , a glfw window must be initialized as a pointer
    //probably because windows are dynamically allocated in the heap

    //the resolution you set to the window is the resolution openGL MUST FOLLOW
    //that can condratict with glviewport() which results in stretching (which is whats intented)
    GLFWwindow* window = glfwCreateWindow(800,600,"hello world",NULL,NULL);
    glfwMakeContextCurrent(window); //this is important to let opengl know which window to operate on

    /* load glad to work with glfw
    to do this we need to understand what glad needs , it needs the loading proceedure

    glfw has the loading proceedure in the form of void addresses
    but glad needs the specific datatype called GLADloadproc,

    and it turns out that the data stored in the glfw proc address 
    match perfectly with the gladloadproc datatype

    so we can do a c_type casting to convert the address into the intended datatype */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ //we call the function inside the condition
        //that trick helps load opengl functions while checking if the function returned false
        //(which means an error occured)
        std::cout << "fail";
        return -1;
    }

    //any updates in the frame buffer size runs the resize function (aka: the window scaled up or down)
    glfwSetFramebufferSizeCallback(window,resize);

    //setting up imgui first by checking version and then creating context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    //setting up the input output by initializing the io type and getting the io
    //use void casting to avoid unused warnings
    ImGuiIO& io = ImGui::GetIO();(void)io;

    //set the style color to dark
    ImGui::StyleColorsDark();
    
    //implment imgui in glfw and opengl by passing the window and version
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330"); 

    float color[3];

    while(!glfwWindowShouldClose(window)){

        //make a tab of imgui and inform opengl/glfw of that (tabs here are called frames)
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //you can now add imgui elements to the frame
        ImGui::Begin("hallo :3");
        ImGui::Text("welcom to my engine new UI !!!111!!!");
        ImGui::Text("tahya masr wooooooo!!!!");
        ImGui::ColorEdit3("Color",color);
        ImGui::End();
        //after ending you need to specifiy imgui that youre going to render the frames
        ImGui::Render();
        //now to send the frame data to opengl impl so it can render it (pass draw data as in argument)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //now we swap the empty buffer with our new frame drawn buffer
        glfwSwapBuffers(window);
        //clear the buffer to draw new frames/change existing ones
        glClearColor(color[0],color[1],color[2],1);
        glClear(GL_COLOR_BUFFER_BIT);
        //poll events to check for any input changes/resizes
        glfwPollEvents();

    }

    //shut down everything ,terminate glfw and destroy imgui's context
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
/*if you are confident with the setup you made 
 make sure to rewrite it without looking too much at this script*/