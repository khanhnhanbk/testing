#include "knight.h"

int MAX_HP;
int MAX_LEVEL = 10;
int OLD_LEVEL = 0;
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)
{
    // read file
    ifstream file(file_input);

    file >> HP >> level >> remedy >> maidenkiss >> phoenixdown;
    rescue = -1; // event not ended

    // event
    string events;
    getline(file, events);
    getline(file, events);
    // file supports
    string support_files;
    getline(file, support_files);

    file.close();


    // adding variables
    MAX_HP = HP;
    int state = 0; // 0: normal, 1: small, 2: frog
    int state_end = 0;
    OLD_LEVEL = level;

    // tokenize events by ' '
    int event;
    int index = 0;

    
    // read event from events by ' '
    stringstream ss(events);
    while (ss >> event && rescue == -1)
    {
        index++;
        // cout << "event: " << event << endl;
        switch (event)
        {
        case 0:
            rescue = 1;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            handle_event_1_to_5(index, event, HP, level, remedy, maidenkiss, phoenixdown, rescue, state);
            break;
        case 6:
            if (state != 0) // skip if not normal
                    break;
            handle_event_6(index, HP, level, remedy, maidenkiss, phoenixdown, rescue, state, state_end);
            break;
        case 7:
            if (state != 0) // skip if not normal
                    break;
            handle_event_7(index, HP, level, remedy, maidenkiss, phoenixdown, rescue, state, state_end);
            break;
        default:
            break;
        }
        if (state == 1)
            if (index >= state_end)
                {
                    state = 0;
                    HP = HP * 5;
                    HP = HP > MAX_HP ? MAX_HP : HP;
                }
        else if (state == 2)
            if (index >= state_end)
                {
                    state = 0;
                    level = OLD_LEVEL;
                }
        
    }

    if (HP > 0)
        rescue = 1;
    // display
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
}
int calculateLevel(int index)
{
    int b = index % 10;
    int levelO = (index > 6) ? ((b > 5 ? b : 5)) : b;
    return levelO;
}
void handle_event_1_to_5(int index, int event, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue, int &state)
{

    int levelO = calculateLevel(index);

    if (level > levelO)
    {
        level = level + 1;
        level = level > MAX_LEVEL ? MAX_LEVEL : level;
        return;
    }
    if (level == levelO)
        return;

    float baseDamage[6] = {1, 1.5, 4.5, 7.5, 9.5};
    int damage = baseDamage[event - 1] * levelO * 10;
    HP = HP - damage;
    if (HP <= 0)
    {
        if (phoenixdown == 0)
        {
            rescue = 0;
        }
        else
        {
            // revive
            HP = MAX_HP;
            phoenixdown--;
            state = 0;
        }
    }
}

void handle_event_6(int index, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue, int &state, int &state_end)
{
    int levelO = calculateLevel(index);
    if (level > levelO)
    {
        level = level + 2;
        level = level > MAX_LEVEL ? MAX_LEVEL : level;
        return;
    }
    if (level == levelO)
        return;
    if (remedy > 0)
    {
        remedy--;
        HP = (HP / 5) * 5;
        return;
    }

    state = 1;
    state_end = index + 3;
    HP = HP < 5 ? 1 : HP / 5;
}
void handle_event_7(int index, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue, int &state, int &state_end)
{
    int levelO = calculateLevel(index);
    if (level > levelO)
    {
        level = level + 2;
        level = level > MAX_LEVEL ? MAX_LEVEL : level;
        return;
    }
    if (level == levelO)
        return;
    if (maidenkiss > 0)
    {
        maidenkiss--;
        return;
    }

    state = 2;
    state_end = index + 3;
    OLD_LEVEL = level;
    level = 1;
}