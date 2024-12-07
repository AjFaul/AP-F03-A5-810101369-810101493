#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm> 

using namespace std;
using namespace sf;
namespace fs = std::filesystem;

//-------------------
const int TYPE_OF_SHEEP=3;
const int SPEED_GAME=100;
//--------------------
const int X_PAGE=1024;
const int Y_PAGE=1024;
//--------------------
const string ADDRESS_INITIAL_COUNT="/home/ubuntu/Desktop/image/inital_count";
const string ADDRESS_BACK_GROUND="/home/ubuntu/Desktop/image/start/background.png";
//----------------
const int GAME_START=0;
const int GAME_INITIAL=1;
const int MAIN_GAME=2;
//-------------
const int TIME_INITIAL_GAME=3;
//------------
const int CLOSE=0;
const int MOUSE_LEFT=1;
const int ARROW_UP=2;
const int ARROW_DOWN=3;
const int KEY_S=4;
const int KEY_W=5;
const int KEY_ENTER=6;
//------------ 
const int RIGHT=1;
const int LEFT=0;
//------------





class Player
{
private:
    int health=100;
    string player_name;
    vector<int> queue_sheeps={1,2,3};

    void left_sheeps(){
        int last_sheep=queue_sheeps[2];
        queue_sheeps[2]=0;
        last_sheep_size=last_sheep;
    }

    void sheft_queue(){
        for(int i=2;i>=0;i--){
            if(i==0)
                queue_sheeps[i]=0;
            else
                queue_sheeps[i]=queue_sheeps[i-1];
        }
    }

    void update_queue(){
        // 2 is length of list of sheep
        for(int i=0;i<=2;i++){
            if(queue_sheeps[i]==0)
                queue_sheeps[i]=rand()%TYPE_OF_SHEEP+1;
        }

    }

    int decrease_health(int size_sheep){
        // 5 is power of one unit of sheep 
        health-=size_sheep*5;
        if(health<=0)
        {
            health=0;
            return 0;
        }
        return 1;
    }

public:
    int last_sheep_size=0;
    Player(string name){
        player_name=name;
    }

    ~Player(){}

    void print_queue(){
        for(int i=0;i<=2;i++){
            cout<<queue_sheeps[i]<<endl;
        }
        cout<<"--------------------"<<endl;
    }

    int get_health(){return health;}

    int get_last_sheep_size(){return last_sheep_size;}


    void send_sheep(){
        left_sheeps();
        sheft_queue();
        update_queue();
    }

};

class Sheep
{
private:
    int size_sheep;
    int x,y;
public:
    Sheep(int size,int x_ , int y_){
        size_sheep=size;
        x=x_;
        y=y_;
    }

    void move_sheep(){
        int dx=SPEED_GAME/size_sheep;
        x+=dx;
    }


    bool is_in_page(){
        if(x>=X_PAGE)
            return 0;
        return 1;
    }

    int get_x(){return x;}

    ~Sheep(){};

};


class Arrow
{
private:
    float y;
    float x;
    float time=0;
public:
    Arrow(int type_RL){
        y=212;
        if(type_RL==0)
            x=30;
        if(type_RL==1)
            x=915;
    }

    void arrow_up(){
        y-=212;
        if(y<=150)
            y=828;
    }

    void arrow_down(){
        y+=212;
        if(y>=900)
            y=212;
    }

    void set_time(float cur_time){
        time=cur_time;
    }

    float get_pos_y(){return y;}
    float get_pos_x(){return x;}


    ~Arrow(){}
};






int get_floor(int y)
{
    if(y<=300 && y>=100)
        return 1;
    if(y<=500 && y>=301)
        return 2;
    if(y<=700 && y>=501)
        return 3;
    if(y<=900 && y>=700)
        return 4;
    return 0;
}



int checkMouseInRectangle_start(sf::RenderWindow &window) {
    FloatRect targetRect(193,202,(709-193),(363-202));
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (targetRect.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        return 1;
    }
    return 0;
}

int checkMouseInRectangle_exit(sf::RenderWindow &window) {
    FloatRect targetRect(355,376,(632-355),(482-376));
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (targetRect.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        return 1;
    }
    return 0;
}

