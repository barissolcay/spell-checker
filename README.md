# Spell Checker

Spell Checker is a project designed to identify and suggest corrections for misspelled words in a given text file. The system reads a lexicon of correct words and an input file containing text to be checked, then outputs the misspelled words along with their possible corrections.

## Project Overview

Spell Checker is developed using C and provides functionalities for loading a lexicon, checking words in an input file, and suggesting corrections based on similarity metrics.

### Features

The project includes:
1. **Lexicon Loading**: Reads a list of correct words from a lexicon file.
2. **Word Cleaning**: Removes punctuation and converts words to lowercase.
3. **Spell Checking**: Identifies misspelled words in the input text.
4. **Correction Suggestions**: Suggests possible corrections for misspelled words based on character replacement, insertion, deletion, and swapping.
5. **Command Line Interface**: Reads input data from files and writes results to an output file.

## Technologies Used

- **C**: The primary programming language used for developing the spell checker system.

## Project Structure

The project structure includes several files organized as follows:

- **`spellchecker.c`**: The main file that implements the spell checker logic.
- **`spellchecker.exe`**: Compiled executable file for running the spell checker.
- **`input.txt`**: The input file containing text to be checked for spelling errors.
- **`lexicon.txt`**: The lexicon file containing a list of correct words.
- **`output.txt`**: The output file containing misspelled words and their suggested corrections.

## Usage

### Prerequisites

To run the project, you need to have the following installed:
- **C Compiler**: Ensure you have a C compiler installed on your system.

### Running the Project

1. Clone the repository:

    ```bash
    git clone https://github.com/barissolcay/spell-checker.git
    cd spell-checker
    ```

2. Compile the C file:

    ```bash
    gcc spellchecker.c -o spellchecker
    ```

3. Run the Spell Checker with the input and lexicon files:

    ```bash
    ./spellchecker
    ```

    The program will read from `input.txt` and `lexicon.txt`, and write the results to `output.txt`.

## Contributing

We welcome contributions to improve the Spell Checker project. Feel free to open issues or submit pull requests if you have suggestions for improvements or find any bugs.

## License

MIT License

```markdown
MIT License

Copyright (c) 2025 Baris Solcay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
