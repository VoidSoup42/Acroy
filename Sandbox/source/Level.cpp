#include "Level.hpp"
#include "Renderer/Renderer.hpp"

void Level::Load()
{
    // ----------------------------------------
    // -------------- Ground ------------------
    // ----------------------------------------

    float planeVertices[] = {
        // positions          // normals         // texcoords
        -150.0f, 0.0f, -150.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         150.0f, 0.0f, -150.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         150.0f, 0.0f,  150.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -150.0f, 0.0f,  150.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    uint32_t planeIndices[] = { 0, 1, 2, 2, 3, 0 };

    m_groundVertexArray = Acroy::CreateRef<Acroy::VertexArray>();

    Acroy::Ref<Acroy::VertexBuffer> groundVertexBuffer = Acroy::CreateRef<Acroy::VertexBuffer>(planeVertices, sizeof(planeVertices));

    Acroy::BufferLayout layout = {
        { "a_position", Acroy::ShaderDataType::Float3, false },
        { "a_normal", Acroy::ShaderDataType::Float3, false },
        { "a_texCoord", Acroy::ShaderDataType::Float2, false }
    };

    groundVertexBuffer->SetLayout(layout);

    m_groundVertexArray->AddVertexBuffer(groundVertexBuffer);

    Acroy::Ref<Acroy::IndexBuffer> groundIndexBuffer = Acroy::CreateRef<Acroy::IndexBuffer>(planeIndices, sizeof(planeIndices) / sizeof(uint32_t));
    m_groundVertexArray->SetIndexBuffer(groundIndexBuffer);

    m_groundTexture = Acroy::CreateRef<Acroy::Texture2D>("/home/sam/Downloads/Grass008_2K-JPG/Grass008_2K-JPG_Color.jpg");



    // ----------------------------------------
    // -------------- Cube --------------------
    // ----------------------------------------

    float cubeVertices[] = {
    //  Positions           Normals       TextureCoords
        // Front
       -0.5, -0.5,  0.5,    0,  0,  1,    0, 0,
        0.5, -0.5,  0.5,    0,  0,  1,    1, 0,
        0.5,  0.5,  0.5,    0,  0,  1,    1, 1,
       -0.5,  0.5,  0.5,    0,  0,  1,    0, 1,
        // Back
       -0.5, -0.5, -0.5,    0,  0, -1,    1, 0,
        0.5, -0.5, -0.5,    0,  0, -1,    0, 0,
        0.5,  0.5, -0.5,    0,  0, -1,    0, 1,
       -0.5,  0.5, -0.5,    0,  0, -1,    1, 1,
        // Left
       -0.5, -0.5, -0.5,   -1,  0,  0,    0, 0,
       -0.5, -0.5,  0.5,   -1,  0,  0,    1, 0,
       -0.5,  0.5,  0.5,   -1,  0,  0,    1, 1,
       -0.5,  0.5, -0.5,   -1,  0,  0,    0, 1,
        // Right
        0.5, -0.5, -0.5,    1,  0,  0,    1, 0,
        0.5, -0.5,  0.5,    1,  0,  0,    0, 0,
        0.5,  0.5,  0.5,    1,  0,  0,    0, 1,
        0.5,  0.5, -0.5,    1,  0,  0,    1, 1,
        // Top
       -0.5,  0.5, -0.5,    0,  1,  0,    0, 1,
       -0.5,  0.5,  0.5,    0,  1,  0,    0, 0,
        0.5,  0.5,  0.5,    0,  1,  0,    1, 0,
        0.5,  0.5, -0.5,    0,  1,  0,    1, 1,
        // Bottom
       -0.5, -0.5, -0.5,    0, -1,  0,    1, 1,
       -0.5, -0.5,  0.5,    0, -1,  0,    1, 0,
        0.5, -0.5,  0.5,    0, -1,  0,    0, 0,
        0.5, -0.5, -0.5,    0, -1,  0,    0, 1
    };

    uint32_t cubeIndices[] = {
        0,1,2,2,3,0,    4,5,6,6,7,4,
        8,9,10,10,11,8, 12,13,14,14,15,12,
        16,17,18,18,19,16, 20,21,22,22,23,20
    };

    m_cubeVertexArray = Acroy::CreateRef<Acroy::VertexArray>();

    Acroy::Ref<Acroy::VertexBuffer> cubeVertexBuffer = Acroy::CreateRef<Acroy::VertexBuffer>(cubeVertices, sizeof(cubeVertices));
    cubeVertexBuffer->SetLayout(layout);

    m_cubeVertexArray->AddVertexBuffer(cubeVertexBuffer);
    
    Acroy::Ref<Acroy::IndexBuffer> cubeIndexBuffer = Acroy::CreateRef<Acroy::IndexBuffer>(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t));
    m_cubeVertexArray->SetIndexBuffer(cubeIndexBuffer);
 
    m_cubeTexture = Acroy::CreateRef<Acroy::Texture2D>("/home/sam/Documents/dev/OpenGL-Sandbox-main/resources/textures/Planks/planks.png");
    m_cubeTransform = glm::translate(m_cubeTransform, glm::vec3(0.0, 1.0, 0.0));
    m_cubeTransform = glm::scale(m_cubeTransform, glm::vec3(2.0f));



    // ----------------------------------------
    // -------------- Shader ------------------
    // ----------------------------------------

    std::string vertexSrc = R"(
        #version 460 core
        layout(location = 0) in vec3 a_position;
        layout(location = 1) in vec3 a_normal;
        layout(location = 2) in vec2 a_texCoord;

        uniform mat4 u_model;
        uniform mat4 u_view;
        uniform mat4 u_proj;
        out vec2 v_texCoord;

        void main()
        {
            gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0);
            v_texCoord = a_texCoord;
        }
    )";

    std::string fragSrc = R"(
        #version 460 core

        out vec4 FragColor;
        in vec2 v_texCoord;

        uniform sampler2D u_texture;
        uniform float u_textureScale;

        void main()
        {
            FragColor = texture(u_texture, v_texCoord * u_textureScale);
        }
    )";

    m_shader = Acroy::CreateRef<Acroy::Shader>(vertexSrc, fragSrc);

    m_shader->Bind();
    m_shader->SetUniformInt("u_texture", 0);
}

void Level::Update(Acroy::Timestep timestep)
{
    m_groundTexture->Bind(0);
    m_shader->SetUniformFloat("u_textureScale", 150.0f);
    Acroy::Renderer::Submit(m_groundVertexArray, m_shader, m_groundTransform);

    m_cubeTexture->Bind(0);
    m_shader->SetUniformFloat("u_textureScale", 2.0f);
    Acroy::Renderer::Submit(m_cubeVertexArray, m_shader, m_cubeTransform);
}