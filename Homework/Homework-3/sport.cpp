#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

class Sport {
public:
    Sport (string name, bool outdoor) : m_name(name), m_outdoor(outdoor) {}
    virtual ~Sport() {}
    bool isOutdoor() const {
        if (m_outdoor == 1) return true;
        return false;
    }
    string name() const { return m_name; }
    virtual string icon() const = 0;
    
private:
    bool m_outdoor;
    string m_name;
   
};

class Snowboarding : public Sport {
    public:
    Snowboarding (string name) : Sport(name, 1) {}
    virtual string icon() const {
        return "a descending snowboarder";
    }
    virtual ~Snowboarding() {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }
};


class Biathlon : public Sport {
public:
    Biathlon (string name, double dist) : Sport(name, 1), km(dist) {}
    virtual string icon() const {
        return "a skier with a rifle";
    }
    virtual ~Biathlon() {
        cout << "Destroying the Biathlon object named " << name() << ", distance " << km << " km." << endl;
    }
private:
    double km;
};

class FigureSkating : public Sport {
    public:
    FigureSkating (string name) : Sport(name, 0) {}
    virtual string icon() const {
        return "a skater in the Biellmann position";
    }
    virtual ~FigureSkating() {
        cout << "Destroying the FigureSkating object named " << name() << "." << endl;
    }
};

void display(const Sport* sp)
{
    cout << sp->name() << " is ";
    if (sp->isOutdoor())
        cout << "an outdoor sport ";
    else
        cout << "an indoor sport ";
    cout << "with an icon showing " << sp->icon() << "." << endl;
}

int main()
{
    Sport* sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
      // Biathlon events have a distance in kilometers
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");

    cout << "Here are the sports." << endl;
    for (int k = 0; k < 4; k++)
        display(sports[k]);

      // Clean up the sports before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete sports[k];
}
