/*
 * input:
 * 040873060
 * 780010025
 * 000004000
 * 408000007
 * 930050048
 * 600000201
 * 000700000
 * 590030074
 * 070469030
 *
 * human look:
 * 040|873|060
 * 780|010|025
 * 000|004|000
 * -----------
 * 408|000|007
 * 930|050|048
 * 600|000|201
 * -----------
 * 000|700|000
 * 590|030|074
 * 070|469|030
 *
 */

#include <iostream>

using namespace std;

#define LEN 9

class Sudoku {
public:
    Sudoku(char input[LEN][LEN]);
    void pp(); //print puzzle.
    bool cal(); //calculate. return false if no answer.
private:
    int puzzle[LEN][LEN] = {{0}}; //懒，就不用char了
    unsigned short horizontal[LEN] = {0}; //横
    unsigned short vertical[LEN] = {0}; //竖
    unsigned short block[LEN] = {0}; //块
    void h_set(int x, int v) { horizontal[x] |= (1<<v); } 
    void v_set(int y, int v) { vertical[y] |= (1<<v); } 
    void b_set(int x, int y, int v) { block[3*(x/3)+y/3] |= (1<<v); } 
    void h_clear(int x, int v) { horizontal[x] &= ~(1<<v); }
    void v_clear(int y, int v) { vertical[y] &= ~(1<<v); }
    void b_clear(int x, int y, int v) { block[3*(x/3)+y/3] &= ~(1<<v); }
    bool h_valid(int x, int v) { return 0 == (horizontal[x] & (1<<v)); }
    bool v_valid(int y, int v) { return 0 == (vertical[y] & (1<<v)); }
    bool b_valid(int x, int y, int v) { return 0 == (block[3*(x/3)+y/3] & (1<<v)); }
    bool valid(int x, int y, int v) { return h_valid(x,v) && v_valid(y,v) && b_valid(x,y,v); }
};

Sudoku::Sudoku(char input[LEN][LEN])
{
    for (int i=0; i<LEN; ++i) {
        for (int j=0; j<LEN; ++j) {
            int v = input[i][j] - '0';
            puzzle[i][j] = v; 
            h_set(i,v);v_set(j,v);b_set(i,j,v);
        }
    }
}

void Sudoku::pp()
{
    for (int i=0; i<LEN; ++i) {
        for (int j=0; j<LEN; ++j)
            cout << puzzle[i][j];
        cout << endl;
    }
}

bool Sudoku::cal()
{
    for (int i=0; i<LEN; ++i) {
        for (int j=0; j<LEN; ++j) {
            //跳过已经有数字的
            if (puzzle[i][j]) continue;

            //从1到9中选一个
            for (int v=1; v<=LEN; ++v) {
                //横竖块不满足的跳过 
                if (!valid(i,j,v)) continue;

                //设置
                puzzle[i][j] = v;
                h_set(i,v);v_set(j,v);b_set(i,j,v);
                if (cal())
                    return true;
                else {
                    //失败了得把数字擦掉
                    puzzle[i][j] = 0;
                    h_clear(i,v);v_clear(j,v);b_clear(i,j,v);
                }
            }
            //1-9都失败了，返回失败
            return false;
        }
    }

    //全都有数字，返回成功
    return true;
}

int main()
{
    cout << "Input the puzzle:" << endl;
    char input[LEN][LEN];
    for (int i=0; i<LEN; ++i)
        for (int j=0; j<LEN; ++j)
            cin >> input[i][j];

    Sudoku s(input);
    bool res = s.cal();
    if (res) {
        cout << "Result:" << endl;
        s.pp();
    } else
        cout << "No answer!" << endl;

    return 0;
}
