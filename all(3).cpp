#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    string g[1000];               // карта лабиринта
    for (int i = 0; i < N; i++) cin >> g[i];

    // ищем выход E
    int ei = -1, ej = -1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (g[i][j] == 'E') { ei = i; ej = j; }

    // best[i][j] = максимум P, с которым можно прийти в клетку (i,j)
    int best[1000][1000];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            best[i][j] = -1;

    // старт — верхний левый угол (0,0)
    // если стартовая клетка — это P, считаем её
    int startP = (g[0][0] == 'P') ? 1 : 0;
    best[0][0] = startP;

    queue<pair<int,int>> q;
    q.push({0, 0});

    // 4 направления: вверх, вниз, влево, вправо
    int di[4] = {-1, 1, 0, 0};
    int dj[4] = { 0, 0,-1, 1};

    while (!q.empty()) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();

        // пробуем пойти в каждую из 4 сторон
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d];
            int nj = j + dj[d];

            // вышли за границы — пропускаем
            if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
            // стена — пропускаем
            if (g[ni][nj] == '1') continue;

            // сколько P соберём, если пойдём сюда
            int add = (g[ni][nj] == 'P') ? 1 : 0;
            int newP = best[i][j] + add;

            // если так приходить выгоднее — обновляем и идём дальше
            if (newP > best[ni][nj]) {
                best[ni][nj] = newP;
                q.push({ni, nj});
            }
        }
    }

    // ответ — сколько P собрали, дойдя до выхода
    cout << best[ei][ej] << endl;

    return 0;
}
