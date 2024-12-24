// #include "Game.hpp"

// void space_invaders::Game::Init() {
//   using space_invaders::Game;

//   //it should be uninialized first!
//   if (!(state == State::st_uninitialized)) return;

//   sf::VideoMode mode = sf::VideoMode::getDesktopMode();
//   window.create(sf::VideoMode(mode.width, mode.height, mode.bitsPerPixel),
//                 "Space Invaders", sf::Style::Fullscreen);
//   state = State::st_menu;

//   while (!isQuitting()) {
//     run();
//   }
//   std::cout << "Quitting---" << std::endl;
//   window.close();
// }

// bool space_invaders::Game::isQuitting() {
//   return state == State::st_quit;
// }

// //main game loop
// void space_invaders::Game::run() {
//   switch (state) {

//   case State::st_menu: {
//     menu();
//   } break;

//   case State::st_options: {
//     options();
//   } break;

//   case State::st_level: {
//     level();
//   } break;

//   case State::st_win: {
//     win();
//   } break;

//   case State::st_lose: {
//     lose();
//   } break;

//   default:
//     break;
//   }
// }

// void space_invaders::Game::menu()
// {
//     window.setTitle("Menu");
//     std::cout<<"Menu State"<<std::endl;

//     //create a menu object
//     space_invaders::Menu gameMenu;
//     gameMenu.show(window);
//     if(gameMenu.menuState() == space_invaders::Menu::s_play)
//         state = State::s_level;
//     else if(gameMenu.menuState() == space_invaders::menu::s_options)
//         state = State::s_options;
//     else if(gameMenu.menuState() == space_invaders::menu::s_info)
//         m_state = state::s_info;
//     else if(gameMenu.menuState() == nasic::menu::s_quit)
//         m_state = state::s_quit;
// }

// void space_invaders::Game::options() {
//   window.setTitle("Options");
//   std::cout << "Options State" << std::endl;

// }

// void space_invaders::Game::level() {
//   window.setTitle("Level");
//   std::cout << "Level State" << std::endl;

// }

// void space_invaders::Game::win() {
//   window.setTitle("You Win");
//   std::cout << "Win State" << std::endl;

// }

// void space_invaders::Game::lose() {
//   window.setTitle("You Lose");
//   std::cout << "Lose State" << std::endl;

// }

// sf::Uint32 space_invaders::Game::state = st_uninitialized;
// sf::RenderWindow space_invaders::Game::window;
