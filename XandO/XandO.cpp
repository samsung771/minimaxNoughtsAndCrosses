#include <iostream>

int board[3][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

int turnNum = 0;

int minimaxCalls = 0;

void print(int board[3][3]) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            switch (board[y][x]) {
            case 0:
                std::cout << "- ";
                break;
            case 1:
                std::cout << "X ";
                break;
            case 2:
                std::cout << "O ";
                break;
            }
        }
        std::cout << "\n";
    }
}

int returnWin(int board[3][3]) {
    for (int column = 0; column < 3; column++)
        if (board[0][column] == board[1][column] && board[1][column] == board[2][column])
            if (board[0][column] == 1) {
                return 1;
            }
            else if (board[0][column] == 2) {
                return 2;
            }

    for (int row = 0; row < 3; row++)
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
            if (board[row][0] == 1) {
                return 1;
            }
            else if (board[row][0] == 2) {
                return 2;
            }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 1) {
            return 1;
        }
        else if (board[0][0] == 2) {
            return 2;
        }
    }

    if (board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
        if (board[2][0] == 1) {
            return 1;
        }
        else if (board[2][0] == 2) {
            return 2;
        }
    }

    int moves = 0;
    for (int y = 0; y < 3; y++) 
        for (int x = 0; x < 3; x++) 
            if (board[y][x] == 0)
                moves++;

    if (moves == 0)
        return 3;            

    return 0;
}

int minimax(int board[3][3], int depth, bool maxPlayer, int player, int alpha, int beta) {
    int result = returnWin(board);
    minimaxCalls++;

    switch (result) {
    case 1:
        return -1;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 0;
        break;
    }

    if (maxPlayer) {
        int bestScore = -99999;

        bool breakLoop = false;

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (board[y][x] == 0) {
                    int newBoard[3][3] = {
                        {board[0][0],board[0][1],board[0][2]},
                        {board[1][0],board[1][1],board[1][2]},
                        {board[2][0],board[2][1],board[2][2]}
                    };

                    newBoard[y][x] = player;

                    int score;

                    if (player == 1)
                        score = minimax(newBoard, depth - 1, false, 2, alpha, beta);
                    else
                        score = minimax(newBoard, depth - 1, false, 1, alpha, beta);

                    bestScore = score > bestScore ? score : bestScore;

                    alpha = score > alpha ? score : alpha;

                    if (beta <= alpha){
                        breakLoop = true;
                        break;
                    }
                }
            }
            if (breakLoop)
                break;
        }
        return bestScore;
    }
    else {
        int bestScore = 99999;

        bool breakLoop = false;

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (board[y][x] == 0) {
                    //copies board
                    int newBoard[3][3] = {
                        {board[0][0],board[0][1],board[0][2]},
                        {board[1][0],board[1][1],board[1][2]},
                        {board[2][0],board[2][1],board[2][2]}
                    };

                    newBoard[y][x] = player;

                    int score;

                    if (player == 1)
                        score = minimax(newBoard, depth - 1, true, 2, alpha, beta);
                    else
                        score = minimax(newBoard, depth - 1, true, 1, alpha, beta);

                    bestScore = score < bestScore ? score : bestScore;
                    
                    beta = score < beta ? score : beta;

                    if (beta <= alpha) {
                        breakLoop = true;
                        break;
                    }
                }
            }
            if (breakLoop)
                break;
        }
        return bestScore;
    }
}

void makeMove(int player) {
    int bestScore = -99999;
    int bestMove[2] = { 0 };

    minimaxCalls = 0;


    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == 0) {
                int newBoard[3][3] = {
                    {board[0][0],board[0][1],board[0][2]},
                    {board[1][0],board[1][1],board[1][2]},
                    {board[2][0],board[2][1],board[2][2]}
                };

                newBoard[y][x] = player;
                int score;

                if (player == 1)
                    score = minimax(newBoard, 9 - turnNum, false, 2, -99999, 99999);
                else
                    score = minimax(newBoard, 9 - turnNum, false, 1, -99999, 99999);

                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = x;
                    bestMove[1] = y;
                }
            }
        }
    }

    std::cout << minimaxCalls << "\n";

    board[bestMove[1]][bestMove[0]] = player;
}

