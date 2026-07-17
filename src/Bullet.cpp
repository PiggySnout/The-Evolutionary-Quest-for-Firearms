#include "Bullet.h"

Bullet::Bullet() : damage(0),
                   pos({0,0}),
                   Velocity({0,0})
{}
Bullet::Bullet(int damage, int LifeTime, Vector2 pos, Vector2 Velocity, Texture2D* T, float angle) : 
                                                                         damage(damage),
                                                                         pos(pos),
                                                                         Velocity(Velocity),
                                                                         texture(T),
                                                                         Lifetime(LifeTime),
                                                                         angle(angle)
{}
void Bullet::Update_Pos(){
    --Lifetime;
    if (Lifetime <= 0)
        return;
    pos.x += Velocity.x;
    pos.y += Velocity.y;
}
void Bullet::Draw(Vector2 POS, bool special_angle){
    if (!special_angle){
        POS.x -= texture->width * 4.0f;
        POS.y -= texture->height * 4.0f;
        DrawTextureEx(*texture, POS, 0.0f, 8.0f, WHITE);
        return;
    }

    Rectangle source = {
        0, 0,
        (float)texture->width,
        (float)texture->height
    };

    Rectangle dest = {
        POS.x,
        POS.y,
        texture->width * 8.0f,
        texture->height * 8.0f
    };

    Vector2 origin = {
        dest.width / 2.0f,
        dest.height / 2.0f
    };

    DrawTexturePro(*texture, source, dest, origin, angle, WHITE);
}

Vector2 Bullet::getPos(){
    return pos;
}

bool Bullet::CheckCollisions(std::vector<Npc>& Npcs){
    if (Lifetime == -3600)
        return true;
    for (Npc& i : Npcs){
        Rectangle NpcBox{
            i.getPos().x,
            i.getPos().y,
            i.GetWH().x * 10.0f,
            i.GetWH().y * 10.0f
        };
        Rectangle BulletBox{
            pos.x,
            pos.y,
            texture->width * 10.0f,
            texture->height * 10.0f
        };

        if (CheckCollisionRecs(BulletBox,NpcBox)){
            i.TakeDamage(damage);
            return true;
        }
    }
    return false;
}