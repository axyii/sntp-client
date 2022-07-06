#include <stdint.h>
#include <time.h>

// This timestap is the difference between 1900 and the unix epoch 1970. We subtract this from the trasmit timestamp to get the current time
#define NTP_TIMESTAMP_DELTA 2208988800ull

// Here li = 0, vn = 3, mode = 3, which corresponds to (in binary) li = 00 , vn = 011 , mode = 011 -> 00011011 which is 27 in decimal
#define LI_VN_MODE 27

typedef struct sntp_packet{
    uint8_t li_vn_mode; // li   2 bit code warning of a leap second
                        // vn   3 bit integer version number
                        // mode 3 bit number for protocol mode

    uint8_t stratum; // 8 bit unsigned indicator for stratum
    uint8_t poll_int; // 8 bit unsigned maximum interval between sucessive messages in seconds
    int8_t precision; // 8 bit signed precision of system clock
    int32_t root_delay; // 32 bit signed fixed point total roundtrip delay
    uint32_t root_disp; // 32 bit unsigned indicating the maximum error due to the clock frequency tolerance  
    uint32_t refid; // 32 bits. Reference clock identifier
    uint64_t reftim; //  64-bit Reference Timestamp
    uint64_t oritim; //  64-bit originate Timestamp
    uint64_t recitim; //  64-bit receive Timestamp 
    uint64_t trantim; //  64-bit transmit Timestamp; Time at which packet left the server. For most cases, using this gets you pretty accurate time.

    //384 Bytes
}sntp_packet;

time_t get_time(const char* host);
