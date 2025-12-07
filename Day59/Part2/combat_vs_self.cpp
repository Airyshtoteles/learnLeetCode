#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Action {
    string type; // "Attack", "Guard"
    int val; // damage or unused
};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    int H, T;
    if (!(cin >> H >> T)) return 0;

    vector<Action> actions(T);
    for (int i = 0; i < T; ++i) {
        cin >> actions[i].type;
        if (actions[i].type == "Attack") {
            cin >> actions[i].val;
        } else {
            actions[i].val = 0;
        }
    }

    int current_hp = H;
    bool survived = true;

    for (int t = 0; t < T; ++t) {
        // Clone action from t-5
        if (t >= 5) {
            Action clone_act = actions[t - 5];
            Action my_act = actions[t];

            if (clone_act.type == "Attack") {
                int dmg = clone_act.val;
                if (my_act.type == "Guard") {
                    dmg /= 2;
                }
                current_hp -= dmg;
            }
            // If clone guards, no damage.
        }

        if (current_hp <= 0) {
            survived = false;
            break;
        }
    }

    if (survived) cout << "true" << endl;
    else cout << "false" << endl;

    return 0;
}
