//DECLERATIONS

class Character
{
public:
	Character(string name);
	void name() const;
	virtual void printWeapon() const = 0;
	virtual void attackAction() const;
	virtual ~Character();
private:
	string m_name;
};

class Dwarf : public Character
{
public:
	Dwarf(string name);
	virtual void printWeapon() const;
	~Dwarf();
private:
};

class Elf : public Character
{
public:
	Elf(string name, int arrows);
	virtual void printWeapon() const;
	~Elf();
private:
	int m_arrows;
};

class Boggie : public Character
{
public:
	Boggie(string name);
	virtual void printWeapon() const;
	virtual void attackAction() const;
	~Boggie();
private:
};

//IMPLEMENTATIONS

//Character
Character::Character(string name)
{
	this->m_name = name;
}

void Character::name() const
{
	cout << m_name;
}

void Character::attackAction() const
{
	cout << "rushes toward the enemy";
}

Character::~Character() {}

//Dwarf
Dwarf::Dwarf(string name) : Character(name) {}

void Dwarf::printWeapon() const
{
	cout << "an axe";
}

Dwarf::~Dwarf()
{	
	cout << "Destroying ";
	name();
	cout << " the dwarf" << endl;
}

//Elf
Elf::Elf(string name, int arrows) : Character(name), m_arrows(arrows) {}

void Elf::printWeapon() const
{
	cout << "a bow and quiver of " << m_arrows << " arrows";
}

Elf::~Elf()
{
	cout << "Destroying ";
	name();
	cout << " the elf" << endl;
}

//Boggie
Boggie::Boggie(string name) : Character(name) {}

void Boggie::printWeapon() const
{
	cout << "a short sword";
}

void Boggie::attackAction() const
{
	cout << "whimpers";
}

Boggie::~Boggie()
{
	cout << "Destroying ";
	name();
	cout << " the boggie" << endl;
}


//EXECUTION

/*void strike(const Character* cp)
{
	cp->name(); cout << ", wielding ";
	cp->printWeapon();
	cout << ", "; cp->attackAction(); cout << "." << endl;
}

int main()
{
	Character* characters[4];
	characters[0] = new Dwarf("Gimlet");
	// Elves have a name and initial number of arrows in their quiver
	characters[1] = new Elf("Legolam", 10);
	characters[2] = new Boggie("Frito");
	characters[3] = new Boggie("Spam");

	cout << "The characters strike!" << endl;
	for (int k = 0; k < 4; k++)
		strike(characters[k]);

	// Clean up the characters before exiting
	cout << "Cleaning up" << endl;
	for (int k = 0; k < 4; k++)
		delete characters[k];
}*/