////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp> //this was added
#include<Windows.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <ctime>




//this seems to be getting the sprites and then returning the sprite

sf::Sprite displayImage(std::string input, sf::Texture &texture)
{

	
	if (!texture.loadFromFile( input  + ".bmp"))
	{
		std::cout << "Image " << input << ".bmp failed to load\n"; 


        texture.loadFromFile("error.bmp"); 




	}


	sf::Sprite sprite;
	sprite.setTexture(texture);

    return sprite; 





}

void  Listmaker(std::list <std::string> &flags)
{

    

    std::string filename = "event_names.txt"; //gonna have to change to ktp


    std::string line;
    std::ifstream file(filename);

    if (file.is_open())
    {

        while (std::getline(file, line))
        {

            flags.push_back(line);


        }

    }
    else
    {

        std::cout << "error unable to read\n";

    }


    file.close();


    /*for (auto i : flags)
        std::cout << i << std::endl;*/


    


}

void textSetter(std::string input, sf::Text& text, sf::Font& font, int textposXChoice, sf::Color color)
{




    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString(input);

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);



    if (textposXChoice == 1)
    {

        text.setPosition(20.f, 780.f);


    }
    else if (textposXChoice == 2)
    {

        // set the color
        text.setFillColor(sf::Color::Blue);


        text.setPosition(20.f, 810.f);


    }
    else if (textposXChoice == 3)
    {

        text.setFillColor(sf::Color::Green);
        text.setPosition(20.f, 840.f);



    }
    else if (textposXChoice == 4)
    {
        text.setFillColor(sf::Color::Magenta);
        text.setPosition(20.f, 870.f);



    }
    else
    {

        // set the string to display
        text.setString("error");

        // set the character size
        text.setCharacterSize(24); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::Yellow);

        // set the text style
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);

        text.setPosition(20.f, 200.f);


    }






}





void wrongAnswers(std::string input, sf::Text& text, sf::Font& font,
    int textposXChoice, std::list <std::string> flags,
    std::list <std::string> correctanswers, int& wrongtextpos1, int& wrongtextpos2, int& wrongtextpos3)
{

    srand(time(0)); 



    while (wrongtextpos1 == textposXChoice)
    {
        wrongtextpos1 = rand() % 4 + 1;

        if (wrongtextpos1 != textposXChoice)
        {

            break; 

        }

    }

    while (wrongtextpos2 == textposXChoice || wrongtextpos2 == wrongtextpos1)
    {
        wrongtextpos2 = rand() % 4 + 1;

        if (wrongtextpos2 != textposXChoice && wrongtextpos2 != wrongtextpos1)
        {

            break;

        }

    }

    while (wrongtextpos3 == textposXChoice || wrongtextpos3 == wrongtextpos1 || wrongtextpos3 == wrongtextpos2)
    {
        wrongtextpos3 = rand() % 4 + 1;

        if (wrongtextpos3 != textposXChoice && wrongtextpos3 != wrongtextpos1 && wrongtextpos3 != wrongtextpos2)
        {

            break;

        }

    }
   

  

}











