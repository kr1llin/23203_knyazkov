// #include "Menu.hpp"

// space_invaders::Menu::Menu()
// {
//     using space_invaders::Menu;

//     m_choice = choice::st_uninitialized;

//     std::size_t selection = 0;
//     std::size_t boundcount = 0;
//     std::size_t hovercount = 0;
// }


// void space_invaders::menu::show(sf::RenderWindow& window)
// {
//     using space_invaders::Menu;


//     sf::VideoMode mode = sf::VideoMode::getDesktopMode();
//     float scale = mode.width/800.f;
//     m_winsizeX = mode.width;
//     m_winsizeY = mode.height;
//     std::cout<<m_winsizeX<<"\n"<<m_winsizeY<<std::endl;
//     m_scale = scale;

//     window.setKeyRepeatEnabled(false);
//     window.setFramerateLimit(60);//set the refresh limit to the current frame rate 60fps

//     if(!m_choice == choice::s_uninitialized)
//         return;

//     m_choice = choice::s_undecided;

//     //set up menu resources
//     sf::Font standardfont;
//     if(!standardfont.loadFromFile("fonts/contb.ttf"))
//     {
//         std::cerr<<"Could not load contb.ttf."<<std::endl;
//     }

//     sf::Texture bgtex;
//     if(!bgtex.loadFromFile("img/title.png"))
//     {
//         std::cerr<<"Could not load title.png."<<std::endl;
//     }

//     sf::Sprite title;
//     title.setTexture(bgtex);
//     title.setOrigin(title.getGlobalBounds().width/2.f, title.getGlobalBounds().height/2.f);
//     title.setScale(m_scale, m_scale);
//     title.setPosition(m_winsizeX/2.f, m_winsizeY/6.f);
//     title.setColor(sf::Color(255,255,255,255));
//     std::cout<<title.getPosition().x<<"\n"<<title.getPosition().y<<std::endl;

//     sf::Text subtitle("...not another Space Invaders clone!", standardfont, 24);
//     subtitle.setOrigin(subtitle.getGlobalBounds().width/2.f, subtitle.getGlobalBounds().height/2.f);
//     subtitle.setScale(m_scale, m_scale);
//     subtitle.setPosition(title.getPosition().x, title.getPosition().y + (title.getGlobalBounds().height * 1.25f)/m_scale);
//     subtitle.setColor(sf::Color(0,255,255,255));

//     sf::Text play("Play", standardfont, 52);
//     play.setOrigin(0.f, play.getGlobalBounds().height/2.f);
//     play.setScale(m_scale, m_scale);
//     play.setPosition(0.f, window.getSize().y/2.f);

//     sf::Text info("Info", standardfont, 52);
//     info.setOrigin(0.f, info.getGlobalBounds().height/2.f);
//     info.setScale(m_scale, m_scale);
//     info.setPosition(play.getPosition().x, play.getPosition().y + (play.getGlobalBounds().height * 2.0f));

//     sf::Text options("Options", standardfont, 52);
//     options.setOrigin(0.f, options.getGlobalBounds().height/2.f);
//     options.setScale(m_scale, m_scale);
//     options.setPosition(info.getPosition().x, info.getPosition().y + (info.getGlobalBounds().height * 2.0f));

//     //set up hexgrid and starfield backgrounds
//     nasic::hexgrid hex(window, nasic::hexgrid::hexStyle::cyan, scale);
//     starfield stars(window, starfield::starStyle::starsAndPlanets, scale);

//     sf::SoundBuffer menubuff;
//     if(!menubuff.loadFromFile("sound/select.wav"))
//     {
//         std::cerr<<"Could not load select.wav."<<std::endl;
//     }
//     sf::Sound menusound;
//     menusound.setBuffer(menubuff);
//     menusound.setVolume(m_initialEff*5.f);

//     sf::Music menumusic;
//     if(!menumusic.openFromFile("sound/title.ogg"))
//     {
//         std::cout<<"Could not open stream for title.ogg"<<std::endl;
//     }
//     menumusic.setVolume(m_initialVol*5.f);
//     menumusic.play();

//     //housekeeping variables for keeping track of the selection
//     std::size_t selection = 0;
//     std::size_t boundcount = 0;
//     std::size_t hovercount = 0;

//     bool running = true;
//     sf::Event e;

//     //time stuff...
//     sf::Clock tickClock;
//     sf::Time timeSinceLastUpdate = sf::Time::Zero;
//     sf::Time TimePerFrame = sf::seconds(1.f/60.f);
//     sf::Time moveText = sf::Time::Zero;
//     sf::Time colorChanger = sf::Time::Zero;

//     while(running)
//     {
//         while(window.pollEvent(e))
//         {
//             if(e.type == sf::Event::Closed)
//             {
//                 m_choice = choice::s_quit;
//                 return;
//             }

