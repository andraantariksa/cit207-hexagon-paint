#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdio>
#include <vector>
#include <cstdio>

#include "fps.hpp"
#include "canvas.hpp"

class Application
{
    private:
    sf::RenderWindow *window;
    sf::Clock clock;
    FPS fps;
    Canvas *canvas;

    public:
    Application(const unsigned int window_width, const unsigned int window_height,
        sf::String title)
    {
        this->window = new sf::RenderWindow(sf::VideoMode(window_width, window_height, 32),
            title);
        // 100 FPS should be enough
        this->window->setFramerateLimit(100);
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
        this->canvas = new Canvas(800, this->window->getSize().y);
        this->canvas->setPosition(200, 0);

        std::size_t move_x = 0;
        std::size_t move_y = 0;

        sf::Clock delta_clock;
        while (this->window->isOpen())
        {
            fps.start();

            sf::Event event;

            while (this->window->pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);

                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }

                if (event.key.code == sf::Keyboard::Right) {
                    move_x += 10;
                }

                if (event.key.code == sf::Keyboard::Left) {
                    move_x -= 10;
                }

                if (event.key.code == sf::Keyboard::Up) {
                    move_y -= 10;
                }

                if (event.key.code == sf::Keyboard::Down) {
                    move_y += 10;
                }
            }

            this->window->clear();

            ImGui::SFML::Update(*(this->window), delta_clock.restart());

            float main_menu_bar_height;
            // Main menu
            if (ImGui::BeginMainMenuBar())
            {
                main_menu_bar_height = ImGui::GetWindowHeight();
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open..", "Ctrl+O"))
                    {
                    }
                    if (ImGui::MenuItem("Save", "Ctrl+S"))
                    {
                    }
                    if (ImGui::MenuItem("Close", "Ctrl+W"))
                    {
                        this->window->close();
                    }
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
            // End main menu

            ImGui::SetNextWindowPos(ImVec2(0, main_menu_bar_height));
            if (ImGui::Begin("Toolbox", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
            {
                if (ImGui::BeginTabBar("#tab_toolbox"))
                {
                    if (ImGui::BeginTabItem("Shape"))
                    {
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


            this->canvas->clear();
            
            // Begin canvas draw
            
            std::vector<CanvasDrawable*> shapes;
            shape::Line down = shape::Line::from(400, 400)
                .to(400, 500)
                .build();
            shapes.push_back(&down);

            shape::Line rightdown = shape::Line::from(400, 400)
                .to(500, 500)
                .build();
            shapes.push_back(&rightdown);

            shape::Line leftdown = shape::Line::from(400, 400)
                .to(300, 500)
                .build();
            shapes.push_back(&leftdown);

            shape::Line right = shape::Line::from(400, 400)
                .to(500, 400)
                .build();
            shapes.push_back(&right);

            shape::Line rightup = shape::Line::from(400, 400)
                .to(500, 300)
                .build();
            shapes.push_back(&rightup);

            shape::Line leftup = shape::Line::from(400, 400)
                .to(300, 300)
                .build();
            shapes.push_back(&leftup);

            shape::Line up = shape::Line::from(400, 400)
                .to(400, 300)
                .build();
            shapes.push_back(&up);

            shape::Line left = shape::Line::from(400, 400)
                .to(300, 400)
                .build();
            shapes.push_back(&left);

            // Begin assignment box with dot in the center
            this->canvas->setPixel(75 + move_x, 75 + move_y, Color::Red());

            shape::Line line_right = shape::Line::from(100 + move_x, 50 + move_y)
                .to(100 + move_x, 100 + move_y)
                .build();
            shapes.push_back(&line_right);

            shape::Line line_left = shape::Line::from(50 + move_x, 100 + move_y)
                .to(50 + move_x, 50 + move_y)
                .build();
            shapes.push_back(&line_left);
            
            shape::Line line_bottom = shape::Line::from(50 + move_x, 100 + move_y)
                .to(100 + move_x, 100 + move_y)
                .build();
            shapes.push_back(&line_bottom);

            shape::Line line_top = shape::Line::from(50 + move_x, 50 + move_y)
                .to(100 + move_x, 50 + move_y)
                .build();
            shapes.push_back(&line_top);

            this->canvas->drawShapes(shapes);

            // End assignment box with dot in the center

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