sf::Texture set_image(string filepath)
{
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(filepath)) 
    {
        cout<<"-1";
    }
    return backgroundTexture;
}

int handle_event(const Event & event){
    if(event.type==sf::Event::Closed)
        return 0;
    
    if(event.type==sf::Event::MouseButtonPressed)
        if(event.mouseButton.button==Mouse::Left)
            return 1;

    if(event.type==Event::KeyPressed)
    {
        if(event.key.code==Keyboard::S)
            return KEY_S;

        if(event.key.code==Keyboard::W)
            return KEY_W;
        
        if(event.key.code==Keyboard::Up)
            return ARROW_UP;

        if(event.key.code==Keyboard::Down)
            return ARROW_DOWN;

        if(event.key.code==Keyboard::Enter)
            return KEY_ENTER;
    }

    return -1;
}

void update_window(sf::RenderWindow & window, Sprite backgroundSprite){
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);
    window.display();
}



// void update_L_R_line(vector<float> &L_R){
//     for(int i=0;i<L_R.size();i++)
//         L_R[i] = L_R[i] +0.01;
// }




void start_game()
{
    sf::RenderWindow window(sf::VideoMode(X_PAGE, Y_PAGE), "Game");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("/home/ubuntu/Desktop/image/start/Start.png")) 
    {
        return ;
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    int status_game=0;
    int initial_count=TIME_INITIAL_GAME;

    sf::Clock clock;


    Arrow right(RIGHT);
    Arrow left(LEFT);


//---------------------------------------------------
    Texture logo_arrow_left;
    if(!logo_arrow_left.loadFromFile("/home/ubuntu/Desktop/image/logo/small_yang.png"))
        return;
    Sprite left_arrow_sprite(logo_arrow_left);
    left_arrow_sprite.setPosition(float(left.get_pos_x()),float(left.get_pos_y()));

    Texture logo_arrow_right;
    if(!logo_arrow_right.loadFromFile("/home/ubuntu/Desktop/image/logo/small_yang.png"))
        return;
    Sprite right_arrow_sprite(logo_arrow_right);
    right_arrow_sprite.setPosition(float(right.get_pos_x()),float(right.get_pos_y()));



    Texture logo_pig;
    if(!logo_pig.loadFromFile("/home/ubuntu/Desktop/image/logo/fliped_pig.png"))
        return;
    Sprite logo_pic_sprite(logo_pig);





//---------------------------------------------------



    while (window.isOpen())
    {
        sf::Event event;
        if(handle_event(event)==CLOSE)
            window.close();

        while (window.pollEvent(event) && status_game==GAME_START)
        {
            if (handle_event(event)==CLOSE)
                window.close();

            //start game
            if(checkMouseInRectangle_start(window))
                if(handle_event(event)==MOUSE_LEFT){
                    status_game=GAME_INITIAL;
                    backgroundTexture=set_image(ADDRESS_BACK_GROUND);
                    backgroundSprite.setTexture(backgroundTexture);
                    break;
                }
       
            //end game
            if(checkMouseInRectangle_exit(window) && status_game!=1)
                if(handle_event(event)==MOUSE_LEFT)
                    window.close();
        }  

        update_window(window,backgroundSprite);

        clock.restart();

        while (status_game==GAME_INITIAL)
        {
            window.pollEvent(event);
            if (handle_event(event)==CLOSE)
            {
                window.close();
                abort();
            }
            // show initial count number in page 
            if(clock.getElapsedTime().asSeconds()>=1.0f && initial_count!=0){
                clock.restart();
                backgroundTexture=set_image(ADDRESS_INITIAL_COUNT+"/"+to_string(initial_count)+".png");
                backgroundSprite.setTexture(backgroundTexture);
                initial_count--;
            }
            if(initial_count==0)
                status_game=MAIN_GAME; 
            update_window(window,backgroundSprite);
        }




        vector<Clock> clocks;
        Clock clock_enter;
        vector<Sheep> sheeps_1_L;
        vector<float> L_1;
        vector<Sheep> sheeps_2_L;
        vector<float> L_2;
        vector<Sheep> sheeps_3_L;
        vector<float> L_3;
        vector<Sheep> sheeps_4_L;
        vector<float> L_4;
        vector<Sheep> sheeps_1_R;
        vector<float> R_1;
        vector<Sheep> sheeps_2_R;
        vector<float> R_2;
        vector<Sheep> sheeps_3_R;
        vector<float> R_3;
        vector<Sheep> sheeps_4_R;
        vector<float> R_4;
        vector<Sprite> sheeps_sprit;




        Player amirabas("amirabas");
        Player ali("ali");
        int last_sheep_R;
        int last_sheep_L;
        int last_size;
        while (status_game==MAIN_GAME)
        {
            window.pollEvent(event);
            backgroundTexture=set_image("/home/ubuntu/Desktop/image/start/background.png");
            backgroundSprite.setTexture(backgroundTexture);
            window.clear(sf::Color::Black);
            window.draw(backgroundSprite);
            window.draw(left_arrow_sprite);
            window.draw(right_arrow_sprite);
            

            if(handle_event(event)==CLOSE)
            {
                window.close();
                abort();
            }

            if(handle_event(event)==ARROW_DOWN)
            {
                right.arrow_down();
                right_arrow_sprite.setPosition(right.get_pos_x(),right.get_pos_y());
            }

            if(handle_event(event)==ARROW_UP)
            {
                right.arrow_up();
                right_arrow_sprite.setPosition(right.get_pos_x(),right.get_pos_y());
            }
            
            if(handle_event(event)==KEY_S)
            {
                left.arrow_down();
                left_arrow_sprite.setPosition(left.get_pos_x(),left.get_pos_y());                
            }

            if(handle_event(event)==KEY_W)
            {
                left.arrow_up();
                left_arrow_sprite.setPosition(left.get_pos_x(),left.get_pos_y());                
            }


            //just for left
            if(handle_event(event)==KEY_ENTER)
            {
                if(clock_enter.getElapsedTime().asSeconds() >= 3)  
                {

                    switch (get_floor(left.get_pos_y()))
                    {
                    case 1:
                        amirabas.send_sheep();
                        last_size=amirabas.get_last_sheep_size();
                        sheeps_1_L.push_back(Sheep(last_size,60,left.get_pos_y()));
                        L_1.push_back(60);
                        sheeps_sprit.push_back(logo_pic_sprite);
                        sheeps_sprit[sheeps_sprit.size()-1].setPosition(60,212);
                        

                        break;
                    case 2:
                        amirabas.send_sheep();
                        last_size=amirabas.get_last_sheep_size();
                        sheeps_2_L.push_back(Sheep(last_size,60,left.get_pos_y()));
                        L_2.push_back(60);
                        sheeps_sprit.push_back(logo_pic_sprite);
                        sheeps_sprit[sheeps_sprit.size()-1].setPosition(60,212*2);
                        break;
                    case 3:
                        amirabas.send_sheep();
                        last_size=amirabas.get_last_sheep_size();
                        sheeps_3_L.push_back(Sheep(last_size,60,left.get_pos_y()));
                        L_3.push_back(60);
                        sheeps_sprit.push_back(logo_pic_sprite);
                        sheeps_sprit[sheeps_sprit.size()-1].setPosition(60,212*3);
                        break;
                    case 4:
                        amirabas.send_sheep();
                        last_size=amirabas.get_last_sheep_size();
                        sheeps_4_L.push_back(Sheep(last_size,60,left.get_pos_y()));
                        L_4.push_back(60);
                        sheeps_sprit.push_back(logo_pic_sprite);
                        sheeps_sprit[sheeps_sprit.size()-1].setPosition(60,828);
                        break;
                    default:
                        break;
                    }
                    clock_enter.restart();
                }
                else
                    continue;

            }

            for(int i=0; i<sheeps_sprit.size();i++)
            {
                sheeps_sprit[i].move(0.1f,0.0f);
                window.draw(sheeps_sprit[i]);
            }
            


            window.display();
        }
        

    }
    

}


    




int main() {
    start_game();

   


    return 0;
}
    

