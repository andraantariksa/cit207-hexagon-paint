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
        Nothing,
        LineFrom,
        LineTo,
        LineDone,
        PenDraw,
        PenIdle,
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

        sf::Image window_icon;
        window_icon.loadFromFile("../assets/icon-32x32.png");
        this->window->setIcon(32, 32, window_icon.getPixelsPtr());

        // 100 FPS should be enough
        this->window->setFramerateLimit(60);
        this->state = State::Nothing;
        ImGui::SFML::Init(*(this->window));
        ImGui::GetIO().IniFilename = nullptr;
    }

    ~Application()
    {
        ImGui::SFML::Shutdown();
        delete this->canvas;
        delete this->window;
    }

    void dispatch()
    {

        this->canvas = new Canvas(800, this->window->getSize().y);
        this->canvas->setPosition(sf::Vector2f(200, 0));

        sf::Clock delta_clock;
        sf::Event event{};
        bool line_is_dotted = false;
        int line_width_size = 1;
        float chosen_rgb_color[3] = {0, 0, 0};
        float main_menu_bar_height = 0;

        int my_image_width = 0;
        int my_image_height = 0;
        GLuint texture_icon_line = 0;
        GLuint texture_icon_pen = 0;
        LoadTextureFromFile("../assets/line.png", &texture_icon_line, &my_image_width, &my_image_height);
        LoadTextureFromFile("../assets/pen.png", &texture_icon_pen, &my_image_width, &my_image_height);

        int x1, y1, x2, y2;

        while (this->window->isOpen())
        {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(*this->window);
            Color chosen_color(chosen_rgb_color);

            fps.start();
            this->window->clear();

            while (this->window->pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);

                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }

                if (event.type == sf::Event::LostFocus)
                {
                    break;
                }

                if (mouse_position.x >= 200 && mouse_position.x <= 200 + this->canvas->getWidth()
                    && mouse_position.y >= 0 && mouse_position.y <= 0 + this->canvas->getHeight())
                {
                    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        if (this->state == State::PenDraw)
                        {
                            this->state = State::PenIdle;
                        }
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        if (this->state == State::PenIdle)
                        {
                            this->canvas->setPixel(mouse_position.x - 200, mouse_position.y, chosen_color);
                            x1 = mouse_position.x - 200;
                            y1 = mouse_position.y;
                            this->state = State::PenDraw;
                        }
                        else if (this->state == State::PenDraw)
                        {
                            shape::Line line = shape::Line::from(x1, y1)
                                .to(mouse_position.x - 200, mouse_position.y)
                                .withColor(chosen_color)
                                .build();
                            this->canvas->drawShape(&line);
                            x1 = mouse_position.x - 200;
                            y1 = mouse_position.y;
//                            this->canvas->setPixel(mouse_position.x - 200, mouse_position.y, chosen_color);
                            this->state = State::PenDraw;
                        }
                    }

                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (this->state == State::LineFrom)
                        {
                            x1 = mouse_position.x - 200;
                            y1 = mouse_position.y;
                            this->state = State::LineTo;
                        }
                        else if (this->state == State::LineTo)
                        {
                            this->canvas->alternateEnd();
                            auto line_pending = shape::Line::from(x1, y1)
                                .to(mouse_position.x - 200, mouse_position.y)
                                .withColor(chosen_color);

                            if (line_is_dotted)
                            {
                                shape::Line line_from_to_mouse_position = line_pending.isDotted(true).build();
                                this->canvas->drawShape(&line_from_to_mouse_position);
                            }
                            else
                            {
                                shape::Line line_from_to_mouse_position = line_pending.build();
                                this->canvas->drawShape(&line_from_to_mouse_position);
                            }

                            this->state = State::LineDone;
                        }
                    }
                }
            }

            if (this->canvas->isAlternateOn())
            {
                this->canvas->alternateFromMain();
            }

            ImGui::SFML::Update(*this->window, delta_clock.restart());

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
            ImGui::SetNextWindowSize(ImVec2(200, 300));
            if (ImGui::Begin("Toolbox", nullptr,
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                if (ImGui::BeginTabBar("#tab_toolbox"))
                {
                    if (ImGui::BeginTabItem("Shape"))
                    {
                        // Pen
                        if (ImGui::ImageButton(texture_icon_pen, ImVec2(32, 32)))
                        {
                            this->state = State::PenIdle;
                        }
                        if (ImGui::IsItemHovered())
                            ImGui::SetTooltip("Pen");

                        ImGui::SameLine();

                        // Line
                        if (ImGui::ImageButton(texture_icon_line, ImVec2(32, 32)))
                        {
                            this->canvas->alternateBegin();
                            this->state = State::LineFrom;
                        }
                        if (ImGui::IsItemHovered())
                            ImGui::SetTooltip("Line shape");
                    }
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();

                if (this->state == State::LineFrom || this->state == State::LineTo)
                {
                    if (ImGui::CollapsingHeader("Line Options", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        ImGui::Checkbox("Dotted", &line_is_dotted);

                        ImGui::SameLine();

                        ImGui::DragInt("Width", &line_width_size, 1.0, 1, 5, "%d px");
                    }
                }

                if (ImGui::CollapsingHeader("Color", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    ImGui::ColorEdit3("Color", chosen_rgb_color);
                }
                if (ImGui::CollapsingHeader("Layer Tools", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (ImGui::Button("Clear"))
                    {
                        this->canvas->clear();
                    }
                }
            }
            ImGui::End();


            if (mouse_position.x >= 200 && mouse_position.x <= 200 + this->canvas->getWidth()
                && mouse_position.y >= 0 && mouse_position.y <= this->canvas->getHeight())
            {
                if (this->state == State::LineTo)
                {
                    auto line_pending = shape::Line::from(x1, y1)
                        .to(mouse_position.x - 200, mouse_position.y)
                        .withColor(chosen_color);

                    if (line_is_dotted)
                    {
                        shape::Line line_from_to_mouse_position = line_pending.isDotted(true).build();
                        this->canvas->drawShape(&line_from_to_mouse_position);
                    }
                    else
                    {
                        shape::Line line_from_to_mouse_position = line_pending.build();
                        this->canvas->drawShape(&line_from_to_mouse_position);
                    }
                }
            }

            // Begin canvas draw

//            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*(this->window));
//            auto l = shape::Line::from(300, 300).to(mouse_pos.x - 200, mouse_pos.y).build();
//            auto l = shape::Line::from(300, 300).to(500, 500).build();
//            this->canvas->drawShape(&l);

            // End canvas draw

            if (this->canvas->isAlternateOn())
            {
                this->canvas->alternateUpdate();
            }
            else
            {
                this->canvas->update();
            }

            this->window->draw(*this->canvas);
            this->window->draw(fps);

            ImGui::SFML::Render(*this->window);
            this->window->display();
        }
    }
};