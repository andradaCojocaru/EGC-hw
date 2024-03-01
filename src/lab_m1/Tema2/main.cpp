#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string s;
    // while(getline(fin, s)) {
    //     if (s[0] == 'l') {
    //         continue;
    //     }
    //     for (int i = 0; i < s.size(); i++) {
    //         if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.' || s[i] == '-') {
    //             fout << s[i];
    //         }
    //         if (s[i] == ',') {
    //             fout << " ";
    //         }
    //     }
    //     fout << '\n';
    // }
    int count = 189;
    for (int i = 0; i < count; i++) {
        float x, y;
        while (fin >> x >> y) {
            fout << "glm::vec3(" << x << ", y, "  << y << ")," << '\n';
        }
    }
}