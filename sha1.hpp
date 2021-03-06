/*
    sha1.hpp - header of

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
    Safety fixes
        -- Eugene Hopkinson <slowriot at voxelstorm dot com>
    Add ability to run in iterative mode (peek)
        -- John Barbero Unenge <john.barbero.unenge@gmail.com>
*/

#ifndef SHA1_HPP
#define SHA1_HPP


#include <cstdint>
#include <iostream>
#include <string>

namespace sha1
{
class SHA1
{
public:
    SHA1();
    void update(const char *data, size_t size);
    void update(const std::string &s);
    void update(std::istream &is);
    std::string final();

    /**
    * Essentially the same as final, but doesn't reset the SHA1 (more expensive as it will do some copying)
    */
    std::string peek() const;

    static std::string from_file(const std::string &filename);

private:
    uint32_t m_digest[5];
    std::string m_buffer;
    uint64_t m_transforms;
};
}

#endif /* SHA1_HPP */
