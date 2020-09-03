#include "Window.h"
#include "../../Resources/Image/PixelArray/PixelArray.h"
#include "../../Resources/Image/PixelArray/PixelArrayLoader.h"
#include "../../Resources/Font/BitMapFont/BitMapFontLoader.h"


Window* Window::_instance;

void Window::UpdateInput()
{
    KeyBoard* keyboard = &Input.KeyBoardInput;
    Mouse* mouse = &Input.MouseInput;

    if (keyboard->Letter.W)
    {
        _camera.Move(Direcion::Forward);
    }

    if (keyboard->Letter.A)
    {
        _camera.Move(Direcion::Left);
    }

    if (keyboard->Letter.S)
    {
        _camera.Move(Direcion::Backward);
    }

    if (keyboard->Letter.D)
    {
        _camera.Move(Direcion::Right);
    }

    if (keyboard->SpaceBar)
    {
        _camera.Move(Direcion::Up);
    }

    if (keyboard->FunktionKey.ShitftLeft)
    {
        _camera.Move(Direcion::Down);
    }

    if (keyboard->Letter.R)
    {
        bool axisEnabled = mouse->EnableInputAxis;

        if (axisEnabled)
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        mouse->EnableInputAxis = !axisEnabled;
    }

    /*
    if (window->KeyBoardInput->Letter.F)
    {
        camera->Settings->Mode = camera->Settings->Mode == CameraMode::Perspectdive ? CameraMode::Orthographic : CameraMode::Perspectdive;
    }*/

    _camera.Rotate(mouse->InputAxis.X, mouse->InputAxis.Y);

    mouse->ResetAxis();
}

Window* Window::GetInstance()
{
    return _instance;
}

Window::Window()
{
    _instance = this;
    Exit = false;

    if (!Create(400, 500, "[N/A]"))
    {
        printf("Error loading window\n");
    }

    glfwSetTime(0);
}

Window::Window(const int width, const int height, const char* title)
{
    _instance = this;
    Exit = false;

    if (!Create(width, height, title))
    {
        printf("Error loading window\n");
    }

    glfwSetTime(0);
}