//             if(e.type == sf::Event::KeyPressed)
//             {
//                 switch(e.key.code)
//                 {
//                 case sf::Keyboard::Escape:
//                 {
//                     m_choice = choice::s_quit;
//                     return;
//                 }
//                 break;

//                 case sf::Keyboard::Return:
//                 {
//                     return;
//                 }
//                 break;

//                 case sf::Keyboard::Up:
//                 {
//                     if(moveText.asSeconds() >= 1.f)
//                         moveText = sf::Time::Zero;//reset the counter for text movement
//                     if(selection <= 0)
//                     {
//                         boundcount++;
//                         selection = 0;
//                         std::cout<<"bound count : "<<boundcount<<std::endl;
//                     }
//                     else
//                     {
//                         selection--;
//                         boundcount = 0;
//                         std::cout<<"bound count : "<<boundcount<<std::endl;
//                     }

//                     if(boundcount == 0)
//                         menusound.play();
//                 }
//                 break;

//                 case sf::Keyboard::Down:
//                 {
//                     if(moveText.asSeconds() >= 1.f)
//                         moveText = sf::Time::Zero;
//                     if(selection >= 2)
//                     {
//                         boundcount++;
//                         selection = 2;
//                         std::cout<<"bound count : "<<boundcount<<std::endl;
//                     }
//                     else
//                     {
//                         boundcount = 0;
//                         selection++;
//                         std::cout<<"bound count : "<<boundcount<<std::endl;
//                     }

//                     if(boundcount == 0)
//                         menusound.play();
//                 }
//                 break;

//                 default:
//                     break;
//                 }
//             }

//             sf::Vector2i mousepos = sf::Mouse::getPosition(window);
//             if(mousepos.x >= play.getPosition().x
//                     && mousepos.y >= play.getPosition().y
//                     && mousepos.x <= play.getPosition().x + play.getGlobalBounds().width
//                     && mousepos.y <= play.getPosition().y + play.getGlobalBounds().height)
//             {

//                 //set selection to play
//                 //and keep track of mouse over text
//                 selection = 0;
//                 hovercount++;

//                 //reset the text movement counter
//                 if(moveText.asSeconds() >= 1.f && hovercount == 1 && play.getPosition().x < 70.f)
//                         moveText = sf::Time::Zero;

//                 //play sound according to mouse hover events
//                 if(hovercount == 1)//because there are multiple mouse events we just want the first one
//                 {
//                     menusound.play();
//                 }
//                 else
//                 {
//                     //kill it after the first play
//                     //so it doesn't do that aweful repeating thing
//                     if(!menusound.getStatus() == sf::Sound::Playing)
//                         menusound.stop();
//                 }

//                 if(e.type == sf::Event::MouseButtonPressed)
//                 {
//                     return;
//                 }

//             }

//             else if(mousepos.x >= info.getPosition().x
//                     && mousepos.y >= info.getPosition().y
//                     && mousepos.x <= info.getPosition().x + info.getGlobalBounds().width
//                     && mousepos.y <= info.getPosition().y + info.getGlobalBounds().height)
//             {

//                 //set selection to info
//                 //and keep track of mouse over text
//                 selection = 1;
//                 hovercount++;

//                 //reset the text movement counter
//                 if(moveText.asSeconds() >= 1.f && hovercount == 1 && info.getPosition().x < 70.f)
//                         moveText = sf::Time::Zero;

//                 //play sound according to mouse hover events
//                 if(hovercount == 1)//because there are multiple mouse events we just want the first one
//                 {
//                     menusound.play();
//                 }
//                 else
//                 {
//                     //kill it after the first play
//                     //so it doesn't do that aweful repeating thing
//                     if(!menusound.getStatus() == sf::Sound::Playing)
//                         menusound.stop();
//                 }

//                 if(e.type == sf::Event::MouseButtonPressed)
//                 {
//                     return;
//                 }
//             }

//             else if(mousepos.x >= options.getPosition().x
//                     && mousepos.y >= options.getPosition().y
//                     && mousepos.x <= options.getPosition().x + options.getGlobalBounds().width
//                     && mousepos.y <= options.getPosition().y + options.getGlobalBounds().height)
//             {

//                 //set selection to options
//                 //and keep track of mouse over text
//                 selection = 2;
//                 hovercount++;

//                 //reset the text movement counter
//                 if(moveText.asSeconds() >= 1.f && hovercount == 1 && options.getPosition().x < 70.f)
//                         moveText = sf::Time::Zero;

