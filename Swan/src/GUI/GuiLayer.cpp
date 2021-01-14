#include "pch.h"
#include "GuiLayer.h"

#include <glad/glad.h>
#include "Base/Application.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>


#define INCLUDE_STYLE
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include <nuklear.h>
#include <nuklear_glfw_gl3.h>
#include <style.c>


#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

namespace Swan
{
    NuklearLayer::NuklearLayer()
    {
        /* Platform */
        m_Glfw = malloc(sizeof(nk_glfw{0}));
        struct nk_glfw* glfw = (nk_glfw*)m_Glfw;

        GLFWwindow *win;
        int width = 0, height = 0;
        struct nk_colorf bg;

        win = (GLFWwindow*)Application::GetApp()->GetWindow()->GetNativeWindow();

        glfwGetWindowSize(win, &width, &height);

        m_Ctx = nk_glfw3_init(glfw, win, NK_GLFW3_INSTALL_CALLBACKS);
        auto ctx = (nk_context*)m_Ctx;

        {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(glfw, &atlas);
        //struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "./Swan/vendor/Nuklear/extra_font/Cousine-Regular.ttf", 14, 0);
        /*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
        /*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
        /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
        /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
        //struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "./Swan/vendor/Nuklear/extra_font/Cousine-Regular.ttf", 13, 0);
        nk_glfw3_font_stash_end(glfw);
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        //nk_style_set_font(ctx, &cousine->handle);
        }

        
        set_style(ctx, THEME_WHITE);
        /*set_style(ctx, THEME_RED);*/
        /*set_style(ctx, THEME_BLUE);*/
        /*set_style(ctx, THEME_DARK);*/

        //bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    }

    NuklearLayer::~NuklearLayer()
    {
        nk_glfw3_shutdown((nk_glfw*)m_Glfw);
    }

    void NuklearLayer::OnAttach()
    {
        
    }
    void NuklearLayer::OnDetach()
    {
        nk_glfw3_shutdown((nk_glfw*)m_Glfw);
    }
    // void NuklearLayer::OnUpdate(Timestep ts)
    // {
    //     // struct nk_colorf bg;
    //     // bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    //     // auto ctx = static_cast<nk_context*>(m_Ctx);
    //     // /* GUI */
    //     // if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
    //     //     NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
    //     //     NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    //     // {
    //     //     enum {EASY, HARD};
    //     //     static int op = EASY;
    //     //     static int property = 20;
    //     //     nk_layout_row_static(ctx, 30, 80, 1);
    //     //     if (nk_button_label(ctx, "button"))
    //     //         fprintf(stdout, "button pressed\n");

    //     //     nk_layout_row_dynamic(ctx, 30, 2);
    //     //     if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
    //     //     if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

    //     //     nk_layout_row_dynamic(ctx, 25, 1);
    //     //     nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

    //     //     nk_layout_row_dynamic(ctx, 20, 1);
    //     //     nk_label(ctx, "background:", NK_TEXT_LEFT);
    //     //     nk_layout_row_dynamic(ctx, 25, 1);
    //     //     if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
    //     //         nk_layout_row_dynamic(ctx, 120, 1);
    //     //         bg = nk_color_picker(ctx, bg, NK_RGBA);
    //     //         nk_layout_row_dynamic(ctx, 25, 1);
    //     //         bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
    //     //         bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
    //     //         bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
    //     //         bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
    //     //         nk_combo_end(ctx);
    //     //     }
    //     // }
    //     // nk_end(ctx);
    // }
    void NuklearLayer::Begin()
    {
        nk_glfw3_new_frame((nk_glfw*)m_Glfw);
    }
    void NuklearLayer::End()
    {
        nk_glfw3_render((nk_glfw*)m_Glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
    }


    ImGuiLayer::ImGuiLayer()
    {

    }
    ImGuiLayer::~ImGuiLayer()
    {

    }

    void ImGuiLayer::OnAttach()
    {
        const char* glsl_version = "#version 130";
        GLFWwindow* win = (GLFWwindow*)Application::GetApp()->GetWindow()->GetNativeWindow();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(win, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'docs/FONTS.txt' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);
    }
    void ImGuiLayer::OnDetach()
    {

    }
    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
       
    }
    void ImGuiLayer::End()
    {
        ImGui::Render();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        GLFWwindow* win = (GLFWwindow*)Application::GetApp()->GetWindow()->GetNativeWindow();
        int display_w, display_h;
        glfwGetFramebufferSize(win, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        //glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        //glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    	
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}