Window::~Window()
{
    float cx = TimeCollection::ActiveTime;

    if (cx >= 60)
    {
        printf("Window was active for : %.2fm\n", cx / 60.0f);
    }
    else
    {
        printf("Window was active for : %.2fs\n", cx);
    }

    glfwTerminate();
}

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* currentWindow = Window::GetInstance();
    KeyBoard* keyBoard = &currentWindow->Input.KeyBoardInput;

    /* [key]
        The key will be GLFW_KEY_UNKNOWN
    */

    /* [action]
    0 = GLFW_RELEASE
    1 = GLFW_PRESS
    2 = GLFW_REPEAT
    */

    /* [mods]
    GLFW_STICKY_KEYS "Caps"
    GLFW_LOCK_KEY_MODS "NumPad"
    */

    switch (key)
    {
    case GLFW_KEY_A: keyBoard->Letter.A = action; break;
    case GLFW_KEY_B: keyBoard->Letter.B = action; break;
    case GLFW_KEY_C: keyBoard->Letter.C = action; break;
    case GLFW_KEY_D: keyBoard->Letter.D = action; break;
    case GLFW_KEY_E: keyBoard->Letter.E = action; break;
    case GLFW_KEY_F: keyBoard->Letter.F = action; break;
    case GLFW_KEY_G: keyBoard->Letter.G = action; break;
    case GLFW_KEY_H: keyBoard->Letter.H = action; break;
    case GLFW_KEY_I: keyBoard->Letter.I = action; break;
    case GLFW_KEY_J: keyBoard->Letter.J = action; break;
    case GLFW_KEY_K: keyBoard->Letter.K = action; break;
    case GLFW_KEY_L: keyBoard->Letter.L = action; break;
    case GLFW_KEY_M: keyBoard->Letter.M = action; break;
    case GLFW_KEY_N: keyBoard->Letter.N = action; break;
    case GLFW_KEY_O: keyBoard->Letter.O = action; break;
    case GLFW_KEY_P: keyBoard->Letter.P = action; break;
    case GLFW_KEY_Q: keyBoard->Letter.Q = action; break;
    case GLFW_KEY_R: keyBoard->Letter.R = action; break;
    case GLFW_KEY_S: keyBoard->Letter.S = action; break;
    case GLFW_KEY_T: keyBoard->Letter.T = action; break;
    case GLFW_KEY_U: keyBoard->Letter.U = action; break;
    case GLFW_KEY_V: keyBoard->Letter.V = action; break;
    case GLFW_KEY_W: keyBoard->Letter.W = action; break;
    case GLFW_KEY_X: keyBoard->Letter.X = action; break;
    case GLFW_KEY_Y: keyBoard->Letter.Y = action; break;
    case GLFW_KEY_Z: keyBoard->Letter.Z = action; break;


        // Fuction Keys
    case GLFW_KEY_LEFT_SHIFT: keyBoard->FunktionKey.ShitftLeft = action; break;
    case GLFW_KEY_SPACE: keyBoard->SpaceBar = action; break;

    }
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    Window* currentWindow = Window::GetInstance();
    Mouse* mouse = &currentWindow->Input.MouseInput;

    /*
    0 = GLFW_MOUSE_BUTTON_1 | GLFW_MOUSE_BUTTON_LEFT
    1 = GLFW_MOUSE_BUTTON_2 | GLFW_MOUSE_BUTTON_RIGHT
    2 = GLFW_MOUSE_BUTTON_3 | GLFW_MOUSE_BUTTON_MIDDLE
    3 = GLFW_MOUSE_BUTTON_4
    4 = GLFW_MOUSE_BUTTON_5
    5 = GLFW_MOUSE_BUTTON_6
    6 = GLFW_MOUSE_BUTTON_7
    7 = GLFW_MOUSE_BUTTON_8 | GLFW_MOUSE_BUTTON_LAST
    */

    switch (button)
    {
    case GLFW_MOUSE_BUTTON_1:
        mouse->LeftButton = action;
        break;

    case GLFW_MOUSE_BUTTON_2:
        mouse->RightButton = action;
        break;

    case GLFW_MOUSE_BUTTON_3:
        mouse->ScrollButton = action;
        break;

    case GLFW_MOUSE_BUTTON_4:
        mouse->CustomButton1 = action;
        break;

    case GLFW_MOUSE_BUTTON_5:
        mouse->CustomButton2 = action;
        break;

    case GLFW_MOUSE_BUTTON_6:
        mouse->CustomButton3 = action;
        break;

    case GLFW_MOUSE_BUTTON_7:
        mouse->CustomButton4 = action;
        break;

    case GLFW_MOUSE_BUTTON_8:
        mouse->CustomButton5 = action;
        break;
    }
}

void OnMousePosition(GLFWwindow* window, double xpos, double ypos)
{
    Window* currentWindow = Window::GetInstance();
    Mouse* mouse = &currentWindow->Input.MouseInput;

    if (mouse->EnableInputAxis)
    {
        mouse->InputAxis.X = mouse->Position.X - xpos;
        mouse->InputAxis.Y = mouse->Position.Y - ypos;

        // Clamp
        mouse->InputAxis.X = Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.X);
        mouse->InputAxis.Y = Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.Y);

        mouse->Position.X = xpos;
        mouse->Position.Y = ypos;
    }
}

void OnWindowSizeChanged(GLFWwindow* window, int _width, int _height)
{
    Window* currentWindow = Window::GetInstance();

    currentWindow->ResizeWindow(_width, _height);
}

void Window::ResizeWindow(const int width, const int height)
{
    bool hasChanged = _camera.Settings->Width != width || _camera.Settings->Height != height;

    if (hasChanged)
    {
        _camera.Settings->Width = width;
        _camera.Settings->Height = height;

        glViewport(0, 0, width, height);

        //glfwSetWindowSize(_window, width, height);
    }
}

