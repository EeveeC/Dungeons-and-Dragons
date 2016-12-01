#include "CharacterBuilder.h"
#include "HumanPlayerStrategy.h"
#include "FriendlyStrategy.h"
#include "AggressorStrategy.h"
#include "../GameData.h"

CharacterBuilder::CharacterBuilder(string fighterType, int level) {
	this->fighterType = fighterType;
	this->fighterLevel = level;
}

Fighter* CharacterBuilder::getCharacter() {
	return this->c_character;
};

void CharacterBuilder::createCharacter() {
	vector<int> singleRoll;
	vector<int> ability;
	for (int i = 0; i < 6; i++) {
		singleRoll = GameData::gameDice->roll("4d6");
		sort(singleRoll.begin(), singleRoll.end(), greater<int>());
		ability.push_back(singleRoll[0] + singleRoll[1] + singleRoll[2]);
	}
	sort(ability.begin(), ability.end(), greater<int>());
	if (this->fighterType == "Bully") {
		CharacterAttr *bullyAttr = new CharacterAttr(ability[3], ability[5], ability[0], ability[2], ability[1], ability[4]);
		this->c_character = new Bully(bullyAttr);
	}
	if (this->fighterType == "Nimble") {
		CharacterAttr *nimbleAttr = new CharacterAttr(ability[3], ability[5], ability[2], ability[0], ability[1], ability[4]);
		this->c_character = new Nimble(nimbleAttr);
	}
	if (this->fighterType == "Tank") {
		CharacterAttr *tankAttr = new CharacterAttr(ability[3], ability[5], ability[2], ability[1], ability[0], ability[4]);
		this->c_character = new Tank(tankAttr);
	}
	for (int i = 0; i < this->fighterLevel-1; i++) {
		this->c_character->levelUp();
	}
}
string CharacterBuilder::getFighterType()
{
	return this->fighterType;
}
int CharacterBuilder::getFighterLevel()
{
	return this->fighterLevel;
}
;

PlayerCharacterBuilder::PlayerCharacterBuilder(string fighterType, int level) : CharacterBuilder(fighterType, level) {};

void PlayerCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("player");
	this->c_character->setTypeOnMap('S');
        this->c_character->setStrategy(new HumanPlayerStrategy());
}

AggressorCharacterBuilder::AggressorCharacterBuilder(string fighterType, int level) : CharacterBuilder(fighterType, level) {};

void AggressorCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("aggressor");
	this->c_character->setTypeOnMap('O');
	this->c_character->setStrategy(new AggressorStrategy());
}

FriendlyCharacterBuilder::FriendlyCharacterBuilder(string fighterType, int level) : CharacterBuilder(fighterType, level) {};

void FriendlyCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("friendly");
	this->c_character->setTypeOnMap('C');
	this->c_character->setStrategy(new FriendlyStrategy());
}