int minimax(int board[3][3], int depth, bool maxPlayer, int player) {
    int result = returnWin(board);
    minimaxCalls++;

    switch (result) {
    case 1:
        return -1;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 0;
        break;
    }

    if (maxPlayer) {
        int bestScore = -99999;

        bool breakLoop = false;

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (board[y][x] == 0) {
                    int newBoard[3][3] = {
                        {board[0][0],board[0][1],board[0][2]},
                        {board[1][0],board[1][1],board[1][2]},
                        {board[2][0],board[2][1],board[2][2]}
                    };

                    newBoard[y][x] = player;

                    int score;

                    if (player == 1)
                        score = minimax(newBoard, depth - 1, false, 2);
                    else
                        score = minimax(newBoard, depth - 1, false, 1);

                    if (score > bestScore)
                        bestScore = score;
                }
            }
            if (breakLoop)
                break;
        }
        return bestScore;
    }
    else {
        int bestScore = 99999;

        bool breakLoop = false;

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (board[y][x] == 0) {
                    int newBoard[3][3] = {
                        {board[0][0],board[0][1],board[0][2]},
                        {board[1][0],board[1][1],board[1][2]},
                        {board[2][0],board[2][1],board[2][2]}
                    };

                    newBoard[y][x] = player;

                    int score;

                    if (player == 1)
                        score = minimax(newBoard, depth - 1, true, 2);
                    else
                        score = minimax(newBoard, depth - 1, true, 1);

                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
            if (breakLoop)
                break;
        }
        return bestScore;
    }
}

void makeMoveNOPRUNE(int player) {
    int bestScore = -99999;
    int bestMove[2] = { 0 };

    minimaxCalls = 0;

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == 0) {
                int newBoard[3][3] = {
                    {board[0][0],board[0][1],board[0][2]},
                    {board[1][0],board[1][1],board[1][2]},
                    {board[2][0],board[2][1],board[2][2]}
                };

                newBoard[y][x] = player;
                int score;
                if (player == 1)
                    score = minimax(newBoard, 9 - turnNum, false, 2);
                else
                    score = minimax(newBoard, 9 - turnNum, false, 1);

                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = x;
                    bestMove[1] = y;
                }
            }
        }
    }

    std::cout << minimaxCalls << "\n";

    board[bestMove[1]][bestMove[0]] = player;
}

int main()
{
    bool playing = 1;
    bool turn = 1;

    print(board);

    while (playing) {
        if (turn) {
            std::cout << "X turn\n";

            int x = 0;
            int y = 0;

            while (x <= 0 || x > 3) {
                std::cout << "input X: ";
                std::cin >> x;
            }

            while (y <= 0 || y > 3) {
                std::cout << "input Y: ";
                std::cin >> y;
            }

            if (board[y - 1][x - 1] == 0) {
                board[y - 1][x - 1] = 1;

                int eval = returnWin(board);

                if (eval == 1) {
                    std::cout << "X wins\n";
                    playing = false;
                }
                else if (eval == 2) {
                    std::cout << "O wins\n";
                    playing = false;
                }
                else if (eval == 3) {
                    std::cout << "draw\n";
                    playing = false;
                }

                turn = !turn;
                print(board);
            }
        }
        else {
            std::cout << "O turn\n";
            makeMove(2);

            int eval = returnWin(board);

            if (eval == 1) {
                std::cout << "X wins\n";
                playing = false;
            }
            else if (eval == 2) {
                std::cout << "O wins\n";
                playing = false;
            }
            else if (eval == 3) {
                std::cout << "draw\n";
                playing = false;
            }

            turn = !turn;
            print(board);
        }
        turnNum++;
    }
}