bool Window::Create(const int width, const int height, const char* title)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return false;
    }

    /* Create a windowed mode window and its OpenGL context */
    {
        _window = glfwCreateWindow(width, height, title, NULL, NULL);
    }

    if (!_window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    if (glewInit() != GLEW_OK)
    {
        return false;
    }

    // SetCallBacks
    {
        glfwSetKeyCallback(_window, OnKeyPressed);
        glfwSetMouseButtonCallback(_window, OnMouseButton);
        glfwSetCursorPosCallback(_window, OnMousePosition);
        glfwSetWindowSizeCallback(_window, OnWindowSizeChanged);
        

    }

    /*
    GLFW_CURSOR_NORMAL
    GLFW_CURSOR_HIDDEN
    GLFW_CURSOR_DISABLED
    */

    // glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    {
        // Texture* text = TextureLoader::LoadTexture("C:/_WorkSpace/C++/Cursor.hex");

        PixelArray pixel = PixelArrayLoader::LoadFromFile("C:/_WorkSpace/C++/Data/O.hex");

        unsigned char height = 286;
        unsigned char width = 214;
        unsigned char* icon = new  unsigned char[height * width * 4]
        {
            0xFF, 0x00, 0x00, 0xFF,
                0x00, 0x00, 0xFF, 0xFF,
                0x00, 0x00, 0xFF, 0xFF,
                0xFF, 0x00, 0x00, 0xFF

        };

        GLFWimage image;
        image.width = width;
        image.height = height;
        image.pixels = pixel.PixelData;

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);


        // GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
        glfwSetCursor(_window, cursor);
    }


    if (false)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if (true)
    {
        glEnable(GL_DEPTH_TEST);
    }

    if (true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    glfwSwapInterval(1);
    _models = 2;
    _renderModel;
    //_renderB;

    //TriangleModel* tria = new TriangleModel();
    //RectangleModel* rect = new RectangleModel();

    //_renderModel[0] = *tria; 
    //_renderModel[1] = *rect;

   // WaveFront waveFront = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/QF.obj");

   // _renderModel.LoadFromWaveFront(waveFront);
     _renderModel = RectangleModel();




    Mesh* mesh = &_renderModel.VertexMeshList.at(0);



    mesh->GenerateArrayData();

    buffer.ChangeMesh(mesh);
    buffer.BindBuffer();





    //_renderB = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/S.obj");
    //_renderB->VertexMesh->GenerateArrayData();

 // _renderModel[0] = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/TigefffR.obj");
  //mod = WaveFrontLoader::LoadFromFile("C:/_WorkSpace/C++/Data/Q.obj");
//  mod->VertexMesh->GenerateArrayData();

// _renderModel = mod;





    return true;
}

float x;

