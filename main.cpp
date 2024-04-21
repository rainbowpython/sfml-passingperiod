#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include <bits/stdc++.h>
class Methods{
public:
    int rectNumber(std::vector<sf::RectangleShape> rectangles, sf::RectangleShape player);
    int randomClass(int n);
};
//remnant of hallway slowing you down concept
class Hallway : public sf::RectangleShape{
    public:
        float traffic;
        Hallway(sf::Vector2f size);

};
Hallway::Hallway(sf::Vector2f size) : sf::RectangleShape(size){
    traffic = 0;
}

class Door : public sf::RectangleShape{
    public:
        sf::Vector2f loc1;
        sf::Vector2f loc2;
        Door(sf::Vector2f size, sf::Vector2f entrance, sf::Vector2f exit);

};

Door::Door(sf::Vector2f size, sf::Vector2f entrance, sf::Vector2f exit) : sf::RectangleShape(size){
    loc1 = entrance;
    loc2 = exit;
}


int main(){
    //Initialize window
    sf::RenderWindow window(sf::VideoMode(900, 500), "passingperiod");
    sf::Event event;
    sf::RectangleShape player(sf::Vector2f(25,25));
    Methods methods;
    
    //add hallways and store in array
    std::vector<sf::RectangleShape> room;
    //hall 1
    room.push_back(Hallway(sf::Vector2f(450,50)));
    room.at(0).setPosition(sf::Vector2f(150,75));
    //hall 2
    room.push_back(Hallway(sf::Vector2f(50,300)));
    room.at(1).setPosition(sf::Vector2f(500,128));
    //room 1
    room.push_back(sf::RectangleShape(sf::Vector2f(75,75)));
    room.at(2).setPosition(sf::Vector2f(150, -2));
    //room 2
    room.push_back(sf::RectangleShape(sf::Vector2f(75,75)));
    room.at(3).setPosition(sf::Vector2f(250, -2));
    //restroom
    room.push_back(sf::RectangleShape(sf::Vector2f(50,75)));
    room.at(4).setPosition(sf::Vector2f(262, 128));
    //room 3
    room.push_back(sf::RectangleShape(sf::Vector2f(75,75)));
    room.at(5).setPosition(sf::Vector2f(350, 128));
    //room 4
    room.push_back(sf::RectangleShape(sf::Vector2f(75,75)));
    room.at(6).setPosition(sf::Vector2f(550, 150));
    //room 5
    room.push_back(sf::RectangleShape(sf::Vector2f(75,75)));
    room.at(7).setPosition(sf::Vector2f(550, 250));
    //room 6
    room.push_back(sf::RectangleShape(sf::Vector2f(75,75)));
    room.at(8).setPosition(sf::Vector2f(522, -2));

    //same with doors
    std::vector<Door> doors;
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(525,90), sf::Vector2f(525,140)));
    doors.at(0).setPosition(sf::Vector2f(500,128));
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(155,40), sf::Vector2f(155,90)));
    doors.at(1).setPosition(sf::Vector2f(162,70));
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(155,40), sf::Vector2f(155,90)));
    doors.at(2).setPosition(sf::Vector2f(262,70));
    //restroom door
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(155, 90), sf::Vector2f(155, 150)));
    doors.at(3).setPosition(sf::Vector2f(262,125));
    //room 3 door
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(155, 90), sf::Vector2f(155, 150)));
    doors.at(4).setPosition(sf::Vector2f(362,125));
    //room 4 door
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(515, 150), sf::Vector2f(575, 150)));
    doors.at(5).setPosition(sf::Vector2f(550,165));
    doors.at(5).setRotation(90);
    //room 5 door
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(515, 150), sf::Vector2f(575, 150)));
    doors.at(6).setPosition(sf::Vector2f(550,262));
    doors.at(6).setRotation(90);
    //room 6 door
    doors.push_back(Door(sf::Vector2f(50, 5), sf::Vector2f(515, 40), sf::Vector2f(575, 90)));
    doors.at(7).setPosition(sf::Vector2f(537,70));


    sf::Font font;
    font.loadFromFile("COMICSANS.TTF");
    sf::Text timerText;
    timerText.setFont(font);
    bool classtime = true;
    float x = 150;
    float y = 20;
    float vx = 0;
    float vy = 0;
    //for delta time
    sf::Clock time;
    //game time
    sf::Clock timer;
    float speed = 0.9;
    //class room arrays{2, 3, 5, 6}
    int goalClass = methods.randomClass(0);
    
    //game loop
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        
        //-------------timer drawing------------
        timerText.setString(std::to_string(static_cast<int>(timer.getElapsedTime().asSeconds())));
        int n = methods.rectNumber(room, player);
        //-------------rectangle drawing------------
        for (size_t i = 0; i < room.size(); i++){
            if(i == 4){
                room.at(i).setFillColor(sf::Color::Black);
                room.at(i).setOutlineColor(sf::Color::Yellow);
                room.at(i).setOutlineThickness(2);
            }
            
            else{
                room.at(i).setFillColor(sf::Color::Black);
                room.at(i).setOutlineColor(sf::Color::White);
                room.at(i).setOutlineThickness(2);
            }
            if(i == goalClass){
                room.at(i).setFillColor(sf::Color::Black);
                room.at(i).setOutlineColor(sf::Color::Green);
                room.at(i).setOutlineThickness(2);
            }
        }
        for (size_t i = 0; i < doors.size(); i++){
            doors.at(i).setFillColor(sf::Color::Black);
            doors.at(i).setOutlineColor(sf::Color::Blue);
            doors.at(i).setOutlineThickness(3);
        }

        //-------------controls------------
        vx = 0;
        vy = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(x > + room.at(n).getPosition().x){
                vx = -1;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(x + player.getLocalBounds().width + 3< + room.at(n).getPosition().x + room.at(n).getLocalBounds().width){
                vx = 1;
            }
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(y > + room.at(n).getPosition().y){
                vy = -1;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(y + player.getLocalBounds().height + 3 < room.at(n).getLocalBounds().height + room.at(n).getPosition().y){
                vy = 1;
            }
        }
        
        x += vx * time.getElapsedTime().asSeconds()*100*speed;
        y += vy * time.getElapsedTime().asSeconds()*100*speed;
        
        //-------------doors------------
        for (size_t i = 0; i < doors.size(); i++){
            if(doors.at(i).getRotation() == 0){
                if (
                    x >= doors.at(i).getPosition().x &&
                    x + player.getGlobalBounds().width < + doors.at(i).getPosition().x + doors.at(i).getGlobalBounds().width &&
                    y < + doors.at(i).getPosition().y &&
                    y + player.getGlobalBounds().height + 4 > + doors.at(i).getPosition().y
                    ){
                    y = doors.at(i).loc2.y;
                }
                if (
                    x >= doors.at(i).getPosition().x &&
                    x + player.getGlobalBounds().width < doors.at(i).getPosition().x + doors.at(i).getGlobalBounds().width &&
                    y < doors.at(i).getPosition().y + doors.at(i).getGlobalBounds().height &&
                    y + player.getGlobalBounds().height > doors.at(i).getPosition().y 
                    ){ 
                    y = doors.at(i).loc1.y;
                }
            }
            else{
                if (
                    y > doors.at(i).getPosition().y &&
                    y + player.getGlobalBounds().height < + doors.at(i).getPosition().y + doors.at(i).getGlobalBounds().height &&
                    x < + doors.at(i).getPosition().x  &&
                    x + player.getGlobalBounds().width + 4 > + doors.at(i).getPosition().x
                    ){
                    x = doors.at(i).loc2.x;
                }
                if (
                    y > doors.at(i).getPosition().y &&
                    y + player.getGlobalBounds().height < + doors.at(i).getPosition().y + doors.at(i).getGlobalBounds().height &&
                    x < + doors.at(i).getPosition().x + player.getGlobalBounds().width &&
                    x + player.getGlobalBounds().width + 4 > + doors.at(i).getPosition().x
                    ){ 
                    x = doors.at(i).loc1.x;
                }
            }
        }
        
        if(timer.getElapsedTime().asSeconds() >= 10){
            window.close();
        }

        if (n == goalClass){
            timer.restart();
            goalClass = methods.randomClass(n);
            speed-=0.1;
        }

        if (speed <= 0.2)
        {
            window.close();
        }
        
        
        time.restart();
        player.setPosition(x, y);
        window.clear();
        for (size_t i = 0; i < room.size(); i++){
            window.draw(room.at(i));
        }
        for (size_t i = 0; i < doors.size(); i++){
            window.draw(doors.at(i));
        }
        window.draw(timerText);
        window.draw(player);
        window.display();
    }
    return 0;
}
int Methods::rectNumber(std::vector<sf::RectangleShape> rectangles, sf::RectangleShape player){
    int index = 0; 
    for (size_t i = 0; i < rectangles.size(); i++){
        if (rectangles.at(i).getGlobalBounds().contains(player.getPosition())){
            index = i;
        }
    }
    return index;
}
int Methods::randomClass(int n){
    int classes[6] = {2, 3, 5, 6, 7, 8};
    int random = std::rand() % (6);
    while (random == n){
        random = std::rand() % (6);
    }
    return classes[random];
}

