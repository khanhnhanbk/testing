#include "knight.h"

int MAX_HP;
int MAX_LEVEL = 10;
int OLD_LEVEL = 0;
int TYPE_KNIGHT = 0; // 0: normal, 1: author, 2: Lancelot
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
    // <file_mush_ghost>,<file_asclepius_pack>,<file_merlin_pack>
    string file_mush_ghost = support_files.substr(0, support_files.find(','));
    string file_asclepius_pack = support_files.substr(support_files.find(',') + 1, support_files.find_last_of(',') - support_files.find(',') - 1);
    string file_merlin_pack = support_files.substr(support_files.find_last_of(',') + 1, support_files.length() - support_files.find_last_of(',') - 1);

    file.close();
    // adding variables
    MAX_HP = HP;
    if (MAX_HP == 999)
        TYPE_KNIGHT = 1;
    else if (is_prime(MAX_HP))
        TYPE_KNIGHT = 2;


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
        case 11:
            handle_event_11(HP, level, phoenixdown);
            break;
        case 12:
            handle_event_12(HP);
            break;
        case 15:
            handle_event_15(HP, remedy, state);
            break;
        case 16:
            handle_event_16(level, maidenkiss, state);
            break;
        case 17:
            phoenixdown++;
            phoenixdown = phoenixdown > 99 ? 99 : phoenixdown;
            break;
        case 18:
            handle_event_18(HP, file_merlin_pack);
            break;
        case 19:
            handle_event_19(HP, level, remedy, maidenkiss, phoenixdown, rescue, state, file_asclepius_pack);
            break;
        case 99:
            handle_event_99(level, rescue);
            break;
        default:
            // event 13, start 131 or 1324
            if (to_string(event).substr(0, 2) == "13")
            {
                handle_event_13(index, event, HP, level, remedy, maidenkiss, phoenixdown, rescue, state, state_end, file_mush_ghost);
            }
            break;
        }

        // end of event
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        if (state == 1) // small
            if (index >= state_end)
            {
                state = 0;
                HP = HP * 5;
                HP = HP > MAX_HP ? MAX_HP : HP;
            }
            else if (state == 2) // frog
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

bool is_prime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return false;
        if (i * i > n)
            break;
    }
    return true;
}
int nearest_prime(int n)
{
    // nearest prime number larger than n
    n++;
    for (int i = n; i < 1000; i++)
        if (is_prime(i))
            return i;
    return 1000;
}

bool is_knight_dead(int HP, int &phoenixdown, int &rescue, int &state)
{
    if (HP > 0)
        return false;

    if (phoenixdown <= 0)
    {
        rescue = 0;
        return true;
    }

    // revive
    HP = MAX_HP;
    state = 0;
    phoenixdown--;
    return false;
}

bool isMountainShape(int *nums, int numsSize, int &mtx, int &mti)
{

    if (numsSize < 3)
        return false; // mountain shape requires at least 3 elements
    int peak = -1, i = 0;
    // search for the peak
    while (i < numsSize - 1 && nums[i] < nums[i + 1])
        i++;
    if (i == 0 || i == numsSize - 1)
    {
        mtx = -2;
        mti = -3;
        return false;
    } // peak can't be first or last element
    peak = i;
    // check descending property
    while (i < numsSize - 1 && nums[i] > nums[i + 1])
        i++;
    if (i == numsSize - 1 && peak > 0)
    {
        mtx = peak;
        mti = i;
        return true;
    }
    mtx = -2;
    mti = -3;
    return false;
}

