#include <iostream>
#include <set>
#include <bits/stdc++.h> //to lower string in input function
#include <windows.h>     //to sleep
#include <queue>         //for the gun
#include <ctime>         //for random
#include <cstdlib>       // same

using namespace std;
// learn classes, make object of user class
// best of five, l3 format

// SWITCH STATEMENTS

// used for getUserInput;
map<string, int> acceptableActions = {{"shoot self", 0}, {"Shoot opponent", 1}, {"Gods Liability Waiver", 2}, {"Beer", 3}, {"Magnifying Glass",4}, {"Saw",5}, {"Handcuffs",6}, { "Cigarette",7}}; // allowed actions

// objects
vector<string> allObjects = {"Gods Liability Waiver", "Beer", "Magnifying Glass", "Saw", "Handcuffs", "Cigarette"};

bool conductRound(User *p1, User *p2, int round); // Used to conduct a round
void round(User *attacker, User *defendent,queue<string> gun, int dam); //the round
int getUserInput();       // used for actions
queue<string> generateGun(); // used to generate gun

int generateRandomBetween(int a, int b); // Used to get random numbers

void showChamber(string *chamber[], int &letters); // to show whats in the chamber

vector<string> generateObjects(); // used to generate objects (this needs to be passed)

class User
{
private:
    int m_health;
    int m_bufferHealth;
    int m_wins;
    string m_name;
    vector<string> m_tools;
    bool m_permadeath;
    bool m_alive;

public:
    User(){
        m_health=4;
        m_bufferHealth=2;
        m_wins=0;
        m_permadeath=false;
        m_alive=true;
    }

    void printHealth(){
        if(!m_alive){
            cout << m_name << "died..." <<endl;
        }
        cout << m_name <<" has " <<m_health+m_bufferHealth <<" health left"<<endl;
    }

    int getWins()
    {
        return m_wins;
    }

    void wonMatch()
    {
        m_wins++;
    }

    string getName()
    {
        return m_name;
    }

    void askName()
    {
        cout << "Enter your name : " << endl;
        cin >> m_name;
        cout << "The name is " << m_name << endl;
    }

    void printObjects()
    {
        cout << this->m_name << " currently has:" << endl;
        if ((this->m_tools).empty())
        {
            cout << "nothing..." << endl;
        }
        else
        {
            for (int i = 0; i < (this->m_tools).size(); i++)
            {
                cout << (this->m_tools)[i] << endl;
            }
        }
    }

    void addObjectsToTools(vector<string> *objs)
    {
        while (!objs->empty())
        {
            if ((this->m_tools).size() == 8)
            {
                cout << "You have enough items. make it work." << endl;
                break;
            }
            m_tools.push_back(objs->front());
            objs->erase(objs->begin());
        }
    }

    void shot(int dam){
        if(m_permadeath){
            m_alive=false;
        }
        else{
            m_health-=dam;
            if(m_health<0){
                m_permadeath=!m_permadeath;
                cout <<"Careful "<<m_name<< " ..., your'e on thin ice. Defibulators have been deactivated."<<endl;
            }
        }
    }

    void usedObject(string obj){
        
    }
};

int main()
{
    while (true)
    {
        // Where matchups occur
        User player1, player2;
        int round = 1;

        // Setup
        cout << "Player 1-";
        player1.askName();
        cout << "Player 2-";
        player2.askName();

        cout << "Ready?" << endl;

        while ((player1.getWins() < 3) || (player2.getWins() < 3))
        {
            for (int i = 0; i < 3; i++)
            {
                cout << "." << endl;
            }

            // printing score
            cout << "Current Score" << endl;
            cout << player1.getName() << ": " << player1.getWins() << endl;
            cout << player2.getName() << ": " << player2.getWins() << endl;
            cout << "------ ROUND " << round << " ------" << endl;

            // Where the rounds happen
            bool result = conductRound(&player1, &player2, round);

            if (result)
                player1.wonMatch();
            else
                player2.wonMatch();

            round++;
        }
    }
}

