#pragma once

#include <cstdio>
#include <vector>
#include <cstdio>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "fps.hpp"
#include "canvas.hpp"
#include "helpers.hpp"

class Application
{
private:
    enum class State
    {
        LINE_CHOOSEN,
        LINE_FROM,
        LINE_TO,
        LINE_DONE,
    };

    sf::RenderWindow* window;
    sf::Clock clock;
    FPS fps;
    Canvas* canvas;
    State state;

public:
    Application(const unsigned int window_width, const unsigned int window_height,
        sf::String title)
    {
        this->window = new sf::RenderWindow(sf::VideoMode(window_width, window_height, 32),
            title);
        // 100 FPS should be enough
        this->window->setFramerateLimit(60);
        ImGui::SFML::Init(*(this->window));
    }

    ~Application()
    {
        ImGui::SFML::Shutdown();
        delete this->canvas;
        delete this->window;
    }

    void dispatch()
    {
        sf::Event event{};

        this->canvas = new Canvas(800, this->window->getSize().y);
        this->canvas->setPosition(200, 0);

        sf::Clock delta_clock;
        while (this->window->isOpen())
        {
            fps.start();

            while (this->window->pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);

                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }
            }

            this->window->clear();

            ImGui::SFML::Update(*(this->window), delta_clock.restart());

            float main_menu_bar_height = 0;
            // Main menu
            if (ImGui::BeginMainMenuBar())
            {
                main_menu_bar_height = ImGui::GetWindowHeight();
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open"))
                    {
                        char const* filter_pattern[1] = { "*.png" };
                        char const* file_name = tinyfd_openFileDialog(
                            "Open file",
                            nullptr,
                            1,
                            filter_pattern,
                            "PNG",
                            false);
                        this->canvas->load(file_name);
                    }
                    if (ImGui::MenuItem("Save"))
                    {
                        char const* filter_pattern[1] = { "*.png" };
                        char default_file_name[22];
                        defaultPNGFilename(default_file_name);
                        char const* file_name = tinyfd_saveFileDialog(
                            "Save file",
                            default_file_name,
                            1,
                            filter_pattern,
                            "PNG");
                        this->canvas->save(file_name);
                    }
                    if (ImGui::MenuItem("Close"))
                    {
                        this->window->close();
                    }
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
            // End main menu

            ImGui::SetNextWindowPos(ImVec2(0, main_menu_bar_height));
            if (ImGui::Begin("Toolbox", nullptr,
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                if (ImGui::BeginTabBar("#tab_toolbox"))
                {
                    if (ImGui::BeginTabItem("Shape"))
                    {
                        int my_image_width = 0;
                        int my_image_height = 0;
                        GLuint my_image_texture = 0;
                        bool ret = LoadTextureFromFile("../assets/line.png", &my_image_texture, &my_image_width, &my_image_height);
                        ImGui::Image((uintptr_t)my_image_texture, ImVec2(32, 32));
                        ImGui::Button("Test");
                    }
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
                if (ImGui::CollapsingHeader("Color", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    float rgba[3];
                    ImGui::ColorEdit3("Color", rgba);
                }
            }
            ImGui::End();

            // Begin canvas draw

//            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*(this->window));
//            auto l = shape::Line::from(300, 300).to(mouse_pos.x - 200, mouse_pos.y).build();
//            auto l = shape::Line::from(300, 300).to(500, 500).build();
//            this->canvas->drawShape(&l);

            // End canvas draw

            // TODO
            // Shouldn't be call this, it should be done automatically
            // when the canvas was drawn
            this->canvas->update();

            this->window->draw(*(this->canvas));
            this->window->draw(fps);

            ImGui::SFML::Render(*(this->window));
            this->window->display();
        }
    }
};