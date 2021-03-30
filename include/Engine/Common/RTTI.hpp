#pragma once
#include <string>
#include <iostream>

class RTTI {
public:
  std::string m_ClassName;
  const RTTI& m_Parent;
  static RTTI Default;
  RTTI(const char* name, const RTTI& parent_type = RTTI::Default);
  bool IsExactly(const RTTI& other) const;
  bool IsA(const RTTI& other) const;  // IsExactly () recursif
};


#define RTTI_DECLARATION \
	static RTTI rtti;

#define RTTI_DEFINITION_BASE(ClassName) \
	RTTI ClassName::rtti(#ClassName);

#define RTTI_DEFINITION(ClassName, parent) \
	RTTI ClassName::rtti(#ClassName, parent::rtti);


/*
struct GameObject {
  RTTI_DECLARATION  //GameObject.hpp
};
RTTI_DEFINITION_BASE(GameObject); //GameObject.cpp


struct Player : public GameObject {
  RTTI_DECLARATION
};
RTTI_DEFINITION(Player, GameObject);


struct Enemy : public GameObject {
  RTTI_DECLARATION
};
RTTI_DEFINITION(Enemy, GameObject);


struct Boss : public Enemy {
  RTTI_DECLARATION
};
RTTI_DEFINITION(Boss, Enemy); //Relation d'heritage


//cas d'utilisation
void main(void) {
  Boss boss;
  std::cout << boss.rtti.m_ClassName << std::endl;

  bool isPlayer = boss.rtti.IsA(Player::rtti);
  bool isEnemy  = boss.rtti.IsA(Enemy::rtti);
}
*/