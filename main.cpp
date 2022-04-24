// https://www.youtube.com/watch?v=4ls9cHMpgvk for the tutorial
// 08 / Feb / 2022 (My 14th birthday!)

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>

using namespace std;

class LoginManager{
    public:
        loginManager() {
            accessGranted = 0;
        }
        void login() {
            cout << "Hey! enter your username and password.\n"
            << "Username: ";
            getline(cin, userNameAttempt);

            int usrID = checkFile(userNameAttempt, "users.dat");
            if (usrID != 0) {
                cout << "Password: ";
                getline(cin, passwordAttempt);
                passwdID = checkFile(passwordAttempt, "passwords.dat");
                if (usrID == passwdID) {
                    cout << "Welcome user!" << endl;
                    login();
                } else {
                    cout << "Incorrect password! try again." << endl;
                    login();
                }
            } else {
                cout << "Incorrect username! try again." << endl;
                login();
            }
        }

        void addUser(const string username, const string password) {
            if (checkFile(username, "users.dat") != 0) {
                cout << "That username is not availble." << endl;
                return;
            }

            int id = 1 + getLastID();
            saveFile(username, "users.dat", id);
            saveFile(password, "passwords.dat", id);
        }

        int getLastID() {
            fstream file;
            file.open("users.dat", ios::in);
            file.seekg(0, ios::end);

            if (file.tellg() == -1)
                return 0;

            string s;
            for (int i = -1; s.find("#") == string::npos; i--) {
                file.seekg(i, ios::end);
                file >> s;
            }

            file.close();
            s.erase(0, 4);

            int id;
            istringstream(s) >> id;

            return id;
        }

        int checkFile(string attempt, const char* p_file) {
            string line;
            fstream file;

            string currentLine;
            long long eChar;

            file.open(p_file, ios::in);

            while (1) {
                file >> currentLine;
                if (currentLine.find("#ID:") != string::npos) {
                    if (attempt == line) {
                        file.close();
                        currentLine.erase(0, 4);
                        int id;
                        istringstream(currentLine) >> id;
                        return id;
                    } else {
                        line.erase(line.begin(), line.end());
                    }
                } else {
                    istringstream(currentLine) >> eChar
                    line += (char)decrypt(eChar);
                    currentChar = "";
                }

                if (file.peek() == EOF) {
                    file.close();
                    return 0;
                }
            }
        }

        void saveFile(string p_line, const char* p_file, const int& id) {
            fstream file;
            file.open(p_file, ios::app);
            file.seekg(0, ios::end);

            if (file.tellg() != 0) {
                file << "\n";
            }

            file.seekg(0, ios::beg);

            for (int i = 0; i < p_line.length(); i++) {
                file << encrypt(p_line[i]);
                file << "\n";
            }

            file << "#ID:" << id;
            file.close();
        }

        long long encrypt(int p_letter) {
            return powf(p_letter, 5) * 4 - 14;
        }

        int decrypt(long long p_letter) {
            return powf((p_letter + 14) / 4, 1/5.f);
        }

    private:
        string userNameAttempt;
        string passwordAttempt;
        bool accessGranted;
};

int main() {
    LoginManager loginManagerObj;
    loginManagerObj.login();

    // temp accounts: (omar, oh)

    system("pause");
}
