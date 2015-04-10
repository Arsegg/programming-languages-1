#include "settings.h"

int main() {
    using namespace std;

    test();

    settings cfg("settings.cfg");
    cfg.set("author", "Arsegg");
    cfg.set("build", "1");
    cfg.set("perfectProgram", "true");
    cfg.set("version", "0.1");

    string author = cfg["author"];
    int build = cfg["build"];
    bool perfectProgram = cfg["perfectProgram"];
    double version = cfg["version"];
    cout << "author: " << author
            << "\nbuild: " << build
            << "\nperfectProgram: " << perfectProgram
            << "\nversion: " << version << "\n";

    cout << "Press any key...";
    getchar();
    return 0;
}