bool conductRound(User *p1, User *p2, int round)
{
    // true means player 1 won

    queue<string> gun = generateGun();

    // give them the objects

    p1->addObjectsToTools(&generateObjects());
    p1->printObjects();
    p2->addObjectsToTools(&generateObjects());
    p2->printObjects();

    // loop the round/actions
    round(p1,p2,gun,0);
    // trigger permadeath
    // return the winner
}

void round(User *attacker, User *defendent, queue<string> *g,int dam)//pass dam as 0 initially
{
    /*
    map<string, int> acceptableActions = {{"shoot self", 0}, {"Shoot opponent", 1}, {"Gods Liability Waiver", 2}, {"Beer", 3}, {"Magnifying Glass",4}, {"Saw",5}, {"Handcuffs",6}, { "Cigarette",7}}; // allowed actions
    */
    int action = getUserAction();
    int damage=dam;

    switch (action) //In deafult case add check for dead
    {
        case 0:
            string bullet=(*g).front();
            g->pop();

            if(bullet.find("Live")!=string::npos){
                cout <<"Uh Oh..."<<endl;
                damage++;
                attacker->shot(damage);
                round(defendent,attacker,g,0);
            }
            else{
                cout <<"Lady Luck Favors You..."<<endl;
                round(attacker,defendent,g,0);
            }

        case 1:
            string bullet=(*g).front();
            g->pop();

            if(bullet.find("Live")!=string::npos){
                cout <<"Good Choice..."<<endl;
                damage++;
                defendent->shot(damage);
            }
            else{
                cout <<"Lady Luck Favors " << defendent->getName()<<endl;
            }
            round(attacker,defendent,g,0);
        
        case 2:
            cout<<"Even God Can't Save You Now..."<<endl;
            round(attacker,defendent,g,0);
        
        case 3:
            string bullet=(*g).front();
            g->pop();
            cout << "A "<<bullet<<"\b  \b Flies Out..."<<endl;
            round(attacker,defendent,g,0);

        case 4:
            string bullet=(*g).front();
            cout << "Hmm... Its a "<<bullet<<"\b  \b"<<endl;
            round(attacker,defendent,g,0);



    }

}

int getUserAction()
{
    string input;
    cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::tolower); // lowercase

    if (acceptableActions.count(input) == 0 || acceptableActions.find(input)==acceptableActions.end())
    {
        cout << "Please enter a valid input: " << endl;
        input = getUserInput();
    }

    return acceptableActions[input];
}

queue<string> generateGun()
{
    queue<string> rounds;
    int numberOfRounds = generateRandomBetween(4, 8);
    int numberOfCharacters = 0;
    string basic[numberOfRounds];

    for (int i = 0; i < numberOfRounds; i++)
    {
        if (generateRandomBetween(0, 2) % 2 == 0)
        {
            rounds.push("Live, ");
            basic[i] = "Live, ";
            numberOfCharacters += 6;
        }
        else
        {
            rounds.push("Blank, ");
            numberOfCharacters += 7;
            basic[i] = "Blank, ";
        }
    }

    showChamber(basic, numberOfCharacters);

    return rounds;
}

void showChamber(string *chamber, int &letters)
{

    auto temp = chamber;
    shuffle(temp->front(), temp->back(), generateRandomBetween(0, 100));

    cout << "Pay close attention";
    for (int i = 0; i < 3; i++)
    {
        Sleep(750);
        cout << ". ";
    }
    cout << endl;

    for (int i = 0; i < size(*temp); i++)
    {
        cout << *(temp + i);
    }

    Sleep(3000);

    while (letters > 0)
    {
        cout << "\b \b";
        letters--;
    }

    cout << "Entering the shells in a random order";
    for (int i = 0; i < 3; i++)
    {
        Sleep(750);
        cout << ". ";
    }
    cout << endl;
}

int generateRandomBetween(int a, int b)
{
    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    return (4 + rand() % (b - a + 1));
}

vector<string> generateObjects()
{
    vector<string> obj;

    for (int x = 0; x < 4; x++)
    {
        obj.insert(obj.end(), allObjects[generateRandomBetween(0, allObjects.size() - 1)]);
    }

    return obj;
}
