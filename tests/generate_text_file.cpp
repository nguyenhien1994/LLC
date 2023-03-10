#include <bits/stdc++.h>

#define MAX_WORD_LENGTH (100)

static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alpha) - 1;

  // Random string generator function.
char genRandom()
{
    return alpha[rand() % stringLength];
}

void generateRandomTextFile(std::string filename, unsigned maxsize)
{
    std::ofstream outfile;
    outfile.open(filename.c_str());
    unsigned total = 0;
    unsigned wordsize = 0;

    while (total < maxsize)
    {
        /* Random the word length */
        wordsize = 1 + rand() % MAX_WORD_LENGTH;
        if ((total + wordsize) > maxsize)
            wordsize = maxsize - total + wordsize;

        for (unsigned i = 0; i < wordsize; i++)
        {
            outfile << genRandom();
        }
        total += wordsize;
        if (total + 1 < maxsize)
        {
            outfile << '\n';
            total++;
        }
    }
    outfile.close();
    std::cout << "File " << filename << " has been generated!" << std::endl;
}

int main (int argc, char** argv)
{
    if (argc != 3) {
        std::cout << "USAGE: " << argv[0] << " <filename> " << "<file size in bytes>" << std::endl;
        return EXIT_FAILURE;
    }

    generateRandomTextFile(argv[1], atol(argv[2]));

    return EXIT_SUCCESS;
}