int main()
{
	
    std::string input = "test2";
    sf::Texture texture;
    sf::Color color = sf::Color::Red; 

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "FlagGuesser");
    
    int prevtextpos = 0; 

    int points = 100;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
        }

        window.clear();

        
        

        std::list <std::string> flags; 
        std::list <std::string> correctanswers; 

        Listmaker(flags); 


        
        srand(time(0)); 

        //auto jk = rand() % flags.size() + 1; 

        std::list<std::string>::iterator iter = flags.begin();
        std::string correctanswerholder; 
  
        
        
        for (int uppy = 0; uppy < 20; uppy++)
        {
            
            if (uppy == 20)
            {

                window.close();
                break; 

            }

            auto jk = rand() % flags.size();
            

            



            advance(iter, jk);
            

            window.clear();

            window.draw(displayImage(*iter, texture));

            correctanswers.push_back(*iter); //loads the correct answer onto separate list



            sf::Font font;
            if (!font.loadFromFile("arial.ttf"))
            {
                std::cout << "font error\n";
            }

            sf::Text text;
            sf::Text wrong1, wrong2, wrong3; 



            int textposXChoice = rand() % 4 + 1;  //between 1 and 4 inclusive 
            
            while (prevtextpos != textposXChoice)
            {

                int textposXChoice = rand() % 4 + 1;  //between 1 and 4 inclusive 

                if (prevtextpos != textposXChoice)
                {
                    break; 

                }


            }




            textSetter(*iter, text, font, textposXChoice, color);

            window.draw(text);

            correctanswerholder = *iter; 


            //wrong answers don't trust iter after this line till end of for loop

            int wrongtextpos1 = 1;
            int wrongtextpos2 = 1; 
            int wrongtextpos3 = 1;


            

            



            wrongAnswers(*iter, text, font, textposXChoice, flags, 
                correctanswers, wrongtextpos1, wrongtextpos2, wrongtextpos3);


            color = sf::Color::Green; 
            iter = flags.begin();
            jk = rand() % flags.size();
            advance(iter, jk);
            textSetter(*iter, text, font, wrongtextpos1,color); 
            window.draw(text);


            color = sf::Color::Blue;
            iter = flags.begin();
            jk = rand() % flags.size();
            advance(iter, jk);
            textSetter(*iter, text, font, wrongtextpos2, color);
            window.draw(text);


            color = sf::Color::Magenta;
            iter = flags.begin();
            jk = rand() % flags.size();
            advance(iter, jk);
            textSetter(*iter, text, font, wrongtextpos3, color);
            window.draw(text);

            
            
            





            iter = flags.begin();
            prevtextpos = textposXChoice; //stores previous
            textposXChoice = 0; 

            


        }
        
        window.display();

        std::string repuesta; 


        std::cout << "What event or person do you think this is? \n"; 
        getline(std::cin, repuesta); 

        std::cout << "\n the correct answer was:  " << correctanswerholder << std::endl;


       

        std::cout << "Turn up your volume!!! \n"; 
        

        if (repuesta == correctanswerholder)
        {

            int win_points = rand() % 32; //this added

            std::cout << "\n YOU WON " << win_points << " POINTS! \n"; 

            points += win_points;
            std::cout << "\n Your score: " << points << std::endl; 

            
            int possible_sound = rand() % 3 + 1;

            if (possible_sound == 2)
            {


                //added sound buffer
                sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("yes.wav"))
                    return -1;


                sf::Sound sound(buffer);
                sound.play();

                // Wait until sound finishes playing
                while (sound.getStatus() == sf::Sound::Playing)
                    sf::sleep(sf::milliseconds(1));

            }
            else if (possible_sound == 3)
            {

                //added sound buffer
                sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("sponge.wav"))
                    return -1;


                sf::Sound sound(buffer);
                sound.play();

                // Wait until sound finishes playing
                while (sound.getStatus() == sf::Sound::Playing)
                    sf::sleep(sf::milliseconds(20));

            }
           
            


        }
        else
        {

            int loss_points = rand() % 67; //this got changed

            std::cout << "\n You lost " <<  loss_points << " points!\n";

            points -= loss_points;
            std::cout << "\n Your score: " << points << std::endl;



            int possible_sound = rand() % 5 + 1; 

            if (possible_sound == 3)
            {

                for (int x = 0; x <= 500; x++) //3
                {

                   std::cout << "aosdifaowenoe[eiwnoeommasdf[oaweinwl3mkw[ofdijasdo[fnae[o"; 

                }



                //added sound buffer
                sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("no.wav"))
                    return -1;


                sf::Sound sound(buffer);
                sound.play();

                // Wait until sound finishes playing
                while (sound.getStatus() == sf::Sound::Playing)
                    sf::sleep(sf::milliseconds(20));


                std::abort(); 

            }
            else if (possible_sound == 2)
            {
                //added sound buffer
                sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("leg.wav"))
                    return -1;


                sf::Sound sound(buffer);
                sound.play();

                // Wait until sound finishes playing
                while (sound.getStatus() == sf::Sound::Playing)
                    sf::sleep(sf::milliseconds(20));


            }
            else if (possible_sound == 5)
            {
                //added sound buffer
                sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("foghorn.wav"))
                    return -1;


                sf::Sound sound(buffer);
                sound.play();

                // Wait until sound finishes playing
                while (sound.getStatus() == sf::Sound::Playing)
                    sf::sleep(sf::milliseconds(20));


            }
            else if (possible_sound == 1)
            {


                //added sound buffer
                sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("steve.wav"))
                    return -1;


                sf::Sound sound(buffer);
                sound.play();

                // Wait until sound finishes playing
                while (sound.getStatus() == sf::Sound::Playing)
                    sf::sleep(sf::milliseconds(1));

            }
            else if (possible_sound == 4)
            {

                //added sound buffer
                sf::SoundBuffer buffer;
                if (!buffer.loadFromFile("womp.wav"))
                    return -1;


                sf::Sound sound(buffer);
                sound.play();

                // Wait until sound finishes playing
                while (sound.getStatus() == sf::Sound::Playing)
                    sf::sleep(sf::milliseconds(20));

            }

            

            


        }


        std::cout << "\n ____________________________________ \n";


        if (points < 0)
        {

            std::cout << "\n You have ran out of points! Thank's for playing! \n"; 

            //added sound buffer
            sf::SoundBuffer buffer;
            if (!buffer.loadFromFile("rawr.wav"))
                return -1;


            sf::Sound sound(buffer);
            sound.play();

            // Wait until sound finishes playing
            while (sound.getStatus() == sf::Sound::Playing) 
                sf::sleep(sf::milliseconds(120));

            if (!buffer.loadFromFile("roblox.wav"))
                return -1;

            sound.play(); 

            while (sound.getStatus() == sf::Sound::Playing)
                sf::sleep(sf::milliseconds(300));


            std::abort(); 


            exit(0); 

        }








        Sleep(4000);

      
    }
    

    
    return 0; 
    

}