#ifndef __MODIFICATION_H__
#define __MODIFICATION_H__

// Holds data for a modification within a Chunk.
struct Modification
{
    unsigned char data;

    Modification()
        : data(0)
    {
    }

    Modification(unsigned char const d)
        : data(d)
    {
    }

    static Modification block(unsigned char const d)
    {
        return Modification(d);
    }
};

#endif // __MODIFICATION_H__