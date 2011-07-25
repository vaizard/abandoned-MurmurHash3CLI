/*
 *  MurmurHash3CLI - command line interface for MurmurHash3
 *  Copyright (C) 2011 Jaromir Capik <tavvva@email.cz>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <cstdlib>
#include <sstream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <iterator>
#include <iostream>
#include "MurmurHash3.h"

#define MURMURHASH3_OUTPUT_LENGTH	16

typedef uint8_t MurmurHash3_output_t[MURMURHASH3_OUTPUT_LENGTH];
typedef uint32_t MurmurHash3_seed_t;

using namespace std;

int main(int argc, char **argv)
{
  if (argc != 2) {
    cerr << "Usage : MurmurHash3CLI <32bit-decimal-seed>" << endl;
    cerr << endl;
    cerr << "Application reads the input data from the standard input" << endl;
    cerr << "and prints the result 128-bit hex coded hash to the standard output." << endl;
    cerr << "Seed can be either signed or unsigned." << endl;
    exit(EXIT_FAILURE);
  }

  // convert the seed argument to int32_t/uint32_t with type checking
  istringstream seed_arg(argv[1]);
  MurmurHash3_seed_t seed;
  if ((seed_arg >> seed) && (seed_arg.eof())) {
    // conversion successful
    // we could test the input for negative values, but we don't want to do that
    // that allows us to be signed/unsigned independent
    ;
  } else {
    // conversion failed
    cerr << "Seed invalid or out of range." << endl;
    exit(EXIT_FAILURE);
  }

  // stdin -> string    (copy until EOF)
  cin >> noskipws;
  istream_iterator<char> it(std::cin);
  istream_iterator<char> end;
  string input(it, end);

  // Hash calculation
  MurmurHash3_output_t output;
  MurmurHash3_x64_128(input.c_str(), input.length(), seed, output);

  // Write the hex coded hash to stdout
  for (int i = 0; i < MURMURHASH3_OUTPUT_LENGTH; i++) {
    cout << setfill('0') << setw(2) << hex << int(output[i]);
  }

  return EXIT_SUCCESS;
}