//                 //play sound according to mouse hover events
//                 if(hovercount == 1)//because there are multiple mouse events we just want the first one
//                 {
//                     menusound.play();
//                 }
//                 else
//                 {
//                     //kill it after the first play
//                     //so it doesn't do that aweful repeating thing
//                     if(!menusound.getStatus() == sf::Sound::Playing)
//                         menusound.stop();
//                 }

//                 if(e.type == sf::Event::MouseButtonPressed)
//                 {
//                     return;
//                 }
//             }
//             else
//                 hovercount = 0;
//         }

//         //handle game ticks and return a fixed dt
//         //for updates
//         timeSinceLastUpdate += tickClock.restart();
//         while (timeSinceLastUpdate > TimePerFrame)
//         {
//             timeSinceLastUpdate -= TimePerFrame;
//             stars.update(window,TimePerFrame);

//             moveText += TimePerFrame;//for fixed movement of text below...
//             colorChanger += TimePerFrame;//for color changing of title below...

//             //visual indicators of selection made
//             //as well as setting the choice enum accordingly
//             //to trigger the proper state
//             switch(selection)
//             {
//             case 0:
//             {
//                 m_choice = choice::s_play;

//                 //set properties for the play option
//                 play.setColor(sf::Color(255,0,255,255));
//                 if(moveText.asSeconds() < 1.f && play.getPosition().x < 100.f && boundcount == 0)
//                     play.move(10.f*interpolate::backEaseOut(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     play.setPosition(70.f, play.getPosition().y);//make sure it is sitting at the max when animation stops...

//                 //set properties for the info option
//                 info.setColor(sf::Color(255,255,255,255));
//                 if(moveText.asSeconds() < 1.f && info.getPosition().x > 10.f)
//                     info.move(-10.f*interpolate::backEaseIn(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     info.setPosition(10.f,info.getPosition().y);//make sure it is sitting at the min when animation ends...

//                 //set properties for the options option
//                 options.setColor(sf::Color(255,255,255,255));
//                 if(moveText.asSeconds() < 1.f && options.getPosition().x > 10.f)
//                     options.move(-10.f*interpolate::backEaseIn(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     options.setPosition(10.f, options.getPosition().y);//make sure it is sitting at the min when animation ends...
//             }
//             break;

//             case 1:
//             {
//                 m_choice = choice::s_info;
//                 play.setColor(sf::Color(255,255,255,255));
//                 if(moveText.asSeconds() < 1.f && play.getPosition().x > 10.f)
//                     play.move(-10.f*interpolate::backEaseIn(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     play.setPosition(10.f, play.getPosition().y);

//                 info.setColor(sf::Color(255,55,0,255));
//                 if(moveText.asSeconds() < 1.f && info.getPosition().x < 100.f)
//                     info.move(10.f*interpolate::backEaseOut(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     info.setPosition(70.f, info.getPosition().y);

//                 options.setColor(sf::Color(255,255,255,255));
//                 if(moveText.asSeconds() < 1.f && options.getPosition().x > 10.f)
//                     options.move(-10.f*interpolate::backEaseIn(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     options.setPosition(10.f, options.getPosition().y);
//             }
//             break;

//             case 2:
//             {
//                 m_choice = choice::s_options;
//                 play.setColor(sf::Color(255,255,255,255));
//                 if(moveText.asSeconds() < 1.f && play.getPosition().x > 10.f)
//                     play.move(-10.f*interpolate::backEaseIn(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     play.setPosition(10.f, play.getPosition().y);

//                 info.setColor(sf::Color(255,255,255,255));
//                 if(moveText.asSeconds() < 1.f && info.getPosition().x > 10.f)
//                     info.move(-10.f*interpolate::backEaseIn(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     info.setPosition(10.f,info.getPosition().y);

//                 options.setColor(sf::Color(0,255,0,255));
//                 if(moveText.asSeconds() < 1.f && options.getPosition().x < 100.f && boundcount == 0)
//                     options.move(10.f*interpolate::backEaseOut(moveText.asSeconds(), 0.f, 1.f, 1.f), 0.f);
//                 else
//                     options.setPosition(70.f, options.getPosition().y);
//             }
//             break;

//             default:
//                 break;
//             }

//             if(colorChanger.asSeconds() < 3.f)//subtract result from 255 to fade from cyan(?) to green
//                 title.setColor(sf::Color(255, 255, 255-(int)interpolate::circularEaseIn(colorChanger.asSeconds(), 0.f, 255.f, 3.f), 255));
//         }

//         window.clear();

//         window.draw(stars);
//         window.draw(hex);
//         window.draw(title);
//         window.draw(subtitle);
//         window.draw(play);
//         window.draw(info);
//         window.draw(options);
//         window.display();
//     }
//     return;
// }

// //instantiate static members
// nasic::menu::choice nasic::menu::m_choice = nasic::menu::choice::s_uninitialized;


