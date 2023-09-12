#include "communication.h"

namespace Communication
{
    /*
        @brief Calculate checksum of buffer (xor 2)

        @param buffer: buffer to calculate checksum of
        @param size: size of buffer (with checksum byte)

        @return checksum
    */
    byte calculateChecksum(byte buffer[], int size)
    {
        byte checksum = 0;

        for (int i = 0; i < size - 1; i++)
        {
            checksum ^= buffer[i];
        }

        checksum ^= 2;

        return checksum;
    }
}