void Window::Update()
{
    Exit = glfwWindowShouldClose(_window);

    if (Exit)
    {
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateInput();

    _camera.Update();


     glClearColor(0.2f, 0.2f, 0.2f, 1);


     //model = glm::rotate(model, 0.002f, glm::vec3(0, 1, 0));      

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(1,1.2,0));

    modelView = _camera._view * model;
    invModelView = glm::transpose(glm::inverse(modelView));

    std::string text = "Who is sample text?";

    for (size_t i = 0; i < text.size(); i++)
    {
        Mesh* mesh = &_renderModel.VertexMeshList.at(0);        
        BitMapFontCharacter bitMapFontCharacter = font.GetCharacterPosition( text.at(text.size() - 1 -i));

        float xoffset = Interpolate::Liniar(0, 1, 0, 512, bitMapFontCharacter.StartPosition.X);
        float yoffset = Interpolate::Liniar(0, 1, 0, 512, bitMapFontCharacter.StartPosition.Y);

        float xoffsetW = Interpolate::Liniar(0, 1, 0, 512, bitMapFontCharacter.StartPosition.X + bitMapFontCharacter.Size.X);
        float yoffsetW = Interpolate::Liniar(0, 1, 0, 512, bitMapFontCharacter.StartPosition.Y + bitMapFontCharacter.Size.Y);

        mesh->Vertices.at(0).TexturePoint = Point(1-xoffsetW, yoffset); // 0 0
        mesh->Vertices.at(1).TexturePoint = Point(1-xoffset, yoffset); // 1 0
        mesh->Vertices.at(2).TexturePoint =  Point(1-xoffset, yoffsetW); // 1 1
        mesh->Vertices.at(3).TexturePoint = Point(1-xoffsetW, yoffsetW); // 0 1
           
        mesh->GenerateArrayData();

        buffer.ChangeMesh(mesh);
        buffer.BindBuffer();

        unsigned int indsize = mesh->GetIndiceData()->Lengh;

        //buffer.ChangeMesh(mesh);

        int off = 6;
        int xOFF;
        int yOFF;


        glfwGetWindowPos(_window, &xOFF, &yOFF);

        x += 0.01f;

        xOFF += sin(x) * 100 * TimeCollection::DeltaTime;
        //yOFF += cos(i) * TimeCollection::DeltaTime;

        glfwSetWindowPos(_window, xOFF, yOFF);

        glm::mat4 diff = glm::translate(_camera._view, glm::vec3(i*1.0f, 0, 0));

        completematrix = _camera._projection * diff * model;

        glUniformMatrix4fv(_modelViewID, 1, GL_FALSE, &modelView[0][0]);
        glUniformMatrix4fv(_modelViewProjectionID, 1, GL_FALSE, &completematrix[0][0]);
        glUniformMatrix4fv(_inverseModelViewID, 1, GL_FALSE, &invModelView[0][0]);


        glDrawElements(GL_TRIANGLES, indsize, GL_UNSIGNED_INT, nullptr);
        //glDrawElements(GL_LINE_LOOP, indsize, GL_UNSIGNED_INT, nullptr);

         //buffer.UnBindBuffer();
    }

    glfwSwapBuffers(_window); /* Swap front and back buffers */
    glfwPollEvents();   /* Poll for and process events */

    TimeCollection::SetDeltaTimeStamp();
    TimeCollection::ActiveTime = glfwGetTime();
}

void Window::SetShader(ShaderFile shaderFile)
{
    shader = ShaderLoader::CreateShader(shaderFile.VertexShader.Content, shaderFile.FragmentShader.Content);

    glUseProgram(shader);

    _modelViewProjectionID = glGetUniformLocation(shader, "ModelViewProjection");
    _inverseModelViewID = glGetUniformLocation(shader, "ModelView");
    _modelViewID = glGetUniformLocation(shader, "InverseModelView");


    int is = glGetUniformLocation(shader, "texture");

    if (true)// Texture
    {
        unsigned int texture;
        glGenTextures(1, &texture);

        unsigned int width;
        unsigned int height;

        pixelarray = PixelArray();

        if (false)
        {
            pixelarray = PixelArrayLoader::LoadFromFile("C:/_WorkSpace/C++/Data/O.hex");
            width = 214;//774;
            height = 286;//  674;
        }
        else
        {
            font = BitMapFontLoader::LoadBitMapFont("C:/_WorkSpace/C++/Data/arial.fnt");
            boxTexture = BitMapLoader::LoadFromFile("C:/_WorkSpace/C++/Data/F/A.bmp");

            width = boxTexture.InformationHeader->Width;
            height = boxTexture.InformationHeader->Height;

            //BitMapLoader::PrintBitMapInformation(boxTexture);
            pixelarray = BitMapLoader::GeneratePixelArray(boxTexture);
        }

        //PixelArrayLoader::PrintPixelArray(pixelarray);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelarray.PixelData);
        glGenerateMipmap(GL_TEXTURE_2D);

    }

    _camera.Settings->Mode = CameraMode::Perspectdive;

    printf("SHADER ID %i | %i | %i | %i\n", shader, _modelViewProjectionID, _inverseModelViewID, _modelViewID);
    //printf("ModelViewProjection ID %i\n", modelViewMapos);    
}