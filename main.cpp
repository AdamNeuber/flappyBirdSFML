#include <SFML/Graphics.hpp>
#include <filesystem>
#include <cmath>
#include <vector>

int main()
{
    sf::Texture birdTexture;
    std::filesystem::path exeDir = std::filesystem::path().remove_filename();
    std::filesystem::path birdPath = exeDir / "assets/flepyGentlmen.png";

    birdTexture.loadFromFile(birdPath.string());

    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Flepy Brt");
    
    sf::RectangleShape hitbox;
    hitbox.setSize({50.f, 50.f});
    hitbox.setPosition({400.f, 100.f});

    sf::Sprite bird(birdTexture);

    float velocityY = 0.f;
    const float gravity = 0.7f;
    const float jumpStrength = -600.f;
    bool hasJumped = false;

    sf::Vector2 movement(0.f, velocityY);

    bird.setPosition({400.f, 100.f});
    bird.setScale({5.f, 5.f});
    bird.setOrigin({birdTexture.getSize().x / 2.f, birdTexture.getSize().y / 2.f});
    hitbox.setOrigin({birdTexture.getSize().x / 2.f, birdTexture.getSize().y / 2.f});

    sf::Clock clok;

    float wallWidth = 120.f;
    float wallHeight = 480.f;
    float vertOffsetD = 540.f;
    float vertOffsetU = -220.f;
    float spacing = 400.f;

    int numOfWalls = 5;

    std::vector<sf::RectangleShape>walls;

    sf::RectangleShape wallD ({wallWidth, wallHeight});
    sf::RectangleShape wallU ({wallWidth, wallHeight});

    for (size_t i = 0; i < numOfWalls; i++)
    {
        float random = (std::rand() % 400) - 200;

        wallD.setPosition({1100.f + spacing*i,vertOffsetD + random});
        wallD.setFillColor(sf::Color({22, 255, 0}));
        walls.push_back(wallD);
        
        wallU.setPosition({1100.f + spacing*i, vertOffsetU + random});
        wallU.setFillColor(sf::Color({22, 255, 0}));
        walls.push_back(wallU);
    }

    while (window.isOpen())
    {
    
        movement = {0.f, velocityY};

        float delta = clok.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !hasJumped) {
            velocityY = jumpStrength;
            hasJumped = true;
        }

         if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && hasJumped) {
            hasJumped = false;
        }

        velocityY = std::clamp(velocityY + gravity, -1000.f, 1000.f);
        
        bird.move(movement * delta);
        hitbox.setPosition(bird.getPosition());

        if(hitbox.getPosition().y >= 900.f || hitbox.getPosition().y < -100.f) {
            window.close();
        }

        for(size_t i = 0; i < walls.size(); i+=2) {
            walls[i].move(sf::Vector2f(-120.f, 0.f) * delta);
            walls[i+1].move(sf::Vector2f(-120.f, 0.f) * delta);
            if(walls[i].getPosition().x < -wallWidth) {
                float random = (std::rand() % 400) - 200;
                walls[i].setPosition({numOfWalls * spacing - wallWidth,vertOffsetD + random});
                walls[i+1].setPosition({numOfWalls * spacing - wallWidth,vertOffsetU + random});
            }
        }

        for(auto &wall : walls) {
            if(hitbox.getGlobalBounds().findIntersection(wall.getGlobalBounds()).has_value()) {
                window.close();
            }
        }
        

        window.clear(sf::Color{83, 255, 254});
        for (auto &wall : walls)
        {
            window.draw(wall);
        }
        window.draw(bird);
        window.display();
    }
}