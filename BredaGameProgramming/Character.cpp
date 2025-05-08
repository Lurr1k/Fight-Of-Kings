#include "Character.h"


Character::Character(const std::string& texturePath, float xCoordinate, float yCoordinate, const std::string& battleSide, const std::string& soundPath, const std::string& characterName, float healthLimit, float characterAttackRange, float attackDamage, float characterVelocity, float targetRange) {
    
    hp = healthLimit;
    maxHp = healthLimit;
    attackRange = characterAttackRange;
    name = characterName;
    damage = attackDamage;
    velocity = characterVelocity;
    sightRange = targetRange;
    heroOrEnemy = battleSide;
    time = 0;

    
    texture.loadFromFile(texturePath);
    character.setTexture(texture, true);

    if (name != "Tower") {
        Audio::instance().character_sound(soundPath);
    }


    barBackground.setSize({ 40, 4 });
    barBackground.setOrigin({ 20, 0 });
    barBackground.setFillColor(sf::Color::Green);

    character.setPosition({xCoordinate, yCoordinate});
    sf::Vector2f bounds = character.getLocalBounds().size;
    character.setOrigin({ bounds.x / 2, bounds.y / 2 });
}

// Coordinates the movement and attack logic for the character
void Character::move_and_attack(std::vector<std::unique_ptr<Character>>& enemies, float& deltaTime) {
    time = deltaTime;
    if (name != "Tower") {
        int targetIndex = identify_closest_target(enemies);
        target = enemies[targetIndex]->get_position();
        sf::Vector2f currentPos = character.getPosition();
        float xDistance = target.x - currentPos.x;
        float yDistance = target.y - currentPos.y;
        float distance = (std::sqrt(xDistance * xDistance + yDistance * yDistance));
        attacking = false;
        if (distance <= attackRange) {
            if (enemies[targetIndex]->get_hp() > 0) {
                enemies[targetIndex]->take_damage(damage);
                attacking = true;
            }
            else {
                delete_target(enemies[targetIndex].get(), enemies);
            }
        }
        else if ((currentPos.y >= 450) and (currentPos.y <= 510) and not ((currentPos.x >= 50 and currentPos.x <= 154) or (currentPos.x >= 595 and currentPos.x <= 700))) {
            if (currentPos.y < 480) {
                character.setPosition({ currentPos.x, 450 });
            }
            else {
                character.setPosition({ currentPos.x, 510 });
            }

            if (currentPos.x < 375) {
                character.move({ -velocity * time, 0.f });
                character.setRotation(sf::degrees(-90));
            }
            else {
                character.move({ velocity * time, 0.f });
                character.setRotation(sf::degrees(90));
            }
        }
        else {
            move_character(xDistance, yDistance, time, currentPos);
        }

    }
}

// Moves the character towards the target
void Character::move_character(float xDistance, float yDistance, float& time, sf::Vector2f& currentPos) {
    std::string moving = "";
    if (xDistance < -2 and not (currentPos.y >= 450 and currentPos.y <= 510)) {
        moving = "left";
        character.move({ -velocity * time, 0.f });
        character.setRotation(sf::degrees(-90));
    }
    else if (xDistance > 2 and not (currentPos.y >= 450 and currentPos.y <= 510)) {
        moving = "right";
        character.move({ velocity * time, 0.f });
        character.setRotation(sf::degrees(90));
    }

    if (yDistance < -2) {
        character.move({ 0, -velocity * time });
        if (moving == "left") {
            character.setRotation(sf::degrees(-45));
        }
        else if (moving == "right") {
            character.setRotation(sf::degrees(45));
        }
        else {
            character.setRotation(sf::degrees(0));
        }
    }

    else if (yDistance > 2) {
        character.move({ 0.f, velocity * time });
        if (moving == "left") {
            character.setRotation(sf::degrees(-135));
        }
        else if (moving == "right") {
            character.setRotation(sf::degrees(135));
        }
        else {
            character.setRotation(sf::degrees(180));
        }
    }
}

// Deletes the enemy character
void Character::delete_target(Character* targetCharacter, std::vector<std::unique_ptr<Character>>& enemies) {
    for (std::size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].get() == targetCharacter) {
            enemies.erase(enemies.begin() + i);

            break;
        }
    }

}

// Returns character's current position
sf::Vector2f Character::get_position() {
    return character.getPosition();
}

// Displays the character
void Character::draw_character(sf::RenderWindow& window) {
    window.draw(character);
}

// Decreases the character's hp by the damage dealt to it
void Character::take_damage(float damageTaken) {
    

    hp -= damageTaken*time;
    
}

// Returns the characters name (type)
std::string Character::get_name() {

    return name;
}

// Identifies the closest enemy character and returns its index
int Character::identify_closest_target(std::vector<std::unique_ptr<Character>>& enemies) {
    sf::Vector2f posDifference;
    float newDistance;
    int chosenIndex = -1;
    float distance = 1000;
    for (int i = 0; i < enemies.size(); i++) {
        posDifference = character.getPosition() - enemies[i]->get_position();
        newDistance = std::sqrt((posDifference.x * posDifference.x) + (posDifference.y * posDifference.y));
        if (newDistance < distance and newDistance < sightRange) {
            distance = newDistance;
            chosenIndex = i;
        }
    }
    if (chosenIndex == -1) {
        distance = 1000;
        for (int i = 0; i < enemies.size(); i++) {
            posDifference = character.getPosition() - enemies[i]->get_position();
            newDistance = std::sqrt((posDifference.x * posDifference.x) + (posDifference.y * posDifference.y));
            if (newDistance < distance and (enemies[i]->get_name() == "Tower")) {
                distance = newDistance;
                chosenIndex = i;
            }
        }
    }
    if (chosenIndex == -1) {
        chosenIndex = 0;
    }
    return chosenIndex;
}

// Displays and manages the healthbar
void Character::display_health_bar(sf::RenderWindow& window) {
    sf::Vector2f characterToBarDistance;
    if (hp < 0) {
        hp = 0;
    }
    else if (hp > maxHp) {
        hp = maxHp;
    }
    if (heroOrEnemy == "enemy") {
        characterToBarDistance = { 0, -30 };
        barBackground.setFillColor(sf::Color::Red);
        healthBar.setFillColor(sf::Color::Green);
    }
    else {
        characterToBarDistance = { 0, 30 };
        barBackground.setFillColor(sf::Color::Green);
        healthBar.setFillColor(sf::Color::Red);
    }

    sf::Vector2f healthBarPos = character.getPosition() + characterToBarDistance;
    barBackground.setPosition(healthBarPos);
    healthBar.setSize({ 30 * (hp/maxHp), 2});
    healthBar.setOrigin({0,0});
    healthBar.setPosition(healthBarPos + sf::Vector2f({-15, 1}));

    window.draw(barBackground);
    window.draw(healthBar);
    

}

// Returns the character's current hp
float Character::get_hp() {

    return hp;
}

// Displays the character
void Archer::draw_character(sf::RenderWindow& window){
    window.draw(character);

    if (attacking) {
        if (not arrow.is_flying()) {
            arrow.shoot(character.getPosition(), target);
        }
        arrow.draw_arrow(window);
        arrow.move_arrow(target, time);
        
    }

}


