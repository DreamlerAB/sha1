/*
    test_sha1.cpp - test program of
 
    ============
    SHA-1 in C++
    ============
 
    100% Public Domain.
 
    Original C Code
        -- Steve Reid <steve@edmweb.com>
    Small changes to fit into bglibs
        -- Bruce Guenter <bruce@untroubled.org>
    Translation to simpler C++ Code
        -- Volker Grabsch <vog@notjusthosting.com>
    Add ability to run in iterative mode (peek)
        -- John Barbero Unenge <john.barbero.unenge@gmail.com>
*/

#include "sha1.hpp"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;


void compare(const string &result, const string &expected)
{
    const string &state = (result == expected) ? "OK" : "Failure";
    cout << "Result:   " << result << endl;
    cout << "Expected: " << expected << "  (" << state << ")" << endl;
}


/*
 * The 3 test vectors from FIPS PUB 180-1
 */

void test_standard()
{
    sha1::SHA1 checksum;

    cout << endl;
    cout << "Test:     abc" << endl;
    checksum.update("abc");
    {
        std::string expected("a9993e364706816aba3e25717850c26c9cd0d89d");
        compare(checksum.peek(), expected);
        compare(checksum.final(), expected);
    }

    cout << endl;
    cout << "Test:     abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" << endl;
    checksum.update("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    {
        std::string expected("84983e441c3bd26ebaae4aa1f95129e5e54670f1");
        compare(checksum.peek(), expected);
        compare(checksum.final(), expected);
    }


    cout << endl;
    cout << "Test:     A million repetitions of 'a'" << endl;
    for (int i = 0; i < 1000000 / 200; ++i)
    {
        checksum.update("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        );
    }
    {
        std::string expected("34aa973cd4c4daa4f61eeb2bdbad27316534016f");
        compare(checksum.peek(), expected);
        compare(checksum.final(), expected);
    }
}


/*
 * Other tests
 */

void test_other()
{
    sha1::SHA1 checksum;

    cout << endl;
    cout << "Test:     No string" << endl;
    {
        std::string expected("da39a3ee5e6b4b0d3255bfef95601890afd80709");
        compare(checksum.peek(), expected);
        compare(checksum.final(), expected);
    }

    cout << endl;
    checksum.update("");
    cout << "Test:     Empty string" << endl;
    {
        std::string expected("da39a3ee5e6b4b0d3255bfef95601890afd80709");
        compare(checksum.peek(), expected);
        compare(checksum.final(), expected);
    }

    cout << endl;
    cout << "Test:     abcde" << endl;
    checksum.update("abcde");
    {
        std::string expected("03de6c570bfe24bfc328ccd7ca46b76eadaf4334");
        compare(checksum.peek(), expected);
        compare(checksum.final(), expected);
    }

    cout << endl;
    cout << "Test:     Two concurrent checksum calculations" << endl;
    sha1::SHA1 checksum1, checksum2;
    checksum1.update("abc");
    compare(checksum2.final(), "da39a3ee5e6b4b0d3255bfef95601890afd80709"); /* "" */
    compare(checksum1.final(), "a9993e364706816aba3e25717850c26c9cd0d89d"); /* "abc" */
}


/*
 * immitate "sha1sum -b"
 */

void test_file(const string &filename)
{
    cout << sha1::SHA1::from_file(filename) << " *" << filename << endl;
}

/*
 * main
 */

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            test_file(argv[i]);
        }
    }
    else
    {
        test_standard();
        test_other();
        cout << endl;
        cout << endl;
    }

    return 0;
}
