#include "knight.h"

bool compareFiles(std::string filename1, std::string filename2)
{
    std::ifstream file1(filename1);
    std::ifstream file2(filename2);
    char char1, char2;

    if (!file1 || !file2)
    {
        return false;
    }

    while (file1.get(char1) && file2.get(char2))
    {
        if (char1 != char2)
        {
            return false;
        }
    }

    return char1 == char2;
}
int main()
{
    for (int i = 1; i < 3; i++)
    {
        string folder = "./testcases/test" + to_string(i) + "/";
        ofstream out(folder + "output");
        streambuf *coutbuf = cout.rdbuf();
        cout.rdbuf(out.rdbuf());

        string file_input = folder + "tc1_input";

        // change line 3 in tc1_input
        ifstream file(file_input);
        string line1, line2, line3;
        getline(file, line1);
        getline(file, line2);
        getline(file, line3);
        // add folder to line
        string file_mush_ghost = line3.substr(0, line3.find(','));
        string file_asclepius_pack = line3.substr(line3.find(',') + 1, line3.find_last_of(',') - line3.find(',') - 1);
        string file_merlin_pack = line3.substr(line3.find_last_of(',') + 1, line3.length() - line3.find_last_of(',') - 1);

        file_mush_ghost = folder + file_mush_ghost;
        file_asclepius_pack = folder + file_asclepius_pack;
        file_merlin_pack = folder + file_merlin_pack;
        string line3_new = file_mush_ghost + "," + file_asclepius_pack + "," + file_merlin_pack;
        file.close();
        // rewrite line 3 in tc1_input
        ofstream file2(file_input);
        file2 << line1 << endl
              << line2 << endl
              << line3_new << endl;
        file2.close();

        int HP, level, remedy, maidenkiss, phoenixdown, rescue;
        adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);

        ofstream file3(file_input);
        file3 << line1 << endl
              << line2 << endl
              << line3 << endl;
        file3.close();

        // compare output
        // Restore cout
        cout.rdbuf(coutbuf);
        string file_output = folder + "output";
        string file_output_expected = folder + "expected";
        
        bool isSame = compareFiles(file_output, file_output_expected);
        if (isSame)
        {
            cout << "Testcase " << i << " passed" << endl;
        }
        else
        {
            cout << "Testcase " << i << " failed" << endl;
        }
    }
    return 0;
}