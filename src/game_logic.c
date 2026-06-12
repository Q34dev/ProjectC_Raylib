// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int IsGameFinished(int cellCountX, int cellCountY, int **board)
{
    int result = 0;
    for (int row = 0; row < cellCountY; row++)
    {
        for (int col = 0; col < cellCountX; col++)
        {
            for (int i = 0; i < 4; i++)
            {
                result = CheckIfFourCellsBelongsToOnePlayer(row, col, i, cellCountX, cellCountY, board);
                if (result != 0)
                    return result;
            }
        }
    }
    return 0;
}
// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int CheckIfFourCellsBelongsToOnePlayer(int y, int x, int direction, int cellCountX, int cellCountY, int **board) // 0 - right, 1 - diagonalDownRight, 2 - down,3 - diagonalDownLeft
{
    switch (direction)
    {
    case 0:

        if (y + 3 >= cellCountY)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x] && board[y][x] == board[y + 2][x] && board[y][x] == board[y + 3][x])
        {
            return board[y][x];
        }
        return 0;
    case 1:
        if (y + 3 >= cellCountY)
        {
            return 0;
        }
        if (x + 3 >= cellCountX)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x + 1] && board[y][x] == board[y + 2][x + 2] && board[y][x] == board[y + 3][x + 3])
        {
            return board[y][x];
        }
        return 0;
    case 2:
        if (x + 3 >= cellCountX)
        {
            return 0;
        }
        if (board[y][x] == board[y][x + 1] && board[y][x] == board[y][x + 2] && board[y][x] == board[y][x + 3])
        {
            return board[y][x];
        }
        return 0;
    case 3:
        if (y + 3 >= cellCountY)
        {
            return 0;
        }
        if (x - 3 < 0)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x - 1] && board[y][x] == board[y + 2][x - 2] && board[y][x] == board[y + 3][x - 3])
        {
            return board[y][x];
        }
        return 0;
    }
}