/* Copyright © 2015, Intel Corporation.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

-       Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
-       Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
-       Neither the name of Intel Corporation nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL INTEL CORPORATION BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE. */

/*! \file main.c
*  \brief Test Program to demonstrate DRNG Lib.
*
* This is the main file of the test project.
* It demonstrates the use of different APIs for RDSEED and RDRAND.
*/

#include <stdio.h>
#include <string.h>

#include "drng.h"

#define BUFFSIZE 1275

/*! \def RDSEED_CUTOFF
*	Minimum number of RDSEED results required
*/
#define RDSEED_CUTOFF 10

/*! \def RDRAND_CUTOFF
*	Minimum number of RDRAND results required
*/
#define RDRAND_CUTOFF 10

/*! \def MAX_RETRY_LIMIT
*	Maximum number of rdseed retries when nesting multiple calls to rdseed in a wrapper function.
*/
#define MAX_RETRY_LIMIT 75

int main()
{
	int i, j;
	int r;
	uint16_t u16;
	uint32_t u32;
	uint32_t array32[10];
	unsigned char buffer[BUFFSIZE];

#ifdef _NOT_WIN32
	uint64_t u64;
	uint64_t array64[10];
#endif
	

	/* -------------------- Sample code for RDRAND Starts here --------------- */


	printf("*************** RDRAND TEST STARTS HERE **************\n");

	if (RdRand_isSupported())
	{

		r = rdrand_16(&u16, 10);
		if (r != DRNG_SUCCESS) printf("rdrand instruction failed with code %d\n", r);
		printf("RDRAND uint16: %u\n", u16);

		r = rdrand_32(&u32, 10);
		if (r != DRNG_SUCCESS) printf("rdrand instruction failed with code %d\n", r);
		printf("RDRAND uint32: %u\n", u32);

		/* rdrand_64 is not defined for Windows 32bit compiler */
#ifdef _NOT_WIN32
		r = rdrand_64(&u64, 10);
		if (r != DRNG_SUCCESS) printf("rdrand instruction failed with code %d\n", r);
		printf("RDRAND uint64: %llu\n", u64);	
#endif

		r = rdrand_get_n_32(RDRAND_CUTOFF, array32);
		if (r == DRNG_SUCCESS) {
			printf("\nRDRAND 10 uint32's:\n");
			for (i = 0; i < RDRAND_CUTOFF; ++i) {
				printf("%u\n", array32[i]);
			}
		}
		else printf("rdrand instruction failed with code %d\n", r);
		
		/* rdrand_64 is not defined for Windows 32bit compiler */
#ifdef _NOT_WIN32	

		r = rdrand_get_n_64(RDRAND_CUTOFF, array64);
		if (r == DRNG_SUCCESS) {
			printf("\nRDRAND 10 uint64's:\n");
			for (i = 0; i < RDRAND_CUTOFF; ++i) {
				printf("%llu\n", array64[i]);
			}
		}
		else printf("rdrand instruction failed with code %d\n", r);

#endif

		memset(buffer, 0, BUFFSIZE);
		r = rdrand_get_bytes(BUFFSIZE, buffer);
		if (r == DRNG_SUCCESS) {
			printf("\nRDRAND Buffer of %d bytes:\n", BUFFSIZE);

			j = 0;
			for (i = 0; i < BUFFSIZE; ++i)
			{
				printf("%02x ", buffer[i]);

				++j;

				if (j == 16) {
					j = 0;
					printf("\n");
				}
				else if (j == 8) printf(" ");

			}
			printf("\n");
		}
		else printf("rdrand instruction failed with code %d\n", r);
	}

	else printf("\nRdRand instruction is not supported by your system\n");

	printf("\n***************** RDRAND TEST ENDS HERE ***************\n\n");

	/* --------------------- Sample code for RDRAND Ends here ------------------ */

	/* --------------------- Sample code for RDSEED Start here ----------------- */

	printf("\n*************** RDSEED TEST STARTS HERE **************\n");

	if (RdSeed_isSupported())
	{

		r = rdseed_16(&u16, MAX_RETRY_LIMIT);
		if (r != DRNG_SUCCESS) printf("rdseed instruction failed with code %d\n", r);
		printf("RDSEED uint16: %u\n", u16);

		r = rdseed_32(&u32, MAX_RETRY_LIMIT);
		if (r != DRNG_SUCCESS) printf("rdseed instruction failed with code %d\n", r);
		printf("RDSEED uint32: %u\n", u32);

		/* rdseed_64 is not defined for Windows 32bit compiler */
#ifdef _NOT_WIN32
		r = rdseed_64(&u64, MAX_RETRY_LIMIT);
		if (r != DRNG_SUCCESS) printf("rdseed instruction failed with code %d\n", r);
		printf("RDSEED uint64: %llu\n", u64);
#endif
		
		r = 0;
		r = rdseed_get_n_32(RDSEED_CUTOFF, array32, r, MAX_RETRY_LIMIT);
		if (r == DRNG_UNSUPPORTED)
			printf("RDSEED is not supported by system\n");

		while (r < RDSEED_CUTOFF)
		{
			printf("\nRSEED numbers %d uint32's and continuing...\n", r);
			r = rdseed_get_n_32(RDSEED_CUTOFF, array32, r, MAX_RETRY_LIMIT);
		}

		printf("\nRDSEED numbers %d uint32's:\n", r);
		for (i = 0; i < RDSEED_CUTOFF; ++i) {
			printf("%u\n", array32[i]);
		}
		
		/* rdseed_64 is not defined for Windows 32bit compiler */
#ifdef _NOT_WIN32
		r = 0;
		r = rdseed_get_n_64(RDSEED_CUTOFF, array64, r, MAX_RETRY_LIMIT);
		if (r == DRNG_UNSUPPORTED)
			printf("RDSEED is not supported by system\n");

		while (r < RDSEED_CUTOFF)
		{
			printf("\nRDSEED numbers %d uint64's and continuing...\n", r);
			r = rdseed_get_n_64(RDSEED_CUTOFF, array64, r, MAX_RETRY_LIMIT);
		}



		printf("\nRDSEED numbers %d uint64's:\n", r);
		for (i = 0; i < RDSEED_CUTOFF; ++i) {
			printf("%llu\n", array64[i]);
		}

#endif

		memset(buffer, 0, BUFFSIZE);
		r = 0;
		r = rdseed_get_bytes(BUFFSIZE, buffer, r, MAX_RETRY_LIMIT);
		if (r == DRNG_UNSUPPORTED)
			printf("RDSEED is not supported by system\n");

		else
		{

			while (r < BUFFSIZE)
			{
				printf("\nRDSEED generated %d bytes and continuing.... \n", r);
				r = rdseed_get_bytes(BUFFSIZE, buffer, r, MAX_RETRY_LIMIT);
			}

			printf("\nTotal generated RDSEED Buffer of %d bytes:\n", r);

			j = 0;
			for (i = 0; i < BUFFSIZE; ++i)
			{
				printf("%02x ", buffer[i]);

				++j;

				if (j == 16) {
					j = 0;
					printf("\n");
				}
				else if (j == 8) printf(" ");

			}
			printf("\n");
		}

	}

	else   printf("\nRdSeed instruction is not supported by your system\n");

	printf("\n*************** RDSEED TEST ENDS HERE **************\n\n");

	/* -------------------- Sample code for RDSEED Ends here --------------- */
	return 0;
}