void handle_event_1_to_5(int index, int event, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue, int &state)
{

    int levelO = calculateLevel(index);

    if (level > levelO || TYPE_KNIGHT != 0)
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
    if (level > levelO || TYPE_KNIGHT != 0)
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
        return;
    }

    state = 1;
    state_end = index + 3;
    HP = HP < 5 ? 1 : HP / 5;
}
void handle_event_7(int index, int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue, int &state, int &state_end)
{
    int levelO = calculateLevel(index);
    if (level > levelO || TYPE_KNIGHT != 0)
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
void handle_event_11(int &HP, int level, int phoenixdown)
{
    int n1 = ((level + phoenixdown) % 5 + 1) * 3;
    int s1 = 100 * n1 - n1 * n1;
    HP += (s1 % 100);
    HP = nearest_prime(HP);
    if (HP > MAX_HP)
    {
        HP = MAX_HP;
    }
}
void handle_event_12(int &HP)
{
    if (HP > 1)
    {
        int prev = 1, cur = 1;
        while (cur <= HP)
        {
            int temp = cur;
            cur += prev;
            prev = temp;
        }
        HP = prev;
    }
}
void handle_event_13(int index, int event_code, int &HP, int &level,
                     int &remedy, int &maidenkiss, int &phoenixdown,
                     int &rescue, int &state, int &state_end, string filename)
{
    string mush = to_string(event_code).substr(2);
    // readfile
    ifstream file(filename);
    int n2;
    file >> n2;
    int *numbers = new int[n2];
    for (int i = 0; i < n2; i++)
    {
        file >> numbers[i];
    }
    file.close();

    for (size_t i = 0; i < mush.length(); i++)
    {
        if (mush[i] == '1')
        {
            // find maxpos in numbers
            int maxpos = 0;
            int minpos = 0;
            for (int j = 0; j < n2; j++)
            {
                if (numbers[j] >= numbers[maxpos])
                    maxpos = j;
                if (numbers[j] <= numbers[minpos])
                    minpos = j;
            }
            HP = HP - (maxpos + minpos);
            if (is_knight_dead(HP, phoenixdown, rescue, state))
            {
                delete[] numbers;
                return;
            }
        }
        else if (mush[i] == '2')
        {
            int mtx, mti;
            isMountainShape(numbers, n2, mtx, mti);

            HP = HP - (mtx + mti);
            if (is_knight_dead(HP, phoenixdown, rescue, state))
            {
                delete[] numbers;
                return;
            }
            HP = HP > MAX_HP ? MAX_HP : HP;
        }
        else if (mush[i] == '3')
        {
            // – xi = −xi nếu xi < 0
            // – xi = (17 ∗ xi + 9)%257
            for (int i = 0; i < n2; i++)
            {
                if (numbers[i] < 0)
                    numbers[i] = -numbers[i];
                else
                    numbers[i] = (17 * numbers[i] + 9) % 257;
            }
            int maxpos = 0;
            int minpos = 0;
            for (int j = 0; j < n2; j++)
            {
                if (numbers[j] > numbers[maxpos])
                    maxpos = j;
                if (numbers[j] < numbers[minpos])
                    minpos = j;
            }
            HP = HP - (maxpos + minpos);
            if (is_knight_dead(HP, phoenixdown, rescue, state))
            {
                delete[] numbers;
                return;
            }
        }
        else if (mush[i] == '4')
        {
            // find second max in 3-first elements
            int maxpos = 0;
            int minpos = 0;
            for (int j = 0; j < 3; j++)
            {
                if (numbers[j] > numbers[maxpos])
                    maxpos = j;
                if (numbers[j] < numbers[minpos])
                    minpos = j;
            }
            int secondmaxpos = 0;
            int secondminpos = 0 + 1 + 2 - maxpos - minpos;
            if (numbers[secondmaxpos] == numbers[maxpos])
                secondmaxpos = -5;
            int max2 = secondmaxpos >= 0 ? numbers[maxpos] : -7;
            HP = HP - (max2 + numbers[secondminpos]);
            if (is_knight_dead(HP, phoenixdown, rescue, state))
            {
                delete[] numbers;
                return;
            }
            HP = HP > MAX_HP ? MAX_HP : HP;
        }
    }
    delete[] numbers;
}
void handle_event_15(int &HP, int &remedy, int &state)
{
    if (state == 1)
    {
        HP = HP * 5;
        HP = HP > MAX_HP ? MAX_HP : HP;
        state = 0;
        return;
    }
    if (remedy < 99)
        remedy++;
}

void handle_event_16(int &level, int &maidenkiss, int &state)
{
    if (state == 2)
    {
        level = OLD_LEVEL;
        state = 0;
        return;
    }
    if (maidenkiss < 99)
        maidenkiss++;
}
void handle_event_19(int &HP, int &level, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue, int &state, std::string filename)
{
    if (filename == "")
        return;

    ifstream file(filename);
    int r1, c1;
    file >> r1 >> c1;
    int **matrix = new int *[r1];
    for (int i = 0; i < r1; i++)
    {
        matrix[i] = new int[c1];
        for (int j = 0; j < c1; j++)
        {
            file >> matrix[i][j];
        }
    }
    file.close();

    // read each row
    for (int i = 0; i < r1; i++)
    {
        int sum = 0;
        for (int j = 0; j < c1; j++)
        {
            if (matrix[i][j] == 16)
            {
                handle_event_15(HP, remedy, state);
                sum++;
            }
            else if (matrix[i][j] == 17)
            {
                handle_event_16(level, maidenkiss, state);
                sum++;
            }
            else if (matrix[i][j] == 18)
            {
                phoenixdown++;
                phoenixdown = phoenixdown > 99 ? 99 : phoenixdown;
                sum++;
            }
            if (sum >= 3)
                break;
        }
    }
    filename = "";
}
void handle_event_99(int &level, int &rescue)
{
    if (TYPE_KNIGHT == 1 || (TYPE_KNIGHT == 2 && level >= 8) || level == 10) // author
    {
        level = 10;
        return;
    }
    else
    {
        rescue = 0;
    }
}

string tolower(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] - 'A' + 'a';
    }
    return s;
}
// check string has merlin
int has_merlin(std::string s)
{
    // lowercase
    s = tolower(s);
    if (s.find("merlin") != std::string::npos)
        return 3;
    // check if contains 6 letters in "merlin" without index
    bool check[6] = {false};
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'm')
            check[0] = true;
        else if (s[i] == 'e')
            check[1] = true;
        else if (s[i] == 'r')
            check[2] = true;
        else if (s[i] == 'l')
            check[3] = true;
        else if (s[i] == 'i')
            check[4] = true;
        else if (s[i] == 'n')
            check[5] = true;
    }
    for (int i = 0; i < 6; i++)
    {
        if (!check[i])
            return 1;
    }
    return 2;
}
void handle_event_18(int &HP, std::string filename)
{
    if (filename == "")
        return;

    ifstream file(filename);
    int n9;
    file >> n9;
    string *merlin_strings = new string[n9];
    for (int i = 0; i < n9; i++)
    {
        file >> merlin_strings[i];
    }
    file.close();

    for (int i = 0; i < n9; i++)
    {
        HP *= has_merlin(merlin_strings[i]);
        if (HP > MAX_HP)
        {
            HP = MAX_HP;
            break;
        }
    }
    delete[] merlin_strings;

    filename = "";
}