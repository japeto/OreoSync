/**
 * @file sha1.h
 * @brief
 *      This is the header file for code which implements the Secure
 *      Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 *      April 17, 1995.
 * @details
 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the names
 *      used in the publication.
 *
 *      Please read the file sha1.c for more information.
 *
 */

#ifndef _SHA1_H_
#define _SHA1_H_

#include <stdint.h>
/*
 * If you do not have the ISO standard stdint.h header file, then you
 * must typdef the following:
 *    name              meaning
 *  uint32_t         unsigned 32 bit integer
 *  uint8_t          unsigned 8 bit integer (i.e., unsigned char)
 *  int_least16_t    integer of >= 16 bits
 *
 */

#ifndef _SHA_enum_
#define _SHA_enum_
/**
 * 
 */
enum{
    shaSuccess = 0,
    shaNull,            /*!< Null pointer parameter */
    shaInputTooLong,    /*!< input data too long */
    shaStateError       /*!< called Input after Result */
};
#endif
#define SHA1HashSize 20

/**
 * @brief This structure will hold context information for the SHA-1
 *  hashing operation
 */
typedef struct SHA1Context
{
    uint32_t Intermediate_Hash[SHA1HashSize/4]; /*!< Message Digest  */
    uint32_t Length_Low;                        /*!< Message length in bits*/
    uint32_t Length_High;                       /*!< Message length in bits*/
    int_least16_t Message_Block_Index;          /*!< Index into message block array*/
    uint8_t Message_Block[64];                  /*!< 512-bit message blocks*/
    int Computed;                               /*!< Is the digest computed?*/
    int Corrupted;                              /*!< Is the message digest corrupted?*/
} SHA1Context;

/**
 *@brief Resets the sha1 context and starts a new hashprocess.
 *@param * 	The context to reset
 *@return 0 on succes an error number otherwise
 */
int SHA1Reset(  SHA1Context *);
/**
 * @brief Data input.
 * @details This memberfunction add data to the specified context.
 * @param context 	The context to add data to
 * @param message_array 	The data to add
 * @param length 	The length of the data to add
 */
int SHA1Input(  SHA1Context *,const uint8_t *,unsigned int);
/**
 * @brief This ends the sha operation, zeroizing the context and returning the computed hash.
 * @param context The context to reset
 * @param Message_Digest 	This is an OUT parameter which contains the hash after the menberfunction returns
 * @return 0 on succes, an error-code otherwise
 */
int SHA1Result( SHA1Context *, uint8_t Message_Digest[SHA1HashSize]);

#endif
