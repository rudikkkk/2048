#include <iostream>
#include <random>
#include <vector>

// генерирует случайное число от 1 до x
auto random_number (int x)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, x);
  return dis(gen);
}

struct Line
{
  std::vector<int> line{0, 0, 0, 0};

  Line (std::vector<int> l) { update(l); }

  void update (std::vector<int> l) { line = l; }

  int& operator[] (int index) { return line[index]; }
};

std::ostream& operator<< (std::ostream& os, Line l)
{
  for (int i{0}; i < 4; ++i)
  {
    os << l[i];
  }
  return os;
}

// считает кол-во пустых клеток на игровом поле
int count_blank (std::vector<Line> board)
{
  int counter{0};
  for (int i{0}; i < 4; ++i)
  {
    for (int j{0}; j < 4; ++j)
    {
      if (board[i][j] == 0)
      {
        ++counter;
      }
    }
  }
  return counter;
}

struct Matrix
{
  std::vector<Line> board{};

  Matrix ()
  {
    board = {std::vector<int>{0, 0, 0, 0},   // Строки комментариев
             std::vector<int>{0, 0, 0, 0},   // нужны чтобы
             std::vector<int>{0, 0, 0, 0},   // автоформатирование
             std::vector<int>{0, 0, 0, 0}};  // не переносило матрицу
  }

  Line& operator[] (int index) { return board[index]; }

  std::ostream& operator<< (std::ostream& os)
  {
    for (int i{0}; i < 4; ++i)
    {
      os << board[i] << std::endl;
    }
    return os;
  }

  // вырезано за ненадобностью
  //   bool is_full ()
  //   {
  //     for (int i{0}; i < 4; ++i)
  //     {
  //       for (int j{0}; j < 4; ++j)
  //       {
  //         if (board[i][j] == 0)
  //         {
  //           return false;
  //         }
  //       }
  //     }
  //     return true;
  //   }

  // сдвигает все блоки на игровом поле вверх, совмещая одинаковые
  void up ()
  {
    for (int x{0}; x < 4; ++x)
    {
      int l{0};
      int r{1};
      while (r < 4)
      {
        if (board[l][x])
        {
          if (board[l][x] == board[r][x])
          {
            board[l][x] *= 2;
            board[r][x] = 0;
            l = r + 1;
            r += 2;
          }
          else if (!board[r][x])
          {
            ++r;
          }
          else
          {
            l = r++;
          }
        }
        else
        {
          r = ++l + 1;
        }
      }
      l = 0;
      r = 1;
      while (r < 4)
      {
        if (!board[l][x])
        {
          if (board[r][x])
          {
            board[l][x] = board[r][x];
            board[r][x] = 0;
            r = ++l + 1;
          }
          else
          {
            ++r;
          }
        }
        else
        {
          r = ++l + 1;
        }
      }
    }
  }

  // сдвигает все блоки на игровом поле вниз, совмещая одинаковые
  void down ()
  {
    for (int x{0}; x < 4; ++x)
    {
      int l{3};
      int r{2};
      while (r > -1)
      {
        if (board[l][x])
        {
          if (board[l][x] == board[r][x])
          {
            board[l][x] *= 2;
            board[r][x] = 0;
            l = r - 1;
            r -= 2;
          }
          else if (!board[r][x])
          {
            --r;
          }
          else
          {
            l = r--;
          }
        }
        else
        {
          r = --l - 1;
        }
      }
      l = 3;
      r = 2;
      while (r > -1)
      {
        if (!board[l][x])
        {
          if (board[r][x])
          {
            board[l][x] = board[r][x];
            board[r][x] = 0;
            r = --l - 1;
          }
          else
          {
            --r;
          }
        }
        else
        {
          r = --l - 1;
        }
      }
    }
  }

  // сдвигает все блоки на игровом поле влево, совмещая одинаковые
  void left ()
  {
    for (int y{0}; y < 4; ++y)
    {
      int l{0};
      int r{1};
      while (r < 4)
      {
        if (board[y][l])
        {
          if (board[y][l] == board[y][r])
          {
            board[y][l] *= 2;
            board[y][r] = 0;
            l = r + 1;
            r += 2;
          }
          else if (!board[y][r])
          {
            ++r;
          }
          else
          {
            l = r++;
          }
        }
        else
        {
          r = ++l + 1;
        }
      }
      l = 0;
      r = 1;
      while (r < 4)
      {
        if (!board[y][l])
        {
          if (board[y][r])
          {
            board[y][l] = board[y][r];
            board[y][r] = 0;
            r = ++l + 1;
          }
          else
          {
            ++r;
          }
        }
        else
        {
          r = ++l + 1;
        }
      }
    }
  }

