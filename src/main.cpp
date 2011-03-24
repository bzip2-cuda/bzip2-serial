#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <fstream.h>

#include "func.h"

int main(int argc, char* argv[])
{
  if (argc < 2) { help(argv[0]); return 1; }
  std::vector<std::string> file;
  std::string line;
  file.clear();
  std::ifstream infile (argv[1], std::ios_base::in);
  while (getline(infile, line, '\n'))
  {
    file.push_back (line);
  }

  std::cout << "Read " << file.size() << " lines.\n";

  return 0;
}

