
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Create the main rendering window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

    // Load the sprite image from a file
    sf::Image* Image = new sf::Image(60,60);
    for(int i=0;i<60;i++) Image->SetPixel(i,i,sf::Color::Red);

    // Create the sprite
    sf::Sprite* Sprite = new sf::Sprite(*Image);


    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // Get elapsed time
        float ElapsedTime = App.GetFrameTime();

        // Move the sprite
        if (App.GetInput().IsKeyDown(sf::Key::Left))  Sprite->Move(-100 * ElapsedTime, 0);
        if (App.GetInput().IsKeyDown(sf::Key::Right)) Sprite->Move( 100 * ElapsedTime, 0);
        if (App.GetInput().IsKeyDown(sf::Key::Up))    Sprite->Move(0, -100 * ElapsedTime);
        if (App.GetInput().IsKeyDown(sf::Key::Down))  Sprite->Move(0,  100 * ElapsedTime);

        // Rotate the sprite
        if (App.GetInput().IsKeyDown(sf::Key::Add))      Sprite->Rotate(- 100 * ElapsedTime);
        if (App.GetInput().IsKeyDown(sf::Key::Subtract)) Sprite->Rotate(+ 100 * ElapsedTime);

        // Clear screen
        App.Clear();

        // Display sprite in our window
        App.Draw(*Sprite);

        // Display window contents on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}