  // сдвигает все блоки на игровом поле вправо, совмещая одинаковые
  void right ()
  {
    for (int y{0}; y < 4; ++y)
    {
      int l{3};
      int r{2};
      while (r > -1)
      {
        if (board[y][l])
        {
          if (board[y][l] == board[y][r])
          {
            board[y][l] *= 2;
            board[y][r] = 0;
            l = r - 1;
            r -= 2;
          }
          else if (!board[y][r])
          {
            --r;
          }
          else
          {
            l = r--;
          }
        }
        else
        {
          r = --l - 1;
        }
      }
      l = 3;
      r = 2;
      while (r > -1)
      {
        if (!board[y][l])
        {
          if (board[y][r])
          {
            board[y][l] = board[y][r];
            board[y][r] = 0;
            r = --l - 1;
          }
          else
          {
            --r;
          }
        }
        else
        {
          r = --l - 1;
        }
      }
    }
  }

  // печатает матрицу игрового поля в понятном для игрока виде
  void print ()
  {
    for (int i{0}; i < 4; ++i)
    {
      std::cout << "---------------------" << '\n' << '|';
      for (int j{0}; j < 4; ++j)
      {
        switch (board[i][j])
        {
        case 0:
          std::cout << "    |";
          break;
        case 2:
        case 4:
        case 8:
          std::cout << "  " << board[i][j] << " |";
          break;
        case 16:
        case 32:
        case 64:
          std::cout << ' ' << board[i][j] << " |";
          break;
        case 128:
        case 256:
        case 512:
          std::cout << ' ' << board[i][j] << '|';
          break;
        case 1024:
        case 2048:
          std::cout << board[i][j] << '|';
          break;
        default:
          break;
        }
      }
      std::cout << '\n';
    }
    std::cout << "---------------------" << std::endl;
  }

  /*
  функция добавляет на игровое поле новый блок, возвращает:
  true - успешно добавлен,
  false - недостаточно свободного места
  */
  bool new_block ()
  {
    if (count_blank(board))
    {
      int n = random_number(count_blank(board));

      int block = (random_number(100) <= 10) ? 4 : 2;
      // с шансом 10% блок равен 4, 90% - 2

      int c = 0;
      for (int i{0}; i < 4; ++i)
      {
        for (int j{0}; j < 4; ++j)
        {
          if (board[i][j] == 0)
          {
            if (++c == n)
            {
              board[i][j] = block;
            }
          }
        }
      }
      return true;
    }
    else
    {
      return false;
    }
  }

  bool is_win ()
  {
    for (int i{0}; i < 4; ++i)
    {
      for (int j{0}; j < 4; ++j)
      {
        if (board[i][j] == 2048)
        {
          return true;
        }
      }
    }
    return false;
  }
};

// вызывает методы сдвигающие блоки в соответствующих направлениях
void move (Matrix& board, char direction)
{
  switch (direction)
  {
  case 'w':
    board.up();
    break;
  case 'a':
    board.left();
    break;
  case 's':
    board.down();
    break;
  case 'd':
    board.right();
    break;

  default:
    break;
  }
}

void clear_console () { std::cout << "\033[2J" << std::endl; }

/*
отвечает за игровой процесс
(вызов функций/методов, проверку условий победы/поражения)
*/
void game ()
{
  std::cout << "Welcome to 2048 game!\n"
            << "enter w/a/s/d to start" << std::endl;
  Matrix board;
  char direction{' '};
  board.new_block();
  board.print();
  do
  {
    std::cin >> direction;
    clear_console();
    move(board, direction);
    if (board.new_block())
      board.print();
    else
      break;
  }
  while (!board.is_win());

  if (board.is_win())
  {
    std::cout << "You win!" << std::endl;
  }
  else
  {
    std::cout << "You lose!" << std::endl;
  }
}

int main ()
{
  game();
  return 0;
}
