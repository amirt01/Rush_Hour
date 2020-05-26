#include "stdafx.h"
#include "Entity.h"

void Entity::setTexture(sf::Texture& texture_sheet)
{
	sprite.setTexture(texture_sheet);
}

void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::addAnimation(const std::string key, float animation_time, int animation_level, int frames, int width, int height)
{
	animations[key] = new Animation(
		sprite, textureSheet,
		animation_time,
		animation_level, frames, width, height
	);
}

void Entity::render(sf::RenderTarget* renderTarget)
{
	std::cout << sprite.getPosition().x << std::endl;
	renderTarget->draw(sprite);
}
