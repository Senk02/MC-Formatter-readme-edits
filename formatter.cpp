#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>

using namespace std;

void ct_recipe();
void ct_print(string, string, string, const vector<string>&);
string get_main_name(const string&);
string get_recipe_name(const string&);

int main()
{
    int val;
    cout << "\n------------------------------------\n"
         << "CT Formatter\n"
         << "------------------------------------\n"
         << "[1] CraftTweaker Table Recipe\n"
         << "[2] Extended Crafting 3x3\n"
         << "[3] Extended Crafting 5x5\n"
         << "[4] Extended Crafting 7x7\n"
         << "[5] Extended Crafting 9x9\n"
         << "------------------------------------\n\n"
         << "Select Recipe Type: ";
    
    cin >> val;
    switch (val)
    {
        case 1:
            cin.ignore();
            ct_recipe();
            break;
        default:
            break;
    }
    

    return 0;
}

void ct_recipe()
{
    string input_string;
    string item_name_main;
    string item_name_recipe;
    string item_name;
    string substring;

    vector<string> ingredient(9);

    size_t pos;
    size_t ingredient_index;
    size_t end_pos;

    while (true)
    {
        cout << "\nPaste in the unfromatted recipe below, type exit to end program:\n";
        getline(cin, input_string);

        if (input_string == "exit")
        {
            break;
        }
        else
        {
        pos = input_string.find('<');
        ingredient_index = 0;

        while (pos != string::npos && ingredient_index < 9)
        {
            end_pos = input_string.find('>', pos);
            if (end_pos != string::npos)
            {
                substring = input_string.substr(pos + 1, end_pos - pos - 1);

                if (item_name.empty())
                {
                    item_name = substring;
                }
                else
                {
                    ingredient[ingredient_index] = substring;
                    ++ingredient_index;
                }

                pos = input_string.find('<', end_pos);
            }
            else
            {
                break;
            }
        }
        item_name_main = get_main_name(item_name);
        item_name_recipe = get_recipe_name(item_name);
        ct_print(item_name, item_name_main, item_name_recipe, ingredient);
        }
    }
}

string get_main_name(const string& item_name)
{
    size_t colon_pos = item_name.find(':');
    if (colon_pos == string::npos)
    {
        return "";
    }

    string item_name_main = item_name.substr(colon_pos + 1);

    for (size_t i = 0; i < item_name_main.length(); ++i)
    {
        if (item_name_main[i] == '_')
        {
            item_name_main[i] = ' ';
        }
    }

    bool capitalize_next = true;
    for (size_t i = 0; i < item_name_main.length(); ++i)
    {
        if (capitalize_next && islower(item_name_main[i]))
        {
            item_name_main[i] = toupper(item_name_main[i]);
            capitalize_next = false;
        }
        else if (isspace(item_name_main[i]))
        {
            capitalize_next = true;
        }
    }

    return item_name_main;
}


string get_recipe_name(const string& item_name)
{
    string item_name_recipe;

    for (char ch : item_name)
    {
        if (ch == ':' || ch == '_')
        {
            continue;
        }
        item_name_recipe += ch;
    }

    bool capitalize_next = true;
    for (char& ch : item_name_recipe)
    {
        if (capitalize_next && islower(ch))
        {
            ch = toupper(ch);
            capitalize_next = false;
        }
        else if (isspace(ch))
        {
            capitalize_next = true;
        }
    }

    return item_name_recipe;
}


void ct_print(string item_name, string item_name_main, string item_name_recipe, const vector<string>& ingredient)
{
    cout << "\n<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n\n"
         << setfill(' ') << "#" << item_name_main << "\n"
         << setw(4) << " " << "recipes.addShaped(\"" << item_name_recipe << "\",\n"
         << setw(8) << " " << "<" << item_name << ">,\n"
         << setw(8) << " " << "[[<" << ingredient[0] << ">, <" << ingredient[1] << ">, <" << ingredient[2] << ">],\n"
         << setw(8) << " " << "[<" << ingredient[3] << ">, <" << ingredient[4] << ">, <" << ingredient[5] << ">],\n"
         << setw(8) << " " << "[<" << ingredient[6] << ">, <" << ingredient[7] << ">, <" << ingredient[8] << ">]]);\n"
         << "\n<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>\n";
}