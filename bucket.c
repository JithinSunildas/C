#include <stdio.h>

#define C0 10
#define C1 7
#define C2 4

typedef struct State {
    int vol[3];
} State;

int visited[C1 + 1][C2 + 1] = {0};

int caps[3] = {C0, C1, C2};

int is_goal(State s) { return s.vol[1] == 2 || s.vol[2] == 2; }

State pour(State current, int from, int to) {
    if (from == to)
        return current;

    State new_state = current;
    int vol_from = current.vol[from];
    int vol_to = current.vol[to];
    int c_to = caps[to];
    int space = c_to - vol_to;
    int delta = (vol_from < space) ? vol_from : space;
    new_state.vol[from] -= delta;
    new_state.vol[to] += delta;

    return new_state;
}

int grapher_dfs(State current) {
    if (is_goal(current)) {
        printf("GOAL REACHED! State: (%d, %d, %d)\n", current.vol[0], current.vol[1],
               current.vol[2]);
        return 1;
    }

    if (visited[current.vol[1]][current.vol[2]]) {
        return 0;
    }

    visited[current.vol[1]][current.vol[2]] = 1;

    for (int from = 0; from < 3; from++) {
        for (int to = 0; to < 3; to++) {
            if (from == to)
                continue;

            if (current.vol[from] > 0 && current.vol[to] < caps[to]) {
                State next_state = pour(current, from, to);
                printf("(%d, %d, %d) -> Pour %d to %d -> (%d, %d, %d)\n", current.vol[0],
                       current.vol[1], current.vol[2], from, to, next_state.vol[0],
                       next_state.vol[1], next_state.vol[2]);

                if (grapher_dfs(next_state)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void solve_puzzle() {
    State start = {0, 7, 4};

    if (!grapher_dfs(start)) {
        printf("\nNo sequence of pourings found to leave exactly 2 litres in the 7L or 4L "
               "container.\n");
    }
}

int main() {
    solve_puzzle();
    return 0;
}
