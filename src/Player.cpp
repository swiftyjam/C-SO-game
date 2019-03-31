#include "Player.h"
#include <SFML/Graphics.hpp>
using namespace std;

Player::Player()
{
    //inicializamos matriz de frames
    frames.resize(4);
    for (int i = 0 ; i < 4 ; i++)
        frames[i].resize(2);

    frames[0][0]=sf::IntRect(0, 0,32, 32);//Frente 0----0
    //La carga de texturas podria ser otra clase
    texture.loadFromFile("resources/Sunny-land-files/PNG/sprites/player/player.png");
    if (!texture.loadFromFile("resources/Sunny-land-files/PNG/sprites/player/player.png"))
    {
        std::cerr << "Error cargando la imagen player.png";
        exit(0);
    }

    sprite.setTexture(texture);
    sprite.setOrigin(28/2,44/2);
    sprite.setTextureRect(frames[0][0]);
    sprite.scale(1.2,1.2);


    renderPos.push_back(0.0);
    renderPos.push_back(0.0);
    posNow.push_back(300.0),posNow.push_back(200.0);
    posBef.push_back(0.0),posBef.push_back(0.0);
    vel.push_back(0.0),vel.push_back(0.0);

//    colliderTop= sf::FloatRect(posNow[0],posNow[1]-45,50,15);
    colliderDown= sf::FloatRect(posNow[0],posNow[1],15,10);

    dir=1;
    frame=0;
    touchingFloor=false;
}


void Player::setFrame(int f)
{
    frame=f;
}

void Player::setTouchingFloor(bool t)
{

    touchingFloor=t;
}
void Player::setTouchingEscalera(bool t)
{
    touchingEscalera=t;
}
bool Player::isTouchingFloor()
{
    return touchingFloor;

}
bool Player::isTouchingEscalera()
{
    return touchingEscalera;
}



vector<double> Player::getPos()
{

    return posNow;

}
sf::Sprite Player::getSprite()
{
    return sprite;
}

sf::Rect<float>  Player::getColliderTop()
{
    return colliderTop;
}
sf::Rect<float>  Player::getColliderDown()
{
    return colliderDown;
}

void Player::updatePlayer(double velx, double vely, sf::Time et, float of)
{


    posBef=posNow;


    if(isTouchingEscalera())
    {
        cout<<"Tocando el suelo o escalera"<<endl;
        vel[1]=vely;
        of=0;

    }

    if(isTouchingFloor()){
        vel[1]=vely;

    }
    else
    {
        //cout<<"En el aire"<<endl;
        if(vel[1]<150)
        vel[1]+=980*et.asSeconds();
    }



    vel[0]=velx;
    posNow[0] += vel[0]*et.asSeconds();
    posNow[1] += vel[1]*et.asSeconds()-of;


}

void Player::drawPlayer(sf::RenderWindow& w, double i)
{

    //sprite.setTextureRect(frames[dir][frame]);
    sprite.setTextureRect(frames[0][0]);


    renderPos[0]=(posNow[0]-posBef[0])*i+posBef[0];
    renderPos[1]=(posNow[1]-posBef[1])*i+posBef[1];

    sprite.setPosition(renderPos[0],renderPos[1]);

    // colliderTop.top=renderPos[1]-45;
    // colliderTop.left=renderPos[0];
    colliderDown.top=renderPos[1]+9;
    colliderDown.left=renderPos[0]-8;


    w.draw(sprite);
    collisionBox.setSize(sf::Vector2f(colliderDown.width,colliderDown.height));
    collisionBox.setFillColor(sf::Color(100, 250, 50));
    collisionBox.setPosition(colliderDown.left,colliderDown.top);
    w.draw(collisionBox);
    w.draw(sprite);

}

Player::~Player()
{
    //dtor
}